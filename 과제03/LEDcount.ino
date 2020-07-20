#define LED1 D1 // Led in NodeMCU at pin GPIO16 (D0).
#define LED2 D2
#define LED3 D3

int count = 0;
bool direction = true;

void setup() {
pinMode(LED1, OUTPUT); // set the digital pin as output.
pinMode(LED2, OUTPUT);
pinMode(LED3, OUTPUT);
}

 void blinkLED(int ledPin, int delayTime){
    digitalWrite(ledPin, HIGH);
    delay(delayTime);          
    digitalWrite(ledPin, LOW); 
    delay(delayTime);
    count++;   
  }
  
void loop() {
  count = 0;
  if(direction){
    blinkLED(LED1, 500);  //1
    blinkLED(LED2, 500); //2
    blinkLED(LED3, 500); //3
    direction = false;  
  }
  if (!direction){
    blinkLED(LED2, 500); //2
    blinkLED(LED1, 500); //1
    direction = true;
  } 
  if (direction){ 
     blinkLED(LED2, 500); //2
     blinkLED(LED3, 500); //3
     direction = false;
  } else {
    blinkLED(LED1, 500); //2
    direction = true;
  }
  
}
