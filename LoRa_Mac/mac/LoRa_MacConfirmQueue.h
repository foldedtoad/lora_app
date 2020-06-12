/*!
 * \file      LoRa_MacConfirmQueue.h
 *
 * \brief     LoRa MAC confirm queue implementation
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
 * \defgroup  LORA_MACCONFIRMQUEUE LoRa MAC confirm queue implementation
 *            This module specifies the API implementation of the LoRaMAC confirm queue.
 *            The confirm queue is implemented with as a ring buffer. The number of
 *            elements can be defined with \ref LORA_MAC_MLME_CONFIRM_QUEUE_LEN. The
 *            current implementation does not support multiple elements of the same
 *            Mlme_t type.
 * \{
 */
#ifndef __LORA_MAC_CONFIRMQUEUE_H__
#define __LORA_MAC_CONFIRMQUEUE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdint.h>

#include "LoRa_Mac.h"

/*!
 * LoRa_Mac MLME-Confirm queue length
 */
#define LORA_MAC_MLME_CONFIRM_QUEUE_LEN             5

/*!
 * Structure to hold multiple MLME request confirm data
 */
typedef struct sMlmeConfirmQueue
{
    /*!
     * Holds the previously performed MLME-Request
     */
    Mlme_t Request;
    /*!
     * Status of the operation
     */
    LoRa_MacEventInfoStatus_t Status;
    /*!
     * Set to true, if the request is ready to be handled
     */
    bool ReadyToHandle;
    /*!
     * Set to true, if it is not permitted to set the ReadyToHandle variable
     * with a function call to LoRa_MacConfirmQueueSetStatusCmn.
     */
    bool RestrictCommonReadyToHandle;
}MlmeConfirmQueue_t;

/*!
 * Signature of callback function to be called by this module when the
 * non-volatile needs to be saved.
 */
typedef void ( *LoRa_MacConfirmQueueNvmEvent )( void );

/*!
 * \brief   Initializes the confirm queue
 *
 * \param   [IN] primitives - Pointer to the LoRa_Mac primitives.
 *
 * \param   [IN] confirmQueueNvmCtxChanged - Callback function which will be called when the
 *                                           non-volatile context needs to be saved.
 */
void LoRa_MacConfirmQueueInit( LoRa_MacPrimitives_t* primitives, LoRa_MacConfirmQueueNvmEvent confirmQueueNvmCtxChanged  );

/*!
 * Restores the internal non-volatile context from passed pointer.
 *
 * \param   [IN] confirmQueueNvmCtx - Pointer to non-volatile class B module context to be restored.
 *
 * \retval  [true - operation was successful, false - operation failed]
 */
bool LoRa_MacConfirmQueueRestoreNvmCtx( void* confirmQueueNvmCtx );

/*!
 * Returns a pointer to the internal non-volatile context.
 *
 * \param   [IN] confirmQueueNvmCtxSize - Size of the module non-volatile context
 *
 * \retval  - Points to a structure where the module store its non-volatile context
 */
void* LoRa_MacConfirmQueueGetNvmCtx( size_t* confirmQueueNvmCtxSize );

/*!
 * \brief   Adds an element to the confirm queue.
 *
 * \param   [IN] mlmeConfirm - Pointer to the element to add.
 *
 * \retval  [true - operation was successful, false - operation failed]
 */
bool LoRa_MacConfirmQueueAdd( MlmeConfirmQueue_t* mlmeConfirm );

/*!
 * \brief   Removes the last element which was added into the queue.
 *
 * \retval  [true - operation was successful, false - operation failed]
 */
bool LoRa_MacConfirmQueueRemoveLast( void );

/*!
 * \brief   Removes the first element which was added to the confirm queue.
 *
 * \retval  [true - operation was successful, false - operation failed]
 */
bool LoRa_MacConfirmQueueRemoveFirst( void );

/*!
 * \brief   Sets the status of an element.
 *
 * \param   [IN] status - The status to set.
 *
 * \param   [IN] request - The related request to set the status.
 */
void LoRa_MacConfirmQueueSetStatus( LoRa_MacEventInfoStatus_t status, Mlme_t request );

/*!
 * \brief   Gets the status of an element.
 *
 * \param   [IN] request - The request to query the status.
 *
 * \retval  The status of the related MlmeRequest.
 */
LoRa_MacEventInfoStatus_t LoRa_MacConfirmQueueGetStatus( Mlme_t request );

/*!
 * \brief   Sets a common status for all elements in the queue.
 *
 * \param   [IN] status - The status to set.
 */
void LoRa_MacConfirmQueueSetStatusCmn( LoRa_MacEventInfoStatus_t status );

/*!
 * \brief   Gets the common status of all elements.
 *
 * \retval  The common status of all elements.
 */
LoRa_MacEventInfoStatus_t LoRa_MacConfirmQueueGetStatusCmn( void );

/*!
 * \brief   Verifies if a request is in the queue and active.
 *
 * \param   [IN] request - The request to verify.
 *
 * \retval  [true - element is in the queue, false - element is not in the queue].
 */
bool LoRa_MacConfirmQueueIsCmdActive( Mlme_t request );

/*!
 * \brief   Handles all callbacks of active requests
 *
 * \param   [IN] mlmeConfirm - Pointer to the generic mlmeConfirm structure.
 */
void LoRa_MacConfirmQueueHandleCb( MlmeConfirm_t* mlmeConfirm );

/*!
 * \brief   Query number of elements in the queue.
 *
 * \retval  Number of elements.
 */
uint8_t LoRa_MacConfirmQueueGetCnt( void );

/*!
 * \brief   Verify if the confirm queue is full.
 *
 * \retval  [true - queue is full, false - queue is not full].
 */
bool LoRa_MacConfirmQueueIsFull( void );

#ifdef __cplusplus
}
#endif

#endif // __LORA_MAC_CONFIRMQUEUE_H__
