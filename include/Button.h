// BUTTON
#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <Bounce2.h>
#include <Arduino.h>

/*!
    @brief  initializes and returns a button object
            
    @param    pin
              The pin that is to be debounced.
    @param    mode
              A valid Arduino pin mode (INPUT, INPUT_PULLUP or OUTPUT).
    @param    interval_millis
              The debounce interval time in milliseconds.
    @param    state
              The electrical state (HIGH/LOW) that corresponds to a physical press.
              Defaults to HIGH
*/
Button initButton(int pin, int mode, int interval_millis, bool state = HIGH);

#endif //__BUTTON_H__
