/*!
 * \file      LoRa_MacParser.h
 *
 * \brief     LoRa MAC layer message parser functionality implementation
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
#ifndef __LORA_MAC_PARSER_H__
#define __LORA_MAC_PARSER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "LoRa_MacMessageTypes.h"

/*!
 * LoRa_Mac Parser Status
 */
typedef enum eLoRa_MacParserStatus
{
    /*!
     * No error occurred
     */
    LORA_MAC_PARSER_SUCCESS = 0,
    /*!
     * Failure during parsing occurred
     */
    LORA_MAC_PARSER_FAIL,
    /*!
     * Null pointer exception
     */
    LORA_MAC_PARSER_ERROR_NPE,
    /*!
     * Undefined Error occurred
     */
    LORA_MAC_PARSER_ERROR,
}LoRa_MacParserStatus_t;


/*!
 * Parse a serialized join-accept message and fills the structured object.
 *
 * \param[IN/OUT] macMsg       - Join-accept message object
 * \retval                     - Status of the operation
 */
LoRa_MacParserStatus_t LoRa_MacParserJoinAccept( LoRa_MacMessageJoinAccept_t *macMsg );

/*!
 * Parse a serialized data message and fills the structured object.
 *
 * \param[IN/OUT] macMsg       - Data message object
 * \retval                     - Status of the operation
 */
LoRa_MacParserStatus_t LoRa_MacParserData( LoRa_MacMessageData_t *macMsg );

/*! \} addtogroup LORA_MAC */

#ifdef __cplusplus
}
#endif

#endif // __LORA_MAC_PARSER_H__

