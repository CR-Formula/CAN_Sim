// CAN Send Example
//

#include <SPI.h>
#include <mcp_can.h>
#include <stdio.h>
#include <stdlib.h>

MCP_CAN CAN0(10); // Set CS to pin 10

void setup() {
  Serial.begin(115200);

  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the
  // masks and filters disabled.
  if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(
      MCP_NORMAL); // Change to normal mode to allow messages to be transmitted
}

byte data[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

void packet1(double rpm, double tps, double fuelOpenTime,
             double ignistionAngle) {

  data[0] = (rpm / 2) / 256;
  data[1] = (rpm / 2);
  data[2] = (tps / 2) / 256;
  data[3] = tps / 2;
  data[4] = (fuelOpenTime / 2) / 256;
  data[5] = fuelOpenTime / 2;
  data[6] = (ignistionAngle / 2) / 256;
  data[7] = ignistionAngle / 2;
}

void packet2(double lam) {
  data[0] = 0;
  data[1] = 0;
  data[2] = 0;
  data[3] = 0;
  data[4] = (lam / 2) / 256;
  data[5] = (lam / 2);
  data[6] = 0;
  data[7] = 0;
  data[8] = 0;
}

void packet6(double airT, double cT) {
  data[0] = 0;
  data[0] = 0;
  data[2] = (airT / 2) / 256;
  data[3] = airT / 2;
  data[4] = (cT / 2) / 256;
  data[5] = (cT / 2);
  data[0] = 0;
  data[0] = 0;
}

void SendData() {
  packet1(100.000, 28.0000, 25.0000, 15.0000);
  byte sndStat1 = CAN0.sendMsgBuf(0x0CFF048, 0, 8, data);
  packet2(63.3000);
  byte sndStat2 = CAN0.sendMsgBuf(0x0CFF148, 0, 8, data);
  packet6(56.74000, 71.68000);
  byte sndStat3 = CAN0.sendMsgBuf(0x0CFF548, 0, 8, data);

  if (sndStat1 == CAN_OK & sndStat2 == CAN_OK & sndStat3 == CAN_OK) {
    Serial.println("Messages Sent Successfully!");
  } else {
    Serial.println("Error Sending Message...");
  }
}

void loop() {

  SendData();
  delay(100); // send data per 100ms
}
