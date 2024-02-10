#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "OneButtonTiny.h"

// #include "controller.ino"
#include "HelperEEPROM.h"
#include "controller.h"


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define UPDATE_INTERVAL 200 // Update every 200 milliseconds



#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// // The actions I ca do...
// typedef enum {
//   ACTION_MAIN,
//   ACTION_MANUAL,
//   ACTION_STATS,
//   ACTION_SET,
// } MyActions;

// typedef enum {
//   SET_MAIN,
//   SET_1,
//   SET_2,
//   SET_3,
//   SET_SAVE,
//   SET_SURE,
//   SET_SAVING,
//   SET_SAVED,
// } SetActions;

// 'test', 128x32px
const unsigned char myImage [] PROGMEM = {
  0xef, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x0f, 
  0xff, 0xf8, 0x01, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x1f, 
  0xff, 0xf8, 0x09, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x1f, 
  0xff, 0xf0, 0x39, 0x01, 0xff, 0xc0, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x1f, 
  0x7b, 0xe1, 0xfd, 0x49, 0xff, 0xf8, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x3f, 
  0x77, 0x87, 0xfc, 0x41, 0xff, 0xfc, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x3f, 
  0xc7, 0x0f, 0xfc, 0x4f, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x3f, 
  0x86, 0x1f, 0xfc, 0x0b, 0xff, 0xef, 0x80, 0x00, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x3f, 
  0x80, 0x3f, 0xfc, 0x07, 0xff, 0xef, 0xc0, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x3f, 
  0x00, 0x7f, 0xfe, 0x07, 0xff, 0xef, 0xe0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x7f, 
  0x00, 0x7f, 0xff, 0x9f, 0xff, 0xcf, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x7f, 
  0x00, 0xff, 0xff, 0xff, 0xf9, 0xcd, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x7f, 
  0x79, 0xff, 0xff, 0xff, 0xf9, 0xcd, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x82, 0x08, 0x7f, 
  0xe3, 0xff, 0xff, 0xff, 0xfe, 0xcd, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x88, 0xff, 
  0xfc, 0xff, 0xff, 0xff, 0xfd, 0xcd, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xf8, 0xff, 
  0xfc, 0xff, 0xff, 0xef, 0xf9, 0xcd, 0xf0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xf8, 0x7f, 
  0x40, 0xff, 0xff, 0x0f, 0xf9, 0xcd, 0xf0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xf8, 0x7f, 
  0x40, 0x7f, 0xfe, 0x0f, 0xff, 0xcf, 0xe0, 0x03, 0xff, 0xff, 0xff, 0xfc, 0x0f, 0xff, 0xf8, 0xff, 
  0x40, 0x7f, 0xfc, 0x0f, 0xff, 0xcf, 0xc0, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xf0, 0xff, 
  0x00, 0x7f, 0xfc, 0x0f, 0xff, 0xcf, 0x80, 0x01, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x3f, 0xe8, 0x7f, 
  0x00, 0x3f, 0xfc, 0x07, 0xff, 0xff, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xfc, 0x0f, 0x88, 0x7f, 
  0x00, 0x3f, 0xfc, 0x43, 0xff, 0xf8, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x3f, 
  0x00, 0x1f, 0xfc, 0x09, 0xff, 0xf0, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x3f, 
  0x80, 0x07, 0xfd, 0x03, 0xff, 0x80, 0x00, 0x01, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x3f, 
  0xc0, 0x01, 0xfd, 0x03, 0xfe, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x1f, 
  0xe0, 0x00, 0x3d, 0x87, 0xf8, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x1f, 
  0xf0, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x1f, 
  0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x1f, 
  0xfe, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x1f, 
  0xff, 0xec, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x0f, 
  0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x0f, 
  0xff, 0xff, 0xe1, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x0f
};

MyActions mainAction = ACTION_MAIN;  // no action when starting
SetActions SetAction = SET_MAIN;  // no action when starting

// solid values
uint16_t wateringTime = 3000; // ms
uint16_t manualWateringTime = 1000; // ms
uint16_t cooldown = 5; // min
uint16_t threshold = 550;

unsigned long lastUpdateTime = 0;

int progress = 0;

const int PIN_LED = 13; // Button connected to pin 13
const int PIN_INPUT = 5; // Button connected to pin 5
const int PIN_RELAY = 8; // Button connected to pin 8

