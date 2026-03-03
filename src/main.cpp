#include <Arduino.h>
#include "tasks.h"

bool timeToScanPrio3 = false;


void setup() {


}

void loop() {

  // läs kritiska sensorer (Prio 1) - löpande

  // lös hög-prio sensorer (Prio 2) var 1:e sek?
  
  // om larm triggats - skicka till ESP (via BLE)

  // läs övriga sensorer (Prio 3) var 3:e sek? * 3.
  //if (timeToScanPrio3) ... 

  // skicka till broker - var 10 sek?

  // håll igång wifi

}