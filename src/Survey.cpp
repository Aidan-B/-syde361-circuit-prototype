#include "Survey.h"

void Survey::update() {
    for (int i = 0; i < Survey::NUM_BUTTONS; i++) {
        _buttons[i].update();
        if (_buttons[i].pressed()) {
            _last_result = i + 1;
        };
    }
}

int Survey::result() {
    int result = _last_result;
    _last_result = 0;
    return result;
}
