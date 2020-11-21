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

#include "Usr_Queue.h"
#include "stdio.h"
#include "stdlib.h"
#include "Usr_Debug.h"
#include "Usr_Memory.h"


/**@brief ������ʼ��һ��ѭ������
* @param[in]  T_CQueue* tpCirQue         ���нṹ��
* @param[in]  uint8* pBuf                       ��������Buffer
* @param[in]  uint16 wMaxSize                   ��������Buffer��С
* @return  �ɹ����Byte��
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

/**@brief ѭ������β��������ֵ
* @param[in]  T_CQueue* tpCirQue           ���нṹ��
* @param[in]  uint8* bypVar                       �������ָ��
* @param[in]  uint16 wVarLen                      �������ָ��ֵ����
* @return  ����ִ�н��
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

/**@brief ��ѭ��������ƫ��λ�ö�ȡ������ֵ
* @param[in]  T_CQueue* tpCirQue                ���нṹ��
* @param[in]  uint16 wIndex                     ����ƫ��λ��
* @param[in]  uint16 wNum                       ��Ҫ��ȡ������
* @param[in]  uint8* bypObjBuf                  �������ָ��
* @param[in]  uint16 wObjBufLen                 ��������С
* @return  �ɹ����Byte��
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


/**@brief ��ѭ��������ɾ�����ֵ
* @param[in]  T_CQueue* tpCirQue           ���нṹ��
* @param[in]  uint16 wNum                         ɾ������
* @return  ����ִ�н��
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




