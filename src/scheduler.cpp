// --- definierar NÄR resp. funktion ska köras ---
#include <stdio.h>
#include <Arduino.h>
#include "tasks.h"
#include "alarm.h"
#include "wifi_manager.h"
#include "indicateStatus.h"
#include "mqtt_client.h"
#define WAKE_UP_SYSTEM_MS 20000 // maybe 60s ? (MQ2 behöver tid..)

// 'TaskFunction' blir en definition av funktionspekare.
typedef int (*TaskFunction)(void);

// struct för resp. TASK, innehållande: [Funktionspekare] - [intervall (ms)] - [senaste körningen (ms)]
struct Tasks {
    TaskFunction run;               // pekare till funktion
    const unsigned long intervall;  // hur tätt den tillåts köra
    unsigned long lastRun;          // när den senast kördes
};

// Tasks-array: "taskList" -> innehåller samtliga Tasks, med tillhörande parametrar) 
Tasks taskList[] = {
    {readPrio1Sensors, 20},     // Security sensors              -> 20ms?
    {readPrio2Sensors, 500},    // Saftey sensors                -> 300ms
    {readPrio3Sensors, 1500},   // Temp, fukt, lekage            -> 1500ms
    {checkAlarmStatus, 100},    // Kolla om larm är aktivt  -> 1500ms
    //{manageBLE, 100,50},      // håll BLE aktivt & skcka data - lastRun 50ms ("offset"): underviker krock med Wifi-> 100ms
    {manageWiFi, 5000},         // håll WiFi aktivt & skcka data -> 5000ms
    {manageMQTT, 100},          // håll WiFi aktivt & skcka data -> 100ms
    {statusLED, 100},
};

void taskScheduler(){
  const int numOfTasks = sizeof(taskList) / sizeof(taskList[0]);

  // Loopa igenom listan med TASKS (taskList) & checka tiden.
  for (int i = 0; i<numOfTasks; i++){
    if (node.sysTime - taskList[i].lastRun >= taskList[i].intervall){
      taskList[i].run();
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