#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN0(10);     // Initialize CAN

int input[6][4] = {{10000, 40, 10, 50}, {0, 0, 5, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 500, 500, 0}};

void setup()
{
  Serial.begin(115200);
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) 
    Serial.println("MCP2515 Initialized Successfully!");
  else 
    Serial.println("Error Initializing MCP2515...");
}

void loop() {
  for(int packetNum = 0; packetNum < 6; packetNum++)
  {
    int packetHexNum = 0x0CFFF048 + (packetNum * 256);
    int highByte[4];
    int lowByte[4];
    for (int i = 0; i < 4; i++)
    {
      highByte[i] = input[packetNum][i] / 256; //rpm highByte, tps highByte, etc...
      lowByte[i] = input[packetNum][i] % 256; //rpm lowByte, tps lowByte, etc...
    }
    byte output[8]; //rpm lowByte, rpm highByte, etc...
    int c = 0; //new counter
    for (int i = 0; i < 4; i++)
    {
      output[c] = lowByte[i]; //fills even numbers of array with lowBytes
      output[c + 1] = highByte[i]; //fills odd numbers of arrays with highBytes
      c += 2;
    }
    byte sndStat = CAN0.sendMsgBuf(packetHexNum, 0, 8, output); //sends output
    if(sndStat == CAN_OK) //checks if it sends successfully
      Serial.println("Message Sent Successfully!");
    else
      Serial.println("Error Sending Message...");
  }
}
