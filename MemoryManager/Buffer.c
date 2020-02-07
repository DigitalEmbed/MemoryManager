#include "./Configs.h"

#if (defined(__BUFFER_MANAGER_ENABLE__))

  #include "./Buffer.h"
  #include <stdio.h>
  #include <string.h>
  #include <EmbeddedTools.h>
  #include "./MemoryPool.h"
  #include "./DataBank.h"
  #include "./Queue.h"
  #include "./Stack.h"
  #include "./Circular.h"

  //! Function: Buffer Writer
  /*!
    Write a data on a buffer.
    \param bfBuffer is a buffer_structure_t pointer. This parameter is the address of buffer.
    \param vpData is a void pointer. This parameter is the data to be inserted on the buffer.
  */
  void Buffer_push(buffer_t bfBuffer, void* vpData){
    switch(bfBuffer->btBufferType){

      case BUFFER_TYPE_QUEUE:
        __QueueBuffer_push(bfBuffer, vpData);
        break;

      case BUFFER_TYPE_STACK:
        __StackBuffer_push(bfBuffer, vpData);
        break;

      case BUFFER_TYPE_CIRCULAR:
        __CircularBuffer_push(bfBuffer, vpData);
        break;

    }
  }

  //! Private Function: Buffer Reader
  /*!
    Pull buffer address data.
    \param bfBuffer is a buffer_t type. This parameter is a initialized buffer.
    \return Returns data buffer adress.
  */
  void* (Buffer_popAddress)(buffer_t bfBuffer){
    switch(bfBuffer->btBufferType){

      case BUFFER_TYPE_QUEUE:
        return __QueueBuffer_pop(bfBuffer);

      case BUFFER_TYPE_STACK:
        return __StackBuffer_pop(bfBuffer);

      case BUFFER_TYPE_CIRCULAR:
        return __CircularBuffer_pop(bfBuffer);

      default:
        return NULL;

    }
  }

  //! Function: Amount of Pending Data Getter
  /*!
    Get the amount of pending data on a circular buffer.
    \param bfBuffer is a buffer_structure_t pointer. This parameter is the address of buffer.
    \return Returns the amount of pending data.
  */
  uint8_t Buffer_getAmountOfPendingData(buffer_t bfBuffer){
    return bfBuffer->ui8AmountOfData;
  }

  //! Function: Buffer Cleaner
  /*!
    Clean a buffer.
    \param bfBuffer is a buffer_structure_t pointer. This parameter is the address of buffer.
  */
  void Buffer_clear(buffer_t bfBuffer){
    bfBuffer->ui8ReadPosition = 0;
    bfBuffer->ui8WritePosition = 0;
    bfBuffer->ui8AmountOfData = 0;
  }

  //! Function: Write Position Getter
  /*!
    Get the write position of buffer.
    \param bfBuffer is a buffer_structure_t pointer. This parameter is the address of buffer.
    \return Returns write position.
  */
  uint8_t Buffer_getWritePosition(buffer_t bfBuffer){
    return bfBuffer->ui8WritePosition;
  }

  //! Function: Read Position Getter
  /*!
    Get the read position of buffer.
    \param bfBuffer is a buffer_structure_t pointer. This parameter is the address of buffer.
    \return Returns read position.
  */
  uint8_t Buffer_getReadPosition(buffer_t bfBuffer){
    return bfBuffer->ui8ReadPosition;
  }

#endif
