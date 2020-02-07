//! Example 01 - Typed linked list
/*!
  This simply example demonstrates the use of typed linked lists. This list has
  a great peculiarity: You can save "infinite" variables in the list. However,
  there is a small disadvantage: The memory space needed to store a given data
  is given by the equation below:

    * For typed linked lists:
      Bytes = sum(sizeof(YourVariables)) + numberOfVariables*sizeof(TypedElement) + sizeof(LinkedList)

    * For untyped linked lists:
      Bytes = sum(sizeof(YourVariables)) + numberOfVariables*sizeof(UntypedElement) + sizeof(LinkedList)

    Wherever,
    * sizeof(TypedElement) = 2*sizeof(void*)
    * sizeof(UntypedElement) = 2*sizeof(void*) + sizeof(uint8_t)
    * sizeof(LinkedList) = sizeof(uint8_t) + sizeof(uint16_t) + 2*sizeof(void*)

  Each system has a pointer size. In an Arduino UNO
  (ATMega328p) , for example, the function for one char
  allocation would become:

    Bytes = 10 + 1 + sizeof(YourVariable)
    Bytes = 11 + sizeof(YourVariable)

  As we can see, the storage of any data would require 11 bytes more than
  direct storage on ATMega328p. We would have, for example, a char occupying
  11 bytes of its RAM. Use with caution...

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

void vPrintMemoryStatus();                                                                                    /*!< Void type function. */

/*!
  Main function.
*/
int main(){
  /*!
    Printing memory status...
  */
  printf("Printing memory status...");
  vPrintMemoryStatus();

  /*!
    Linked List creating...
  */
  newTypedList(tlMyList, uint16_t);

  /*!
    Inserting data on Linked List...
  */
  printf("\nInserting data on Linked List...\n");
  uint16_t ui16Counter = 0;
  for (ui16Counter = 0; ui16Counter < 5; ui16Counter++){
    if (TypedList_insertEnd(tlMyList, &ui16Counter) == TYPED_LIST_STATUS_DATA_NOT_ADDED){                     /*!< Check the header of ListLinked library to view all possible errors in this process... */
      printf("ERROR: Could not add this data in this list.\n");                                               /*!< Print an error message and returns 2 for the operational system. */
      return 2;                                                                                               /*!< You can treat the problem any way you want! */
    }
  }
  printf("Data inserted... ");
  vPrintMemoryStatus();

  /*!
    Reading data from Linked List...
  */
  printf("\nPrinting Linked List:\n");
  printf("  -> List size: %d\n", TypedList_getListSize(tlMyList));
  for (ui16Counter = 0; ui16Counter < TypedList_getListSize(tlMyList); ui16Counter++){
    printf("   * Position %d: %d\n", ui16Counter, TypedList_getData(tlMyList, uint16_t, ui16Counter));        /*!< You can use TypedList_getData if you are ignoring 0 value in your list. In contrary case, you should use TypedList_getDataAddress!*/
  }

  /*!
    Printing memory status...
  */
  vPrintMemoryStatus();

  /*!
    Removing data from Linked List...
  */
  printf("\nRemoving the 3 firsts data from Linked List...\n");
  for (ui16Counter = 0; ui16Counter < 3; ui16Counter++){
    if (TypedList_remove(tlMyList, 0) == TYPED_LIST_STATUS_DATA_NOT_REMOVED){                                 /*!< Check the header of ListLinked library to view all possible errors in this process... */
      printf("ERROR: Could not delete this data in this list.\n");                                            /*!< Print an error message and returns 3 for the operational system. */
      return 3;                                                                                               /*!< You can treat the problem any way you want! */
    }
  }
  printf("Memory Pool spaces deallocated...");
  vPrintMemoryStatus();

  /*!
    Reading data from Linked List...
  */
  printf("\nReading data from Linked List...\n");
  printf("Linked List:\n");
  printf("  -> List size: %d\n", TypedList_getListSize(tlMyList));
  for (ui16Counter = 0; ui16Counter < TypedList_getListSize(tlMyList); ui16Counter++){
    printf("   * Position %d: %d\n", ui16Counter, TypedList_getData(tlMyList, uint16_t, ui16Counter));
  }
  vPrintMemoryStatus();

  /*!
    Cleaning Linked List...
  */
  printf("\nCleaning Linked List...\n");
  TypedList_clear(tlMyList);
  uint16_t* ui16pBuffer = TypedList_getDataAddress(tlMyList, uint16_t, ui16Counter);
  if (ui16pBuffer != NULL){                                                                                   /*!< Check if typed list has been cleared... */
    printf("ERROR: Typed list is not clear!\n");                                                              /*!< Print an error message and returns 3 for the operational system. */
    return 4;                                                                                                 /*!< You can treat the problem any way you want! */
  }
  printf("Linked list cleared!");
  vPrintMemoryStatus();

  return 0;
}

//! Memory pool status printer
/*!
  Print the memory pool actual status.
*/
void vPrintMemoryStatus(){
  printf("\nMemory status:\n");
  printf(" -> Typed Linked Lists\n");
  printf("   * Typed Elements: %d\n", TypedList_getFreeSpace());
  printf("   * 8-Bits: %d\n", DataBank_getFreeSpace(sizeof(uint8_t)));
  printf("   * 16-Bits: %d\n", DataBank_getFreeSpace(sizeof(uint16_t)));
  printf("   * 32-Bits: %d\n", DataBank_getFreeSpace(sizeof(uint32_t)));
  printf("   * 64-Bits: %d\n", DataBank_getFreeSpace(sizeof(uint64_t)));
}

