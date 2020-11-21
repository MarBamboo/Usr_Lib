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
 *  ����AT�ظ�֡ͨ�ýṹ��
 * @details
 */
typedef struct
{
	//banding
	T_CQueue* ptCirQue;			///<  ѭ������ָ��
	uint8* pbyData;				///<  ����ָ֡��
	uint16 wDataMaxSize;		///<  ��֡ATָ�����Bytes

	//Reset
	T_Timer tDecodeDrmTimer;	///<  AT�ظ����ճ�ʱ
	uint16 wIndex;				///<  ����֡�Ӷ�����Ԥȡֵλ��

	//UnReset
	uint8 byAtRspErrNum;			///<  ��¼AT�ظ�����

}T_AtRspProcHandle;

typedef int(*PFN_AtRspProc) (const uint8* pData, const uint16 wDataLen);

int GprsAtRsp_W_OkOrErr(const uint8* pData, const uint16 wDataLen);
int GprsAtRsp_W_CipRxGet_2(const uint8* pData, const uint16 wDataLen);













T_AtRspProcHandle* At_ProcFun_Init(uint16 wFrmMaxLen, uint16 wCqBufMaxLen);
void At_ProcFun_Destroy(T_AtRspProcHandle* ptAtH);







BOOLE GprsAtRsp_Handle(T_AtRspProcHandle* ptAtH, PFN_AtRspProc pFun, uint16 wCostTimes);


#endif // !_USR_AT_PROC_H_
