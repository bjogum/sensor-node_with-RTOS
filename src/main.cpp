#include <Arduino.h>
#include "scheduler.h"
#include "sensor_dht11.h"
#include "wifi_manager.h"
#include "tasks.h"
#include "alarm.h"
#include <ArduinoBLE.h>

void setup() {
  Serial.begin(115200);
  initWiFi();
  initComonents();
  // attachInterrupt --- HW interrupt: bryter pågående (lägre prioriterad) process omedelbart
}

void loop() { 
  node.sysTime = millis();
  startingSystem();

  
  if (node.runStatus == RUNNING){
    taskScheduler(); 
  }
}