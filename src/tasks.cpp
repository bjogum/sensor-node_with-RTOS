// --- definierar HUR (sekvensen) och VAD som ska köras --- 
#include "tasks.h"
#include "alarm.h"
#include "sensor_dht11.h"
#include <stdio.h>
#include <Arduino.h>
#include "sensor_ds18b20.h"
#include "indicateStatus.h"
#include "wifi_manager.h"
#include "mqtt_client.h"
#include "sensor_motion.h"
#include "sensor_reed.h"
#define numOfPrio3Sensors 2

void initComponents(){
    initWiFi();
    initDHT();
    initDS18B20();
    initPIR();
    initReed();
    initMatrix();
}

int readPrio2Sensors(){
    static int currentSensor = READING_DS18B20; // static -> sätts endast EN gång (init)
    // för att minimiera jitter för "låg-prio" sensorer - läs asynkront, en sensor åt gången.
    switch (currentSensor)
    {
    case READING_DS18B20: 
        getDS18B20data();
        currentSensor = READING_MQ2; 
        return 0;

        
    case READING_MQ2:
        //läs smoke sensor
        currentSensor = READING_DS18B20; 
        return 0;
    }
};

int readPrio3Sensors(){
    static int currentSensor = READING_DHT; // static -> sätts endast EN gång (init)
    // för att minimiera jitter för "låg-prio" sensorer - läs asynkront, en sensor åt gången.
    switch (currentSensor)
    {
    case READING_DHT: 
        if (getDHTData()){
            // -- DEBUG --
            Serial.print("DHT11: ");
            Serial.print(node.sensors.indoorTemp, 1); // 1 decimal
            Serial.print(" °C | Humidity: ");
            Serial.print(node.sensors.indoorHumidity, 1);
            Serial.println(" %");
            // -- DEBUG --
        } else {
            Serial.print("<< DHT11 ERROR >>");
        }


        currentSensor = READING_WATER; 
        return 0;

        
    case READING_WATER:
        //läs water leak
        Serial.println("Checking 'Water-Leak'..\n"); 
        currentSensor = READING_DHT;
        return 0;
    }
};