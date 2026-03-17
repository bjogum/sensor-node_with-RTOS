#include "sensor_motion.h"
#include <Arduino.h>
#include "alarm.h"



void initPIR(){
    pinMode(pirPin, INPUT);
}

void motionIsDetected(){
    if (node.sysTime > 70000 && node.alarmMode == STATE_ARMED_AWAY){ // warm-up time
        //node.sensors.motionDetect = true;
        // add trigger-time ?
    }
}