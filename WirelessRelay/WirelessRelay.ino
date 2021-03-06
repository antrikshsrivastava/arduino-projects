/**
 * A Mirf example to test the latency between two Ardunio.
 *
 * Pins:
 * Hardware SPI:
 * MISO -> 12
 * MOSI -> 11
 * SCK -> 13
 *
 * Configurable:
 * CE -> 8
 * CSN -> 7
 *
 * Note: To see best case latency comment out all Serial.println
 * statements not displaying the result and load 
 * 'ping_server_interupt' on the server.
 */

#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

int LED = 10;

void setup(){
  Serial.begin(9600);
  /*
   * Setup pins / SPI.
   */

  /* To change CE / CSN Pins:
   * 
   * Mirf.csnPin = 9;
   * Mirf.cePin = 7;
   */
  /*
  Mirf.cePin = 7;
   Mirf.csnPin = 8;
   */
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();

  /*
   * Configure reciving address.
   */

  Mirf.setRADDR((byte *)"clie1");

  /*
   * Set the payload length to sizeof(unsigned long) the
   * return type of millis().
   *
   * NB: payload on client and server must be the same.
   */

  Mirf.payload = sizeof(unsigned long);

  /*
   * Write channel and payload config then power up reciver.
   */

  /*
   * To change channel:
   * 
   * Mirf.channel = 10;
   *
   * NB: Make sure channel is legal in your area.
   */

  Mirf.config();

  pinMode(LED, OUTPUT);
  Serial.println("Beginning ... "); 
}

void loop(){
  unsigned long data;
  Mirf.setTADDR((byte *)"serv1");
  while(!Mirf.dataReady()){
  }
  Serial.println("GOT DATA: "); 
  Mirf.getData((byte *) &data);
  float cm = data/100.0;
  Serial.println(cm);

  if (cm > 160) {
    digitalWrite(LED, HIGH);  
  } 
  else {
    digitalWrite(LED, LOW);  
  }
  delay(100);
} 





