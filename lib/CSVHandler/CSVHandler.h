// LED
#ifndef __CSVHANDLER_H__
#define __CSVHANDLER_H__

#include <SD.h>
#include <Arduino.h>

/*!
  @brief The CSVHandler class handles formating CSV files to an SD card
*/
class CSVHandler {
public:

/*!
  @brief  Creates a new CSV File
            
  @param    file_name
            The name of the csv file
  @param    SD_card
            The SD card to write to
  @param    column_names[]
            String array of the columns in the CSV
  @param    num_columns
            The number of columns in the csv
*/
  CSVHandler(const String &file_name, SDClass &SD_card, String column_names[], int num_columns);
  CSVHandler(){};

/*!
  @brief  Creates a new CSV File
            
  @param    file_name
            The name of the new csv file
  @param    SD_card
            The SD card to write to
  @param    column_names[]
            String array of the columns in the CSV
  @param    num_columns
            The number of columns in the csv

  @returns  false if the file could not be created
*/
  bool init(const String &file_name, SDClass &SD_card, String column_names[], int num_columns);

/*!
  @brief  Writes a line of data to the CSV
            
  @param    data
            The array of data to write to the csv
  @returns  false if an error occurred writing to the file
*/
  bool write(String data[]);

/*!
  @brief  Print the contents of csv to the serial port

  @returns  false if an error reading the file occurred
*/
  bool printToSerial();

/*!
  @returns  The name of the current csv file
*/
  String getFileName() {return _file_name;}
  
private:
  int _num_columns;
  String _file_name;
  SDClass* _SD_card;

};

#endif //__CSVHANDLER_H__
