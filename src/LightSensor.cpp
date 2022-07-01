#include "LightSensor.h"

float LightSensor::brightness() {
    int reading = read();
    return (reading * reading * 0.000225f); //just a quickly calculated polynomial fit to the measured data
}