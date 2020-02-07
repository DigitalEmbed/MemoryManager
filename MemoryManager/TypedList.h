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

#ifndef __TYPED_LIST_HEADER__
  #define __TYPED_LIST_HEADER__

  #include "./Configs.h"

  #if defined(__TYPED_LIST_MANAGER_ENABLE__)
  
    #ifdef __cplusplus
      extern "C" {
    #endif

    #include <stdint.h>

    //! Structure: Typed Linked List
    /*!
      Typed linked list structure.
    */
    struct typed_list_structure_t{
      uint8_t ui8DataSize;                                  /*!< 8-bit integer type. */
      uint16_t ui16ListSize;                                /*!< 16-bit integer type. */
      struct uelem_t* uepStart;                             /*!< uelem_t pointer type. */
    };

    //! Enumeration Definition: Typed List Status
    /*!
      This typedef is for facilitate the use of this library.
    */
    typedef enum {
      TYPED_LIST_STATUS_DATA_NOT_ADDED = 0,
      TYPED_LIST_STATUS_DATA_ADDED,
      TYPED_LIST_STATUS_DATA_NOT_REMOVED,
      TYPED_LIST_STATUS_DATA_REMOVED
    } typed_list_status_t;

    //! Type Definition: list_t.
    /*!
      This typedef is for facilitate the use of this library.
    */
    typedef struct typed_list_structure_t* typed_list_t;

    //! Macro: Typed List Constructor
    /*!
      Constructes a typed list.
      \param tlListName is a name for your typed list.
      \param xDataType is the type of data list.
    */
    #define newTypedList(tlListName, xDataType)\
      struct typed_list_structure_t __tlsListStructure##tlListName = {\
        .ui8DataSize = sizeof(xDataType),\
        .ui16ListSize = 0,\
        .uepStart = NULL\
      };\
      typed_list_t tlListName = &__tlsListStructure##tlListName;\

    //! Macro: Static Typed List Constructor
    /*!
      Constructes a static typed list.
      \param tlListName is a name for your typed list.
      \param xDataType is the type of data list.
    */
    #define newStaticTypedList(tlListName, xDataType)\
      static struct typed_list_structure_t __tlsListStructure##tlListName = {\
        .ui8DataSize = sizeof(xDataType),\
        .ui16ListSize = 0,\
        .uepStart = NULL\
      };\
      static typed_list_t tlListName = &__tlsListStructure##tlListName;\

    //! Macro: List Data Size
    /*!
      Get data list element size.
      \param tlList is a typed_list_t variable. It's your typed list.
      \return Returns data size of one element of list.
    */
    #define TypedList_getDataSize(tlList)\
      (tlList->ui8DataSize)

    //! Macro: List Size
    /*!
      Get list size.
      \param tlList is a typed_list_t variable. It's your typed list.
      \return Returns list size.
    */
    #define TypedList_getListSize(tlList)\
      (tlList->ui16ListSize)

    //! Function: Address List Data Getter
    /*!
      Get list data.
      \param tlList is a typed_list_t variable. It's your typed list.
      \param xDataType is the type of data list.
      \param ui16Position is a 8-Bit integer. This parameter refers to the position of the list in which the data will be saved.
      \return Returns addres list data.
    */
    #define TypedList_getDataAddress(tlList, xDataType, ui16Position)\
      ((xDataType*) TypedList_getDataAddress(tlList, ui16Position))

    //! Function: List Data Getter
    /*!
      Get list data. You can use this macro if you are ignoring 0 value in your list. In contrary case, you should use TypedList_getDataAddress.
      \param tlList is a typed_list_t variable. It's your typed list.
      \param xDataType is the type of data list.
      \param ui16Position is a 8-Bit integer. This parameter refers to the position of the list in which the data will be saved.
      \return Returns addres list data.
    */
    #define TypedList_getData(tlList, xDataType, ui16Position)\
      ((TypedList_getListSize(tlList) > ui16Position) ?\
        (*(TypedList_getDataAddress(tlList, xDataType, ui16Position))) :\
        0)

    //! Function: Typed List Data Start Inserter
    /*!
      Insert a data at the beginning of a typed list.
      \param tlList is a typed_list_t variable. It's your typed list.
      \param vpData is a void pointer. This parameter is the data that will be saved.
      \return Returns TYPED_LIST_STATUS_DATA_NOT_ADDED or TYPED_LIST_STATUS_DATA_ADDED.
    */
    #define TypedList_insertStart(tlList, vpData)\
      TypedList_insert(tlList, vpData, 0)

    //! Function: Typed List Data End Inserter
    /*!
      Insert a data at the end of a typed list.
      \param tlList is a typed_list_t variable. It's your typed list.
      \param vpData is a void pointer. This parameter is the data that will be saved.
      \return Returns TYPED_LIST_STATUS_DATA_NOT_ADDED or TYPED_LIST_STATUS_DATA_ADDED.
    */
    #define TypedList_insertEnd(tlList, vpData)\
      TypedList_insert(tlList, vpData, TypedList_getListSize(tlList))

    //! Macro: List Eraser
    /*!
      Clear all list content.
      \param tlList is a typed_list_t variable. It's your typed list.
    */
    #define TypedList_clear(tlList)\
      while(TypedList_getListSize(tlList) > 0){\
        TypedList_remove(tlList, 0);\
      }

    void* (TypedList_getDataAddress)(typed_list_t tlList, uint16_t ui16Position);                               /*!< void pointer type function. */
    typed_list_status_t TypedList_insert(typed_list_t tlList, void* vpData, uint16_t ui16Position);             /*!< typed_list_status_t integer type function. */
    typed_list_status_t TypedList_remove(typed_list_t tlList, uint16_t ui16Position);                           /*!< typed_list_status_t integer type function. */
    uint16_t TypedList_getFreeSpace(void);                                                                      /*!< 16-bits integer type function. */

    #ifdef __cplusplus
      }
    #endif
  
  #endif
#endif
