void Settings() {
  dPauseState = digitalRead(DPAUSEPIN);
  if (dPauseState != dPauseLastState) {
    if (dPauseState == LOW) {  //the desk start button is pushed

      bright += 10;
    }
    dPauseLastState = dPauseState;
  }

  dResetState = digitalRead(DRESETPIN);
  if (dResetState != dResetLastState) {
    if (dResetState == LOW) {  //the desk start button is pushed

      bright -= 10;
    }
    dResetLastState = dResetState;
  }
  if (bright > 255) {
    bright = 0;
  }
  if (bright < 0) {
    bright = 250;
  }
  for (int s = 0; s < 3; s++) {
    strip[s].setBrightness(bright);  //full brightness 255
  }


  dStopState = digitalRead(DSTOPPIN);
  if (dStopState != dStopLastState) {
    if (dStopState == LOW) {  //the desk start button is pushed

      wm.resetSettings();
      dispColor = 6;
      wifiSetup();
    }
    dStopLastState = dStopState;
  }
}




void automaticTime() {
  /*
  time_t rawtime = time(nullptr);
  struct tm* timeinfo = localtime(&rawtime);
  int h = timeinfo->tm_hour;
  int m = timeinfo->tm_min;
  int minsTens = m / 10;  //get the tens place of minutes
  int minsOnes = m % 10;  //get the ones place of minutes
  int hrsTens = h / 10;   //get the tens place of hours
  int hrsOnes = h % 10;   //get the ones place of hours
                          
  if (hrsTens >= 0 && hrsOnes == 8 && minsTens == 0 && minsOnes == 0) {  // 08-10 190   2hrs
    autoBright = 100;
  }
  if (hrsTens == 1 && hrsOnes == 0 && minsTens == 0 && minsOnes == 0) {  // 10-14 250   4hrs
    autoBright = 190;
  }
  if (hrsTens == 1 && hrsOnes == 4 && minsTens == 0 && minsOnes == 0) {  // 14-20 190    6hrs
    autoBright = 100;
  }
  if (hrsTens == 2 && hrsOnes == 0 && minsTens == 0 && minsOnes == 0) {  // 20-08 10     12hrs
    autoBright = 50;
  }
  for (int s = 0; s < 3; s++) {
    strip[s].setBrightness(autoBright);
    strip[s].show();
  }
  */
  time_t rawtime = time(nullptr);
  struct tm* timeinfo = localtime(&rawtime);
  int h = timeinfo->tm_hour;
  int m = timeinfo->tm_min;
  int minsTens = m / 10;  //get the tens place of minutes
  int minsOnes = m % 10;  //get the ones place of minutes
  int hrsTens = h / 10;   //get the tens place of hours
  int hrsOnes = h % 10;   //get the ones place of hours

  int autoBright = calculateAutoBrightness(hrsTens, hrsOnes, minsTens, minsOnes);

  for (int s = 0; s < 3; s++) {
    strip[s].setBrightness(autoBright);
    strip[s].show();
  }
}

int calculateAutoBrightness(int hrsTens, int hrsOnes, int minsTens, int minsOnes) {
  int autoBright = 50;  // Default brightness

  // Define hours for each brightness level
  int startHourLow = 20;
  int endHourLow = 8;
  int startHourMedium = 10;
  int endHourMedium = 14;
  int startHourHigh = 14;
  int endHourHigh = 20;

  int brightLow = 10;
  int brightMed = 100;
  int brightHig = 200;

  // Calculate total minutes from midnight
  int totalMinutes = hrsTens * 600 + hrsOnes * 60 + minsTens * 10 + minsOnes;

  // Adjust brightness based on time
  if ((totalMinutes >= (startHourLow * 60) && totalMinutes < (endHourLow * 60)) ||
      (totalMinutes >= (endHourHigh * 60) && totalMinutes < (startHourLow * 60))) {
    // Low brightness for 2hrs or high brightness for 12hrs
    autoBright = (totalMinutes < (endHourLow * 60)) ? brightMed : brightLow;
  } else if (totalMinutes >= (startHourMedium * 60) && totalMinutes < (endHourMedium * 60)) {
    // Medium brightness for 4hrs
    autoBright = brightHig;
  } else if (totalMinutes >= (endHourMedium * 60) && totalMinutes < (startHourHigh * 60)) {
    // Low brightness for 6hrs
    autoBright = brightMed;
  }

  return autoBright;
}
