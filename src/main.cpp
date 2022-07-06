#include "util.h"
#include "globals.h"

#include "LED.h"
#include "LightSensor.h"
#include "Button.h"
#include "CSVHandler.h"
#include "Survey.h"

#include <Adafruit_Sensor.h>
#include <DHT.h>

#include <SD.h>
#include <TimeLib.h>
#include <LiquidCrystal.h>

#include <Bounce2.h>
#include <Arduino.h>

elapsedMillis time_since_measure;
elapsedMillis time_since_button_press;

LED red_led;
LED green_led;
LightSensor light_sensor;
Button big_button;
Button little_button;
CSVHandler nightly_recording;
CSVHandler mood;
Survey survey;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
DHT temp_sensor(DHT11_PIN, DHT_TYPE);

static bool is_sleeping = false;
static bool recording_message_displayed = false;

void setup()
{
  Serial.begin(BAUD_RATE);
  // while (!Serial); // Wait for serial connection before starting

  // Increase the resolution so we can see the small changes in brightness
  analogReadResolution(13);

  // Setup clock
  setSyncProvider(getTeensy3Time);

  // Dynamically control LCD backlight
  pinMode(LCD_BRIGHTNESS_PIN, OUTPUT);
  analogWrite(LCD_BRIGHTNESS_PIN, 255);

  // Setup peripherals
  lcd.begin(16, 2);
  temp_sensor.begin();
  red_led = LED(RED_LED_PIN);
  green_led = LED(GREEN_LED_PIN);
  light_sensor = LightSensor(LIGHTSENSOR_PIN);

  big_button = initButton(BIG_BUTTON_PIN, INPUT_PULLUP, DEBOUNCE_INTERVAL, LOW);
	little_button = initButton(LITTLE_BUTTON_PIN, INPUT_PULLUP, DEBOUNCE_INTERVAL, LOW);

  // Check clock status
  if (timeStatus() != timeSet) {
    error_handler("Unable to sync with the RTC");
  }

  // Check SD card
	if (!SD.begin(BUILTIN_SDCARD)) {
    error_handler("SD card failed");
  } else if (!SD.mediaPresent()) {
    error_handler("SD card not present");
  }

  // Open the mood tracking CSV file
  if (!mood.init(MOOD_FILENAME, SD, mood_csv_columns, MOOD_NUM_COLUMNS)){
    error_handler("Unable to init mood CSV");
  }

  // Check if the power was killed during a recording for some reason and continue from that state
  if (SD.exists(RECORDING_STATE_FILENAME.c_str())) {
    is_sleeping = true;
    nightly_recording.init(getFilename(true), SD, nightly_csv_columns, NIGHTLY_NUM_COLUMNS);
  }

  survey = Survey(
    SURVEY_BUTTON_0_PIN,
    SURVEY_BUTTON_1_PIN,
    SURVEY_BUTTON_2_PIN,
    SURVEY_BUTTON_3_PIN,
    SURVEY_BUTTON_4_PIN,
    INPUT_PULLUP, DEBOUNCE_INTERVAL, LOW
  );
}

void loop()
{
  updateButtons();
  analogWrite(LCD_BRIGHTNESS_PIN,  (light_sensor.read() >> 5)); //Dim the LCD when it's dark, convert from 13 bit to 8 bit integer

  // Interpret serial commands
  if (Serial.available()) { 
    char incomingByte = Serial.read();

    if (incomingByte == TIME_COMMAND) {
      updateRTC();
    } else if (incomingByte == PRINT_COMMAND) {
      outputStoredData();
    } else if (incomingByte == CLEAR_COMMAND) {
      deleteStoredData();
    }
  }

  if (is_sleeping) {
    // Ask for survey after sleep
    if (recording_message_displayed && time_since_button_press > RECORDING_MESSAGE_DELAY) {
      lcd.setCursor(0, 0);
      lcd.print("How did you     ");
      lcd.setCursor(0, 1);
      lcd.print("sleep?          ");

    } else { // Inform the user that a recording has started after pressing a button
      recording_message_displayed = true;
      lcd.setCursor(0, 0);
      lcd.print("Recording       ");
      lcd.setCursor(0, 1);
      lcd.print("Started         ");
    }

    // Make sensor readings every measurement inteval and save it to the current csv
    if (time_since_measure > MEASUREMENT_INTERVAL) {
      time_since_measure -= MEASUREMENT_INTERVAL;

      float humidity = temp_sensor.readHumidity();
      float temp = temp_sensor.readTemperature();
      char brightness[20];
      snprintf(brightness, sizeof(brightness), "%.3f", light_sensor.brightness()); //save 3 decimal places of resolution

      if (isnan(humidity) || isnan(temp)) {
        error_handler("Failed to read from DHT sensor!");
      }

      String columns[NIGHTLY_NUM_COLUMNS] =
        {
          getTeensy3Time(),
          getFriendlyDate(),
          getFriendlyTime(),
          brightness,
          temp,
          humidity
        };

      if (!nightly_recording.write(columns)) {
        error_handler("Unable to write to CSV");
      }
    }
    
  } else if (!big_button.isPressed() && !little_button.isPressed()) {
    // Ask for survey before sleep
    if (recording_message_displayed && time_since_button_press > RECORDING_MESSAGE_DELAY) {
      lcd.setCursor(0, 0);
      lcd.print("How was your    ");
      lcd.setCursor(0, 1);
      lcd.print("day?            ");

    } else {
      // Inform the user that a recording has stopped after pressing a button
      recording_message_displayed = true;
      lcd.setCursor(0, 0);
      lcd.print("Recording       ");
      lcd.setCursor(0, 1);
      lcd.print("Stopped         ");
    }
  }
  
  // Check if the user has ansered the question on the LCD, record their response
  int survey_result = survey.result();
  if (survey_result) {
    String columns[MOOD_NUM_COLUMNS] =
      {
        getTeensy3Time(),
        getFriendlyDate(),
        getFriendlyTime(),
        !is_sleeping,
        survey_result
      };
    mood.write(columns);

    // Start or stop sleeping recording
    is_sleeping = !is_sleeping;
    recording_message_displayed = false;
    time_since_measure = 0;
    time_since_button_press = 0;

    // If we are starting to sleep, create a new recording
    if (is_sleeping) {
      if (!nightly_recording.init(getFilename(), SD, nightly_csv_columns, NIGHTLY_NUM_COLUMNS)){
        error_handler("Unable to start new CSV");
      }
      // Save the fact that we are recording in case of power loss
      File file = SD.open(RECORDING_STATE_FILENAME.c_str(), FILE_WRITE);
      file.close();
    } else {
      SD.remove(RECORDING_STATE_FILENAME.c_str());
    }
  }

  // Print time to LCD on little button press
  if (little_button.isPressed()) {
    lcd.setCursor(0, 0);
    lcd.printf("%u        ", getTeensy3Time());
    lcd.setCursor(0, 1);
    lcd.print(getFriendlyTime());
	}

  // Print Temperature & Brightness to LCD on big button press
  if (big_button.isPressed()) {
      lcd.setCursor(0, 0);
      lcd.printf("Temp: %f        ", temp_sensor.readTemperature());
      lcd.setCursor(0, 1);
      lcd.printf("Light: %f       ", light_sensor.brightness());
  }
}
