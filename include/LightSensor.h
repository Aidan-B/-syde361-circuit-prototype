#ifndef __LIGHTSENSOR_H__
#define __LIGHTSENSOR_H__

#include "AnalogSensor.h"

/*!
  @brief An interface for the photoresistor based LightSensor
*/
class LightSensor : public AnalogSensor {
public:
/*!
  @brief  Creates an instance of the LightSensor class.

  @param  pin
          The analog input pin that is connected to the sensor.
*/
  LightSensor(int pin): AnalogSensor(pin) {}
  LightSensor():AnalogSensor() {}
  
/*!
  @brief  Measure the sensor voltage and convert to Lux. Note that this calculation
          of brightness is flawed, in that it was calulated with a phone's luxmeter
          under non-ideal testing conditions. For future prototype iterations this
          should be done in a more controlled environment with better equipment.

  @return The measured brighness in Lux
*/
  float brightness();
};

#endif //__LIGHTSENSOR_H__
