#include "controller.h"

void handle_actions(unsigned long now) {
  
  if (mainAction == ACTION_MAIN) {
    digitalWrite(PIN_LED, LOW);

  } else if (mainAction == ACTION_MANUAL) {
    // turn LED on
    digitalWrite(PIN_LED, HIGH);

  } else if (mainAction == ACTION_STATS) {
    // do a slow blinking
    if (now % 1000 < 500) {
      digitalWrite(PIN_LED, LOW);
    } else {
      digitalWrite(PIN_LED, HIGH);
    }  // if

  } else if (mainAction == ACTION_SET) {
    // do a fast blinking
    if (now % 200 < 100) {
      digitalWrite(PIN_LED, LOW);
    } else {
      digitalWrite(PIN_LED, HIGH);
    }  // if

    if (SetAction == SET_SAVING) {
      // doing save
      update_display();
      delay(3000);
      SetAction = SET_SAVED;
    }


  }  // if
}  // loop


// this function will be called when the button was pressed 1 time and them some time has passed.
void myClickFunction() {

  if (mainAction == ACTION_SET) {
    if (SetAction == SET_1) {
      wateringTime += 1000;

      if (wateringTime > 10000) {
        wateringTime = 1000;
      }

    } else if (SetAction == SET_SURE || SetAction == SET_SAVED) {
      mainAction = ACTION_MAIN;
      SetAction = SET_MAIN; 
    }
  }
if (mainAction == ACTION_MANUAL) {
  manualWateringTime += 1000;

  if (manualWateringTime > 10000) {
    manualWateringTime = 1000;
  }

  }
}  // myClickFunction


// this function will be called when the button was pressed 2 times in a short timeframe.
void myDoubleClickFunction() {
  if (mainAction == ACTION_SET) {

    if (SetAction == SET_MAIN) {
      SetAction = SET_1;
    } else if (SetAction == SET_1) {
      SetAction = SET_2;
    } else if (SetAction == SET_2) {
      SetAction = SET_3;
    } else if (SetAction == SET_3) {
      SetAction = SET_SAVE;
    } else if (SetAction == SET_SAVE) {
      SetAction = SET_MAIN;
    }

  } else if (mainAction == ACTION_MAIN) {
    mainAction = ACTION_MANUAL;
  } else if (mainAction == ACTION_MANUAL) {
    mainAction = ACTION_STATS;
  } else if (mainAction == ACTION_STATS) {
    mainAction = ACTION_MAIN;
  }
}  // myDoubleClickFunction

void myLongPressFunction() {

  if (mainAction == ACTION_MAIN) {
    mainAction = ACTION_SET;
    return;    
  } else if (mainAction == ACTION_MANUAL) {
    digitalWrite(PIN_RELAY, LOW);
    // delay(manualWateringTime);
    performDelayedAction(manualWateringTime);
    digitalWrite(PIN_RELAY, HIGH);
    return;
  }

  if (mainAction == ACTION_SET) {
    if (SetAction == SET_SAVE) {
      SetAction = SET_SURE;
    } else if (SetAction == SET_SURE) {
      SetAction = SET_SAVING;
    } else if (SetAction == SET_MAIN) {
      mainAction = ACTION_MAIN;
    }
    return;
  }
}  // myLongPressFunction


void performDelayedAction(int delayTime) {
  unsigned long previousMillis = 0;
  const long interval = 50; // Interval between actions in milliseconds
  int counter = 0; // Counter to keep track of the number of actions performed
  progress = 0;

  while (counter * interval < delayTime) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      progress = map(counter * interval, 0, delayTime, 0, 1000);
      update_display();
      previousMillis = currentMillis;
      counter++;
    }
  }
  update_display();
  progress = 0;
}