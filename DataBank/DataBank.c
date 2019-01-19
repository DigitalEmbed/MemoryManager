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

#include "DataBank.h"

uint8_t ui8DataBankStatus = 0;

/*!
  This vectors is the dataSpace of the Memory Pool.
  You can decrease the size of this vector to force
  a insufficient memory error.
*/
uint8_t ui8Pool[SIZE_MPOOL_8BIT];
uint16_t ui16Pool[SIZE_MPOOL_16BIT];
uint32_t ui32Pool[SIZE_MPOOL_32BIT];
uint64_t ui64Pool[SIZE_MPOOL_64BIT];
/*!
  Declaration of a bitvector_t type vector. This is an
  auxiliary vector that is responsible for managing the
  use of spaces allocated in the memory pool.
*/
bitvector_t bvAux8Pool[uiAuxiliaryVectorSize(SIZE_MPOOL_8BIT)];
bitvector_t bvAux16Pool[uiAuxiliaryVectorSize(SIZE_MPOOL_16BIT)];
bitvector_t bvAux32Pool[uiAuxiliaryVectorSize(SIZE_MPOOL_32BIT)];
bitvector_t bvAux64Pool[uiAuxiliaryVectorSize(SIZE_MPOOL_64BIT)];

/*!
  Declaration of the memory pool struct.
*/
mpool_t mp8bitPool;
mpool_t mp16bitPool;
mpool_t mp32bitPool;
mpool_t mp64bitPool;

//! Memory Pool initialization function
/*!
  Initialize the memory pools.
  \return Returns 0 if allocation is successful, 8 if deallocation of the mp8bitPool is unsuccessful, 16 if deallocation of the mp16bitPool is unsuccessful, 32 if deallocation of the mp32bitPool is unsuccessful or 64 if deallocation of the mp64bitPool is unsuccessful.
*/
uint8_t ui8DataBankInit(){
  if (ui8DataBankStatus != DATABANK_INITIALIZED){
    if (ui8MPInit(&mp8bitPool, ui8Pool, bvAux8Pool, SIZE_MPOOL_8BIT, sizeof(uint8_t)) == MEMORYPOOL_INIT_ERROR){           /*!< If not possible memory pool allocation... */
      return 8;                                                                                                                               /*!< You can treat the problem any way you want! */
    }
    if (ui8MPInit(&mp16bitPool, ui16Pool, bvAux16Pool, SIZE_MPOOL_16BIT, sizeof(uint16_t)) == MEMORYPOOL_INIT_ERROR){      /*!< If not possible memory pool allocation... */
      return 16;                                                                                                                              /*!< You can treat the problem any way you want! */
    }
    if (ui8MPInit(&mp32bitPool, ui32Pool, bvAux32Pool, SIZE_MPOOL_32BIT, sizeof(uint32_t)) == MEMORYPOOL_INIT_ERROR){      /*!< If not possible memory pool allocation... */
      return 32;                                                                                                                              /*!< You can treat the problem any way you want! */
    }
    if (ui8MPInit(&mp64bitPool, ui64Pool, bvAux64Pool, SIZE_MPOOL_64BIT, sizeof(uint64_t)) == MEMORYPOOL_INIT_ERROR){      /*!< If not possible memory pool allocation... */
      return 64;                                                                                                                              /*!< You can treat the problem any way you want! */
    }
    ui8DataBankStatus = DATABANK_INITIALIZED;
  }
  return DATABANK_INITIALIZED;
}

//! Memory Pool allocation function
/*!
  Allocate memory space in Memory Pools.
  \param ui8ElementSize is a unsigned 8-bit integer. This is the size of the elements.
  \param ui16AllocationSize is a unsigned 16-bit integer. This is the size of space allocation.
  \return Returns the memory allocation address or NULL if the allocation is unsuccessful.
*/
void* vpDBAlloc(uint8_t ui8ElementSize, uint16_t ui16AllocationSize){
  if (ui8ElementSize == sizeof(uint8_t)){
    return vpMPAlloc(&mp8bitPool, ui16AllocationSize);
  }
  else if(ui8ElementSize <= sizeof(uint16_t) && ui8ElementSize > sizeof(uint8_t)){
    return vpMPAlloc(&mp16bitPool, ui16AllocationSize);
  }
  else if(ui8ElementSize <= sizeof(uint32_t) && ui8ElementSize > sizeof(uint16_t)){
    return vpMPAlloc(&mp32bitPool, ui16AllocationSize);
  }
  else if(ui8ElementSize <= sizeof(uint64_t) && ui8ElementSize > sizeof(uint32_t)){
    return vpMPAlloc(&mp64bitPool, ui16AllocationSize);
  }
  else{
    return NULL;
  }
}

//! Memory Pool deallocation function
/*!
  Deallocate memory space in Memory Pool.
  \param pvAllocatedPointer is a void pointer parameter. It's the address of the allocation. On case deallocation successfully, this function going to set this pointer to NULL
  \param ui8ElementSize is a unsigned 8-bit integer. This is the size of the elements.
  \param ui16AllocationSize is a unsigned 16-bit integer. This is the size of space allocation.
*/
void vDBFree(void* pvAllocatedPointer, uint8_t ui8ElementSize, uint16_t ui16AllocationSize){
  if (ui8ElementSize == sizeof(uint8_t)){
    vMPFree(&mp8bitPool, (void**) pvAllocatedPointer, ui16AllocationSize);
  }
  else if(ui8ElementSize <= sizeof(uint16_t) && ui8ElementSize > sizeof(uint8_t)){
    vMPFree(&mp16bitPool, (void**) pvAllocatedPointer, ui16AllocationSize);
  }
  else if(ui8ElementSize <= sizeof(uint32_t) && ui8ElementSize > sizeof(uint16_t)){
    vMPFree(&mp32bitPool, (void**) pvAllocatedPointer, ui16AllocationSize);
  }
  else if(ui8ElementSize <= sizeof(uint64_t) && ui8ElementSize > sizeof(uint32_t)){
    vMPFree(&mp64bitPool, (void**) pvAllocatedPointer, ui16AllocationSize);
  }
}

