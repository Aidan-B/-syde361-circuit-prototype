// LED
#ifndef __LED_H__
#define __LED_H__

/*!
  @brief The LED class creates an interface for LEDs.
*/
class LED {
public:

/*!
  @brief  creates an instance of the LED class. By default a HIGH state on
          the pin is assumed to turn off the LED.
            
  @param    pin
            The pin that is connected to the LED.
  @param    pin_is_sink
            True if a HIGH state on the pin is assumed to turn off the LED.
            Defaults to true.
*/
  LED(int pin, bool pin_is_sink = true);
  LED() {}
/*!
  @brief  creates an instance of the LED class. By default a HIGH state on
          the pin is assumed to turn off the LED.
            
  @param    pin
            The pin that is connected to the LED.
  @param    pin_is_sink
            True if a HIGH state on the pin is assumed to turn off the LED.
            Defaults to true.
*/
  void init(int pin, bool pin_is_sink = true);

/*!
  @brief turns on the LED
*/
  void on();

/*!
  @brief turns off the LED
*/
  void off();

/*!
  @brief toggles the LED state 
*/
  void toggle();

private:
  int _pin;
  bool _pin_is_sink;
  bool _is_on;

};

#endif //__LED_H__
