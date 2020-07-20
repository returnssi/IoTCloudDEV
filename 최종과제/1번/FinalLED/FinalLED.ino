#include <ESP8266WiFi.h>                                              
#include <FirebaseArduino.h>      
// 파이어베이스 설정
#define FIREBASE_HOST "sensorfirebase-a3c65.firebaseio.com"
#define FIREBASE_AUTH "icqzyzlz1x9K0qQdY6yb9PCVEQYmrnKJy1jNNghb"

// WiFi 연결 설정
#define WIFI_SSID "U+Net8F5C" // WiFi 이름
#define WIFI_PASSWORD "DD82007902" // WiFi 비밀번호
 
String BLUE_fireStatus = "";
 
int BLUE_LED = D2;      
                                                             
void setup(){
 Serial.begin(9600);
 delay(1000);    
 pinMode(BLUE_LED, OUTPUT);  
               
 WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                              
 Serial.print("Connecting to ");
 Serial.print(WIFI_SSID);
 while (WiFi.status() != WL_CONNECTED){
   Serial.print(".");
   delay(500);
 }
 Serial.println();
 Serial.print("Connected to ");
 Serial.println(WIFI_SSID);
 Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 Firebase.setString("BLUE_LED_STATUS", "OFF");
}
void loop(){
 BLUE_fireStatus = Firebase.getString("BLUE_LED_STATUS");    
 if (BLUE_fireStatus == "ON")  {
   Serial.println("BLUE LED Turned ON");                                                        
   digitalWrite(BLUE_LED, HIGH);      
 }
 else if (BLUE_fireStatus == "OFF") {
   Serial.println("BLUE LED Turned OFF");
   digitalWrite(BLUE_LED, LOW);    
 } else {
   Serial.println("Command Error! Please send ON/OFF");
 }
 delay(1000);
}
