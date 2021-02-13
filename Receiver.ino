#include <SPI.h>
#include <LoRa.h>

#define ss 5
#define rst 0
#define dio0 4

byte localAddress = 0xFF;
int recipient;
String incoming;
byte sender;
byte incomingMsgId;
byte incomingLength;
byte Latitude;
byte Longitude;
byte Course;
byte Speed;

void setup() {
  Serial.begin(9600);
  Serial.println("LoRa Receiver");
  LoRa.setPins(ss, rst, dio0);  
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize == 0) return;
  recipient = LoRa.read();
  sender = LoRa.read();
  incomingMsgId = LoRa.read();
  incomingLength = LoRa.read();
  Latitude = LoRa.read();
  Longitude = LoRa.read();
  Course = LoRa.read();
  Speed = LoRa.read();
  incoming = String(Latitude) + String(Longitude) + String(Course) + String(Speed);
  if (incomingLength != incoming.length()) {
    Serial.println("error: message length does not match length");
    return;
  }
  if (recipient != localAddress) {
    Serial.println("This message is not for me.");
    return;
  }
  Serial.println("********************************************");
  Serial.println("Received from: 0x" + String(sender, HEX));
  Serial.println("Sent to: 0x" + String(recipient, HEX));
  Serial.println("Message ID: " + String(incomingMsgId));
  Serial.println("Message length: " + String(incomingLength));
  Serial.println("Latitude: " + String(Latitude));
  Serial.println("Longitude: " + String(Longitude));
  Serial.println("Course: " + String(Course));
  Serial.println("Speed: " + String(Speed));
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println("");
}
