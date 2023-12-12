#include <Arduino.h>
#include <Melsec.h>
#include <SPI.h>
TaskHandle_t Task1;
TaskHandle_t Task2;

// alo phai dao day lại nha may dai ca (rx-tx va tx-rx)
// hic hic
  
#define led 2
#define TXEN  0
#define RXD2 16
#define TXD2 17
int kt_1=0;
int out=11;
int d0=0;
unsigned long Time=0;

Melsec plc(Serial2,38400);

void Task1code( void * pvParameters ) {
  for (;;) {
    Serial.print("123");
    // code main esp32 
   
  }
}
 void Task2code( void * pvParameters ) {
    Serial.print("Task2 running on core ");
    Serial.println(xPortGetCoreID());

     for (;;) {
      Serial.print("123"); 
     // Serial.print(plc.ReadWord(0));
      d0=plc.ReadWord(0);
    if(d0==1)
    {
      digitalWrite(led,HIGH);
    }else {
      digitalWrite(led,LOW);
    }
       if(((unsigned long)(millis()- Time)>=100))
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
     plc.WriteBit(plc.Output,8,false);
    plc.WriteBit(plc.Output,9,false);
    plc.WriteBit(plc.Output,10,false);
    kt_1=0;
    Time=millis();
  }
}
     }
 }

void setup() {
  plc.init();
  Serial.begin(115200);
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
  Time=millis();
      // code chia 2 coil
    xTaskCreatePinnedToCore(
    Task1code,   /* Task function. */
    "Task1",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &Task1,      /* Task handle to keep track of created task */
    0);          /* pin task to core 0 */
  delay(500);
  //  *************----------------*************
  //  *************----------------*************
  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
    Task2code,   /* Task function. */
    "Task2",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &Task2,      /* Task handle to keep track of created task */
    1);          /* pin task to core 1 */
  delay(500);
}
  //Serial.print(plc.ReadWord(0));


void loop() 
{

}
/*
   if(((unsigned long)(millis()- Time)>=100))
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
     plc.WriteBit(plc.Output,8,false);
    plc.WriteBit(plc.Output,9,false);
    plc.WriteBit(plc.Output,10,false);
    kt_1=0;
    Time=millis();
  }
}
     ///int km=plc.ReadWord(0);
   //Serial.print(plc.ReadWord(0));
    // plc.WriteBit(plc.Output,0,true);
    // plc.WriteBit(plc.Output,1,false);
    // delay(1000);
    // plc.WriteBit(plc.Output,0,false);
    // plc.WriteBit(plc.Output,1,true);
    // delay(1000);
}
*/