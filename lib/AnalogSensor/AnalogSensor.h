#ifndef __ANALOGSENSOR_H__
#define __ANALOGSENSOR_H__

/*!
  @brief An interface for simple analog input sensors
*/
class AnalogSensor {
public:
/*!
  @brief  creates an instance of the AnalogSensor class.
            
  @param    pin
            The analog input pin that is connected to the sensor.
*/
  AnalogSensor(int pin);
  AnalogSensor(){}

/*!
  @brief  creates an instance of the AnalogSensor class.
            
  @param    pin
            The analog input pin that is connected to the sensor.
*/
  void init(int pin);
  
/*!
  @brief  Reads the analog input from the sensor.
*/
  int read();

private:
  int _pin;
};

#endif //__ANALOGSENSOR_H__
