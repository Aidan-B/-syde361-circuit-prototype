#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <DHT.h>
#include <Arduino.h>

static const int BAUD_RATE = 9600;

static const int GREEN_LED_PIN = 34;
static const int RED_LED_PIN = 33;

static const int LIGHTSENSOR_PIN = A16;

static const int BIG_BUTTON_PIN = 20;
static const int SURVEY_BUTTON_0_PIN = 19;
static const int SURVEY_BUTTON_1_PIN = 18;
static const int SURVEY_BUTTON_2_PIN = 17;
static const int SURVEY_BUTTON_3_PIN = 16;
static const int SURVEY_BUTTON_4_PIN = 15;
static const int LITTLE_BUTTON_PIN = 14;
static const int DEBOUNCE_INTERVAL = 50; //ms

static const int NIGHTLY_NUM_COLUMNS = 6;
static String nightly_csv_columns[NIGHTLY_NUM_COLUMNS] = {"timestamp", "date", "time", "brightness (lux)", "temp (C)", "% humidity"};

static const int MOOD_NUM_COLUMNS = 5;
static const String MOOD_FILENAME = "daily_mood_ratings.csv";
static String mood_csv_columns[MOOD_NUM_COLUMNS] = {"timestamp", "date", "time", "starting sleep" ,"rating"};

static const int rs = 1, en = 0, d4 = 2, d5 = 3, d6 = 4, d7 = 5; // LCD pins
static const int LCD_BRIGHTNESS_PIN = A17;

static const int MEASUREMENT_INTERVAL = 60 * 1000; //ms
static const int RECORDING_MESSAGE_DELAY = 5 * 1000; //ms

// Temperature Sensor
static const int DHT11_PIN = 6;
static const int DHT_TYPE = DHT11;

// Serial commands
static const char TIME_COMMAND = 'T';
static const char PRINT_COMMAND = 'P';
static const char CLEAR_COMMAND = 'C';

// Recording state
static const String RECORDING_STATE_FILENAME = ".recording"

#endif //__GLOBALS_H__