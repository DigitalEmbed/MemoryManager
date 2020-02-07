//! Example 02 - Generic stack buffer
/*!
  This simply example demonstrates the use of generic stack buffer. A generic
  buffer is a buffer that is not of a primitive type of C.

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
  Definition of sample_t structure.
*/
typedef struct{
  char cSample;
  uint16_t ui16Sample;
}sample_t;

int main(){
  const uint8_t ui8SizeOfVector = 5;
  newStaticBuffer(bfSampleStruct, BUFFER_TYPE_STACK, sample_t, 5);
  if (bfSampleStruct == NULL){                                                                                          /*!< If not possible stack buffer allocation... */
    printf("\nERROR: Allocation for stack buffer error!");                                                              /*!< Print an error message and returns 3 for the operational system. */
    return 3;                                                                                                           /*!< You can treat the problem any way you want! */
  }

  /*!
    Writing data in stack buffer...
  */
  printf("Writing data on stack buffer... ");
  uint8_t ui8Counter = 0;
  for (ui8Counter = 0; ui8Counter < ui8SizeOfVector; ui8Counter ++){
    sample_t spBuffer;
    spBuffer.cSample = ui8Counter + 'a';
    spBuffer.ui16Sample = ui8Counter;
    Buffer_push(bfSampleStruct, &spBuffer);
  }

  /*!
    Reading data in stack buffer...
  */
  printf("Complete!\n\nReading data on stack buffer:\n");
  for (ui8Counter = 0; ui8Counter < ui8SizeOfVector; ui8Counter ++){
    sample_t* spBuffer = Buffer_popAddress(bfSampleStruct, sample_t);
    if (spBuffer != NULL){
      uint16_t ui16Buffer = spBuffer->ui16Sample;
      char cBuffer = spBuffer->cSample;
      printf("\nPosition %d:\n  ui16Buffer: %d\n  cBuffer: %c\n", ui8Counter, ui16Buffer, cBuffer);
    }
  }

  /*!
    Cleaning the stack buffer... This function is only for queue or stack buffer type.
  */
  printf("\nCleaning stack buffer... ");
  Buffer_clear(bfSampleStruct);
  sample_t* spBuffer = Buffer_popAddress(bfSampleStruct, sample_t);
  if (spBuffer == NULL){
    printf("The stack buffer is empty");
  }
  else{
    printf("ERROR: The stack buffer is not cleaned!");                                                                  /*!< Print an error message and returns 4 for the operational system. */
    return 4;                                                                                                           /*!< You can treat the problem any way you want! */
  }
  return 0;
}

