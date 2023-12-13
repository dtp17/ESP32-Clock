////////////////////////////////////////////////////////////////////////////////
void digitWrite(int digit, int val, int col) {
  //use this to light up a digit
  //digit is which digit panel one (right to left, 0 indexed)
  //val is the character value to set on the digit
  //col is the predefined color to use, R,G,B or W
  //example:
  //        digitWrite(0, 4, 2);
  //would set the first digit
  //on the right to a "4" in green.

  /*
    // Letters are the standard segment naming, as seen from the front,
    // numbers are based upon the wiring sequence

            A 2
       ----------
      |          |
      |          |
    F 1 |          | B 3
      |          |
      |     G 7  |
       ----------
      |          |
      |          |
    E 6 |          | C 4
      |          |
      |     D 5  |
       ----------    dp 8

  */
  //these are the digit panel character value definitions,
  //if color argument is a 0, the segment is off
  if (val == 0) {
    //segments F,A,B,C,D,E,G, dp
    segLight(digit, 1, col);
    segLight(digit, 2, col);
    segLight(digit, 3, col);
    segLight(digit, 4, col);
    segLight(digit, 5, col);
    segLight(digit, 6, col);
    segLight(digit, 7, 0);
    //segLight(digit,8,col);
  }
  if (val == 1) {
    segLight(digit, 1, 0);
    segLight(digit, 2, 0);
    segLight(digit, 3, col);
    segLight(digit, 4, col);
    segLight(digit, 5, 0);
    segLight(digit, 6, 0);
    segLight(digit, 7, 0);
    //segLight(digit,8,col);
  }
  if (val == 2) {
    segLight(digit, 1, 0);
    segLight(digit, 2, col);
    segLight(digit, 3, col);
    segLight(digit, 4, 0);
    segLight(digit, 5, col);
    segLight(digit, 6, col);
    segLight(digit, 7, col);
    //segLight(digit,8,col);
  }
  if (val == 3) {
    segLight(digit, 1, 0);
    segLight(digit, 2, col);
    segLight(digit, 3, col);
    segLight(digit, 4, col);
    segLight(digit, 5, col);
    segLight(digit, 6, 0);
    segLight(digit, 7, col);
    //segLight(digit,8,col);
  }
  if (val == 4) {
    segLight(digit, 1, col);
    segLight(digit, 2, 0);
    segLight(digit, 3, col);
    segLight(digit, 4, col);
    segLight(digit, 5, 0);
    segLight(digit, 6, 0);
    segLight(digit, 7, col);
    //segLight(digit,8,col);
  }
  if (val == 5) {
    segLight(digit, 1, col);
    segLight(digit, 2, col);
    segLight(digit, 3, 0);
    segLight(digit, 4, col);
    segLight(digit, 5, col);
    segLight(digit, 6, 0);
    segLight(digit, 7, col);
    //segLight(digit,8,col);
  }
  if (val == 6) {
    segLight(digit, 1, col);
    segLight(digit, 2, col);
    segLight(digit, 3, 0);
    segLight(digit, 4, col);
    segLight(digit, 5, col);
    segLight(digit, 6, col);
    segLight(digit, 7, col);
    //segLight(digit,8,col);
  }
  if (val == 7) {
    segLight(digit, 1, 0);
    segLight(digit, 2, col);
    segLight(digit, 3, col);
    segLight(digit, 4, col);
    segLight(digit, 5, 0);
    segLight(digit, 6, 0);
    segLight(digit, 7, 0);
    //segLight(digit,8,col);
  }
  if (val == 8) {
    segLight(digit, 1, col);
    segLight(digit, 2, col);
    segLight(digit, 3, col);
    segLight(digit, 4, col);
    segLight(digit, 5, col);
    segLight(digit, 6, col);
    segLight(digit, 7, col);
    //segLight(digit,8,col);
  }
  if (val == 9) {
    segLight(digit, 1, col);
    segLight(digit, 2, col);
    segLight(digit, 3, col);
    segLight(digit, 4, col);
    segLight(digit, 5, col);
    segLight(digit, 6, 0);
    segLight(digit, 7, col);
    //segLight(digit,8,col);
  }
  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////

  //these are the numeric character definitions,
  //if last argument is a 0, the segment is off
  if (val == 10) { // "0"
    //segments A,B,C,D,E,F
    segLight(digit, 11, col);
    segLight(digit, 12, col);
    segLight(digit, 13, col);
    segLight(digit, 14, col);
    segLight(digit, 15, col);
    segLight(digit, 16, col);
    segLight(digit, 17, 0);
    //segLight(digit, 8, 0); //dp
  }
  if (val == 11) { // "1"
    //segments A,B,C,D,E,F
    segLight(digit, 11, 0);
    segLight(digit, 12, 0);
    segLight(digit, 13, col);
    segLight(digit, 14, col);
    segLight(digit, 15, 0);
    segLight(digit, 16, 0);
    segLight(digit, 17, 0);
    //segLight(digit, 8, 0); //dp
  }
  if (val == 12) { // "2"
    //segments A,B,C,D,E,F
    segLight(digit, 11, 0);
    segLight(digit, 12, col);
    segLight(digit, 13, col);
    segLight(digit, 14, 0);
    segLight(digit, 15, col);
    segLight(digit, 16, col);
    segLight(digit, 17, col);
    //segLight(digit, 8, 0); //dp
  }
  if (val == 13) { // "3"
    //segments A,B,C,D,E,F
    segLight(digit, 11, 0);
    segLight(digit, 12, col);
    segLight(digit, 13, col);
    segLight(digit, 14, col);
    segLight(digit, 15, col);
    segLight(digit, 16, 0);
    segLight(digit, 17, col);
    //segLight(digit, 8, 0); //dp
  }
  if (val == 14) { // "4"
    //segments A,B,C,D,E,F
    segLight(digit, 11, col);
    segLight(digit, 12, 0);
    segLight(digit, 13, col);
    segLight(digit, 14, col);
    segLight(digit, 15, 0);
    segLight(digit, 16, 0);
    segLight(digit, 17, col);
    //segLight(digit, 8, 0); //dp
  }
  if (val == 15) { // "5"
    //segments A,B,C,D,E,F
    segLight(digit, 11, col);
    segLight(digit, 12, col);
    segLight(digit, 13, 0);
    segLight(digit, 14, col);
    segLight(digit, 15, col);
    segLight(digit, 16, 0);
    segLight(digit, 17, col);
    //segLight(digit, 8, 0); //dp
  }
  if (val == 16) { // "6"
    //segments A,B,C,D,E,F
    segLight(digit, 11, col);
    segLight(digit, 12, col);
    segLight(digit, 13, 0);
    segLight(digit, 14, col);
    segLight(digit, 15, col);
    segLight(digit, 16, col);
    segLight(digit, 17, col);
    //segLight(digit, 8, 0); //dp
  }
  if (val == 17) { // "7"
    //segments A,B,C,D,E,F
    segLight(digit, 11, 0);
    segLight(digit, 12, col);
    segLight(digit, 13, col);
    segLight(digit, 14, col);
    segLight(digit, 15, 0);
    segLight(digit, 16, 0);
    segLight(digit, 17, 0);
    //segLight(digit, 8, 0); //dp
  }
  if (val == 18) { // "8"
    //segments A,B,C,D,E,F
    segLight(digit, 11, col);
    segLight(digit, 12, col);
    segLight(digit, 13, col);
    segLight(digit, 14, col);
    segLight(digit, 15, col);
    segLight(digit, 16, col);
    segLight(digit, 17, col);
    //segLight(digit, 8, 0); //dp
  }
  if (val == 19) { // "9"
    //segments A,B,C,D,E,F
    segLight(digit, 11, col);
    segLight(digit, 12, col);
    segLight(digit, 13, col);
    segLight(digit, 14, col);
    segLight(digit, 15, col);
    segLight(digit, 16, 0);
    segLight(digit, 17, col);
    //segLight(digit, 8, 0); //dp
  }
  if (val == 20) {
    segLight(digit, 1, 0);
    segLight(digit, 2, 0);
    segLight(digit, 3, 0);
    segLight(digit, 4, 0);
    segLight(digit, 5, 0);
    segLight(digit, 6, 0);
    segLight(digit, 7, 0);
    segLight(digit, 8, 0);
    segLight(digit, 9, 0);
    segLight(digit, 10, 0);
    segLight(digit, 11, 0);
    segLight(digit, 12, 0);
    segLight(digit, 13, 0);
    segLight(digit, 14, 0);
    segLight(digit, 15, 0);
    segLight(digit, 16, 0);
    segLight(digit, 17, 0);
    segLight(digit, 18, 0);
    segLight(digit, 19, 0);
    segLight(digit, 20, 0);

  }
  if (val == 21) {// o1
    segLight(digit, 1, col);
    segLight(digit, 2, col);
    segLight(digit, 3, col);
    segLight(digit, 4, col);
    segLight(digit, 5, col);
    segLight(digit, 6, col);
    segLight(digit, 7, 0);
  }
  if (val == 22) {// n2
    segLight(digit, 11, col);
    segLight(digit, 12, col);
    segLight(digit, 13, col);
    segLight(digit, 14, col);
    segLight(digit, 15, 0);
    segLight(digit, 16, col);
    segLight(digit, 17, 0);
  }
  if (val == 23) {// l1
    segLight(digit, 1, col);
    segLight(digit, 2, 0);
    segLight(digit, 3, 0);
    segLight(digit, 4, 0);
    segLight(digit, 5, col);
    segLight(digit, 6, col);
    segLight(digit, 7, 0);
  }
  if (val == 24) {// i2
    segLight(digit, 11, 0);
    segLight(digit, 12, 0);
    segLight(digit, 13, col);
    segLight(digit, 14, col);
    segLight(digit, 15, 0);
    segLight(digit, 16, 0);
    segLight(digit, 17, 0);
  }
  if (val == 25) {// n1
    segLight(digit, 1, col);
    segLight(digit, 2, col);
    segLight(digit, 3, col);
    segLight(digit, 4, col);
    segLight(digit, 5, 0);
    segLight(digit, 6, col);
    segLight(digit, 7, 0);
  }
  if (val == 26) {// e2
    segLight(digit, 11, col);
    segLight(digit, 12, col);
    segLight(digit, 13, 0);
    segLight(digit, 14, 0);
    segLight(digit, 15, col);
    segLight(digit, 16, col);
    segLight(digit, 17, col);
  }
}
//END void digitWrite()
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
void segLight(int digit, int seg, int col) {
  //use this to light up a segment
  //digit picks which neopixel strip
  //seg calls a segment
  //col is color
  int color[3];

  //color sets
  if (col == 0) { //off
    color[0] = {0};
    color[1] = {0};
    color[2] = {0};
  }
  if (col == 1) { //red
    color[0] = {255};
    color[1] = {0};
    color[2] = {0};
  }
  if (col == 2) { //green
    color[0] = {0};
    color[1] = {255};
    color[2] = {0};
  }
  if (col == 3) { //blue
    color[0] = {0};
    color[1] = {0};
    color[2] = {255};
  }
  if (col == 4) { //white -- careful with this one, 3x power consumption
    //if 255 is used
    color[0] = {100};
    color[1] = {100};
    color[2] = {100};
  }

  if (col == 5) { //yellow
    color[0] = {220};
    color[1] = {150};
    color[2] = {0};
  }
  if (col == 6) { //
    color[0] = {0};
    color[1] = {150};
    color[2] = {150};
  }
  if (col == 7) { //
    color[0] = {150};
    color[1] = {0};
    color[2] = {150};
  }
  if (col == 8) { //
    color[0] = {220};
    color[1] = {50};
    color[2] = {50};
  }
  if (col == 9) { //
    color[0] = {200};
    color[1] = {100};
    color[2] = {0};
  }
  if (col == 10) { //
    color[0] = {0};
    color[1] = {50};
    color[2] = {200};
  }

  //upper colon 0
  //segments 1-3, 4-6, 7-9, 10-12, 13-15, 16-18, 19-21
  //dp 22
  //lower colon 23

  //seg F
  if (seg == 1) {
    //light first 8
    for (int i = 1; i < 4; i++) {
      strip[digit].setPixelColor(i, color[0], color[1], color[2]);
    }
    //strip(digit).show();
  }
  //seg A
  if (seg == 2) {
    //light second 8
    for (int i = 4; i < 7; i++) {
      strip[digit].setPixelColor(i, color[0], color[1], color[2]);
    }
    //strip(digit).show();
  }
  //seg B
  if (seg == 3) {
    for (int i = 7; i < 10; i++) {
      strip[digit].setPixelColor(i, color[0], color[1], color[2]);
    }
    //strip(digit).show();
  }
  //seg C
  if (seg == 4) {
    for (int i = 10; i < 13; i++) {
      strip[digit].setPixelColor(i, color[0], color[1], color[2]);
    }
    //strip.show();
  }
  //seg D
  if (seg == 5) {
    for (int i = 13; i < 16; i++) {
      strip[digit].setPixelColor(i, color[0], color[1], color[2]);
    }
    //strip(digit).show();
  }
  //seg E
  if (seg == 6) {
    for (int i = 16; i < 19; i++) {
      strip[digit].setPixelColor(i, color[0], color[1], color[2]);
    }
    //strip(digit).show();
  }
  //seg G
  if (seg == 7) {
    for (int i = 19; i < 22; i++) {
      strip[digit].setPixelColor(i, color[0], color[1], color[2]);
    }
    //strip(digit).show();
  }
  //seg dp
  if (seg == 8) {
    for (int i = 22; i < 23; i++) {
      strip[digit].setPixelColor(i, color[0], color[1], color[2]);
    }
    //strip.show();
  }
  //Upper Colon left
  if (seg == 9) {
    for (int i = 0; i < 1; i++) {
      strip[digit].setPixelColor(i, color[0], color[1], color[2]);
    }
    //strip.show();
  }
  //Lower Colon right
  if (seg == 10) {
    for (int i = 23; i < 24; i++) {
      strip[digit].setPixelColor(i, color[0], color[1], color[2]);
    }
    //strip.show();
  }

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////

  //upper colon 0
  //segments 1-3, 4-6, 7-9, 10-12, 13-15, 16-18, 19-21
  //dp 22
  //lower colon 23

  //seg F
  if (seg == 11) {
    for (int i = 25; i < 28; i++) {
      strip[digit].setPixelColor(i, color[0], color[1], color[2]);
    }
    //strip(digit).show();
  }
  //seg A
  if (seg == 12) {
    //light second 8
    for (int i = 28; i < 31; i++) {
      strip[digit].setPixelColor(i, color[0], color[1], color[2]);
    }
    //strip(digit).show();
  }
  //seg B
  if (seg == 13) {
    for (int i = 31; i < 34; i++) {
      strip[digit].setPixelColor(i, color[0], color[1], color[2]);
    }
    //strip(digit).show();
  }
  //seg C
  if (seg == 14) {
    for (int i = 34; i < 37; i++) {
      strip[digit].setPixelColor(i, color[0], color[1], color[2]);
    }
    //strip.show();
  }
  //seg D
  if (seg == 15) {
    for (int i = 37; i < 40; i++) {
      strip[digit].setPixelColor(i, color[0], color[1], color[2]);
    }
    //strip(digit).show();
  }
  //seg E
  if (seg == 16) {
    for (int i = 40; i < 43; i++) {
      strip[digit].setPixelColor(i, color[0], color[1], color[2]);
    }
    //strip(digit).show();
  }
  //seg G
  if (seg == 17) {
    for (int i = 43; i < 46; i++) {
      strip[digit].setPixelColor(i, color[0], color[1], color[2]);
    }
    //strip(digit).show();
  }
  //seg dp
  if (seg == 18) {
    for (int i = 46; i < 47; i++) {
      strip[digit].setPixelColor(i, color[0], color[1], color[2]);
    }
    //strip.show();
  }
  //Upper Colon left
  if (seg == 19) {
    for (int i = 24; i < 25; i++) {
      strip[digit].setPixelColor(i, color[0], color[1], color[2]);
    }
    //strip.show();
  }
  //Lower Colon right
  if (seg == 20) {
    for (int i = 47; i < 48; i++) {
      strip[digit].setPixelColor(i, color[0], color[1], color[2]);
    }
    //strip.show();
  }

}
//END void segLight()
////////////////////////////////////////////////////////////////////////////////
