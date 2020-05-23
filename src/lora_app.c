/*
 *  Copyright (c) 2020  Callender-Consulting
 *
 *  SPDX-License-Identifier: Apache-2.0
 */

#include <device.h>
#include <drivers/lora.h>
#include <errno.h>
#include <sys/util.h>
#include <zephyr.h>

#include "lora_app.h"

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(lora_app);

#if 1
#define MAX_DATA_LEN 10
char data[MAX_DATA_LEN] = {'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd'};
#else
#define MAX_DATA_LEN 16
#define FROM_ID 1
#define TO_ID   2
char data[MAX_DATA_LEN] = {TO_ID, FROM_ID, 0, 0, 
                  'h', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd'};
#endif

static struct device * lora_dev;

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
int lora_app_init(void)
{
    struct lora_modem_config config;
    int ret;

    lora_dev = device_get_binding(DT_INST_0_SEMTECH_SX1276_LABEL);
    if (!lora_dev) {
        LOG_ERR("%s Device not found", DT_INST_0_SEMTECH_SX1276_LABEL);
        return -1;
    }

#if 1
    config.frequency = 904300000; // FIXME make this a parameter.
    config.bandwidth = BW_125_KHZ;
    config.datarate = SF_7;
    config.preamble_len = 8;
    config.coding_rate = CR_4_5;
    config.tx_power = 21;
    config.tx = true;
#else
    config.frequency = 915000000;    // FIXME make this a parameter.
    config.bandwidth = BW_125_KHZ;
    config.datarate = SF_7;
    config.preamble_len = 8;
    config.coding_rate = CR_4_5;
    config.tx_power = 4;
    config.tx = true;
#endif

    ret = lora_config(lora_dev, &config);
    if (ret < 0) {
        LOG_ERR("LoRa config failed");
        return 0;
    }
    return 0;
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
void lora_app_send( void )
{
    int ret;

    while (1) {

        k_sleep(1000);

        ret = lora_send(lora_dev, data, MAX_DATA_LEN);
        if (ret < 0) {
            LOG_ERR("LoRa send failed");
            return;
        }

        LOG_INF("Data sent!");
    }
}
