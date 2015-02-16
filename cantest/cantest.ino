// demo: CAN-BUS Shield, send data
#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN(10);                                      // Set CS to pin 10

void setup()
{
    Serial.begin(115200);

START_INIT:

    if(CAN_OK == CAN.begin(CAN_500KBPS))                   // init can bus : baudrate = 500k
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
    
    unsigned char startingPacket[4] = {100, 50, 255, 0};

    unsigned char maxTorquePacket[4] = {100, 0, 0, 0};

    CAN.sendMsgBuf(0x99, 0, 4, maxTorquePacket);
    CAN.sendMsgBuf(0x98, 0, 4, startingPacket); 
}

unsigned char stmp[4] = {0, 0, 0, 0};
void loop()
{
    // send data:  id = 0x00, standrad flame, data len = 8, stmp: data buf
    CAN.sendMsgBuf(0x96, 0, 4, stmp);
    delay(100);                       // send data per 100ms
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
