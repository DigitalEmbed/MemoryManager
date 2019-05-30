//! Example 02 - Memory fragmentation
/*!
  This simply example demonstrates the use fragmentation of memory detector
  function. This problem is very common on embedded systems! Two ways to solve
  this problem are:
  
    1 - Allocates memories that will be permanently
    in the system;
    
    2 - Use linked lists for temporary variables;
    
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
#include <MemoryManager.h>

/*!
  This macro leaves your code cleaner in the memory pool statements.
*/
xCreatePool(mpCharPool, char, 80);

/*!
  Main function.
*/
int main(){
  /*!
    Memory Pool initializing... When using the xCreatePool macro, you must initialize the memory pool manager by using this macro.
  */
  if (ui8PoolInit(mpCharPool) == MEMORYPOOL_INIT_ERROR){                                              /*!< If not possible memory pool allocation... */
    printf("ERROR: Memory Pool init error!");                                                         /*!< Print an error message and returns 1 for the operational system. */
    return 1;                                                                                         /*!< You can treat the problem any way you want! */
  }

  /*!
    Allocating...
  */
  char* cpSampleA = (char*) vpMPAlloc(&mpCharPool, 20);
  char* cpSampleB = (char*) vpMPAlloc(&mpCharPool, 40);
  char* cpSampleC = NULL;
  if (cpSampleA == NULL || cpSampleB == NULL){                                                        /*!< If the pointer is NULL... */
    printf("ERROR: Dynamic memory allocation error!");                                                /*!< Print an error message and returns 2 for the operational system. */
    return 2;                                                                                         /*!< You can treat the problem any way you want! */
  }

  /*!
    Deleting cpSampleA in Memory Pool...
  */
  vMPFree(&mpCharPool, (void*) &cpSampleA, 20);
  if(cpSampleA != NULL){                                                                              /*!< If cpSampleA pointer is not NULL... */
    printf("ERROR: Dynamic memory deallocation error!\n");                                            /*!< Print an error message and returns 3 for the operational system. */
    return 3;                                                                                         /*!< You can treat the problem any way you want! */
  }

  /*!
    Checking the state of Memory Pool...
  */
  if (ui8MPCheckFragmentation(&mpCharPool) == FRAGMENTED_MEMORY){                                     /*!< If memory pool is fragmented... */
    printf("ATENTION: The memory pool is fragmented!\n");                                             /*!< Print an error message and the maximum size of allocation... */
    printf("Possible maximum size allocation: %d\n", ui16MPGetFragmentedFreeSpace(&mpCharPool));      /*!< You can treat the problem any way you want! */
  }

  /*!
    Trying allocate memory...
  */
  cpSampleC = (char*) vpMPAlloc(&mpCharPool, 40);
  if (cpSampleC == NULL){                                                                             /*!< If not possible memory pool allocation... */
    printf("ERROR: Allocation memory error!");                                                        /*!< Print an error message and returns 2 for the operational system. */
    return 2;                                                                                         /*!< You can treat the problem any way you want! */
  }

  return 0;
}
