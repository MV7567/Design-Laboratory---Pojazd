#ifndef SENSOR_CONTROL_H
#define SENSOR_CONTROL_H

#include <Arduino.h>

const int TRIG_PIN = 11;
const int ECHO_PIN = 12;

void setupSensor();
long getDistance(); // Returns distance in cm

#endif