#include "hex_to_char.h"
#include "sys.h"
#include "stdio.h"
#include "string.h"

//第一个参数表示输出转换Ascll格式字符串 空间大小为src的2分之一
//第二个参数表示输入字符串(16进制)
//第三个参数表示需要转换字符串长度
int HexToChar(unsigned char* dst,const void* src,int len)
{
    int i;
    const char* psrc = (const char*)src;
    int nNum = 0;
    int nRun = len / 2;
    int nRem = len % 2;//如果最后余最后一个16位数字转换成Ascll
	
	if (0 == src || 0>= len)
    {
        return -1;
    }
	
    for (i = 0;i < nRun;i++)
    {
        int nval = CharToInt(*(psrc + i * 2)) * 16 + CharToInt(*(psrc + i * 2 + 1));
        *(dst + i) = nval; 
        nNum++;
    }
    if (0 == nRem)
    {
        return nNum;
    }
    *(dst + nNum) = CharToInt(*(psrc + len - 1));
    nNum++;
    return nNum;
}

int CharToInt(char src)
{
    if ('0' <= src && '9' >= src)
    {
        return src - '0';
    }
    else if ('A' <= src && 'F' >= src)
    {
        return src - 'A' + 10;
    }
    else if ('a' <= src && 'f' >= src)
    {
        return src - 'a' + 10;
    }
    return 0;
}
