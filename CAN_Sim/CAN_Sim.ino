#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN0(10);     // Initialize CAN


void setup()
{
  Serial.begin(115200);
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) 
    Serial.println("MCP2515 Initialized Successfully!");
  else 
    Serial.println("Error Initializing MCP2515...");
}
byte data[8];

void packet1(double rpm, double tps, double fuelOpenTime, double ignistionAngle) {

  data[0] = rpm % 256;
  data[1] = rpm / 256;
  data[2] = tps % 256;
  data[3] = tps / 256;
  data[4] = fuelOpenTime % 256;
  data[5] = fuelOpenTime / 256;
  data[6] = ignistionAngle % 256;
  data[7] = ignistionAngle / 256;
  for(int i = 0; i < 8; i++ ){
    Serial.println(data[i]);
  }
}

void packet2(double lam) {
  data[0] = 0;
  data[1] = 0;
  data[2] = 0;
  data[3] = 0;
  data[4] = lam % 256;
  data[5] = lam /  256;
  data[6] = 0;
  data[7] = 0;
}

void packet3() {}

void packet4() {}

void packet5() {}

void packet6(double airT, double cT) {
  data[0] = 0;
  data[0] = 0;
  data[2] = airT % 256;
  data[3] = airT / 256;
  data[4] = cT %256;
  data[5] = cT / 256;
  data[0] = 0;
  data[0] = 0;
}

void packet7() {}

void sendMsgs() {
  packet1(10000, 28.0000, 25.0000, 15.0000);
    byte sndStat1 = CAN0.sendMsgBuf(0x0CFF048, 0, 8, data);
    packet2(63.3000);
    byte sndStat2 = CAN0.sendMsgBuf(0x0CFF148, 0, 8, data);
    packet6(56.74000, 71.68000);
    byte sndStat3 = CAN0.sendMsgBuf(0x0CFF548, 0, 8, data);
    if(sndStat1 == CAN_OK & sndStat2 == CAN_OK & sndStat3 == CAN_OK) //checks if it sends successfully
      Serial.println("Message Sent Successfully!");
    else
      Serial.println("Error Sending Message...");
}

void loop() {
    sendMsgs();
    delay(100);
  }
