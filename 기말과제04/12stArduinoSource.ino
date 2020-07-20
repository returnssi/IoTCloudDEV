  
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>
#include <time.h>

// Config Firebase
#define FIREBASE_HOST "hellofirebase3-f62f6.firebaseio.com"
#define FIREBASE_AUTH "rzJGnuuL5yo2ZTxgoBsB7dLZjPc3PMZNF39Z8Nc0"

// Config connect WiFi
#define WIFI_SSID "U+Net8F5C" // Put here your Wi-Fi SSID
#define WIFI_PASSWORD "DD82007902" // Put here your Wi-Fi password

// Config DHT
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Config time
int timezone = 9; // 9 -> 한국시간
int dst = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.mode(WIFI_STA);  // Wi-Fi 초기화 
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting......");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  // NTP 설정(네트워크 시간 설정)
  configTime(timezone * 3600, dst, "kr.pool.ntp.org", "time.kriss.re.kr");
  Serial.println("Waiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Now: " + NowString());

  // Firebase 실시간 데이터베이스 인증
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  delay(5000);
  // Read temp & Humidity for DHT22
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(500);
    return;
  }
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.println();

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["temperature"] = t;
  root["humidity"] = h;
  root["time"] = NowString();
  
  // append a new value to /logDHT
  String name = Firebase.push("logDHT", root);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logDHT/");
  Serial.println(name);
  delay(5000);
}

// 현재 시간 받아오는 함수
String NowString() {
  time_t now = time(nullptr);
  struct tm* newtime = localtime(&now);
  String tmpNow = "";
  tmpNow += String(newtime->tm_year + 1900);
  tmpNow += "년";
  tmpNow += String(newtime->tm_mon + 1);
  tmpNow += "월";
  tmpNow += String(newtime->tm_mday);
  tmpNow += "일 ";
  tmpNow += String(newtime->tm_hour + 6);
  tmpNow += "시";
  tmpNow += String(newtime->tm_min);
  tmpNow += "분";
  tmpNow += String(newtime->tm_sec);
  return tmpNow;
}
