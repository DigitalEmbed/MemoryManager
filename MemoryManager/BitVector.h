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

#ifndef __BIT_VECTOR_HEADER__
  #define __BIT_VECTOR_HEADER__

  #include "./Configs.h"

  #if defined(__BIT_VECTOR_MANAGER_ENABLE__)

    #ifdef __cplusplus
      extern "C" {
    #endif

    #include <stdint.h>
    #include <EmbeddedTools.h>

    //! Type Definition: bitvector_t
    /*!
      This typedef exist for organization purpose. This type is equivalent of a 8-bit unsigned integer.
    */
    typedef uint8_t bitvector_t;

    //! Macro: Static Bit Vector Allocation
    /*!
      This macro is for calculate the size of cell of bit-vectors type.
      \param uiAmountOfBit is a unsigned integer. It's a desirable amount of bits.
      \return Returns real uint8_t vector size.
    */
    #define BitVector_getSize(uiAmountOfBit)\
      (((uiAmountOfBit) < 8) ? 1 : (((uiAmountOfBit - 1) >> 3) + 1))

    //! Macro: Bit Vector Creator
    /*!
      This macro creates a bit vector.
      \param bvName is a bit vector name.
      \param uiAmountOfBit is a unsigned integer. It's the desirable amount of bits. If possible, chose a 8 multiple number.
    */
    #define newBitVector(bvName, uiAmountOfBit)\
      bitvector_t bvName[BitVector_getSize(uiAmountOfBit)] = {0}

    //! Macro: Static Bit Vector Creator
    /*!
      This macro creates a static bit vector.
      \param bvName is a bit vector name.
      \param uiAmountOfBit is a unsigned integer. It's the desirable amount of bits. If possible, chose a 8 multiple number.
    */
    #define newStaticBitVector(bvName, uiAmountOfBit)\
      static bitvector_t bvName[BitVector_getSize(uiAmountOfBit)] = {0}

    //! Macro: Bit Position Calculus
    /*!
      These macros are for calculate the bit position of bit-vectors type.
      \param uiPosition is a unsigned integer. It's the desirable position.
      \return Returns bit position.
    */
    #define BitVector_getBytePosition(uiPosition)\
      (((uiPosition) < 8) ? 0 : ((uiPosition) >> 3))

    //! Macro: Bit Position Calculus
    /*!
      These macros are for calculate the position of cell of bit-vectors.
      \param uiPosition is a unsigned integer. It's the desirable position.
      \return Returns byte position.
    */
    #define BitVector_getBitPosition(uiPosition)\
      ((uiPosition) & (7))

    //! Macro: Bit Vector Setter
    /*!
      Sets a bit of bit vector.
      \param bvBitVector is a bit_vector_t type. It's the bit vector.
      \param uiPosition is a unsigned integer. It's the desirable position.
    */
    #define BitVector_setBit(bvBitVector, uiPosition)\
      Bitwise_setBit(bvBitVector[(BitVector_getBytePosition(uiPosition))], (BitVector_getBitPosition(uiPosition)))

    //! Macro: Bit Vector Eraser
    /*!
      Erases a bit of bit vector.
      \param bvBitVector is a bit_vector_t type. It's the bit vector.
      \param uiPosition is a unsigned integer. It's the desirable position.
    */
    #define BitVector_clearBit(bvBitVector, uiPosition)\
      Bitwise_clearBit(bvBitVector[(BitVector_getBytePosition(uiPosition))], (BitVector_getBitPosition(uiPosition)))

    //! Macro: Bit Vector Reader
    /*!
      Reads a bit of bit vector.
      \param bvBitVector is a bit_vector_t type. It's the bit vector.
      \param uiPosition is a unsigned integer. It's the desirable position.
    */
    #define BitVector_readBit(bvBitVector, uiPosition)\
      Bitwise_readBit(bvBitVector[(BitVector_getBytePosition(uiPosition))], (BitVector_getBitPosition(uiPosition)))

    #ifdef __cplusplus
      }
    #endif

  #endif
#endif
