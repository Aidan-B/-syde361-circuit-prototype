#ifndef __SURVEY_H__
#define __SURVEY_H__

#include "Button.h"
#include <Arduino.h>

class Survey {
public:
/*!
    @brief  Creates an instance of the Survey class

    @param  pin_1 
            The pin button 1 is connected to
    @param  pin_2
            The pin button 2 is connected to
    @param  pin_3 
            The pin button 3 is connected to
    @param  pin_4 
            The pin button 4 is connected to
    @param  pin_5 
            The pin button 5 is connected to
    @param  mode
            A valid Arduino pin mode (INPUT, INPUT_PULLUP or OUTPUT).
    @param  interval_millis
            The debounce interval time in milliseconds.
    @param  state
            The electrical state (HIGH/LOW) that corresponds to a physical press. Defaults to HIGH
*/
    Survey(int pin_1, int pin_2, int pin_3, int pin_4, int pin_5, 
        int mode, int debounce_interval, bool state = HIGH) :
        _buttons({ 
            initButton(pin_1, mode, debounce_interval, state),
            initButton(pin_2, mode, debounce_interval, state),
            initButton(pin_3, mode, debounce_interval, state),
            initButton(pin_4, mode, debounce_interval, state),
            initButton(pin_5, mode, debounce_interval, state)
        }) {}
    Survey() {}
/*!
    @brief updates the status of the buttons. This has to be done as often as possible. Only call update() once per loop().
*/
    void update();

/*!
    @brief get the index of the most recent button press.

    @returns The most recent button press (indexed from 1). 0 if no button was pressed since the last check.
*/
    int result();

private:
    static const int NUM_BUTTONS = 5;
    Button _buttons[NUM_BUTTONS];
    int _last_result = 0;
};

#endif //__SURVEY_H__
