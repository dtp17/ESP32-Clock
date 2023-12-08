void updateDisplay1() {
  int secs = (ninjaMillisTime / 1000) % 60;
  int mins = (ninjaMillisTime / 1000 / 60) % 60 ;
  int hrs = (ninjaMillisTime / 1000 / 60 / 60) % 60 ;

  int secsTens = secs / 10; //get the tens place of seconds
  int secsOnes = secs % 10; //get the ones place of seconds
  int minsTens = mins / 10; //get the tens place of minutes
  int minsOnes = mins % 10; //get the ones place of minutes
  int hrsTens = hrs / 10;
  int hrsOnes = hrs % 10;

  //write to NeoPixel seven segments, colors:
  //0 = off
  //1 = red
  //2 = green
  //3 = blue
  //4 = white
  //5 =  yellow
  //
  if (hrsTens == 0) {
    digitWrite(2, hrsTens, 0);
    strip[2].show();
  } else {
    digitWrite(2, hrsTens, dispColor);
    strip[2].show();
  }

  if (hrsTens == 0 && hrsOnes == 0) {
    digitWrite(2, hrsOnes + 10, 0);
    strip[2].show();
  } else {
    digitWrite(2, hrsOnes + 10, dispColor);
    segLight(2, 20, dispColor);
    strip[2].show();
    segLight(1, 9, dispColor);
    strip[1].show();
  }

  if (minsTens == 0 && hrsTens == 0 && hrsOnes == 0) {
    digitWrite(1, minsTens, 0);
    strip[1].show();
  } else {
    digitWrite(1, minsTens, dispColor);
    strip[1].show();
  }

  if (minsOnes == 0 && minsTens == 0 && hrsTens == 0 && hrsOnes == 0) {
    digitWrite(1, minsOnes + 10, 0);
    strip[1].show();
  } else {
    digitWrite(1, minsOnes + 10, dispColor);
    segLight(1, 20, dispColor);
    strip[1].show();
    segLight(0, 9, dispColor);
    strip[0].show();
  }
  if (secsTens == 0 && minsOnes == 0 && minsTens == 0 && hrsTens == 0 && hrsOnes == 0) {
    digitWrite(0, secsTens, 0);
    strip[0].show();
  } else {
    digitWrite(0, secsTens, dispColor);
    strip[0].show();
  }
  digitWrite(0, secsOnes + 10, dispColor);
  strip[0].show();

}
void updateDisplay2() {
  int tenths = (ninjaMillisTime / 100) % 10;
  int secs = (ninjaMillisTime / 1000) % 60;
  int mins = (ninjaMillisTime / 1000 / 60) % 60 ;
  int hrs = (ninjaMillisTime / 1000 / 60 / 60) % 60 ;
  int secsTens = secs / 10; //get the tens place of seconds
  int secsOnes = secs % 10; //get the ones place of seconds
  int minsTens = mins / 10; //get the tens place of minutes
  int minsOnes = mins % 10; //get the ones place of minutes
  int hrsOnes = hrs % 10;
  //write to NeoPixel seven segments, colors:
  //0 = off
  //1 = red
  //2 = green
  //3 = blue
  //4 = white
  //5 =  yellow
  //
  if (hrsOnes == 0) {
    digitWrite(2, hrsOnes, 0);
    strip[2].show();
  } else {
    digitWrite(2, hrsOnes, dispColor);
    segLight(2, 10, dispColor);
    segLight(2, 19, dispColor);
    strip[2].show();
  }
  if (minsTens == 0 && hrsOnes == 0) {
    digitWrite(2, minsTens + 10, 0);
    strip[2].show();
  } else {
    digitWrite(2, minsTens + 10, dispColor);
    strip[2].show();
  }
  if (minsOnes == 0 && minsTens == 0 && hrsOnes == 0) {
    digitWrite(1, minsOnes, 0);
    strip[1].show();
  } else {
    digitWrite(1, minsOnes, dispColor);
    segLight(1, 10, dispColor);
    segLight(1, 19, dispColor);
    strip[1].show();
  }
  if (secsTens == 0 && minsOnes == 0 && minsTens == 0 && hrsOnes == 0) {
    digitWrite(1, secsTens + 10, 0);
    strip[1].show();
  } else {
    digitWrite(1, secsTens + 10, dispColor);
    strip[1].show();
  }

  digitWrite(0, secsOnes, dispColor);
  segLight(0, 8, dispColor);
  strip[0].show();
  digitWrite(0, tenths + 10, dispColor);
  strip[0].show();

}
void updateDisplay3() {


  int secs = (countdownTime / 1000) % 60;
  int mins = (countdownTime / 1000 / 60) % 60 ;
  int hrs = (countdownTime / 1000 / 60 / 60) % 60 ;

  int secsTens = secs / 10; //get the tens place of seconds
  int secsOnes = secs % 10; //get the ones place of seconds
  int minsTens = mins / 10; //get the tens place of minutes
  int minsOnes = mins % 10; //get the ones place of minutes
  int hrsTens = hrs / 10;
  int hrsOnes = hrs % 10;

  //write to NeoPixel seven segments, colors:
  //0 = off
  //1 = red
  //2 = green
  //3 = blue
  //4 = white
  //5 =  yellow
  //
  if (remainingTime == 0) {
    dispColor = 1;
    StopC = true;
  } else {
    dispColor = 2;
  }
  digitWrite(2, hrsTens, dispColor);
  strip[2].show();
  digitWrite(2, hrsOnes + 10, dispColor);
  segLight(2, 20, dispColor);
  strip[2].show();
  segLight(1, 9, dispColor);
  digitWrite(1, minsTens, dispColor);
  strip[1].show();
  digitWrite(1, minsOnes + 10, dispColor);
  segLight(1, 20, dispColor);
  strip[1].show();
  segLight(0, 9, dispColor);
  digitWrite(0, secsTens, dispColor);
  strip[0].show();
  digitWrite(0, secsOnes + 10, dispColor);
  strip[0].show();

}

