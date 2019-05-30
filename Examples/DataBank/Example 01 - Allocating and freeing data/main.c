//! Example 01 - Allocating and freeing data
/*!
  This simply example demonstrates the use of DataBank lib. On this software,
  different types of data are allocated in memory pools.

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
  A sample structure. The size of this type is 64 bits.
  The sizes supported in this example are 8-bit, 16-bit,
  32-bit, and 64-bit. Any other size should be created
  a memory pool for allocation of this type.
*/
typedef struct{
  uint8_t ui8Integer;
  char cCharacter;
  float fFloat;
} AnyStruct;

/*!
  Main function.
*/
int main(){
  /*!
    Data Bank initializing...
  */
  if (ui8DataBankInit() != DATABANK_INITIALIZED){                                                                       /*!< If not possible data bank initialization... */
    printf("ERROR: Data Bank initialization error!");                                                                   /*!< Print an error message and returns 1 for the operational system. */
    return 1;                                                                                                           /*!< You can treat the problem any way you want! */
  }

  /*!
    Allocating...
  */
  float* fpFloatSample = (float*) vpDBAlloc(sizeof(float), 5);
  char* cpCharSample = (char*) vpDBAlloc(sizeof(char), 5);
  uint8_t* ui8pIntegerSample = (uint8_t*) vpDBAlloc(sizeof(uint8_t), 5);
  AnyStruct* sspStructSample = (AnyStruct*) vpDBAlloc(sizeof(AnyStruct), 5);
  if (fpFloatSample == NULL || cpCharSample == NULL || ui8pIntegerSample == NULL || sspStructSample == NULL){           /*!< If not possible memory pool allocation... */
    printf("\nERROR: Allocation memories error!");                                                                      /*!< Print an error message and returns 2 for the operational system. */
    return 2;                                                                                                           /*!< You can treat the problem any way you want! */
  }

  /*!
    Writing data in Memory Pools...
  */
  uint8_t ui8Counter = 0;
  for (ui8Counter = 0 ; ui8Counter < 5 ; ui8Counter++){
    fpFloatSample[ui8Counter] = 3.14*ui8Counter;
    cpCharSample[ui8Counter] = 'a' + ui8Counter;
    ui8pIntegerSample[ui8Counter] = ui8Counter;
    sspStructSample[ui8Counter].cCharacter = 'A' + ui8Counter;
    sspStructSample[ui8Counter].fFloat = 2.71*ui8Counter;
    sspStructSample[ui8Counter].ui8Integer = ui8Counter*10;
  }

  /*!
    Reading float type data in Memory Pool...
  */
  printf("Printing fpFloatSample: \n[");
  for (uint8_t ui8Counter = 0 ; ui8Counter < 5 ; ui8Counter++){
    printf(" %.2f", fpFloatSample[ui8Counter]);
  }

  printf(" ]\n");
  /*!
    Reading char type data in Memory Pool...
  */
  printf("\nPrinting cpCharSample: \n[");
  for (uint8_t ui8Counter = 0 ; ui8Counter < 5 ; ui8Counter++){
    printf(" %c", cpCharSample[ui8Counter]);
  }
  printf(" ]\n");

  /*!
    Reading integer type data in Memory Pool...
  */
  printf("\nPrinting ui8pIntegerSample: \n[");
  for (uint8_t ui8Counter = 0 ; ui8Counter < 5 ; ui8Counter++){
    printf(" %d", ui8pIntegerSample[ui8Counter]);
  }
  printf(" ]\n");

  /*!
    Reading AnyStruct type data in Memory Pool...
  */
  printf("\nPrinting sspStructSample:");
  for (uint8_t ui8Counter = 1 ; ui8Counter < 5 ; ui8Counter++){
    printf("\n\nui8Integer: %d", sspStructSample[ui8Counter].ui8Integer);
    printf("\nfFloat: %.2f", sspStructSample[ui8Counter].fFloat);
    printf("\ncCharacter: %c", sspStructSample[ui8Counter].cCharacter);
  }
  printf("\n");

  /*!
    Deleting data in Memory Pool...
  */
  vDBFree(&fpFloatSample, sizeof(float), 5);
  vDBFree(&cpCharSample, sizeof(char), 5);
  vDBFree(&ui8pIntegerSample, sizeof(uint8_t), 5);
  vDBFree(&sspStructSample, sizeof(AnyStruct), 5);
  if((fpFloatSample != NULL) || (cpCharSample  != NULL) || (ui8pIntegerSample  != NULL) || (sspStructSample != NULL)){    /*!< If any pointer is not NULL... */
    printf("\nERROR: Dynamic memory deallocation error!\n");                                                              /*!< Print an error message and returns 3 for the operational system. */
    return 3;                                                                                                             /*!< You can treat the problem any way you want! */
  }

  return 0;
}
