#include <WiFi.h>
#include <time.h>
#include <Adafruit_NeoPixel.h>
#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>

const char* host = "ESP32 CLOCK";

WebServer server(80);

//192.168.0.49

#define NUMPIXELS 48  // # of LEDs in a strip (some are actually 56, some 57
// due to dots), each strip is a digit
#define DATAPIN0 13  //digit 0 NeoPixel 60 strip far RIGHT
#define DATAPIN1 12  //digit 1 plus lower colon dot
#define DATAPIN2 11  //digit 2 plus upper colon dot


Adafruit_NeoPixel strip[] = {  //here is the variable for the multiple strips
  Adafruit_NeoPixel(NUMPIXELS, DATAPIN0, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, DATAPIN1, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, DATAPIN2, NEO_GRB + NEO_KHZ800)
};

WiFiManager wm;
int bright = 190;  //brightness for all pixels 0-255 range, 32 being dim
int autoBright;    // auto brightness
bool flash = true;
int GMTOffset = 0;                 //Replace with your GMT Offset in seconds
int daylightOffset = 3600;         // Replace with your daylight savings offset in seconds
unsigned long previousMillis = 0;  // will store last time flash was updated
const long interval = 1000;        // interval at which to flash (milliseconds)

unsigned long startTimex = 0;
const unsigned long twentyFourHours = 10000;


#define DRESETPIN A0  //desk RESET button pin
#define DSTOPPIN A1   //desk STOP button pin
#define DSTARTPIN A2  //desk START button pin
#define DPAUSEPIN A3  //desk PAUSE button pin

int switchPin = A5;


//Button states for reading the pushbuttons, since pullup: off = HIGH, on = LOW

int dStartState = 1;
int dStopState = 1;
int dPauseState = 1;
int dResetState = 1;

//variables for debouncing

int dStartLastState = 1;
int dStopLastState = 1;
int dPauseLastState = 1;
int dResetLastState = 1;


int runningMode = 0;  //counter to tell overall state since reset
//0 means it is a clean start, 1 means it's already running or ran
int pauseMode = 0;  //counter for using pause to stop and start timer
int stoppedMode = 0;
int go = 0;         //start counter once blinking/beeping is done
int dispColor = 3;  //color to call out for display, feeds other voids
int counter = 1;
int timeout = 120;  // seconds to run for
int switchVal;
int Chours = 0;
int Cminutes = 0;
int Cseconds = 0;
long remainingTime = 0;
long elapsedTime = 0;
long startTime = 0;
unsigned long currentMillis;
bool done = false;
int Select = 0;

volatile bool isNinjaCounting = false;  // true when start button pressed
volatile uint32_t ninjaMillisTime = 0;  // the actual counter value
volatile bool isNinjaDowning = false;   // true when start button pressed
volatile uint32_t countdownTime = 0;    // the actual counter value

//bool manual = false;

// how often the inputs are readInputs
const int inputsMillis = 10;
// how often the counter is updated
const int counterMillis = 10;
// how often the display is updated
const int displayMillis = 100;

// task prototypes
void readInputs();
void updateCounter();
void updateDisplay();
void debugDisplay();

