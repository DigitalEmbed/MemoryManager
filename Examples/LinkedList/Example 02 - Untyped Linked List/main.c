//! Example 02 - Untyped linked list
/*!
  This simply example demonstrates the use of untyped linked lists. The great 
  advantage of this list is that it makes it possible to save files of different 
  types. The problem is that when reading a certain data, the programming language 
  C can not recognize the type of this data, and this becomes a problem. This 
  example is only a possible resolution of this problem. The only disadvantage is 
  that, in a list, you can not store different types of data that have the same size 
  (Example: uint8_t, bool and char).

  Put the "Bits", "MemoryPool", "DataBank" and "LinkedList" library folder in 
  the same location as this file.

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

#include <stdio.h>
#include <inttypes.h>
#include "LinkedList/LinkedList.h"
#include "DataBank/DataBank.h"

/*!
  Declaration of a list_t type list.
*/
list_t* lpLinkedList;

/*!
  Function Scopes.
*/
uint8_t ui8AddChar(list_t* lpList, char cData, uint16_t ui16Position);                            /*!< 8-bit integer type function. */
uint8_t ui8AddInt(list_t* lpList, int32_t i32Data, uint16_t ui16Position);                        /*!< 8-bit integer type function. */
uint8_t ui8AddDouble(list_t* lpList, double dData, uint16_t ui16Position);                        /*!< 8-bit integer type function. */                                                                /*!< Void type function. */
void vListPrint(list_t* lpList, uint16_t ui16Position);                                           /*!< Void type function. */
void vPrintMemoryStatus();                                                                        /*!< Void type function. */

/*!
  Main function.
*/
int main(){
  /*!
    Initializing DataBank manager...
  */
  if (ui8DataBankInit() != DATABANK_INITIALIZED){                                                 /*!< If not possible data bank initialization... */
    printf("ERROR: Data Bank initialization error!");                                             /*!< Print an error message and returns 1 for the operational system. */
    return 1;                                                                                     /*!< You can treat the problem any way you want! */
  }
  
  /*!
    Initializing circular buffer manager...
  */
  if (ui8ListManagerInit() != LIST_INIT_SUCESS){                                                  /*!< If not possible circular buffer manager initialization... */
    printf("ERROR: Circular buffer manager initialization error!");                               /*!< Print an error message and returns 2 for the operational system. */
    return 2;                                                                                     /*!< You can treat the problem any way you want! */
  }
  printf("Memory Manager initialized... ");
  vPrintMemoryStatus();
  
  /*!
    Linked List creating...
  */
  lpLinkedList = lpCreateUntypedList();
  if (lpLinkedList == NULL){                                                                      /*!< If the pointer is NULL... */
    printf("ERROR: Linked list creation error!\n");                                               /*!< Print an error message and returns 1 for the operational system. */
    return 1;                                                                                     /*!< You can treat the problem any way you want! */
  }
  
  /*!
    Inserting data on Linked List...
  */
  char cTest = 'a';
  int32_t i32Test = -10;
  double dTest = 3.14;
  uint8_t ui8Counter = 0;
  for (ui8Counter = 0; ui8Counter < 20; ui8Counter++){
    if (ui8AddChar(lpLinkedList, cTest + ui8Counter, 0) != DATA_ADDED){                           /*!< Check the header of ListLinked library to view all possible errors in this process... */
      printf("ERROR: Could not add this data in this list.\n");                                   /*!< Print an error message and returns 2 for the operational system. */
      return 2;                                                                                   /*!< You can treat the problem any way you want! */
    }
    if (ui8AddDouble(lpLinkedList, dTest * ui8Counter, 0) != DATA_ADDED){                         /*!< Check the header of ListLinked library to view all possible errors in this process... */
      printf("ERROR: Could not add this data in this list.\n");                                   /*!< Print an error message and returns 2 for the operational system. */
      return 2;                                                                                   /*!< You can treat the problem any way you want! */
    }
    if (ui8AddInt(lpLinkedList, ui8Counter + i32Test, 0) != DATA_ADDED){                          /*!< Check the header of ListLinked library to view all possible errors in this process... */
      printf("ERROR: Could not add this data in this list.\n");                                   /*!< Print an error message and returns 2 for the operational system. */
      return 2;                                                                                   /*!< You can treat the problem any way you want! */
    }
  }
  
  /*!
    Printing data from Linked List...
  */
  printf("\nAll data are allocated... Printing linked list:\n");
  printf("  -> List size: %d\n", ui16GetListSize(lpLinkedList));
  for (ui8Counter = 0; ui8Counter < 60; ui8Counter++){
     printf("   * Position %d: ", ui8Counter);
     vListPrint(lpLinkedList, ui8Counter);
     printf("\n");
  }
  printf("\n");
  vPrintMemoryStatus();
  
  /*!
    Deleting data from lpLinkedList...
  */
  printf("\nDeleting Linked List... ");
  vDeleteList(&lpLinkedList);
  if (lpLinkedList != NULL){                                                                      /*!< If the pointer is not NULL... */
    printf("\nERROR: Could not delete this list.\n");                                             /*!< Print an error message and returns 2 for the operational system. */
    return 4;                                                                                     /*!< You can treat the problem any way you want! */
  }
  vPrintMemoryStatus();
  return 0;
}

