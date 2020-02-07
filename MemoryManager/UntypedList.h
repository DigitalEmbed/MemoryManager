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

#ifndef __UNTYPED_LIST_HEADER__
  #define __UNTYPED_LIST_HEADER__

  #include "./Configs.h"

  #if defined(__UNTYPED_LIST_MANAGER_ENABLE__)
  
    #ifdef __cplusplus
      extern "C" {
    #endif

    #include <stdint.h>

    //! Structure: Typed Linked List
    /*!
      Typed linked list structure.
    */
    struct untyped_list_structure_t{
      uint16_t ui16ListSize;                                /*!< 16-bit integer type. */
      struct telem_t* tepStart;                             /*!< telem_t pointer type. */
    };

    //! Enumeration Definition: Typed List Status
    /*!
      This typedef is for facilitate the use of this library.
    */
    typedef enum {
      UNTYPED_LIST_STATUS_DATA_NOT_ADDED = 0,
      UNTYPED_LIST_STATUS_DATA_ADDED,
      UNTYPED_LIST_STATUS_DATA_NOT_REMOVED,
      UNTYPED_LIST_STATUS_DATA_REMOVED
    } untyped_list_status_t;

    //! Type Definition: list_t.
    /*!
      This typedef is for facilitate the use of this library.
    */
    typedef struct untyped_list_structure_t* untyped_list_t;

    //! Macro: Typed List Constructor
    /*!
      Constructes a typed list.
      \param ulListName is a name for your typed list.
    */
    #define newUntypedList(ulListName)\
      struct untyped_list_structure_t __tlsListStructure##ulListName = {\
        .ui16ListSize = 0,\
        .tepStart = NULL\
      };\
      untyped_list_t ulListName = &__tlsListStructure##ulListName;\

    //! Macro: Static Typed List Constructor
    /*!
      Constructes a static typed list.
      \param ulListName is a name for your typed list.
    */
    #define newStaticUntypedList(ulListName)\
      static struct untyped_list_structure_t __tlsListStructure##ulListName = {\
        .ui16ListSize = 0,\
        .tepStart = NULL\
      };\
      static untyped_list_t ulListName = &__tlsListStructure##ulListName;\

    //! Macro: List Eraser
    /*!
      Clear all list content.
      \param ulList is a untyped_list_t variable. It's your typed list.
    */
    #define UntypedList_clear(ulList)\
      while(ulList->ui16ListSize > 0){\
        UntypedList_remove(ulList, 0);\
      }

    //! Macro: List Size
    /*!
      Get list size.
      \param ulList is a untyped_list_t variable. It's your typed list.
      \return Returns list size.
    */
    #define UntypedList_getListSize(ulList)\
      (ulList->ui16ListSize)

    //! Function: Address List Data Getter
    /*!
      Get list data.
      \param ulList is a untyped_list_t variable. It's your typed list.
      \param xDataType is the type of data list.
      \param ui16Position is a 8-Bit integer. This parameter refers to the position of the list in which the data will be saved.
      \return Returns addres list data.
    */
    #define UntypedList_getDataAddress(ulList, xDataType, ui16Position)\
      ((xDataType*) UntypedList_getDataAddress(ulList, ui16Position))

    //! Function: List Data Getter
    /*!
      Get list data. You can use this macro if you are ignoring 0 value in your list. In contrary case, you should use UntypedList_getDataAddress.
      \param ulList is a untyped_list_t variable. It's your typed list.
      \param xDataType is the type of data list.
      \param ui16Position is a 8-Bit integer. This parameter refers to the position of the list in which the data will be saved.
      \return Returns addres list data.
    */
    #define UntypedList_getData(ulList, xDataType, ui16Position)\
      ((UntypedList_getListSize(ulList) > ui16Position) ?\
        (*(UntypedList_getDataAddress(ulList, xDataType, ui16Position))) :\
        0)

    //! Function: Typed List Data Start Inserter
    /*!
      Insert a data at the beginning of a typed list.
      \param ulList is a untyped_list_t variable. It's your typed list.
      \param xDataType is the type of data list.
      \param vpData is a void pointer. This parameter is the data that will be saved.
      \return Returns UNTYPED_LIST_STATUS_DATA_NOT_ADDED or UNTYPED_LIST_STATUS_DATA_ADDED.
    */
    #define UntypedList_insertStart(ulList, xDataType, vpData)\
      UntypedList_insert(ulList, sizeof(xDataType), vpData, 0)

    //! Function: Typed List Data End Inserter
    /*!
      Insert a data at the end of a typed list.
      \param ulList is a untyped_list_t variable. It's your typed list.
      \param vpData is a void pointer. This parameter is the data that will be saved.
      \return Returns UNTYPED_LIST_STATUS_DATA_NOT_ADDED or UNTYPED_LIST_STATUS_DATA_ADDED.
    */
    #define UntypedList_insertEnd(ulList, xDataType, vpData)\
      UntypedList_insert(ulList, sizeof(xDataType), vpData, UntypedList_getListSize(ulList))

    void* (UntypedList_getDataAddress)(untyped_list_t ulList, uint16_t ui16Position);                                                       /*!< void pointer type function. */
    untyped_list_status_t UntypedList_insert(untyped_list_t ulList, void* vpData, uint8_t ui8DataSize, uint16_t ui16Position);              /*!< untyped_list_status_t integer type function. */
    untyped_list_status_t UntypedList_remove(untyped_list_t ulList, uint16_t ui16Position);                                                 /*!< untyped_list_status_t integer type function. */
    uint8_t UntypedList_getDataSize(untyped_list_t ulList, uint16_t ui16Position);                                                          /*!< 8-bits integer type function. */
    uint16_t UntypedList_getFreeSpace(void);                                                                                                /*!< 16-bits integer type function. */

    #ifdef __cplusplus
      }
    #endif
  
  #endif
#endif
