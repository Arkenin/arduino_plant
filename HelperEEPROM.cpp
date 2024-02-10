#include "HelperEEPROM.h"

// Function to save variables to EEPROM
void saveToEEPROM() {
  EEPROM.update(WATERING_TIME_ADDR, wateringTime);
  EEPROM.update(MANUAL_WATERING_TIME_ADDR, manualWateringTime);
  EEPROM.update(COOLDOWN_ADDR, cooldown);
  EEPROM.update(THRESHOLD_ADDR, threshold);
}

// Function to read variables from EEPROM
void readFromEEPROM() {
  EEPROM.get(WATERING_TIME_ADDR, wateringTime);
  EEPROM.get(MANUAL_WATERING_TIME_ADDR, manualWateringTime);
  EEPROM.get(COOLDOWN_ADDR, cooldown);
  EEPROM.get(THRESHOLD_ADDR, threshold);
}

void printEEPROMValues() {
  Serial.print("Watering Time: ");
  Serial.println(wateringTime);
  Serial.print("Manual Watering Time: ");
  Serial.println(manualWateringTime);
  Serial.print("Cooldown: ");
  Serial.println(cooldown);
  Serial.print("Threshold: ");
  Serial.println(threshold);
}