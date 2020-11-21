#ifndef _USR_AT_PROC_H_
#define _USR_AT_PROC_H_

#include "TypeDef.h"
#include "Usr_Queue.h"
#include "Usr_Timer.h"

typedef enum
{
    AT_RSP_RET_SUC,
    AT_RSP_RET_ERR,
    AT_RSP_RET_ING,
}EM_AtRspRet;


typedef enum
{
	DECODE_AT_FSM_HEAD,
	DECODE_AT_FSM_DATA,
	DECODE_AT_FSM_TAIL,

	DECODE_AT_FSM_UNKNOWN,
}EM_AtRspDecodeFsm;



/**
 * @brief
 *  处理AT回复帧通用结构体
 * @details
 */
typedef struct
{
	//banding
	T_CQueue* ptCirQue;			///<  循环队列指针
	uint8* pbyData;				///<  数据帧指针
	uint16 wDataMaxSize;		///<  单帧AT指令最大Bytes

	//Reset
	T_Timer tDecodeDrmTimer;	///<  AT回复接收超时
	uint16 wIndex;				///<  数据帧从队列中预取值位置

	//UnReset
	uint8 byAtRspErrNum;			///<  记录AT回复错误

}T_AtRspProcHandle;

typedef int(*PFN_AtRspProc) (const uint8* pData, const uint16 wDataLen);

int GprsAtRsp_W_OkOrErr(const uint8* pData, const uint16 wDataLen);
int GprsAtRsp_W_CipRxGet_2(const uint8* pData, const uint16 wDataLen);













T_AtRspProcHandle* At_ProcFun_Init(uint16 wFrmMaxLen, uint16 wCqBufMaxLen);
void At_ProcFun_Destroy(T_AtRspProcHandle* ptAtH);







BOOLE GprsAtRsp_Handle(T_AtRspProcHandle* ptAtH, PFN_AtRspProc pFun, uint16 wCostTimes);


#endif // !_USR_AT_PROC_H_
