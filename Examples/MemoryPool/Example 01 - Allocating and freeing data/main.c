//! Example 01 - Allocating and freeing data
/*!
  This simply example demonstrates the use of MemoryPool lib. On this 
  software, all characters of char-type are written on memory pool and 
  printed.
  
  Put the "Bits" and "MemoryPool" library folder in the same location as 
  this file.

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
#include "MemoryPool/MemoryPool.h"

/*!
  There is a macro that automates this process in this 
  library. But if you do not want to, you can use this 
  more manual method, which saves 1 byte of memory compared 
  to automated. Declaration of a char type vector. This 
  vector is the dataSpace of the Memory Pool. You can decrease 
  the size of this vector to force a insufficient memory error.
*/
char cCharPool[128];

/*!
  Declaration of a bitvector_t type vector. This is an
  auxiliary vector that is responsible for managing the
  use of spaces allocated in the memory pool.
*/
bitvector_t bvAuxCharPool[uiAuxiliaryVectorSize(sizeof(cCharPool))];

/*!
  Declaration of the memory pool struct.
*/
mpool_t mpCharPool;

/*!
  Main function.
*/
int main(){
  /*!
    Memory Pool creating...
  */
  if (ui8MPInit(&mpCharPool, cCharPool, bvAuxCharPool, sizeof(cCharPool), sizeof(char)) == MEMORYPOOL_INIT_ERROR){          /*!< If not possible memory pool allocation... */
    printf("ERROR: Memory Pool init error!");                                                                               /*!< Print an error message and returns 1 for the operational system. */
    return 1;                                                                                                               /*!< You can treat the problem any way you want! */
  }
  
  /*!
    Allocating...
  */
  char* cpDinamicVectorChar = (char*) vpMPAlloc(&mpCharPool, 26);                                                           /*!< Allocating memory space in memory pool, similar to malloc() function. */
  if (cpDinamicVectorChar == NULL){                                                                                         /*!< If the pointer is NULL... */
    printf("ERROR: Dynamic memory allocation error!");                                                                      /*!< Print an error message and returns 2 for the operational system. */
    return 2;                                                                                                               /*!< You can treat the problem any way you want! */
  }
  
  /*!
    Control Functions...
  */
  printf("ElementSize: %d bytes\n", ui8MPGetElementSize(&mpCharPool));                                                      /*!< You can get the size of memory pool element! */
  printf("DataSize: %d\n", ui16MPGetDataSize(&mpCharPool));                                                                 /*!< You can get the size of memory pool! */
  printf("FreeSpace: %d\n", ui16MPGetFreeSpace(&mpCharPool));                                                               /*!< You can get the memory pool free space! */
  printf("WritePosition: %d\n", ui16MPGetWritePosition(&mpCharPool));                                                       /*!< You can get the memory pool write position! */
  
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
  vMPFree(&mpCharPool, (void*) &cpDinamicVectorChar, 26);                                                                   /*!< Deallocating memory space in memory pool, similar to free() function. */
  if (cpDinamicVectorChar != NULL){                                                                                         /*!< If the pointer is not NULL... */
    printf("ERROR: Dynamic memory deallocation error!\n");                                                                  /*!< Print an error message and returns 3 for the operational system. */
    return 3;                                                                                                               /*!< You can treat the problem any way you want! */
  }
  
  /*!
    Control Functions...
  */
  printf("ElementSize: %d bytes\n", ui8MPGetElementSize(&mpCharPool));                                                      /*!< You can get the size of memory pool element! */
  printf("DataSize: %d\n", ui16MPGetDataSize(&mpCharPool));                                                                 /*!< You can get the size of memory pool! */
  printf("FreeSpace: %d\n", ui16MPGetFreeSpace(&mpCharPool));                                                               /*!< You can get the memory pool free space! */
  printf("WritePosition: %d\n", ui16MPGetWritePosition(&mpCharPool));                                                       /*!< You can get the memory pool write position! */
  
  return 0;
}
