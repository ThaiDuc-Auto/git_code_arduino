#include <Arduino.h>

//      -----------------LED MATRIX ------------------------
//----------------CONG TY TNHH KY THUAT TMKEK---------------
//   ----------------- WEBSITE: tmktek.com ----------------
// writen by : TRAN QUANG THAI vs THAI MINH DUC
// date: 21/07/2022
// HIEN THI NHIET AM TU CAM BIEN
// LED MATRIX 1 PANEL (32X128) DEMO

#include <SPI.h>
#include <EEPROM.h>
#include <Wire.h>          
#include "Config.h"        // CAU HÌNH MATRIX
#include "Show_Led.h"
//#include <ModbusRtu.h>
// khoi tao cac bien nha pro
// #define input_2 39
#define reset 39
#define input 18
#define setting 34
#define next 36
#define tang 35
// #define input_2
//#define button_1  34 // nut thu 4
int adress=0;
int muc_tieu=0;   
int muc_tieu_1=0;   
int do_dai=0;int do_dai_1=0;

int thuc_te=0;
int thuc_te_1=0;int couter_Mode;int couter_Mode1=0;
long startTime=0;long startTime1=0;
// cac bien trang thai cua nut nhan cg nhu cong input nha
int state_next=0; 
int state_tang=0;
int state_setting=0;
int state_reset=0;
int state_input=0;
//cac bien phu nha
int k=0;
int next_command=0;
// bien che do hien thi nha
int che_do=0;

