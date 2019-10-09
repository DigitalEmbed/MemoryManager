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

#include "MemoryPool.h"
#include "MemoryManager.h"

//! Macro: Address Calculation
/*!
  This macro is for calculate the address of a ui8Position specified of the uiDataSpace vector.
*/
#define     uiAdressCalculation(uiDataSpace, uiWritePosition, uiElementSize)      (char*) uiDataSpace + uiWritePosition*uiElementSize

//! Function: Memory Pool Initializer
/*!
  Create a Memory Pool with the vector stored in vpDataSpace in struct mpMemoryPool.
  \param mpMemoryPool is a pointer of mpool_t type. It is the memory space where the control variables of the memory pool will be.
  \param vpDataSpace is a void pointer parameter. Basically, this parameter is the memory pool.
  \param bvInUse is a unsigned 8-bit integer. The size of this vector is calculated with macro "uiAuxiliaryVectorSize(size-of-vpDataSpace)": On this macro, put the size of the vector vpDataSpace. This vector is for control of in use ui8Position of vpDataSpace.
  \param ui16DataSize is a unsigned 16-bit integer. This is the size of vector vpDataSpace.
  \param ui8ElementSize is a unsigned 8-bit integer. This is the size of the elements.
  \return Returns MEMORYPOOL_INIT_SUCESS or MEMORYPOOL_INIT_ERROR.
*/
uint8_t ui8MPInit(mpool_t* mpMemoryPool, void *vpDataSpace, bitvector_t* bvInUse, uint16_t ui16DataSize, uint8_t ui8ElementSize){
  if(mpMemoryPool != NULL && ui16DataSize > 0 && vpDataSpace != NULL && bvInUse != NULL && ui8ElementSize > 0){
    mpMemoryPool->bvInUse = bvInUse;
    mpMemoryPool->ui16DataSize = ui16DataSize;
    mpMemoryPool->ui16FreeSpace = ui16DataSize;
    mpMemoryPool->ui16WritePosition = 0;
    mpMemoryPool->vpDataSpace = vpDataSpace;
    mpMemoryPool->ui8ElementSize = ui8ElementSize;
    return MEMORYPOOL_INIT_SUCESS;
  }
  else{
    return MEMORYPOOL_INIT_ERROR;
  }
}

//! Getter Function: Write Position of Last Element Written
/*!
  This function get a write ui8Position of the last element written.
  \return Returns write ui8Position of the last element written.
*/
uint16_t ui16MPGetWritePosition(mpool_t *mpMemoryPool){
  return mpMemoryPool->ui16WritePosition;
}

//! Getter Function: Free Space
/*!
  This function get the free space of memory pool.
  \return Returns free space of memory pool.
*/
uint16_t ui16MPGetFreeSpace(mpool_t *mpMemoryPool){
  return mpMemoryPool->ui16FreeSpace;
}

//! Getter Function: Element Size
/*!
  This function get the element size of memory pool.
  \return Returns element size of memory pool.
*/
uint8_t ui8MPGetElementSize(mpool_t *mpMemoryPool){
  return mpMemoryPool->ui8ElementSize;
}

//! Getter Function: Memory Pool Size
/*!
  This function get the memory pool size.
  \return Returns data size of memory pool.
*/
uint16_t ui16MPGetDataSize(mpool_t *mpMemoryPool){
  return mpMemoryPool->ui16DataSize;
}

//! Function: Memory Pool Allocation
/*!
  Allocate memory space in Memory Pool.
  \param mpMemoryPool is a pointer of mpool_t type. It is the memory space where the control variables of the memory pool will be.
  \param ui16DataSize is a unsigned 16-bit integer. This is the size of space allocation.
  \return Returns memory allocation address or NULL if the allocation is unsuccessful.
*/
void* vpMPAlloc(mpool_t* mpMemoryPool, uint16_t ui16AllocationSize){
  if (mpMemoryPool->ui16DataSize == 0 || mpMemoryPool->ui16FreeSpace < ui16AllocationSize){
    return NULL;
  }
  uint16_t ui16FreeDataSpace = 0;
  uint8_t ui8FlagFreeSpace = 0;
  while(ui8FlagFreeSpace == 0){
    if (mpMemoryPool->ui16WritePosition == mpMemoryPool->ui16DataSize){
      return NULL;
    }
    mpMemoryPool->ui16WritePosition++;
    if (ui8ReadBitVector(mpMemoryPool->bvInUse, mpMemoryPool->ui16WritePosition) == 0){
      ui16FreeDataSpace++;
    }
    else{
      ui16FreeDataSpace = 0;
    }
    if (ui16FreeDataSpace == ui16AllocationSize){
      ui8FlagFreeSpace = 1;
    }
  }
  uint16_t ui16StartPosition = mpMemoryPool->ui16WritePosition - ui16AllocationSize;
  uint16_t ui16CounterPositionVector = 0;
  for (ui16CounterPositionVector = ui16StartPosition ; ui16CounterPositionVector < mpMemoryPool->ui16WritePosition ; ui16CounterPositionVector++){
    vSetBitVector(mpMemoryPool->bvInUse, ui16CounterPositionVector);
  }
  mpMemoryPool->ui16FreeSpace = mpMemoryPool->ui16FreeSpace - ui16FreeDataSpace;
  void *adressAllocation = uiAdressCalculation(mpMemoryPool->vpDataSpace, ui16StartPosition, mpMemoryPool->ui8ElementSize);
  return (void*) adressAllocation;
}

