#include "LightSensor.h"
#include <Arduino.h>

double LightSensor::brightness() {
    // Values calculated based on measurements and weighted polynomial fit of the exponential data 
    return 19.715161169948434 * (exp(0.0008625912609350731 * read()) - 1);
}