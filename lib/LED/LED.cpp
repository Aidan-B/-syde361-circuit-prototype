//LED output
#include "LED.h"
#include <Arduino.h>

LED::LED(int pin, bool pin_is_sink)
{
    init(pin, pin_is_sink);
}

void LED::init(int pin, bool pin_is_sink)
{
    _pin = pin;
    _pin_is_sink = pin_is_sink;
    _is_on = pin_is_sink;
    
    pinMode(pin, OUTPUT);
    off();
}

void LED::on()
{
    if (!_is_on) {
        if (_pin_is_sink) {
            digitalWrite(_pin, LOW);
        } else {
            digitalWrite(_pin, HIGH);
        }
        _is_on = true;
    }
}

void LED::off()
{
    if (_is_on) {
        if (_pin_is_sink) {
            digitalWrite(_pin, HIGH);
        } else {
            digitalWrite(_pin, LOW);
        }
        _is_on = false;
    }
}

void LED::toggle()
{
    if (_is_on) {
        off();
    } else {
        on();
    }
}
