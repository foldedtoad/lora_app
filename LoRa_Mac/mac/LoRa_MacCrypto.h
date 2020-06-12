/*!
 * \file      LoRa_MacCrypto.h
 *
 * \brief     LoRa MAC layer cryptographic functionality implementation
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
 *              (C)2013-2017 Semtech
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
#ifndef __LORA_MAC_CRYPTO_H__
#define __LORA_MAC_CRYPTO_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "utilities.h"
#include "LoRa_MacTypes.h"
#include "LoRa_MacMessageTypes.h"

/*
 * Initial value of the frame counters
 */
#define FCNT_DOWN_INITAL_VALUE          0xFFFFFFFF

/*!
 * LoRa_Mac Cryto Status
 */
typedef enum eLoRa_MacCryptoStatus
{
    /*!
     * No error occurred
     */
    LORA_MAC_CRYPTO_SUCCESS = 0,
    /*!
     * MIC does not match
     */
    LORA_MAC_CRYPTO_FAIL_MIC,
    /*!
     * Address does not match
     */
    LORA_MAC_CRYPTO_FAIL_ADDRESS,
    /*!
     * JoinNonce was not greater than previous one.
     */
    LORA_MAC_CRYPTO_FAIL_JOIN_NONCE,
    /*!
     * RJcount0 reached 2^16-1
     */
    LORA_MAC_CRYPTO_FAIL_RJCOUNT0_OVERFLOW,
    /*!
     * FCNT_ID is not supported
     */
    LORA_MAC_CRYPTO_FAIL_FCNT_ID,
    /*!
     * FCntUp/Down check failed (new FCnt is smaller than previous one)
     */
    LORA_MAC_CRYPTO_FAIL_FCNT_SMALLER,
    /*!
     * FCntUp/Down check failed (duplicated)
     */
    LORA_MAC_CRYPTO_FAIL_FCNT_DUPLICATED,
    /*!
     * MAX_GAP_FCNT check failed
     */
    LORA_MAC_CRYPTO_FAIL_MAX_GAP_FCNT,
    /*!
     * Not allowed parameter value
     */
    LORA_MAC_CRYPTO_FAIL_PARAM,
    /*!
     * Null pointer exception
     */
    LORA_MAC_CRYPTO_ERROR_NPE,
    /*!
     * Invalid key identifier exception
     */
    LORA_MAC_CRYPTO_ERROR_INVALID_KEY_ID,
    /*!
     * Invalid address identifier exception
     */
    LORA_MAC_CRYPTO_ERROR_INVALID_ADDR_ID,
    /*!
     * Invalid LoRaWAN specification version
     */
    LORA_MAC_CRYPTO_ERROR_INVALID_VERSION,
    /*!
     * Incompatible buffer size
     */
    LORA_MAC_CRYPTO_ERROR_BUF_SIZE,
    /*!
     * The secure element reports an error
     */
    LORA_MAC_CRYPTO_ERROR_SECURE_ELEMENT_FUNC,
    /*!
     * Error from parser reported
     */
    LORA_MAC_CRYPTO_ERROR_PARSER,
    /*!
     * Error from serializer reported
     */
    LORA_MAC_CRYPTO_ERROR_SERIALIZER,
    /*!
     * RJcount1 reached 2^16-1 which should never happen
     */
    LORA_MAC_CRYPTO_ERROR_RJCOUNT1_OVERFLOW,
    /*!
     * Undefined Error occurred
     */
    LORA_MAC_CRYPTO_ERROR,
}LoRa_MacCryptoStatus_t;

/*!
 * Signature of callback function to be called by the LoRa_Mac Crypto module when the
 * non-volatile context have to be stored. It is also possible to save the entire
 * crypto module context.
 *
 */
typedef void ( *LoRa_MacCryptoNvmEvent )( void );

