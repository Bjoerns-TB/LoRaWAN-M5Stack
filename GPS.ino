

#include <M5Stack.h>
#include <TinyGPS++.h>
#include "LoRaWan.h"

//LoRa
char buffer[256];
//unsigned char payload[9];
long sentMillis = 0;
long currentMillis = 0;
long interval = 15000;
byte coords[9];

//GPS
//static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
HardwareSerial serialgps(2);
float latitude, longitude, hdop, alt, hdop2;

void setup() {
  /* Prepare M5STACK */
  M5.begin();
  serialgps.begin(9600, SERIAL_8N1, 16, 17);
  initlora();
  smartDelay(1000);
  Serial.println("Started");
}

void loop() {

  currentMillis = millis();
  if (currentMillis - sentMillis > interval) {
    sendobject();
  }
  smartDelay(1000);
  M5.update();
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (serialgps.available())
      gps.encode(serialgps.read());
  } while (millis() - start < ms);
}

void initlora() {

  lora.init();

  delay(1000);

  memset(buffer, 0, 256);
  lora.getVersion(buffer, 256, 1);
  Serial.print(buffer);

  memset(buffer, 0, 256);
  lora.getId(buffer, 256, 1);
  Serial.print(buffer);

  // void setId(char *DevAddr, char *DevEUI, char *AppEUI);
  lora.setId("12345678", NULL, NULL);
  // setKey(char *NwkSKey, char *AppSKey, char *AppKey);
  lora.setKey("12345678901234567890", "12345678901234567890", NULL);

  lora.setDeciveMode(LWABP);
  lora.setDataRate(DR5, EU868);

  lora.setChannel(0, 868.1);
  lora.setChannel(1, 868.3);
  lora.setChannel(2, 868.5);
  //  lora.setChannel(3, 867.1);
  //  lora.setChannel(4, 867.3);
  //  lora.setChannel(5, 867.5);
  //  lora.setChannel(6, 867.7);
  //  lora.setChannel(7, 867.9);

  lora.setReceiceWindowFirst(0, 868.1);
  lora.setReceiceWindowSecond(869.525, DR3);

  lora.setPower(14);
  lora.setPort(1);
  lora.setAdaptiveDataRate(false);
}

void gpsdata() {
  latitude = gps.location.lat();
  longitude = gps.location.lng();
  alt = gps.altitude.meters();
  hdop = gps.hdop.value();
}

void sendobject() {
  bool result = false;

  gpsdata();

  int32_t lat = latitude * 10000;
  int32_t lon = longitude * 10000;
  int16_t altitude = alt * 100;
  int8_t hdopGPS = hdop / 10;

  coords[0] = lat;
  coords[1] = lat >> 8;
  coords[2] = lat >> 16;

  coords[3] = lon;
  coords[4] = lon >> 8;
  coords[5] = lon >> 16;

  coords[6] = altitude;
  coords[7] = altitude >> 8;

  coords[8] = hdopGPS;


  sentMillis = millis();

  Serial.println("Sending");

  result = lora.transferPacket(coords, sizeof(coords), 5);

  if (result == true) {
    Serial.println("Sent");

  } else {
    Serial.println("Error");
  }
}

