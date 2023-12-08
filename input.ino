void input() {
  int switchVal = digitalRead(switchPin);

  if (switchVal == LOW) {// If the mode button has been pressed
    if (ninjaMillisTime == 0) {// But timer is not currently running
      dispColor = 3;
      Press = true;
      digitWrite(2, 20, 0);
      strip[2].show();
      digitWrite(1, 20, 0);
      strip[1].show();
      digitWrite(0, 20, 0);
      strip[0].show();
      Mode1 =  false;
      Mode2 = false;
      Mode3 = false;
      Mode4 = false;
      Mode5 = false;
      delay(500);
      counter ++;

      if (counter == 6)//Reset count if over max mode number
      {
        counter = 1;
      }
    }
  }

  else

    if (Press == true) {// Can only change mode if mode button was pressed
      switch (counter) {

        case 1:
          Serial.println(counter);
          Serial.println("HH:MM:SS TIMER MODE");
          digitWrite(2, 1, 3);
          strip[2].show();
          dStartState = digitalRead(DSTARTPIN);
          if (dStartState != dStartLastState) {
            if (dStartState == LOW) { //the desk start button is pushed
              Serial.print("mode ");
              Serial.print(counter);
              Serial.println(" selected");
              Mode1 = true;
              Mode2 = false;
              Mode3 = false;
              Mode4 = false;
              Mode5 = false;
              Press = false;
              digitWrite(2, 1, 2);
              strip[2].show();

            }
            dStartLastState = dStartState;
          }
          break;

        case 2:
          Serial.println(counter);
          Serial.println("H:MM:SS.T TIMER MODE");
          digitWrite(2, 2, 3);
          strip[2].show();
          dStartState = digitalRead(DSTARTPIN);
          if (dStartState != dStartLastState) {
            if (dStartState == LOW) { //the desk start button is pushed
              Serial.print("mode ");
              Serial.print(counter);
              Serial.println(" selected");
              Mode2 = true;
              Mode1 = false;
              Mode3 = false;
              Mode4 = false;
              Mode5 = false;
              Press = false;
              digitWrite(2, 2, 2);
              strip[2].show();

            }
            dStartLastState = dStartState;
          }
          break;

        case 3:
          Serial.println(counter);
          Serial.println("HH:MM:SS COUNTDOWN MODE");
          digitWrite(2, 3, 3);
          strip[2].show();
          dStartState = digitalRead(DSTARTPIN);
          if (dStartState != dStartLastState) {
            if (dStartState == LOW) { //the desk start button is pushed
              Serial.print("mode ");
              Serial.print(counter);
              Serial.println(" selected");
              Mode3 = true;
              Mode1 = false;
              Mode2 = false;
              Mode4 = false;
              Mode5 = false;
              Press = false;
              digitWrite(2, 3, 2);
              strip[2].show();

            }
            dStartLastState = dStartState;
          }
          break;

        case 4:
          Serial.println(counter);
          Serial.println("H:MM:SS.T CLOCK MODE");
          digitWrite(2, 4, 3);
          strip[2].show();
          dStartState = digitalRead(DSTARTPIN);
          if (dStartState != dStartLastState) {
            if (dStartState == LOW) { //the desk start button is pushed
              Serial.print("mode ");
              Serial.print(counter);
              Serial.println(" selected");
              Mode4 = true;
              Mode1 = false;
              Mode2 = false;
              Mode3 = false;
              Mode5 = false;
              Press = false;
              digitWrite(2, 4, 2);
              strip[2].show();

            }
            dStartLastState = dStartState;
          }
          break;

        case 5:
          Serial.println(counter);
          Serial.println("SETUP MODE");
          digitWrite(2, 5, 3);
          strip[2].show();
          dStartState = digitalRead(DSTARTPIN);
          if (dStartState != dStartLastState) {
            if (dStartState == LOW) { //the desk start button is pushed
              Serial.print("mode ");
              Serial.print(counter);
              Serial.println(" selected");
              Mode5 = true;
              Mode1 = false;
              Mode2 = false;
              Mode3 = false;
              Mode4 = false;
              Press = false;
              digitWrite(2, 5, 2);
              strip[2].show();

            }
            dStartLastState = dStartState;
          }
          break;
      }
    }
}

void readInputs() {
  Serial.println("reading inputs");
  //check the state of the buttons

  dStartState = digitalRead(DSTARTPIN);
  dStopState =  digitalRead(DSTOPPIN);
  dPauseState = digitalRead(DPAUSEPIN);
  dResetState = digitalRead(DRESETPIN);



  //Start
  //
  if (dStartState != dStartLastState) {
    if (dStartState == LOW) { //the desk start button is pushed
      if (runningMode == 0) { //normal start
        dispColor = 2;  //color is green



        startCounter();
        if (Mode3 == true) {
          StartC = true;
          startTime = millis();
        }

        runningMode = 1;//indicates it is running or has run
      }
      else if (runningMode == 1) {

      }
    }
    dStartLastState = dStartState;
  }

  //Desk Stop
  //
  if (dStopState != dStopLastState) {
    if (runningMode == 1) { //only can stop if started
      if (dStopState == LOW) { //the desk stop button is pushed
        dispColor = 1; //red
        stopCounter();

        stoppedMode = 1;
      }
    }
    dStopLastState = dStopState;
  }

  //Pause
  //
  if (dPauseState != dPauseLastState) { //for debouncing
    if (dPauseState == LOW) {
      if (runningMode == 1 && stoppedMode == 0) { //only makes sense to pause if running
        if (ninjaMillisTime > 0) {
          //the pause button is pushed
          if (pauseMode == 0) { //it was previously running
            dispColor = 5; //yellow
            pauseCounter();
            pauseMode = 1;
          }
          else if (pauseMode == 1) { //it was previously pause, start up again
            dispColor = 2; //green
            startCounter();
            pauseMode = 0;
          }
        }
      }
    }
    dPauseLastState = dPauseState; //for debouncing
  }

  //Reset
  //
  if (dResetState != dResetLastState) { //for debouncing
    if (dResetState == LOW) { //the reset button is pushed
      dispColor = 3; //blue
      //flash dashes
      for (int t = 0; t < 3; t++) {
        digitWrite(t, 20, 0); //blank
        strip[t].show();
        segLight(t, 7, 4);//white dashes
        segLight(t, 17, 4);//white dashes
        strip[t].show();
        delay(170);
      }
      runningMode = 0;
      pauseMode = 0;
      stoppedMode = 0;
      resetCounter();
    }
    dResetLastState = dResetState; //for debouncing
  }

}

//END void readInputs()
////////////////////////////////////////////////////////////////////////////////
