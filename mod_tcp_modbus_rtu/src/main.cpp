#include <Arduino.h>
// sử dụng modbus poll de kiem tra nhe
#ifdef ESP8266
  #include <ESP8266WiFi.h>
#else //ESP32
  #include <WiFi.h>
#endif
#include <ModbusIP_ESP8266.h>

#include <Wire.h>  
#include <ModbusRtu.h>

#define TXEN  0
#define RXD2 16
#define TXD2 17

#define Output_1 21

const int SENSOR_HREG = 0;
const int TERMO = 1;
const int  D3 = 2;
uint16_t res=0;
// ModbusIP object
// nhan gia tri cua di chi ip esp32 nhé
// 
ModbusIP mb;
unsigned long ts=0;

uint16_t au16data[10]; //!< data array for modbus network sharing
uint8_t u8state; //!< machine state
uint8_t u8query; //!< pointer to message query

ModbusRS master(0,0,0); // this is master and RS-232 or USB-FTDI
modbus_t telegram[1];
unsigned long u32wait;

void setup() {

      telegram[0].u8id = 1;           // slave address
      telegram[0].u8fct = 3;          // function code (this one is registers read)
      telegram[0].u16RegAdd = 0;      // start address in slave
      telegram[0].u16CoilsNo = 10;    // number of elements (coils or registers) to read
      telegram[0].au16reg = au16data; // pointer to a memory array in the Arduino

      Serial2.begin(38400,SERIAL_8N1,RXD2,TXD2);
      master.start();
      master.setTimeOut(100);         // if there is no answer in 5000 ms, roll over
      u32wait = millis() + 1;
      u8state = u8query = 0; 
      Serial.begin(115200);
      //Conectar con SSID de red local
      // WiFi.begin("linksys");
       WiFi.begin("TMK LAU 1 2.4GHz", "tmk654321");
      //WiFi.begin("ChiSen", "12347788");
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP()); //Mostrar IP asignada

    mb.server();                    //ESP32 en modo servidor
    mb.addHreg(SENSOR_HREG);        //Crear Holding registers en la dirección seleccionada
    mb.addHreg(TERMO);              // ghi gia tri len server
    mb.addIreg(D3);                 // nhan gia tri tu server
    ts = millis();

   pinMode(Output_1, OUTPUT);
   digitalWrite(Output_1, HIGH);
    
}
int i=0;
void loop() {

  //Llamar a librerias y funciones para protocolo MODBUS
  mb.task();

  switch( u8state ) {
  case 0: 
    if (millis() > u32wait) u8state++; // wait state
    break;
  case 1: 
    master.query( telegram[u8query] ); // send query (only once)
     u8state++;
     u8query++;
  if (u8query >1) u8query = 0;
    break;
  case 2:
    master.poll();                    // check incoming messages
    if (master.getState() == COM_IDLE) {
      u8state = 0;
      u32wait = millis()+1; 
    }
    break;
  }
   //Leer temperatura e incrementar variable cada 2 segundos
   if (millis() > ts + 2000) {
       ts = millis();
       i++;                           //Incremento de variable
       if(i>100){ 
        i=0;
       } 
       //int k1=0;
       mb.Hreg(SENSOR_HREG, i);      //Escribir valor de contador y temperatura en los holding registers
       mb.Hreg(TERMO,45);
       int k1=mb.Ireg(D3);
       

       //mb.Ireg(D3,res);
       Serial.print(mb.Hreg(SENSOR_HREG));
       Serial.println(mb.Hreg(TERMO));
       Serial.println(k1);
       //Serial.println(res);
   }
   delay(10);
    if(au16data[0]>=1)
  {
    digitalWrite(Output_1,LOW);
  }else{
     digitalWrite(Output_1,HIGH);
  }
   //delay(10);
}