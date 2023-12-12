#include <Arduino.h>
#include <Wire.h>  

#include "FX1S.h"

 #define LED 2

  int brightness = 0;    // how bright the LED is
  int fadeAmount = 5;    // how many points to fade the LED by
//by program-plc.blogspot.com
#define FX1Sbaud 19200
#define FX1Sformat SERIAL_8N1
#define FX1Stimeout 1000

#define TXEN  0
#define RXD2 16
#define TXD2 17

  const int freq = 5000;
  const int ledChannel = 0;
  const int resolution = 10; //Resolution 8, 10, 12, 15
enum
{
  FX1SPACKET1,
  FX1SPACKET2,
  FX1STOTAL_NO_OF_PACKETS
};
FX1SPacket FX1Spackets[FX1STOTAL_NO_OF_PACKETS];

FX1SpacketPointer FX1Spacket1 = &FX1Spackets[FX1SPACKET1];
FX1SpacketPointer FX1Spacket2 = &FX1Spackets[FX1SPACKET2];

unsigned int FX1SreadD[1];

unsigned int FX1SwriteD[1];

#define AnalogInputPin 8
#define AnalogOutputPin 9

void setup() {
   //Serial2.begin(19200,SERIAL_8N1,RXD2,TXD2);
   Serial.begin(9600);
   
FX1S_construct(FX1Spacket1, FX1S_READ_D, 0, 1, FX1SreadD);
  
FX1S_construct(FX1Spacket2, FX1S_WRITE_D, 1, 1, FX1SwriteD);

FX1S_configure(&Serial2, FX1Sbaud, FX1Sformat, FX1Stimeout, FX1Spackets, FX1STOTAL_NO_OF_PACKETS);

  // configure LED PWM functionalitites
    ledcSetup(ledChannel, freq, resolution);
    // attach the channel to the GPIO2 to be controlled
    ledcAttachPin(LED, ledChannel);
}

void loop() {
  FX1S_update();
  //Write to D1
  int sensorValue = analogRead(AnalogInputPin);
  int outputValue = map(sensorValue, 0, 1023, 0, 32767);
  FX1SwriteD[0] = outputValue;
  
  //Read from D0
  unsigned int D0 = FX1SreadD[0];
  D0 = map(D0, 0, 32767, 0, 255); 
  ledcWrite (ledChannel,D0);
  //analogWrite(AnalogOutputPin, D0);
  Serial.println(D0);

}