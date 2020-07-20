#define red_pin D1
#define yellow_pin D2
#define blue_pin D3

void setup() {

pinMode(red_pin, OUTPUT); // set the digital pin as output.
pinMode(yellow_pin, OUTPUT);
pinMode(blue_pin, OUTPUT);
Serial.begin(9600);
}
void loop() {
blinkLED(red_pin,500);
blinkLED(yellow_pin,500);
blinkLED(blue_pin,500);
}

void blinkLED(int pinNo, int delayTime)
{
  digitalWrite(pinNo, HIGH);
  delay(delayTime);
  digitalWrite(pinNo, LOW);
  delay(delayTime);
}
