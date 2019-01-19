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

#include "Buffer.h"
#include "Queue/Queue.h"
#include "Stack/Stack.h"

//! Type of buffer data macros
/*!
  This macro are for internal use and exists only to separate the buffers dynamically allocated in the Data Bank from the rest.
*/
#define   GENERIC   0
#define   DATABANK  1

/*!
  This variable indicates whether the database manager
  has been initialized or not.
*/
uint8_t ui8BufferManagerStatus = 0;

/*!
  Statement of memory pools of buffers.
*/
xCreatePool(mpBufferPool, buffer_t, NUMBER_OF_BUFFER);

//! Buffer manager initializer function
/*!
  Initialize the buffer manager.
*/
uint8_t ui8BufferManagerInit(){
  if (ui8BufferManagerStatus != BUFFER_INITIALIZED){
    ui8BufferManagerStatus = ui8PoolInit(mpBufferPool);
    return ui8BufferManagerStatus;
  }
  else{
    return BUFFER_INITIALIZED;
  }
}

//! Buffer creator function
/*!
  Create a dynamic buffer.
  \param ui8ElementSize is a 8-Bit integer. That's the size of type of vpVector.
  \param ui8BufferSize is a 8-Bit integer. This parameter refers to the size of vpVector.
  \return Returns the adress of allocation of the buffer.
*/
buffer_t* bpCreateBuffer(uint8_t ui8BufferType, uint8_t ui8ElementSize, uint8_t ui8BufferSize){
  if(ui8BufferSize > 1 && ui8ElementSize > 0 && ui8BufferType < 2){
    buffer_t *bpBuffer = (buffer_t*) vpMPAlloc(&mpBufferPool, 1);
    bpBuffer->vpVector = (buffer_t*) vpDBAlloc(ui8ElementSize, ui8BufferSize);
    if (bpBuffer->vpVector != NULL){
      bpBuffer->ui8ReadPosition = 0;
      bpBuffer->ui8ElementSize = ui8ElementSize;
      bpBuffer->ui8BufferSize = ui8BufferSize;
      bpBuffer->ui8WritePosition = 0;
      bpBuffer->ui8AmountOfData = 0;
      bpBuffer->ui8AllocationType = DATABANK;
      bpBuffer->ui8BufferType = ui8BufferType;
      return bpBuffer;
    }
    else{
      return NULL;
    }
  }
  else{
    return NULL;
  }
}

//! Buffer creator function
/*!
  Create a dynamic buffer.
  \param vpVector is a void pointer type. It's the vector that will be "converted" into circular vector.
  \param ui8ElementSize is a 8-Bit integer. That's the size of type of vpVector.
  \param ui8BufferSize is a 8-Bit integer. This parameter refers to the size of vpVector.
  \return Returns the adress of allocation of the buffer.
*/
buffer_t* bpCreateGenericBuffer(void* vpVector, uint8_t ui8BufferType, uint8_t ui8ElementSize, uint8_t ui8BufferSize){
  if(ui8BufferSize > 1 && ui8ElementSize > 0 && ui8BufferType < 2){
    buffer_t *bpBuffer = (buffer_t*) vpMPAlloc(&mpBufferPool, 1);
    bpBuffer->vpVector = vpVector;
    bpBuffer->ui8ReadPosition = 0;
    bpBuffer->ui8ElementSize = ui8ElementSize;
    bpBuffer->ui8BufferSize = ui8BufferSize;
    bpBuffer->ui8WritePosition = 0;
    bpBuffer->ui8AmountOfData = 0;
    bpBuffer->ui8AllocationType = GENERIC;
    bpBuffer->ui8BufferType = ui8BufferType;
    return bpBuffer;
  }
  else{
    return NULL;
  }
}

//! Buffer writer function
/*!
  Write a data on a buffer.
  \param bpBuffer is a buffer_t pointer. This parameter is the address of buffer.
  \param vpData is a void pointer. This parameter is the data to be inserted on the buffer.
*/
void vPushBufferData(buffer_t* bpBuffer, void* vpData){
  switch(bpBuffer->ui8BufferType){

    case QUEUE:
      vPushQueueBuffer(bpBuffer, vpData);
      break;

    case STACK:
      vPushStackBuffer(bpBuffer, vpData);
      break;

  }
}

//! Buffer reader function
/*!
  Pull data on a buffer.
  \param bpBuffer is a buffer_t pointer. This parameter is the address of buffer.
  \return Returns the adress of data on the buffer.
*/
void* vpPullBufferData(buffer_t* bpBuffer){
  switch(bpBuffer->ui8BufferType){

    case QUEUE:
      return vpPullQueueBuffer(bpBuffer);

    case STACK:
      return vpPullStackBuffer(bpBuffer);

    default:
      return NULL;

  }
}

//! Buffer deleter function
/*!
  Delete a buffer.
  \param bpBuffer is a buffer_t pointer. This parameter is the address of buffer.
  \param ui8TypeOfAllocationVector is a 8-Bit integer. This parameter depends of the type of you circular buffer: if your buffer is static allocated, put STATIC in this parameter. If your buffer is dinamic allocated, put POOL in this parameter.
*/
void vDeleteBuffer(buffer_t** bpBuffer){
  if ((*bpBuffer)->ui8AllocationType == DATABANK){
    vDBFree(&(*bpBuffer)->vpVector, (*bpBuffer)->ui8ElementSize, (*bpBuffer)->ui8BufferSize);
    if ((*bpBuffer)->vpVector == NULL){
      vMPFree(&mpBufferPool, (void**) bpBuffer, (*bpBuffer)->ui8BufferSize);
    }
  }
  else{
    vMPFree(&mpBufferPool, (void**) bpBuffer, (*bpBuffer)->ui8BufferSize);
  }
}

//! Amount of pending data function getter for buffer.
/*!
  Get the amount of pending data on a circular buffer. This function is incompatible with circular buffer types.
  \param bpBuffer is a buffer_t pointer. This parameter is the address of buffer.
  \return Returns the amount of pending data.
*/
uint8_t ui8GetAmountOfPendingData(buffer_t* bpBuffer){
  return bpBuffer->ui8AmountOfData;
}

//! Buffer cleaner function
/*!
  Clean a buffer. This function is incompatible with circular buffer types.
  \param bpBuffer is a buffer_t pointer. This parameter is the address of buffer.
*/
void vCleanBuffer(buffer_t* bpBuffer){
  bpBuffer->ui8ReadPosition = 0;
  bpBuffer->ui8WritePosition = 0;
  bpBuffer->ui8AmountOfData = 0;
}
