//! Example 02 - Untyped linked list
/*!
  This simply example demonstrates the use of untyped linked lists. The great
  advantage of this list is that it makes it possible to save files of different
  types. The problem is that when reading a certain data, the programming language
  C can not recognize the type of this data, and this becomes a problem. This
  example is only a possible resolution of this problem. The only disadvantage is
  that, in a list, you can not store different types of data that have the same size
  (Example: uint8_t, bool and char).

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
#include <MemoryManager.h>

/*!
  Function Scopes.
*/
uint8_t ui8AddChar(untyped_list_t ulpList, char cData, uint16_t ui16Position);                          /*!< 8-bit integer type function. */
uint8_t ui8AddInt(untyped_list_t ulpList, int32_t i32Data, uint16_t ui16Position);                      /*!< 8-bit integer type function. */
uint8_t ui8AddDouble(untyped_list_t ulpList, double dData, uint16_t ui16Position);                      /*!< 8-bit integer type function. */                                                                /*!< Void type function. */
void vListPrint(untyped_list_t ulpList, uint16_t ui16Position);                                         /*!< Void type function. */
void vPrintMemoryStatus();                                                                              /*!< Void type function. */

/*!
  Main function.
*/
int main(){
  /*!
    Printing memory status...
  */
  vPrintMemoryStatus();

  /*!
    Linked List creating...
  */
  newUntypedList(ulMyUntypedList);

  /*!
    Inserting data on Linked List...
  */
  char cTest = 'a';
  int32_t i32Test = -10;
  double dTest = 3.14;
  uint8_t ui8Counter = 0;
  for (ui8Counter = 0; ui8Counter < 20; ui8Counter++){
    if (ui8AddChar(ulMyUntypedList, cTest + ui8Counter, 0) != UNTYPED_LIST_STATUS_DATA_ADDED){          /*!< Check the header of ListLinked library to view all possible errors in this process... */
      printf("ERROR: Could not add this data in this list.\n");                                         /*!< Print an error message and returns 2 for the operational system. */
      return 2;                                                                                         /*!< You can treat the problem any way you want! */
    }
    if (ui8AddDouble(ulMyUntypedList, dTest * ui8Counter, 0) != UNTYPED_LIST_STATUS_DATA_ADDED){        /*!< Check the header of ListLinked library to view all possible errors in this process... */
      printf("ERROR: Could not add this data in this list.\n");                                         /*!< Print an error message and returns 2 for the operational system. */
      return 2;                                                                                         /*!< You can treat the problem any way you want! */
    }
    if (ui8AddInt(ulMyUntypedList, ui8Counter + i32Test, 0) != UNTYPED_LIST_STATUS_DATA_ADDED){         /*!< Check the header of ListLinked library to view all possible errors in this process... */
      printf("ERROR: Could not add this data in this list.\n");                                         /*!< Print an error message and returns 2 for the operational system. */
      return 2;                                                                                         /*!< You can treat the problem any way you want! */
    }
  }

  /*!
    Printing data from Linked List...
  */
  printf("\nAll data are allocated... Printing linked list:\n");
  printf("  -> List size: %d\n", UntypedList_getListSize(ulMyUntypedList));
  for (ui8Counter = 0; ui8Counter < 60; ui8Counter++){
     printf("   * Position %d: ", ui8Counter);
     vListPrint(ulMyUntypedList, ui8Counter);
     printf("\n");
  }
  printf("\n");
  vPrintMemoryStatus();

  /*!
    Deleting data from ulMyUntypedList...
  */
  printf("\nDeleting Linked List... ");
  UntypedList_clear(ulMyUntypedList);
  void* vpBuffer = UntypedList_getDataAddress(ulMyUntypedList, void, 0);
  if (vpBuffer != NULL){                                                                                /*!< If the pointer is not NULL... */
    printf("\nERROR: Could not delete this list.\n");                                                   /*!< Print an error message and returns 2 for the operational system. */
    return 4;                                                                                           /*!< You can treat the problem any way you want! */
  }
  printf("Deleted!\n\n");
  vPrintMemoryStatus();
  return 0;
}

//! Linked List printer
/*!
  Print a data from a list.
  \param ulpList is a untyped_list_t type parameter. Is a linked list.
  \param ui16Position is a 16-bits integer type parameter. This is the position where the data will be inserted.
*/
void vListPrint(untyped_list_t ulpList, uint16_t ui16Position){
  uint8_t ui8DataSize = UntypedList_getDataSize(ulpList, ui16Position);
  if (UntypedList_getListSize(ulpList) > 0){
    if (ui8DataSize == sizeof(char)){
      printf("%c", UntypedList_getData(ulpList, char, ui16Position));
    }
    else if (ui8DataSize == sizeof(double)){
      printf("%.2f", UntypedList_getData(ulpList, double, ui16Position));
    }
    else if (ui8DataSize == sizeof(int32_t)){
      printf("%d", UntypedList_getData(ulpList, int32_t, ui16Position));
    }
  }
}

//! Linked List char type adder
/*!
  Add char type in a list.
  \param ulpList is a untyped_list_t type parameter. Is a linked list.
  \param cData is a char type parameter. Is a data which will be inserted in the list.
  \param ui16Position is a 16-bits integer type parameter. This is the position where the data will be inserted.
  \return Returns insert status. See the status macros in the header of LinkedList library for errors that may occur during insertion.
*/
uint8_t ui8AddChar(untyped_list_t ulpList, char cData, uint16_t ui16Position){
  char cBuffer = cData;
  return UntypedList_insert(ulpList, &cBuffer, sizeof(char), ui16Position);
}

//! Linked List integer type adder
/*!
  Add integer type in a list.
  \param ulpList is a untyped_list_t type parameter. Is a linked list.
  \param i32Data is a integer type parameter. Is a data which will be inserted in the list.
  \param ui16Position is a 16-bits integer type parameter. This is the position where the data will be inserted.
  \return Returns insert status. See the status macros in the header of LinkedList library for errors that may occur during insertion.
*/
uint8_t ui8AddInt(untyped_list_t ulpList, int32_t i32Data, uint16_t ui16Position){
  int32_t i32Buffer = i32Data;
  return UntypedList_insert(ulpList, &i32Buffer, sizeof(int32_t), ui16Position);
}

//! Linked List double type adder
/*!
  Add double type in a list.
  \param ulpList is a untyped_list_t type parameter. Is a linked list.
  \param dData is a double type parameter. Is a data which will be inserted in the list.
  \param ui16Position is a 16-bits integer type parameter. This is the position where the data will be inserted.
  \return Returns insert status. See the status macros in the header of LinkedList library for errors that may occur during insertion.
*/
uint8_t ui8AddDouble(untyped_list_t ulpList, double dData, uint16_t ui16Position){
  double dBuffer = dData;
  return UntypedList_insert(ulpList, &dBuffer, sizeof(double), ui16Position);
}

//! Memory pool status printer
/*!
  Print the memory pool actual status.
*/
void vPrintMemoryStatus(){
  printf("Memory status:\n");
  printf(" -> Untyped Linked Lists:\n");
  printf("  -> Typed Elements: %d\n", UntypedList_getFreeSpace());
  printf("   * 8-Bits: %d\n", DataBank_getFreeSpace(sizeof(uint8_t)));
  printf("   * 16-Bits: %d\n", DataBank_getFreeSpace(sizeof(uint16_t)));
  printf("   * 32-Bits: %d\n", DataBank_getFreeSpace(sizeof(uint32_t)));
  printf("   * 64-Bits: %d\n", DataBank_getFreeSpace(sizeof(uint64_t)));
}

