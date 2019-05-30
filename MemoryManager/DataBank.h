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

#ifndef DataBank_H
#define DataBank_H

#ifdef __cplusplus
  extern "C" {
#endif

#include <inttypes.h>

//! Macros: Data Bank State
/*!
  This macros are for facilitate the use of this library.
*/
#define   DATABANK_INITIALIZED      1
#define   DATABANK_NOT_INITIALIZED  7
#define   SIZE_UNRECOGNIZED         65535

uint8_t ui8DataBankInit(void);																		                                                                            /*!< 8-bits integer type function. */
uint16_t ui16CheckFragmentation(uint8_t ui8ElementSize);                                                                                      /*!< 8-bits integer type function. */
uint16_t ui16GetFragmentedFreeSpace(uint8_t ui8ElementSize);                                                                                  /*!< 16-bits integer type function. */
uint16_t ui16GetFreeSpace(uint8_t ui8ElementSize);                                                                                            /*!< 16-bits integer type function. */
void* vpDBAlloc(uint8_t ui8ElementSize, uint16_t ui16AllocationSize);							                                                            /*!< Void pointer type function. */
void* vpDBRealloc(uint8_t ui8ElementSize, void* pvAllocatedPointer, uint16_t ui16OldAllocationSize, uint16_t ui16NewAllocationSize);          /*!< Void pointer type function. */
void vDBFree(void* pvAllocatedPointer, uint8_t ui8ElementSize, uint16_t ui16AllocationSize);                                                  /*!< Void type function. */

#ifdef __cplusplus
  }
#endif

#endif
