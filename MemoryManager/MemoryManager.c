#include "MemoryManager.h"

//! Function: Memory Manager Initializer
/*!
  Initialize the memory manager.
  \return Returns MEMORY_MANAGER_INITIALIZED if initialization is successful or MEMORY_MANAGER_NOT_INTIALIZED in contrary case.
*/
uint8_t ui8MemoryManagerInit(void){
  /*if (ui8ListManagerInit() != LIST_INIT_SUCESS){
    return MEMORY_MANAGER_NOT_INTIALIZED;
  }*/
  return MEMORY_MANAGER_INITIALIZED;
}
