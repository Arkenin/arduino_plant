#ifndef CONTROLLER_h
#define CONTROLLER_h
#include <Arduino.h>

extern void update_display();


void handle_actions(unsigned long now);
void myClickFunction();
void myDoubleClickFunction();
void myLongPressFunction();
void performDelayedAction(int delayTime);

// The actions I ca do...
typedef enum {
  ACTION_MAIN,
  ACTION_MANUAL,
  ACTION_STATS,
  ACTION_SET,
} MyActions;

typedef enum {
  SET_MAIN,
  SET_1,
  SET_2,
  SET_3,
  SET_SAVE,
  SET_SURE,
  SET_SAVING,
  SET_SAVED,
} SetActions;

extern MyActions mainAction;  // no action when starting
extern SetActions SetAction;  // no action when starting

extern const int PIN_LED; // Button connected to pin 13
extern const int PIN_INPUT; // Button connected to pin 5
extern const int PIN_RELAY; // Button connected to pin 8

extern int progress;
extern uint16_t wateringTime;
extern uint16_t manualWateringTime;
extern uint32_t cooldown;
extern uint16_t threshold;



#endif