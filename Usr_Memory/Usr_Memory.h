#ifndef _USR_MEMORY_H_
#define _USR_MEMORY_H_

#include "TypeDef.h"

void* Mem_Malloc(uint32 uSize);
void Mem_Free(void* p);
uint32 Mem_GetHeadUsdSize(void);



#endif // !_USR_MEMORY_H_