bool Mode1 = false;
bool Mode2 = false;
bool Mode3 = false;
bool Mode4 = false;
bool Mode5 = false;
bool Press = true;
bool Setup = false;
bool countdownSet = false;
bool res;
bool StartC = false;
bool StopC = false;
bool Portal = false;
bool Run = true;

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
void setup() {
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  startTimex = millis();
  //NeoPixel array setup
  for (int s = 0; s < 3; s++) {
    strip[s].begin();                // Initialize pins for output
    strip[s].setBrightness(bright);  //full brightness 255
    strip[s].show();                 // Turn all LEDs off
    delay(200);
  }
  //flash dashes
  for (int t = 0; t < 3; t++) {
    digitWrite(t, 20, 0);  //blank
    strip[t].show();
    segLight(t, 7, dispColor);
    segLight(t, 17, dispColor);
    strip[t].show();
  }

  delay(1000);


  pinMode(DSTARTPIN, INPUT_PULLUP);
  pinMode(DSTOPPIN, INPUT_PULLUP);
  pinMode(DPAUSEPIN, INPUT_PULLUP);
  pinMode(DRESETPIN, INPUT_PULLUP);
  pinMode(switchPin, INPUT_PULLUP);
  for (int t = 0; t < 3; t++) {
    digitWrite(t, 20, 0);  //blank
    strip[t].show();
  }
}
//END void setup()
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
void loop() {
  input();

  if (millis() - startTimex >= twentyFourHours) {
    // It has been 24 hours
    Serial.println("24 hours have passed.");
    configTime(GMTOffset, daylightOffset, "pool.ntp.org", "time.nist.gov");
    // Reset the start time
    startTimex = millis();
  }
  if (Mode1 == true) {
    readInputs();
    updateCounter();
    updateDisplay1();
  }
  if (Mode2 == true) {
    readInputs();
    updateCounter();
    updateDisplay2();
  }
  if (Mode3 == true) {
    if (done == false) {
      countdownSetup();
    } else {
      //dispColor = 2;
      readInputs();
      updateCounter();
      updateDisplay3();
    }
  }
  if (Mode4 == true) {
    if (Setup == false) {
      wifiSetup();
    }
    dispColor = 6;
    updateDisplay4();
    automaticTime();
    ninjaMillisTime = 0;
  }
  if (Mode5 == true) {
    dispColor = 2;
    Settings();
    updateDisplay5();
  }
  if (Setup == true) {
    server.handleClient();
  }
}

//END void loop()
////////////////////////////////////////////////////////////////////////////////
// task called periodically by TaskScheduler
void updateCounter() {
  if (isNinjaCounting) {
    // FIXME: this doesn't take into account overhead
    ninjaMillisTime += counterMillis;
  }
  if (isNinjaDowning) {
    // FIXME: this doesn't take into account overhead
    countdownTime -= counterMillis;
  }
}
//END void updateCounter()
////////////////////////////////////////////////////////////////////////////////

// starts the counter running
// via START button
void startCounter() {
  isNinjaCounting = true;
  isNinjaDowning = true;
}
//END void startCounter()
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// stops the counter running
// via STOP button
// does NOT reset display
void stopCounter() {
  isNinjaCounting = false;
}
//END void stopCounter()
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// pauses counter
// via PAUSE button
void pauseCounter() {
  isNinjaCounting = false;
}
//END void pauseCounter()
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// reset counter to zero, stops counter
// via RESET button (or boot)
void resetCounter() {
  ninjaMillisTime = 0;
  //fromReset = true;
  digitWrite(2, 20, 0);
  strip[2].show();
  digitWrite(1, 20, 0);
  strip[1].show();
  digitWrite(0, 20, 0);
  strip[0].show();
  stopCounter();
}
//END void resetCounter()
////////////////////////////////////////////////////////////////////////////////

