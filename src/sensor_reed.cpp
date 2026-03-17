#include <Arduino.h>
#include "alarm.h"

void initReed(){
    pinMode(reedPin, INPUT_PULLUP);
}

void reedIsTriggerd(){
    if (node.alarmMode != STATE_DISARMED){
        node.sensors.reedSensor1 = true;
        // add trigger-time ?
    }
}