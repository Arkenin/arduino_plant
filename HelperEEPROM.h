#ifndef HELPER_EEPROM_h
#define HELPER_EEPROM_h
#include <Arduino.h>
#include <EEPROM.h>

// EEPROM addresses for each variable
#define WATERING_TIME_ADDR 100
#define MANUAL_WATERING_TIME_ADDR 104
#define COOLDOWN_ADDR 108
#define THRESHOLD_ADDR 112

// solid values
extern uint16_t wateringTime;
extern uint16_t manualWateringTime;
extern uint32_t cooldown;
extern uint16_t threshold;

void saveToEEPROM();
void readFromEEPROM();
void printEEPROMValues();

#endif