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
#include <LinkedList.h>

/*!
  Declaration of a list_t type list.
*/
list_t* lpLinkedList;

void vPrintMemoryStatus();                                                                          /*!< Void type function. */

/*!
  Main function.
*/
int main(){
  
  /*!
    Initializing circular buffer manager...
  */
  if (ui8ListManagerInit() != LIST_INIT_SUCESS){                                                    /*!< If not possible circular buffer manager initialization... */
    printf("ERROR: Circular buffer manager initialization error!");                                 /*!< Print an error message and returns 2 for the operational system. */
    return 2;                                                                                       /*!< You can treat the problem any way you want! */
  }
  printf("Memory Manager initialized... ");
  vPrintMemoryStatus();
  
  /*!
    Linked List creating...
  */
  lpLinkedList = lpCreateTypedList(sizeof(uint16_t));
  if (lpLinkedList == NULL){                                                                        /*!< If the pointer is NULL... */
    printf("ERROR: Linked list creation error!\n");                                                 /*!< Print an error message and returns 1 for the operational system. */
    return 1;                                                                                       /*!< You can treat the problem any way you want! */
  }
  
  /*!
    Inserting data on Linked List...
  */
  printf("\nInserting data on Linked List...\n");
  uint16_t ui16Counter = 0;
  for (ui16Counter = 0; ui16Counter < 10; ui16Counter++){
    if (ui8AddOnTypedList(lpLinkedList, &ui16Counter, 0) == DATA_NOT_ADDED){                        /*!< Check the header of ListLinked library to view all possible errors in this process... */
      printf("ERROR: Could not add this data in this list.\n");                                     /*!< Print an error message and returns 2 for the operational system. */
      return 2;                                                                                     /*!< You can treat the problem any way you want! */
    }
  }
  printf("Data inserted... ");
  vPrintMemoryStatus();
  
  /*!
    Reading data from Linked List...
  */
  printf("\nPrinting Linked List:\n");
  printf("  -> List size: %d\n", ui16GetListSize(lpLinkedList));
  for (ui16Counter = 0; ui16Counter < ui16GetListSize(lpLinkedList); ui16Counter++){
    printf("   * Position %d: %d\n", ui16Counter, *(uint16_t*) vpGetElement(lpLinkedList, ui16Counter));
  }
  
  /*!
    Removing data from Linked List...
  */
  printf("\nRemoving the eight firsts data from Linked List...\n");
  for (ui16Counter = 0; ui16Counter < 8; ui16Counter++){
    if (ui8RemoveFromList(lpLinkedList, 0) == DATA_NOT_REMOVED){                                    /*!< Check the header of ListLinked library to view all possible errors in this process... */
      printf("ERROR: Could not delete this data in this list.\n");                                  /*!< Print an error message and returns 3 for the operational system. */
      return 3;                                                                                     /*!< You can treat the problem any way you want! */
    }
  }
  printf("Memory Pool spaces deallocated... ");
  vPrintMemoryStatus();
  
  /*!
    Reading data from Linked List...
  */
  printf("\nReading data from Linked List...\n");
  printf("Linked List:\n");
  printf("  -> List size: %d\n", ui16GetListSize(lpLinkedList));
  for (ui16Counter = 0; ui16Counter < ui16GetListSize(lpLinkedList); ui16Counter++){
    printf("   * Position %d: %d\n", ui16Counter, *(uint16_t*) vpGetElement(lpLinkedList, ui16Counter));
  }
  
  /*!
    Deleting lpLinkedList...
  */
  printf("\nDeleting Linked List... ");
  vDeleteList(&lpLinkedList);
  
  /*!
    Reading data from Linked List...
  */
  if (lpLinkedList != NULL){                                                                          /*!< If the pointer is not NULL... */
    printf("\nERROR: Could not delete this list.\n");                                                 /*!< Print an error message and returns 2 for the operational system. */
    return 4;                                                                                         /*!< You can treat the problem any way you want! */
  }
  printf("List deallocated!\n");
  vPrintMemoryStatus();
  
  return 0;
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
