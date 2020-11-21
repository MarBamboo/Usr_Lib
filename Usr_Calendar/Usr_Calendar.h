/**@file  Usr_Calendar.h
* @brief       Usr_Calendar.c 头文件
* @details
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
#ifndef _USR_CALENDAR_H_
#define _USR_CALENDAR_H_

#define Cdr_Clock_Disp_Len	(13)
#define Cdr_Clock_Disp(buf)	sprintf(buf, "%02d:%02d:%02d:%03d>",tCdrPara.byHour,tCdrPara.byMin,tCdrPara.bySec,tCdrPara.wMsec)

#define Cdr_Disp_Len	(25)
#define Cdr_Disp(buf)		sprintf(buf, "\n%02d:%02d:%02d:%02d:%02d:%02d:%03d>", tCdrPara.wYear,tCdrPara.byMonth,tCdrPara.byDay,tCdrPara.byHour,tCdrPara.byMin,tCdrPara.bySec,tCdrPara.wMsec)


typedef struct
{
	unsigned short wYear;	
	unsigned char byMonth;
	unsigned char byDay;
	unsigned char byHour;
	unsigned char byMin;
	unsigned char bySec;
	unsigned short wMsec;
}T_CdrPara;

extern T_CdrPara tCdrPara;

unsigned char max_day(int year, int month);
int total_day(int year, int month, int day);
int weekday(int year, int month, int day);


char cdr_Set(unsigned short wYear,unsigned char byMonth,unsigned char byDay,unsigned char byHour,unsigned char byMin,unsigned char bySec,unsigned short wMsec);
void cdr_Timing(unsigned short ms);




#endif	/*_CALENDAR_H*/