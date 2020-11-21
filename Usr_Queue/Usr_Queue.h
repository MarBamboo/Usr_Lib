/**@file  TypeDef.h
* @brief       通用定义
* @details  主要包含变量声明的重定义和字节操作
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

#ifndef _USR_QUEUE_H_
#define _USR_QUEUE_H_
#include "TypeDef.h"



#define CQ_INIT(q)          ((q)->wHead = (q)->wTail = 0)
#define CQ_GET_DATA_LEN(q)   (((q)->wTail + (q)->wMaxSize - (q)->wHead) % q->wMaxSize)
#define CQ_GET_EMPT_LEN(q)   ((q)->wMaxSize - 1 - CQ_GET_DATA_LEN(q))

#define CQ_WRITE(q, var)    { (q)->pBuf[(q)->wTail] = (var); (q)->wTail = (((q)->wTail + 1) % q->wMaxSize); }
#define CQ_READ(q, var)     { (var) = (q)->pBuf[(q)->wHead];}
#define CQ_DELETE(q)        { (q)->wHead = (((q)->wHead + 1) % q->wMaxSize); }


typedef  struct
{
    uint16      wMaxSize;
    uint16		wHead;
    uint16		wTail;
    uint8		*pBuf;
} T_CQueue;

T_CQueue* CQ_Create(uint16 wMaxSize);

uint16 CQ_WriteMul(T_CQueue* tpCirQue, uint8* bypVar, uint16 wVarLen);
uint16 CQ_ReadMul(T_CQueue* tpCirQue, uint16 wIndex, uint16 wNum, uint8* bypObjBuf, uint16 wObjBufLen);
void CQ_DeleteMul(T_CQueue* tpCirQue, uint16 wNum);

#endif /* !_USR_QUEUE_H_*/