#ifndef __MENU_H
#define __MENU_H
#include "sys.h"

extern u8 en_refresh;			//允许刷新
extern int Quantity_1;				//商品1数量   饮料
extern int Quantity_2;				//商品2数量   纸巾
extern int Total_1;				//购买数量1   购买的饮料数量
extern int Total_2;				//购买数量2   购买的纸巾数量

//line == y ；row == x
#define	line1	10
#define	row1	20

#define	line2	50
#define	row2	44

#define	line3	90
#define	row3	20

#define	line4	115
#define	row4	76

#define	line5	140
#define	row5	76

#define	line6	185
#define	row6	20

#define	line7	210
#define	row7	43

#define	line8	235
#define	row8	43

#define	line9	280
#define	row9	43


void Layout(void);
void Refresh(void);
void Menu(void);

void Confirm(void);
void Cancel(void);

#endif
