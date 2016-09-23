#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 7); // RX, TX

int led = 13;   // the pin that the LED is attached to
char chByte = 0;  // incoming serial byte
String strInput = "";    // buffer for incoming packet
String strCompare = "switch";

// the setup routine runs once when you press reset:
void setup() {
 // declare pin 9 to be an output:
 pinMode(led, OUTPUT);
 // initialize serial:
 mySerial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {

 while (mySerial.available() > 0)
 {
  // get incoming byte:
  chByte = mySerial.read();
  if (chByte == '\r')
  {
   //compare input message
   if(strInput.equals(strCompare))
   {
    //toggle LED
    digitalWrite(led, HIGH);
    mySerial.println("LED is ON");
    delay(1000);
    digitalWrite(led, LOW);
    mySerial.println("LED is OFF");
   }
   //reset strInput
   strInput = "";
  }
  else
  {
  strInput += chByte;
  }
 }
}
