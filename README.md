# LoRa Application project
LoRa implementation on nRF52 (PCA10040) platform using Zephyr v2.2.0 RTOS and the Dragino Lora Shield 1.4. 

NOTES:
* Remove the jumpers from J_DIO1, J_DIO2 and J_DIO5, as they interfer with the LEDs on the PCA10040 board.
* Defeat the PCA10040 onboard LEDs and Buttons by grounding the DETECT pin on header P5.
* Don't run the SPI bus clock below 4MHz: system crashes due to unhandled BUSY errors from SPI controller.
