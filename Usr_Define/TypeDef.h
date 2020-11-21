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

#ifndef	_TYPE_DEF_H_
#define	_TYPE_DEF_H_

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include "string.h"


#ifndef	NULL
#define	NULL			(0)
#endif

#ifndef	TRUE
#define	TRUE			(1)
#endif

#ifndef	FALSE
#define	FALSE			(0)
#endif

#ifndef	ON
#define	ON				(1)
#endif

#ifndef	OFF
#define	OFF				(0)
#endif

#ifndef	LOW
#define	LOW				(0)
#endif

#ifndef	HIGH
#define	HIGH			(1)
#endif

/*
bool flag;		char cval
short sval;		unsigned short usval
int ival;		unsigned int uiVal;
long lval;		unsigned long ulVal;
float fVal;		double dVal;
*/


/**@name 自定义数据类型*/
typedef	unsigned char		uint8;		/*uint8 byExample*/
typedef	unsigned short		uint16;		/*uint16 wExample*/
typedef	unsigned int		uint32;		/*uint32 uExample*/
typedef unsigned long long 	uint64;		/*INT64U ulExample*/
	
typedef	signed char			int8;		/*int8 cExample*/
typedef	signed short		int16;		/*int16 sExample*/
typedef	signed int			int32;		/*int32 iExample*/
typedef signed long long 	int64;		/*int64 lExample*/

typedef	unsigned char		BOOLE;		/*BOOLE bExample*/

#if (1)
typedef union
{
	uint8	u8;
	
	struct
	{
	uint8	C:1;			//运算后的进位标志
	uint8 	:7;
	};
	
	struct
	{
	uint8	b0:1;
	uint8 	b1:1;
	uint8 	b2:1;
	uint8 	b3:1;
	uint8 	b4:1;
	uint8 	b5:1;
	uint8 	b6:1;
	uint8 	b7:1;
	};
}UN_INT8;

typedef union
{
	uint16	u16;
	uint8	u8[2];

	struct
	{
		uint8 u8_0;
		uint8 u8_1;
	};

	struct
	{
		uint8	low;
		uint8	high;
	} byte;
	
	struct
	{
		uint8	u16_lower:4;
		uint8	u16_low:4;
		uint8	u16_high:4;
		uint8	u16_higher:4;
	}bits;
	
	struct
	{
	uint8 b0:1;
	uint8 b1:1;
	uint8 b2:1;
	uint8 b3:1;
	uint8 b4:1;
	uint8 b5:1;
	uint8 b6:1;
	uint8 b7:1;
	uint8 b8:1;
	uint8 b9:1;
	uint8 b10:1;
	uint8 b11:1;
	uint8 b12:1;
	uint8 b13:1;
	uint8 b14:1;
	uint8 b15:1;
	};
}UN_INT16;

typedef union
{
	uint32	u32;

	uint8	u8[4];
	struct
	{
		uint8 u8_0;
		uint8 u8_1;
		uint8 u8_2;
		uint8 u8_3;
	};

	uint16	u16[2];
	struct
	{
		uint16 u16_0;
		uint16 u16_1;
	};
	
	struct
	{
		uint8	low;
		uint8	high;
		uint8	higher;
		uint8	highest;
	}byte;
		
	struct
	{
	uint8 b0:1;
	uint8 b1:1;
	uint8 b2:1;
	uint8 b3:1;
	uint8 b4:1;
	uint8 b5:1;
	uint8 b6:1;
	uint8 b7:1;
	uint8 b8:1;
	uint8 b9:1;
	uint8 b10:1;
	uint8 b11:1;
	uint8 b12:1;
	uint8 b13:1;
	uint8 b14:1;
	uint8 b15:1;
	uint8 b16:1;
	uint8 b17:1;
	uint8 b18:1;
	uint8 b19:1;
	uint8 b20:1;
	uint8 b21:1;
	uint8 b22:1;
	uint8 b23:1;
	uint8 b24:1;
	uint8 b25:1;
	uint8 b26:1;
	uint8 b27:1;
	uint8 b28:1;
	uint8 b29:1;
	uint8 b30:1;
	uint8 b31:1;
	};
}UN_INT32;

typedef union
{
	uint64	u64;
	uint8	u8[8];
	struct
	{
	uint16 	u16_0;
	uint16 	u16_1;
	uint16 	u16_2;
	uint16 	u16_3;
	};
}UN_INT64;
#endif

////////////////////////////////////////////////////////////
/**@name bit位定义*/
////////////////////////////////////////////////////////////
#define BIT0 0x00000001
#define BIT1 0x00000002
#define BIT2 0x00000004
#define BIT3 0x00000008
#define BIT4 0x00000010
#define BIT5 0x00000020
#define BIT6 0x00000040
#define BIT7 0x00000080
#define BIT8 0x00000100
#define BIT9 0x00000200
#define BIT10 0x00000400
#define BIT11 0x00000800
#define BIT12 0x00001000
#define BIT13 0x00002000
#define BIT14 0x00004000
#define BIT15 0x00008000
#define BIT16 0x00010000
#define BIT17 0x00020000
#define BIT18 0x00040000
#define BIT19 0x00080000
#define BIT20 0x00100000
#define BIT21 0x00200000
#define BIT22 0x00400000
#define BIT23 0x00800000
#define BIT24 0x01000000
#define BIT25 0x02000000
#define BIT26 0x04000000
#define BIT27 0x08000000
#define BIT28 0x10000000
#define BIT29 0x20000000
#define BIT30 0x40000000
#define BIT31 0x80000000


////////////////////////////////////////////////////////////
//将两个uint8的变量，组合成uint16的变量
/////////////////////////////////////////////////////////////
#define	JointWord(low, high)	(((uint16)(low)) | ((uint16)(high)<<8))

#define MAKE_WORD(a, b)      (((uint16)((uint8)((a) & 0xff))) << 8) | (uint16)(((uint8)((b) & 0xff)))
#define MAKE_DWORD(a, b)      (((uint32)((uint16)(a) & 0xffffU)) << 16 | (uint32 )((uint16)(b) & 0xffffU))


/////////////////////////////////////////////////////////
//二维数组指针表示
#define TWO_ARRAY(a,colSize,row,col)	(*(a + row * colsize + col))




#endif	/*_TYPE_DEF_H_*/
