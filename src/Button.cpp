#include "Button.h"

Button initButton(int pin, int mode, int interval_millis, bool state)
{
  Button button = Button();
  button.attach(pin, mode);
  button.interval(interval_millis);
  button.setPressedState(state);
  return button;
}