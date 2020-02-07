//! Example 01 - Allocating and freeing data
/*!
  This simply example demonstrates the use of MemoryPool lib. On this
  software, all characters of char-type are written on memory pool and
  printed.

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
  Main function.
*/
int main(){
  /*!
    Memory Pool creating...
  */
  newMemoryPool(mpCharPool, sizeof(char), 128);

  /*!
    Allocating...
  */
  char* cpDinamicVectorChar = (char*) MemoryPool_malloc(mpCharPool, 26);                                                    /*!< Allocating memory space in memory pool, similar to malloc() function. */
  if (cpDinamicVectorChar == NULL){                                                                                         /*!< If the pointer is NULL... */
    printf("ERROR: Dynamic memory allocation error!");                                                                      /*!< Print an error message and returns 2 for the operational system. */
    return 2;                                                                                                               /*!< You can treat the problem any way you want! */
  }

  /*!
    Control Functions...
  */
  printf("ElementSize: %d bytes\n", MemoryPool_getElementSize(mpCharPool));                                                  /*!< You can get the size of memory pool element! */
  printf("DataSize: %d\n", MemoryPool_getSize(mpCharPool));                                                                  /*!< You can get the size of memory pool! */
  printf("FreeSpace: %d\n", MemoryPool_getFreeSpace(mpCharPool));                                                            /*!< You can get the memory pool free space! */

  /*!
    Writing data in Memory Pool...
  */
  char cBuffer = 0;
  for (cBuffer = 'a' ; cBuffer < 'z' + 1 ; cBuffer++){
    cpDinamicVectorChar[cBuffer - 'a'] = cBuffer;
  }

  /*!
    Reading data in Memory Pool...
  */
  printf("\nPrinting the contents of cpDinamicVectorChar:\n[");
  uint8_t ui8Counter = 0;
  for (ui8Counter = 0 ; ui8Counter < 26 ; ui8Counter++){
    printf(" %c", cpDinamicVectorChar[ui8Counter]);
  }
  printf(" ]\n\n");

  /*!
    Deleting data in Memory Pool...
  */
  MemoryPool_free(mpCharPool, &cpDinamicVectorChar, 26);                                                                    /*!< Deallocating memory space in memory pool, similar to free() function. */
  if (cpDinamicVectorChar != NULL){                                                                                         /*!< If the pointer is not NULL... */
    printf("ERROR: Dynamic memory deallocation error!\n");                                                                  /*!< Print an error message and returns 3 for the operational system. */
    return 3;                                                                                                               /*!< You can treat the problem any way you want! */
  }

  /*!
    Control Functions...
  */
  /*!
    Control Functions...
  */
  printf("ElementSize: %d bytes\n", MemoryPool_getElementSize(mpCharPool));                                                  /*!< You can get the size of memory pool element! */
  printf("DataSize: %d\n", MemoryPool_getSize(mpCharPool));                                                                  /*!< You can get the size of memory pool! */
  printf("FreeSpace: %d\n", MemoryPool_getFreeSpace(mpCharPool));                                                            /*!< You can get the memory pool free space! */

  return 0;
}

