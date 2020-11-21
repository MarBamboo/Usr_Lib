/**@file  TypeDef.h
* @brief       ͨ�ö���
* @details  ��Ҫ���������������ض�����ֽڲ���
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

