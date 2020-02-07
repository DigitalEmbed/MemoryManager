#include "./Configs.h"

#if defined(__BIT_VECTOR_MANAGER_ENABLE__) && defined(__MEMORY_POOL_MANAGER_ENABLE__) && defined(__DATA_BANK_MANAGER_ENABLE__)

  #include "./DataBank.h"
  #include "./MemoryPool.h"

  //! Memory Pools: Data Bank Pools
  /*!
    Declaration of memory pools for data bank.
  */
  #define X(mpMemoryPoolName, ui8DataPoolSize, ui16MemoryPoolSize)\
    newMemoryPool(mpMemoryPoolName, ui8DataPoolSize, ui16MemoryPoolSize);

    __DATA_BANK_POOL_LIST__
  #undef X

  //! Function: Data Bank Allocation
  /*!
    Allocate space memory in Data Bank.
    \param ui8ElementSize is a unsigned 8-bit integer. This is the size of the elements.
    \param ui16AllocationSize is a unsigned 16-bit integer. This is the size of space allocation.
    \return Returns the memory allocation address or NULL if the allocation is unsuccessful.
  */
  void* DataBank_malloc(uint8_t ui8ElementSize, uint16_t ui16AllocationSize){
    #define X(mpMemoryPoolName, ui8DataPoolSize, ui16MemoryPoolSize)\
      if (ui8DataPoolSize == ui8ElementSize){\
        return MemoryPool_malloc(mpMemoryPoolName, ui16AllocationSize);\
      }

      __DATA_BANK_POOL_LIST__
    #undef X
    return NULL;
  }

  //! Function: Data Bank Allocation
  /*!
    Allocates and clears space memory in Data Bank.
    \param ui8ElementSize is a unsigned 8-bit integer. This is the size of the elements.
    \param ui16AllocationSize is a unsigned 16-bit integer. This is the size of space allocation.
    \return Returns the memory allocation address or NULL if the allocation is unsuccessful.
  */
  void* DataBank_calloc(uint8_t ui8ElementSize, uint16_t ui16AllocationSize){
    #define X(mpMemoryPoolName, ui8DataPoolSize, ui16MemoryPoolSize)\
      if (ui8DataPoolSize == ui8ElementSize){\
        return MemoryPool_calloc(mpMemoryPoolName, ui16AllocationSize);\
      }

      __DATA_BANK_POOL_LIST__
    #undef X
    return NULL;
  }

  //! Function: Data Bank Deallocation
  /*!
    Deallocate space memory in Data Bank.
    \param vppAllocatedPointer is a void pointer parameter. It's the address of the allocation. On case deallocation successfully, this function going to set this pointer to NULL
    \param ui8ElementSize is a unsigned 8-bit integer. This is the size of the elements.
    \param ui16AllocationSize is a unsigned 16-bit integer. This is the size of space allocation.
  */
  void (DataBank_free)(void** vpAllocatedPointer, uint8_t ui8ElementSize, uint16_t ui16AllocationSize){
    #define X(mpMemoryPoolName, ui8DataPoolSize, ui16MemoryPoolSize)\
      if (ui8DataPoolSize == ui8ElementSize){\
        return MemoryPool_free(mpMemoryPoolName, vpAllocatedPointer, ui16AllocationSize);\
      }

      __DATA_BANK_POOL_LIST__
    #undef X
  }

  //! Function: Data Bank Fragmentation Checker
  /*!
    Check if data bank is fragmented.
    \param ui8ElementSize is a unsigned 8-bit integer. This is the size of the elements.
    \return Return FRAGMENTED_MEMORY, UNFRAGMENTED_MEMORY or DATA_BANK_STATUS_UNRECOGNIZED_SIZE.
  */
  data_bank_status_t DataBank_checkFragmentation(uint8_t ui8ElementSize){
    #define X(mpMemoryPoolName, ui8DataPoolSize, ui16MemoryPoolSize)\
      if (ui8DataPoolSize == ui8ElementSize){\
        return ((MemoryPool_checkFragmentation(mpMemoryPoolName) == MEMORY_POOL_STATUS_FRAGMENTED_MEMORY) ? DATA_BANK_STATUS_FRAGMENTED_MEMORY : DATA_BANK_STATUS_UNFRAGMENTED_MEMORY);\
      }

      __DATA_BANK_POOL_LIST__
    #undef X
    return DATA_BANK_STATUS_UNRECOGNIZED_SIZE;
  }

  //! Function: Data Bank Fragmented Free Space Checker
  /*!
    Check the maximum data bank allocation.
    \param ui8ElementSize is a unsigned 8-bit integer. This is the size of the elements.
    \return Return the maximum memory pool allocation or DATA_BANK_STATUS_UNRECOGNIZED_SIZE.
  */
  uint16_t DataBank_getMaxFreeSpace(uint8_t ui8ElementSize){
    #define X(mpMemoryPoolName, ui8DataPoolSize, ui16MemoryPoolSize)\
      if (ui8DataPoolSize == ui8ElementSize){\
        return MemoryPool_getMaxFreeSpace(mpMemoryPoolName);\
      }

      __DATA_BANK_POOL_LIST__
    #undef X
    return DATA_BANK_STATUS_UNRECOGNIZED_SIZE;
  }

  //! Function: Data Bank Reallocation
  /*!
    Reallocate space memory in data bank.
    \param ui8ElementSize is a unsigned 8-bit integer. This is the size of the elements.
    \param vppAllocatedPointer is a void pointer to pointer parameter. It's the address of the pointer of the allocation. On case deallocation successfully, this function going to set this pointer to NULL.
    \param ui16OldAllocationSize is a unsigned 16-bit integer. This is the old size of space allocation.
    \param ui16NewAllocationSize is a unsigned 16-bit integer. This is the new size of space allocation.
    \return Returns the new memory allocation address or NULL if the allocation is unsuccessful.
  */
  data_bank_status_t (DataBank_realloc)(uint8_t ui8ElementSize, void** vppAllocatedPointer, uint16_t ui16OldAllocationSize, uint16_t ui16NewAllocationSize){
    #define X(mpMemoryPoolName, ui8DataPoolSize, ui16MemoryPoolSize)\
      if (ui8DataPoolSize == ui8ElementSize){\
        return ((MemoryPool_realloc(mpMemoryPoolName, vppAllocatedPointer, ui16OldAllocationSize, ui16NewAllocationSize) == MEMORY_POOL_STATUS_REALLOCATED_MEMORY) ? DATA_BANK_STATUS_REALLOCATED_MEMORY : DATA_BANK_STATUS_REALLOCATION_ERROR);\
      }

      __DATA_BANK_POOL_LIST__
    #undef X
    return DATA_BANK_STATUS_REALLOCATION_ERROR;
  }

  //! Function: Data Bank Free Space Checker
  /*!
    Check data bank free space.
    \param ui8ElementSize is a unsigned 8-bit integer. This is the size of the elements.
    \return Return the memory pool free space or DATA_BANK_STATUS_UNRECOGNIZED_SIZE.
  */
  uint16_t DataBank_getFreeSpace(uint8_t ui8ElementSize){
    #define X(mpMemoryPoolName, ui8DataPoolSize, ui16MemoryPoolSize)\
      if (ui8DataPoolSize == ui8ElementSize){\
        return MemoryPool_getFreeSpace(mpMemoryPoolName);\
      }

      __DATA_BANK_POOL_LIST__
    #undef X
    return DATA_BANK_STATUS_UNRECOGNIZED_SIZE;
  }

#endif
