void setup() {
  #define LED_PIN1 D1
  #define LED_PIN2 D2
  // put your setup code here, to run once:
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_PIN1, HIGH);
  delay(1000);
  digitalWrite(LED_PIN1, LOW);
  delay(1000);

  digitalWrite(LED_PIN2, HIGH);
  delay(1000);
  digitalWrite(LED_PIN2, LOW);
  delay(1000);
}
