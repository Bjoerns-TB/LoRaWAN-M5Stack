# LoRaWAN-M5Stack
LoRaWAN library for M5Stack LoRaWAN Module, based on the Seeeduino LoRaWAN library. This version works with The Things Network (TTN).

The lora.receivePacket function now also informs about the SNR.

    result = lora.transferPacketWithConfirmed(coords, sizeof(coords), 5);
    
    if (result == true) {
      Seriel.println("ACK OK");

      short length;
      short rssi;
      float snr;
      char charsnr[5];
      short gwcnt;

      memset(buffer, 0, 256);
      length = lora.receivePacket(buffer, 256, &rssi, &snr, &gwcnt);

      dtostrf(snr, 5, 1, charsnr);

      Seriel.println(rssi);
      Seriel.println(charsnr);

    } else {
      Seriel.println("Error");
    }

The lora.transferPacketLinkCheckReq function uses the LinkCheckReq MAC command to inform about the number of LoRaWAN gateways which received the request.

    result = lora.transferPacketLinkCheckReq(5);
    
    if (result == true) {
      Seriel.println("LCR OK");

      short length;
      short rssi;
      float snr;
      char charsnr[5];
      short gwcnt;

      memset(buffer, 0, 256);
      length = lora.receivePacket(buffer, 256, &rssi, &snr, &gwcnt);

      dtostrf(snr, 5, 1, charsnr);

      Seriel.println(rssi);
      Seriel.println(charsnr);
      Seriel.println(gwcnt);

    } else {
      Seriel.println("Error");
    }

A bug in the for loop within the lora.transferPacket functions which made the loop run endlessly was fixed.
Buffer overflow in sprintf() was fixed.

Used UART has to be configured in LoRaWan.cpp

The RHF76-052 with Firmware 2.1.19 performs the first JOIN with SF12, which will fail, an then switches to SF7.
