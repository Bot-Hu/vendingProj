#ifndef __BUTTON_H
#define __BUTTON_H
#include "sys.h"

//��ť�궨��
#define UNPRESS 0
#define PRESS 1
#define INVALID 2

void Button1(u16 x1,u16 y1,u16 x2,u16 y2,u8 mode,u8 *p,u16 lon,u8 size,u16 bg_color);//����
void Button(u16 x1,u16 y1,u16 x2,u16 y2,u8 mode,u8 *p,u16 lon,u8 size);//����

#endif
