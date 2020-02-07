//! MemoryManager Version 3.2b
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

#ifndef __DATA_BANK_H__
  #define __DATA_BANK_H__

  #include "./Configs.h"

  #if defined(__BIT_VECTOR_MANAGER_ENABLE__) && defined(__MEMORY_POOL_MANAGER_ENABLE__) && defined(__DATA_BANK_MANAGER_ENABLE__)

    #ifdef __cplusplus
      extern "C" {
    #endif

    #include <stdint.h>

    typedef enum{
      DATA_BANK_STATUS_UNFRAGMENTED_MEMORY = 0,
      DATA_BANK_STATUS_FRAGMENTED_MEMORY,
      DATA_BANK_STATUS_REALLOCATED_MEMORY,
      DATA_BANK_STATUS_REALLOCATION_ERROR,
      DATA_BANK_STATUS_UNRECOGNIZED_SIZE = 65535
    } data_bank_status_t;

    //! Macro: Data Bank Deallocation
    /*!
      Deallocate space memory in Data Bank.
      \param vppAllocatedPointer is a void pointer parameter. It's the address of the allocation. On case deallocation successfully, this function going to set this pointer to NULL
      \param ui8ElementSize is a unsigned 8-bit integer. This is the size of the elements.
      \param ui16AllocationSize is a unsigned 16-bit integer. This is the size of space allocation.
    */
    #define DataBank_free(vpAllocatedPointer, ui8ElementSize, ui16AllocationSize)\
      DataBank_free((void**)vpAllocatedPointer, ui8ElementSize, ui16AllocationSize)

    //! Macro: Data Bank Reallocation
    /*!
      Reallocate space memory in data bank.
      \param ui8ElementSize is a unsigned 8-bit integer. This is the size of the elements.
      \param vppAllocatedPointer is a void pointer to pointer parameter. It's the address of the pointer of the allocation. On case deallocation successfully, this function going to set this pointer to NULL.
      \param ui16OldAllocationSize is a unsigned 16-bit integer. This is the old size of space allocation.
      \param ui16NewAllocationSize is a unsigned 16-bit integer. This is the new size of space allocation.
      \return Returns the new memory allocation address or NULL if the allocation is unsuccessful.
    */
    #define DataBank_realloc(ui8ElementSize, vppAllocatedPointer, ui16OldAllocationSize, ui16NewAllocationSize)\
      DataBank_realloc(ui8ElementSize, (void**) vppAllocatedPointer, ui16OldAllocationSize, ui16NewAllocationSize)

    uint16_t DataBank_getMaxFreeSpace(uint8_t ui8ElementSize);                                                                                                        /*!< 16-bits integer type function. */
    uint16_t DataBank_getFreeSpace(uint8_t ui8ElementSize);                                                                                                           /*!< 16-bits integer type function. */
    void* DataBank_malloc(uint8_t ui8ElementSize, uint16_t ui16AllocationSize);							                                                                          /*!< void pointer type function. */
    void* DataBank_calloc(uint8_t ui8ElementSize, uint16_t ui16AllocationSize);							                                                                          /*!< void pointer type function. */
    void (DataBank_free)(void** vpAllocatedPointer, uint8_t ui8ElementSize, uint16_t ui16AllocationSize);                                                             /*!< void type function. */
    data_bank_status_t DataBank_checkFragmentation(uint8_t ui8ElementSize);                                                                                           /*!< data_bank_status_t integer type function. */
    data_bank_status_t (DataBank_realloc)(uint8_t ui8ElementSize, void** vppAllocatedPointer, uint16_t ui16OldAllocationSize, uint16_t ui16NewAllocationSize);          /*!< data_bank_status_t type function. */

    #ifdef __cplusplus
      }
    #endif

  #endif
#endif
