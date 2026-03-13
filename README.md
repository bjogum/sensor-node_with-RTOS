## Alarm sensor node, with custom task scheduler → ![](https://img.shields.io/badge/status-under%20development-8A2BE2)
#### Overview
This is a modular component of a larger IoT system (Smart Hub) consisting of multiple nodes.

This repo handles all sensor data for an alarm system, utilizing an Arduino Uno R4 WiFi with a bespoke non-blocking task scheduler to manage concurrent sensor polling and network communication. Sensor data is distributed to neighboring nodes via Wi-Fi using the MQTT protocol, and via BLE.


...more info is coming

#### Architecture
...

#### Features
...

#### Hardware
* MCU: Arduino Uno R4 WiFi

* Sensors:

| Sensors       | Detect         | PIN |
| ------------- |:--------------:| ---:|
| DHT11         | In: temp+humid | D2  |
| DS18B20       | Temp, fire     | D5  |
| MQ2           | Gas, fire      |  -  |
| PIR           | Motion         |  -  |
| Reed          | Open door/win  |  -  |
| Rain-sensor   | Water leak     |  -  |

