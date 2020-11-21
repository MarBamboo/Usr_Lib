/**@file  Usr_Timer.c
* @brief       软定时器
* @details  主要实现软定时功能
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


/* Includes ------------------------------------------------------------------*/
#include "stdlib.h"
#include "stdint.h"
#include "Usr_Timer.h"

/* ---- Private macro ------------------------------------------------------- */
#define TIMER_DELAY_MAX         (0xFFFFFFFF)    
unsigned int volatile g_ulTick = 0;

/*
** Starts a timer.
*/
void TIMER_Start(T_Timer *tm)
{
    tm->uStart = TIMER_GetNow();
    tm->bFlag = TIM_OPEN;
}

/*
** Set delay for the specified timer.
*/
TIM_STA TIMER_GetSta(T_Timer *tm)
{
    return tm->bFlag;
}

void TIMER_SetDelay(T_Timer *tm, unsigned int uDelay)
{
    tm->uDelay = uDelay;
    tm->bFlag = TIM_CLOSE;
}

/*
** Stop the specified timer.
*/
void TIMER_Stop(T_Timer *tm)
{
    tm->bFlag = TIM_CLOSE;
}

/* 
** Check whether or not the specified timer elapsed.
** ret --
**      True: Elapsed; TIM_CLOSE: NOT elapsed.
*/
TIM_STA TIMER_Elapsed(T_Timer *tm)
{
    if (tm->bFlag == TIM_CLOSE) 
	{	
		return TIM_CLOSE;
	}

    return (TIM_STA)((TIMER_GetNow() - tm->uStart) >= tm->uDelay); 
}

/*
** Delay a specified time.
*/
void TIMER_Delay(unsigned int uDelay)
{
    unsigned int uStart;
    
    uStart = TIMER_GetNow();
    while (((unsigned int)(TIMER_GetNow() - uStart)) < uDelay)
	{
	}
}

int TIMER_CostTimes(T_Timer *tm)
{
    if (tm->bFlag == TIM_CLOSE) 
	{	
		return -1;
	}
    return (int)((TIMER_GetNow() - (tm->uStart)));
}