OneButtonTiny button(PIN_INPUT, true);  // This example also works with reduced OneButtonTiny class saving.

void setup() {

  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_RELAY, OUTPUT);

  digitalWrite(PIN_RELAY, HIGH);

  button.attachClick(myClickFunction);
  button.attachDoubleClick(myDoubleClickFunction);
  button.attachLongPressStart(myLongPressFunction);

  Serial.begin(9600);
  delay(500);
  Serial.println("Starting Serial");
  // saveToEEPROM();
  readFromEEPROM();
  printEEPROMValues();

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for (;;)
      ; // Don't proceed, loop forever
  }

  // Reset display settings
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {
  unsigned long currentMillis = millis();
  button.tick();

  unsigned long now = millis();
  handle_actions(now);

  // Screen Update HOME
  if (currentMillis - lastUpdateTime >= UPDATE_INTERVAL) {
    update_display();

    lastUpdateTime = currentMillis;
  } // Screen Update END

  // Your additional loop code can go here
  // ...

}

void update_display() {
    display.clearDisplay(); 
    display.setCursor(0, 0);
    display.setTextColor(WHITE);
    
    if (mainAction == ACTION_MAIN) { 
      int analogValue2 = analogRead(A1);
    
      display.print("Set: ");
      display.println(threshold);

      display.setCursor(64, 0);
      display.print("Cur: ");
      display.println(analogValue2);
      display.println("Testing ");
      display.println("Cooldown: True");

      display.setTextColor(BLACK, WHITE); // 'inverted' text
      display.setCursor(0,24);
      display.println("    Arkenin, 2024    ");

    } else if (mainAction == ACTION_SET) {
      if (SetAction == SET_MAIN) {
        
        display.println("Set: Threshold ");
        display.print(threshold);

        int progressBarWidth = map(threshold, 0, 1023, 0, SCREEN_WIDTH - 1);
        display.drawRect(0, 26, SCREEN_WIDTH - 1, 6, WHITE); // Outline
        display.fillRect(0, 26, progressBarWidth, 6, WHITE); // Fill

      } else if (SetAction == SET_1) {
        
        display.println("Set: Watering Time");
        display.print(wateringTime);
        display.print("ms");

        int progressBarWidth = map(wateringTime, 0, 10000, 0, SCREEN_WIDTH - 1);
        display.drawRect(0, 26, SCREEN_WIDTH - 1, 6, WHITE); // Outline
        display.fillRect(0, 26, progressBarWidth, 6, WHITE); // Fill

      } else if (SetAction == SET_2) {
        display.println("Set: Cooldown Time");

        display_time_minutes(cooldown);
    
      } else if (SetAction == SET_3) {
        //display.print("Setings: 3");
        display.drawBitmap(0, 0, myImage, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);

      } else if (SetAction == SET_SAVE) {
        display.println("Long press to save...");
        display.println("");
        display.print("Trsh: ");
        display.print(threshold);
        display.print(" Water: ");
        display.print(wateringTime/1000);
        display.println("s");
        display.print("Cooldown: ");
        display.print(cooldown);
        display.print("min");

      } else if (SetAction == SET_SURE) {
        display.println("Long press to save...");
        display.println("Sure?");
      } else if (SetAction == SET_SAVING) {
        display.println("Saving...");
      } else if (SetAction == SET_SAVED) {
        display.println("Saved.");
      }



    } else if (mainAction == ACTION_MANUAL) {
      display.print("Man Controll: ");
      display.print(manualWateringTime);

      int progressBarWidth = map(progress, 0, 1000, 0, SCREEN_WIDTH - 1);
      display.drawRect(0, 26, SCREEN_WIDTH - 1, 6, WHITE); // Outline
      display.fillRect(0, 26, progressBarWidth, 6, WHITE); // Fill

    } else if (mainAction == ACTION_STATS) {
      display.setTextSize(1);
      display.println("TEMP/HM");
    }

    display.display();
}

void display_time_minutes(uint16_t min){

  uint8_t hours = min / 60;
  uint8_t minutes = min % 60;

  display.print(hours);
  display.print("h");
  display.print(minutes);
  display.print("min");
}

void display_time_seconds(uint16_t sec){

  uint8_t hours = sec / 3600;
  uint8_t minutes = sec / 60;
  uint8_t seconds = sec % 60;

  display.print(hours);
  display.print("h");
  display.print(minutes);
  display.print("min");
  display.print(seconds);
  display.print("s");
}