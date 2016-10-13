

//Notes



//This sketch is to make a glowbs mode that uses tilt to change the color on the sphere
//FASTLED
//ROLL

//Map yaw and pitch from -90 - (90) to 0, 255


//val = map(val, 0, 1023, 0, 255);


//showcolor(roll(imu.ax.), saturation , luminenice)



//getroll  = float pitch = atan2(-ax, sqrt(ay * ay + az * az));

//getroll_fp(imu.ax, imu.ay, imu.az, -imu.my, -imu.mx, imu.mz);

//float printAttitude(
//float ax, float ay, float az, float mx, float my, float mz)
//{



////////////////////// Proto Functions


/*void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
*/


////////////////////////////////////////////////////



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


 int getPitch_int(float ay, float az)
 {
  //get radians to degrees
  
 
  float roll = atan2(ay, az);
  roll *= 180.0 / PI;
    Serial.print("roll: ");
  Serial.print(roll , 2);

  Serial.println();
  return map(roll, -180, 180, 0, 255);

 }

 int getRoll_int(float ax, float ay, float az)
 {
  //get radians to degrees
 
  float pitch = atan2(-ax, sqrt(ay * ay + az * az));
  pitch *= 180.0 / PI;

  Serial.print("Pitch: ");
  Serial.print(pitch, 2);

  Serial.println();
  
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

  Serial.begin(115200);
  
  
  // Before initializing the IMU, there are a few settings
  // we may need to adjust. Use the settings struct to set
  // the device's communication mode and addresses:
  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;
  imu.begin();

  //FastLed Settings

  //delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    //I really dont have to set this pallette - but will for sake of time right now

    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;

}


//currentPalette[i] = CHSV();

//fill_solid( currentPalette, 16, CRGB::Black);
//CRGB purple = CHSV( HUE_PURPLE, 255, 255);



void loop() {

  //Read data off Accel
  imu.readAccel();

  //Debug data coming off 
  Serial.print(imu.ax);
  Serial.print(", ");
  Serial.print(imu.ay); 
  Serial.print(", ");
  Serial.println(imu.az);
  Serial.println();

  //
  
  Serial.print(imu.calcAccel(imu.ax), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.ay), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.az), 2);
  Serial.println();
  
  ///

  
  Serial.print(getRoll_int(imu.ax, imu.ay, imu.az));
  Serial.println();
  
  // put your main code here, to run repeatedly:
  
  fill_solid( currentPalette, 16,CHSV(getRoll_int(imu.ax, imu.ay, imu.az), getPitch_int(-imu.my, imu.mz),255 ));
  //FastLED.setBrightness( getPitch_int(-imu.my, imu.mz) );
  
  FillLEDsFromPaletteColors(0);
  
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}