/*!
 * Initialization of LoRa_Mac Crypto module
 * It sets initial values of volatile variables and assigns the non-volatile context.
 *
 * \param[IN]     cryptoNvmCtxChanged - Callback function which will be called  when the
 *                                      non-volatile context have to be stored.
 * \retval                            - Status of the operation
 */
LoRa_MacCryptoStatus_t LoRa_MacCryptoInit( LoRa_MacCryptoNvmEvent cryptoNvmCtxChanged );

/*!
 * Sets the LoRaWAN specification version to be used.
 * 
 * \warning This function should be used for ABP only. In case of OTA the version will be set automatically.
 *
 * \param[IN]     version             - LoRaWAN specification version to be used.
 *
 * \retval                            - Status of the operation
 */
LoRa_MacCryptoStatus_t LoRa_MacCryptoSetLrWanVersion( Version_t version );

/*!
 * Restores the internal nvm context from passed pointer.
 *
 * \param[IN]     cryptoNmvCtx     - Pointer to non-volatile crypto module context to be restored.
 * \retval                         - Status of the operation
 */
LoRa_MacCryptoStatus_t LoRa_MacCryptoRestoreNvmCtx( void* cryptoNvmCtx );

/*!
 * Returns a pointer to the internal non-volatile context.
 *
 * \param[IN]     cryptoNvmCtxSize - Size of the module non-volatile context
 * \retval                         - Points to a structure where the module store its non-volatile context
 */
void* LoRa_MacCryptoGetNvmCtx( size_t* cryptoNvmCtxSize );

/*!
 * Returns updated fCntID downlink counter value.
 *
 * \param[IN]     fCntID         - Frame counter identifier
 * \param[IN]     maxFcntGap     - Maximum allowed frame counter difference (only necessary for L2 LW1.0.x)
 * \param[IN]     frameFcnt      - Received frame counter (used to update current counter value)
 * \param[OUT]    currentDown    - Current downlink counter value
 * \retval                       - Status of the operation
 */
LoRa_MacCryptoStatus_t LoRa_MacCryptoGetFCntDown( FCntIdentifier_t fCntID, uint16_t maxFCntGap, uint32_t frameFcnt, uint32_t* currentDown );

/*!
 * Returns updated fCntUp uplink counter value.
 *
 * \param[IN]     currentUp      - Uplink counter value
 * \retval                       - Status of the operation
 */
LoRa_MacCryptoStatus_t LoRa_MacCryptoGetFCntUp( uint32_t* currentUp );

/*!
 * Provides multicast context.
 *
 * \param[IN]     multicastList - Pointer to the multicast context list
 *
 * \retval                      - Status of the operation
 */
LoRa_MacCryptoStatus_t LoRa_MacCryptoSetMulticastReference( MulticastCtx_t* multicastList );

/*!
 * Sets a key
 *
 * \param[IN]     keyID          - Key identifier
 * \param[IN]     key            - Key value (16 byte), if its a multicast key it must be encrypted with McKEKey
 * \retval                       - Status of the operation
 */
LoRa_MacCryptoStatus_t LoRa_MacCryptoSetKey( KeyIdentifier_t keyID, uint8_t* key );

/*!
 * Prepares the join-request message.
 * It computes the mic and add it to the message.
 *
 * \param[IN/OUT] macMsg         - Join-request message object
 * \retval                       - Status of the operation
 */
LoRa_MacCryptoStatus_t LoRa_MacCryptoPrepareJoinRequest( LoRa_MacMessageJoinRequest_t* macMsg );

/*!
 * Prepares a rejoin-request type 1 message.
 * It computes the mic and add it to the message.
 *
 * \param[IN/OUT] macMsg         - Rejoin message object
 * \retval                       - Status of the operation
 */
LoRa_MacCryptoStatus_t LoRa_MacCryptoPrepareReJoinType1( LoRa_MacMessageReJoinType1_t* macMsg );

/*!
 * Prepares a rejoin-request type 0 or 2 message.
 * It computes the mic and add it to the message.
 *
 * \param[IN/OUT] macMsg         - Rejoin message object
 * \retval                       - Status of the operation
 */
