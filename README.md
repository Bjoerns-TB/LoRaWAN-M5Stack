# LoRaWAN-M5Stack
LoRaWAN library for M5Stack LoRaWAN Module, based on the Seeeduino LoRaWAN library. This version works with The Things Network (TTN).

The lora.receivePacket function now also informs about the SNR.

The lora.transferPacketLinkCheckReq function uses the LinkCheckReq MAC command to inform about the number of LoRaWAN gateways which received the request.

A bug in the for loop within the lora.transferPacket functions which madde the loop run endlessly was fixed.

ToDo:
- provide OTAA version example

