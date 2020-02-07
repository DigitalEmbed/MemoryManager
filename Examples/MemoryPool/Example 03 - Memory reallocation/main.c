//! Example 03 - Memory reallocation
/*!
  This simply example demonstrates the use of reallocation function.

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
  Declaration of a char pool. This vector is the data
  Space of the Memory Pool. You can decrease the size
  of this vector to force a insufficient memory error.
  When reallocating, you need at least the sum of the
  old allocation size with the new size of non-fragmented
  free space in your memory pool.
*/
newMemoryPool(mpCharPool, sizeof(char), 150);

/*!
  Main function.
*/
int main(){

  /*!
    Allocating...
  */
  char* cpSample = (char*) MemoryPool_calloc(mpCharPool, 26);
  if (cpSample == NULL){                                                  /*!< If the pointer is NULL... */
    printf("ERROR: Dynamic memory allocation error!");                    /*!< Print an error message and returns 2 for the operational system. */
    return 2;                                                             /*!< You can treat the problem any way you want! */
  }

  /*!
    Writing data in Memory Pool...
  */
  char cBuffer = 0;
  for (cBuffer = 'a' ; cBuffer < 'z' + 1 ; cBuffer++){
    cpSample[cBuffer - 'a'] = cBuffer;
  }

  /*!
    Reading data in Memory Pool...
  */
  printf("Printing the contents of the cSampleA pointer:\n[");
  uint8_t ui8Counter = 0;
  for (ui8Counter = 0 ; ui8Counter < 26 ; ui8Counter++){
    printf(" %c", cpSample[ui8Counter]);
  }
  printf(" ]\n");

  /*!
    Reallocating...
  */
  if (MemoryPool_getMaxFreeSpace(mpCharPool) < (26 + 52)){                /*!< If not enough space for reallocation... */
    printf("ERROR: No enough space for memory reallocation!");            /*!< Print an error message and returns 3 for the operational system. */
    return 3;                                                             /*!< You can treat the problem any way you want! */
  }
  MemoryPool_realloc(mpCharPool, &cpSample, 26, 52);
  if (cpSample == NULL){                                                  /*!< If the pointer is NULL... */
    printf("ERROR: Dynamic memory reallocation error!");                  /*!< Print an error message and returns 2 for the operational system. */
    return 2;                                                             /*!< You can treat the problem any way you want! */
  }

  /*!
    Writing data in Memory Pool...
  */
  for (char cBuffer = 'A' ; cBuffer < 'Z' + 1 ; cBuffer++){
    cpSample[26 + cBuffer - 'A'] = cBuffer;
  }

  /*!
    Reading data in Memory Pool...
  */
  printf("\nPrinting the contents of the cSampleB pointer:\n[");
  for (uint8_t ui8Counter = 0 ; ui8Counter < 52 ; ui8Counter++){
    printf(" %c", cpSample[ui8Counter]);
  }
  printf(" ]\n");

  return 0;
}

