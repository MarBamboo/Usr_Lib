/**@file  Usr_Queue.cpp
* @brief       通用队列
* @details  主要包含对循环队列的操作
* @author      MCL
* @date        2018-8-17
* @version     V1.0
* @copyright    GPL
**********************************************************************************
* @attention
* SDK版本：v2050.0.0
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/02/17  <td>1.0      <td>MCL		 <td>创建初始版本
* </table>
*
**********************************************************************************
*/

#ifndef _USR_DECODE_H_
#define _USR_DECODE_H_
#include "TypeDef.h"
#include "Usr_Timer.h"
#include "Usr_Queue.h"

typedef enum
{
	DECODE_RET_ING,
	DECODE_RET_SUC,

	DECODE_RET_ERROR,
	DECODE_RET_UNKNOWN,
}EM_DecodeRet;

typedef enum
{
	DECODE_DLMS_FSM_HEAD,
	DECODE_DLMS_FSM_TYPE_LEN_CMD,
	DECODE_DLMS_FSM_CRC16,
	DECODE_DLMS_FSM_TAIL,

	DECODE_DLMS_FSM_UNKNOWN,
}EM_DecodeFsm;

typedef struct
{
	uint8 byHead;
	uint8 byType;
	uint16 wLen;
	uint8 byCmd;
	uint16 wCrc16;
	uint8 byTail;
}T_DlmsFrm;


/**
 * @brief
 *  处理数据帧通用结构体
 * @details
 */
typedef struct
{
	//banding
	T_CQueue* ptCirQue;			///<  循环队列指针
	uint16 wDataMaxSize;		///<  单数据帧最大Bytes

	//Reset
	EM_DecodeFsm emDecodeFsm;	///<  数据帧处理状态

	T_DlmsFrm tDlmsFrm;			///<  数据帧协议识别关键字

	T_Timer tDecodeDrmTimer;	///<  数据帧接收超时
	uint16 wIndex;				///<  数据帧从队列中预取值位置
	uint8* pbyData;				///<  数据帧指针
	uint16 wDataLen;			///<  数据帧长度
}T_DecodeHandle;




EM_DecodeRet Dec_Frm(T_DecodeHandle* ptDecH);
T_DecodeHandle* Dec_Fun_Init(uint16 wFrmMaxLen, uint16 wCqBufMaxLen);
void Dec_Fun_Destroy(T_DecodeHandle* ptD);
int8 Dec_Fun_Fsm(T_DecodeHandle* ptDecHandle);
#endif // !_USR_DECODE_H_
