/**@file  Usr_Calendar.c
* @brief       日历
* @details  主要提供时间
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
#include "Usr_Calendar.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"
#include "string.h"
#include "math.h"

T_CdrPara tCdrPara;

int isleap(int year)
{
	if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))
		return 1;
	else
		return 0;
}

unsigned char max_day(int year, int month)
{
	unsigned char day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (isleap(year) == 1)
		day[1] = 29;
	return day[month - 1];
}

int total_day(int year, int month, int day)
{
	int sum = 0;
	int i = 1;
	for (i = 1; i < month; i++)
		sum += max_day(year, i);
	sum += day;
	return sum;
}

int weekday(int year, int month, int day)
{
	int count;
	count = (year - 1) + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400 + total_day(year, month, day);
	count %= 7;
	return count;
}


char cdr_Set(unsigned short wYear,
					unsigned char byMonth,
					unsigned char byDay,
					unsigned char byHour,
					unsigned char byMin,
					unsigned char bySec,
					unsigned short wMsec)
{
	memset(&tCdrPara, 0, sizeof(tCdrPara));
	if ((wYear >= 2100) || (byMonth >= 12) || (byDay >= 31) || (byHour >= 24) || (byMin >= 60) || (bySec >= 60 || (wMsec >= 1000))) {
		return -1;
	}

	tCdrPara.wYear = wYear;
	tCdrPara.byMonth = byMonth;
	tCdrPara.byDay = byDay;
	tCdrPara.byHour = byHour;
	tCdrPara.byMin = byMin;
	tCdrPara.bySec = bySec;
	tCdrPara.wMsec = wMsec;

	return 0;
}

void cdr_Timing(unsigned short wMsec)
{
	static unsigned char byCout = 0;
	static unsigned char tmpDayNum = 0;

	tCdrPara.wMsec += wMsec;

	byCout = tCdrPara.wMsec / 1000;
	if (byCout > 0){	// millisecond
		tCdrPara.wMsec %= 1000;
		tCdrPara.bySec += byCout;
		byCout = tCdrPara.bySec / 60;

		if (byCout > 0) {	// Second
			tCdrPara.bySec %= 60;
			tCdrPara.byMin += byCout;
			byCout = tCdrPara.byMin / 60;

			if (byCout > 0) {	// minute
				tCdrPara.byMin %= 60;
				tCdrPara.byHour += byCout;
				byCout = tCdrPara.byHour / 24;

				if (byCout > 0) {	// hour
					tmpDayNum = max_day(tCdrPara.wYear, tCdrPara.byMonth);

					tCdrPara.byHour %= 24;
					tCdrPara.byDay += byCout;
					byCout = tCdrPara.byDay / tmpDayNum;

					if (byCout > 0) {	// day
						tCdrPara.byDay %= tmpDayNum;
						tCdrPara.byMonth += byCout;
						byCout = tCdrPara.byMonth / 12;

						if (byCout > 0) {	// month
							if ((tCdrPara.byMonth % 12) > 0)
							{
								tCdrPara.byMonth %= 12;
								tCdrPara.wYear += byCout;
							}
						}
					}
				}
			}
		}
	}
}
