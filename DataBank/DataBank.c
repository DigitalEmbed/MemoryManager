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

//! Memory Pools: Data Bank Pools
/*!
  Declaration of memory pools for data bank.
*/
xCreatePool(mp8bitPool, uint8_t, SIZE_MPOOL_8BIT);
xCreatePool(mp16bitPool, uint16_t, SIZE_MPOOL_16BIT);
xCreatePool(mp32bitPool, uint32_t, SIZE_MPOOL_32BIT);
xCreatePool(mp64bitPool, uint64_t, SIZE_MPOOL_64BIT);

//! Function: Data Bank Initializer
/*!
  Initialize the data bank.
  \return Returns 0 if allocation is successful, 8 if deallocation of the mp8bitPool is unsuccessful, 16 if deallocation of the mp16bitPool is unsuccessful, 32 if deallocation of the mp32bitPool is unsuccessful or 64 if deallocation of the mp64bitPool is unsuccessful.
*/
uint8_t ui8DataBankInit(){
  static uint8_t ui8DataBankStatus = 0;
  if (ui8DataBankStatus != DATABANK_INITIALIZED){
    if (ui8PoolInit(mp8bitPool) == MEMORYPOOL_INIT_ERROR){
      return 8;
    }
    if (ui8PoolInit(mp16bitPool) == MEMORYPOOL_INIT_ERROR){
      return 16;
    }
    if (ui8PoolInit(mp32bitPool) == MEMORYPOOL_INIT_ERROR){
      return 32;
    }
    if (ui8PoolInit(mp64bitPool) == MEMORYPOOL_INIT_ERROR){
      return 64;
    }
    ui8DataBankStatus = DATABANK_INITIALIZED;
  }
  return DATABANK_INITIALIZED;
}

//! Function: Data Bank Allocation
/*!
  Allocate memory space in Data Bank.
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

//! Function: Data Bank Deallocation
/*!
  Deallocate memory space in Data Bank.
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

//! Function: Data Bank Fragmentation Checker
/*!
  Check if data bank is fragmented.
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

//! Function: Data Bank Fragmented Free Space Checker
/*!
  Check the maximum data bank allocation.
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

//! Function: Data Bank Reallocation
/*!
  Reallocate memory space in data bank.
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

//! Function: Data Bank Free Space Checker
/*!
  Check data bank free space.
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
