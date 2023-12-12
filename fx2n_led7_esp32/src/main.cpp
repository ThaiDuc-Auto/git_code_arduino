
/*
#include <Arduino.h>
#include <Melsec.h>
#include <Wire.h>  
#include<SPI.h>

int d0=0;

#include <Arduino.h>
#include <Melsec.h>

#include <Config.h>       // CAU HÌNH MATRIX
#include <EEPROM.h>
#include <Wire.h>    
#include <SPI.h>

// alo phai dao day lại nha may dai ca (rx-tx va tx-r)
#define tang 35
#define qua 36
#define lai 34
#define giam 17

//#define button_1  34 // nut thu 4

int timer_counter=700;

int error_1=0;
int error_2=0;

int val_speed;
int val_tong;
int state_os_2=0;
int state_os_1=0;
  
 int adress=0;     

int dem=0;
int dem_input=0;    
int tong_sp=0;   
int dem_1=0;
int dem_input_1=0;    
int tong_sp_1=0; 
int state_nut_qua=0;
int state_nut_lai=0;
int state_nut_tang=0;
int state_nut_giam=0;
int dem_set=0;

int kt_1=0;
int kt_2=0;
int kt_3=0;

unsigned long startTime=0;
unsigned long startTime_1=0;
unsigned long startTime_2=0;
unsigned long startTime_3=0;
unsigned long startTime_4=0;
unsigned long startTime_5=0;

int state_input_1=0;
int state_xoa=0;
int state_reset=0;
int state_m=0;
int state_m1=0;
int couter_Mode=0;
int couter_Mode_1=0;
int che_do=0;

int bit_chay=0;
int state_setting=0;
int state_setting_1=0;
int state_exit=0;
int state_exit_1=0;

int set_1=0;
int set_2=0;
int set_3=0;
int set_4=0;

int do_dai_1=0;
int do_dai_2=0;
int do_dai_3=0;
#define led 2
#define TXEN  0
#define RXD2 16
#define TXD2 17
int out=8;

unsigned long Time=0;

Melsec plc(Serial2,9600);

void setup() {
 // Serial.println(plc.ReadMemory(0));
  Serial.begin(115200);
  plc.init();
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);
  Time=millis();
  configLedmatrix();
}

void loop() {

  matrix.setTextSize(1); 
   matrix.setFont(&Font_Thai_design_12_LED7_5_27);
    matrix.setTextColor(RED);
    matrix.setCursor(12,24);
    if((dem_input_1/10)<10)
    {
         matrix.print(0);
    }
    matrix.print(dem_input_1/10);
    matrix.print(".");
    matrix.print(dem_input_1%10);
    // xu li voi cac nut or cac che do nha
    if((dem_input!=int(plc.ReadWord(0)))&(int(plc.ReadWord(0))<1000))
    {
      dem_input=int(plc.ReadWord(0));
    }

      if(dem_input_1!=dem_input)
    {
     // ham xu xi hien thi dem input
     kt_1=String(dem_input_1).length();
     //-------------------------------------------------------   
     // xu li hien thi hang don vi
      // code hack xiu nha
     clear_vitri(52,6,1);
     if(kt_1==2)
     {
      if((dem_input_1/10)!=(dem_input/10))
        { 
           clear_vitri(106,38,1);clear_vitri(42,6,1);
        }
     }
     else if(kt_1==3)
     {
      if((dem_input_1/10)!=(dem_input/10)){clear_vitri(42,6,1);}
      if((dem_input_1/100)!=(dem_input/100)){clear_vitri(32,6,1);}
     }
     //if(dem_input-dem_input_1>5){clear_vitri(1,26,65);}
      dem_input_1=dem_input;
     // luu vao bien eeprom
     }
}
*/
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
  digitalWrite(led,HIGH);
}
void loop() {
    
  //  bool m0=plc.ReadMemory(0);
  //  bool m1=plc.ReadMemory(1);
  //  bool m2=plc.ReadMemory(2);
  //  bool m3=plc.ReadMemory(3);
  //  Serial.print(m0);
  //  Serial.print("|");
  //  Serial.print(m1);
  //  Serial.print("|");
  //  Serial.print(m2);
  //  Serial.print("|");
  //  Serial.print(m3);
  //  Serial.println("");
  //int km=int(plc.ReadWord(0));
  // su dung tc tien la dc word va dword nha
   // Serial.print(plc.ReadDWord(0));
  // viet lai phan read input
  // viet lai phan read memorry
  //Serial.print(int(plc.ReadInput(0)));
  // Serial.print("kh");
   //Serial.print(int(plc.ReadOutput(0)));
    //Serial.println("");

    // su dung duoc lenh Write Word nha
    // plc.WriteWord(0,1);
    // delay(300);
    // plc.WriteWord(0,2);
    // delay(300);
    // plc.WriteWord(0,3);
    // delay(300);
    // plc.WriteWord(0,4);
    // delay(300);
    // plc.WriteWord(0,0);
    // delay(300);

    plc.WriteBit(plc.Output,1,1);
    delay(100);
    plc.WriteBit(plc.Output,1,0);
    delay(100);
}