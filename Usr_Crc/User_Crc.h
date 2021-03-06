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
#ifndef  _USR_CRC_H_
#define _USR_CRC_H_
#include "TypeDef.h"

uint16 CRC_Frm(uint8* pBuf, uint16 nBufLen);

#endif // ! _USR_CRC_H_

