#include <Arduino.h>
#include "scheduler.h"
#include "sensor_dht11.h"
#include "tasks.h"
#include "alarm.h"
#include "sensor_reed.h"
#include "sensor_motion.h"
#include <ArduinoBLE.h>

extern "C" void SysTick_Handler(){
  node.sysTime++;
}

void setup() {
  Serial.begin(115200);
  while (!Serial); 
  initComponents();

  // prio 1 sensors - HW interrupt 
  attachInterrupt(digitalPinToInterrupt(reedPin), reedIsTriggerd , RISING);
  attachInterrupt(digitalPinToInterrupt(pirPin), motionIsDetected , RISING);

  // sysTick - starta HW klockan (& systick_handler)
  SysTick_Config(SystemCoreClock / 1000);
}

void loop() { 
  startingSystem();
  
  if (node.runStatus == RUNNING){
    taskScheduler(); 
  }
}