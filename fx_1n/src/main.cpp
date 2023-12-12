#include <Arduino.h>
#include <Melsec.h>
#include <Wire.h>  

 #define TXEN  0

 #define RXD2 16
 #define TXD2 17

 bool state=false;

Melsec plc(Serial2,9600);
void setup() {
   Serial2.begin(9600,SERIAL_7E1,RXD2,TXD2);
    Serial.begin(115200);
   plc.init();
}

void loop() {
   if(state)
   {
    state=!state;
    plc.WriteBit(plc.Output,0,state);
    plc.WriteBit(plc.Output,7,state);
   }else{
     state=!state;
    plc.WriteBit(plc.Output,0,state);
    plc.WriteBit(plc.Output,7,state);
   }
   delay(1000);
} 