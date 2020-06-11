# LoRa Application project
LoRa implementation on nRF52 (PCA10040) platform using Zephyr v2.2.0 RTOS and the Dragino Lora Shield 1.4. 

## HARDWARE NOTES:
* Remove the jumpers from J_DIO1, J_DIO2 and J_DIO5, as they interfer with the LEDs on the PCA10040 board.
* Defeat the PCA10040 onboard LEDs and Buttons by grounding the DETECT pin on header P5.  

 ![Hardware setup](https://github.com/foldedtoad/lora_app/blob/master/docs/LoRa_Hardware.jpg)

## SOFTWARE NOTES:
* Don't run the SPI bus clock below 4MHz: system crashes due to unhandled BUSY errors from SPI controller.
* A custom board DTS (Device Tree Structure) was created: nrf52_pca10040_raw.dts.  
This new board profile cloned from the Zephyr-provided nrf52_pca10040.dts and modified to remove 
various defines which interferred with the operation of the LoRa shield.

## Building the Code
This code was developed on a MacBook-Pro with the Zephyr RTOS development environment installed. 
After cloning the project to you local development system, run the "./configure.sh" script in the project 
root directory to configure the build. Next navigate to the "build" directory and run "make".  

Currently the code can be run in either send-mode (TX) or receive-mode (RX). In the file lora_app.h, 
you will find the build-time parameter to select for TX or RX mode.  Note that TX and RX are mutually exclusive
modes of operation.

## Runtime Output
Below is an example of the TX output via the Zephyr's Log facility.

```
[00:00:00.221,557] <inf> sx1276: SX1276 Version:12 found
*** Booting Zephyr OS build zephyr-v2.2.0-294-g8b14807e5540  ***

[00:00:17.166,748] <inf> main: lora_send_thread
[00:00:17.166,778] <inf> lora_app: TX mode ---------
[00:00:17.166,778] <inf> lora_app: frequency:    915000000Hz
[00:00:17.166,778] <inf> lora_app: bandwidth:    0
[00:00:17.166,778] <inf> lora_app: datarate:     7
[00:00:17.166,778] <inf> lora_app: preamble_len: 8
[00:00:17.166,778] <inf> lora_app: coding_rate:  1
[00:00:17.166,809] <inf> lora_app: tx_power:     14
[00:00:17.166,870] <inf> main: main_thread
[00:00:22.170,104] <inf> lora_app: Data sent!
[00:00:27.172,149] <inf> lora_app: Data sent!
[00:00:32.174,194] <inf> lora_app: Data sent!
[00:00:37.176,239] <inf> lora_app: Data sent!
[00:00:42.178,283] <inf> lora_app: Data sent!
[00:00:47.180,328] <inf> lora_app: Data sent!
[00:00:52.182,373] <inf> lora_app: Data sent!
[00:00:57.184,417] <inf> lora_app: Data sent!
[00:01:02.186,462] <inf> lora_app: Data sent!
```

Below is an example of the RX output via the Zephyr's Log facility.  
The sending host was a RaspberryPi running RadioHead for the RF95 (rf95_client)

```
[00:00:00.221,588] <inf> sx1276: SX1276 Version:12 found
*** Booting Zephyr OS build zephyr-v2.2.0-294-g8b14807e5540  ***

[00:00:03.397,338] <inf> main: lora_receive_thread
[00:00:03.397,338] <inf> lora_app: RX mode ---------
[00:00:03.397,338] <inf> lora_app: frequency:    915000000Hz
[00:00:03.397,338] <inf> lora_app: bandwidth:    0
[00:00:03.397,338] <inf> lora_app: datarate:     7
[00:00:03.397,338] <inf> lora_app: preamble_len: 8
[00:00:03.397,369] <inf> lora_app: coding_rate:  1
[00:00:03.397,369] <inf> lora_app: tx_power:     14
[00:00:03.397,430] <inf> main: main_thread
[00:00:03.398,559] <inf> lora_app: Receive posted...
[00:00:06.132,720] <inf> lora_app: Received data
48 69 20 52 61 73 70 69  21 00                   |Hi Raspi !.      
[00:00:06.132,751] <inf> lora_app: Receive posted...
[00:00:11.137,969] <inf> lora_app: Received data
48 69 20 52 61 73 70 69  21 00                   |Hi Raspi !.      
[00:00:11.137,969] <inf> lora_app: Receive posted...
[00:00:16.143,310] <inf> lora_app: Received data
48 69 20 52 61 73 70 69  21 00                   |Hi Raspi !.      
[00:00:16.143,341] <inf> lora_app: Receive posted...
[00:00:21.148,590] <inf> lora_app: Received data
48 69 20 52 61 73 70 69  21 00                   |Hi Raspi !.      
[00:00:21.148,620] <inf> lora_app: Receive posted...
```

