
//------------------------------------------------------ ATME VIET NAM ---------------------------------------------------
//-------------- https://www.atme.vn --------------- thu.vo.lhu@gmail.com ------------- 0983 383 283 ---------------------

#include "Adafruit_GFX.h" // Chen thu vien font chu

String inString="";
boolean stringComplete=false;
String commandString="";

#include <Fonts/Font_TMKFreeMonoBold9pt7b.h>
#include <Fonts/Font_TMKTEK_18x7.h>
#include <Fonts/Font_Thai.h>
#include <Fonts/Font_Thai_2.h>
#include <Fonts/tmk_te1.h>
#include <Fonts/Font_TMK_mini_8.h>
#include <Fonts/Font_Thai_2_1panel_led7_nguoc.h>
//#include <Fonts/Font_TMK_mono_12x8.h>

#include <Fonts/Font_Thai_design_12.h>
#include <Fonts/Font_Thai_design_12_LED7.h>
#include <Fonts/Font_Thai_design_12_LED7_1.h>
#include <Fonts/Font_Thai_design_12_LED7_4so.h>
#include <Fonts/Font_Thai_design_12_LED7_5.h>
#include <ESP32-RGB64x32MatrixPanel-I2S-DMA.h>

RGB64x32MatrixPanel_I2S_DMA matrix;

#define setBrightness(x) fillScreen(0) // 
#define clear() fillScreen(0)
#define show() drawPixel(0, 0, 0);     //
#define Color(x,y,z) color444(x/16,y/16,z/16)

#define LED_BLACK    0

//B G R  rgb
#define RED     matrix.Color(0,0,255)
#define BLUE    matrix.Color(255,0,0)
#define YELLOW  matrix.Color(255,255,0)
#define GREEN   matrix.Color(0,255,0)
#define WHITE   matrix.Color(255,255,255)
#define Color_TMK_1 matrix.Color(20,150,400)
#define Color_TMK_2 matrix.Color(10,200,40)
#define Color_TMK_3 matrix.Color(255,5,5)
#define Black   matrix.Color(0,0,0)

#define LED_RED_VERYLOW (3  << 11)
#define LED_RED_LOW     (7  << 11)
#define LED_RED_MEDIUM  (15 << 11)
#define LED_RED_HIGH    (31 << 11)

#define LED_GREEN_VERYLOW (1  << 5)   
#define LED_GREEN_LOW     (15 << 5)  
#define LED_GREEN_MEDIUM  (31 << 5)  
#define LED_GREEN_HIGH    (63 << 5)  

#define LED_BLUE_VERYLOW  3
#define LED_BLUE_LOW      7
#define LED_BLUE_MEDIUM   15
#define LED_BLUE_HIGH     31

#define LED_ORANGE_VERYLOW  (LED_RED_VERYLOW + LED_GREEN_VERYLOW)
#define LED_ORANGE_LOW      (LED_RED_LOW     + LED_GREEN_LOW)
#define LED_ORANGE_MEDIUM   (LED_RED_MEDIUM  + LED_GREEN_MEDIUM)
#define LED_ORANGE_HIGH     (LED_RED_HIGH    + LED_GREEN_HIGH)

#define LED_PURPLE_VERYLOW  (LED_RED_VERYLOW + LED_BLUE_VERYLOW)
#define LED_PURPLE_LOW      (LED_RED_LOW     + LED_BLUE_LOW)
#define LED_PURPLE_MEDIUM   (LED_RED_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_PURPLE_HIGH     (LED_RED_HIGH    + LED_BLUE_HIGH)

#define LED_CYAN_VERYLOW    (LED_GREEN_VERYLOW + LED_BLUE_VERYLOW)
#define LED_CYAN_LOW        (LED_GREEN_LOW     + LED_BLUE_LOW)
#define LED_CYAN_MEDIUM     (LED_GREEN_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_CYAN_HIGH       (LED_GREEN_HIGH    + LED_BLUE_HIGH)

#define LED_WHITE_VERYLOW   (LED_RED_VERYLOW + LED_GREEN_VERYLOW + LED_BLUE_VERYLOW)
#define LED_WHITE_LOW       (LED_RED_LOW     + LED_GREEN_LOW     + LED_BLUE_LOW)
#define LED_WHITE_MEDIUM    (LED_RED_MEDIUM  + LED_GREEN_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_WHITE_HIGH      (LED_RED_HIGH    + LED_GREEN_HIGH    + LED_BLUE_HIGH)
boolean enMatrixClear = false;
unsigned long timer_update_display = 0;  //thoi gian update man hinh cua code
unsigned long timer_update_value =  0; // thoi gian update gia tri tu modbus len man hinh
int Code_Step = 0;//bien xac nhan tung buoc
const static unsigned long Time_Step = 3; // thoi gian chyen buoc ms