char* show[]={"000","00","0",""};
// bien thay doi trang thai 
int don_vi=0;
int chuc=0;
int tram=0;
int nghin=0;
int kt_1;
// cac  bien cho che do nhap nhay nha
unsigned long Time1=0;
unsigned long Time2=0;
unsigned long Time3=0;
unsigned long Time4=0;
void setup()
{
   EEPROM.begin(10);
   // lay du lieu tu epprom
   muc_tieu = int(EEPROM.read(adress))*256;
   muc_tieu|= int(EEPROM.read(adress+1));
   thuc_te = int(EEPROM.read(adress+2))*256;
   thuc_te |= int(EEPROM.read(adress+3));
  
  pinMode(reset, INPUT_PULLUP);
  pinMode(input, INPUT_PULLUP);
  pinMode(tang, INPUT_PULLUP);
  pinMode(setting, INPUT_PULLUP);
  pinMode(next, INPUT_PULLUP);
  configLedmatrix();
}
void loop()
{
   for(int d3=0;d3<=31;d3++)
  {
    for(int d4=0;d4<=63;d4++)             ///xiu co the sua cho nay nha
    {
      matrix.drawPixel(d4,d3,RED);
    }
  }
  delay(400);
   for(int d3=0;d3<=31;d3++)
  {
    for(int d4=0;d4<=63;d4++)             ///xiu co the sua cho nay nha
    {
      matrix.drawPixel(d4,d3,BLUE);
    }
  }
  delay(400);
   for(int d3=0;d3<=31;d3++)
  {
    for(int d4=0;d4<=63;d4++)             ///xiu co the sua cho nay nha
    {
      matrix.drawPixel(d4,d3,YELLOW);
    }
  }
  delay(500);
   for(int d3=0;d3<=31;d3++)
  {
    for(int d4=0;d4<=63;d4++)             ///xiu co the sua cho nay nha
    {
      matrix.drawPixel(d4,d3,WHITE);
    }
  }
  delay(400);
}
  /*
  if(thuc_te>10000){thuc_te=0; EEPROM.write(adress+2,0); EEPROM.write(adress+3,0);EEPROM.commit(); }
  if(muc_tieu>10000){muc_tieu=0;EEPROM.write(adress,0); EEPROM.write(adress+1,0);EEPROM.commit();}
  matrix.setTextSize(1);
  matrix.setFont(&Font_Thai_design_12_LED7_4so);
  if(che_do==0)
  {
     matrix.setTextColor(RED);
     do_dai=String(muc_tieu).length();
     matrix.setCursor(1,29);
     matrix.print(show[do_dai-1]);
     matrix.setCursor(61-(do_dai*15),29);
     matrix.print(muc_tieu);
  
     matrix.setTextColor(RED);
     do_dai_1=String(thuc_te_1).length();
     matrix.setCursor(61-(do_dai_1*15),62);
     matrix.print(thuc_te_1);
  }
   if((che_do==1)&(k!=0))
     {
      matrix.setTextColor(RED);
      do_dai=String(muc_tieu).length();
      matrix.setCursor(1,29);
      if((unsigned long)(millis()-Time1)<400)
              {
                matrix.print(show[do_dai-1]);
                matrix.setCursor(61-(do_dai*15),29);
                matrix.print(muc_tieu);
              }else if((unsigned long)(millis()-Time1)<700)
              {
                if(k==1){clear_vitri(46,29,1);}
                  else if(k==2){clear_vitri(31,29,1);}
                    else if(k==3){clear_vitri(16,29,1);}
                      else if(k==4){clear_vitri(1,29,1);}
              }else if((unsigned long)(millis()-Time1)>=700)
              {
                Time1=millis();
              } 
     }

  int inputStatus = digitalRead(input); 
     if (inputStatus == LOW)
     { 
      if((inputStatus==LOW)&(state_input!=1))
      {
        state_input=1;
        if(che_do==0)
        {
            if(thuc_te<9999)
              {
                thuc_te++;
              }   
        }
       }
     }else if(inputStatus==HIGH){state_input=0;}

    // nut setting nha anh em
     int settingStatus = digitalRead(setting); 
     if (settingStatus == LOW)
     { 
      if((settingStatus==LOW)&(state_setting!=1))
      {
         state_setting=1;
         startTime=millis();
         
         if((che_do==1)&(k!=0))
         {
           che_do=0;
           k=0;
           clear_vitri(1,29,4);
            muc_tieu=(nghin*1000)+(tram*100)+(chuc*10)+don_vi;
            EEPROM.write(adress,muc_tieu/256);
            EEPROM.write(adress+1,muc_tieu%256);
            EEPROM.commit();
           }
         
      }
      if((settingStatus==LOW)&(state_setting==1))
      {
        couter_Mode = (millis() - startTime) / 1000;
              couter_Mode = couter_Mode / 1 % 10;
              if((che_do==0)&(k==0))
              {
                 if (couter_Mode >=1)
                 {
                      che_do=1;
                      k=1;   // bien chuyen cac che do 
                      nghin=muc_tieu/1000;
                      tram=(muc_tieu%1000)/100;
                      chuc=(muc_tieu%100)/10;
                      don_vi=muc_tieu%10;
                      clear_vitri(1,29,4);
                      Time1=millis();
                 }
              }
      }
     }else if(settingStatus==HIGH){state_setting=0;}

     // nut reset gia tri cái này có thể 
      int resetStatus = digitalRead(reset); 
     if (resetStatus == LOW)
     { 
      if((resetStatus==LOW)&(state_reset!=1))
      {
        state_reset=1;
        startTime1=millis();
        //thuc_te=0;
        //clear_vitri(1,62,4);
       }
       if((resetStatus==LOW)&(state_reset==1))
      {
        couter_Mode1 = (millis() - startTime1) / 1000;
        couter_Mode1 = couter_Mode1 / 1 % 10;
        if ((couter_Mode1 >=1)&(thuc_te!=0))
           {
              thuc_te=0;
              clear_vitri(1,62,4);
            }
      }
     }else if(resetStatus==HIGH){state_reset=0;}

     // cac nut khac trong che do cai dat
      int nextStatus = digitalRead(next); 
     if (nextStatus == LOW)
     { 
      if((nextStatus==LOW)&(state_next!=1))
      {
         state_next=1;
         Time2=millis();
      }
      if((nextStatus==LOW)&(state_next==1)&(che_do==1))
      {
         if(((unsigned long)(millis()-Time2)>20)&(next_command!=1))
         {
           next_command=1;
            if(k<4)
            {
              k++;
            }else k=1;
            Time1=millis();
         }
        
       }
     }else if(nextStatus==HIGH){state_next=0;next_command=0;}

     //nut tang nha pro 
     // cac nut khac trong che do cai dat
      int tangStatus = digitalRead(tang); 
     if (tangStatus == LOW)
     { 
      if((tangStatus==LOW)&(state_tang!=1))
      {
        state_tang=1;
        if(che_do==1)
        {
          switch(k)
          {
          case 1:
            if(don_vi<9)
            {
              don_vi ++;
            }else don_vi=0;
            clear_vitri(46,29,1);
            break;
          case 2:
            if(chuc<9)
            {
              chuc ++;
            }else chuc=0;
            clear_vitri(31,29,1);
            break;
          case 3:
            if(tram<9)
            {
              tram ++;
            }else tram=0;
            clear_vitri(16,29,1);
            break;
          case 4:
            if(nghin<9)
            {
              nghin ++;
            }else nghin=0;
            clear_vitri(1,29,1);
            break;
           // default:
           // break;
          }
          muc_tieu=(nghin*1000)+(tram*100)+(chuc*10)+don_vi;
          //muc_tieu=(nghin*1000)+(tram*100)+(chuc*10)+don_vi;
          //EEPROM.write(adress,muc_tieu);
           //EEPROM.commit();
           
        }
       }
     }else if(tangStatus==HIGH){state_tang=0;}
 if(thuc_te_1!=thuc_te)
 {
  kt_1=String(thuc_te_1).length();
  clear_vitri(46,62,1);
    if(kt_1==2)
    {
      if(((thuc_te_1%100)/10)!=((thuc_te%100)/10)){clear_vitri(31,62,1);}
    }else if(kt_1==3)
    {
      if(((thuc_te_1%100)/10)!=((thuc_te%100)/10)){clear_vitri(31,62,1);}
      if(((thuc_te_1%1000)/100)!=((thuc_te%1000)/100)){clear_vitri(16,62,1);}
    }else if(kt_1==4)
    {
      if(((thuc_te_1%100)/10)!=((thuc_te%100)/10)){clear_vitri(31,62,1);}
      if(((thuc_te_1%1000)/100)!=((thuc_te%1000)/100)){clear_vitri(16,62,1);}
      if((thuc_te_1/1000)!=(thuc_te/1000)){clear_vitri(1,62,1);}
    }

    thuc_te_1=thuc_te;
    EEPROM.write(adress+2,thuc_te_1/256);
     EEPROM.write(adress+3,thuc_te_1%256);
     EEPROM.commit();
 }
}
*/