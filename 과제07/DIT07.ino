#include <ESP8266WiFi.h>

const char* ssid = "Galaxy";  // 와이파이 공유기 혹은 스마트폰 테더링 SSID
const char* password = "15441544";  // 와이파이 공유기 혹은 스마트폰 테더링 접속 비밀번호

int redledpin = D4;
int Blueledpin = D5;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(100);
  pinMode(redledpin, OUTPUT);    
  digitalWrite(redledpin, LOW);   

  pinMode(Blueledpin, OUTPUT);    
  digitalWrite(Blueledpin, LOW);  

  // 와이파이 네트워크에 접속
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected!!");

  // 웹서버 개시
  server.begin();
  Serial.println("Server started");

  // 접속할 IP 주소 표시
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  Serial.println("");
}

void loop() {
// 클라이언트가 접속되었는지 확인
  WiFiClient client = server.available();   
  if(!client) {  
    return;
  } 

  // 클라이언트가 데이터를 보낼 때까지 기다림
  Serial.println("연결 완료 !");
  while(!client.available()) {
    delay(1);
  }

  // request의 첫번째 줄을 읽어들임 : GET / HTTP/1.1
  String request = client.readStringUntil('\r');
  Serial.print("요청 : ");
  Serial.println(request);
  client.flush();

  // request에 따른 LED 제어
  // request.indexOf는 "/LED=ON" 혹은 "/LED=OFF" 문자열이 있는지 찾고
  // 찾는 문자열이 있으면 문자열을 return하고, 없으면 -1을 return 한다.
  int value = LOW;
  if(request.indexOf("/redLED=ON") != -1) {
    digitalWrite(redledpin, HIGH);
    value = HIGH;   
  }
  if(request.indexOf("/redLED=OFF") != -1) {
    digitalWrite(redledpin, LOW);
    value = LOW;
  }
  if(request.indexOf("/BlueLED=ON") != -1) {
    digitalWrite(Blueledpin, HIGH);
    value = HIGH;   
  }
  if(request.indexOf("/BlueLED=OFF") != -1) {
    digitalWrite(Blueledpin, LOW);
    value = LOW;
  }

  // 클라이언트 request에 대한 응답 메시지
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<meta charset=\"UTF-8\">"); -
  client.println("<h1> LED 제어기 </h1>");
  
  if(value)
    client.print("On");
  else 
    client.print("Off");
  
  client.println("<br><br>");
  client.println("<a href=\"/redLED=ON\"\"><button>빨간색 LED 켜</button></a>");
  client.println("<a href=\"/redLED=OFF\"\"><button>빨간색 LED 꺼</button></a>");
  client.println("</html>");
  client.println("<br><br>");
  client.println("<a href=\"/BlueLED=ON\"\"><button>파란색 LED 켜</button></a>");
  client.println("<a href=\"/BlueLED=OFF\"\"><button>파란색 LED 켜</button></a>");
  client.println("</html>");

  delay(1);
  Serial.println("클라이언트 연결 종료!!");
  Serial.println();
}
