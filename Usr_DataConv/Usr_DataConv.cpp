/**@file  Usr_DataConv.cpp
* @brief       数据转换
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
#include <stdint.h>
#include <string.h>
#include "Usr_DataConv.h"

/**@brief HEX data convert to Ascii format
* @param[in]  void* pHexStr				Hex data point
* @param[in]  unsigned int uHexLen		Hex data length
* @param[in]  void* pAscStr				Ascii data point
* @param[in]  unsigned int				Ascii data length
* @return  number of success
*/
unsigned int HexToAscii(void* pHex, unsigned int uHexLen, void* pAsc, unsigned int uAscSpaceSize)
{
	const char arrList[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

	char Nibble[2];

	if (2 * uHexLen + 1 > uAscSpaceSize)
	{
		return 0;
	}

	for (int i = 0; i < uHexLen; ++i)
	{
		Nibble[0] = *((unsigned char*)pHex + i) >> 4 & 0x0F;
		Nibble[1] = *((unsigned char*)pHex + i) & 0x0F;

		if ((Nibble[0] < 0x0F) && (Nibble[1] < 0x0F))
		{
			*((unsigned char*)pAsc + i * 2) = arrList[Nibble[0]];
			*((unsigned char*)pAsc + i * 2 + 1) = arrList[Nibble[1]];
		}
		else
		{
			return 0;
		}
	}

	*((unsigned char*)pAsc + 2 * uHexLen) = 0x00;
	return 2 * uHexLen + 1;
}


/**@brief Ascii data convert to Hex format
* @param[in]  void* pAscii					Asc data point
* @param[in]  void* pHex					Hex data point
* @param[in]  unsigned int uHexSpaceSize	Hex data length
* @return  number of success
*/
unsigned int AsciiToHex(void* pAscii, void* pHex, unsigned int uHexSpaceSize)
{
	unsigned char* pTmpAscii = (unsigned char*)pAscii;
	unsigned int uAscLen = strlen((const char*)pTmpAscii);
	unsigned int nLen = uAscLen / 2;
	unsigned char Nibble[2] = { 0 };
	int i,j;
	if ((uAscLen % 2) || (nLen > uHexSpaceSize))
	{
		return 1;
	}

	for (i = 0; i < nLen; i++)
	{
		Nibble[0] = *(pTmpAscii++);
		Nibble[1] = *(pTmpAscii++);

		for (j = 0; j < 2; j++)
		{
			if (Nibble[j] <= 'F' && Nibble[j] >= 'A')
				Nibble[j] = Nibble[j] - 'A' + 10;
			else if (Nibble[j] <= 'f' && Nibble[j] >= 'a')
				Nibble[j] = Nibble[j] - 'a' + 10;
			else if (Nibble[j] >= '0' && Nibble[j] <= '9')
				Nibble[j] = Nibble[j] - '0';
			else
				return 0;
		}	
		*((unsigned char*)pHex + i) = Nibble[0] << 4;	// Set the high nibble
		*((unsigned char*)pHex + i) |= Nibble[1];	//Set the low nibble
	}
	return nLen;
}