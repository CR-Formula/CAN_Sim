#include <mcp_can.h>

void setup() {
  Serial.begin(115200);
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) 
    Serial.println("MCP2515 Initialized Successfully!");
  else 
    Serial.println("Error Initializing MCP2515...");
  int input_packet1[4] = {10000, 40, 10, 50};  //rpm, tps, fuel open time, ignition angle
  int input_packet2[4] = {0, 0, 5, 0};
  int input_packet3[4] = {0, 0, 0, 0};
  int input_packet4[4] = {0, 0, 0, 0};
  int input_packet5[4] = {0, 0, 0, 0};
  int input_packet6[4] = {0, 500, 500, 0};

  int input[6] = {input_packet1, input_packet2, input_packet3, input_packet4, input_packet5, input_packet6};
  for (int i = 0; i < 6; i++)
    loop(i, input[i]); //run function loop with each input of the array
}

void loop(int packetNum, int input) {
  long float packetHexNum = 0x0CFFF048 + (packetNum * 256);
  int highByte[4];
  int lowByte[4];
  for (int i = 0; i < 4; i++){
    highByte[i] = input[i] / 256; //rpm highByte, tps highByte, etc...
    lowByte[i] = input[i] % 256; //rpm lowByte, tps lowByte, etc...
  }
  int output[8]; //rpm lowByte, rpm highByte, etc...
  int c = 0; //new counter
  for (int i = 0; i < 4; i++){
    output[c] = lowByte[i]; //fills even numbers of array with lowBytes
    output[c + 1] = highByte[i]; //fills odd numbers of arrays with highBytes
    c + 2;
  }
  byte sndStat = CAN0.senMsgBuf(packetHexNum, 0, 8, output); //sends output
  if(sndStat == CAN_OK) //checks if it sends successfully
    Serial.println("Message Sent Successfully!");
  else
    Serial.println("Error Sending Message...");
}
