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

// alo phai dao day lại nha may dai ca (rx-tx va tx-r
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
   matrix.setFont(&Font_Thai_2_1panel_LED7_17);
    matrix.setTextColor(RED);
    //
    do_dai_1=String(dem_1).length();
    matrix.setCursor(76,17);
    for(int i=0;i<(5-do_dai_1);i++)
    {
      matrix.print(0);
    }
    matrix.setCursor(126-(do_dai_1*10),17);
    matrix.print(dem_1);
    
    do_dai_2=String(dem_input_1).length();
    matrix.setCursor(126-(do_dai_2*10),38);
    matrix.print(dem_input_1);
     matrix.setCursor(62-(do_dai_2*10),6);
    matrix.print(dem_input_1);
    //
    do_dai_3=String(tong_sp_1).length();
    matrix.setCursor(62-(do_dai_3*10),30);
    matrix.print(tong_sp_1);

    matrix.setTextColor(BLUE);
     if(che_do==1)
     {
         matrix.setCursor(126-(bit_chay*10),18);
         matrix.print(".");
     }else {
         clear_vitri_gach(18);
     }
    // xu li voi cac nut or cac che do nha
    if((dem_input!=int(plc.ReadWord(0)))&(int(plc.ReadWord(0))<100000))
    {
      dem_input=int(plc.ReadWord(0));
    }
    // xuat ra tong sp nha
    if((tong_sp!=(int(plc.ReadWord(25))*65536+int(plc.ReadWord(24))))&((int(plc.ReadWord(25))*65536+int(plc.ReadWord(24)))<1000000))
    {
      tong_sp=(int(plc.ReadWord(25))*65536+int(plc.ReadWord(24)));
    }
      // if(che_do==0)
      // {
       if(dem_set!=int(plc.ReadWord(20)))
        {
          dem_set=int(plc.ReadWord(20));
          dem=dem_set; 
        }
   //}
   // //////////***********************
      // ham cai cho nut de cai dat
     int inputStatus_lai = digitalRead(lai); 
   if (inputStatus_lai==HIGH)
   {
     Serial.println("lai");
      if ((inputStatus_lai==HIGH)&(state_nut_lai!=1))
      {
        if(che_do==0)
           {
             startTime_2=millis();
             set_1=1;
           }
         if(che_do==1)
           {
             if(bit_chay>1)
             {
                bit_chay--;
             }else{bit_chay=5;}
              clear_vitri_gach(18);
             startTime_3=millis();
             set_2=1;
           }
           state_nut_lai=1;
      }
      if ((inputStatus_lai== HIGH)&(state_nut_lai==1)&(state_setting!=1)&(set_1==1))
         {
              if(((unsigned long)(millis()- startTime_2)>=1000))
              {
                 che_do=1;
                 bit_chay=1;
                 state_setting=1;
                 dem_set=dem;
              }
         }
         if ((inputStatus_lai== HIGH)&(state_nut_lai==1)&(state_setting_1!=1)&(set_2==1))
         {
              if(((unsigned long)(millis()- startTime_3)>=1000))
              {
                 che_do=0;
                 state_setting_1=1;
                 clear_vitri_gach(18);
                 dem=dem_set;
                 //plc.WriteWord(8)=dem_set;
                        // luu vao bien eeprom
                   dem_1=dem;
                 clear_vitri(66,38,6);
              }
         }
   }else if (inputStatus_lai==LOW)
   {
       state_nut_lai=0;
       set_1=0;
       set_2=0;
       state_setting_1=0;
       state_setting=0;
   }
            // //////////***********************
              // ham cai cho nut de cai dat
             int inputStatus_qua= digitalRead(qua); 
           if (inputStatus_qua==HIGH)
           {
            Serial.println("qua");
              if ((inputStatus_qua==HIGH)&(state_nut_qua!=1))
              {
                if(che_do==0)
                   {
                     startTime_4=millis();
                     set_3=1;
                   }
                 if(che_do==1)
                   {
                     if(bit_chay<5)
                     {
                        bit_chay++;
                     }else{bit_chay=1;}
                       clear_vitri_gach(18);
                     startTime_5=millis();
                     set_4=1;
                   }
                   state_nut_qua=1;
              }
              if ((inputStatus_qua== HIGH)&(state_nut_qua==1)&(state_exit!=1)&(set_3==1))
                 {
                      if(((unsigned long)(millis()- startTime_4)>=1000))
                      {
                         state_exit=1;
                         matrix.clear();
                      }
                 }
                 if ((inputStatus_qua== HIGH)&(state_nut_qua==1)&(state_exit_1!=1)&(set_4==1))
                 {
                      if(((unsigned long)(millis()- startTime_5)>=1000))
                      {
                         che_do=0;
                         state_exit_1=1;
                         dem_1=dem;
                         bit_chay=0;
                         clear_vitri_gach(18);
                         clear_vitri(66,17,6);
                      }
                 }
           }else if (inputStatus_qua==LOW)
           {
               state_nut_qua=0;
               set_3=0;
               set_4=0;
               state_exit_1=0;
               state_exit=0;
           }


        // nut tang 
       int inputStatus_tang = digitalRead(tang); 
         if (inputStatus_tang== HIGH)
         {
           Serial.println("tang");
            if ((inputStatus_tang == HIGH)&(state_nut_tang!=1))
               { 
                  if(che_do==1)
                  {
                    switch (bit_chay){
                       case 1:
                          if(dem_set%10<9)
                          {
                            dem_set++;
                          }else {dem_set=(dem_set/10)*10;}
                       break;
                       case 2:
                          if(((dem_set%100)/10)<9)
                          {
                             dem_set=dem_set+10;
                          }else {dem_set=((dem_set/100)*100)+(dem_set%10);}
                       break;
                       case 3:
                          if(((dem_set%1000)/100)<9)
                          {
                             dem_set=dem_set+100;
                          }else {dem_set=((dem_set/1000)*1000)+(dem_set%100);}
                       break;
                       case 4:
                          if(((dem_set%10000)/1000)<9)
                          {
                             dem_set=dem_set+1000;
                          }else {dem_set=((dem_set/10000)*10000)+(dem_set%1000);}
                       break;
                       case 5:
                          if((dem_set/10000)<9)
                          {
                             dem_set=dem_set+10000;
                          }else {dem_set=dem_set%10000;}
                       break;
                    }
                      //dem=dem_set;
                  }
                  state_nut_tang=1;
               }
         }else if (inputStatus_tang== LOW)
               {
                   state_nut_tang=0 ;
               }

           // nut giam
       int inputStatus_giam = digitalRead(giam); 
         if (inputStatus_giam== HIGH)
         {
           Serial.println("giam");
            if ((inputStatus_giam == HIGH)&(state_nut_giam!=1))
               { 
                  if(che_do==1)
                  {
                    switch (bit_chay){
                       case 1:
                          if(dem_set%10>1)
                          {
                            dem_set--;
                          }else {dem_set=(dem_set/10)*10+9;}
                       break;
                       case 2:
                          if(((dem_set%100)/10)>1)
                          {
                             dem_set=dem_set-10;
                          }else {dem_set=((dem_set/100)*100)+(dem_set%10)+90;}
                       break;
                       case 3:
                          if(((dem_set%1000)/100)>1)
                          {
                             dem_set=dem_set-100;
                          }else {dem_set=((dem_set/1000)*1000)+(dem_set%100)+900;}
                       break;
                       case 4:
                          if(((dem_set%10000)/1000)>1)
                          {
                             dem_set=dem_set-1000;
                          }else {dem_set=((dem_set/10000)*10000)+(dem_set%1000)+9000;}
                       break;
                       case 5:
                          if((dem_set/10000)>1)
                          {
                             dem_set=dem_set+10000;
                          }else {dem_set=dem_set%10000+90000;}
                       break;
                    }
                    // dem=dem_set;
                  }
                  state_nut_giam=1;
               }
             }else if (inputStatus_giam== LOW)
               {
                   state_nut_giam=0 ;
               }

      if(dem_input_1!=dem_input)
   {
     // ham xu xi hien thi dem input
     kt_1=String(dem_input_1).length();
     //-------------------------------------------------------   
     // xu li hien thi hang don vi
      // code hack xiu nha
     clear_vitri(116,38,1);
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
      if((dem_input_1/10)!=(dem_input/10)){clear_vitri(106,38,1);clear_vitri(42,6,1);}
      if((dem_input_1/100)!=(dem_input/100)){clear_vitri(96,38,1);clear_vitri(32,6,1);}
     }
      else if(kt_1==4)
     {
      if((dem_input_1/10)!=(dem_input/10)){clear_vitri(106,38,1);clear_vitri(42,6,1);}
      if((dem_input_1/100)!=(dem_input/100)){clear_vitri(96,38,1);clear_vitri(32,6,1);}
      if((dem_input_1/1000)!=(dem_input/1000)){clear_vitri(86,38,1);clear_vitri(22,6,1);}
     }else
     {
      if((dem_input_1/10)!=(dem_input/10)){clear_vitri(106,38,1);clear_vitri(42,6,1);}
      if((dem_input_1/100)!=(dem_input/100)){clear_vitri(96,38,1);clear_vitri(32,6,1);}
      if((dem_input_1/1000)!=(dem_input/1000)){clear_vitri(86,38,1);clear_vitri(22,6,1);}
      if((dem_input_1/10000)!=(dem_input/10000)){clear_vitri(76,38,1);clear_vitri(12,6,1);}  
     }
     //if(dem_input-dem_input_1>5){clear_vitri(1,26,65);}
     dem_input_1=dem_input;
     // luu vao bien eeprom
     EEPROM.write(adress+6,dem_input_1/256);
     EEPROM.write(adress+7,dem_input_1%256);
     EEPROM.commit(); 
     //Serial.println(dem_input);
     }

     ///// ****************

       if(tong_sp_1!=tong_sp)
   {
     // ham xu xi hien thi dem input
     kt_2=String().length();
     //-------------------------------------------------------   
     // xu li hien thi hang don vi
      // code hack xiu nha
      //     matrix.setCursor(62-(do_dai_3*10),30);
     clear_vitri(52,30,1);
     if(kt_2==2)
     {
      if((tong_sp_1/10)!=(tong_sp/10))
        { 
             clear_vitri(42,30,1);
        }
     }
     else if(kt_2==3)
     {
      if((tong_sp_1/10)!=(tong_sp/10)){clear_vitri(42,30,1);}
      if((tong_sp_1/100)!=(tong_sp/100)){clear_vitri(32,30,1);}
     }
      else if(kt_2==4)
     {
      if((tong_sp_1/10)!=(tong_sp/10)){clear_vitri(42,30,1);}
      if((tong_sp_1/100)!=(tong_sp/100)){clear_vitri(32,30,1);}
      if((tong_sp_1/1000)!=(tong_sp/1000)){clear_vitri(22,30,1);}
     }else if(kt_2==5)
     {
      if((tong_sp_1/10)!=(tong_sp/10)){clear_vitri(42,30,1);}
      if((tong_sp_1/100)!=(tong_sp/100)){clear_vitri(32,30,1);}
      if((tong_sp_1/1000)!=(tong_sp/1000)){clear_vitri(22,30,1);}
      if((tong_sp_1/10000)!=(tong_sp/10000)){clear_vitri(12,30,1);}  
     }else 
     {
      if((tong_sp_1/10)!=(tong_sp/10)){clear_vitri(42,30,1);}
      if((tong_sp_1/100)!=(tong_sp/100)){clear_vitri(32,30,1);}
      if((tong_sp_1/1000)!=(tong_sp/1000)){clear_vitri(22,30,1);}
      if((tong_sp_1/10000)!=(tong_sp/10000)){clear_vitri(12,30,1);}    
       if((tong_sp_1/100000)!=(tong_sp/100000)){clear_vitri(2,30,1);}
     }
     //if(dem_input-dem_input_1>5){clear_vitri(1,26,65);}
     tong_sp_1=tong_sp;
     // luu vao bien eeprom
     EEPROM.write(adress+2,tong_sp_1/256);
     EEPROM.write(adress+3,tong_sp_1%256);
     EEPROM.commit(); 
     //Serial.println(dem_input);
     }

      if(dem_1!=dem_set)
     {
     // ham xu xi hien thi dem input
     kt_3=String(dem_1).length();
     //------------------------------------------------------- 
     if(kt_3!=String(dem_set).length())
     {
         clear_vitri(66,17,6);
     }
     // xu li hien thi hang don vi
      // code hack xiu nha
     // matrix.setCursor(126-(do_dai_1*10),17);
     if(kt_3==1)
     {
          clear_vitri(116,17,1);
     }
     else if(kt_3==2)
     {
             if((dem_1%10)!=(dem_set%10)){ clear_vitri(116,17,1);}
             if(((dem_1%100)/10)!=((dem_set%100)/10))
              { 
                 //clear_vitri(106,38,1);clear_vitri(42,6,1);
                 clear_vitri(106,17,1);
              }
           }
           else if(kt_3==3)
           {
            if((dem_1%10)!=(dem_set%10)){ clear_vitri(116,17,1);}
            if(((dem_1%100)/10)!=((dem_set%100)/10)){clear_vitri(106,17,1);}
            if(((dem_1%1000)/100)!=((dem_set%1000)/100)){clear_vitri(96,17,1);}
           }
            else if(kt_3==4)
           {
            if((dem_1%10)!=(dem_set%10)){ clear_vitri(116,17,1);}
            if(((dem_1%100)/10)!=((dem_set%100)/10)){clear_vitri(106,17,1);}
            if(((dem_1%1000)/100)!=((dem%1000)/100)){clear_vitri(96,17,1);}
            if(((dem_1%10000)/1000)!=((dem_set%10000)/1000)){clear_vitri(86,17,1);}
           }else
           {
            if((dem_1%10)!=(dem_set%10)){ clear_vitri(116,17,1);}
            if(((dem_1%100)/10)!=((dem_set%100)/10)){clear_vitri(106,17,1);}
            if(((dem_1%1000)/100)!=((dem_set%1000)/100)){clear_vitri(96,17,1);}
            if(((dem_1%10000)/1000)!=((dem_set%10000)/1000)){clear_vitri(86,17,1);}
            if((dem_1/10000)!=(dem_set/10000)){clear_vitri(76,17,1);}  
           }
          //if(dem_input-dem_input_1>5){clear_vitri(1,26,65);}
           dem_1=dem_set;
          }
 
}

/*#include <Arduino.h>
#include <Melsec.h>
#include <Wire.h>  
#include<SPI.h>

int d0=0;

#define led 2

Melsec plc(Serial2,38400);
void setup() {

  Serial.begin(115200);
  plc.init();
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
}
void loop() {
    // d0=plc.ReadWord(0);
    // if(d0==1)
    // {
    //   digitalWrite(led,HIGH);
    // }else {
    //   digitalWrite(led,LOW);
    // }
   
}*/