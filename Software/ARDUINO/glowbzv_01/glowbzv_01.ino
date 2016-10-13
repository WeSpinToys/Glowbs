#include <Adafruit_NeoPixel.h>

#define PIN 13



const int buttonPin = 12;     // the number of the pushbutton pin
int dataPin = 13;
int clockPin = 3;

int oldButtonVal = 0;

int nPatterns = 13;
int lightPattern = 1;

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

// Don't forget to connect the ground wire to Arduino ground,
// and the +5V wire to a +5V supply


// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, 2, NEO_GRB + NEO_KHZ800);

// Optional: leave off pin numbers to use hardware SPI
// (pinout is then specific to each board and can't be changed)
//WS2801 strip = WS2801(25);

void setup() {
    
    strip.begin();
    strip.show();                // initialize all pixels to 'off'    
// initialize the BUTTON pin as an input
    pinMode(buttonPin, INPUT);
    digitalWrite(buttonPin, HIGH);  // button pin is HIGH, so it drops to 0 if pressed
}

  
  // initialize the pushbutton pin as an input:

  
 


  // Update LED contents, to start they are all 'off'



void loop() {
  // Some example procedures showing how to display to the pixels
  
   // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
   int buttonVal = digitalRead(buttonPin);

  if (buttonVal == LOW && oldButtonVal == HIGH) {// button has just been pressed
    lightPattern = lightPattern + 1;
  }
  if (lightPattern > nPatterns) lightPattern = 1;
  oldButtonVal = buttonVal;
  
  switch(lightPattern) {
    case 1:
      pattern1();
      break;
    case 2:
      rainbow();
      break;
      case 3:
      Fire();
      break;
    case 4:
      pattern4();
      break;
      case 5:
      pattern5();
      break;
    case 6:
      pattern6();
      break;
      case 7:
      pattern7();
      break;
    case 8:
      pattern8();
      break;
      case 9:
      pattern9();
      break;
    case 10:
      pattern10();
      break;
      case 11:
      pattern11();
      break;
    case 12:
      pattern12();
      break;
    case 13:
      pattern13();
      break;
  }
}void pattern1() {
     strip.setPixelColor(0, LOW);
     strip.setPixelColor(1, LOW);
     strip.show();   // write all the pixels out
  } void pattern2() {
     strip.setPixelColor(0, Color(255,0,255));
     strip.setPixelColor(1, Color(0,0,255));
     strip.setPixelColor(2, Color(255,0,255));
     strip.setPixelColor(3, Color(0,0,255));
     strip.show();   // write all the pixels out
  }  void pattern3() {
       strip.setPixelColor(0, Color(155,255,100));
     strip.setPixelColor(1, Color(0,190,255));
     strip.setPixelColor(2, Color(155,255,100));
     strip.setPixelColor(3, Color(0,190,255));
     strip.show();   // write all the pixels out
  }  void pattern4() {
  strip.setPixelColor(0, Color(255,0,122));
     strip.setPixelColor(1, Color(255,0,255));
     strip.setPixelColor(2, Color(255,0,122));
     strip.setPixelColor(3, Color(255,0,255));
     strip.show();   // write all the pixels out
    } void pattern5() {//circus
       strip.setPixelColor(0, Color(144,144,255));
     strip.setPixelColor(1, Color(144,255,0));
     strip.setPixelColor(2, Color(144,144,255));
     strip.setPixelColor(3, Color(144,255,0));
     strip.show();   // write all the pixels out
  }  void pattern6() {//rain
       strip.setPixelColor(0, Color(104,144,244));
     strip.setPixelColor(1, Color(25,78,255));
     strip.setPixelColor(2, Color(104,144,244));
     strip.setPixelColor(3, Color(25,78,255));
     strip.show();   // write all the pixels out
  }  void pattern7() {
    strip.setPixelColor(0, Color(0,44,244));
     strip.setPixelColor(1, Color(0,78,255));
     strip.setPixelColor(2, Color(0,44,244));
     strip.setPixelColor(3, Color(0,78,255));
     strip.show();   // write all the pixels out
    } void pattern8() {
      strip.setPixelColor(0, Color(255,0,255));
     strip.setPixelColor(1, Color(0,0,255));
     strip.setPixelColor(2, Color(255,0,255));
     strip.setPixelColor(3, Color(0,0,255));
     strip.show();   // write all the pixels out
  }  void pattern9() {
       strip.setPixelColor(0, Color(255,255,155));
     strip.setPixelColor(1, Color(255,255,155));
     strip.setPixelColor(2, Color(255,255,155));
     strip.setPixelColor(3, Color(255,255,155));
     strip.show();   // write all the pixels out
  }  void pattern10() {
       strip.setPixelColor(0, Color(255,45,0));
     strip.setPixelColor(1, Color(255,45,0));
     strip.setPixelColor(2, Color(255,45,0));
     strip.setPixelColor(3, Color(200,45,0));
     strip.show();   // write all the pixels out
    } void pattern11() {
      strip.setPixelColor(0, Color(55,0,255));
     strip.setPixelColor(1, Color(55,0,255));
     strip.setPixelColor(2, Color(55,0,255));
     strip.setPixelColor(3, Color(55,0,235));
     strip.show();   // write all the pixels out
  }  void pattern12() {
      strip.setPixelColor(0, Color(104,144,244));
     strip.setPixelColor(1, Color(25,78,255));
     strip.setPixelColor(2, Color(104,144,244));
     strip.setPixelColor(3, Color(25,78,255));
     strip.show();   // write all the pixels out
     }void pattern13() {
     strip.setPixelColor(0, LOW);
     strip.setPixelColor(1, LOW);
      strip.setPixelColor(2, LOW);
     strip.setPixelColor(3
     , LOW);
     strip.show();   // write all the pixels out
 
  
    
    
  }
  void Fire() {
  int i, j;
    for (j=0; j < 60; j++) {    
      for (i=0; i < strip.numPixels(); i++) {
      
        strip.setPixelColor(i, Wheel( ((i * 255 / strip.numPixels()) + j) % 60) );
        
      }  
      strip.show();   // write all the pixels out
     
    }
    
    for (j=60; j < 0; j--) {    
      for (i=0; i < strip.numPixels(); i++) {
      
        strip.setPixelColor(i, Wheel( ((i * 60/ strip.numPixels()) + j) % 255) );
        
      }  
      strip.show();   // write all the pixels out

    }
}

 
  
  


void rainbow() {
  int i, j;

  for (j=0; j < 255; j++) {     // 3 cycles of all 256 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 255));
    }  
    strip.show();   // write all the pixels out

  }
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  int i, j;

  for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// fill the dots one after the other with said color
// good for testing purposes
void colorWipe(uint32_t c, uint8_t wait) {
  int i;

  for (i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

/* Helper functions */

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
    return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170; 
    return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

