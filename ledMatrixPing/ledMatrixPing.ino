#include <SPI.h>
#include <avr/pgmspace.h>
#include "font.h"

#include <NewPing.h>

#define TRIGGER_PIN  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     6  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

//const byte SS = 10;  // omit this line for Arduino 1.0 onwards

 // define max7219 registers
const byte MAX7219_REG_NOOP        = 0x0;
const byte MAX7219_REG_DIGIT0      = 0x1;
const byte MAX7219_REG_DIGIT1      = 0x2;
const byte MAX7219_REG_DIGIT2      = 0x3;
const byte MAX7219_REG_DIGIT3      = 0x4;
const byte MAX7219_REG_DIGIT4      = 0x5;
const byte MAX7219_REG_DIGIT5      = 0x6;
const byte MAX7219_REG_DIGIT6      = 0x7;
const byte MAX7219_REG_DIGIT7      = 0x8;
const byte MAX7219_REG_DECODEMODE  = 0x9;
const byte MAX7219_REG_INTENSITY   = 0xA;
const byte MAX7219_REG_SCANLIMIT   = 0xB;
const byte MAX7219_REG_SHUTDOWN    = 0xC;
const byte MAX7219_REG_DISPLAYTEST = 0xF;
 

void sendByte (const byte reg, const byte data)
  {    
  digitalWrite (SS, LOW);
  SPI.transfer (reg);
  SPI.transfer (data);
  digitalWrite (SS, HIGH); 
  }  // end of sendByte
 
 
void letter (const byte c)
 {
  for (byte col = 0; col < 8; col++)
    sendByte (col + 1, pgm_read_byte (&cp437_font [c] [col]));
 }  // end of letter
 
void showString (const char * s, const unsigned long time)
{
  char c;
  while (c = *s++)
    {
    letter (c); 
    delay (time);
    letter (' ');  // brief gap between letters
    delay (10);  
    unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
    Serial.print("Ping: ");
    Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    Serial.println("cm");    
    }
}  // end of showString

void setup () {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.

  SPI.begin ();
    
  sendByte (MAX7219_REG_SCANLIMIT, 7);   // show all 8 digits
  sendByte (MAX7219_REG_DECODEMODE, 0);  // using an led matrix (not digits)
  sendByte (MAX7219_REG_DISPLAYTEST, 0); // no display test
  
  // clear display
  for (byte col = 0; col < 8; col++)
    sendByte (col + 1, 0);

  sendByte (MAX7219_REG_INTENSITY, 7);  // character intensity: range: 0 to 15
  sendByte (MAX7219_REG_SHUTDOWN, 1);   // not in shutdown mode (ie. start it up)
                                        
}   // end of setup
 
void loop () 
 {
    delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
    Serial.print("Ping: ");
    Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    Serial.println("cm");   
   showString ("AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz..", 500);
 }  // end of loop
