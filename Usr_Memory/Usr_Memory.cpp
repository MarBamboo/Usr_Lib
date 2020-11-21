#include "Usr_Memory.h"

#define MEM_MAX_BLOCK	(12)

typedef struct
{
	uint8* pHead;
	uint8* pTail;
}T_MemUnit;

T_MemUnit tMemUnit[MEM_MAX_BLOCK] = {0};



void* Mem_Malloc(uint32 uSize)
{
	uint8* p;
	p = (uint8*)malloc(uSize);
	if (p != NULL)
	{
		uint16 i;
		for (i = 0; i < MEM_MAX_BLOCK; ++i)
		{
			if ((tMemUnit[i].pHead == NULL) && (tMemUnit[i].pTail == NULL))
			{
				tMemUnit[i].pHead = p;
				tMemUnit[i].pTail = p + uSize;
				break;
			}
		}
	}

	return p;
}


void Mem_Free(void* p)
{
	uint16 i;
	if (p != NULL)
	{

		for (i = 0; i < MEM_MAX_BLOCK; ++i)
		{
			if ((tMemUnit[i].pHead <= p) && (tMemUnit[i].pTail > p))
			{
				free(p);
				p = NULL;
				tMemUnit[i].pHead = NULL;
				tMemUnit[i].pTail = NULL;
				break;
			}
		}		
	}
}



uint32 Mem_GetHeadUsdSize(void)
{
	uint16 i;
	uint32 uMemUsdSize = 0;

	for (i = 0;  i < MEM_MAX_BLOCK; ++i)
	{
		if ((tMemUnit[i].pHead != NULL) && (tMemUnit[i].pTail != NULL))
		{
			uMemUsdSize += (tMemUnit[i].pTail - tMemUnit[i].pHead);
		}
	}

	return uMemUsdSize;
}