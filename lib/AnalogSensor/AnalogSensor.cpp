#include "AnalogSensor.h"
#include <Arduino.h>

AnalogSensor::AnalogSensor(int pin) : _pin(pin)
{
    init(pin);
}
void AnalogSensor::init(int pin) 
{
    _pin = pin;
    pinMode(pin, INPUT);
}

int AnalogSensor::read()
{
    return analogRead(_pin);
}
