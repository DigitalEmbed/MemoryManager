#include "./Configs.h"

#if (defined(__UNTYPED_LIST_MANAGER_ENABLE__))

  #if ((defined(__UNTYPED_LIST_MANAGER_ENABLE__) && (!defined(__BIT_VECTOR_MANAGER_ENABLE__) || !defined(__MEMORY_POOL_MANAGER_ENABLE__)))\
  ||((defined(__UNTYPED_LIST_MANAGER_ENABLE__) && defined(__UNTYPED_LIST_TYPED_ELEMENT_POOL_SIZE__) && (__UNTYPED_LIST_TYPED_ELEMENT_POOL_SIZE__ > 0))))

    #include "./UntypedList.h"
    #include "./MemoryPool.h"
    #include "./DataBank.h"
    #include <string.h>

    #if !defined(__MEMORY_POOL_MANAGER_ENABLE__) || !defined(__BIT_VECTOR_MANAGER_ENABLE__)
      #include <stdlib.h>
    #endif

    //! Type Definition: Untyped Linked List Element Structure
    /*!
      Untyped element struct for non-typed linked lists.
    */
    struct telem_t{
      void* vpData;                                                                                       /*!< Pointer void type. */
      struct telem_t* tepNext;                                                                            /*!< Pointer telem_t type. */
      uint8_t ui8DataSize;                                                                                    /*!< 8-bits integer type. */
    };

    //! Type Definition: telem_t and telem_t
    /*!
      This typedef is for facilitate the use of lList library.
    */
    typedef struct telem_t telem_t;

    #if defined(__BIT_VECTOR_MANAGER_ENABLE__) && defined(__MEMORY_POOL_MANAGER_ENABLE__)
      //! Memory Pool: Untyped Elements
      /*!
        Memory pool creation of untyped elements.
      */
      newMemoryPool(mpTypedElement, sizeof(telem_t), __UNTYPED_LIST_TYPED_ELEMENT_POOL_SIZE__);
    #endif

    //! Function: Untyped List Data Inserter
    /*!
      Insert a data on a typed list.
      \param ulList is a untyped_list_t variable. It's your typed list.
      \param vpData is a void pointer. This parameter is the data that will be saved.
      \param ui8DataSize is a 8-bit integer
      \param ui16Position is a 16-bit integer. This parameter refers to the position of the list in which the data will be saved.
      \return Returns UNTYPED_LIST_STATUS_DATA_NOT_ADDED or UNTYPED_LIST_STATUS_DATA_ADDED.
    */
    untyped_list_status_t UntypedList_insert(untyped_list_t ulList, void* vpData, uint8_t ui8DataSize, uint16_t ui16Position){
      if (ui8DataSize == 0 || ui16Position > ulList->ui16ListSize || vpData == NULL){
        return UNTYPED_LIST_STATUS_DATA_NOT_ADDED;
      }
      else{

        #if defined(__BIT_VECTOR_MANAGER_ENABLE__) && defined(__MEMORY_POOL_MANAGER_ENABLE__)
          telem_t* tepNewElement = (telem_t*) MemoryPool_malloc(mpTypedElement, 1);
        #else
          telem_t* tepNewElement = (telem_t*) malloc(sizeof(telem_t));
        #endif

        if(tepNewElement == NULL){
          return UNTYPED_LIST_STATUS_DATA_NOT_ADDED;
        }

        #if defined(__BIT_VECTOR_MANAGER_ENABLE__) && defined(__MEMORY_POOL_MANAGER_ENABLE__)
          tepNewElement->vpData = DataBank_malloc(ui8DataSize, 1);
        #else
          tepNewElement->vpData = malloc(ui8DataSize);
        #endif

        if (tepNewElement->vpData == NULL){
          return UNTYPED_LIST_STATUS_DATA_NOT_ADDED;
        }
        if (vpData != NULL){
          memcpy(tepNewElement->vpData, vpData, ui8DataSize);
        }
        else{
          memset(tepNewElement->vpData, 0, ui8DataSize);
        }
        tepNewElement->ui8DataSize = ui8DataSize;

        telem_t* tepBuffer = ulList->tepStart;
        if (ui16Position == 0){
          tepNewElement->tepNext = ulList->tepStart;
          ulList->tepStart = tepNewElement;
        }
        else{
          uint16_t ui16Counter = 0;
          for (ui16Counter = 1; ui16Counter != ui16Position; ui16Counter++){
            tepBuffer = tepBuffer->tepNext;
          }
          telem_t* tepBufferpNext = tepBuffer->tepNext;
          tepBuffer->tepNext = tepNewElement;
          tepNewElement->tepNext = tepBufferpNext;
        }
        ulList->ui16ListSize++;
        return UNTYPED_LIST_STATUS_DATA_ADDED;
      }
    }

    //! Function: List Data Remover
    /*!
      Remove a data from list.
      \param ulList is a untyped_list_t variable. It's your typed list.
      \param ui16Position is a 8-Bit integer. This parameter refers to the position of the list in which the data will be saved.
      \return Returns UNTYPED_LIST_STATUS_DATA_NOT_REMOVED or UNTYPED_LIST_STATUS_DATA_REMOVED.
    */
    untyped_list_status_t UntypedList_remove(untyped_list_t ulList, uint16_t ui16Position){
      if (ui16Position >= ulList->ui16ListSize){
        return UNTYPED_LIST_STATUS_DATA_NOT_REMOVED;
      }
      telem_t* tepBuffer = ulList->tepStart;
      if (ui16Position == 0){
        ulList->tepStart = tepBuffer->tepNext;
      }
      else {
        telem_t* tepNextElement = tepBuffer->tepNext;
        uint16_t ui16Counter = 0;
        for (ui16Counter = 1; ui16Counter < ui16Position; ui16Counter++){
          tepBuffer = tepBuffer->tepNext;
          tepNextElement = tepBuffer->tepNext;
        }
        tepBuffer->tepNext = tepNextElement->tepNext;
        tepBuffer = tepNextElement;
      }

      #if defined(__BIT_VECTOR_MANAGER_ENABLE__) && defined(__MEMORY_POOL_MANAGER_ENABLE__)
        DataBank_free(&tepBuffer->vpData, tepBuffer->ui8DataSize, 1);
        if (tepBuffer->vpData != NULL){
          return UNTYPED_LIST_STATUS_DATA_NOT_REMOVED;
        }
        MemoryPool_free(mpTypedElement, &tepBuffer, 1);
        if (tepBuffer != NULL){
          return UNTYPED_LIST_STATUS_DATA_NOT_REMOVED;
        }
      #else
        free(tepBuffer->vpData);
        tepBuffer->vpData = NULL;
        free(tepBuffer);
        tepBuffer = NULL;
      #endif

      ulList->ui16ListSize--;
      return UNTYPED_LIST_STATUS_DATA_REMOVED;
    }

    //! Function: List Data Getter
    /*!
      Get list data.
      \param ulList is a untyped_list_t variable. It's your typed list.
      \param ui16Position is a 8-Bit integer. This parameter refers to the position of the list in which the data will be saved.
      \return Returns addres list data.
    */
    void* (UntypedList_getDataAddress)(untyped_list_t ulList, uint16_t ui16Position){
      if (ui16Position >= ulList->ui16ListSize){
        return NULL;
      }
      telem_t* tepBuffer = ulList->tepStart;
      uint16_t ui16Counter = 0;
      for (ui16Counter = 0; ui16Counter != ui16Position; ui16Counter++){
        tepBuffer = tepBuffer->tepNext;
      }
      return tepBuffer->vpData;
    }

    //! Function: List Data Getter
    /*!
      Get list data.
      \param ulList is a typed_list_t variable. It's your typed list.
      \param ui16Position is a 16-bit integer. This parameter refers to the position of the list in which the data will be saved.
      \return Returns addres list data.
    */
    uint8_t UntypedList_getDataSize(untyped_list_t ulList, uint16_t ui16Position){
      if (ulList->ui16ListSize == 0){
        return 0;
      }
      telem_t* tepBuffer = ulList->tepStart;
      uint16_t ui16Counter = 0;
      for (ui16Counter = 0; ui16Counter < ui16Position; ui16Counter++){
        tepBuffer = tepBuffer->tepNext;
      }
      return tepBuffer->ui8DataSize;
    }

    //! Function: List Free Space
    /*!
      Get then free space of list memory pools.
      \return Returns free space of list memory pools.
    */
    uint16_t UntypedList_getFreeSpace(void){
      #if defined(__BIT_VECTOR_MANAGER_ENABLE__) && defined(__MEMORY_POOL_MANAGER_ENABLE__)
        return MemoryPool_getFreeSpace(mpTypedElement);
      #else
        return 0;
      #endif
    }

  #else
    #error Invalid __UNTYPED_LIST_TYPED_ELEMENT_POOL_SIZE__ value!
  #endif

#endif
