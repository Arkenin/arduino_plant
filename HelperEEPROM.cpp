#include "HelperEEPROM.h"

// Function to save variables to EEPROM
void saveToEEPROM() {
  writeIntIntoEEPROM(WATERING_TIME_ADDR, wateringTime);
  writeIntIntoEEPROM(MANUAL_WATERING_TIME_ADDR, manualWateringTime);
  writeIntIntoEEPROM(COOLDOWN_ADDR, cooldown);
  writeIntIntoEEPROM(THRESHOLD_ADDR, threshold);
}

// Function to read variables from EEPROM
void readFromEEPROM() {
  readIntFromEEPROM(WATERING_TIME_ADDR, &wateringTime);
  readIntFromEEPROM(MANUAL_WATERING_TIME_ADDR, &manualWateringTime);
  readIntFromEEPROM(COOLDOWN_ADDR, &cooldown);
  readIntFromEEPROM(THRESHOLD_ADDR, &threshold);
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

void writeIntIntoEEPROM(int address, uint16_t number){ 
    EEPROM.update(address, number >> 8);
    EEPROM.update(address + 1, number & 0xFF);
  }

void readIntFromEEPROM(int address, uint16_t* number){
  *number = (uint16_t(EEPROM.read(address)) << 8) + uint16_t(EEPROM.read(address + 1));
}