void updateDisplay4() {
  unsigned long currentMillis = millis();
  time_t rawtime = time(nullptr);
  struct tm* timeinfo = localtime(&rawtime);
  int h = timeinfo->tm_hour;
  int m = timeinfo->tm_min;
  int s = timeinfo->tm_sec;
  int secsTens = s / 10; //get the tens place of seconds
  int secsOnes = s % 10; //get the ones place of seconds
  int minsTens = m / 10; //get the tens place of minutes
  int minsOnes = m % 10; //get the ones place of minutes
  int hrsTens = h / 10; //get the tens place of hours
  int hrsOnes = h % 10; //get the ones place of hours

  if (hrsTens == 0 && hrsOnes == 8 && minsTens == 0 && minsOnes == 0) {// 08-10 190   2hrs
    brightness = 190;
  }
  if (hrsTens == 1 && hrsOnes == 0 && minsTens == 0 && minsOnes == 0) {// 10-14 250   4hrs
    brightness = 250;
  }
  if (hrsTens == 1 && hrsOnes == 4 && minsTens == 0 && minsOnes == 0) {// 14-20 190    6hrs
    brightness = 190;
  }
  if (hrsTens == 2 && hrsOnes == 0 && minsTens == 0 && minsOnes == 0) {// 20-08 10     12hrs
    brightness = 190;
  }
  for (int s = 0; s < 3; s++) {
    strip[s].setBrightness(brightness); // set strips to new brightness
  }

  digitWrite(2, hrsTens, dispColor);
  Serial.println(hrsTens);
  strip[2].show();
  digitWrite(2, hrsOnes + 10, dispColor);
  Serial.println(hrsOnes);
  if (flash == true) {
    segLight(2, 20, dispColor);
  } else {
    segLight(2, 20, 0);
  }
  strip[2].show();
  if (flash == true) {
    segLight(1, 9, dispColor);
  } else {
    segLight(1, 9, 0);
  }
  digitWrite(1, minsTens, dispColor);
  Serial.println(minsTens);
  strip[1].show();
  digitWrite(1, minsOnes + 10, dispColor);
  Serial.println(minsOnes);
  if (flash == true) {
    segLight(1, 20, dispColor);
  } else {
    segLight(1, 20, 0);
  }
  strip[1].show();
  if (flash == true) {
    segLight(0, 9, dispColor);
  } else {
    segLight(0, 9, 0);
  }
  digitWrite(0, secsTens, dispColor);
  Serial.println(secsTens);
  strip[0].show();
  digitWrite(0, secsOnes + 10, dispColor);
  Serial.println(secsOnes);
  strip[0].show();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    if (flash == true) {
      flash = false;
    } else {
      flash = true;
    }
  }
}
void updateDisplay5() {
  int hundreds = bright / 100; //get the hundreds place of brightness
  int tens = (bright - (100 * hundreds)) / 10; //get the tens place of brightness
  int ones = (bright - (100 * hundreds)) % 10; //get the ones place of brightness




  if (hundreds == 0) {
    digitWrite(1, hundreds + 10, 0);
    strip[1].show();
  } else {
    digitWrite(1, hundreds + 10, dispColor);
    strip[1].show();
  }
  if (tens == 0 && hundreds == 0) {
    digitWrite(0, tens, 0);
    strip[0].show();
  } else {
    digitWrite(0, tens, dispColor);
    strip[0].show();
  }
  digitWrite(0, ones + 10, dispColor);
  strip[0].show();

}
