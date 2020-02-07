//! MemoryManager Version 3.2b
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

#ifndef __BUFFER_HEADER__
  #define __BUFFER_HEADER__

  #include "./Configs.h"

  #if defined(__BUFFER_MANAGER_ENABLE__)

    #ifdef __cplusplus
      extern "C" {
    #endif

    #include <stdint.h>

    //! Enumeration Definition: Buffer Type
    /*!
      This typedef is for facilitate the use of this library.
    */
    typedef enum {
      BUFFER_TYPE_STACK = 0,
      BUFFER_TYPE_QUEUE,
      BUFFER_TYPE_CIRCULAR
    } buffer_type_t;

    //! Type Definition: Buffer Structure
    /*!
      Structure of circular buffer.
    */
    typedef struct {
      void* const vpVector;                                                                                                         /*!< const void pointer type. */
      const uint8_t ui8ElementSize;                                                                                                 /*!< const 8-bits integer type. */
      const uint8_t ui8BufferSize;                                                                                                  /*!< const 8-bits integer type. */
      uint8_t ui8ReadPosition;                                                                                                      /*!< 8-bits integer type. */
      uint8_t ui8WritePosition;                                                                                                     /*!< 8-bits integer type. */
      uint8_t ui8AmountOfData;                                                                                                      /*!< const 8-bits integer type. */
      const buffer_type_t btBufferType;                                                                                             /*!< const buffer_type_t type. */
    } buffer_structure_t;

    //! Type Definition: Buffer Pointer
    /*!
      This typedef is for facilitate the use of this library.
    */
    typedef buffer_structure_t* buffer_t;

    //! Private Function: Buffer Creator
    /*!
      Create a buffer.
      \param bfBufferName is a buffer name.
      \param btTypeOfBuffer is a buffer_type_t type. The available values are BUFFER_TYPE_STACK, BUFFER_TYPE_QUEUE or BUFFER_TYPE_CIRCULAR.
      \param xDataType is the type of receiving buffer data.
      \param ui8SizeOfBuffer is a 8-Bit integer. Its buffer size.
    */
    #define newBuffer(bfBufferName, btTypeOfBuffer, xDataType, ui8SizeOfBuffer)\
      xDataType __xBufferVector##bfBufferName[ui8SizeOfBuffer] = {0};\
      buffer_structure_t __bfhBufferStructure##bfBufferName = {\
        .vpVector = (void*) __xBufferVector##bfBufferName,\
        .ui8ElementSize = sizeof(xDataType),\
        .ui8BufferSize = ui8SizeOfBuffer,\
        .ui8ReadPosition = 0,\
        .ui8WritePosition = 0,\
        .ui8AmountOfData = 0,\
        .btBufferType = btTypeOfBuffer\
      };\
      buffer_t bfBufferName = &(__bfhBufferStructure##bfBufferName);\

    //! Private Function: Static Buffer Creator
    /*!
      Create a static buffer.
      \param bfBufferName is a buffer name.
      \param btTypeOfBuffer is a buffer_type_t type. The available values are BUFFER_TYPE_STACK, BUFFER_TYPE_QUEUE or BUFFER_TYPE_CIRCULAR.
      \param xDataType is the type of receiving buffer data.
      \param ui8SizeOfBuffer is a 8-Bit integer. Its buffer size.
    */
    #define newStaticBuffer(bfBufferName, btTypeOfBuffer, xDataType, ui8SizeOfBuffer)\
      static xDataType __xBufferVector##bfBufferName[ui8SizeOfBuffer] = {0};\
      static buffer_structure_t __bfhBufferHandler##bfBufferName = {\
        .vpVector = (void*) __xBufferVector##bfBufferName,\
        .ui8ElementSize = sizeof(xDataType),\
        .ui8BufferSize = ui8SizeOfBuffer,\
        .ui8ReadPosition = 0,\
        .ui8WritePosition = 0,\
        .ui8AmountOfData = 0,\
        .btBufferType = btTypeOfBuffer\
      };\
      static buffer_t bfBufferName = &__bfhBufferHandler##bfBufferName;

    //! Private Function: Pointer Buffer Data Getter
    /*!
      Pull buffer address data.
      \param bpBuffer is a buffer_t type. This parameter is a initialized buffer.
      \param xDataType is the type of receiving buffer data.
      \return Returns data buffer adress.
    */
    #define Buffer_popAddress(bfBuffer, xDataType)\
      ((xDataType*) Buffer_popAddress(bfBuffer))

    //! Macro: Content Buffer Data Getter
    /*!
      Pull buffer data. You can use this macro if you are ignoring 0 value in your buffer. In contrary case, you should use Buffer_popAddress.
      \param bpBuffer is a buffer_t type. This parameter is a initialized buffer.
      \param xDataType is the type of receiving buffer data.
      \return Returns buffer data.
    */
    #define Buffer_pop(bfBuffer, xDataType)\
      (*(Buffer_popAddress(bfBuffer, xDataType)))

    void Buffer_clear(buffer_t bfBuffer);                                                                                           /*!< void type function. */
    void Buffer_push(buffer_t bfBuffer, void* vpData);                                                                              /*!< void type function. */
    uint8_t Buffer_getAmountOfPendingData(buffer_t bfBuffer);                                                                       /*!< 8-bits integer type. */
    uint8_t Buffer_getWritePosition(buffer_t bfBuffer);                                                                             /*!< 8-bits integer type. */
    uint8_t Buffer_getReadPosition(buffer_t bfBuffer);                                                                              /*!< 8-bits integer type. */
    void* (Buffer_popAddress)(buffer_t bfBuffer);                                                                                   /*!< private void pointer type function. */

    #ifdef __cplusplus
      }
    #endif

  #endif
#endif
