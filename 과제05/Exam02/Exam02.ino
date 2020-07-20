#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);



void setup() {
Serial.begin(115200);
dht.begin();
Wire.begin(D2,D1);
// lcd init
lcd.begin();
lcd.home();
// lcd back light on
//lcd.backlight();
lcd.print("Test");
}

void loop() {
float temp = dht.readTemperature();
float humi = dht.readHumidity();
Serial.print("Temp: ");
Serial.print(temp);
Serial.print(" 습도: ");
Serial.println(humi);
// LCD Display
// LCD Cursor change to (0,0)
lcd.setCursor(0,0);
lcd.print("온도: ");
lcd.print(temp);
// LCD Cursor change to (0,1)
lcd.setCursor(0,1);
lcd.print("습도: ");
lcd.print(humi);
delay(300);
}
