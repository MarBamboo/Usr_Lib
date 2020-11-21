/**@file  Usr_Queue.cpp
* @brief       ͨ�ö���
* @details  ��Ҫ������ѭ�����еĲ���
* @author      MCL
* @date        2018-8-17
* @version     V1.0
* @copyright    GPL
**********************************************************************************
* @attention
* SDK�汾��v2050.0.0
* @par �޸���־:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/02/17  <td>1.0      <td>MCL		 <td>������ʼ�汾
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
 *  ��������֡ͨ�ýṹ��
 * @details
 */
typedef struct
{
	//banding
	T_CQueue* ptCirQue;			///<  ѭ������ָ��
	uint16 wDataMaxSize;		///<  ������֡���Bytes

	//Reset
	EM_DecodeFsm emDecodeFsm;	///<  ����֡����״̬

	T_DlmsFrm tDlmsFrm;			///<  ����֡Э��ʶ��ؼ���

	T_Timer tDecodeDrmTimer;	///<  ����֡���ճ�ʱ
	uint16 wIndex;				///<  ����֡�Ӷ�����Ԥȡֵλ��
	uint8* pbyData;				///<  ����ָ֡��
	uint16 wDataLen;			///<  ����֡����
}T_DecodeHandle;




EM_DecodeRet Dec_Frm(T_DecodeHandle* ptDecH);
T_DecodeHandle* Dec_Fun_Init(uint16 wFrmMaxLen, uint16 wCqBufMaxLen);
void Dec_Fun_Destroy(T_DecodeHandle* ptD);
int8 Dec_Fun_Fsm(T_DecodeHandle* ptDecHandle);
#endif // !_USR_DECODE_H_
