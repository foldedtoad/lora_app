/*!
 * \file      LoRa_MacMessageTypes.h
 *
 * \brief     LoRa MAC layer message type definitions
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
#ifndef __LORA_MAC_MESSAGE_TYPES_H__
#define __LORA_MAC_MESSAGE_TYPES_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "LoRa_MacHeaderTypes.h"


/*! MAC header field size */
#define LORA_MAC_MHDR_FIELD_SIZE             1

/*! Join EUI field size */
#define LORA_MAC_JOIN_EUI_FIELD_SIZE         8

/*! Device EUI field size */
#define LORA_MAC_DEV_EUI_FIELD_SIZE          8

/*! Join-server nonce field size */
#define LORA_MAC_JOIN_NONCE_FIELD_SIZE        3

/*! Network ID field size */
#define LORA_MAC_NET_ID_FIELD_SIZE           3

/*! Port field size */
#define LORA_MAC_F_PORT_FIELD_SIZE           1

/*! CFList field size */
#define LORA_MAC_C_FLIST_FIELD_SIZE          16

/*! MIC field size */
#define LORA_MAC_MIC_FIELD_SIZE              4

/*! Join-request message size */
#define LORA_MAC_JOIN_REQ_MSG_SIZE           23

/*! ReJoin-request type 1 message size */
#define LORA_MAC_RE_JOIN_1_MSG_SIZE          24

/*! ReJoin-request type 0 or 2 message size */
#define LORA_MAC_RE_JOIN_0_2_MSG_SIZE        19

/*!
 * LoRa_Mac type for Join-request message
 */
typedef struct sLoRa_MacMessageJoinRequest
{
    /*!
     * Serialized message buffer
     */
    uint8_t* Buffer;
    /*!
     * Size of serialized message buffer
     */
    uint8_t BufSize;
    /*!
     * MAC header
     */
    LoRa_MacHeader_t MHDR;
    /*!
     *  Join EUI
     */
    uint8_t JoinEUI[LORA_MAC_JOIN_EUI_FIELD_SIZE];
    /*!
     * Device EUI
     */
    uint8_t DevEUI[LORA_MAC_DEV_EUI_FIELD_SIZE];
    /*!
     * Device Nonce
     */
    uint16_t DevNonce;
    /*!
     * Message integrity code (MIC)
     */
    uint32_t MIC;
}LoRa_MacMessageJoinRequest_t;

/*!
 * LoRa_Mac type for rejoin-request type 1 message
 */
typedef struct sLoRa_MacMessageReJoinType1
{
    /*!
     * Serialized message buffer
     */
    uint8_t* Buffer;
    /*!
     * Size of serialized message buffer
     */
    uint8_t BufSize;
    /*!
     * MAC header
     */
    LoRa_MacHeader_t MHDR;
    /*!
     * Rejoin-request type ( 1 )
     */
    uint8_t ReJoinType;
    /*!
     *  Join EUI
     */
    uint8_t JoinEUI[LORA_MAC_JOIN_EUI_FIELD_SIZE];
    /*!
     * Device EUI
     */
    uint8_t DevEUI[LORA_MAC_DEV_EUI_FIELD_SIZE];
    /*!
     * ReJoin Type 1 counter
     */
    uint16_t RJcount1;
    /*!
     * Message integrity code (MIC)
     */
    uint32_t MIC;
}LoRa_MacMessageReJoinType1_t;

/*!
 * LoRa_Mac type for rejoin-request type 0 or 2 message
 */
typedef struct sLoRa_MacMessageReJoinType0or2
{
    /*!
     * Serialized message buffer
     */
    uint8_t* Buffer;
    /*!
     * Size of serialized message buffer
     */
    uint8_t BufSize;
    /*!
     * MAC header
     */
    LoRa_MacHeader_t MHDR;
    /*!
     * Rejoin-request type ( 0 or 2 )
     */
    uint8_t ReJoinType;
    /*!
     * Network ID ( 3 bytes )
     */
    uint8_t NetID[LORA_MAC_NET_ID_FIELD_SIZE];
    /*!
     * Device EUI
     */
    uint8_t DevEUI[LORA_MAC_DEV_EUI_FIELD_SIZE];
    /*!
     * ReJoin Type 0 and 2 frame counter
     */
    uint16_t RJcount0;
    /*!
     * Message integrity code (MIC)
     */
    uint32_t MIC;
}LoRa_MacMessageReJoinType0or2_t;

