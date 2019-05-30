/*!
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

#include "Circular.h"
#include "MemoryManager.h"

//! Function: Circular Buffer Writer
/*!
  Write a data on a circular buffer.
  \param bpBuffer is a buffer_t pointer. This parameter is the address of circular buffer.
  \param vpData is a void pointer. This parameter is the data to be inserted on the buffer.
*/
void vPushCircularBuffer(buffer_t* bpBuffer, void* vpData){
  if (bpBuffer->ui8AmountOfData < bpBuffer->ui8BufferSize){
    bpBuffer->ui8AmountOfData++;
  }
  void* vpAdressBuffer = (char*) bpBuffer->vpVector + bpBuffer->ui8WritePosition * bpBuffer->ui8ElementSize;
  if (vpData != NULL){
    memcpy(vpAdressBuffer, vpData, bpBuffer->ui8ElementSize);
  }
  else{
    memset(vpAdressBuffer, 0, bpBuffer->ui8ElementSize);
  }
  if (bpBuffer->ui8WritePosition == bpBuffer->ui8BufferSize){
    bpBuffer->ui8WritePosition = 0;
  }
  else{
    bpBuffer->ui8WritePosition++;
  }
}

//! Function: Circular Buffer Reader
/*!
  Read data on a circular buffer.
  \param bpBuffer is a buffer_t pointer. This parameter is the address of circular buffer.
  \return Returns the adress of data on the buffer.
*/
void* vpPullCircularBuffer(buffer_t* bpBuffer){
  if (bpBuffer->ui8AmountOfData == 0){
    return NULL;
  }
  void* vpAdressBuffer = (char*) bpBuffer->vpVector + bpBuffer->ui8ReadPosition * bpBuffer->ui8ElementSize;
  if (bpBuffer->ui8ReadPosition == bpBuffer->ui8AmountOfData - 1){
    bpBuffer->ui8ReadPosition = 0;
  }
  else{
    bpBuffer->ui8ReadPosition++;
  }
  return vpAdressBuffer;
}
