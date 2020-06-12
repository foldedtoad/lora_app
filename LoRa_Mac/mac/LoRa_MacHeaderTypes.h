/*!
 * \file      LoRa_MacHeaderTypes.h
 *
 * \brief     LoRa MAC layer header type definitions
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \code
 *                ______                              _
 *               / _____)             _              | |
 *              ( (____  _____ ____ _| |_ _____  ____| |__
 *               \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 *               _____) ) ____| | | || |_| ____( (___| | | |
 *              (______/|_____)_|_|_| \__)_____)\____)_| |_|
 *              (C)2013 Semtech
 *
 *               ___ _____ _   ___ _  _____ ___  ___  ___ ___
 *              / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 *              \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 *              |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 *              embedded.connectivity.solutions===============
 *
 * \endcode
 *
 * \author    Miguel Luis ( Semtech )
 *
 * \author    Gregory Cristian ( Semtech )
 *
 * \author    Daniel Jaeckle ( STACKFORCE )
 *
 * \author    Johannes Bruder ( STACKFORCE )
 *
 * addtogroup LORA_MAC
 * \{
 *
 */
#ifndef __LORA_MAC_HEADER_TYPES_H__
#define __LORA_MAC_HEADER_TYPES_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

/*! Frame header (FHDR) maximum field size */
#define LORA_MAC_FHDR_MAX_FIELD_SIZE            22

/*! FHDR Device address field size */
#define LORA_MAC_FHDR_DEV_ADD_FIELD_SIZE         4

/*! FHDR Frame control field size */
#define LORA_MAC_FHDR_F_CTRL_FIELD_SIZE          1

/*! FHDR Frame control field size */
#define LORA_MAC_FHDR_F_CNT_FIELD_SIZE           2

/*! FOpts maximum field size */
#define LORA_MAC_FHDR_F_OPTS_MAX_FIELD_SIZE          15


/*!
 * LoRaMAC field definition of DLSettings
 *
 * LoRaWAN Specification V1.0.2, chapter 5.4
 */
typedef union uLoRa_MacDLSettings
{
    /*!
     * Byte-access to the bits
     */
    uint8_t Value;
    /*!
     * Structure containing single access to header bits
     */
    struct sDLSettingsBits
    {
        /*!
         * Data rate of a downlink using the second receive window
         */
        uint8_t RX2DataRate     : 4;
        /*!
         * Offset between up and downlink datarate of first reception slot
         */
        uint8_t RX1DRoffset     : 3;
        /*!
         * Indicates network server LoRaWAN implementation version 1.1 or later.
         */
        uint8_t OptNeg          : 1;
    }Bits;
}LoRa_MacDLSettings_t;

/*!
 * LoRaMAC header field definition (MHDR field)
 *
 * LoRaWAN Specification V1.0.2, chapter 4.2
 */
typedef union uLoRa_MacHeader
{
    /*!
     * Byte-access to the bits
     */
    uint8_t Value;
    /*!
     * Structure containing single access to header bits
     */
    struct sMacHeaderBits
    {
        /*!
         * Major version
         */
        uint8_t Major           : 2;
        /*!
         * RFU
         */
        uint8_t RFU             : 3;
        /*!
         * Message type
         */
        uint8_t MType           : 3;
    }Bits;
}LoRa_MacHeader_t;

/*!
 * LoRaMAC frame control field definition (FCtrl)
 *
 * LoRaWAN Specification V1.0.2, chapter 4.3.1
 */
typedef union uLoRa_MacFrameCtrl
{
    /*!
     * Byte-access to the bits
     */
    uint8_t Value;
    /*!
     * Structure containing single access to bits
     */
    struct sCtrlBits
    {
        /*!
         * Frame options length
         */
        uint8_t FOptsLen        : 4;
        /*!
         * Frame pending bit
         */
        uint8_t FPending        : 1;
        /*!
         * Message acknowledge bit
         */
        uint8_t Ack             : 1;
        /*!
         * ADR acknowledgment request bit
         */
        uint8_t AdrAckReq       : 1;
        /*!
         * ADR control in frame header
         */
        uint8_t Adr             : 1;
    }Bits;
}LoRa_MacFrameCtrl_t;

/*!
 * LoRa_Mac Frame header (FHDR)
 *
 * LoRaWAN Specification V1.0.2, chapter 4.3.1
 */
typedef struct sLoRa_MacFrameHeader
{
    /*!
     * Device address
     */
    uint32_t DevAddr;
    /*!
     * Frame control field
     */
    LoRa_MacFrameCtrl_t FCtrl;
    /*!
     * Frame counter
     */
    uint16_t FCnt;
    /*!
     * FOpts field may transport  MAC commands (opt. 0-15 Bytes)
     */
    uint8_t FOpts[LORA_MAC_FHDR_F_OPTS_MAX_FIELD_SIZE];
}LoRa_MacFrameHeader_t;

/*! \} addtogroup LORA_MAC */

#ifdef __cplusplus
}
#endif

#endif // __LORA_MAC_HEADER_TYPES_H__
