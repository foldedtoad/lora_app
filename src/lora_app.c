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

/*---------------------------------------------------------------------------*/
/*  Local reference taken from ./zephyr/include/drivers/lora.h               */
/*---------------------------------------------------------------------------*/
/*
        enum lora_signal_bandwidth {
            BW_125_KHZ = 0,
            BW_250_KHZ,
            BW_500_KHZ,
        };
        
        enum lora_datarate {
            SF_6 = 6,
            SF_7,
            SF_8,
            SF_9,
            SF_10,
            SF_11,
            SF_12,
        };
        
        enum lora_coding_rate {
            CR_4_5 = 1,
            CR_4_6 = 2,
            CR_4_7 = 3,
            CR_4_8 = 4,
        };
*/

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/

#define FROM_ID 1
#define TO_ID   2

#define MAX_SEND_DATA_LEN 16
char send_data[MAX_SEND_DATA_LEN] = {TO_ID, FROM_ID, 0, 0, 
               'h', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd'};

#define MAX_RECEIVE_DATA_LEN  255
char receive_data[MAX_RECEIVE_DATA_LEN] = {0};

static struct device * lora_dev;
static bool initialized = false;

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
int lora_app_init(void)
{
    struct lora_modem_config config;
    int ret;

    if (initialized) {
        return 0;
    }
    initialized = true;

    lora_dev = device_get_binding(DT_INST_0_SEMTECH_SX1276_LABEL);
    if (!lora_dev) {
        LOG_ERR("%s Device not found", DT_INST_0_SEMTECH_SX1276_LABEL);
        initialized = false;
        return -1;
    }

#if 0
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
    config.tx_power = 14;
    config.tx = true;               // true for TX, false for RX
#endif

    LOG_INF("%s mode ---------",   (config.tx) ? "TX" : "RX");
    LOG_INF("frequency:    %uHz", config.frequency);
    LOG_INF("bandwidth:    %u",   config.bandwidth);
    LOG_INF("datarate:     %u",   config.datarate);
    LOG_INF("preamble_len: %u",   config.preamble_len);
    LOG_INF("coding_rate:  %u",   config.coding_rate);
    LOG_INF("tx_power:     %u",   config.tx_power);

    ret = lora_config(lora_dev, &config);
    if (ret < 0) {
        LOG_ERR("LoRa config failed");
        initialized = false;
        return -1;
    }
    return 0;
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
void lora_app_receive( void )
{
    int   len;
    s16_t rssi;
    s8_t  snr;

    while (1) {
        /* Block until data arrives */
        LOG_INF("Receive posted...");
        len = lora_recv(lora_dev, receive_data, 
                        MAX_RECEIVE_DATA_LEN, K_FOREVER, &rssi, &snr);
        if (len < 0) {
            LOG_ERR("LoRa receive failed");
            return;
        }

        LOG_INF("Received data: %s (RSSI:%ddBm, SNR:%ddBm)",
                 receive_data, rssi, snr);
    }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
void lora_app_send( void )
{
    int ret;

    while (1) {

        k_sleep(5000);

        ret = lora_send(lora_dev, send_data, MAX_SEND_DATA_LEN);
        if (ret < 0) {
            LOG_ERR("LoRa send failed");
            return;
        }

        LOG_INF("Data sent!");
    }
}
