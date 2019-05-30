//! MemoryManager Version 1.0b
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

#ifndef BitVector_H
#define BitVector_H

#include <MemoryManager.h>
#include <inttypes.h>

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
