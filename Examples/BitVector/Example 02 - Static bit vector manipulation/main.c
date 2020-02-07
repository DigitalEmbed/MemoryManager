//! Example 02 - Static bit vector manipulation
/*!
  This simply example demonstrates the use of bit vector manipulation.

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
#include <stdbool.h>
#include <MemoryManager.h>

int main(){
  /*!
    A) Declaring a bit vector...
    Always try to define the size with multiple numbers of 8!
    All bits is 0!
  */
  newStaticBitVector(bvMyFlags, 16);

  /*!
    B) Declaring a bool vector (for comparations purpose only)...
  */
  bool bBoolVector[16] = {false};

  /*!
    C) Comparing...
  */
  printf("Size of bBoolVector: %d bytes\n", (int) sizeof(bBoolVector));
  printf("Size of bvMyFlags: %d bytes\n\n", (int) sizeof(bvMyFlags));

  /*!
    C) Reading bit 4...
  */
  printf("Bit 4 value: %d\n\n", BitVector_readBit(bvMyFlags, 4));

  /*!
    D) Setting bit 4...
  */
  BitVector_setBit(bvMyFlags, 4);

  /*!
    E) Reading bit 4...
  */
  printf("Bit 4 value: %d\n\n", BitVector_readBit(bvMyFlags, 4));

  /*!
    F) Erasing bit 4...
  */
  BitVector_clearBit(bvMyFlags, 4);

  /*!
    E) Reading bit 4...
  */
  printf("Bit 4 value: %d\n", BitVector_readBit(bvMyFlags, 4));
  return 0;
}

