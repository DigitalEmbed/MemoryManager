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

#ifndef Bits_H
#define Bits_H

#include <inttypes.h>

//! Macro: Set a Bit
/*!
  Set a bit of a number.
  \param uiNumber is an undefined parameter.It is the number that will have it bit seted.
  \param uiPosition is an undefined parameter. Position 0 is the least significant bit in the number.
*/
#define       vSetBit(uiNumber, uiPosition)                                                                     (uiNumber) |= (1 << (uiPosition))

//! Macro: Set Bits
/*!
  Set several bits of a number.
  \param uiNumber is an undefined parameter. It is the number that will have your bits seted.
  \param uiPosition is an undefined parameter. Position 0 is the least significant bit in the number.
  \param uiNumberOfBits is an undefined parameter. It is the number of bits that will be set.
*/
#define       vSetBits(uiNumber, uiPosition, uiNumberOfBits)                                                    (uiNumber) |= ((uiNumberOfBits) << (uiPosition))

//! Macro: Set a Byte
/*!
  Set a byte of a number.
  \param uiNumber is an undefined parameter. It is the number that will have it byte seted.
  \param uiPosition is an undefined parameter. Position 0 is the least significant bit in the number.
*/
#define       vSetByte(uiNumber, uiPosition)                                                                    (uiNumber) |= (255 << ((uiPosition) << 3))


//! Macro: Erase a Bit
/*!
  Erase a bit of a number.
  \param uiNumber É um parâmetro indefinido. É o número que terá seu bit apagado.
*/
#define       vEraseBit(uiNumber, uiPosition)                                                                   (uiNumber) &= ~(1 << (uiPosition))

//! Macro: Erase Bits
/*!
  Erase several bits of a number.
  \param uiNumber is an undefined parameter. It is the number that will have your bits erased.
  \param uiPosition is an undefined parameter. Position 0 is the least significant number in the number.
  \param uiNumberOfBits is an undefined parameter. It is the number of bits that will be erase.
*/
#define       vEraseBits(uiNumber, uiPosition, uiNumberOfBits)                                                  (uiNumber) &= ~(((1 << (uiNumberOfBits)) - 1) << (uiPosition));

//! Macro: Erase a Byte
/*!
  Erase a byte of a number.
  \param uiNumber is an undefined parameter. It is the number that will have it byte deleted.
  \param uiPosition is an undefined parameter. Position 0 is the least significant bit in the number.
*/
#define       vEraseByte(uiNumber, uiPosition)                                                                  (uiNumber) &= ~(255 << ((uiPosition) << 3))

//! Macro: Read a Bit
/*!
  Read a bit of a number.
  \param uiNumber is an undefined parameter. It is the number that will have it bit readed.
  \param uiPosition is an undefined parameter. Position 0 is the least significant bit in the number.
  \return "Returns" the bit readed.
*/
#define       ui8ReadBit(uiNumber, uiPosition)                                                                  (((uiNumber) >> (uiPosition)) & 1)

//! Macro: Read Bits
/*!
  Returns a selection of bits of a number.
  \param uiNumber is an undefined parameter. It is the number that will have your bits selected.
  \param uiPositionByte is an undefined parameter. Position 0 is the least significant bit in the number.
  \param uiNumberOfBits It is an undefined parameter. It is the number of bits that will be erased.
  \return "Returns" bit selection of the "uiNumber" parameter.
*/
#define       uiReadBits(uiNumber, uiPosition, uiNumberOfBits)                                                  ((((1 << (uiNumberOfBits)) - 1) << (uiPosition)) & (uiNumber))

//! Macro: Read a Byte
/*!
  Read a byte of a number.
  \param uiNumber is an undefined parameter. It is the number that will have it byte readed.
  \param uiPosition is an undefined parameter. Position 0 is the least significant bit in the number.
  \return "Returns" the byte readed.
*/
#define       ui8ReadByte(uiNumber, uiPosition)                                                                 (((uiNumber) >> ((uiPosition) << 3)) & 255)

//! Macro: Invert a Bit
/*!
  Invert a bit of a number.
  \param uiNumber is an undefined parameter. It is the number that will have it bit inverted.
  \param uiPosition is an undefined parameter. Position 0 is the least significant bit in the number.
*/
#define       vInvertBit(uiNumber, uiPosition)                                                                  (uiNumber) ^= (1 << (uiPosition))

