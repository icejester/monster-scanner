#include <Adafruit_NeoPixel.h>

// Pin 13 has an LED connected on most Arduino boards:
// use this pin to give device status
// BEGIN STATUS LIGHT GLOBAL VARS...
int STATUSLIGHT = 13;
int STATBRIGHTNESS = 25;
int MAXBRIGHTNESS = 250;
int MINBRIGHTNESS = 25;
int STATDIRECTION = 1; // 1 is up, 0 is down
// END STATUS LIGHT GLOBAL VARS...

// BEGIN SCANNER ARRAY GLOBAL VARS...
#define SIGNALPIN   7
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, SIGNALPIN, NEO_RGBW + NEO_KHZ800);
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.
// END SCANNER ARRAY GLOBAL VARS...

// BEGIN BUTTON GLOBAL VARS...
#define BUTTONPIN  9
int buttonState = 0;
// END BUTTON GLOBAL VARS...

void setup()
{  // initialize the digital pin as an output.
  pinMode(STATUSLIGHT, OUTPUT);

  strip.begin();
  strip.setBrightness(5);
  strip.show();

  pinMode(BUTTONPIN, INPUT);
  digitalWrite(BUTTONPIN, HIGH);
  
}

void loop()
{
  pulseStatus();

  buttonState = digitalRead(BUTTONPIN);

  if(buttonState == LOW)
  {
    scanning();
    allClear();
  }
  
  delay(20);
}

// ################################################################
// ################################################################
// ###
// ### BEGIN MISC FUNCTION DEFINITIONS...
// ###
// ################################################################
// ################################################################

void pulseStatus()
{
  if (STATBRIGHTNESS < MINBRIGHTNESS)
  {
    STATDIRECTION = 1;
  }
  else if (STATBRIGHTNESS > MAXBRIGHTNESS)
  {
    STATDIRECTION = 0;
  }

  if (STATDIRECTION > 0)
  {
    STATBRIGHTNESS += 5;
  }
  else
  {
    STATBRIGHTNESS -= 5;
  }
  analogWrite(STATUSLIGHT, STATBRIGHTNESS);
}

void scanning()
{
  int i = 0;
  int x = 4;
  int y = 8;
  int z = 12;
  int loops = 0;

  // for a random number of iterations between 7 and 25...
  for(loops = 0; loops < random(17,45); loops++)
  {
    // chase around the ring
    for(i = 0; i < strip.numPixels(); i++)
    {
      strip.setPixelColor(i, strip.Color(0,0,150));
      strip.setPixelColor(x, strip.Color(150,0,0));
      strip.setPixelColor(y, strip.Color(150,0,150));
      strip.setPixelColor(z, strip.Color(0,150,150));
      
      if(x == 15){ x = 0; } else{ x++; }
      if(y == 15){ y = 0; } else{ y++; }
      if(z == 15){ z = 0; } else{ z++; }
      
      strip.show();
      delay(50);
    }
  }
}

void allClear()
{
  int i = 0;
  int y = 0;

  for(y = 0; y <= 6; y++)
  {
    for(i = 0; i < strip.numPixels(); i++)
    {
      strip.setPixelColor(i, strip.Color(150,0,0));
    }
    strip.show();
    delay(250);
    
    for(i = 0; i < strip.numPixels(); i++)
    {
      strip.setPixelColor(i, strip.Color(0,0,0));
    }
    strip.show();
    delay(250); 
  }
}
//// Slightly different, this makes the rainbow equally distributed throughout
//void rainbowCycle(uint8_t wait) {
//  uint16_t i, j;
//
//  // for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
//  for(j=0; j<256; j++) { // 5 cycles of all colors on wheel
//    for(i=0; i< strip.numPixels(); i++) {
//      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
//    }
//    strip.show();
//    delay(wait);
//  }
//}
//
//// Input a value 0 to 255 to get a color value.
//// The colours are a transition r - g - b - back to r.
//uint32_t Wheel(byte WheelPos) {
//  if(WheelPos < 85) {
//   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
//  } else if(WheelPos < 170) {
//   WheelPos -= 85;
//   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//  } else {
//   WheelPos -= 170;
//   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//  }
//}
