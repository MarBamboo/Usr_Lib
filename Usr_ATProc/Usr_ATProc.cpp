#include "Usr_ATProc.h"
#include "Usr_Memory.h"
#include "Usr_Timer.h"
#include "Usr_Debug.h"

int Find(const uint8* buff, const int length, int nStart, const uint8* buff1, const int16 len1)
{
	int i = 0;
	if (nStart + length > len1)
	{
		return -1;
	}

	for (i = nStart; i < len1; i++)
	{
		if (buff1[i] == buff[0])
		{
			if ((i + length) > len1)
			{
				return -2;
			}
			if (memcmp(&buff1[i], buff, length) == 0)
			{
				return i;
			}
		}
	}
	return -3;
}

void At_ProcFun_Reset(T_AtRspProcHandle* ptAtH)
{
	if (ptAtH != NULL)
	{
		TIMER_Stop(&ptAtH->tDecodeDrmTimer);
		ptAtH->wIndex = 0;
	}
}

/**@brief 初始化一个数据解析句柄，绑定参数
* @param[in]  uint16 wFrmMaxLen               单个数据帧最长字节
* @param[in]  uint16 wCqBufMaxLen             存储数据帧循环队列最大缓存
* @return  获取的数据解析句柄地址
*/
T_AtRspProcHandle* At_ProcFun_Init(uint16 wFrmMaxLen, uint16 wCqBufMaxLen)
{
	uint8* pFrm;
	T_AtRspProcHandle* ptAtH;
	T_CQueue* ptCq;

	//get cycle queue
	ptCq = CQ_Create(wCqBufMaxLen);
	if (ptCq == NULL)
	{
		return NULL;
	}

	//get handle
	pFrm = (uint8*)Mem_Malloc(wFrmMaxLen);
	ptAtH = (T_AtRspProcHandle*)Mem_Malloc(sizeof(T_AtRspProcHandle));
	if ((pFrm == NULL) || (ptAtH == NULL))
	{
		Mem_Free(pFrm);
		Mem_Free(ptAtH);
		return NULL;
	}

	//band
	ptAtH->ptCirQue = ptCq;
	ptAtH->pbyData = pFrm;
	ptAtH->wDataMaxSize = wFrmMaxLen;


	//reset
	At_ProcFun_Reset(ptAtH);

	//
	ptAtH->byAtRspErrNum = 0;


	return ptAtH;
}


/**@brief 初始化一个数据解析句柄，绑定参数
* @param[in]  T_DecodeHandle* ptD               数据解析结构体句柄
* @return  获取的数据解析句柄地址
*/
void At_ProcFun_Destroy(T_AtRspProcHandle* ptAtH)
{
	if (ptAtH != NULL)
	{
		Mem_Free(ptAtH->ptCirQue->pBuf);
		Mem_Free(ptAtH->ptCirQue);
		Mem_Free(ptAtH->pbyData);
		Mem_Free(ptAtH);
	}
}

/**@brief 处理AT命令的OK与Error回复
* @param[in]  T_DecodeHandle* ptD               数据解析结构体句柄
* @return 
*/
int GprsAtRsp_W_OkOrErr(const uint8* pData, const uint16 wDataLen)
{
	const static uint8 aAtRspCmdLen_OK = 2;
	const static uint8 aAtRspCmd_OK[] = { "OK" };

	const static uint8 aAtRspCmdLen_ERROR = 5;
	const static uint8 aAtRspCmd_ERROR[] = { "ERROR"};

	uint8 i;
	int uLoc;
	//step 1: Find At response head flag
	for (i = 0; i < aAtRspCmdLen_OK; ++i)
	{
		if (pData[i] != aAtRspCmd_OK[i])
		{
			break;
		}
	}

	if (i == aAtRspCmdLen_OK)
	{
		return aAtRspCmdLen_OK;
	}
	
	for (i = 0; i < aAtRspCmdLen_ERROR; ++i)
	{
		if (pData[i] != aAtRspCmd_ERROR[i])
		{
			break;
		}
	}

	if (i == aAtRspCmdLen_ERROR)
	{
		return -aAtRspCmdLen_ERROR;
	}

	return 0;
}

int GprsAtRsp_W_CipRxGet_2(const uint8* pData, const uint16 wDataLen)
{
	return 0;
}

int GprsAtRsp_W_CipSend(const uint8* pData, const uint16 wDataLen)
{
	return 0;
}

#define AT_RSP_URC_FUN	(2)

typedef struct 
{
	const char* pAtRsp;
	const uint8 byAtRspLen;
	PFN_AtRspProc CallBackFun;
}T_AtCmdRspCb;

T_AtCmdRspCb AtRspProcGroup[] = {
									"OK", 2, GprsAtRsp_W_CipRxGet_2,
									"+CIPSEND:", 9, GprsAtRsp_W_CipSend,
};


