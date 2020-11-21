#ifndef _USR_DATA_CONV_H_
#define _USR_DATA_CONV_H_




unsigned int HexToAscii(void* pHexStr, unsigned int uHexLen, void* pAscStr, unsigned int uAscSpaceSize);
unsigned int AsciiToHex(void* pAscii, void* pHex, unsigned int uHexSpaceSize);

#endif // !_USR_DATA_CONV_H_
