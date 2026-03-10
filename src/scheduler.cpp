// --- definierar NÄR resp. funktion ska köras ---
#include <stdio.h>
#include <Arduino.h>
#include "tasks.h"
#include "alarm.h"
#include "wifi_manager.h"
#include "indicateStatus.h"
#include "mqtt_client.h"
#define WAKE_UP_SYSTEM_MS 20000 // maybe 60s ? (MQ2 & MQTT behöver tid..)


// enum för resp. PRIO-klass.
enum TaskType {sensorPrio1, sensorPrio2, sensorPrio3, serviceCheckAlarm, serviceBLE, serviceWiFi, serviceMQTT};

// struct för resp. TASK, innehållande: [Prioklass/funktion] - [intervall (ms)] - [senaste körningen (ms)]
// [ersätter ev. prioType med funktionspekare senare..]
struct Tasks {
    TaskType prioType;
    const unsigned long intervall;
    unsigned long lastRun;
};

// Tasks-array: "taskList" -> innehåller samtliga TASKS. ( utelämnar parametern lastRun->0) ) 
Tasks taskList[] = {
    {sensorPrio1, 20},    // Security sensors              -> 20ms?
    {sensorPrio2, 500},   // Saftey sensors                -> 300ms
    {sensorPrio3, 1500},  // Temp, fukt, lekage            -> 1500ms
    {serviceCheckAlarm, 100},  // Kolla om larm är aktivt  -> 1500ms
    {serviceBLE, 100,50}, // håll BLE aktivt & skcka data - lastRun 50ms ("offset"): underviker krock med Wifi-> 100ms
    {serviceWiFi, 5000},   // håll WiFi aktivt & skcka data -> 5000ms
    {serviceMQTT, 100},   // håll WiFi aktivt & skcka data -> 100ms
};

void taskScheduler(){
  const int numOfTasks = sizeof(taskList) / sizeof(taskList[0]);

  // Loopa igenom listan med TASKS (taskList) & checka tiden.
  for (int i; i<numOfTasks; i++){
    if (node.sysTime - taskList[i].lastRun >= taskList[i].intervall){

      // kör den task det är dax att köra
      switch (taskList[i].prioType)
      {
        
      case sensorPrio1:
        statusLED();
        // security
        // triggar någon sensor -> sätts extern var. till True
        break;

      case sensorPrio2:
        Serial.println("\n<-----PRIO2_READ----->\n");
        readPrio2Sensors();  
        // triggar någon sensor -> sätts extern var. till True
        break;

      case sensorPrio3:
        Serial.println("\n<-----PRIO3_READ----->\n");
        readPrio3Sensors();
        
        break;
      
      case serviceCheckAlarm:
        checkAlarmStatus();
        break;
      
      case serviceBLE:
        // håll BLE igång -> skicka aktuell data
        break;

      case serviceWiFi:
        // kolla så wifi är anslutet
        manageWiFi();
        break;

      case serviceMQTT:
        // sub/pub mqtt
        manageMQTT();
        sendMQTT();
        receiveMQTT();
        break;    

      }
      taskList[i].lastRun = node.sysTime;
    }
  };
};

void startingSystem(){
    if (node.runStatus == WAKING_UP){
      if ((manageWiFi()) && (millis() >= WAKE_UP_SYSTEM_MS) && (manageMQTT())) {
        node.runStatus = RUNNING;
        Serial.println("\n<<< SYSTEM IS READY >>>\n\n");
      }
    }
}