/*!
 * LoRa_Mac type for Join-accept message
 */
typedef struct sLoRa_MacMessageJoinAccept
{
    /*!
     * Serialized message buffer
     */
    uint8_t* Buffer;
    /*!
     * Size of serialized message buffer
     */
    uint8_t BufSize;
    /*!
     * MAC header
     */
    LoRa_MacHeader_t MHDR;
    /*!
     *  Server Nonce ( 3 bytes )
     */
    uint8_t JoinNonce[LORA_MAC_JOIN_NONCE_FIELD_SIZE];
    /*!
     * Network ID ( 3 bytes )
     */
    uint8_t NetID[LORA_MAC_NET_ID_FIELD_SIZE];
    /*!
     * Device address
     */
    uint32_t DevAddr;
    /*!
     * Device address
     */
    LoRa_MacDLSettings_t DLSettings;
    /*!
     * Delay between TX and RX
     */
    uint8_t RxDelay;
    /*!
     * List of channel frequencies (opt.)
     */
    uint8_t CFList[16];
    /*!
     * Message integrity code (MIC)
     */
    uint32_t MIC;
}LoRa_MacMessageJoinAccept_t;


/*!
 * LoRa_Mac type for Data MAC messages
 * (Unconfirmed Data Up, Confirmed Data Up, Unconfirmed Data Down, Confirmed Data Down)
 */
typedef struct sLoRa_MacMessageData
{
    /*!
     * Serialized message buffer
     */
    uint8_t* Buffer;
    /*!
     * Size of serialized message buffer
     */
    uint8_t BufSize;
    /*!
     * MAC header
     */
    LoRa_MacHeader_t MHDR;
    /*!
     * Frame header (FHDR)
     */
    LoRa_MacFrameHeader_t FHDR;
    /*!
     * Port field (opt.)
     */
    uint8_t FPort;
    /*!
     * Frame payload may contain MAC commands or data (opt.)
     */
    uint8_t* FRMPayload;
    /*!
     * Size of frame payload (not included in LoRa_Mac messages) 
     */
    uint8_t FRMPayloadSize;
    /*!
     * Message integrity code (MIC)
     */
    uint32_t MIC;
}LoRa_MacMessageData_t;

/*!
 * LoRa_Mac message type enumerator
 */
typedef enum eLoRa_MacMessageType
{
    /*!
     * Join-request message
     */
    LORA_MAC_MSG_TYPE_JOIN_REQUEST,
    /*!
     * Rejoin-request type 1 message
     */
    LORA_MAC_MSG_TYPE_RE_JOIN_1,
    /*!
     * Rejoin-request type 1 message
     */
    LORA_MAC_MSG_TYPE_RE_JOIN_0_2,
    /*!
     * Join-accept message
     */
    LORA_MAC_MSG_TYPE_JOIN_ACCEPT,
    /*!
     * Data MAC messages
     */
    LORA_MAC_MSG_TYPE_DATA,
    /*!
     * Undefined message type
     */
    LORA_MAC_MSG_TYPE_UNDEF,
}LoRa_MacMessageType_t;

/*!
 * LoRa_Mac general message type
 */
typedef struct sLoRa_MacMessage
{
    LoRa_MacMessageType_t Type;
    union uMessage
    {
        LoRa_MacMessageJoinRequest_t JoinReq;
        LoRa_MacMessageReJoinType1_t ReJoin1;
        LoRa_MacMessageReJoinType0or2_t ReJoin0or2;
        LoRa_MacMessageJoinAccept_t JoinAccept;
        LoRa_MacMessageData_t Data;
    }Message;
}LoRa_MacMessage_t;

/*! \} addtogroup LORA_MAC */

#ifdef __cplusplus
}
#endif

#endif // __LORA_MAC_MESSAGE_TYPES_H__
