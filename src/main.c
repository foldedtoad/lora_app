/* 
 *  main.c - Application main entry point 
 */
#include <zephyr.h>
#include <sys/printk.h>

#include "buttons.h"
#include "event.h"

#include <logging/log.h>
LOG_MODULE_REGISTER(main, 3);

#define STACKSIZE 1024
#define PRIORITY 7

int LoRa_init( void );

#ifdef CONFIG_BT
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
#include "ble_policy.h"
#include "ble_base.h"

void bluetooth_thread(void * id, void * unused1, void * unused2)
{
    LOG_INF("%s", __func__);

    ble_policy_init();

    while(1) { /* spin */}
}

K_THREAD_DEFINE(bluetooth_id, STACKSIZE, bluetooth_thread, 
                NULL, NULL, NULL, PRIORITY, 0, K_NO_WAIT);
#endif

#ifdef CONFIG_LORA
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
#include "lora_app.h"

void lora_thread(void * id, void * unused1, void * unused2)
{
    LOG_INF("%s", __func__);

    if (lora_app_init() == 0) {
        lora_app_send();  // never returns
    }
}

K_THREAD_DEFINE(lora_id, STACKSIZE, lora_thread, 
                NULL, NULL, NULL, PRIORITY, 0, K_NO_WAIT);
#endif

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
void main_thread(void * id, void * unused1, void * unused2)
{
    LOG_INF("%s", __func__);

    buttons_init();
    event_init();

    k_sleep( K_MSEC(500));

   ble_start_advertising();
}

K_THREAD_DEFINE(main_id, STACKSIZE, main_thread, 
                NULL, NULL, NULL, PRIORITY, 0, K_NO_WAIT);