//! Macro: Invert All Bits
/*!
  Reverses all bits of a number.
  \param uiNumber is an undefined parameter. It is the number that will have its bits inverted.
*/
#define       vInvertAllBits(uiNumber)                                                                          (uiNumber) = ~(uiNumber) + 1

//! Macro: Copy Bits
/*!
  Copy bits from one number and paste them into another number.
  \param uiDestiny is an undefined parameter. It is the number that will have its bits replaced.
  \param uiDestinyBitPosition is an undefined parameter. Position 0 is the least significant digit of the "uiDestiny" parameter.
  \param uiNumber is an undefined parameter. It is the number that will have your bits selected.
  \param uiDestinyBitPosition is an undefined parameter. Position 0 is the least significant digit of the "uiNumber" parameter.
  \param uiNumberOfBits It is an undefined parameter. It is the bit_numberOfBits that will be copied.
*/
#define       vCopyBits(uiDestiny, uiDestinyBitPosition, uiNumber, uiNumberBitPosition, uiNumberOfBits)         vEraseBits((uiDestiny), (uiDestinyBitPosition), (uiNumberOfBits));\
                                                                                                                (uiDestiny) |= (((uiReadBits((uiNumber), (uiNumberBitPosition), (uiNumberOfBits))) >> (uiNumberBitPosition)) << (uiDestinyBitPosition));

//! Macro: Copy a Byte
/*!
  Copy a Byte from a number and paste it into another number.
  \param uiDestiny is an undefined parameter. It is the number that will have its bits replaced.
  \param uiDestinyBytePosition is an undefined parameter. Position 0 is the byte that contains the least significant digit of the "uiDestiny" parameter.
  \param uiNumber is an undefined parameter. It is the number that will have your bits selected.
  \param uiDestinyBytePosition is an undefined parameter. Position 0 is the byte that contains the least significant digit of the "uiNumber" parameter.
*/
#define       vCopyByte(uiDestiny, uiDestinyBytePosition, uiNumber, uiNumberBytePosition)                       vEraseByte((uiDestiny), (uiDestinyBytePosition));\
                                                                                                                (uiDestiny) |= (((uiNumber >> ((uiNumberBytePosition) << 3)) & 255) << (((uiDestinyBytePosition) << 3)))

//! Macro: Static Bit Vector Allocation
/*!
  This macro are for calculate the iNumber of cell of bit-vectors type.
*/
#define       uiBitVectorSize(uiNumberOfBits)                                                                   ((uiNumberOfBits) < 8) ? 1 : (((uiNumberOfBits) >> 3) + 1)

//! Macros: Bit Vector Position Calculus
/*!
  These macros are for calculate the uiPosition of cell of bit-vectors type and the bit uiPosition of iNumber of cell.
*/
#define       uiBitPosition(uiPosition)                                                                         ((uiBitVectorSize(uiPosition)) - (1))
#define       uiBytePosition(uiPosition)                                                                        ((uiPosition) & (7))

//! Macros: Bit Vector Manipulation
/*!
  These macros are for calculate the iNumber of cell of bit-vectors type.
*/
#define       vSetBitVector(bvBitVector, uiPosition)                                                            vSetBit(bvBitVector[(uiBitPosition(uiPosition))], (uiBytePosition(uiPosition)))
#define       vEraseBitVector(bvBitVector, uiPosition)                                                          vEraseBit(bvBitVector[(uiBitPosition(uiPosition))], (uiBytePosition(uiPosition)))
#define       ui8ReadBitVector(bvBitVector, uiPosition)                                                         ui8ReadBit(bvBitVector[(uiBitPosition(uiPosition))], (uiBytePosition(uiPosition)))

//! Type Definition: bitvector_t
/*!
  This typedef exist for organization purpose. This type is equivalent of a 8-bit unsigned integer.
*/
typedef uint8_t bitvector_t;

#define       xCreateBitVector(bvName, uiSize)                                                                  bitvector_t bvName[uiBitVectorSize(uiSize)]

#endif
