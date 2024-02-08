

// main code here, to run repeatedly:
void handle_actions(unsigned long now) {
  
  if (nextAction == ACTION_OFF) {
    digitalWrite(PIN_LED, LOW);

  } else if (nextAction == ACTION_ON) {
    // turn LED on
    digitalWrite(PIN_LED, HIGH);

  } else if (nextAction == ACTION_1) {
    // do a slow blinking
    if (now % 1000 < 500) {
      digitalWrite(PIN_LED, LOW);
    } else {
      digitalWrite(PIN_LED, HIGH);
    }  // if

  } else if (nextAction == ACTION_2) {
    // do a fast blinking
    if (now % 200 < 100) {
      digitalWrite(PIN_LED, LOW);
    } else {
      digitalWrite(PIN_LED, HIGH);
    }  // if
  }    // if
}  // loop


// this function will be called when the button was pressed 1 time and them some time has passed.
void myClickFunction() {
  if (nextAction == ACTION_OFF) {
    nextAction = ACTION_ON;
  } else if (nextAction == ACTION_1) {
    wateringTime += 1000;
    if (wateringTime > 10000){
      wateringTime = 0;
    }

  } else if (nextAction == ACTION_2) {


  } else if (nextAction == ACTION_3) {
 
  }

}  // myClickFunction


// this function will be called when the button was pressed 2 times in a short timeframe.
void myDoubleClickFunction() {
  if (nextAction == ACTION_ON) {
    nextAction = ACTION_1;

  } else if (nextAction == ACTION_1) {
    nextAction = ACTION_2;

  } else if (nextAction == ACTION_2) {
    nextAction = ACTION_3;

 } else if (nextAction == ACTION_3) {
    nextAction = ACTION_ON;
  }  // if
}  // myDoubleClickFunction


// this function will be called when a long press was detected.
void myLongPressFunction() {
  nextAction = ACTION_OFF;
}  // myLongPressFunction





// End
