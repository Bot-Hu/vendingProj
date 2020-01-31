#ifndef __HEX_TO_CHAR_H
#define __HEX_TO_CHAR_H
#include "sys.h"

int CharToInt(char src);
int HexToChar(unsigned char* dst,const void* src,int len);

#endif
