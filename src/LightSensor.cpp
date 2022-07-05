#include "LightSensor.h"
#include <Arduino.h>

double LightSensor::brightness() {
    // This needs to be calibrated
    return read();
    
    // return pow((double)read() / 3600, 10);; //just a quickly calculated polynomial fit to the measured data
}