LoRa_MacCryptoStatus_t LoRa_MacCryptoPrepareReJoinType0or2( LoRa_MacMessageReJoinType0or2_t* macMsg );

/*!
 * Handles the join-accept message.
 * It decrypts the message, verifies the MIC and if successful derives the session keys.
 *
 * \param[IN]     joinReqType    - Type of last join-request or rejoin which triggered the join-accept response
 * \param[IN]     joinEUI        - Join server EUI (8 byte)
 * \param[IN/OUT] macMsg         - Join-accept message object
 * \retval                       - Status of the operation
 */
LoRa_MacCryptoStatus_t LoRa_MacCryptoHandleJoinAccept( JoinReqIdentifier_t joinReqType, uint8_t* joinEUI, LoRa_MacMessageJoinAccept_t* macMsg );

/*!
 * Secures a message (encryption + integrity).
 *
 * \param[IN]     fCntUp          - Uplink sequence counter
 * \param[IN]     txDr            - Data rate used for the transmission
 * \param[IN]     txCh            - Index of the channel used for the transmission
 * \param[IN/OUT] macMsg          - Data message object
 * \retval                        - Status of the operation
 */
LoRa_MacCryptoStatus_t LoRa_MacCryptoSecureMessage( uint32_t fCntUp, uint8_t txDr, uint8_t txCh, LoRa_MacMessageData_t* macMsg );

/*!
 * Unsecures a message (decryption + integrity verification).
 *
 * \param[IN]     addrID          - Address identifier
 * \param[IN]     address         - Address
 * \param[IN]     fCntID          - Frame counter identifier
 * \param[IN]     fCntDown        - Downlink sequence counter
 * \param[IN/OUT] macMsg          - Data message object
 * \retval                        - Status of the operation
 */
LoRa_MacCryptoStatus_t LoRa_MacCryptoUnsecureMessage( AddressIdentifier_t addrID, uint32_t address, FCntIdentifier_t fCntID, uint32_t fCntDown, LoRa_MacMessageData_t* macMsg );

/*!
 * Derives the McRootKey from the GenAppKey or AppKey.
 *
 * 1.0.x
 * McRootKey = aes128_encrypt(GenAppKey , 0x00 | pad16)
 *
 * 1.1.x
 * McRootKey = aes128_encrypt(AppKey , 0x20 | pad16)
 *
 * \param[IN]     keyID           - Key identifier of the root key to use to perform the derivation ( GenAppKey or AppKey )
 * \retval                        - Status of the operation
 */
LoRa_MacCryptoStatus_t LoRa_MacCryptoDeriveMcRootKey( KeyIdentifier_t keyID );

/*!
 * Derives the McKEKey from the McRootKey.
 *
 * McKEKey = aes128_encrypt(McRootKey , 0x00  | pad16)
 *
 * \param[IN]     keyID           - Key identifier of the root key to use to perform the derivation ( McRootKey )
 * \retval                        - Status of the operation
 */
LoRa_MacCryptoStatus_t LoRa_MacCryptoDeriveMcKEKey( KeyIdentifier_t keyID );

/*!
 * Derives a Multicast group key pair ( McAppSKey, McNwkSKey ) from McKey
 *
 * McAppSKey = aes128_encrypt(McKey, 0x01 | McAddr | pad16)
 * McNwkSKey = aes128_encrypt(McKey, 0x02 | McAddr | pad16)
 *
 * \param[IN]     addrID          - Address identifier to select the multicast group
 * \param[IN]     mcAddr          - Multicast group address (4 bytes)
 * \retval                        - Status of the operation
 */
LoRa_MacCryptoStatus_t LoRa_MacCryptoDeriveMcSessionKeyPair( AddressIdentifier_t addrID, uint32_t mcAddr );

/*! \} addtogroup LORA_MAC */

#ifdef __cplusplus
}
#endif

#endif // __LORA_MAC_CRYPTO_H__
