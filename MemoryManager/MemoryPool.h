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

#ifndef __MEMORY_POOL_HEADER__
  #define __MEMORY_POOL_HEADER__

  #include "./Configs.h"

  #if defined(__BIT_VECTOR_MANAGER_ENABLE__) && defined(__MEMORY_POOL_MANAGER_ENABLE__)

    #ifdef __cplusplus
      extern "C" {
    #endif

    #include <stdint.h>
    #include <string.h>
    #include "./BitVector.h"

    //! Type Definition: Memory Pool Struct.
    /*!
      This struct creates a memory pool space for manager feature on your software.
    */
    typedef struct{
      uint8_t* const ui8pDataMemory;              /*!< uint8_t* const type variable. */
      bitvector_t* bvInUse;                       /*!< bitvector_t type variable. */
      const uint16_t ui16PoolSize;                /*!< const uint16_t integer type variable. */
      uint16_t ui16WritePosition;                 /*!< uint16_t type variable. */
      uint16_t ui16FreeSpace;                     /*!< uint16_t type variable. */
      const uint8_t ui8ElementSize;               /*!< const uint8_t integer type variable. */
    } mpool_structure_t;

    //! Type Definition: mpool_t
    /*!
      This typedef is for facilitate the use of this library.
    */
    typedef mpool_structure_t* mpool_t;

    //! Enumeration Definition: Memory Pool Status
    /*!
      This typedef is for facilitate the use of this library.
    */
    typedef enum{
      MEMORY_POOL_STATUS_UNFRAGMENTED_MEMORY = 0,
      MEMORY_POOL_STATUS_FRAGMENTED_MEMORY,
      MEMORY_POOL_STATUS_REALLOCATED_MEMORY,
      MEMORY_POOL_STATUS_REALLOCATION_ERROR
    } mpool_status_t;

    //! Macro: Memory Pool Creator
    /*!
      Constructs a memory pool.
      \param mpName is a memory pool name.
      \param ui16DataSize is a 16-bit integer. It's type data size of your memory pool.
      \param ui16MemoryPoolSize is a 16-bit integer. It's the amount of blocks that will be in your memory pool.
      \param ui8SizeOfBuffer is a 8-Bit integer. Its buffer size.
    */
    #define newMemoryPool(mpName, ui16DataSize, ui16MemoryPoolSize)\
      uint8_t __ui8p##mpName[((ui16MemoryPoolSize) * (ui16DataSize))];\
      newBitVector(__bv##mpName, (ui16MemoryPoolSize));\
      mpool_structure_t __mpsMemoryPoolStructure##mpName = {\
        .ui8pDataMemory = __ui8p##mpName,\
        .bvInUse = __bv##mpName,\
        .ui16PoolSize = ui16MemoryPoolSize,\
        .ui16WritePosition = 0,\
        .ui16FreeSpace = ui16MemoryPoolSize,\
        .ui8ElementSize = ui16DataSize\
      };\
      mpool_t mpName = &__mpsMemoryPoolStructure##mpName

    //! Macro: Static Memory Pool Creator
    /*!
      Constructs a static memory pool.
      \param mpName is a memory pool name.
      \param ui16DataSize is a 16-bit integer. It's type data size of your memory pool.
      \param ui16MemoryPoolSize is a 16-bit integer. It's the amount of blocks that will be in your memory pool.
      \param ui8SizeOfBuffer is a 8-Bit integer. Its buffer size.
    */
    #define newStaticMemoryPool(mpName, ui16DataSize, ui16MemoryPoolSize)\
      static uint8_t __ui8p##mpName[((ui16MemoryPoolSize) * (ui16DataSize))];\
      newStaticBitVector(__bv##mpName, (ui16MemoryPoolSize));\
      static mpool_structure_t __mpsMemoryPoolStructure##mpName = {\
        .ui8pDataMemory = __ui8p##mpName,\
        .bvInUse = __bv##mpName,\
        .ui16PoolSize = ui16MemoryPoolSize,\
        .ui16WritePosition = 0,\
        .ui16FreeSpace = ui16MemoryPoolSize,\
        .ui8ElementSize = ui16DataSize\
      };\
      static mpool_t mpName = &__mpsMemoryPoolStructure##mpName

    //! Macro: Memory Pool Reallocation
    /*!
      Deallocates memory space in Memory Pool.
      \param mpMemoryPool is a mpool_t type. It's the memory space where the control memory pool variables will be.
      \param vpAllocatedPointer is a void pointer parameter. It's the address of the pointer of the allocation. On case deallocation successfully, this function going to set this pointer to NULL.
      \param ui16OldAllocationSize is a unsigned 16-bit integer. This is the actual allocation size.
      \param ui16NewAllocationSize is a unsigned 16-bit integer. This is the new allocation size.
      \return Returns MEMORY_POOL_STATUS_REALLOCATED_MEMORY or MEMORY_POOL_STATUS_REALLOCATION_ERROR.
    */
    #define MemoryPool_realloc(mpMemoryPool, vpAllocatedPointer, ui16OldAllocationSize, ui16NewAllocationSize)\
      MemoryPool_realloc(mpMemoryPool, (void**) vpAllocatedPointer, ui16OldAllocationSize, ui16NewAllocationSize)

    //! Macro: Memory Pool Deallocation
    /*!
      Deallocates memory space in Memory Pool.
      \param mpMemoryPool is a mpool_t type. It's the memory space where the control memory pool variables will be.
      \param vpAllocatedPointer is a void pointer parameter. It's the address of the pointer of the allocation. On case deallocation successfully, this function going to set this pointer to NULL.
      \param ui16AllocationSize is a unsigned 16-bit integer. This is the size of space allocation.
    */
    #define MemoryPool_free(mpMemoryPool, vpAllocatedPointer, ui16AllocationSize)\
      MemoryPool_free(mpMemoryPool, (void**) vpAllocatedPointer, ui16AllocationSize)

    //! Getter Macro: Memory Pool Size
    /*!
      Gets memory pool size.
      \param mpMemoryPool is a mpool_t type. It's the memory space where the control memory pool variables will be.
      \return Returns size of memory pool.
    */
    #define MemoryPool_getSize(mpMemoryPool)\
      mpMemoryPool->ui16PoolSize

    //! Getter Macro: Free Space
    /*!
      Gets memory pool free space.
      \param mpMemoryPool is a mpool_t type. It's the memory space where the control memory pool variables will be.
      \return Returns free space of memory pool.
    */
    #define MemoryPool_getFreeSpace(mpMemoryPool)\
      mpMemoryPool->ui16FreeSpace

    //! Getter Macro: Element Size
    /*!
      Gets memory pool element size.
      \param mpMemoryPool is a mpool_t type. It's the memory space where the control memory pool variables will be.
      \return Returns size of memory pool element.
    */
    #define MemoryPool_getElementSize(mpMemoryPool)\
      mpMemoryPool->ui8ElementSize

    void* MemoryPool_malloc(mpool_t mpMemoryPool, uint16_t ui16AllocationSize);                                                                               /*!< void pointer type function. */
    void* MemoryPool_calloc(mpool_t mpMemoryPool, uint16_t ui16AllocationSize);                                                                               /*!< void pointer type function. */
    void (MemoryPool_free)(mpool_t mpMemoryPool, void** vpAllocatedPointer, uint16_t ui16AllocationSize);                                                     /*!< void type function. */
    uint16_t MemoryPool_getMaxFreeSpace(mpool_t mpMemoryPool);                                                                                                /*!< uint16_t type function. */
    mpool_status_t (MemoryPool_realloc)(mpool_t mpMemoryPool, void** vpAllocatedPointer, uint16_t ui16OldAllocationSize, uint16_t ui16NewAllocationSize);     /*!< mpool_status_t type function. */
    mpool_status_t MemoryPool_checkFragmentation(mpool_t mpMemoryPool);                                                                                       /*!< mpool_status_t type function. */

    #ifdef __cplusplus
      }
    #endif
  
  #endif
#endif
