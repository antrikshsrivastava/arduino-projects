#include <SPI.h>
#include <avr/pgmspace.h>
#include "font.h"

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
    }
}  // end of showString

void setup () {
 
  SPI.begin ();
    
  sendByte (MAX7219_REG_SCANLIMIT, 7);   // show all 8 digits
  sendByte (MAX7219_REG_DECODEMODE, 0);  // using an led matrix (not digits)
  sendByte (MAX7219_REG_DISPLAYTEST, 0); // no display test
  
  // clear display
  for (byte col = 0; col < 8; col++)
    sendByte (col + 1, 0);

  sendByte (MAX7219_REG_INTENSITY, 13);  // character intensity: range: 0 to 15
  sendByte (MAX7219_REG_SHUTDOWN, 1);   // not in shutdown mode (ie. start it up)
                                        
}   // end of setup
 
void loop () 
 {
 showString ("***AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz..*", 100);
 }  // end of loop
