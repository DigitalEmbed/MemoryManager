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

#ifndef LinkedList_H
#define LinkedList_H

#ifdef __cplusplus
  extern "C" {
#endif

#include <inttypes.h>
#include <stdio.h>
#include "../DataBank/DataBank.h"

//! Macros: List Configurations
/*!
  These macros are for the list manager's working settings.
*/
#ifndef NUMBER_OF_LISTS
  #define   NUMBER_OF_LISTS               20
#endif

#ifndef NUMBER_OF_TYPED_ELEMENT
  #define   NUMBER_OF_TYPED_ELEMENT       60
#endif

#ifndef NUMBER_OF_UNTYPED_ELEMENT
  #define   NUMBER_OF_UNTYPED_ELEMENT     60
#endif

//! Macros: Types
/*!
  These macros leave the code more cleaner and understandable.
*/
#define   UNTYPED                         0
#define   TYPED                           1
#define   LIST                            2

//! Macros: Task Manager Status
/*!
  This macros leave the code more cleaner and understandable.
*/
#define   DATA_NOT_ADDED                  20
#define   DATA_ADDED                      21
#define   DATA_NOT_REMOVED                22
#define   DATA_REMOVED                    23
#define   LIST_INIT_ERROR                 24
#define   LIST_INIT_SUCESS                25

//! Structure: Linked List
/*!
  Linked list structure.
*/
struct list_t{
  uint8_t ui8DataSize;                    /*!< 8-bit integer type. */
  uint16_t ui16ListSize;                  /*!< 16-bit integer type. */
  struct uelem_t* uepStart;               /*!< uelem_t pointer type. */
  struct telem_t* tepStart;               /*!< uelem_t pointer type. */
};

//! Type Definition: list_t.
/*!
  This typedef is for facilitate the use of this library.
*/
typedef struct list_t list_t;

list_t* lpCreateUntypedList();                                                                          /*!< list_t pointer type function. */
list_t* lpCreateTypedList(uint8_t ui8DataSize);                                                         /*!< list_t pointer type function. */
void vDeleteList(list_t** lpList);                                                                      /*!< Void type function. */
uint8_t ui8ListManagerInit();                                                                           /*!< 8-bits integer type function. */
uint8_t ui8AddOnUntypedList(list_t* lpList, void* vpData, uint8_t ui8DataSize, uint16_t ui16Position);  /*!< 8-bits integer type function. */
uint8_t ui8AddOnTypedList(list_t* lpList, void* vpData, uint16_t ui16Position);                         /*!< 8-bits integer type function. */
uint8_t ui8RemoveFromList(list_t* lpList, uint16_t ui16Position);                                       /*!< 8-bits integer type function. */
uint8_t ui8GetListDataSize(list_t* lpList, uint16_t ui16Position);                                      /*!< 8-bits integer type function. */
uint16_t ui16GetListSize(list_t* lpList);                                                               /*!< 16-bits integer type function. */
uint16_t ui16GetListFreeSpace(uint8_t ui8ListType);                                                     /*!< 16-bits integer type function. */
void* vpGetElement(list_t* lpList, uint16_t ui16Position);                                              /*!< Void type pointer function. */

#ifdef __cplusplus
  }
#endif

#endif
