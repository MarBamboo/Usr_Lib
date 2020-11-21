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

  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _USR_TIMER_H_
#define _USR_TIMER_H_
/* ---- Includes ------------------------------------------------------------ */
#include <TypeDef.h>
#include <stdlib.h>
/* ---- Exported macro ------------------------------------------------------ */
extern unsigned int volatile g_ulTick;

#define TIM_OPEN      (1)
#define TIM_CLOSE     (0)
typedef	unsigned char		TIM_STA;		

/* TIMER struct */
typedef struct
{
    unsigned int    uStart;
    unsigned int    uDelay;
    unsigned char     bFlag;
} T_Timer;
/* ---- Exported variables -------------------------------------------------- */


/* ---- Exported function prototypes ---------------------------------------- */
#define TIMER_GetNow()  (g_ulTick)

void TIMER_Start(T_Timer *tm);
TIM_STA TIMER_GetSta(T_Timer *tm);

void TIMER_SetDelay(T_Timer *tm, unsigned int uDelay);
void TIMER_Stop(T_Timer *tm);
TIM_STA TIMER_Elapsed(T_Timer *tm);
void TIMER_Delay(unsigned int uDelay);

int TIMER_CostTimes(T_Timer *tm);

#endif /* _USR_TIMER_H_ */

