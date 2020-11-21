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
#ifndef  _USR_DEBUG_H_
#define _USR_DEBUG_H_
#include "TypeDef.h"
#define DEBUG

#ifdef DEBUG  
#define LOG(format, ...) fprintf(stdout, ">>>>>" format "<<<<", ##__VA_ARGS__)  
#else  
#define LOG(format, ...)  
#endif  









void Dbg_Trace(const char* format, ...);
void Dbg_Trace_Hex(const uint8* pbyBuf, uint16 wBufLen);

#endif /*_USR_DEBUG_H_*/