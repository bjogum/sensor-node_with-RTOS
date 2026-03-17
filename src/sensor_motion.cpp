#include "sensor_motion.h"
#include <Arduino.h>
#include "alarm.h"



void initPIR(){
    pinMode(pirPin, INPUT);
}

void motionIsDetected(){
    if (node.sysTime > 70000){ // warm-up time
        //node.sensors.motionDetect = motionStatusNow;
    }
}