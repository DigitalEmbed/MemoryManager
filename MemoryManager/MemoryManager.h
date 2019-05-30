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

#ifndef MemoryManager_H
#define MemoryManager_H

#ifdef __cplusplus
  extern "C" {
#endif

#include <inttypes.h>
#include <EmbeddedTools.h>

/*!
  MemoryManager system libraries.
*/
#include "MemoryPool.h"
#include "DataBank.h"
#include "Buffer.h"
#include "LinkedList.h"

/*!
  Memory Manager Initialization Status.
*/
#define   MEMORY_MANAGER_INITIALIZED          1
#define   MEMORY_MANAGER_NOT_INTIALIZED       0

//! Configuration: Memory Manager
/*!
  Configure the MemoryManager system here.
*/
#define   SIZE_MPOOL_8BIT                     280
#define   SIZE_MPOOL_16BIT                    40
#define   SIZE_MPOOL_32BIT                    20
#define   SIZE_MPOOL_64BIT                    10

//! Configuration: Linked List Manager
/*!
  Configure the MemoryManager system linked list manager here.
*/
#define   NUMBER_OF_LISTS                     5
#define   NUMBER_OF_TYPED_ELEMENT             10
#define   NUMBER_OF_UNTYPED_ELEMENT           10

//! Configuration: Buffer Manager
/*!
  Configure the MemoryManager system buffer manager here.
*/
#define   NUMBER_OF_BUFFER                    5

uint8_t ui8MemoryManagerInit(void); 					/*!< 8-bits integer type function. */

#ifdef __cplusplus
  }
#endif

#endif
