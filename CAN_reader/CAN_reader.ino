// demo: CAN-BUS Shield, receive data with check mode
// send data coming to fast, such as less than 10ms, you can use this way
// loovee, 2014-6-13


#include <SPI.h>
#include "mcp_can.h"


unsigned char Flag_Recv = 0;
unsigned char len = 0;
unsigned char buf[8];
char str[20];


MCP_CAN CAN(10);                                            // Set CS to pin 10

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
}


void loop()
{
    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
      //Serial.print("MSG: ");
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf
        int ID = CAN.getCanId();
        Serial.print(ID);
        Serial.print("\t");
        Serial.print(buf[0]);
        Serial.print("\t");
        Serial.println(buf[1]);
        if (ID == 20000) {
          double acc = (buf[0] + buf[1] * 256 + 32768) % 65536 - 32768;
          //Serial.println(acc);
          int Xvel = buf[6];
          int Yvel = buf[7];
          Serial.print("X: ");
          if (Xvel > 128) Xvel = Xvel - 256;
          Serial.print((double)(Xvel) * 0.05);
          String temp = String(Xvel);
          for (int i = 0; i < 10 - temp.length(); i++) {
            Serial.print(" ");  
          }
          Serial.print("    Yvel: ");
          if (Yvel > 128) Yvel = Yvel - 256;          
          Serial.print((double)(Yvel) * 0.05);
          temp = String(Yvel);
          for (int i = 0; i < 10 - temp.length(); i++) {
            Serial.print(" ");  
          }
        }
        if (ID == 20100) {
          double height_1 = (double)(buf[6]);
          double height_2 = (double)(buf[7] & 0x0F);
          Serial.print("    Height: ");
          Serial.println((height_2) * 256 + height_1);// + height_2 * 256);
          // Serial.print("    sizeof int: ");
          //Serial.println(height_2);
        }
        for(int i = 0; i<len; i++)    // print the data
        {
          if (i == 0) {

          } else {
            //Serial.print(buf[i]); 
          }
          //Serial.print("\t"); 
        }
        //Serial.println();
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
