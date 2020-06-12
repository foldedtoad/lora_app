/*!
 * \file      LoRa_MacSerializer.h
 *
 * \brief     LoRa MAC layer message serializer functionality implementation
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
#ifndef __LORA_MAC_SERIALIZER_H__
#define __LORA_MAC_SERIALIZER_H__

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
#include "LoRa_MacMessageTypes.h"


/*!
 * LoRa_Mac Serializer Status
 */
typedef enum eLoRa_MacSerializerStatus
{
    /*!
     * No error occurred
     */
    LORA_MAC_SERIALIZER_SUCCESS = 0,
    /*!
     * Null pointer exception
     */
    LORA_MAC_SERIALIZER_ERROR_NPE,
    /*!
     * Incompatible buffer size
     */
    LORA_MAC_SERIALIZER_ERROR_BUF_SIZE,
    /*!
     * Undefined Error occurred
     */
    LORA_MAC_SERIALIZER_ERROR,
}LoRa_MacSerializerStatus_t;

/*!
 * Creates serialized MAC message of structured object.
 *
 * \param[IN/OUT] macMsg        - Join-request message object
 * \retval                      - Status of the operation
 */
LoRa_MacSerializerStatus_t LoRa_MacSerializerJoinRequest( LoRa_MacMessageJoinRequest_t* macMsg );

/*!
 * Creates serialized MAC message of structured object.
 *
 * \param[IN/OUT] macMsg        - Join-request message object
 * \retval                      - Status of the operation
 */
LoRa_MacSerializerStatus_t LoRa_MacSerializerReJoinType1( LoRa_MacMessageReJoinType1_t* macMsg );

/*!
 * Creates serialized MAC message of structured object.
 *
 * \param[IN/OUT] macMsg        - Join-request message object
 * \retval                      - Status of the operation
 */
LoRa_MacSerializerStatus_t LoRa_MacSerializerReJoinType0or2( LoRa_MacMessageReJoinType0or2_t* macMsg );

/*!
 * Creates serialized MAC message of structured object.
 *
 * \param[IN/OUT] macMsg        - Data message object
 * \retval                      - Status of the operation
 */
LoRa_MacSerializerStatus_t LoRa_MacSerializerData( LoRa_MacMessageData_t* macMsg );

/*! \} addtogroup LORA_MAC */

#ifdef __cplusplus
}
#endif

#endif // __LORA_MAC_SERIALIZER_H__

