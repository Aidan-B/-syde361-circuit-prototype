#ifndef __UTIL_H__
#define __UTIL_H__

#include "CSVHandler.h"
#include <Arduino.h>

/*!
  @brief  Catch in this method if an error occurs and communicate the failure

  @param  message
          The message to print over the Serial connection if it is open.
          This message will also be printed to the LCD
*/
void error_handler(String message);

/*!
  @brief  Call the Button::update() method for all buttons
*/
void updateButtons();

/*!
  @brief  Prints all recording files over serial port if a request is received over the serial port
*/
void outputStoredData();

/*!
  @brief  Deletes all csv recordings from the SD card
*/
void deleteStoredData();


/*!
  @brief  Handles received time sync messages over the serial port
*/
void updateRTC();
/*!
  @brief  Parses serial messages for the timestamp
*/
unsigned long processSyncMessage();

/*!
  @brief  Returns the timestamp from the RTC
*/
time_t getTeensy3Time();

/*!
  @brief  Returns the human readable date.
*/
String getFriendlyDate();

/*!
  @brief  Returns the human readable time.
*/
String getFriendlyTime();


/*!
  @brief  Finds a filename that is not currently in use on the SD card

  @param  get_last_filename
          Specify that the last used filename should be used again
*/
String getFilename(bool get_last_filename = false);
#endif //__UTIL_H__