//! Function: Memory Pool Deallocation
/*!
  Deallocate memory space in Memory Pool.
  \param mpMemoryPool is a pointer of mpool_t type. It is the memory space where the control variables of the memory pool will be.
  \param vpAllocatedPointer is a void pointer to pointer parameter. It's the address of the pointer of the allocation. On case deallocation successfully, this function going to set this pointer to NULL.
  \param ui16AllocationSize is a unsigned 16-bit integer. This is the size of space allocation.
*/
void vMPFree(mpool_t* mpMemoryPool, void** vpAllocatedPointer, uint16_t ui16AllocationSize){
  if (vpAllocatedPointer != NULL && (char*) *vpAllocatedPointer >= (char*) mpMemoryPool->vpDataSpace && (char*) *vpAllocatedPointer <= (char*) mpMemoryPool->vpDataSpace + mpMemoryPool->ui16DataSize){
    int32_t i32StartAllocation = ((char*) *vpAllocatedPointer - (char*) mpMemoryPool->vpDataSpace)/mpMemoryPool->ui8ElementSize;
    uint32_t ui32EndAllocation = (uiModule(i32StartAllocation)) + ui16AllocationSize - 1;
    uint32_t ui32Position = 0;
    for (ui32Position = (uiModule(i32StartAllocation)) ; ui32Position <= ui32EndAllocation ; ui32Position++){
      vEraseBitVector(mpMemoryPool->bvInUse, ui32Position);
    }
    if (mpMemoryPool->ui16WritePosition > i32StartAllocation){
      mpMemoryPool->ui16WritePosition = i32StartAllocation;
    }
    mpMemoryPool->ui16FreeSpace = mpMemoryPool->ui16FreeSpace + ui16AllocationSize;
    *vpAllocatedPointer = NULL;
  }
}

//! Function: Memory Pool Fragmentation Checker
/*!
  Check that the memory pool is fragmented.
  \param mpMemoryPool is a pointer of mpool_t type. It is the memory space where the control variables of the memory pool will be.
  \return Returns FRAGMENTED_MEMORY or UNFRAGMENTED_MEMORY.
*/
uint8_t ui8MPCheckFragmentation(mpool_t *mpMemoryPool){
  uint8_t ui8PreviousMemoryState = 0;
  uint8_t ui8CurrentMemoryState = 0;
  uint16_t ui16Counter = 0;
  for(ui16Counter = 0; ui16Counter < mpMemoryPool->ui16DataSize; ui16Counter++){
    ui8PreviousMemoryState = ui8CurrentMemoryState;
    ui8CurrentMemoryState = ui8ReadBitVector(mpMemoryPool->bvInUse, ui16Counter);
    if (ui8PreviousMemoryState == 0 && ui8CurrentMemoryState == 1){
      return FRAGMENTED_MEMORY;
    }
  }
  return UNFRAGMENTED_MEMORY;
}

//! Function: Memory Pool Fragmented Free Space Checker
/*!
  Check the maximum memory pool allocation.
  \param mpMemoryPool is a pointer of mpool_t type. It is the memory space where the control variables of the memory pool will be.
  \return Returns maximum memory pool allocation.
*/
uint16_t ui16MPGetFragmentedFreeSpace(mpool_t* mpMemoryPool){
  uint8_t ui8PreviousMemoryState = 0;
  uint8_t ui8CurrentMemoryState = 0;
  uint16_t ui16FragmentedFreeSpace = 0;
  uint16_t ui16MaxFragmentedFreeSpace = 0;
  uint16_t ui16Counter = 0;
  for(ui16Counter = 0; ui16Counter < mpMemoryPool->ui16DataSize; ui16Counter++){
    ui8PreviousMemoryState = ui8CurrentMemoryState;
    ui8CurrentMemoryState = ui8ReadBitVector(mpMemoryPool->bvInUse, ui16Counter);
    if (ui8CurrentMemoryState == 0){
      ui16FragmentedFreeSpace++;
    }
    if ((ui8PreviousMemoryState == 0 && ui8CurrentMemoryState == 1) || (ui16Counter == (mpMemoryPool->ui16DataSize - 1))){
      ui16MaxFragmentedFreeSpace = iBigger(ui16FragmentedFreeSpace, ui16MaxFragmentedFreeSpace);
      ui16FragmentedFreeSpace = 0;
    }
  }
  return ui16MaxFragmentedFreeSpace;
}

//! Function: Memory Pool Reallocation
/*!
  Reallocate memory space in Memory Pool.
  \param mpMemoryPool is a pointer of mpool_t type. It is the memory space where the control variables of the memory pool will be.
  \param vpAllocatedPointer is a void pointer to pointer parameter. It's the address of the pointer of the allocation. On case deallocation successfully, this function going to set this pointer to NULL.
  \param ui16OldAllocationSize is a unsigned 16-bit integer. This is the old size of space allocation.
  \param ui16NewAllocationSize is a unsigned 16-bit integer. This is the new size of space allocation.
  \return Returns new memory allocation address or NULL if the allocation is unsuccessful.
*/
void* vpMPRealloc(mpool_t* mpMemoryPool, void** vpAllocatedPointer, uint16_t ui16OldAllocationSize, uint16_t ui16NewAllocationSize){
  if (ui16OldAllocationSize != ui16NewAllocationSize){
    void* vpBufferPointer = vpMPAlloc(mpMemoryPool, ui16NewAllocationSize);
    if (vpBufferPointer != NULL){
      memcpy(vpBufferPointer, *vpAllocatedPointer, iSmaller(ui16OldAllocationSize, ui16NewAllocationSize));
      vMPFree(mpMemoryPool, vpAllocatedPointer, ui16OldAllocationSize);
      if (*vpAllocatedPointer != NULL){
        return NULL;
      }
      return vpBufferPointer;
    }
  }
  return NULL;
}