BOOLE GprsAtRsp_Handle(T_AtRspProcHandle* ptAtH, PFN_AtRspProc pFun, uint16 wCostTimes)
{

	uint8 uAtFlag[2] = {0};
	

	const char* p = "OK";

	BOOLE bRet = FALSE;
	int uRet = 0;
	uint16 wReadNum = 0;

	uint8 byUrcFunOrder = 0;

	T_Timer TimWaitAtRsp;
	T_Timer tWaitWholeAtRsp;
	TIMER_SetDelay(&TimWaitAtRsp, wCostTimes);
	TIMER_Start(&TimWaitAtRsp);
	TIMER_Stop(&tWaitWholeAtRsp);

	do {
			wReadNum = CQ_ReadMul(ptAtH->ptCirQue, ptAtH->wIndex, 1, &ptAtH->pbyData[ptAtH->wIndex], ptAtH->wDataMaxSize);
			if (wReadNum)
			{
				ptAtH->wIndex += wReadNum;
				if (!TIMER_GetSta(&tWaitWholeAtRsp))
				{
					TIMER_SetDelay(&tWaitWholeAtRsp, 2000);
					TIMER_Start(&tWaitWholeAtRsp);
				}
			}

			//process active Sent AT Cmd 
			if (ptAtH->wIndex > 2)
			{
				if (pFun == GprsAtRsp_W_CipSend)
				{
					uRet = GprsAtRsp_W_CipSend(ptAtH->pbyData, ptAtH->wIndex);
					if (uRet != 0)
					{
						bRet = (uRet > 0) ? TRUE : FALSE;
						CQ_DeleteMul(ptAtH->ptCirQue, ptAtH->wIndex);
						ptAtH->wIndex = 0;
						TIMER_Stop(&tWaitWholeAtRsp);
						break;
					}
				}
				else
				{
					if ((ptAtH->pbyData[ptAtH->wIndex - 2] == '\r') && (ptAtH->pbyData[ptAtH->wIndex - 1] == '\n'))
					{
						ptAtH->pbyData[ptAtH->wIndex] = 0;
						if (pFun != NULL)
						{
							uRet = pFun(ptAtH->pbyData, ptAtH->wIndex);
							if (uRet != 0)
							{
								bRet = (uRet > 0) ? TRUE : FALSE;
								CQ_DeleteMul(ptAtH->ptCirQue, ptAtH->wIndex);
								ptAtH->wIndex = 0;
								TIMER_Stop(&tWaitWholeAtRsp);
								break;
							}
						}
					}
				}
			}

			/*//process URC AT Rsp
			if (ptAtH->wIndex > 5)
			{
				if ((ptAtH->pbyData[ptAtH->wIndex - 2] == '\r') && (ptAtH->pbyData[ptAtH->wIndex - 1] == '\n'))
				{
					ptAtH->pbyData[ptAtH->wIndex] = 0;
					for (byUrcFunOrder = 0; byUrcFunOrder < AT_RSP_URC_FUN; byUrcFunOrder++)
					{
						uRet = AtRspProcGroup[byUrcFunOrder](ptAtH->pbyData, ptAtH->wIndex);
						if (uRet != 0)
						{
							break;
						}
					}
					CQ_DeleteMul(ptAtH->ptCirQue, ptAtH->wIndex);
					ptAtH->wIndex = 0;
					TIMER_Stop(&tWaitWholeAtRsp);
				}
			}*/


			//filtering
			if ((ptAtH->pbyData[0] == '\r') || ((ptAtH->pbyData[0] == '\n')))
			{
				CQ_DeleteMul(ptAtH->ptCirQue, 1);
				ptAtH->wIndex = 0;
				TIMER_Stop(&tWaitWholeAtRsp);
			}
			else if (ptAtH->wIndex > 2)
			{
				if ((ptAtH->pbyData[ptAtH->wIndex - 2] == '\r') && (ptAtH->pbyData[ptAtH->wIndex - 1] == '\n'))
				{
					ptAtH->pbyData[ptAtH->wIndex] = 0;
					//遍历所以at回复标识
					for (uint8 i = 0; i < AT_RSP_URC_FUN; ++i)
					{
						if (0 != memcmp(AtRspProcGroup[i].pAtRsp, ptAtH->pbyData, AtRspProcGroup[i].byAtRspLen))
						{
							AtRspProcGroup[i].CallBackFun(ptAtH->pbyData, ptAtH->wIndex);
						}						
					}
				}
			}





			if (TIMER_Elapsed(&tWaitWholeAtRsp))
			{
				CQ_DeleteMul(ptAtH->ptCirQue, ptAtH->wIndex);
				ptAtH->wIndex = 0;
			}
		}while (!TIMER_Elapsed(&TimWaitAtRsp));


	if (pFun != NULL)
	{
		Dbg_Trace("At Response Cost time : %d\r\n", TIMER_CostTimes(&TimWaitAtRsp));
		if (bRet == TRUE)
		{
			ptAtH->byAtRspErrNum = 0;
		}
		else
		{
			++ptAtH->byAtRspErrNum;
			Dbg_Trace("At Response :error   %d\r\n", ptAtH->byAtRspErrNum);
		}
	}

	if (ptAtH->byAtRspErrNum >= 10)
	{
		ptAtH->byAtRspErrNum = 0;
	}



	return bRet;
}


