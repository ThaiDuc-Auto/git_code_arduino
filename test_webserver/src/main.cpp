//#include <WiFi.h>
//#include <WebServer.h>
#include <Arduino.h>
//      -----------------LED MATRIX ------------------------
//----------------CONG TY TNHH KY THUAT TMKEK---------------
//   ----------------- WEBSITE: tmktek.com ----------------
// writen by : TRAN QUANG THAI vs THAI MINH DUC
// date: 21/07/2022

#include <EEPROM.h>
//#include "FreqCountESP.h"
#include <Wire.h>          
#include "Config.h"        // CAU HÌNH MATRIX
#include "Show_Led.h"      // HIEN THI NOI DUNG MATRIX
//#define RXD2 16
//#define TXD2 17

//#define tang 35
//#define qua 36
#define thoat 22
//#define xoa 39
#define xoa 34
#define input 18
#define setting 35
#define next 36
// #define input_2
//#define button_1  34 // nut thu 4
int adress=0;
int dem_input=0;   
int dem_input_1;   
int kt_1;
int couter_Mode;int couter_Mode1;
int state_input1=0;
int state_input2=0;
int state_thoat=0;
int state_setting=0;
int state_next=0;
int state_xoa=0;
int state_m=0;

long startTime;long startTime1=0;unsigned long startTime2=0;
int color_setting=0;int color_setting_phu=0;
int so_luong_chu=0;int so_luong_chu_phu=0;
int dislay=0;int dislay_phu=0;
int che_do=0;
// bien chuyen doi giua cac trang cai dat
int k=0;int i=0;
// cac trang cai dat
int trang_cai_so_luong;
// hello
int array_color[5]={RED,BLUE,WHITE,GREEN,YELLOW};
// CAC CHUOI 
//char* chuoi_so_luong[]=
//char* chuoi_color[5]={"RED","BLUE","WHITE","GREEN","YELLOW"};
//char* chuoi_color[5]={"RED","BLUE","WHITE","GREEN","YELLOW"};
int do_dai;
void setup()
{ 
  EEPROM.begin(20);

  dem_input = int(EEPROM.read(adress))*256;
  dem_input |= int(EEPROM.read(adress+1));
  // lay du lieu color tu esp32
  color_setting=int(EEPROM.read(adress+3));
  so_luong_chu=int(EEPROM.read(adress+5));
  dislay=int(EEPROM.read(adress+7));
  Serial.begin(9600);
  startTime2=millis();
  pinMode(xoa, INPUT_PULLUP);
  pinMode(input, INPUT_PULLUP);
  pinMode(thoat, INPUT_PULLUP);
  pinMode(setting, INPUT_PULLUP);
  pinMode(next, INPUT_PULLUP);
  configLedmatrix();
}
void loop() 
{   
  // xu li neu chuoi epprom sai nha
  if(color_setting>5){color_setting=1;EEPROM.write(adress+3,1);EEPROM.commit(); }
  if(so_luong_chu>3){so_luong_chu=2;EEPROM.write(adress+5,1);EEPROM.commit(); }
  if(dislay>2){dislay=1;EEPROM.write(adress+7,1);EEPROM.commit(); }
  if((so_luong_chu==4)&(dem_input>=10000)){dem_input=9999; EEPROM.write(adress,dem_input_1/256); EEPROM.write(adress+1,dem_input_1%256); EEPROM.commit(); matrix.clear();}
   //code hien thi led matrix
    vien_doc(0);vien_doc(63);
    vien_ngang(0);vien_ngang(31);
    
    matrix.setTextSize(1);
    if(che_do==0)
    {
      matrix.setTextColor(array_color[color_setting-1]);
       do_dai=String(dem_input_1).length();
      // truong hop hien thi bt 5 số
      if((dislay==1)&(so_luong_chu+3==5))
      {
        matrix.setFont(&Font_Thai_design_12_LED7_5);
           matrix.setCursor(61-(do_dai*12),26);
          matrix.print(dem_input_1);
      }
      if((dislay==1)&(so_luong_chu+3==4))
      {
        if(dem_input_1>=10000){dem_input_1=9999;}
        matrix.setFont(&Font_Thai_design_12_LED7_4so);
           matrix.setCursor(61-(do_dai*15),29);
          matrix.print(dem_input_1);
      }
      if((dislay==2)&(so_luong_chu+3==5))
      {
          matrix.setFont(&Font_Thai_design_12_LED7_4);
              if(do_dai==1)
             {
               matrix.setCursor(1,26);
               matrix.print(int(dem_input_1%10));
             }
             if(do_dai==2)
             {
                matrix.setCursor(1,26);
               matrix.print(int(dem_input_1%10));
               matrix.setCursor(13,26);
               matrix.print(int(dem_input_1/10));
             }
             if(do_dai==3)
             {
               matrix.setCursor(1,26);
               matrix.print(dem_input_1%10);
               matrix.setCursor(13,26);
               matrix.print((dem_input_1%100)/10);
               matrix.setCursor(25,26);
               matrix.print(dem_input_1/100);
             }
             if(do_dai==4)
             {
               matrix.setCursor(1,26);
               matrix.print(dem_input_1%10);
               matrix.setCursor(13,26);
               matrix.print((dem_input_1%100)/10);
               matrix.setCursor(25,26);
               matrix.print((dem_input_1%1000)/100);
               matrix.setCursor(37,26);
               matrix.print(dem_input_1/1000);
             }
             if(do_dai==5)
             {
                matrix.setCursor(1,26);
               matrix.print(dem_input_1%10);
               matrix.setCursor(13,26);
               matrix.print((dem_input_1%100)/10);
               matrix.setCursor(25,26);
               matrix.print((dem_input_1%1000)/100);
               matrix.setCursor(37,26);
               matrix.print((dem_input_1%10000)/1000);
                matrix.setCursor(49,26);
               matrix.print(dem_input_1/10000);
             }
      }
    //
    if((dislay==2)&(so_luong_chu+3==4))
      {
        if(dem_input>=10000){dem_input=9999;}
          matrix.setFont(&Font_Thai_design_12_LED7_4so_nguoc);
              if(do_dai==1)
             {
               matrix.setCursor(1,29);
               matrix.print(int(dem_input_1%10));
             }
             if(do_dai==2)
             {
                matrix.setCursor(1,29);
               matrix.print(int(dem_input_1%10));
               matrix.setCursor(16,29);
               matrix.print(int(dem_input_1/10));
             }
             if(do_dai==3)
             {
               matrix.setCursor(1,29);
               matrix.print(dem_input_1%10);
               matrix.setCursor(16,29);
               matrix.print((dem_input_1%100)/10);
               matrix.setCursor(31,29);
               matrix.print(dem_input_1/100);
             }
             if(do_dai==4)
             {
               matrix.setCursor(1,29);
               matrix.print(dem_input_1%10);
               matrix.setCursor(16,29);
               matrix.print((dem_input_1%100)/10);
               matrix.setCursor(31,29);
               matrix.print((dem_input_1%1000)/100);
               matrix.setCursor(46,29);
               matrix.print(dem_input_1/1000);
             }
      }
    }
    ///
    if((che_do==1))
    {
       switch(k){
           case 1:
            matrix.setFont(&Font_TMK_mini_8);
            matrix.setTextColor(WHITE);
             matrix.setCursor(4,10);
             matrix.print("SET NUMBER");
              matrix.setFont(&Font_Thai_2);
              matrix.setTextColor(RED);
             matrix.setCursor(16,30);
             matrix.print(so_luong_chu+3);
             matrix.print(" S""\xF2");   
           break;
           case 2:
            matrix.setFont(&Font_TMK_mini_8);
            matrix.setTextColor(WHITE);
            matrix.setCursor(6,10);
             matrix.print("SET COLOR");
             matrix.setFont(&Font_Thai_2);
             matrix.setTextColor(array_color[color_setting-1]);
              if(color_setting==1){
                      matrix.setCursor(18,30);
                   }else if(color_setting==2){
                      matrix.setCursor(13,30);
                   }else if(color_setting==5)
                   {
                        matrix.setCursor(6,30);
                    }else { matrix.setCursor(9,30);}
            // matrix.print(chuoi_color[color_setting-1]);
           break;
           case 3:
             matrix.setFont(&Font_TMK_mini_8);
             matrix.setTextColor(WHITE);
             matrix.setCursor(4,10);
             matrix.print("SET DISLAY");
             matrix.setFont(&Font_Thai_2);
             matrix.setTextColor(RED);
             matrix.setCursor(4,30);
             if(dislay==1)
             {
                matrix.print("NORMAL");
             }else if(dislay==2)
             {
                 matrix.print("CONVER");//converse
             }
           break;
       }
    }else if(che_do==2)
    {
       switch(k){
           case 1:
            matrix.setFont(&Font_TMK_mini_8);
            matrix.setTextColor(WHITE);
             matrix.setCursor(4,10);
             matrix.print("SET NUMBER");
             matrix.setFont(&Font_Thai_2);  
             matrix.setTextColor(RED);
             if ((unsigned long)(millis()-startTime2)<800)
             {
                 matrix.setCursor(16,30);
                 matrix.print(so_luong_chu_phu+3);
                 matrix.print(" S""\xF2"); 
              }else if((unsigned long)(millis()-startTime2)<1000)
               {
                 clear_vitri2(1,30,6);
               }else if((unsigned long)(millis()-startTime2)>=1000)
               {
                 startTime2=millis();
               }
           break;
           case 2:
            matrix.setFont(&Font_TMK_mini_8);
            matrix.setTextColor(WHITE);
            matrix.setCursor(6,10);
             matrix.print("SET COLOR");
               matrix.setFont(&Font_Thai_2);
             matrix.setTextColor(array_color[color_setting_phu-1]);
             if ((unsigned long)(millis()-startTime2)<800)
             {
                 if(color_setting_phu==1){
                      matrix.setCursor(18,30);
                   }else if(color_setting_phu==2){
                      matrix.setCursor(13,30);
                   }else if(color_setting_phu==5)
                   {
                        matrix.setCursor(6,30);
                    }else { matrix.setCursor(9,30);}
                  ////
                // matrix.print(chuoi_color[color_setting_phu-1]); 
              }else if((unsigned long)(millis()-startTime2)<1000)
               {
                 clear_vitri2(1,30,6);
               }else if((unsigned long)(millis()-startTime2)>=1000)
               {
                 startTime2=millis();
               }
           break;
           case 3:
             matrix.setFont(&Font_TMK_mini_8);
             matrix.setTextColor(WHITE);
             matrix.setCursor(4,10);
             matrix.print("SET DISLAY");
             matrix.setFont(&Font_Thai_2);
             matrix.setTextColor(RED);
              if ((unsigned long)(millis()-startTime2)<800)
             {
                         matrix.setCursor(4,30);
                               if(dislay_phu==1)
                               {
                                  matrix.print("NORMAL");
                               }else if(dislay_phu==2)
                               {
                                   matrix.print("CONVER");//converse
                               }
              }else if((unsigned long)(millis()-startTime2)<1000)
               {
                 clear_vitri2(1,30,6);
               }else if((unsigned long)(millis()-startTime2)>=1000)
               {
                 startTime2=millis();
               }
           break;
       }
    }
    // nut xoa nha pro
      int xoaStatus = digitalRead(xoa); 
      if(xoaStatus==LOW){
          if((xoaStatus==LOW)&(state_xoa!=1)){
            if(che_do==0)
            {
              state_xoa=1;
              startTime=millis();
            }
          }
         if((xoaStatus==LOW)&(state_xoa==1)&(state_m!=1))
         {
              couter_Mode = (millis() - startTime) / 1000;
              couter_Mode = couter_Mode / 1 % 10;
               if (couter_Mode >=1)
               {
                    dem_input=0;
                    state_m=1;
                    clear_vitri(1,26,5);
               }
          }
      }else if((xoaStatus==HIGH)&(state_xoa==1)){state_xoa=0;state_m=0;}

      // cam bien dau vao nha
     int inputStatus = digitalRead(input); 
     if (inputStatus == LOW)
     { 
      if((inputStatus==LOW)&(state_input1!=1))
      {
        state_input1=1;
        if(che_do==0)
        {
            if(so_luong_chu+3==5)
            {
              if(dem_input<99999)
              {
               dem_input++;
              }
             }
             if(so_luong_chu+3==4)
                {
                   if(dem_input<9999)
                    {
                     dem_input++;
                    }
                }
        }
       }
     }else if(inputStatus==HIGH){state_input1=0;}

     // lênh xu li cho cac nut cai dat nha pro
     // nut cai dat
    int settingStatus = digitalRead(setting); 
     if (settingStatus == LOW)
     { 
      if((settingStatus==LOW)&(state_setting!=1))
      {
         Serial.print("km");
        state_setting=1;
        startTime1=millis();
        if((che_do==1))
        {
           switch(k){
            // cai dat so luong chu
            case 1:
              so_luong_chu_phu=so_luong_chu;
              i=so_luong_chu;
            break;
              case 2:
              color_setting_phu=color_setting;
              i=color_setting;
            break;
            case 3:
              dislay_phu=dislay;
              i=dislay;
            break;
           }
            che_do=2;
        }else if((che_do==2))
        {
          // xoa han cac ki tu nha
           switch(k){
            // cai dat so luong chu
            case 1:
              so_luong_chu=so_luong_chu_phu;
              EEPROM.write(adress+5,so_luong_chu);EEPROM.commit();
            break;
              case 2:
              color_setting=color_setting_phu;
              EEPROM.write(adress+3,color_setting);EEPROM.commit();
            break;
            case 3:
              dislay=dislay_phu;
              EEPROM.write(adress+7,dislay);EEPROM.commit();
            break;
           }
           che_do=1;
           i=0;
           clear_vitri2(1,30,6);
        }
      }
      // set tang khi nhay 1s nha
       if((settingStatus==LOW)&(state_setting==1))
      {
        couter_Mode1 = (millis() - startTime1) / 1000;
              couter_Mode1 = couter_Mode1 / 1 % 10;
              if((che_do==0)&(k==0))
              {
                 if (couter_Mode1 >=1)
                 {
                      che_do=1;
                      k=1;   // bien chuyen cac che do 
                      matrix.clear();
                     Serial.print("km");
                 }
              }
      }
     }else if((settingStatus==HIGH)){state_setting=0;}
     // -------------
     // nut thoat
       int thoatStatus = digitalRead(thoat); 
         if (thoatStatus == LOW)
         { 
          if((thoatStatus==LOW)&(state_thoat!=1))
          {
              state_thoat=1;
              if((che_do==1)&(k!=0))
              {
                matrix.clear();
                che_do=0;
                //i=0;
                k=0;
                clear_vitri2(1,30,6);
              }else if((che_do==2)&(i!=0))
              {
                che_do=1;
                i=0;
                clear_vitri2(1,30,6);
                // su dung cac ham clear vitri nha
              }
          }
         }else if((thoatStatus==HIGH)){state_thoat=0;}

        // nut next qua nha
      int nextStatus = digitalRead(next); 
     if (nextStatus == LOW)
     { 
      if((nextStatus==LOW)&(state_next!=1))
      {
         state_next=1;
        if((che_do==1)&(k!=0))
        {
          if(k<3)
          {
            k++;
          }else {k=1;}
         // i=0;
          matrix.clear();
        }
        if((che_do==2)&(i!=0))
        {
          switch(k){
            case 1:
              if(i<2)
              {
                i++;
              }else {i=1;}
              // xoa vi tri nha
              so_luong_chu_phu=i;
              clear_vitri2(1,30,6);
            break;
            case 2:
              if(i<5)
              {
                i++;
              }else {i=1;}
              color_setting_phu=i;
              // xoa vi tri nha
              clear_vitri2(1,30,6);
            break;
            case 3:
              if(i<2)
              {
                i++;
              }else {i=1;}
              // xoa vi tri nha
              dislay_phu=i;
              clear_vitri2(1,30,6);
            break;
          }
        }
      }
     }else if((nextStatus==HIGH)){state_next=0;}

     // 1 ham xu li khac nha
     //if(che_do==1){i=0;}
     //if(che_do==0){i=0;k=0;}
     //
   if(che_do==0)
   {
       if(dem_input_1!=dem_input)
       {
         // ham xu xi hien thi dem input
         kt_1=String(dem_input_1).length();
      // code xu li cho hien thi chuoi nha
       if(so_luong_chu+3==5)
       {
        if(dislay==2)
          {
             clear_vitri(1,26,1);
             if(kt_1==2)
             {
              if((dem_input_1/10)!=(dem_input/10)){clear_vitri(13,26,1);}
             }
             else if(kt_1==3)
             {
              if((dem_input_1/10)!=(dem_input/10)){clear_vitri(13,26,1);}
              if((dem_input_1/100)!=(dem_input/100)){clear_vitri(25,26,1);}
             }
              else if(kt_1==4)
             {
              if((dem_input_1/10)!=(dem_input/10)){clear_vitri(13,26,1);}
              if((dem_input_1/100)!=(dem_input/100)){clear_vitri(25,26,1);}
              if((dem_input_1/1000)!=(dem_input/1000)){clear_vitri(37,26,1);}
             }else
             {
              if((dem_input_1/10)!=(dem_input/10)){clear_vitri(13,26,1);}
              if((dem_input_1/100)!=(dem_input/100)){clear_vitri(25,26,1);}
              if((dem_input_1/1000)!=(dem_input/1000)){clear_vitri(37,26,1);}
              if((dem_input_1/10000)!=(dem_input/10000)){clear_vitri(49,26,1);}  
             }
             dem_input_1=dem_input;
             EEPROM.write(adress,dem_input_1/256);
             EEPROM.write(adress+1,dem_input_1%256);
             EEPROM.commit(); 
             Serial.println(dem_input);
            }
             if(dislay==1)
              {
                   clear_vitri(49,26,1);
                   if(kt_1==2)
                   {
                    if((dem_input_1/10)!=(dem_input/10)){clear_vitri(37,26,1);}
                   }
                   else if(kt_1==3)
                   {
                    if((dem_input_1/10)!=(dem_input/10)){clear_vitri(37,26,1);}
                    if((dem_input_1/100)!=(dem_input/100)){clear_vitri(25,26,1);}
                   }
                    else if(kt_1==4)
                   {
                    if((dem_input_1/10)!=(dem_input/10)){clear_vitri(37,26,1);}
                    if((dem_input_1/100)!=(dem_input/100)){clear_vitri(25,26,1);}
                    if((dem_input_1/1000)!=(dem_input/1000)){clear_vitri(13,26,1);}
                   }else
                   {
                    if((dem_input_1/10)!=(dem_input/10)){clear_vitri(37,26,1);}
                    if((dem_input_1/100)!=(dem_input/100)){clear_vitri(25,26,1);}
                    if((dem_input_1/1000)!=(dem_input/1000)){clear_vitri(13,26,1);}
                    if((dem_input_1/10000)!=(dem_input/10000)){clear_vitri(1,26,1);}  
                   }
                   dem_input_1=dem_input;
                   EEPROM.write(adress,dem_input_1/256);
                   EEPROM.write(adress+1,dem_input_1%256);
                   EEPROM.commit(); 
                   Serial.println(dem_input);
             }
            }
            //------------------
            //---------------
            // clear 4 so
         if(so_luong_chu+3==4)
       {
        if(dislay==2)
          {
             clear_vitri3(1,29,1);
             if(kt_1==2)
             {
              if((dem_input_1/10)!=(dem_input/10)){clear_vitri3(16,29,1);}
             }
             else if(kt_1==3)
             {
              if((dem_input_1/10)!=(dem_input/10)){clear_vitri3(16,29,1);}
              if((dem_input_1/100)!=(dem_input/100)){clear_vitri3(31,29,1);}
             }
              else if(kt_1==4)
             {
              if((dem_input_1/10)!=(dem_input/10)){clear_vitri3(16,29,1);}
              if((dem_input_1/100)!=(dem_input/100)){clear_vitri3(31,29,1);}
              if((dem_input_1/1000)!=(dem_input/1000)){clear_vitri3(46,29,1);}
             }
             dem_input_1=dem_input;
             EEPROM.write(adress,dem_input_1/256);
             EEPROM.write(adress+1,dem_input_1%256);
             EEPROM.commit(); 
             Serial.println(dem_input);
            }
             if(dislay==1)
              {
                   clear_vitri3(46,29,1);
                   if(kt_1==2)
                   {
                    if((dem_input_1/10)!=(dem_input/10)){clear_vitri3(31,29,1);}
                   }
                   else if(kt_1==3)
                   {
                    if((dem_input_1/10)!=(dem_input/10)){clear_vitri3(31,29,1);}
                    if((dem_input_1/100)!=(dem_input/100)){clear_vitri3(16,29,1);}
                   }
                    else if(kt_1==4)
                   {
                    if((dem_input_1/10)!=(dem_input/10)){clear_vitri3(31,29,1);}
                    if((dem_input_1/100)!=(dem_input/100)){clear_vitri3(16,29,1);}
                    if((dem_input_1/1000)!=(dem_input/1000)){clear_vitri3(1,29,1);}
                   }
                   dem_input_1=dem_input;
                   EEPROM.write(adress,dem_input_1/256);
                   EEPROM.write(adress+1,dem_input_1%256);
                   EEPROM.commit(); 
                   Serial.println(dem_input);
             }
            }
       }
   }
}