//! Memory Pool fragmentation checker
/*!
  Check that the memory pool is fragmented.
  \param ui8ElementSize is a unsigned 8-bit integer. This is the size of the elements.
  \return Return FRAGMENTED_MEMORY, UNFRAGMENTED_MEMORY or SIZE_UNRECOGNIZED.
*/
uint16_t ui16CheckFragmentation(uint8_t ui8ElementSize){
  if (ui8ElementSize == sizeof(uint8_t)){
    return ui8MPCheckFragmentation(&mp8bitPool);
  }
  else if(ui8ElementSize <= sizeof(uint16_t) && ui8ElementSize > sizeof(uint8_t)){
    return ui8MPCheckFragmentation(&mp16bitPool);
  }
  else if(ui8ElementSize <= sizeof(uint32_t) && ui8ElementSize > sizeof(uint16_t)){
    return ui8MPCheckFragmentation(&mp32bitPool);
  }
  else if(ui8ElementSize <= sizeof(uint64_t) && ui8ElementSize > sizeof(uint32_t)){
    return ui8MPCheckFragmentation(&mp64bitPool);
  }
  else{
    return SIZE_UNRECOGNIZED;
  }
}

//! Memory Pool fragmented free space checker
/*!
  Check the maximum memory pool allocation.
  \param ui8ElementSize is a unsigned 8-bit integer. This is the size of the elements.
  \return Return the maximum memory pool allocation or SIZE_UNRECOGNIZED.
*/
uint16_t ui16GetFragmentedFreeSpace(uint8_t ui8ElementSize){
  if (ui8ElementSize == sizeof(uint8_t)){
    return ui16MPGetFragmentedFreeSpace(&mp8bitPool);
  }
  else if(ui8ElementSize <= sizeof(uint16_t) && ui8ElementSize > sizeof(uint8_t)){
    return ui16MPGetFragmentedFreeSpace(&mp16bitPool);
  }
  else if(ui8ElementSize <= sizeof(uint32_t) && ui8ElementSize > sizeof(uint16_t)){
    return ui16MPGetFragmentedFreeSpace(&mp32bitPool);
  }
  else if(ui8ElementSize <= sizeof(uint64_t) && ui8ElementSize > sizeof(uint32_t)){
    return ui16MPGetFragmentedFreeSpace(&mp64bitPool);
  }
  else{
    return SIZE_UNRECOGNIZED;
  }
}

//! Memory Pool reallocation function
/*!
  Reallocate memory space in Memory Pool.
  \param ui8ElementSize is a unsigned 8-bit integer. This is the size of the elements.
  \param pvAllocatedPointer is a void pointer to pointer parameter. It's the address of the pointer of the allocation. On case deallocation successfully, this function going to set this pointer to NULL.
  \param ui16OldAllocationSize is a unsigned 16-bit integer. This is the old size of space allocation.
  \param ui16NewAllocationSize is a unsigned 16-bit integer. This is the new size of space allocation.
  \return Returns the new memory allocation address or NULL if the allocation is unsuccessful.
*/
void* vpDBRealloc(uint8_t ui8ElementSize, void* pvAllocatedPointer, uint16_t ui16OldAllocationSize, uint16_t ui16NewAllocationSize){
  if (ui8ElementSize == sizeof(uint8_t)){
    return vpMPRealloc(&mp8bitPool, (void**) pvAllocatedPointer, ui16OldAllocationSize, ui16NewAllocationSize);
  }
  else if(ui8ElementSize <= sizeof(uint16_t) && ui8ElementSize > sizeof(uint8_t)){
    return vpMPRealloc(&mp16bitPool, (void**) pvAllocatedPointer, ui16OldAllocationSize, ui16NewAllocationSize);
  }
  else if(ui8ElementSize <= sizeof(uint32_t) && ui8ElementSize > sizeof(uint16_t)){
    return vpMPRealloc(&mp32bitPool, (void**) pvAllocatedPointer, ui16OldAllocationSize, ui16NewAllocationSize);
  }
  else if(ui8ElementSize <= sizeof(uint64_t) && ui8ElementSize > sizeof(uint32_t)){
    return vpMPRealloc(&mp64bitPool, (void**) pvAllocatedPointer, ui16OldAllocationSize, ui16NewAllocationSize);
  }
  else{
    return NULL;
  }
}

//! Memory Pool fragmented free space checker
/*!
  Check the memory pool free space.
  \param ui8ElementSize is a unsigned 8-bit integer. This is the size of the elements.
  \return Return the memory pool free space or SIZE_UNRECOGNIZED.
*/
uint16_t ui16GetFreeSpace(uint8_t ui8ElementSize){
  if (ui8ElementSize == sizeof(uint8_t)){
    return ui16MPGetFreeSpace(&mp8bitPool);
  }
  else if(ui8ElementSize <= sizeof(uint16_t) && ui8ElementSize > sizeof(uint8_t)){
    return ui16MPGetFreeSpace(&mp16bitPool);
  }
  else if(ui8ElementSize <= sizeof(uint32_t) && ui8ElementSize > sizeof(uint16_t)){
    return ui16MPGetFreeSpace(&mp32bitPool);
  }
  else if(ui8ElementSize <= sizeof(uint64_t) && ui8ElementSize > sizeof(uint32_t)){
    return ui16MPGetFreeSpace(&mp64bitPool);
  }
  else{
    return SIZE_UNRECOGNIZED;
  }
}
