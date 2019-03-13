/*!
  This code file was written by Jorge Henrique Moreira Santana and is under
  the GNU GPLv3 license. All legal rights are reserved.

  Permissions of this copyleft license are conditioned on making available
  complete source code of licensed works and modifications under the same
  license or the GNU GPLv3. Copyright and license notices must be preserved.
  Contributors provide an express grant of patent rights. However, a larger
  work using the licensed work through interfaces provided by the licensed
  work may be distributed under different terms and without source code for
  the larger work.

  * Permissions:
    -> Commercial use;
    -> Modification;
    -> Distribuition;
    -> Patent Use;
    -> Private Use;

  * Limitations:
    -> Liability;
    -> Warranty;

  * Conditions:
    -> License and copyright notice;
    -> Disclose source;
    -> State changes;
    -> Same license (library);

  For more informations, check the LICENSE document. If you want to use a
  commercial product without having to provide the source code, send an email
  to jorge_henrique_123@hotmail.com to talk.
*/

#ifndef Buffer_H
#define Buffer_H

#ifdef __cplusplus
  extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

//! Macro: Number of Preallocation
/*!
  This macro is basically the maximum memory size reserved for dynamic allocations for buffers.
*/
#ifndef NUMBER_OF_BUFFER
  #define   NUMBER_OF_BUFFER        10
#endif


//! Macro: Pool Allocation Status
/*!
  This macros are for facilitate the use of this library.
*/
#define   BUFFER_INITIALIZED        1

//! Macro: Buffer Type
/*!
  This macros are for facilitate the use of this library.
*/
#define   STACK                     0
#define   LIFO                      0
#define   FILO                      0

#define   QUEUE                     1
#define   FIFO                      1

#define   CIRCULAR                  2

//! Type Definition: Buffer Structure
/*!
  Structure of circular buffer.
*/
typedef struct {
  void* vpVector;                                                                                                           /*!< Void pointer type. */
  uint8_t ui8ElementSize;                                                                                                   /*!< 8-bits integer type. */
  uint8_t ui8BufferSize;                                                                                                    /*!< 8-bits integer type. */
  uint8_t ui8ReadPosition;                                                                                                  /*!< 8-bits integer type. */
  uint8_t ui8WritePosition;                                                                                                 /*!< 8-bits integer type. */
  uint8_t ui8AmountOfData;                                                                                                  /*!< 8-bits integer type. */
  uint8_t ui8AllocationType;                                                                                                /*!< 8-bits integer type. */
  uint8_t ui8BufferType;
} buffer_t;

buffer_t* bpCreateGenericBuffer(void* vpVector, uint8_t ui8BufferType, uint8_t ui8ElementSize, uint8_t ui8BufferSize);      /*!< buffer_t pointer type function. */
buffer_t* bpCreateBuffer(uint8_t ui8BufferType, uint8_t ui8ElementSize, uint8_t ui8BufferSize);                             /*!< buffer_t pointer type function. */
void vCleanBuffer(buffer_t* bpBuffer);                                                                                     	/*!< Void type function. */
void vDeleteBuffer(buffer_t** bpBuffer);                                                                                   	/*!< Void type function. */
void vPushBufferData(buffer_t* bpBuffer, void* vpData);                                                                     /*!< Void type function. */
void* vpPullBufferData(buffer_t* bpBuffer);                                                                                 /*!< Void pointer type function. */
uint8_t ui8BufferManagerInit();                                                                                             /*!< 8-bits integer type. */
uint8_t ui8GetAmountOfPendingData(buffer_t* bpBuffer);                                                                     	/*!< 8-bits integer type. */
uint8_t ui8GetWritePosition(buffer_t* bpBuffer);                                                                            /*!< 8-bits integer type. */
uint8_t ui8GetReadPosition(buffer_t* bpBuffer);                                                                             /*!< 8-bits integer type. */

#ifdef __cplusplus
  }
#endif

#endif
