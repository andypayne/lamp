#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR
#endif

int fadePin  = 5;
int capIntPin = 3;

const int LAMP_OFF            = 0;
const int LAMP_BRIGHT_WHITE   = 1;
const int LAMP_BRIGHT_YELLOW  = 2;
const int LAMP_DIM_BLUE       = 3;
int lampState = LAMP_OFF;
bool oldTouchState = HIGH;

const int NUMPIXELS = 24;
const int BRIGHTNESS = 255;
Adafruit_NeoPixel ring = Adafruit_NeoPixel(NUMPIXELS, fadePin, NEO_RGBW + NEO_KHZ800);


void setup () {
  pinMode(capIntPin, INPUT);
  digitalWrite(capIntPin, HIGH);
  ring.begin();
  ring.setBrightness(BRIGHTNESS);
  setRing(235, 227, 170);
  delay(1000);
}


void loop() {
  bool newTouchState = digitalRead(capIntPin);
  if (newTouchState == LOW && oldTouchState == HIGH) {
    delay(20);
    newTouchState = digitalRead(capIntPin);
    if (newTouchState == LOW) {
      setLampFromState();
      cycleLampState();
    }
  }

  oldTouchState = newTouchState;
  delay(200);
}


void cycleLampState() {
  if (lampState == LAMP_DIM_BLUE) {
    lampState = LAMP_OFF;
  } else {
    lampState += 1;
  }
}


void setLampFromState() {
  switch(lampState) {
    case LAMP_OFF:
      setRing(0, 0, 0);
      break;
    case LAMP_BRIGHT_WHITE:
      ring.setBrightness(255);
      setRing(255, 255, 255);
      break;
    case LAMP_BRIGHT_YELLOW:
      ring.setBrightness(127);
      setRing(249, 212, 35);
      break;
    case LAMP_DIM_BLUE:
      ring.setBrightness(80);
      setRing(0, 127, 255);
      break;
  }
}


void setRing(int r, int g, int b) {     // Set the strip to one color intensity (red)
   for (int x = 0; x < NUMPIXELS; x++) {
      ring.setPixelColor(x, ring.Color(r, g, b));
   }
   ring.show();
}


