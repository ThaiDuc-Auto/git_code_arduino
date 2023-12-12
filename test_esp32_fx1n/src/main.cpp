#include <Arduino.h>
#include <Melsec.h>

// alo phai dao day lại nha may dai ca (rx-tx va tx-rx)
// hic hic
  
#define led 2
#define TXEN  0
#define RXD2 16
#define TXD2 17
int kt_1=0;
int out=8;

unsigned long Time=0;

Melsec plc(Serial2,9600);

void setup() {
  plc.init();
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);
  Time=millis();
}

void loop() 
{

   if(((unsigned long)(millis()- Time)>=1000))
{
  if(kt_1<=out-2)
  {
      plc.WriteBit(plc.Output,kt_1,true);
      kt_1++;
      Time=millis();
  }else {
    plc.WriteBit(plc.Output,0,false);
    plc.WriteBit(plc.Output,1,false);
    plc.WriteBit(plc.Output,2,false);
    plc.WriteBit(plc.Output,3,false);
    plc.WriteBit(plc.Output,4,false);
    plc.WriteBit(plc.Output,5,false);
    plc.WriteBit(plc.Output,6,false);
    plc.WriteBit(plc.Output,7,false);
    kt_1=0;
    Time=millis();
  }
}
   // Serial.println(plc.ReadMemory(0));
    // plc.WriteBit(plc.Output,0,true);
    // plc.WriteBit(plc.Output,1,false);
    // delay(1000);
    // plc.WriteBit(plc.Output,0,false);
    // plc.WriteBit(plc.Output,1,true);
    // delay(1000);
}