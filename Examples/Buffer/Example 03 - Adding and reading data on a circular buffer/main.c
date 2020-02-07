//! Example 03 - Adding and reading data on a circular buffer
/*!
  This simply example demonstrates the use of circular buffer.

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

int main(){
  newBuffer(bfBuffer, BUFFER_TYPE_CIRCULAR, uint16_t, 5);
  if (bfBuffer == NULL){                                                                  /*!< If not possible circular buffer allocation... */
    printf("\nERROR: Allocation for circular buffer error!");                             /*!< Print an error message and returns 3 for the operational system. */
    return 3;                                                                             /*!< You can treat the problem any way you want! */
  }

  /*!
    Writing data in circular buffer...
  */
  printf("Writing data on circular buffer... ");
  uint8_t ui8Counter = 0;
  for (ui8Counter = 0; ui8Counter < 15; ui8Counter ++){
    uint16_t ui16Buffer = ui8Counter;
    Buffer_push(bfBuffer, &ui16Buffer);
  }

  /*!
    Reading data in circular buffer...
  */
  printf("Complete!\n\nReading data on circular buffer:");
  for (ui8Counter = 0; ui8Counter < 10; ui8Counter ++){
    printf("\nPosition %d: %d", ui8Counter, Buffer_pop(bfBuffer, uint16_t));
  }

  /*!
    Cleaning the circular buffer... This function is only for circular or stack buffer type.
  */
  printf("\n\nCleaning circular buffer... ");
  Buffer_clear(bfBuffer);
  uint16_t* ui16pBuffer = Buffer_popAddress(bfBuffer, uint16_t);
  if (ui16pBuffer == NULL){
    printf("The circular buffer is empty!\n\n");
  }
  else{
    printf("ERROR: The circular buffer is not cleaned!");                                 /*!< Print an error message and returns 4 for the operational system. */
    return 4;                                                                             /*!< You can treat the problem any way you want! */
  }

  printf("Complete deletion!\n");
  return 0;
}

