/**@file  Usr_Decode.cpp
* @brief       对数据帧进行解析
* @details      从队列中取出数据并进行解析
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
#include <iostream>
#include "Usr_Timer.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "Usr_Debug.h"

#include <Usr_Calendar.h>

#include "Usr_Decode.h"
#include "Usr_Timer.h"
#include "Usr_Queue.h"
#include "User_Crc.h"
#include "Usr_Memory.h"

#define DECODE_FRM_OVERTIME         (3)

/**@brief 初始化一个数据解析句柄
* @param[in]  T_DecodeHandle* ptDecHandle           数据解析句柄
* @return  函数执行结果
*/
void Dec_Fun_Reset(T_DecodeHandle* ptDecHandle)
{
    ptDecHandle->emDecodeFsm = DECODE_DLMS_FSM_HEAD;
    TIMER_Stop(&ptDecHandle->tDecodeDrmTimer);
    ptDecHandle->wDataLen = 0;
    ptDecHandle->wIndex = 0;
}


/**@brief 初始化一个数据解析句柄，绑定参数
* @param[in]  uint16 wFrmMaxLen               单个数据帧最长字节
* @param[in]  uint16 wCqBufMaxLen             存储数据帧循环队列最大缓存
* @return  获取的数据解析句柄地址
*/
T_DecodeHandle* Dec_Fun_Init(uint16 wFrmMaxLen, uint16 wCqBufMaxLen)
{
    uint8* pFrm;
    T_DecodeHandle* ptD;
    T_CQueue* ptCq;
    
    //get cycle queue
    ptCq = CQ_Create(wCqBufMaxLen);
    if (ptCq == NULL)
    {
        return NULL;
    }

    //get handle
    pFrm = (uint8*)Mem_Malloc(wFrmMaxLen);
    ptD = (T_DecodeHandle*)Mem_Malloc(sizeof(T_DecodeHandle));
    if ((pFrm == NULL) || (ptD == NULL))
    {
        Mem_Free(pFrm);
        Mem_Free(ptD);
        return NULL;
    }
  
    //band
    ptD->ptCirQue = ptCq;
    ptD->pbyData = pFrm;
    ptD->wDataMaxSize = wFrmMaxLen;

    //reset
    Dec_Fun_Reset(ptD);

    return ptD;
}



/**@brief 初始化一个数据解析句柄，绑定参数
* @param[in]  T_DecodeHandle* ptD               数据解析结构体句柄
* @return  获取的数据解析句柄地址
*/
void Dec_Fun_Destroy(T_DecodeHandle* ptD)
{
    if (ptD != NULL)
    {        
        Mem_Free(ptD->ptCirQue->pBuf);
        Mem_Free(ptD->ptCirQue);
        Mem_Free(ptD->pbyData);
        Mem_Free(ptD);
    }
}




/**@brief 用于统计接收到的数据帧，调试用
* @param[in]  T_DecodeHandle* ptD               数据解析结构体句柄
* @return  获取的数据解析句柄地址
*/
#define DEC_STATISTICS_FUN  (1)

#if (DEC_STATISTICS_FUN == 0)

#define DEC_STATISTICS(p)   { }

#elif (DEC_STATISTICS_FUN == 1)

#define DEC_STATISTICS(p)   Dec_Statistics(p);

uint32 uCmd42 = 0;
uint32 uCmd84 = 0;
extern uint32 lala;

void Dec_Statistics(T_DecodeHandle* ptD)
{
    if (ptD->tDlmsFrm.byCmd == 0x42)
    {
        uCmd42++;
    }

    if (ptD->tDlmsFrm.byCmd == 0x84)
    {
        uCmd84++;
    }

    if ((uCmd42 == 0xFFFFFFFF) || (uCmd84 == 0xFFFFFFFF))
    {
        printf("uCmd42===%d\n", uCmd42);
        printf("uCmd84===%d\n", uCmd84);
        system("pause");
    }

    if ((uCmd84 & 0xFFF) == 0)
    {
        printf("uCmd42===%x\n", uCmd42);
        printf("uCmd84===%x\n", uCmd84);
        printf("lala ===%x\n", lala);
        //system("pause");
    }
}

#endif






