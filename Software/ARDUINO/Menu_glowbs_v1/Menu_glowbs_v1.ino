
/*
 * Notes for success!
 * We want to have the menu system setup such that there is a Mode that display
 *
 *All present color and 
 * 

 * 
 */


#include <Button.h>        //https://github.com/JChristensen/Button

#define BUTTON_PIN 12       //Connect a tactile button switch (or something similar)
                           //from Arduino pin 2 to ground.
#define PULLUP true        //To keep things simple, we use the Arduino's internal pullup resistor.
#define INVERT true        //Since the pullup resistor will keep the pin high unless the
                           //switch is closed, this is negative logic, i.e. a high state
                           //means the button is NOT pressed. (Assuming a normally open switch.)
#define DEBOUNCE_MS 20     //A debounce time of 20 milliseconds usually works well for tactile button switches.

//#define LED_PIN 13         //The standard Arduino "Pin 13" LED.
#define LONG_PRESS 1000    //We define a "long press" to be 1000 milliseconds.
#define BLINK_INTERVAL 100 //In the BLINK state, switch the LED every 100 milliseconds.

Button myBtn(BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);    //Declare the button



//FastLED headers

#include <FastLED.h>

#define LED_PIN     13
#define NUM_LEDS    8
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

//////////////////


// The SFE_LSM9DS1 library requires both Wire and SPI be
// included BEFORE including the 9DS1 library.
#include <Wire.h>
#include <SPI.h>  
#include <SparkFunLSM9DS1.h>

//////////////////////////
// LSM9DS1 Library Init //
//////////////////////////
// Use the LSM9DS1 class to create an object. [imu] can be
// named anything, we'll refer to that throught the sketch.
LSM9DS1 imu;

///////////////////////
// Example I2C Setup //
///////////////////////
// SDO_XM and SDO_G are both pulled high, so our addresses are:
#define LSM9DS1_M  0x1E // Would be 0x1C if   is LOW
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW

#define DECLINATION -8.58 // Declination (degrees) in Boulder, CO.


 int getPitch_int(float ax, float ay, float az)
 {
  
 
  float pitch = atan2(-ax, sqrt(ay * ay + az * az));
  
  //get radians to degrees
  pitch *= 180.0 / PI;

  return map(pitch, -90, 90, 0, 255);

 }


void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

void setup() {


  //Debug information coming off of mapping

 // Serial.begin(115200);
  
  
  // Before initializing the IMU, there are a few settings
  // we may need to adjust. Use the settings struct to set
  // the device's communication mode and addresses:
  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;
  imu.begin();

  //FastLed Settings

    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    //I really dont have to set this pallette - but will for sake of time right now

    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;

}



void loop() {

  //Read data off Accel
  imu.readAccel();

  

  
  Serial.print(getPitch_int(imu.ax, imu.ay, imu.az));
  Serial.println();
  
  // put your main code here, to run repeatedly:
  
  fill_solid( currentPalette, 16,CHSV(getPitch_int(imu.ax, imu.ay, imu.az), 255, 255));

  
  FillLEDsFromPaletteColors(0);
  
  FastLED.show();
//  FastLED.delay(1000 / UPDATES_PER_SECOND);
}
