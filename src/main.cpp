#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "tasks.h"
#include "alarm.h"
#include "sensor_motion.h"
#include "sensor_reed.h"

SemaphoreHandle_t xAlarmSemaphore;
SemaphoreHandle_t xSystemMonitorSemaphore;
SemaphoreHandle_t xNetworkSemaphore;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  initComponents();
  Serial.println("--- STARTING SYSTEM ---");

  xAlarmSemaphore = xSemaphoreCreateBinary();
  xSystemMonitorSemaphore = xSemaphoreCreateBinary();
  xNetworkSemaphore = xSemaphoreCreateBinary();

  //attachInterrupt(digitalPinToInterrupt(mq2Pin), smokeIsDetected, RISING);
  attachInterrupt(digitalPinToInterrupt(reedPin), reedIsTriggerd, RISING);
  attachInterrupt(digitalPinToInterrupt(pirPin), motionIsDetected, RISING);

  xTaskCreate(vAlarmTask, "ALARM", 128, NULL, 3, NULL);
  xTaskCreate(vSystemMonitorTask, "MONITOR", 512, NULL, 2, NULL);
  xTaskCreate(vNetworkTask, "NETWORK", 1024, NULL, 1, NULL);
  
  vTaskStartScheduler();
}

void loop() {
}

extern "C" void vApplicationTickHook(void) {
  node.sysTime++;
}