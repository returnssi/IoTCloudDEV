#include <DHT.h>
#include <ESP8266WiFi.h>
#define DHTPIN D3 // D0
#define DHTTYPE DHT11
#define LED_PIN2 D2

const char* ssid = "U+Net8F5C";
const char* password = "DD82007902";


const char* server = "api.thingspeak.com";
String apiKey = "KFIGONHQ8THTXD5N";

WiFiClient client;
DHT dht(DHTPIN, DHTTYPE, D3);


void setup() {
  pinMode(LED_PIN2, OUTPUT);
  Serial.begin(9600);
  Serial.println();
  Serial.println("ThingSpeak");


  // DHT11 초기화
  dht.begin();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  //WiFi 초기화
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected!!");
 
}
void loop() {
  float t, h;
  t = dht.readTemperature();
  h = dht.readHumidity();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read!");
          digitalWrite(LED_PIN2,HIGH);
    return;
  }
  if (client.connect(server, 80)) { //"아이피" or thingspeak.com
      String postStr = apiKey;
             postStr += "&field1=";
             postStr += String(t);
             postStr += "&field2=";
             postStr += String(h);
             postStr += "\r\n\r\n";

    // Rest API POST  요청 : 웹서버에 resource 생성 요청
    client.print("POST /update HTTP/1.1\n");
    client.print("host: api.thingspeak.com\n");

    // 온도 데이터를 한번 전송하고 client와 연결을 끊고 15초 시간 지연 대기 한다.

      client.print("Connection: close\n");
      client.print("X-THINGSPEAKAPIKEY: " +apiKey+ "\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(postStr.length());
      client.print("\n\n");
      client.print(postStr);

      
      Serial.print("Temp : ");
      Serial.print(t);
      Serial.print("\t humidity: ");
      Serial.print(h);
      Serial.println("%. Send to Thingspeak.");
      
  digitalWrite(LED_PIN2, HIGH);
  delay(500);
  digitalWrite(LED_PIN2, LOW);
  delay(500);
      }
      client.stop();
    // 무료 계정의 업데이트 주기는 15초
      Serial.println("Waiting...");
      digitalWrite(LED_PIN2,HIGH);
      delay(15000);
}
