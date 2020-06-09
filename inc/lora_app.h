/*
 *  lora_app.h
 */
#ifndef __LORA_APP_H__
#define __LORA_APP_H__

/*
 *   If LORA_APP_TX_MODE is defined then build for TX
 *   IF LORA_APP_TX_MODE is not defined (comment out) then build for RX.
 */
 //#define LORA_APP_TX_MODE 1

int  lora_app_init(void);
void lora_app_send(void);
void lora_app_receive(void);

#endif  // __LORA_APP_H__