#include "alarm.h"
#include "mqtt_client.h"
#include "wifi_manager.h"
#include <ArduinoMqttClient.h>
#include <ArduinoJson.h>

#define MQTT_BROKER "192.168.1.101"
#define MQTT_PORT 1883

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = MQTT_BROKER;
int port = MQTT_PORT;
const char indoorTempTopic[] = "sensor/indoorTemp";
const char indoorHumidTopic[] = "sensor/indoorHumidity";

//bool tryMQTTconnect = false;
unsigned long MQTTConnectTimer = 0;
unsigned long MQTTLastSendTimer = 0;

// funktionen håller igång MQTT samt skickar/ta emot meddelanden.
bool manageMQTT() {
    // d) LWT: Maxtid, 10s offline -> ESP ger larm 
    // skriv testamentet här...
    

    // om det gått 2 sek sen connect & nu conencted, skicka init
    if ((node.sysTime - MQTTConnectTimer >= 2000) && (!node.connectionStatus.mqttIsActive)){
        MQTTConnectTimer = node.sysTime;

        if (mqttClient.connect(broker, port)) {
            //tryMQTTconnect = false;
            node.connectionStatus.mqttIsActive = true;
            initSendMQTT();
            return true;

        } else {
            node.connectionStatus.mqttIsActive = false;
            Serial.println("<< MQTT : Connect error >> Test in 2 sec");
            return false;
        }
    }

}

void initSendMQTT(){
    // a) skicka all intressant data vid "init" - sensorer, heartbeat, RSSI, ..
    /*
    // ----TEST ----> topic + meddelandet, temp.
    mqttClient.beginMessage(indoorTempTopic);
    mqttClient.print(node.sensors.indoorTemp);
    if (mqttClient.endMessage()) {
        Serial.println("Temp: Sent OK!");
    }
    // ----TEST ----> topic + meddelandet, humid.
    mqttClient.beginMessage(indoorHumidTopic);
    mqttClient.print(node.sensors.indoorHumidity);
    if (mqttClient.endMessage()) {
        Serial.println("Humidity: Sent OK!");
    }

    // .poll() : håller igång anslutningen (ping) - och skickar/tar emot MQTT
    mqttClient.poll();
    */
    }

// -- avgör om datan behöver publiseras - Beroende på sensorer/status samt state --
void sendMQTT(){
    // .poll() : håller igång anslutningen (ping) - och skickar/tar emot MQTT
    mqttClient.poll();
    
    if (node.sysTime - MQTTLastSendTimer >= 2000){
        MQTTLastSendTimer = node.sysTime;
            // ----TEST ----> topic + meddelandet, temp.
        mqttClient.beginMessage(indoorTempTopic);
        mqttClient.print(node.sensors.indoorTemp);
        if (mqttClient.endMessage()) {
            Serial.println("Temp: Sent OK!");
        }
        // ----TEST ----> topic + meddelandet, humid.
        mqttClient.beginMessage(indoorHumidTopic);
        mqttClient.print(node.sensors.indoorHumidity);
        if (mqttClient.endMessage()) {
            Serial.println("Humidity: Sent OK!");
        }
    }
    // b) skicka förändrad data (enl. u1 & u2)
        // b01) -> temp/fukt (DHT11) vid skillnader && max en gång varje sek..?                      [alla state]
        // b02) -> övrigta sensorer -> vid förändring / triggning -- skicka direkt (prio 1 & 2)      [alla larmade state, utan PIR om "home"]
    
        // c) skicka heartbeat var 30e sek (bra trots LWT)
}

void receiveMQTT(){


    // TA EMOT data (sub) från ESP -> "state"
}