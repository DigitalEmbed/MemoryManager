//! Example 01 - Integer bit manipulation
/*!
  This simply example demonstrates the use of bit manipulation.

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
#include <Bits.h>

/*!
  Declaration of the character that will count the order of the processes...
*/
char cProcessCounter = 'A';

void vPrintBits(uint32_t ui32Number);                 /*!< Void type function. */

int main(){
  /*!
    A) Declaring a simple 32-bit variable...
  */
  uint32_t ui32Number = 7;
  vPrintBits(ui32Number);

  /*!
    B) Erasing bit from position 0 (least significant)...
  */
  vEraseBit(ui32Number, 0);
  vPrintBits(ui32Number);

  /*!
    C) Seting byte from position 1...
  */
  vSetByte(ui32Number, 1);
  vPrintBits(ui32Number);

  /*!
    D) Copying the first byte of number 0xFFFF and pasting in the last position...
  */
  vCopyByte(ui32Number, 3, 0xFFFF, 0);
  vPrintBits(ui32Number);

  /*!
    E) Copying 3 bits at position 0 of number 4 and pasting them into position 10...
  */
  vCopyBits(ui32Number, 10, 4, 0, 3)
  vPrintBits(ui32Number);
  return 0;
}

//! Function: Bit Printer
/*!
  Print all bits of a 32-bits integer.
  \param ui32Number is a 32-bits integer.
*/
void vPrintBits(uint32_t ui32Number){
  int8_t i8Counter = 32;
  printf("%c) ", cProcessCounter);
  for (i8Counter = 31 ; i8Counter > -1 ; i8Counter--){
    printf("%d", ui8ReadBit(ui32Number, i8Counter));
  }
  printf("\n");
  cProcessCounter++;
}
