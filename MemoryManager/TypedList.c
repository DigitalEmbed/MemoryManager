#include "./Configs.h"

#if (defined(__TYPED_LIST_MANAGER_ENABLE__))

  #if ((defined(__TYPED_LIST_MANAGER_ENABLE__) && (!defined(__BIT_VECTOR_MANAGER_ENABLE__) || !defined(__MEMORY_POOL_MANAGER_ENABLE__)))\
  ||((defined(__TYPED_LIST_MANAGER_ENABLE__) && defined(__TYPED_LIST_UNTYPED_ELEMENT_POOL_SIZE__) && (__TYPED_LIST_UNTYPED_ELEMENT_POOL_SIZE__ > 0))))

    #include "./TypedList.h"
    #include "./MemoryPool.h"
    #include "./DataBank.h"
    #include <string.h>

    #if !defined(__BIT_VECTOR_MANAGER_ENABLE__) || !defined(__MEMORY_POOL_MANAGER_ENABLE__)
      #include <stdlib.h>
    #endif

    //! Type Definition: Typed Linked List Element Structure
    /*!
      Non-typed element struct for typed linked lists.
    */
    struct uelem_t{
      void* vpData;                                                                                       /*!< Pointer void type. */
      struct uelem_t* uepNext;                                                                            /*!< Pointer uelem_t type. */
    };

    //! Type Definition: uelem_t and telem_t
    /*!
      This typedef is for facilitate the use of lList library.
    */
    typedef struct uelem_t uelem_t;

    #if defined(__BIT_VECTOR_MANAGER_ENABLE__) && defined(__MEMORY_POOL_MANAGER_ENABLE__)
      //! Memory Pool: Untyped Elements
      /*!
        Memory pool creation of untyped elements.
      */
      newMemoryPool(mpUntypedElement, sizeof(uelem_t), __TYPED_LIST_UNTYPED_ELEMENT_POOL_SIZE__);
    #endif

    //! Function: Typed List Data Inserter
    /*!
      Insert a data on a typed list.
      \param tlList is a typed_list_t variable. It's your typed list.
      \param vpData is a void pointer. This parameter is the data that will be saved.
      \param ui16Position is a 16-bit integer. This parameter refers to the position of the list in which the data will be saved.
      \return Returns TYPED_LIST_STATUS_DATA_NOT_ADDED or TYPED_LIST_STATUS_DATA_ADDED.
    */
    typed_list_status_t TypedList_insert(typed_list_t tlList, void* vpData, uint16_t ui16Position){
      if (tlList->ui8DataSize == 0 || ui16Position > tlList->ui16ListSize || vpData == NULL){
        return TYPED_LIST_STATUS_DATA_NOT_ADDED;
      }
      else{

        #if defined(__BIT_VECTOR_MANAGER_ENABLE__) && defined(__MEMORY_POOL_MANAGER_ENABLE__)
          uelem_t* uepNewElement = (uelem_t*) MemoryPool_malloc(mpUntypedElement, 1);
        #else
          uelem_t* uepNewElement = (uelem_t*) malloc(sizeof(uelem_t));
        #endif

        if(uepNewElement == NULL){
          return TYPED_LIST_STATUS_DATA_NOT_ADDED;
        }

        #if defined(__BIT_VECTOR_MANAGER_ENABLE__) && defined(__MEMORY_POOL_MANAGER_ENABLE__)
          uepNewElement->vpData = DataBank_malloc(tlList->ui8DataSize, 1);
        #else
          uepNewElement->vpData = malloc(tlList->ui8DataSize);
        #endif

        if (uepNewElement->vpData == NULL){
          return TYPED_LIST_STATUS_DATA_NOT_ADDED;
        }
        if (vpData != NULL){
          memcpy(uepNewElement->vpData, vpData, tlList->ui8DataSize);
        }
        else{
          memset(uepNewElement->vpData, 0, tlList->ui8DataSize);
        }
        uelem_t* uepBuffer = tlList->uepStart;
        if (ui16Position == 0){
          uepNewElement->uepNext = tlList->uepStart;
          tlList->uepStart = uepNewElement;
        }
        else{
          uint16_t ui16Counter = 0;
          for (ui16Counter = 1; ui16Counter != ui16Position; ui16Counter++){
            uepBuffer = uepBuffer->uepNext;
          }
          uelem_t* uepBufferpNext = uepBuffer->uepNext;
          uepBuffer->uepNext = uepNewElement;
          uepNewElement->uepNext = uepBufferpNext;
        }
        tlList->ui16ListSize++;
        return TYPED_LIST_STATUS_DATA_ADDED;
      }
    }

    //! Function: List Data Remover
    /*!
      Remove a data from list.
      \param tlList is a typed_list_t variable. It's your typed list.
      \param ui16Position is a 16-bit integer. This parameter refers to the position of the list in which the data will be saved.
      \return Returns TYPED_LIST_STATUS_DATA_NOT_REMOVED or TYPED_LIST_STATUS_DATA_REMOVED.
    */
    typed_list_status_t TypedList_remove(typed_list_t tlList, uint16_t ui16Position){
      if (ui16Position >= tlList->ui16ListSize){
        return TYPED_LIST_STATUS_DATA_NOT_REMOVED;
      }
      if(tlList->ui8DataSize != 0){
        uelem_t* uepBuffer = tlList->uepStart;
        if (ui16Position == 0){
          tlList->uepStart = uepBuffer->uepNext;
        }
        else {
          uelem_t* uepNextElement = uepBuffer->uepNext;
          uint16_t ui16Counter = 0;
          for (ui16Counter = 1; ui16Counter < ui16Position; ui16Counter++){
            uepBuffer = uepBuffer->uepNext;
            uepNextElement = uepBuffer->uepNext;
          }
          uepBuffer->uepNext = uepNextElement->uepNext;
          uepBuffer = uepNextElement;
        }

        #if defined(__BIT_VECTOR_MANAGER_ENABLE__) && defined(__MEMORY_POOL_MANAGER_ENABLE__)
          DataBank_free(&uepBuffer->vpData, tlList->ui8DataSize, 1);
          if (uepBuffer->vpData != NULL){
            return TYPED_LIST_STATUS_DATA_NOT_REMOVED;
          }
          MemoryPool_free(mpUntypedElement, &uepBuffer, 1);
          if (uepBuffer != NULL){
            return TYPED_LIST_STATUS_DATA_NOT_REMOVED;
          }
        #else
          free(uepBuffer->vpData);
          uepBuffer->vpData = NULL;
          free(uepBuffer);
          uepBuffer = NULL;
        #endif

        tlList->ui16ListSize--;
        return TYPED_LIST_STATUS_DATA_REMOVED;
      }
      return TYPED_LIST_STATUS_DATA_NOT_REMOVED;
    }

    //! Function: List Data Getter
    /*!
      Get list data.
      \param tlList is a typed_list_t variable. It's your typed list.
      \param ui16Position is a 16-bit integer. This parameter refers to the position of the list in which the data will be saved.
      \return Returns addres list data.
    */
    void* (TypedList_getDataAddress)(typed_list_t tlList, uint16_t ui16Position){
      if (ui16Position >= tlList->ui16ListSize){
        return NULL;
      }
      uelem_t* uepBuffer = tlList->uepStart;
      uint16_t ui16Counter = 0;
      for (ui16Counter = 0; ui16Counter != ui16Position; ui16Counter++){
        uepBuffer = uepBuffer->uepNext;
      }
      return uepBuffer->vpData;
    }

    //! Function: List Free Space
    /*!
      Get then free space of list memory pools.
      \return Returns free space of list memory pools.
    */
    uint16_t TypedList_getFreeSpace(void){
      #if defined(__BIT_VECTOR_MANAGER_ENABLE__) && defined(__MEMORY_POOL_MANAGER_ENABLE__)
        return MemoryPool_getFreeSpace(mpUntypedElement);
      #else
        return 0;
      #endif
    }

  #else
    #error Invalid __TYPED_LIST_UNTYPED_ELEMENT_POOL_SIZE__ value!
  #endif

#endif
