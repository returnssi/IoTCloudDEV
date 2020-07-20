void setup() {
  #define LED_PIN1 D1
  #define LED_PIN2 D2
  #define LED_PIN3 D3
  
  // put your setup code here, to run once:
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(random(3)==0){
    digitalWrite(LED_PIN1, HIGH);
    delay(1000);
    digitalWrite(LED_PIN1, LOW);
    delay(1000);  
  } else if(random(3)==1){
   digitalWrite(LED_PIN2, HIGH);
   delay(1000);
   digitalWrite(LED_PIN2, LOW);
   delay(1000); 
  } else {
    0digitalWrite(LED_PIN3, HIGH);
   delay(1000);
   digitalWrite(LED_PIN3, LOW);
   delay(1000);  
  }
  

  

  
}
