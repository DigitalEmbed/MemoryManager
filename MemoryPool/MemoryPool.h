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

#ifndef MemoryPool_H
#define MemoryPool_H

#include <inttypes.h>
#include <string.h>

//! Macro of static bit vector allocation.
/*!
  This macros are for calculate the iNumber of cell of bit-vectors type on objects mpool_t.
*/
#define     uiAuxiliaryVectorSize(uiPoolSize)     ((uiPoolSize) < 8) ? 1 : (((uiPoolSize) >> 3) + 1)

//! Macros for cleaning codes.
/*!
  This macros leave the code cleaner when creating pools. This macro can be instantiated outside of a function: this will make the pool be global.
  \param mpName is the name of memory pool.
  \param Type is the type of memory pool.
  \param ui16Size is the size of memory pool.
*/
#define     xCreatePool(mpName, Type, ui16Size)         uint16_t PoolSize##mpName = ui16Size;\
                                                        uint8_t DataSize##mpName = sizeof(Type);\
                                                        Type PoolVector##mpName[ui16Size];\
                                                        bitvector_t BitVector##mpName[uiAuxiliaryVectorSize(ui16Size)];\
                                                        mpool_t mpName;

//! Macros for cleaning codes.
/*!
  This macros leave the code cleaner when initialing pools.
  \param mpName is the name of memory pool.
*/
#define     ui8PoolInit(mpName)                         ui8MPInit(&mpName, PoolVector##mpName, BitVector##mpName, PoolSize##mpName, DataSize##mpName)

//! Allocation State macros.
/*!
  This macros are for facilitate the use of function ui8MPfree of type objects mpool_t.
*/
#define     MEMORYPOOL_INIT_SUCESS            1
#define     MEMORYPOOL_INIT_ERROR             0
#define     DEALLOCATION_SUCESS               1
#define     DEALLOCATION_ERROR                0
#define     FRAGMENTED_MEMORY                 1
#define     UNFRAGMENTED_MEMORY               0

//! bitvector_t typedef.
/*!
  This typedef exist for organization purpose. This type is equivalent of a 8-bit unsigned integer.
*/
typedef uint8_t bitvector_t;

//! Manager-type struct.
/*!
  This struct creates a memory pool space for manager feature on your software.
*/
typedef struct{
  void* vpDataSpace;                                                                                                                            /*!< Pointer void type variable. */
  bitvector_t* bvInUse;                                                                                                                         /*!< 8-bits integer type variable. */
  uint16_t ui16DataSize;                                                                                                                        /*!< 16-bits integer type variable. */
  uint16_t ui16WritePosition;                                                                                                                   /*!< 16-bits integer type variable. */
  uint16_t ui16FreeSpace;                                                                                                                       /*!< 16-bits integer type variable. */
  uint8_t ui8ElementSize;                                                                                                                       /*!< 8-bits integer type variable. */
} mpool_t;

uint8_t ui8MPInit(mpool_t *mpMemoryPool, void *vpDataSpace, bitvector_t* bvInUse, uint16_t ui16DataSize, uint8_t ui8ElementSize);             /*!< 8-bits integer type function. */
uint8_t ui8MPCheckFragmentation(mpool_t *mpMemoryPool);                                                                                       /*!< 8-bits integer type function. */
uint8_t ui8MPGetElementSize(mpool_t *mpMemoryPool);                                                                                           /*!< 8-bits integer type function. */
uint16_t ui16MPGetFragmentedFreeSpace(mpool_t *mpMemoryPool);                                                                                 /*!< 16-bits integer type function. */
uint16_t ui16MPGetWritePosition(mpool_t *mpMemoryPool);                                                                                       /*!< 16-bits integer type function. */
uint16_t ui16MPGetFreeSpace(mpool_t *mpMemoryPool);                                                                                           /*!< 16-bits integer type function. */
uint16_t ui16MPGetDataSize(mpool_t *mpMemoryPool);                                                                                            /*!< 16-bits integer type function. */
void* vpMPAlloc(mpool_t *mpMemoryPool, uint16_t ui16AllocationSize);                                                                          /*!< Void type pointer function. */
void* vpMPRealloc(mpool_t *mpMemoryPool, void** vpAllocatedPointer, uint16_t ui16OldAllocationSize, uint16_t ui16NewAllocationSize);          /*!< Void type pointer function. */
void vMPFree(mpool_t *mpMemoryPool, void** vpAllocatedPointer, uint16_t ui16AllocationSize);                                                  /*!< Void type function. */

#endif
