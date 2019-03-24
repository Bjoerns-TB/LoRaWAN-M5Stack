# LoRaWAN-M5Stack
LoRaWAN library for M5Stack LoRaWAN Module, based on the Seeeduino LoRaWAN library. This version works with The Things Network (TTN).

The lora.receivePacket function now also informs about the SNR.

The lora.transferPacketLinkCheckReq function uses the LinkCheckReq MAC command to inform about the number of LoRaWAN gateways which received the request.

A bug in the for loop within the lora.transferPacket functions which made the loop run endlessly was fixed.
Buffer overflow in sprintf() was fixed.

Used UART has to be configured in LoRaWan.cpp

ToDo:
- debug OTAA version example (First transfer is possible after about 150s cause join is done in SF12; maybee FW related)

