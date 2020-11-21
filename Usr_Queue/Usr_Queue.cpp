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

#include "Usr_Queue.h"
#include "stdio.h"
#include "stdlib.h"
#include "Usr_Debug.h"
#include "Usr_Memory.h"


/**@brief 建立初始化一个循环队列
* @param[in]  T_CQueue* tpCirQue         队列结构体
* @param[in]  uint8* pBuf                       队列链接Buffer
* @param[in]  uint16 wMaxSize                   队列链接Buffer大小
* @return  成功输出Byte数
*/
T_CQueue* CQ_Create(uint16 wMaxSize)
{   
    uint8* pBuf = NULL;
    T_CQueue* ptCq = NULL;

    pBuf = (uint8*)Mem_Malloc(wMaxSize);
    ptCq = (T_CQueue*)Mem_Malloc(sizeof(T_CQueue));

    if ((pBuf == NULL) || (ptCq == NULL))
    {
        Mem_Free(pBuf);
        Mem_Free(ptCq);
        return NULL;
    }

    ptCq->wMaxSize = wMaxSize;
    ptCq->pBuf = pBuf;
    ptCq->wHead = 0;
    ptCq->wTail = 0;

    return ptCq;
}

void CQ_Destroy(T_CQueue* tpCq)
{
    if (tpCq != 0)
    {
        Mem_Free(tpCq->pBuf);
        Mem_Free(tpCq);
    }
}

/**@brief 循环队列尾部插入多个值
* @param[in]  T_CQueue* tpCirQue           队列结构体
* @param[in]  uint8* bypVar                       插入队列指针
* @param[in]  uint16 wVarLen                      插入队列指针值数量
* @return  函数执行结果
*/
uint16 CQ_WriteMul(T_CQueue*  tpCirQue, uint8* bypVar, uint16 wVarLen)
{
    uint16 i = 0;

    for (i = 0; (CQ_GET_EMPT_LEN(tpCirQue) > 0) && (i < wVarLen); ++i)
    {
        CQ_WRITE(tpCirQue, bypVar[i]);        
    }

    return i;
}

/**@brief 从循环队列中偏移位置读取连续的值
* @param[in]  T_CQueue* tpCirQue                队列结构体
* @param[in]  uint16 wIndex                     队列偏移位置
* @param[in]  uint16 wNum                       需要读取的数量
* @param[in]  uint8* bypObjBuf                  输出缓存指针
* @param[in]  uint16 wObjBufLen                 输出缓存大小
* @return  成功输出Byte数
*/
uint16 CQ_ReadMul(T_CQueue*  tpCirQue, uint16 wIndex, uint16 wNum, uint8* bypObjBuf, uint16 wObjBufLen)
{
    uint16 i = 0,k = 0;
    uint16 wTmpLen;
    wTmpLen = CQ_GET_DATA_LEN(tpCirQue) - wIndex;

    if (wNum > wObjBufLen)
    {
        wNum = wObjBufLen;
    }

    for (i = 0; (wTmpLen > 0) && (i < wNum); ++i, --wTmpLen)
    {
        k = (tpCirQue->wHead + wIndex + i) % tpCirQue->wMaxSize;
        bypObjBuf[i] = tpCirQue->pBuf[k];
    }
  
    return i;

}


/**@brief 从循环队列中删除多个值
* @param[in]  T_CQueue* tpCirQue           队列结构体
* @param[in]  uint16 wNum                         删除个数
* @return  函数执行结果
*/
void CQ_DeleteMul(T_CQueue*  tpCirQue, uint16 wNum)
{  
    uint16 wTmpLen;
    wTmpLen = CQ_GET_DATA_LEN(tpCirQue);
    if (wTmpLen)
    {
        if (wNum > wTmpLen)
        {
            wNum = wTmpLen;
        }
        tpCirQue->wHead = ((tpCirQue->wHead + wNum) % tpCirQue->wMaxSize);
    }
}




