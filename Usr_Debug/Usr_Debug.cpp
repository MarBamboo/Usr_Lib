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

//#include "Usr_Calendar.h"
#include "Usr_Debug.h"
//#include "Usr_Queue.h"

#include "stdarg.h"
#include<stdio.h>
#include<stdlib.h>

#include<string.h>

#define DEBUG_BUF_BASE_UNIT         (512)   
#define DEBUG_LOG_HEX_MAXSIZE       (DEBUG_BUF_BASE_UNIT + 1)

#define DEBUG_LOG_PREFIX             0//(Cdr_Clock_Disp_Len)
#define DEBUG_LOG_MAXSIZE           (DEBUG_LOG_HEX_MAXSIZE + DEBUG_LOG_PREFIX)


void Dbg_Trace(const char* format, ...)
{
    static char buf[DEBUG_LOG_MAXSIZE] = { 0 };

    //add prefix
    //Cdr_Clock_Disp(buf);

    //------------
    va_list ap;
    va_start(ap, format);
    //vsprintf_s(&buf[DEBUG_LOG_PREFIX], format, ap);
    va_end(ap);

    //------------
    printf("%s", buf);
}

void Dbg_Trace_Hex(const uint8* pbyBuf, uint16 wBufLen)
{
    static uint8 abyHexStr[DEBUG_LOG_HEX_MAXSIZE] = { 0 };
    static uint8 byTmpChar = 0;
    uint16 j, i;

    while (wBufLen)
    {
        i = (wBufLen > DEBUG_BUF_BASE_UNIT) ? (DEBUG_BUF_BASE_UNIT) : (wBufLen);
        wBufLen -= i;

        for (j = 0; j < i; j++)
        {
            byTmpChar = pbyBuf[j];

            if ((byTmpChar >> 4) <= 0x09)
            {
                abyHexStr[j << 1] = (byTmpChar >> 4) + '0';
            }
            else
            {
                abyHexStr[j << 1] = ((byTmpChar >> 4) - 0x0A) + 'A';
            }
            if ((byTmpChar & 0x0F) <= 0x09)
            {
                abyHexStr[((j << 1) + 1)] = (byTmpChar & 0x0F) + '0';
            }
            else
            {
                abyHexStr[((j << 1) + 1)] = ((byTmpChar & 0x0F) - 0x0A) + 'A';
            }
        }
        abyHexStr[(j << 1)] = 0;

        Dbg_Trace("%s", abyHexStr);
    }
}

