# Anton-s-ESP32-drone
---
## What is this project
* This is a micro drone that uses the esp32 as a FC. 
---
## Why i made this project
* I made this project because I wanted a small drone, that I can pull out of my pocket and just fly it.
* I dont have a drone. 
---
## Images 

--- 
* This is an image of the schematic:
<img width="467" height="431" alt="Screenshot 2026-04-19 160554" src="https://github.com/user-attachments/assets/cc9e3046-34fd-4cca-98af-66d235bdaedb" />


* This is the PCB:

<img width="438" height="488" alt="Screenshot 2026-04-19 202837" src="https://github.com/user-attachments/assets/c6318c91-cc1e-46a6-b404-efe60fb2d359" />

* The 3D model of the PCB:
<img width="428" height="437" alt="Screenshot 2026-05-20 231837" src="https://github.com/user-attachments/assets/f02d127b-5f25-4ad2-be1d-6c2d91bb2989" />

* This is an image of the Frame with the XIAO in it:
<img width="638" height="419" alt="Screenshot 2026-05-06 145236" src="https://github.com/user-attachments/assets/547b3e06-9dd6-4a17-af0d-b28bd539ee38" />

---
## Assembly
* Firt you need to soulder the components on the top and bottom side of the PCB (I preffer to soulder the small ones first then the big ones).
* Then I put the cables for the 4 motors trough the small holes and soulder them to the PCB.
* After that I put the motor into their motor mounts.
* Then you put the top cap on.
* And last you strap the battery with zipties to the body. 
---
## BOM
| Component | Purpose | Qty | Cost (USD) | Distributor |
|---|---|:---:|:---:|---|
| [Seeed Studio XIAO ESP32-S3 Sense](https://www.seeedstudio.com/XIAO-ESP32S3-Sense-p-5639.html) | Camera and controller | 1 | $25.00 | Seeed Studio |
| [MPU-6050](https://www.aliexpress.com/item/1005007986741850.html?pdp_ext_f=%7B%22sku_id%22%3A%2212000043166583348%22%7D&sourceType=1&spm=a2g0o.wish-manage-detail.0.0) | Gyroscope / IMU | 1 | $7.20 | AliExpress |
| [Motors](https://www.aliexpress.com/item/1005006105092170.html?pdp_ext_f=%7B%22sku_id%22%3A%2212000035766688570%22%7D&sourceType=1&spm=a2g0o.wish-manage-detail.0.0) | Spin propellers | 1 | $5.77 | AliExpress |
| [Propellers](https://www.aliexpress.com/item/1005005351811890.html?pdp_ext_f=%7B%22sku_id%22%3A%2212000032714337732%22%7D&sourceType=1&spm=a2g0o.wish-manage-detail.0.0) | Provides lift | 1 | $5.90 | AliExpress |
| [Battery](https://www.aliexpress.com/item/1005006762177546.html?pdp_ext_f=%7B%22sku_id%22%3A%2212000038217592894%22%7D&sourceType=1&spm=a2g0o.wish-manage-detail.0.0) | Power source | 1 | $6.50 | AliExpress |
| [Battery Connector](https://www.aliexpress.com/item/1005003431613901.html?pdp_ext_f=%7B%22sku_id%22%3A%2212000028261810379%22%7D&sourceType=1&spm=a2g0o.wish-manage-detail.0.0) | Connects battery to PCB | 1 | $3.20 | AliExpress |
| [Transistors](https://www.aliexpress.com/item/1005011574380229.html?pdp_ext_f=%7B%22sku_id%22%3A%2212000055960036705%22%7D&sourceType=1&spm=a2g0o.wish-manage-detail.0.0) | Motor switching (SI2300DS) | 1 | $2.50 | AliExpress |
| [Diodes](https://www.aliexpress.com/item/1005007160563285.html?pdp_ext_f=%7B%22sku_id%22%3A%2212000039653324544%22%7D&sourceType=1&spm=a2g0o.wish-manage-detail.0.0) | Flyback protection (1N4148W) | 1 | $2.20 | AliExpress |
| [Resistors](https://www.aliexpress.com/item/1005010519485476.html?pdp_ext_f=%7B%22sku_id%22%3A%2212000052676754449%22%7D&sourceType=1&spm=a2g0o.wish-manage-detail.0.0) | Pull-down / voltage divider | 1 | $4.10 | AliExpress |
| [Capacitors](https://www.aliexpress.com/item/1005007470747384.html?pdp_ext_f=%7B%22sku_id%22%3A%2212000040888645899%22%7D&sourceType=1&spm=a2g0o.wish-manage-detail.0.0) | Motor decoupling | 1 | $1.90 | AliExpress |
| [LED](https://www.aliexpress.com/item/1005010338676055.html?pdp_ext_f=%7B%22sku_id%22%3A%2212000052257941480%22%7D&sourceType=1&spm=a2g0o.wish-manage-detail.0.0) | Status indicator | 1 | $5.20 | AliExpress |
| PCB | Component mounting | 1 | $4.30 | JLCPCB |

**Total Estimated Cost: ~$73.77**

---
## Side note 
* I will change the body of the drone. This one if only for demonstration and I think it wont be the strongest and will bend.
* Also the motor mounts are not the best way to secure them and easiest to place after assembly step 3.
* There will be firmware for a phone and the ESP, but I cant make it now due to the lack of materials to test it. I have added one that will be like a blueprint and I will modify it. 
## Credits

* Designed and built by *(Anton/ Anton-2785-bit)
* Inspired by open‑source mechanical keyboard and hackpad communities (https://macondo.hackclub.com/).
