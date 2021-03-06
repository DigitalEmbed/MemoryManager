#include "./Configs.h"

#if defined(__BUFFER_MANAGER_ENABLE__)

  #include "./Stack.h"
  #include <string.h>

  //! Private Function: Stack Buffer Writer
  /*!
    Write a data on a stack buffer.
    \param bfBuffer is a buffer_handler_t pointer. This parameter is the address of circular buffer.
    \param vpData is a void pointer. This parameter is the data to be inserted on the buffer.
  */
  void __StackBuffer_push(buffer_t bfBuffer, void* vpData){
    bfBuffer->ui8ReadPosition = bfBuffer->ui8WritePosition;
    void* vpAdressBuffer = (char*) bfBuffer->vpVector + bfBuffer->ui8WritePosition * bfBuffer->ui8ElementSize;
    if (vpData != NULL){
      memcpy(vpAdressBuffer, vpData, bfBuffer->ui8ElementSize);
    }
    else{
      memset(vpAdressBuffer, 0, bfBuffer->ui8ElementSize);
    }
    if (bfBuffer->ui8WritePosition == bfBuffer->ui8BufferSize - 1){
      bfBuffer->ui8WritePosition = 0;
    }
    else{
      bfBuffer->ui8WritePosition++;
    }
    if (bfBuffer->ui8AmountOfData < bfBuffer->ui8BufferSize){
      bfBuffer->ui8AmountOfData++;
    }
  }

  //! Private Function: Circular Buffer Reader
  /*!
    Read data on a circular buffer.
    \param bfBuffer is a buffer_handler_t pointer. This parameter is the address of circular buffer.
    \return Returns the adress of data on the buffer.
  */
  void* __StackBuffer_pop(buffer_t bfBuffer){
    if (bfBuffer->ui8AmountOfData > 0){
      void* vpAdressBuffer = (char*) bfBuffer->vpVector + bfBuffer->ui8ReadPosition * bfBuffer->ui8ElementSize;
      if (bfBuffer->ui8ReadPosition == 0){
        bfBuffer->ui8ReadPosition = bfBuffer->ui8BufferSize - 1;
      }
      else{
        bfBuffer->ui8ReadPosition--;
      }
      bfBuffer->ui8AmountOfData--;
      return vpAdressBuffer;
    }
    else{
      return NULL;
    }
  }

#endif
