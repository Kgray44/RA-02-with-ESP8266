#include <SPI.h>
#include <LoRa.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define ss 5
#define rst 0
#define dio0 4

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 4800;

TinyGPSPlus gps;
SoftwareSerial gpsSerial(RXPin, TXPin);

byte msgCount = 0;
byte Latitude;
byte Longitude;
byte Speed;
byte Course;
byte localAddress = 0xBB;
byte destination = 0xFF;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(GPSBaud);
  Serial.println("LoRa Sender");
  LoRa.setPins(ss, rst, dio0);  
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(msgCount);

  Latitude = gps.location.lat();
  Longitude = gps.location.lng();
  Course = gps.course.deg();
  Speed = gps.speed.mph();
  String outgoing = String(Latitude) + String(Longitude) + String(Course) + String(Speed);
  // send packet
  LoRa.beginPacket();
  LoRa.write(destination);
  LoRa.write(localAddress);
  LoRa.write(msgCount);
  LoRa.write(outgoing.length());
  LoRa.write(Latitude);
  LoRa.write(Longitude);
  LoRa.write(Course);
  LoRa.write(Speed);
  LoRa.endPacket();
  msgCount++;
  delay(4000);
}
