#include <ESP8266WiFi.h>                                               
#include <FirebaseArduino.h>
// fireabase 계정 설정      
#define FIREBASE_HOST "fir-led-control-cefd3.firebaseio.com"     
#define FIREBASE_AUTH "PmTq6zaWK7LeUplAAy2W9yJtbs3bUSffLMzktIEM"
// Wife 이름과 비밀번호 설정 
#define WIFI_SSID "U+Net8F5C"                                          
#define WIFI_PASSWORD "DD82007902"  


String LED_fireStatus = ""; // LED_fireStatus를 문자열로 선언
 
int LED = D2;      // LED를 D2에 연결 할 것이다라는 것을 선언
                                                             
void setup(){
 Serial.begin(9600);
 delay(1000);    
 pinMode(LED, OUTPUT);  
               
 WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  // 와이파이 연결을 시도                            
 Serial.print("Connecting to ");
 Serial.print(WIFI_SSID);
 while (WiFi.status() != WL_CONNECTED){
   Serial.print(".");
   delay(500);
 }
 Serial.println();
 Serial.print("Connected to ");
 Serial.println(WIFI_SSID);
 Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);  // firebase 계정 api키 확인 후 연결
 Firebase.setString("LED_STATUS", "OFF"); // 파이어베이스 DB에 LED_STATUS OFF를 셋팅합니다.
}
void loop(){
 LED_fireStatus = Firebase.getString("LED_STATUS");  // LED_STATUS를 LED_fireStatus와 연결합니다.  
 if (LED_fireStatus == "ON")  { // 벨류 값이 ON이면
   Serial.println("RED LED Turned ON");         // 모니터에 출력됨                                               
   digitalWrite(LED, LOW);      
 }
 else if (LED_fireStatus == "OFF") { // 벨류 값이 OFF이면
   Serial.println("RED LED Turned OFF"); //모니터 출력
   digitalWrite(LED, HIGH);    
 } else {
   Serial.println("Command Error! Please send ON/OFF"); // 잘못된 값이 들어갔을 때 시리얼 모니터에 출력됩니다.
 }
 delay(1000);
}