void wifiSetup() {

  //flash dashes
  for (int t = 0; t < 3; t++) {
    digitWrite(t, 20, 0);  //blank
    strip[t].show();
    segLight(t, 7, 6);
    segLight(t, 17, 6);
    strip[t].show();
  }

  // res = wm.autoConnect(); // auto generated AP name from chipid
  // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
  res = wm.autoConnect("RaceTimer", "neonraptor");  // password protected ap

  if (!res) {
    Serial.println("Failed to connect");
    // ESP.restart();
    for (int t = 0; t < 3; t++) {
      digitWrite(t, 20, 0);  //blank
      strip[t].show();
      segLight(t, 7, 1);
      segLight(t, 17, 1);
      strip[t].show();
    }
  } else {
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");

    OTAsetup();
    configTime(GMTOffset, daylightOffset, "pool.ntp.org", "time.nist.gov");

    Setup = true;

    digitWrite(2, 20, 0);
    strip[2].show();
    digitWrite(1, 20, 0);
    strip[1].show();
    digitWrite(0, 20, 0);
    strip[0].show();

    digitWrite(2, 21, dispColor);
    digitWrite(2, 22, dispColor);
    strip[2].show();
    digitWrite(1, 23, dispColor);
    digitWrite(1, 24, dispColor);
    strip[1].show();
    digitWrite(0, 25, dispColor);
    digitWrite(0, 26, dispColor);
    strip[0].show();
    delay(3000);
    digitWrite(2, 20, 0);
    strip[2].show();
    digitWrite(1, 20, 0);
    strip[1].show();
    digitWrite(0, 20, 0);
    strip[0].show();
  }
}
void countdownSetup() {
  while (done == false) {
    dStartState = digitalRead(DSTARTPIN);
    dStopState = digitalRead(DSTOPPIN);
    dPauseState = digitalRead(DPAUSEPIN);
    dResetState = digitalRead(DRESETPIN);
    switchVal = digitalRead(switchPin);

    if (dPauseState == LOW) {
      delay(200);
      // Increment the value
      if (Select == 0) {
        Cseconds++;
        digitWrite(0, (Cseconds % 10) + 10, dispColor);  //sec ones
        digitWrite(0, (Cseconds / 10), dispColor);       // sec tens
        strip[0].show();

        if (Cseconds >= 60) {
          Cseconds = 0;
          digitWrite(0, (Cseconds % 10) + 10, dispColor);  // 0 sec ones
          digitWrite(0, Cseconds / 10, dispColor);         // 0 sec tens
          strip[0].show();

          Cminutes++;
          digitWrite(1, (Cminutes % 10) + 10, dispColor);  //min ones
          digitWrite(1, (Cminutes / 10), dispColor);       // min tens
          strip[1].show();

          if (Cminutes >= 60) {
            Cminutes = 0;
            digitWrite(1, (Cminutes % 10) + 10, dispColor);  // 0 min ones
            digitWrite(1, Cminutes / 10, dispColor);         // 0 min tens
            strip[1].show();

            Chours++;
            digitWrite(2, (Chours % 10) + 10, dispColor);  // hrs ones
            digitWrite(2, (Chours / 10), dispColor);       // hrs tens
            strip[2].show();
          }
        }
      } else if (Select == 1) {
        Cminutes++;
        digitWrite(1, (Cminutes % 10) + 10, dispColor);  //min ones
        digitWrite(1, (Cminutes / 10), dispColor);       // min tens
        strip[1].show();

        if (Cminutes >= 60) {
          Cminutes = 0;
          digitWrite(1, (Cminutes % 10) + 10, dispColor);  // 0 min ones
          digitWrite(1, Cminutes / 10, dispColor);         // 0 min tens
          strip[1].show();

          Chours++;
          digitWrite(2, (Chours % 10) + 10, dispColor);  // hrs ones
          digitWrite(2, (Chours / 10), dispColor);       // hrs tens
          strip[2].show();
        }
      } else if (Select == 2) {
        Chours++;
        digitWrite(2, (Chours % 10) + 10, dispColor);  // hrs ones
        digitWrite(2, (Chours / 10), dispColor);       // hrs tens
        strip[2].show();
      }
    }
    // Check if the decrement button has been pressed
    if (dResetState == LOW) {
      delay(200);
      // Decrement the value
      if (Select == 0) {
        Cseconds--;
        digitWrite(0, (Cseconds % 10) + 10, dispColor);  //sec ones
        digitWrite(0, (Cseconds / 10), dispColor);       // sec tens
        strip[0].show();

        if (Cseconds < 0) {
          Cseconds = 59;
          digitWrite(0, (Cseconds % 10) + 10, dispColor);  //sec ones
          digitWrite(0, (Cseconds / 10), dispColor);       // sec tens
          strip[0].show();

          Cminutes--;
          digitWrite(1, (Cminutes % 10) + 10, dispColor);  // 0 min ones
          digitWrite(1, Cminutes / 10, dispColor);         // 0 min tens
          strip[1].show();

          if (Cminutes < 0) {
            Cminutes = 59;
            digitWrite(1, (Cminutes % 10) + 10, dispColor);  // 0 min ones
            digitWrite(1, Cminutes / 10, dispColor);         // 0 min tens
            strip[1].show();

            Chours--;
            digitWrite(2, (Chours % 10) + 10, dispColor);  // hrs ones
            digitWrite(2, (Chours / 10), dispColor);       // hrs tens
            strip[2].show();

            if (Chours < 0) {
              Chours = 0;
              digitWrite(2, (Chours % 10) + 10, dispColor);  // hrs ones
              digitWrite(2, (Chours / 10), dispColor);       // hrs tens
              strip[2].show();
            }
          }
        }
      } else if (Select == 1) {
        Cminutes--;
        digitWrite(1, (Cminutes % 10) + 10, dispColor);  // 0 min ones
        digitWrite(1, Cminutes / 10, dispColor);         // 0 min tens
        strip[1].show();

        if (Cminutes < 0) {
          Cminutes = 59;
          digitWrite(1, (Cminutes % 10) + 10, dispColor);  // 0 min ones
          digitWrite(1, Cminutes / 10, dispColor);         // 0 min tens
          strip[1].show();

          Chours--;
          digitWrite(2, (Chours % 10) + 10, dispColor);  // hrs ones
          digitWrite(2, (Chours / 10), dispColor);       // hrs tens
          strip[2].show();

          if (Chours < 0) {
            Chours = 0;
            digitWrite(2, (Chours % 10) + 10, dispColor);  // hrs ones
            digitWrite(2, (Chours / 10), dispColor);       // hrs tens
            strip[2].show();
          }
        }
      } else if (Select == 2) {
        Chours--;
        digitWrite(2, (Chours % 10) + 10, dispColor);  // hrs ones
        digitWrite(2, (Chours / 10), dispColor);       // hrs tens
        strip[2].show();

        if (Chours < 0) {
          Chours = 0;
          digitWrite(2, (Chours % 10) + 10, dispColor);  // hrs ones
          digitWrite(2, (Chours / 10), dispColor);       // hrs tens
          strip[2].show();
        }
      }
    }

    // Check if the change mode button has been pressed
    switchVal = digitalRead(switchPin);
    if (switchVal == LOW) {
      delay(500);
      // Toggle the mode
      Select++;
      if (Select > 2) {
        Select = 0;
      }
    }
    for (int t = 0; t < 3; t++) {
      segLight(t, 8, 0);  //blank
      strip[t].show();
    }
    if (Select == 0) {
      segLight(0, 8, dispColor);
      strip[0].show();
    }
    if (Select == 1) {
      segLight(1, 8, dispColor);
      strip[1].show();
    }
    if (Select == 2) {
      segLight(2, 8, dispColor);
      strip[2].show();
    }


    if (dStopState != dStopLastState) {  //for debouncing
      if (dStopState == LOW) {           //the reset button is pushed
        done = true;
      }
      dStopLastState = dStopState;  //for debouncing
    }
  }
  countdownTime = (Chours * 3600) + (Cminutes * 60) + Cseconds;


  for (int t = 0; t < 3; t++) {
    digitWrite(t, 20, 0);  //blank
    strip[t].show();
  }
  digitWrite(0, (Cseconds % 10) + 10, 5);  //sec ones
  digitWrite(0, (Cseconds / 10), 5);       // sec tens
  strip[0].show();
  digitWrite(1, (Cminutes % 10) + 10, 5);  // 0 min ones
  digitWrite(1, Cminutes / 10, 5);         // 0 min tens
  strip[1].show();
  digitWrite(2, (Chours % 10) + 10, 5);  // hrs ones
  digitWrite(2, (Chours / 10), 5);       // hrs tens
  strip[2].show();
  delay(1000);
  countdownSet = true;
}
