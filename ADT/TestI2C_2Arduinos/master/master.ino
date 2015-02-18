#include <Wire.h>

#define LED_PIN 13
#define LED_1 12
#define LED_2 11

byte x = 0;

void setup()
{
  Wire.begin(); // Start I2C Bus as Master
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(9600);
}
void loop()
{
  Wire.beginTransmission(9); // transmit to device #9
  Serial.println(x);
  Wire.write(x);   // sends x 
  Wire.endTransmission();    // stop transmitting
  x++;
  if (x > 5) x=0;
  delay(450);
 
}

