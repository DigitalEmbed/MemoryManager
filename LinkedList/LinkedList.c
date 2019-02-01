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

#include "LinkedList.h"
#include "../MemoryPool/MemoryPool.h"

//! Type Definition: Untyped Linked List Element Structure
/*!
  Typed element struct for non-typed linked lists.
*/
struct telem_t{
  void* vpData;                                                                                       /*!< Pointer void type. */
  struct telem_t* tepNext;                                                                            /*!< Pointer telem_t type. */
  uint8_t ui8Size;                                                                                    /*!< 8-bits integer type. */
};

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
typedef struct telem_t telem_t;

//! Memory Pool: Untyped Elements
/*!
  Memory pool creation of untyped elements.
*/
xCreatePool(mpUntypedElement, uelem_t, NUMBER_OF_UNTYPED_ELEMENT);

//! Memory Pool: Typed Elements
/*!
  Memory pool creation of typed elements.
*/
xCreatePool(mpTypedElement, telem_t, NUMBER_OF_TYPED_ELEMENT);

//! Memory Pool: List
/*!
  Memory pool creation of linked lists.
*/
xCreatePool(mpList, list_t, NUMBER_OF_LISTS);

//! Function: List Initializer
/*!
  Initialize linked list memory pools.
  \return Returns LIST_INIT_SUCESS or LIST_INIT_ERROR.
*/
uint8_t ui8InitList(){
  if (ui8PoolInit(mpUntypedElement) == MEMORYPOOL_INIT_ERROR){
    return LIST_INIT_ERROR;
  }
  if (ui8PoolInit(mpTypedElement) == MEMORYPOOL_INIT_ERROR){
    return LIST_INIT_ERROR;
  }
  if (ui8PoolInit(mpList) == MEMORYPOOL_INIT_ERROR){
    return LIST_INIT_ERROR;
  }
  return LIST_INIT_SUCESS;
}

//! Function: Typed List Creator
/*!
  Create a untyped list.
  \param ui8DataSize is a 8-Bit integer. This parameter is the size of the list data.
*/
list_t* lpCreateTypedList(uint8_t ui8DataSize){
  list_t* lBuffer = (list_t*) vpMPAlloc(&mpList, 1);
  if (lBuffer != NULL){
    lBuffer->ui8DataSize = ui8DataSize;
    lBuffer->ui16ListSize = 0;
    lBuffer->uepStart = NULL;
    lBuffer->tepStart = NULL;
  }
  return lBuffer;
}

//! Function: Untyped List Creator
/*!
  Create a untyped list.
*/
list_t* lpCreateUntypedList(){
  list_t* lBuffer = (list_t*) vpMPAlloc(&mpList, 1);
  if (lBuffer != NULL){
    lBuffer->ui8DataSize = 0;
    lBuffer->ui16ListSize = 0;
    lBuffer->uepStart = NULL;
    lBuffer->tepStart = NULL;
  }
  return lBuffer;
}

//! Function: List Deleter
/*!
  Delete a list.
  \param lpList is a pointer to list_t pointer. This parameter is the address of pointer of list.
  \return Returns DATA_NOT_ADDED or DATA_ADDED.
*/
void vDeleteList(list_t** lpList){
  while((**lpList).ui16ListSize > 0){
    ui8RemoveFromList(*lpList, 0);
  }
  vMPFree(&mpList, (void**) lpList, 1);
}

