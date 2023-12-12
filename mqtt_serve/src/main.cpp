// // #include <Arduino.h>
// // #include <WiFi.h>
// // #include <PubSubClient.h>
// // const char* ssid ="ChiSen";
// // const char* pass ="12347788";

// // const char* brokerUser = "tmducck18b@gmail.com";
// // const char* brokerPass= "tmducam18";
// // const char* broker= "mqtt.dioty.co";

// // WiFiClient espClient;
// // PubSubClient client(espClient);

// // void setupWifi()
// // {
// //   delay(100);
// //   Serial.print("\nConnecting to");
// //   Serial.print(ssid);
// //    WiFi.begin(ssid,pass);
// //    while (WiFi.status() != WL_CONNECTED) {
// //      delay(100);
// //      Serial.println("-  ");
// //  }
// //   Serial.print("\nConnected to");
// //   Serial.print(ssid);
// // }
// // void reconnect()
// // {
// //   while(!client.connected())
// //   {
// //      Serial.print("\nConnectng to");
// //      Serial.println(broker);
// //      if(client.connect("koikoikoi",brokerUser,brokerPass))
// //      {
// //       Serial.print("\nConnected to");
// //       Serial.println(broker);
// //      }else {
// //       Serial.println("\nTrying connected again");
// //       delay(5000);
// //      }
// //   }
// // }

// // void setup() {
// //   Serial.begin(9600);
// //   setupWifi();
// //   client.setServer(broker,1883);
// // }
// // void loop() {
// //   // put your main code here, to run repeatedly:
// //   if(!client.connected())
// //   {
// //     reconnect();
// //   }
// //   client.loop();
// // }

// #include <WiFi.h>
// #include <PubSubClient.h>
// #define BUT1 4
// #define BUT2 16
// #define LED1 17
// #define LED2 5
// String ledStatus1 = "ON";
// String ledStatus2 = "ON";
 
// const char* ssid = "ChiSen";
// const char* password = "12347788";
 
// #define MQTT_SERVER "broker.hivemq.com"
// #define MQTT_PORT 1883
// #define MQTT_USER "mabattu123"
// #define MQTT_PASSWORD "12345678"
 
// #define MQTT_LED1_TOPIC "MQTT_ESP32/LED1"
// #define MQTT_LED2_TOPIC "MQTT_ESP32/LED2"
 
// unsigned long previousMillis = 0; 
// const long interval = 5000;
 
// WiFiClient wifiClient;
// PubSubClient client(wifiClient);
 
 
// void setup_wifi() {
//   Serial.print("Connecting to ");
//   Serial.println(ssid);
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("");
//   Serial.println("WiFi connected");
//   Serial.println("IP address: ");
//   Serial.println(WiFi.localIP());
// }
 
// void connect_to_broker() {
//   while (!client.connected()) {
//     Serial.print("Attempting MQTT connection...");
//     String clientId = "ESP32";
//     clientId += String(random(0xffff), HEX);
//     if (client.connect(clientId.c_str())) {
//       Serial.println("connected");
//       client.subscribe(MQTT_LED1_TOPIC);
//       client.subscribe(MQTT_LED2_TOPIC);
//     } else {
//       Serial.print("failed, rc=");
//       Serial.print(client.state());
//       Serial.println(" try again in 2 seconds");
//       delay(2000);
//     }
//   }
// }
 
// void callback(char* topic, byte *payload, unsigned int length) {
//   char status[20];
//   Serial.println("-------new message from broker-----");
//   Serial.print("topic: ");
//   Serial.println(topic);
//   Serial.print("message: ");
//   Serial.write(payload, length);
//   Serial.println();
//   for(int i = 0; i<length; i++)
//   {
//     status[i] = payload[i];
//   }
//   Serial.println(status);
//   if(String(topic) == MQTT_LED1_TOPIC)
//   {
//     if(String(status) == "OFF")
//     {
//       ledStatus1 = "OFF";
//       digitalWrite(LED1, LOW);
//       Serial.println("LED1 OFF");
//     }
//     else if(String(status) == "ON")
//     {
//       ledStatus1 = "ON";
//       digitalWrite(LED1, HIGH);
//       Serial.println("LED1 ON");
//     }
//   }
 
//   if(String(topic) == MQTT_LED2_TOPIC)
//   {
//     if(String(status) == "OFF")
//     {
//       ledStatus2 = "OFF";
//       digitalWrite(LED2, LOW);
//       Serial.println("LED2 OFF");
//     }
//     else if(String(status) == "ON")
//     {
//       ledStatus2 = "ON";
//       digitalWrite(LED2, HIGH);
//       Serial.println("LED2 ON");
//     }
//   }
   
// }
 
// void setup() {
//   Serial.begin(9600);
//   Serial.setTimeout(500);
//   setup_wifi();
//   client.setServer(MQTT_SERVER, MQTT_PORT );
//   client.setCallback(callback);
//   connect_to_broker();
//   Serial.println("Start transfer");
//   pinMode(BUT1, INPUT_PULLUP);
//   pinMode(BUT2, INPUT_PULLUP);
//   pinMode(LED1, OUTPUT);
//   pinMode(LED2, OUTPUT);
// }
 
  
// void loop() {
//   client.loop();
//   if (!client.connected()) {
//     connect_to_broker();
//   }
 
//   if(digitalRead(BUT1) == 0) 
//   {
//     while (digitalRead(BUT1) == 0)
//     {
//       /* cho nut dc nha */
//     }
//     if(ledStatus1 == "ON")
//     {
//       client.publish(MQTT_LED1_TOPIC, "OFF");
//       ledStatus1 = "OFF";
//     }
//     else if(ledStatus1 == "OFF")
//     {
//       client.publish(MQTT_LED1_TOPIC, "ON");
//       ledStatus1 = "ON";
//     }
//   }
//   if(digitalRead(BUT2) == 0) 
//   {
//     while (digitalRead(BUT2) == 0)
//     {
//       /* cho nut dc nha */
//     }
//     if(ledStatus2 == "ON")
//     {
//       client.publish(MQTT_LED2_TOPIC, "OFF");
//       ledStatus2 = "OFF";
//     }
//     else if(ledStatus2 == "OFF")
//     {
//       client.publish(MQTT_LED2_TOPIC, "ON");
//        ledStatus2 = "ON";
//     }
//   }
// }
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

// WiFi
const char *ssid = "ChiSen"; // Enter your WiFi name
const char *password = "12347788";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "broker.emqx.io";
const char *topic = "esp32/test";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);
void callback(char *topic, byte *payload, unsigned int length) {
 Serial.print("Message arrived in topic: ");
 Serial.println(topic);
 Serial.print("Message:");
 for (int i = 0; i < length; i++) {
     Serial.print((char) payload[i]);
 }
 Serial.println();
 Serial.println("-----------------------");
}
void setup() {
 // Set software serial baud to 115200;
 Serial.begin(115200);
 //Serial.begin(9600);
 // connecting to a WiFi network
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.println("Connecting to WiFi..");
 }
 Serial.println("Connected to the WiFi network");
 //connecting to a mqtt broker
 client.setServer(mqtt_broker, mqtt_port);
 client.setCallback(callback);
 while (!client.connected()) {
     String client_id = "esp32-client-";
     client_id += String(WiFi.macAddress());
     Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
     if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
         Serial.println("Public emqx mqtt broker connected");
     } else {
         Serial.print("failed with state ");
         Serial.print(client.state());
         delay(2000);
     }
 }
 // publish and subscribe
 client.publish(topic, "Hi EMQX I'm ESP32 ^^");
 client.subscribe(topic);
}

void loop() {
 client.loop();
}