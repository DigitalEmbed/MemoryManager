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

#ifndef __MEMORY_MANAGER_CONFIGS_HEADER__
  #define __MEMORY_MANAGER_CONFIGS_HEADER__

  #ifdef __cplusplus
    extern "C" {
  #endif

  //! Configuration: Bit Vector Manager
  /*!
    Enable or disable system bit vector manager here. The available values for this macro are:
      - __BIT_VECTOR_MANAGER_ENABLE__
      - __BIT_VECTOR_MANAGER_DISABLE__
  */
  #define __BIT_VECTOR_MANAGER_ENABLE__

  //! Configuration: Memory Pool Manager
  /*!
    Configure the system memory pool manager here. The available values for this macro are:
      - __MEMORY_POOL_MANAGER_ENABLE__
      - __MEMORY_POOL_MANAGER_DISABLE__
  */
  #define __MEMORY_POOL_MANAGER_ENABLE__

  //! Configuration: Data Bank Manager
  /*!
    Configure the system data bank manager here. The available values for this macro are:
      - __DATA_BANK_MANAGER_ENABLE__
      - __DATA_BANK_MANAGER_DISABLE__
  */
  #define __DATA_BANK_MANAGER_ENABLE__

  #if defined(__BIT_VECTOR_MANAGER_ENABLE__) && defined(__MEMORY_POOL_MANAGER_ENABLE__) && defined(__DATA_BANK_MANAGER_ENABLE__)
    //! Configuration: DataBank Size Pools
    /*!
      Configure the DataBank pools size here.
      X(mpMemoryPoolName, ui8DataPoolSize, ui16MemoryPoolSize)
    */
    #define __DATA_BANK_POOL_LIST__\
      X(mp8BitPool, sizeof(uint8_t), 30)\
      X(mp16BitPool, sizeof(uint16_t), 20)\
      X(mp32BitPool, sizeof(uint32_t), 10)\
      X(mp64BitPool, sizeof(uint64_t), 5)

  #endif

  //! Configuration: Buffer Manager
  /*!
    Enable or disable system buffer manager here. The available values for this macro are:
      - __BUFFER_MANAGER_ENABLE__
      - __BUFFER_MANAGER_DISABLE__
  */
  #define __BUFFER_MANAGER_ENABLE__

  //! Configuration: TypedList Manager
  /*!
    Enable or disable system typed list manager here. The available values for this macro are:
      - __TYPED_LIST_MANAGER_ENABLE__
      - __TYPED_LIST_MANAGER_DISABLE__
  */
  #define __TYPED_LIST_MANAGER_ENABLE__

  #if defined(__TYPED_LIST_MANAGER_ENABLE__) && defined(__BIT_VECTOR_MANAGER_ENABLE__) && defined(__MEMORY_POOL_MANAGER_ENABLE__)

    //! Configuration: Typed List Pool Size
    /*!
      Configure untyped element pool size here.
    */
    #define __TYPED_LIST_UNTYPED_ELEMENT_POOL_SIZE__ 100

  #endif

  //! Configuration: UntypedList Manager
  /*!
    Enable or disable system untyped list manager here. The available values for this macro are:
      - __UNTYPED_LIST_MANAGER_ENABLE__
      - __UNTYPED_LIST_MANAGER_DISABLE__
  */
  #define __UNTYPED_LIST_MANAGER_ENABLE__

  #if defined(__UNTYPED_LIST_MANAGER_ENABLE__) && defined(__BIT_VECTOR_MANAGER_ENABLE__) && defined(__MEMORY_POOL_MANAGER_ENABLE__)
    //! Configuration: Untyped List Pool Size
    /*!
      Configure typed element pool size here.
    */
    #define __UNTYPED_LIST_TYPED_ELEMENT_POOL_SIZE__ 100

  #endif

  #ifdef __cplusplus
    }
  #endif

#endif
