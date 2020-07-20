#include <DHT.h>

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
 
// Set these to run example.
#define FIREBASE_HOST "odindht.firebaseio.com"
#define FIREBASE_AUTH "dJL7UCMBugX9dy37BLD5an1J9n8KsrF2Z9UZJsrJ"
#define WIFI_SSID "sub_OdinBOX"
#define WIFI_PASSWORD "@odin1544"
 
void setup() {
  Serial.begin(9600);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  dht.begin();
  
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
   
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
 
void loop() {
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();
  Serial.print("Temperature = ");
  Serial.println(temp);
  Serial.print("Humidity = ");
  Serial.println(humi);
 
//  Firebase.setFloat("temperature", temp);  
//  Firebase.setFloat("humidity", humi);    

  Firebase.pushFloat("temperature", temp);  
  Firebase.pushFloat("humidity", humi);       

//  StaticJsonBuffer<200> jsonbuffer;
//  JsonObject& root = jsonbuffer.createObject();
//  root["temperature"] = temp;
 // root["humidity"] = humi;

//  String name = Firebase.push("logDHT", root);
  
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logDHT/");
//  Serial.println(name);
  
  delay(5000);
}
