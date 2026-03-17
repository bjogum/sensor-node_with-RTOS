#include <Arduino.h>
#include "alarm.h"

void initReed(){
    pinMode(reedPin, INPUT_PULLUP);
}

void reedIsTriggerd(){
    node.sensors.reedSensor1 = true;
}