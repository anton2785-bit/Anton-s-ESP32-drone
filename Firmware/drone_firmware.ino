#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <MPU6050.h>

// ─── CONFIG ───────────────────────────────────────────────
const char* SSID     = "ESP32_Drone";
const char* PASSWORD = "drone1234";
const int   UDP_PORT = 4210;

#define MOTOR_FL  1   // GPIO1
#define MOTOR_FR  2   // GPIO2
#define MOTOR_RL  3   // GPIO3
#define MOTOR_RR  4   // GPIO4
#define BAT_PIN   10  // GPIO10
#define LED_PIN   43  // Status LED

#define PWM_FREQ  20000
#define PWM_RES   8     // 8-bit = 0–255

// ─── PID GAINS (tune these) ───────────────────────────────
float Kp = 1.2, Ki = 0.02, Kd = 0.5;

// ─── GLOBALS ──────────────────────────────────────────────
WiFiUDP udp;
MPU6050 mpu;

float pitch = 0, roll = 0, yaw = 0;
float pitchPrev = 0, rollPrev = 0;
float pitchInt = 0, rollInt = 0;

int throttle = 0;
float targetPitch = 0, targetRoll = 0, targetYaw = 0;

unsigned long lastPacket = 0;
unsigned long lastLoop   = 0;
float dt = 0.004;

// ─── MOTOR HELPERS ────────────────────────────────────────
void setMotor(int pin, int val) {
  val = constrain(val, 0, 255);
  ledcWrite(pin, val);
}

void motorsOff() {
  setMotor(MOTOR_FL, 0);
  setMotor(MOTOR_FR, 0);
  setMotor(MOTOR_RL, 0);
  setMotor(MOTOR_RR, 0);
}

// ─── SETUP ────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  ledcAttach(MOTOR_FL, PWM_FREQ, PWM_RES);
  ledcAttach(MOTOR_FR, PWM_FREQ, PWM_RES);
  ledcAttach(MOTOR_RL, PWM_FREQ, PWM_RES);
  ledcAttach(MOTOR_RR, PWM_FREQ, PWM_RES);
  motorsOff();

  Wire.begin(5, 6); // SDA=GPIO5, SCL=GPIO6
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 not found!");
    while (1) { digitalWrite(LED_PIN, !digitalRead(LED_PIN)); delay(200); }
  }

  WiFi.softAP(SSID, PASSWORD);
  udp.begin(UDP_PORT);

  Serial.println("Drone ready. IP: " + WiFi.softAPIP().toString());
  digitalWrite(LED_PIN, HIGH);
}

// ─── READ IMU ─────────────────────────────────────────────
void readIMU() {
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  float accPitch = atan2(ay, az) * 180.0 / PI;
  float accRoll  = atan2(-ax, az) * 180.0 / PI;
  float gyroP    = gx / 131.0;
  float gyroR    = gy / 131.0;

  // complementary filter
  pitch = 0.98 * (pitch + gyroP * dt) + 0.02 * accPitch;
  roll  = 0.98 * (roll  + gyroR * dt) + 0.02 * accRoll;
}

// ─── PARSE UDP PACKET ─────────────────────────────────────
// Expected format: "T:150,P:0.5,R:-0.3,Y:0.0"
void parsePacket(char* buf) {
  char* token = strtok(buf, ",");
  while (token != NULL) {
    if (strncmp(token, "T:", 2) == 0) throttle     = atoi(token + 2);
    if (strncmp(token, "P:", 2) == 0) targetPitch  = atof(token + 2);
    if (strncmp(token, "R:", 2) == 0) targetRoll   = atof(token + 2);
    if (strncmp(token, "Y:", 2) == 0) targetYaw    = atof(token + 2);
    token = strtok(NULL, ",");
  }
  lastPacket = millis();
}

// ─── PID ──────────────────────────────────────────────────
float pidCalc(float target, float actual, float& integral, float prev) {
  float err = target - actual;
  integral += err * dt;
  integral = constrain(integral, -50, 50);
  float deriv = (actual - prev) / dt;
  return Kp * err + Ki * integral - Kd * deriv;
}

// ─── BATTERY ──────────────────────────────────────────────
float readBattery() {
  int raw = analogRead(BAT_PIN);
  return (raw / 4095.0) * 3.3 * 2.0;
}

// ─── MAIN LOOP ────────────────────────────────────────────
void loop() {
  unsigned long now = millis();
  dt = (now - lastLoop) / 1000.0;
  if (dt < 0.002) return;
  lastLoop = now;

  // receive UDP
  char buf[64];
  int len = udp.parsePacket();
  if (len > 0) {
    udp.read(buf, sizeof(buf) - 1);
    buf[len] = '\0';
    parsePacket(buf);
  }

  // safety: cut motors if no packet for 500ms
  if (millis() - lastPacket > 500) {
    motorsOff();
    return;
  }

  readIMU();

  float pitchOut = pidCalc(targetPitch, pitch, pitchInt, pitchPrev);
  float rollOut  = pidCalc(targetRoll,  roll,  rollInt,  rollPrev);

  pitchPrev = pitch;
  rollPrev  = roll;

  // motor mixing (+ quad config)
  int fl = throttle + pitchOut - rollOut - targetYaw;
  int fr = throttle + pitchOut + rollOut + targetYaw;
  int rl = throttle - pitchOut - rollOut + targetYaw;
  int rr = throttle - pitchOut + rollOut - targetYaw;

  setMotor(MOTOR_FL, fl);
  setMotor(MOTOR_FR, fr);
  setMotor(MOTOR_RL, rl);
  setMotor(MOTOR_RR, rr);

  // send telemetry back every 100ms
  static unsigned long lastTelem = 0;
  if (millis() - lastTelem > 100) {
    char telem[64];
    float bat = readBattery();
    snprintf(telem, sizeof(telem), "P:%.1f,R:%.1f,B:%.2f", pitch, roll, bat);
    udp.beginPacket(udp.remoteIP(), udp.remotePort());
    udp.write((uint8_t*)telem, strlen(telem));
    udp.endPacket();
    lastTelem = millis();
  }
}