//! Function: Typed List Data Inserter
/*!
  Insert a data on a typed list.
  \param lpList is a list_t pointer. This parameter is the address of list.
  \param vpData is a void pointer. This parameter is the data that will be saved.
  \param ui16Position is a 8-Bit integer. This parameter refers to the position of the list in which the data will be saved.
  \return Returns DATA_NOT_ADDED or DATA_ADDED.
*/
uint8_t ui8AddOnTypedList(list_t* lpList, void* vpData, uint16_t ui16Position){
  if (lpList->ui8DataSize == 0 || ui16Position > lpList->ui16ListSize || vpData == NULL){
    return DATA_NOT_ADDED;
  }
  else{
    uelem_t* uepNewElement = (uelem_t*) vpMPAlloc(&mpUntypedElement, 1);
    if(uepNewElement == NULL){
      return DATA_NOT_ADDED;
    }
    uepNewElement->vpData = vpDBAlloc(lpList->ui8DataSize, 1);
    if (uepNewElement->vpData == NULL){
      return DATA_NOT_ADDED;
    }
    memcpy(uepNewElement->vpData, vpData, lpList->ui8DataSize);
    uelem_t* uepBuffer = lpList->uepStart;
    if (ui16Position == 0){
      uepNewElement->uepNext = lpList->uepStart;
      lpList->uepStart = uepNewElement;
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
    lpList->ui16ListSize++;
    return DATA_ADDED;
  }
}

//! Function: Untyped List Data Inserter
/*!
  Insert a data on a untyped list.
  \param lpList is a list_t pointer. This parameter is the address of list.
  \param vpData is a void pointer. This parameter is the data that will be saved.
  \param ui8DataSize is a 8-Bit integer. This parameter is the size of the list data.
  \param ui16Position is a 8-Bit integer. This parameter refers to the position of the list in which the data will be saved.
  \return Returns DATA_NOT_ADDED or DATA_ADDED.
*/
uint8_t ui8AddOnUntypedList(list_t* lpList, void* vpData, uint8_t ui8DataSize, uint16_t ui16Position){
  if (ui8DataSize == 0 || ui16Position > lpList->ui16ListSize || vpData == NULL){
    return DATA_NOT_ADDED;
  }
  else{
    telem_t* tepNewElement = (telem_t*) vpMPAlloc(&mpTypedElement, 1);
    if(tepNewElement == NULL){
      return DATA_NOT_ADDED;
    }
    tepNewElement->vpData = vpDBAlloc(ui8DataSize, 1);
    if (tepNewElement->vpData == NULL){
      return DATA_NOT_ADDED;
    }
    tepNewElement->ui8Size = ui8DataSize; //NESSA LINHA DA PAU
    memcpy(tepNewElement->vpData, vpData, ui8DataSize); //NESSA LINHA DA PAU
    telem_t* tepBuffer = lpList->tepStart;
    if (ui16Position == 0){
      tepNewElement->tepNext = lpList->tepStart;
      lpList->tepStart = tepNewElement;
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
    lpList->ui16ListSize++;
    return DATA_ADDED;
  }
}

//! Function: List Data Remover
/*!
  Remove a data from list.
  \param lpList is a list_t pointer. This parameter is the address of list.
  \param ui16Position is a 8-Bit integer. This parameter refers to the position of the list in which the data will be saved.
  \return Returns DATA_NOT_REMOVED or DATA_REMOVED.
*/
uint8_t ui8RemoveFromList(list_t* lpList, uint16_t ui16Position){
  if (ui16Position >= lpList->ui16ListSize){
    return DATA_NOT_REMOVED;
  }
  else{
    if(lpList->ui8DataSize != 0){
      uelem_t* uepBuffer = lpList->uepStart;
      if (ui16Position == 0){
        lpList->uepStart = uepBuffer->uepNext;
        vDBFree(&uepBuffer->vpData, lpList->ui8DataSize, 1);
        if (uepBuffer->vpData != NULL){
          return DATA_NOT_REMOVED;
        }
        vMPFree(&mpUntypedElement, (void**) &uepBuffer, 1);
        if (uepBuffer != NULL){
          return DATA_NOT_REMOVED;
        }
      }
      else {
        uelem_t* uepNextElement = uepBuffer->uepNext;
        uint16_t ui16Counter = 0;
        for (ui16Counter = 1; ui16Counter < ui16Position; ui16Counter++){
          uepBuffer = uepBuffer->uepNext;
          uepNextElement = uepBuffer->uepNext;
        }
        uepBuffer->uepNext = uepNextElement->uepNext;
        vDBFree(&uepBuffer->vpData, lpList->ui8DataSize, 1);
        if (uepNextElement->vpData != NULL){
          return DATA_NOT_REMOVED;
        }
        vMPFree(&mpUntypedElement, (void**) &uepBuffer, 1);
        if (uepNextElement != NULL){
          return DATA_NOT_REMOVED;
        }
      }
      lpList->ui16ListSize--;
      return DATA_REMOVED;
    }
    else{
      telem_t* tepBuffer = lpList->tepStart;
      if (ui16Position == 0){
        lpList->tepStart = tepBuffer->tepNext;
        vDBFree(&tepBuffer->vpData, tepBuffer->ui8Size, 1);
        if (tepBuffer->vpData != NULL){
          return DATA_NOT_REMOVED;
        }
        vMPFree(&mpTypedElement, (void**) &tepBuffer, 1);
        if (tepBuffer != NULL){
          return DATA_NOT_REMOVED;
        }
      }
      else {
        telem_t* tepNextElement = tepBuffer->tepNext;
        for (uint16_t ui16Contador = 1; ui16Contador < ui16Position; ui16Contador++){
          tepBuffer = tepBuffer->tepNext;
          tepNextElement = tepBuffer->tepNext;
        }
        tepBuffer->tepNext = tepNextElement->tepNext;
        vDBFree(&tepBuffer->vpData, tepBuffer->ui8Size, 1);
        if (tepNextElement->vpData != NULL){
          return DATA_NOT_REMOVED;
        }
        vMPFree(&mpTypedElement, (void**) &tepBuffer, 1);
        if (tepNextElement != NULL){
          return DATA_NOT_REMOVED;
        }
      }
      lpList->ui16ListSize--;
      return DATA_REMOVED;
    }
  }
}

//! Function: List Data Getter
/*!
  Get data of list.
  \param lpList is a 8-Bit integer. This parameter indicates the type of query you want to know. Use the TYPED, UNTYPED, or LIST macros..
  \param ui16Position is a 8-Bit integer. This parameter refers to the position of the list in which the data will be saved.
  \return Returns data of list.
*/
void* vpGetElement(list_t* lpList, uint16_t ui16Position){
  if (ui16Position >= lpList->ui16ListSize){
    return NULL;
  }
  else{
    if (lpList->ui8DataSize == 0){
      telem_t* tepBuffer = lpList->tepStart;
      uint16_t ui16Counter = 0;
      for (ui16Counter = 0; ui16Counter != ui16Position; ui16Counter++){
        tepBuffer = tepBuffer->tepNext;
      }
      return tepBuffer->vpData;
    }
    else{
      uelem_t* uepBuffer = lpList->uepStart;
      uint16_t ui16Counter = 0;
      for (ui16Counter = 0; ui16Counter != ui16Position; ui16Counter++){
        uepBuffer = uepBuffer->uepNext;
      }
      return uepBuffer->vpData;
    }
  }
}

//! Function: List Data Size
/*!
  Get data size of one element of list.
  \param lpList is a list_t pointer. This parameter is the address of list.
  \param ui16Position is a 8-Bit integer. This parameter refers to the position of the list in which the data will be saved.
  \return Returns data size of one element of list.
*/
uint8_t ui8GetListDataSize(list_t *lpList, uint16_t ui16Position){
  if (lpList->ui8DataSize == 0){
    if (lpList->ui16ListSize == 0){
      return 0;
    }
    telem_t* tepBuffer = lpList->tepStart;
    uint16_t ui16Contador = 0;
    for (ui16Contador = 0; ui16Contador < ui16Position; ui16Contador++){
      tepBuffer = tepBuffer->tepNext;
    }
    return tepBuffer->ui8Size;
  }
  else{
    return lpList->ui8DataSize;
  }
}

//! Function: List Size
/*!
  Get list size.
  \param lpList is a list_t pointer. This parameter is the address of list.
  \return Returns list size.
*/
uint16_t ui16GetListSize(list_t *lpList){
  return lpList->ui16ListSize;
}

//! Function: List Free Space
/*!
  Get then free space of list memory pools.
  \param lpList is a 8-Bit integer. This parameter indicates the type of query you want to know. Use the TYPED, UNTYPED, or LIST macros..
  \return Returns free space of list memory pools.
*/
uint16_t ui16GetListFreeSpace(uint8_t ui8QueryType){
  if (ui8QueryType == TYPED){
    return ui16MPGetFreeSpace(&mpTypedElement);
  }
  else if(ui8QueryType == UNTYPED){
    return ui16MPGetFreeSpace(&mpUntypedElement);
  }
  else if(ui8QueryType == LIST){
    return ui16MPGetFreeSpace(&mpList);
  }
  else{
    return 0;
  }
}
