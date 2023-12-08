void Settings() {
  dPauseState = digitalRead(DPAUSEPIN);
  if (dPauseState != dPauseLastState) {
    if (dPauseState == LOW) { //the desk start button is pushed

      bright += 10;

    }
    dPauseLastState = dPauseState;
  }

  dResetState = digitalRead(DRESETPIN);
  if (dResetState != dResetLastState) {
    if (dResetState == LOW) { //the desk start button is pushed

      bright -= 10;

    }
    dResetLastState = dResetState;
  }
  if (bright > 255) {
    bright = 0;
  }
  if (bright < 0 ) {
    bright = 250;
  }
  for (int s = 0; s < 3; s++) {
    strip[s].setBrightness(bright); //full brightness 255
  }


  dStopState = digitalRead(DSTOPPIN);
  if (dStopState != dStopLastState) {
    if (dStopState == LOW) { //the desk start button is pushed

      wm.resetSettings();
      dispColor = 6;
      wifiSetup();
    }
    dStopLastState = dStopState;
  }

}
