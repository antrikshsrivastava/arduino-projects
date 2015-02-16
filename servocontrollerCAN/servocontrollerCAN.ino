// demo: CAN-BUS Shield, send data
#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN(10);                                      // Set CS to pin 10

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int angle = 0;
//int angle = -37;
int offset = 0;
int ID = 120;

unsigned char startingPacket[4] = {50, 5, 2, 0};

unsigned char packet100[4] = {100, 50, 2, 0};
unsigned char packet1000[4] = {1000, 50, 2, 0};

unsigned char maxTorquePacket[4] = {100, 0, 0, 0};

void setup()
{
    Serial.begin(115200);
    inputString.reserve(200);
    Serial.println("Starting.. Make sure a newline is added to the end of each input line.");  
START_INIT:
  
    if(CAN_OK == CAN.begin(CAN_500KBPS))                   // init can bus : baudrate = 500k
    //if(CAN_OK == CAN.begin(CAN_125KBPS))                   // init can bus : baudrate = 125k
    {
        Serial.println("CAN BUS Shield init ok!");
    }
    else
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(100);
        goto START_INIT;
    }
    //Send max torque and PI constants
    CAN.sendMsgBuf(0x7A, 0, 4, maxTorquePacket);
    CAN.sendMsgBuf(0x7B, 0, 4, startingPacket); 
    CAN.sendMsgBuf(0x5C, 0, 4, maxTorquePacket);
    CAN.sendMsgBuf(0x5D, 0, 4, startingPacket); 
    CAN.sendMsgBuf(0x84, 0, 4, maxTorquePacket);
    CAN.sendMsgBuf(0x85, 0, 4, startingPacket); 
    CAN.sendMsgBuf(0x66, 0, 4, maxTorquePacket); 
    CAN.sendMsgBuf(0x67, 0, 4, startingPacket); 
    CAN.sendMsgBuf(0x8E, 0, 4, maxTorquePacket); 
    CAN.sendMsgBuf(0x8F, 0, 4, startingPacket);     
}

void loop()
{   
      // print the string when a newline arrives:
    if (stringComplete) {
      //Serial.println(inputString); 
      if (inputString.equals("o\n")) {
          Serial.println("Set P to 100");
          CAN.sendMsgBuf(0x5D, 0, 4, packet100);
          CAN.sendMsgBuf(0x85, 0, 4, packet100);
      } else if (inputString.equals("p\n")) {
          Serial.println("Set P to 1000");
          CAN.sendMsgBuf(0x5D, 0, 4, packet1000);  
          CAN.sendMsgBuf(0x85, 0, 4, packet1000);  
      } else {
        angle = inputString.toInt() - offset;
        Serial.println(angle);
        // clear the string:
      }
      inputString = "";
      stringComplete = false;
    }
    
    int16_t commandedAngle; // the angle as an integer expressed in tenths of a degree
    commandedAngle = angle * 10;

    uint8_t *angleBytes = reinterpret_cast<uint8_t*>(&commandedAngle);

    unsigned char stmp[4] = {angleBytes[0], angleBytes[1], 0, 0};
    //unsigned char stm[4] = {0, 0, 0, 0};
    // send data:  id = 0x00, standrad flame, data len = 8, stmp: data buf
    CAN.sendMsgBuf(0x78, 0, 4, stmp);
    CAN.sendMsgBuf(0x50, 0, 4, stmp);
    CAN.sendMsgBuf(0x82, 0, 4, stmp);
    CAN.sendMsgBuf(0x64, 0, 4, stmp);    
    CAN.sendMsgBuf(0x8C, 0, 4, stmp); 
    CAN.sendMsgBuf(0x5C, 0, 4, maxTorquePacket);
    CAN.sendMsgBuf(0x84, 0, 4, maxTorquePacket);
    
    delay(10);                       // send data per 100ms
}


/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
