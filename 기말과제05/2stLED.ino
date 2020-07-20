// 사용할 라이브러리
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <FirebaseArduino.h>
#include <DHT.h>
#include <time.h>

// 파이어베이스 설정
#define FIREBASE_HOST "sensorfirebase-a3c65.firebaseio.com"
#define FIREBASE_AUTH "icqzyzlz1x9K0qQdY6yb9PCVEQYmrnKJy1jNNghb"

// WiFi 연결 설정
#define WIFI_SSID "U+Net8F5C" // WiFi 이름
#define WIFI_PASSWORD "DD82007902" // WiFi 비밀번호

// 온습도 센서 설정 (D4 연결 및 DHT11 사용)
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// NTPClient 설정 및 kr.pool.npt.org의 값들을 가져옴
WiFiUDP udp;
NTPClient timeClient(udp, "kr.pool.ntp.org", 32400, 3600000);

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.mode(WIFI_STA);  // Wi-Fi 초기화 
  // 와이파이 연결
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
  timeClient.begin();

  // Firebase 실시간 데이터베이스 인증
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  delay(5000);

  // h에는 습도, t에는 온도값을 읽음
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // 연결 실패시 실패되었다는 것이 출력이 된 후 되돌아감
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(500);
    return;
  }

  // 시간을 업데이트 함
  timeClient.update();

//  int hour = timeClient.getHours();
//  int minute = timeClient.getMinutes();
//  int second = timeClient.getSeconds();

  // 시간 설정
  unsigned long epochTime = timeClient.getEpochTime();

  struct tm *ptm = gmtime ((time_t *)&epochTime); 
  
  int currentMonth = ptm->tm_mon+1;
  int monthDay = ptm->tm_mday;
  int currentYear = ptm->tm_year+1900;
  String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
  String currentTime = timeClient.getFormattedTime();
  // currentDateTime에 날짜와 시간을 세팅함
  String currentDateTime = currentDate + " " + currentTime;
  
//  Serial.println(timeClient.getFormattedTime());
//  Serial.println(currentDate);

  // 시리얼모니터에 습도와 온도 그리고, 시간을 출력함
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("   Temperature: ");
  Serial.print(t);
  Serial.print("   Time: ");
  Serial.print(currentDateTime);

  // Json 형식으로 파이어베이스에 온도 습도 시간을 차례로 값을 입력함
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["temperature"] = t;
  root["humidity"] = h;
  //root["time"] = hour;
  root["time"] = currentDateTime;
  
  // /odinbox 에 새로운 값을 추가함
  String name = Firebase.push("odinbox", root);
  // handle error
  if (Firebase.failed()) {
      Serial.println("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.println("");
  Serial.print("   pushed: /odinbox/");
  Serial.println(name + "\n");
  delay(5000);
}