//! Linked List printer
/*!
  Print a data from a list.
  \param lpList is a list_t type parameter. Is a linked list.
  \param ui16Position is a 16-bits integer type parameter. This is the position where the data will be inserted.
*/
void vListPrint(list_t* lpList, uint16_t ui16Position){
  uint8_t ui8DataSize = ui8GetListDataSize(lpList, ui16Position);
  if (ui16GetListSize(lpList) > 0){
    if (ui8DataSize == sizeof(char)){
      printf("%c", *(char*) vpGetElement(lpList, ui16Position));
    }
    else if (ui8DataSize == sizeof(double)){
      printf("%.2f", *(double*) vpGetElement(lpList, ui16Position));
    }
    else if (ui8DataSize == sizeof(int32_t)){
      printf("%d", *(int32_t*) vpGetElement(lpList, ui16Position));
    }
  }
}

//! Linked List char type adder
/*!
  Add char type in a list.
  \param lpList is a list_t type parameter. Is a linked list.
  \param cData is a char type parameter. Is a data which will be inserted in the list.
  \param ui16Position is a 16-bits integer type parameter. This is the position where the data will be inserted.
  \return Returns insert status. See the status macros in the header of LinkedList library for errors that may occur during insertion.
*/
uint8_t ui8AddChar(list_t* lpList, char cData, uint16_t ui16Position){
  char cBuffer = cData;
  return ui8AddOnUntypedList(lpList, &cBuffer, sizeof(char), ui16Position);
}

//! Linked List integer type adder
/*!
  Add integer type in a list.
  \param lpList is a list_t type parameter. Is a linked list.
  \param i32Data is a integer type parameter. Is a data which will be inserted in the list.
  \param ui16Position is a 16-bits integer type parameter. This is the position where the data will be inserted.
  \return Returns insert status. See the status macros in the header of LinkedList library for errors that may occur during insertion.
*/
uint8_t ui8AddInt(list_t* lpList, int32_t i32Data, uint16_t ui16Position){
  int32_t i32Buffer = i32Data;
  return ui8AddOnUntypedList(lpList, &i32Buffer, sizeof(int32_t), ui16Position);
}

//! Linked List double type adder
/*!
  Add double type in a list.
  \param lpList is a list_t type parameter. Is a linked list.
  \param dData is a double type parameter. Is a data which will be inserted in the list.
  \param ui16Position is a 16-bits integer type parameter. This is the position where the data will be inserted.
  \return Returns insert status. See the status macros in the header of LinkedList library for errors that may occur during insertion.
*/
uint8_t ui8AddDouble(list_t* lpList, double dData, uint16_t ui16Position){
  double dBuffer = dData;
  return ui8AddOnUntypedList(lpList, &dBuffer, sizeof(double), ui16Position);
}

//! Memory pool status printer
/*!
  Print the memory pool actual status.
*/
void vPrintMemoryStatus(){
  printf("Memory status:\n");
  printf(" -> Linked Lists: %d\n", ui16GetListFreeSpace(LIST));
  printf("  -> Typed Elements: %d\n", ui16GetListFreeSpace(TYPED));
  printf("  -> Untyped Elements: %d\n", ui16GetListFreeSpace(UNTYPED));
  printf("   * 8-Bits: %d\n", ui16GetFreeSpace(sizeof(uint8_t)));
  printf("   * 16-Bits: %d\n", ui16GetFreeSpace(sizeof(uint16_t)));
  printf("   * 32-Bits: %d\n", ui16GetFreeSpace(sizeof(uint32_t)));
  printf("   * 64-Bits: %d\n", ui16GetFreeSpace(sizeof(uint64_t)));
}
