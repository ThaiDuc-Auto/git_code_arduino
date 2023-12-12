#include <Arduino.h>

#define led 2
byte ledStatus = LOW;
unsigned long timer;
void setup() {
  pinMode(led,OUTPUT);
  timer=millis();
  digitalWrite(led, HIGH);
}

void loop() {
  // code nhấp nháy led
  // cach code 1
  /*
 if((unsigned long)(millis()-timer)<=5000)
 {
   digitalWrite(led, HIGH);
 }else if((unsigned long)(millis()-timer)<=10000)
 {
    digitalWrite(led,LOW);
 }else if((unsigned long)(millis()-timer)>10000){
    timer=millis();
 }
 */
 // cách 2
 if((unsigned long)(millis()-timer)>=500)
 {
  ledStatus = !ledStatus;
   digitalWrite(led,ledStatus);
   timer=millis();
 }
}