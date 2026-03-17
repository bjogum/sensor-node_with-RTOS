## Alarm sensor node, with custom task scheduler → ![](https://img.shields.io/badge/status-under%20development-8A2BE2)
#### Overview
This is a modular component of a larger IoT system (Smart Hub) consisting of multiple nodes.

This repo handles all sensor data for an alarm system, utilizing an Arduino Uno R4 WiFi with a bespoke non-blocking task scheduler to manage concurrent sensor polling and network communication. Sensor data is distributed to neighboring nodes via Wi-Fi using the MQTT protocol, and via BLE.

#### Architecture - Event-driven Real-Time Scheduler

The system decouples critical detection from application logic for maximum reliability:

* Hardware Interrupts (PIR/Reed): Ensures microsecond detection latency, independent of system load.
* Deterministic Timing (SysTick): Provides a stable 1ms hardware time-base for precise logging and synchronization.
* Asynchronous Execution: The main loop handles status LEDs, indoor temp/humidity, and resource-heavy communication (BLE/WiFi) by acting on flags and timestamps from the hardware layer.

#### Setup - Info

1) Update your WIFI: SSID + Password → plattformio.ini
2) Update your Broker/Zero IP adress → mqtt_client.cpp
3) Startup time ~20s → when system is up and running : red blink on the led matrix

#### Hardware
* MCU: Arduino Uno R4 WiFi

* Sensor:

| Sensors       | Detect                        | PIN @ Arduino | Transmits to     | Implemented  | External Interrupts |
| ------------- |:-----------------------------:|:-------------:|:----------------:|:------------:|:-------------------:|
| DHT11         | Indoor: temp + humidity       | D2 (P104)     |  Broker @ MQTT   | Yes          |                     |
| DS18B20       | Temp, fire  (pull-up needed)  | D5 (P107)     | *(Broker @ MQTT)*  | Yes          |                     |
| MQ2           | Gas, fire                     |  -            | *(Broker @ MQTT)*  |              |                     |
| Rain-sensor   | Water leak                    |  -            | *(Broker @ MQTT)*  |              |                     |
| PIR           | Motion                        | D4 (P106)     | *(ESP32 @ BLE)*    |              | Yes                 |
| Reed          | Open door or window           | D3 (P105)     | *(ESP32 @ BLE)*    | Yes          | Yes                 |