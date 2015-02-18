#include <Wire.h>

#define LED_PIN 13
#define LED_1 12
#define LED_2 11

int x;

void setup() {
  Wire.begin(9);                // Start I2C Bus as a Slave (Device Number 9)
  Wire.onReceive(receiveEvent); // register event
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  
  digitalWrite(LED_PIN, LOW);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  Serial.begin(9600);
  //x = 0;
}

void loop() {
  //Serial.println(x);
  //If value received is 0 blink LED 1
  if (x == 0) {
    digitalWrite(LED_1, HIGH);
    delay(200);
    digitalWrite(LED_1, LOW);
    delay(200);
    //Serial.println("X was 0");
    Serial.println(x);    
  }
  //If value received is 1 blink LED 2
  if (x == 1) {
    digitalWrite(LED_2, HIGH);
    delay(200);
    digitalWrite(LED_2, LOW);
    delay(200);
//    Serial.println("X was 1");    
    Serial.println(x);

  }
  if (x == 2) {
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_1, HIGH);    
    delay(200);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_1, LOW);    
    delay(200);      
  //  Serial.println("X was 2");    
    Serial.println(x);
  
  } else {
     //delay(400);
     //Serial.println(x); 
  }
  //Serial.println(x); 
  
}

void receiveEvent(int howMany) {
  x = Wire.read();    // receive byte as an integer
}

