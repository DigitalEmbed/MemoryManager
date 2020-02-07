#include "./Configs.h"

#if defined(__BIT_VECTOR_MANAGER_ENABLE__) && defined(__MEMORY_POOL_MANAGER_ENABLE__)

  #include "./MemoryPool.h"

  //! Function: Memory Pool Allocation
  /*!
    Allocates a memory space in a Memory Pool.
    \param mpMemoryPool is a mpool_t type. It's the memory space where the control memory pool variables will be.
    \param ui16AllocationSize is a unsigned 16-bit integer. This is the size of space allocation.
    \return Returns memory allocation address or NULL if the allocation is unsuccessful.
  */
  void* MemoryPool_malloc(mpool_t mpMemoryPool, uint16_t ui16AllocationSize){
    bool bFlagFragmentedSpace = false;
    uint16_t ui16MemoryCounter = 0;
    uint16_t ui16FreeDataBlockCounter = 0;
    uint16_t ui16BitVectorWritePosition = 0;
    if (mpMemoryPool->ui16PoolSize == 0 || mpMemoryPool->ui16FreeSpace < ui16AllocationSize){
      return NULL;
    }
    for (ui16MemoryCounter = mpMemoryPool->ui16WritePosition ; ui16FreeDataBlockCounter != ui16AllocationSize ; ui16MemoryCounter++){
      if (ui16MemoryCounter == mpMemoryPool->ui16PoolSize){
        return NULL;
      }
      if (BitVector_readBit(mpMemoryPool->bvInUse, ui16MemoryCounter) == 0){
        ui16FreeDataBlockCounter++;
      }
      else{
        bFlagFragmentedSpace = true;
        ui16FreeDataBlockCounter = 0;
      }
    }
    for (ui16BitVectorWritePosition = ui16MemoryCounter - ui16AllocationSize ; ui16BitVectorWritePosition < ui16MemoryCounter ; ui16BitVectorWritePosition++){
      BitVector_setBit(mpMemoryPool->bvInUse, ui16BitVectorWritePosition);
    }
    if (bFlagFragmentedSpace == false){
      while(BitVector_readBit(mpMemoryPool->bvInUse, ui16MemoryCounter) == 1){
        ui16MemoryCounter++;
      }
      mpMemoryPool->ui16WritePosition = ui16MemoryCounter;
    }
    mpMemoryPool->ui16FreeSpace = mpMemoryPool->ui16FreeSpace - ui16FreeDataBlockCounter;
    return (void*) &mpMemoryPool->ui8pDataMemory[(ui16BitVectorWritePosition - ui16AllocationSize) * mpMemoryPool->ui8ElementSize];
  }

  //! Function: Memory Pool Allocation
  /*!
    Allocates and clears a memory space in a Memory Pool.
    \param mpMemoryPool is a mpool_t type. It's the memory space where the control memory pool variables will be.
    \param ui16AllocationSize is a unsigned 16-bit integer. This is the size of space allocation.
    \return Returns memory allocation address or NULL if the allocation is unsuccessful.
  */
  void* MemoryPool_calloc(mpool_t mpMemoryPool, uint16_t ui16AllocationSize){
    void* vpReturnPointer = MemoryPool_malloc(mpMemoryPool, ui16AllocationSize);
    if (vpReturnPointer != NULL){
      memset(vpReturnPointer, 0, ui16AllocationSize * mpMemoryPool->ui8ElementSize);
    }
    return vpReturnPointer;
  }

  //! Macro: Memory Pool Reallocation
  /*!
    Deallocates memory space in Memory Pool.
    \param mpMemoryPool is a mpool_t type. It's the memory space where the control memory pool variables will be.
    \param vppAllocatedPointer is a void pointer parameter. It's the address of the pointer of the allocation. On case deallocation successfully, this function going to set this pointer to NULL.
    \param ui16OldAllocationSize is a unsigned 16-bit integer. This is the actual allocation size.
    \param ui16NewAllocationSize is a unsigned 16-bit integer. This is the new allocation size.
    \return Returns MEMORY_POOL_STATUS_REALLOCATED_MEMORY or MEMORY_POOL_STATUS_REALLOCATION_ERROR.
  */
  mpool_status_t (MemoryPool_realloc)(mpool_t mpMemoryPool, void** vppAllocatedPointer, uint16_t ui16OldAllocationSize, uint16_t ui16NewAllocationSize){
    void* vpNewAllocation = MemoryPool_calloc(mpMemoryPool, ui16NewAllocationSize);
    if (vpNewAllocation == NULL){
      return MEMORY_POOL_STATUS_REALLOCATION_ERROR;
    }
    memcpy(vpNewAllocation, *vppAllocatedPointer, ui16OldAllocationSize);
    MemoryPool_free(mpMemoryPool, vppAllocatedPointer, ui16OldAllocationSize);
    if (*vppAllocatedPointer != NULL){
      return MEMORY_POOL_STATUS_REALLOCATION_ERROR;
    }
    *vppAllocatedPointer = vpNewAllocation;
    return MEMORY_POOL_STATUS_REALLOCATED_MEMORY;
  }

  //! Function: Memory Pool Fragmentation Checker
  /*!
    Checks if the memory pool is fragmented.
    \param mpMemoryPool is a mpool_t type. It's the memory space where the control memory pool variables will be.
    \return Returns MEMORY_POOL_STATUS_FRAGMENTED_MEMORY or MEMORY_POOL_STATUS_UNFRAGMENTED_MEMORY.
  */
  mpool_status_t MemoryPool_checkFragmentation(mpool_t mpMemoryPool){
    if (((mpMemoryPool->ui16WritePosition + 1) != (mpMemoryPool->ui16PoolSize - mpMemoryPool->ui16FreeSpace)) && (mpMemoryPool->ui16PoolSize != mpMemoryPool->ui16FreeSpace)){
      return MEMORY_POOL_STATUS_FRAGMENTED_MEMORY;
    }
    return MEMORY_POOL_STATUS_UNFRAGMENTED_MEMORY;
  }

  //! Function: Memory Pool Deallocation
  /*!
    Deallocates memory space in Memory Pool.
    \param mpMemoryPool is a mpool_t type. It's the memory space where the control memory pool variables will be.
    \param vppAllocatedPointer is a void pointer parameter. It's the address of the pointer of the allocation. On case deallocation successfully, this function going to set this pointer to NULL.
    \param ui16AllocationSize is a unsigned 16-bit integer. This is the size of space allocation.
  */
  void (MemoryPool_free)(mpool_t mpMemoryPool, void** vppAllocatedPointer, uint16_t ui16AllocationSize){
    uint8_t* ui8pStartAllocationPointer = mpMemoryPool->ui8pDataMemory;
    uint8_t* ui8pEndAllocationPointer = mpMemoryPool->ui8pDataMemory + (mpMemoryPool->ui16PoolSize * mpMemoryPool->ui8ElementSize);
    uint16_t ui16StartAllocationPosition = SoftMath_module(((uint8_t*) *vppAllocatedPointer - mpMemoryPool->ui8pDataMemory)/mpMemoryPool->ui8ElementSize);
    uint16_t ui16EndAllocationPosition = ui16StartAllocationPosition + ui16AllocationSize - 1;
    if (*vppAllocatedPointer != NULL && (uint8_t*) *vppAllocatedPointer >= ui8pStartAllocationPointer && (uint8_t*) *vppAllocatedPointer <= ui8pEndAllocationPointer && ui16StartAllocationPosition <= mpMemoryPool->ui16PoolSize && ui16EndAllocationPosition <= mpMemoryPool->ui16PoolSize){
      uint16_t ui16Position = 0;
      for (ui16Position = ui16StartAllocationPosition ; ui16Position <= ui16EndAllocationPosition ; ui16Position++){
        BitVector_clearBit(mpMemoryPool->bvInUse, ui16Position);
      }
      if (mpMemoryPool->ui16WritePosition > ui16StartAllocationPosition){
        mpMemoryPool->ui16WritePosition = ui16StartAllocationPosition;
      }
      mpMemoryPool->ui16FreeSpace = mpMemoryPool->ui16FreeSpace + ui16AllocationSize;
      *vppAllocatedPointer = NULL;
    }
  }

  //! Function: Memory Pool Fragmented Free Space Checker
  /*!
    Checks memory pool maximum free space for allocation.
    \param mpMemoryPool is a mpool_t type. It's the memory space where the control memory pool variables will be.
    \return Returns memory pool maximum free space for allocation.
  */
  uint16_t MemoryPool_getMaxFreeSpace(mpool_t mpMemoryPool){
    uint8_t ui8PreviousMemoryState = 0;
    uint8_t ui8CurrentMemoryState = 0;
    uint16_t ui16FragmentedFreeSpace = 0;
    uint16_t ui16MaxFragmentedFreeSpace = 0;
    uint16_t ui16Counter = 0;
    if (MemoryPool_checkFragmentation(mpMemoryPool) == MEMORY_POOL_STATUS_UNFRAGMENTED_MEMORY){
      return mpMemoryPool->ui16FreeSpace;
    }
    for(ui16Counter = 0 ; ui16Counter < mpMemoryPool->ui16PoolSize ; ui16Counter++){
      ui8PreviousMemoryState = ui8CurrentMemoryState;
      ui8CurrentMemoryState = BitVector_readBit(mpMemoryPool->bvInUse, ui16Counter);
      if (ui8CurrentMemoryState == 0){
        ui16FragmentedFreeSpace++;
      }
      if ((ui8PreviousMemoryState == 0 && ui8CurrentMemoryState == 1) || (ui16Counter == (mpMemoryPool->ui16PoolSize - 1))){
        ui16MaxFragmentedFreeSpace = SoftMath_bigger(ui16FragmentedFreeSpace, ui16MaxFragmentedFreeSpace);
        ui16FragmentedFreeSpace = 0;
      }
    }
    return ui16MaxFragmentedFreeSpace;
  }

#endif