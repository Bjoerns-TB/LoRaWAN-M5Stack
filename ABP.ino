#include <M5Stack.h>
#include "LoRaWan.h"

//LoRa 
char buffer[256];
//unsigned char payload[9];
long sentMillis = 0;
long currentMillis = 0;
long interval = 15000;
byte payload[];

void setup() {
 /* Prepare M5STACK */
 M5.begin();

 initlora();

 Serial.println("Started");
}

void loop() { 

  currentMillis = millis();
  if(currentMillis - sentMillis > interval) {  
    sendobject();      
        }
  
  M5.update();
}

void initlora(){
  
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

void sendobject(){
  bool result = false;

  sentMillis = millis();

    Serial.println("Sending");

    result = lora.transferPacket("Hello World!", 5);
    //result = lora.transferPacket(payload, sizeof(payload), 5);
    
    if (result == true){
      Serial.println("Sent");
      
      short length;
      short rssi;
      float snr;
      short gwcnt;

      memset(buffer, 0, 256);
      length = lora.receivePacket(buffer, 256, &rssi, &snr, &gwcnt);

      Serial.print("Length is: ");
      Serial.println(length);
      Serial.print("RSSI is: ");
      Serial.println(rssi);
      Serial.print("SNR is: ");
      Serial.println(snr);
      Serial.print("Data is: ");
      for(unsigned char i = 0; i < length; i ++)
            {
                Serial.print("0x");
                Serial.print(buffer[i], HEX);
                Serial.print(" ");
            }
      Serial.println();

      
    }else {
      Serial.println("Error");
    }
  }
    
