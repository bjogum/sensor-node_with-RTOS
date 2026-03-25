## Alarm sensor node, with RTOS → ![](https://img.shields.io/badge/status-under%20development-8A2BE2)
#### Overview
This is a modular component of a larger IoT system (Smart Hub) consisting of multiple nodes.

This repository manages sensor data for an alarm system running on an Arduino Uno R4 WiFi. The system is designed to be deterministic with non-blocking functions for maximum reliability.

#### Architecture - RTOS & Tasks

The system utilizes Hardware Interrupts for immediate sensor detection and FreeRTOS for task orchestration and Binary Semaphores.
* Priority 3 (High): Critical alarm events (PIR/Reed/MQ2/DS18B20) via hardware interrupts & semaphores.
* Priority 2 (Medium): Network communication (WiFi/MQTT/BLE).
* Priority 1 (Low): System monitoring (Temp/Water leak).
* Software Timer: Used for a real-time LED status indication, without the memory cost of a dedicated task.

#### Alarm-procedure ####

When a alarm is detected, at fire or intrution:
1) The system notis the alarm and update the state machine
2) The alarm info is stored in a packed struct of 5 bytes, "AlarmInfo"
   1) Timestamp is added (unix time)
   2) Alarmtype is added (what kind of alarm)
3) The alarm info is sending three times to a queue (AlarmQueue)
4) The xNetworkTask wake up at queue - and send the alarm to BLE.

#### BLE & MQTT ####

BLE:
  * Heartbet every 5s
  * Send critical alarms, as packages.

MQTT:
* Heartbet every 10s
* Has Will & Testament
  * Is the sensor-node stop sending heartbeats - a 'OFFLINE status' will be publish of the Broker.
* Send info every 30s: temp/humidity & ( soon water leak )

#### Setup - Info

1) Update your WIFI: SSID + Password → plattformio.ini
2) Update your Broker/Zero IP adress → mqtt_client.cpp

**Visual Diagnostic (LED matrix)**
* Flash patterns:
  * System ready: Slow blink
  * Not connected to WiFi, MQTT or BLE: Fast blink

* LED states: 
  * Idle → 2x2 center LEDs
  * Alarming → ALL matrix LEDs

#### Upcomming

* Implement & integrate other sensors (MQ2, PIR, Water-leak)

#### Hardware
* MCU: Arduino Uno R4 WiFi

* Sensor:

| Sensors       | Detect                        | PIN @ Arduino | Transmits to     | Implemented  | External Interrupts |
| ------------- |:-----------------------------:|:-------------:|:----------------:|:------------:|:-------------------:|
| DHT11         | Indoor: temp + humidity       | D2 (P104)     |  Broker @ MQTT   | Yes          |                     |
| DS18B20       | Temp, fire  (pull-up needed)  | D5 (P107)     |  ESP32 @ BLE     | Yes          |                     |
| MQ2           | Gas, fire                     |  -            |  ESP32 @ BLE     |              | Yes                 |
| Rain-sensor   | Water leak                    |  -            | *(Broker @ MQTT)*  |              |                     |
| PIR           | Motion                        | D4 (P106)     |  ESP32 @ BLE     |              | Yes                 |
| Reed          | Open door or window           | D3 (P105)     |  ESP32 @ BLE     | Yes          | Yes                 |

#### More info ####

* *RTC (Time stamp)*
  * The clock is synchronized via WiFi on startup
  * Every alarm event has an time stamp