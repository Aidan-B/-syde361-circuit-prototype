#include "CSVHandler.h"
#include <Arduino.h>

CSVHandler::CSVHandler(const String &file_name, SDClass &SD_card, String column_names[], int num_columns)
{
    init(file_name, SD_card, column_names, num_columns);   
}

bool CSVHandler::init(const String &file_name, SDClass &SD_card, String column_names[], const int num_columns)
{
    _file_name = file_name;
    _SD_card = &SD_card;
    _num_columns = num_columns;
    
    if (_SD_card->exists(_file_name.c_str())) {
        return true;
    } else {
        return write(column_names);
    }
}

bool CSVHandler::write(String data[])
{
    File file = _SD_card->open(_file_name.c_str(), FILE_WRITE);
    if (!file) {return false;}
 
    String output = "";
    for (int i = 0; i < _num_columns; i++) {
        output += data[i];
        if (i+1 < _num_columns)
            output += ",";
    }
    file.println(output);
    file.close();
    return true;
}

bool CSVHandler::printToSerial()
{
    File file = SD.open(_file_name.c_str());
	if (!file) { return false; }

    Serial.println(_file_name);      

    while (file.available()) {
        Serial.write(file.read());
    }
    file.close();
    Serial.println("EOF");
    Serial.println("");
    
    return true;
}
