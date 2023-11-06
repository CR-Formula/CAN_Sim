#include <mcp_can.h>
#include <SPI.h>


// Sets INT to pin 2
#define CAN0_INT 2

// Sets CS
MCP_CAN CAN0(10); // Uno

byte data[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

void setup() {
  Serial.begin(115200);

  // Initializes MCP2515 running at 16MHz with a baudrate of 250kb/s and the masks and filters disabled.
  if (CAN0.begin(MCP_ANY, CAN_250KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted

  pinMode(CAN0_INT, INPUT);   // Configure the INT input pin
}

void loop() {
  if (CAN0.sendMsgBuf(0x100, 0, 8, &data) == CAN_OK) // Format CAN message with ID 100
    Serial.println("Message Sent Successfully!");
  else
    Serial.println("Error Sending Message...");
    delay(100);
    
  // Increment the data
  for (int i = 0 ; i < 8 ; i++)
    data[i] = data[i]++;
}