/**@brief 数据帧协议解析
* @param[in]  uint8* pbyData           待解析数据指针
* @param[in]  uint16 wDataLen           待解析数据长度
* @return  函数执行结果
*/
EM_DecodeRet Dec_Frm(T_DecodeHandle* ptDecH)
{
    EM_DecodeRet emRet;
    BOOLE bContinue;

    do
    {
        emRet = DECODE_RET_ING;
        bContinue = FALSE;

        switch (ptDecH->emDecodeFsm)
        {
        case DECODE_DLMS_FSM_HEAD:
            if (ptDecH->pbyData[0] == 0x7E)
            {
                ptDecH->tDlmsFrm.byHead = 0x7E;
                TIMER_SetDelay(&ptDecH->tDecodeDrmTimer, DECODE_FRM_OVERTIME);
                TIMER_Start(&ptDecH->tDecodeDrmTimer);

                ptDecH->emDecodeFsm = DECODE_DLMS_FSM_TYPE_LEN_CMD;

                bContinue = TRUE;
            }
            else if (TIMER_GetSta(&ptDecH->tDecodeDrmTimer) != TIM_OPEN)
            {
                emRet = DECODE_RET_ERROR;
            }
            else
            {
            }
            break;
        case DECODE_DLMS_FSM_TYPE_LEN_CMD:
            if (ptDecH->wIndex > 4)
            {
                ptDecH->tDlmsFrm.byType = ptDecH->pbyData[1] & 0xF0;
                ptDecH->tDlmsFrm.wLen = (uint16)((((uint16)ptDecH->pbyData[1] & 0x07) << 8) | ptDecH->pbyData[2]);
                ptDecH->tDlmsFrm.byCmd = ptDecH->pbyData[3];

                if ((ptDecH->tDlmsFrm.byType == 0x80)
                    || (ptDecH->tDlmsFrm.byType == 0xF0))
                {
                    ptDecH->emDecodeFsm = DECODE_DLMS_FSM_CRC16;
                    bContinue = TRUE;
                }
                else
                {
                    emRet = DECODE_RET_ERROR;
                }
            }
            break;
        case DECODE_DLMS_FSM_CRC16:
            if (ptDecH->wIndex > ptDecH->tDlmsFrm.wLen)
            {
                uint16 wTmpCrc16;

                wTmpCrc16 = CRC_Frm(&ptDecH->pbyData[1], ptDecH->tDlmsFrm.wLen - 2);
                ptDecH->tDlmsFrm.wCrc16 = MAKE_WORD(ptDecH->pbyData[ptDecH->tDlmsFrm.wLen], ptDecH->pbyData[ptDecH->tDlmsFrm.wLen - 1]);

                if (wTmpCrc16 == ptDecH->tDlmsFrm.wCrc16)
                {
                    ptDecH->emDecodeFsm = DECODE_DLMS_FSM_TAIL;
                    bContinue = TRUE;
                }
                else
                {
                    emRet = DECODE_RET_ERROR;
                }
            }
            break;
        case DECODE_DLMS_FSM_TAIL:
            if (ptDecH->wIndex > (1 + ptDecH->tDlmsFrm.wLen))
            {
                if (ptDecH->pbyData[1 + ptDecH->tDlmsFrm.wLen] == 0x7E)
                {
                    ptDecH->tDlmsFrm.byTail = 0x7E;
                    ptDecH->wDataLen = ptDecH->tDlmsFrm.wLen + 2;
                    ptDecH->emDecodeFsm = DECODE_DLMS_FSM_HEAD;
                    emRet = DECODE_RET_SUC;            //succed
                }
                else
                {
                    emRet = DECODE_RET_ERROR;
                }
            }
            break;
        default:
            emRet = DECODE_RET_UNKNOWN;
            break;
        }
    } while (bContinue == TRUE);


    return emRet;
}


/**@brief 数据帧协议解析
* @param[in]  T_DecodeHandle* ptDecHandle           数据解析结构体句柄
* @return  函数执行结果
*/
int8 Dec_Fun_Fsm(T_DecodeHandle* ptDecHandle)
{
    uint16 wReadNum = 0;
    EM_DecodeRet emRet;

    wReadNum = CQ_ReadMul(ptDecHandle->ptCirQue, ptDecHandle->wIndex, 120, &ptDecHandle->pbyData[ptDecHandle->wIndex], ptDecHandle->wDataMaxSize);
    if (wReadNum)
    {
        ptDecHandle->wIndex += wReadNum;
    }
    
    if(ptDecHandle->wIndex)
    {
        emRet = Dec_Frm(ptDecHandle);
        switch (emRet)
        {
        case DECODE_RET_ING:
            //ing..........
            break;
        case DECODE_RET_SUC:
            
            ptDecHandle->wIndex = 0;
            CQ_DeleteMul(ptDecHandle->ptCirQue, ptDecHandle->wDataLen);
            TIMER_Stop(&ptDecHandle->tDecodeDrmTimer);

            //call DLMS Protocol process function
            DEC_STATISTICS(ptDecHandle);
           
            Dbg_Trace_Hex(ptDecHandle->pbyData, ptDecHandle->wDataLen);
            printf("\n");
            
            break;
        case DECODE_RET_ERROR:
            //Dbg_Trace_Hex(ptDecHandle->pbyData, ptDecHandle->wIndex);
            printf("\n");
            ptDecHandle->wIndex = 0;
            CQ_DELETE(ptDecHandle->ptCirQue);
            Dec_Fun_Reset(ptDecHandle);
            //system("pause");
            break;
        default:
            return -1;
            break;
        }
    }

    if (TIMER_Elapsed(&ptDecHandle->tDecodeDrmTimer))
    {
        ptDecHandle->wIndex = 0;
        CQ_DELETE(ptDecHandle->ptCirQue);
        Dec_Fun_Reset(ptDecHandle);
        system("pause");
    }
    
    return 0;
}

