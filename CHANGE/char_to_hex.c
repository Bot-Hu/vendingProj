#include "char_to_hex.h"
#include "sys.h"
#include "stdio.h"
#include "string.h"

int charToHex(char* dst,const unsigned char* src,int len)
{
//第一个参数表示输出转换字符串 空间大小大大于 src的2倍
//第2个参数表示输入字符串(ASCLL码)
//第3个参数表示需要转换字符串长度
	int i;
	const unsigned char*psrc = src;
	int nNum = 0;
	
	
    if (0 == src)
    {
        return -1;
    }
    
    
    for (i = 0;i < len;i++)
    {
        int nval =  *(psrc + i);
        if (15 >= nval && 0 <= nval)
        {
            if (9 >= nval && 0 <= nval)
            {
                *(dst + i * 2) = '0';
                *(dst + i * 2 + 1) = '0' + nval;
                nNum += 2;
                continue;
            }
            switch (nval)//下面的算法中，把一个ascll字符转换为2个16进制数字，如果ascll小于F那么高位补0
            {
            case 10:
                *(dst + i * 2) = '0';
                *(dst + i * 2 + 1) = 'A';
                break;
            case 11:
                *(dst + i * 2) = '0';
                *(dst + i * 2 + 1) = 'B';
                break;
            case 12:
                *(dst + i * 2) = '0';
                *(dst + i * 2 + 1) = 'C';
                break;
            case 13:
                *(dst + i * 2) = '0';
                *(dst + i * 2 + 1) = 'D';
                break;
            case 14:
                *(dst + i * 2) = '0';
                *(dst + i * 2 + 1) = 'E';
                break;
            case 15:
                *(dst + i * 2) = '0';
                *(dst + i * 2 + 1) = 'F';
                break;
            }
            nNum += 2;
        }
        else if (255 >= nval &&15 < nval)
        {
            int nRun = nval / 16;
            int nRem = nval%16;

            switch (nRun)
            {

            case 10:
                *(dst + i * 2) = 'A';
                break;
            case 11:
                *(dst + i * 2) = 'B';
                break;
            case 12:
                *(dst + i * 2) = 'C';
                break;
            case 13:
                *(dst + i * 2) = 'D';
                break;
            case 14:
                *(dst + i * 2) = 'E';
                break;
            case 15:
                *(dst + i * 2) = 'F';
                break;
            }
            if (9 >= nRun)
            {
                *(dst + i * 2) = '0' + nRun;
                nNum ++;
            }
            else
            {
                nNum ++;
            }
            if (9 >= nRem)
            {
                *(dst + i * 2 + 1) = '0' + nRem;
                nNum ++;
                continue;
            }
            switch (nRem)//个位
            {
            case 10:
                *(dst + i * 2 + 1) = 'A';
                break;
            case 11:
                *(dst + i * 2 + 1) = 'B';
                break;
            case 12:
                *(dst + i * 2 + 1) = 'C';
                break;
            case 13:
                *(dst + i * 2 + 1) = 'D';
                break;
            case 14:
                *(dst + i * 2 + 1) = 'E';
                break;
            case 15:
                *(dst + i * 2 + 1) = 'F';
                break;
            }
            nNum ++;
        }
        else
        {
            *(dst + i * 2) = '0';
            *(dst + i * 2 + 1) = '0';
            nNum += 2;
        }
    }
    return nNum;
}
