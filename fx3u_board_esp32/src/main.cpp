#include <Arduino.h>
#include <Melsec.h>
#include <Wire.h>  
#include<SPI.h>

int d0=0;

#define led 2

Melsec plc(Serial2,9600);
void setup() {

  Serial.begin(115200);
  plc.init();
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
}

void loop() {
    d0=plc.ReadWord(0);
    if(d0==1)
    {
      digitalWrite(led,HIGH);
    }else {
      digitalWrite(led,LOW);
    }
   
} 