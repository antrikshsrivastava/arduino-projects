#include <Ultrasonic.h>
#include <SPI.h>
#include <Mirf.h>
#include <MirfHardwareSpiDriver.h>
#include <MirfSpiDriver.h>
#include <nRF24L01.h>

#define TRIGGER_PIN  5
#define ECHO_PIN     6

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

void setup() {
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();  
  Mirf.setRADDR((byte *)"serv1");
  Mirf.payload = sizeof(unsigned long);
  Mirf.config();
  Serial.println("Listening..");
}

void loop() {
  // Get distance from HRC-04 
  float cm;
  long microsec = ultrasonic.timing();
  cm = ultrasonic.convert(microsec, Ultrasonic::CM);
  //Serial.println("Sending..");
  //Serial.println(cm);
  Mirf.setTADDR((byte *)"serv1");
  long toSend = (long)(cm*100);
  //Serial.print("Int x100 = ");
  //Serial.println(toSend);
  Mirf.send((byte *)&toSend);
  while(Mirf.isSending()){
    Serial.print(".");
  }
  //Serial.println("Finished sending");
  delay(2000);
}
