//! Example 02 - Memory fragmentation
/*!
  This simply example demonstrates the use fragmentation of memory detector
  function. This problem is very common on embedded systems! Two ways to solve
  this problem are:

    1 - Allocates memories that will be permanently
    in the system;

    2 - Use linked lists for temporary variables;

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
    This macro leaves your code cleaner in the memory pool statements.
  */
  newMemoryPool(mpCharPool, sizeof(char), 80);

  /*!
    Allocating...
  */
  char* cpSampleA = (char*) MemoryPool_calloc(mpCharPool, 20);
  char* cpSampleB = (char*) MemoryPool_calloc(mpCharPool, 40);
  char* cpSampleC = NULL;
  if (cpSampleA == NULL || cpSampleB == NULL){                                                        /*!< If the pointer is NULL... */
    printf("ERROR: Dynamic memory allocation error!");                                                /*!< Print an error message and returns 2 for the operational system. */
    return 2;                                                                                         /*!< You can treat the problem any way you want! */
  }

  /*!
    Deleting cpSampleA in Memory Pool...
  */
  MemoryPool_free(mpCharPool, &cpSampleA, 20);
  if(cpSampleA != NULL){                                                                              /*!< If cpSampleA pointer is not NULL... */
    printf("ERROR: Dynamic memory deallocation error!\n");                                            /*!< Print an error message and returns 3 for the operational system. */
    return 3;                                                                                         /*!< You can treat the problem any way you want! */
  }

  /*!
    Checking the state of Memory Pool...
  */
  if (MemoryPool_checkFragmentation(mpCharPool) == MEMORY_POOL_STATUS_FRAGMENTED_MEMORY){             /*!< If memory pool is fragmented... */
    printf("ATENTION: The memory pool is fragmented!\n");                                             /*!< Print an error message and the maximum size of allocation... */
    printf("Possible maximum size allocation: %d\n", MemoryPool_getMaxFreeSpace(mpCharPool));         /*!< You can treat the problem any way you want! */
  }

  /*!
    Trying allocate memory...
  */
  cpSampleC = (char*) MemoryPool_calloc(mpCharPool, 40);
  if (cpSampleC == NULL){                                                                             /*!< If not possible memory pool allocation... */
    printf("ERROR: Allocation memory error!");                                                        /*!< Print an error message and returns 2 for the operational system. */
    return 2;                                                                                         /*!< You can treat the problem any way you want! */
  }

  return 0;
}

