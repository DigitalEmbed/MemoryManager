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

#include "./Configs.h"

//! System Message: BitVector Manager Status
/*!
  Please don't modify this.
*/
#if (!defined(__BIT_VECTOR_MANAGER_ENABLE__))
  #pragma message "Bit vector manager disabled!"
#endif

//! System Message: Memory Pool Manager Status
/*!
  Please don't modify this.
*/
#if (!defined(__MEMORY_POOL_MANAGER_ENABLE__) || !defined(__BIT_VECTOR_MANAGER_ENABLE__))
  #pragma message "Memory pool manager disabled!"
#endif

//! System Message: Memory Pool Manager Status
/*!
  Please don't modify this.
*/
#if (!defined(__MEMORY_POOL_MANAGER_ENABLE__) || !defined(__DATA_BANK_MANAGER_ENABLE__) || !defined(__BIT_VECTOR_MANAGER_ENABLE__))
  #pragma message "Data bank manager disabled!"
#endif

//! System Message: Buffer Manager Status
/*!
  Please don't modify this.
*/
#if (!defined(__BUFFER_MANAGER_ENABLE__))
  #pragma message "Buffer manager disabled!"
#endif

//! System Message: TypedList Manager Status
/*!
  Please don't modify this.
*/
#if (!defined(__TYPED_LIST_MANAGER_ENABLE__))
  #pragma message "Typed list manager disabled!"
#endif

//! System Message: TypedList Dynamic Memory Allocation Warning
/*!
  Please don't modify this.
*/
#if (defined(__TYPED_LIST_MANAGER_ENABLE__) && (!defined(__MEMORY_POOL_MANAGER_ENABLE__) || !defined(__BIT_VECTOR_MANAGER_ENABLE__)))
  #warning TypedLists uses dynamic allocation functions! You shoud be extremely cautious with your RAM. In projects with MISRA rules, you should enable __MEMORY_POOL_MANAGER_ENABLE__.
#endif

//! System Message: UntypedList Manager Status
/*!
  Please don't modify this.
*/
#if (!defined(__UNTYPED_LIST_MANAGER_ENABLE__))
  #pragma message "Untyped list manager disabled!"
#endif

//! System Message: TypedList Dynamic Memory Allocation Warning
/*!
  Please don't modify this.
*/
#if (defined(__UNTYPED_LIST_MANAGER_ENABLE__) && (!defined(__MEMORY_POOL_MANAGER_ENABLE__) || !defined(__BIT_VECTOR_MANAGER_ENABLE__)))
  #warning UntypedLists uses dynamic allocation functions! You shoud be extremely cautious with your RAM. In projects with MISRA rules, you should enable __MEMORY_POOL_MANAGER_ENABLE__.
#endif

//! System Message: TypedList Error
/*!
  Please don't modify this.
*/
#if (!((defined(__TYPED_LIST_MANAGER_ENABLE__) && (!defined(__BIT_VECTOR_MANAGER_ENABLE__) || !defined(__MEMORY_POOL_MANAGER_ENABLE__)))\
||((defined(__TYPED_LIST_MANAGER_ENABLE__) && defined(__TYPED_LIST_UNTYPED_ELEMENT_POOL_SIZE__) && (__TYPED_LIST_UNTYPED_ELEMENT_POOL_SIZE__ > 0)))))
  #error Invalid __SOFT_DECIMAL_AMOUNT_OF_FRACTIONARY_BITS__ value!
#endif

//! System Message: UntypedList Error
/*!
  Please don't modify this.
*/
#if (!((defined(__UNTYPED_LIST_MANAGER_ENABLE__) && (!defined(__BIT_VECTOR_MANAGER_ENABLE__) || !defined(__MEMORY_POOL_MANAGER_ENABLE__)))\
||((defined(__UNTYPED_LIST_MANAGER_ENABLE__) && defined(__UNTYPED_LIST_TYPED_ELEMENT_POOL_SIZE__) && (__UNTYPED_LIST_TYPED_ELEMENT_POOL_SIZE__ > 0)))))
  #error Invalid __UNTYPED_LIST_TYPED_ELEMENT_POOL_SIZE__ value!
#endif