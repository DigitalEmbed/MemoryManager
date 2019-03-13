//! Example 02 - Bit vector manipulation
/*!
  This simply example demonstrates the use of a bit vector.

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
  Creating the bit vector. Use as multiple sizes of 8 for less memory waste.
*/
xCreateBitVector(bvExample, 8);

int main(){
  /*!
    Seting vector bit position 0...
  */
  vSetBitVector(bvExample, 0);

  /*!
    Verifying that the action has been completed...
  */
  if (ui8ReadBitVector(bvExample, 0) == 1){
    printf("This position is seted!\n");
  }

  /*!
    Erasing vector bit position 0...
  */
  vEraseBitVector(bvExample, 0);

  /*!
    Verifying that the action has been completed...
  */
  if (ui8ReadBitVector(bvExample, 0) == 0){
    printf("Now, this position is unseted!\n");
  }

  return 0;
}
