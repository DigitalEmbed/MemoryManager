//! Example 02 - DataBank memory fragmentation
/*!
  This simply example demonstrates the use fragmentation of memory detector 
  function. This problem is very common on embedded systems! Two ways to 
  solve this problem are:

    1 - Allocates memories that will be permanently
    in the system;

    2 - Use linked lists for temporary variables;

  Put the "Bits", "MemoryPool", "DataBank" and "Buffer" library folder in the 
  same location as this file.

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
#include "DataBank/DataBank.h"

/*!
  Main function.
*/
int main(){
  /*!
    Data Bank initializing...
  */
  if (ui8DataBankInit() != DATABANK_INITIALIZED){                                                         /*!< If not possible data bank initialization... */
    printf("ERROR: Data Bank initialization error!");                                                     /*!< Print an error message and returns 1 for the operational system. */
    return 1;                                                                                             /*!< You can treat the problem any way you want! */
  }
  
  /*!
    Allocating...
  */
  uint8_t* ui8SampleA = (uint8_t*) vpDBAlloc(sizeof(uint8_t), 20);
  uint8_t* ui8SampleB = (uint8_t*) vpDBAlloc(sizeof(uint8_t), 40);
  uint8_t* ui8SampleC = NULL;
  if (ui8SampleA == NULL || ui8SampleB == NULL){                                                          /*!< If not possible memory pool allocation... */
    printf("ERROR: Allocation memories error!");                                                          /*!< Print an error message and returns 2 for the operational system. */
    return 2;                                                                                             /*!< You can treat the problem any way you want! */
  }
  
  /*!
    Deleting ui8SampleA in Memory Pool...
  */
  vDBFree(&ui8SampleA, sizeof(float), 20);
  if(ui8SampleA != NULL){                                                                                 /*!< If any pointer is not NULL... */
    printf("ERROR: Dynamic memory deallocation error!\n");                                                /*!< Print an error message and returns 3 for the operational system. */
    return 3;                                                                                             /*!< You can treat the problem any way you want! */
  }
  
  /*!
    Checking the state of Memory Pool...
  */
  if (ui16CheckFragmentation(sizeof(uint8_t)) == FRAGMENTED_MEMORY){                                      /*!< If memory pool is fragmented... */
    printf("ATENTION: The memory pool is fragmented!\n");                                                 /*!< Print an error message and the maximum size of allocation... */
    printf("Possible maximum size allocation: %d\n", ui16GetFragmentedFreeSpace(sizeof(uint8_t)));        /*!< You can treat the problem any way you want! */
  }
  
  /*!
    Trying allocate memory...
  */
  ui8SampleC = (uint8_t*) vpDBAlloc(sizeof(uint8_t), 40);
  if (ui8SampleC == NULL){                                                                                /*!< If not possible memory pool allocation... */
    printf("ERROR: Allocation memory error!");                                                            /*!< Print an error message and returns 2 for the operational system. */
    return 2;                                                                                             /*!< You can treat the problem any way you want! */
  }
  
  return 0;
}
