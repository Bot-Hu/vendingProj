#include "button.h"
#include "text.h"
#include "lcd.h"

//按钮模型
//x1y1左上角,x2y2右下角，确定方框范围
//lon文本长度
//size文本大小
//p文本
//mode为按钮状态
void Button(u16 x1,u16 y1,u16 x2,u16 y2,u8 mode,u8 *p,u16 lon,u8 size)
{
	
	u16 dx=(x2-x1-lon+2)/2;
	u16 dy=(y2-y1-size+2)/2;
	switch(mode)
	{
		case 0:
		{
			LCD_Fill(x1,y1,x2,y2,color(0xd4,0xd0,0xc8));
			LCD_DrawLine_Color((x1+1),(y1+1),(x2-1),(y1+1),color(255,255,255));
			LCD_DrawLine_Color((x1+1),(y1+1),(x1+1),(y2-1),color(255,255,255));
			LCD_DrawLine_Color(x1,y2,x2,y2,color(0x40,0x40,0x40));
			LCD_DrawLine_Color(x2,y1,x2,y2,color(0x40,0x40,0x40));
			LCD_DrawLine_Color((x1+1),(y2-1),(x2-1),(y2-1),color(0x80,0x80,0x80));
			LCD_DrawLine_Color((x2-1),(y1+1),(x2-1),(y2-1),color(0x80,0x80,0x80));
			if(p!=NULL)Show_HZ16_Color((x1+dx),(y1+dy),p,1,color(0,0,0));
		}break;
		case 1:
		{
			LCD_Fill((x1+1),(y1+1),(x2-1),(y2-1),color(0xd4,0xd0,0xc8));
			LCD_DrawLine_Color((x1+1),(y1+1),(x2-1),(y1+1),color(0x80,0x80,0x80));
			LCD_DrawLine_Color((x1+1),(y1+1),(x1+1),(y2-1),color(0x80,0x80,0x80));
			LCD_DrawLine_Color(x1,y1,x2,y1,color(0x40,0x40,0x40));
			LCD_DrawLine_Color(x1,y1,x1,y2,color(0x40,0x40,0x40));
			LCD_DrawLine_Color(x2,y1,x2,y2,color(255,255,255));
			LCD_DrawLine_Color(x1,y2,x2,y2,color(255,255,255));
			if(p!=NULL)Show_HZ16_Color((x1+dx+1),(y1+dy+1),p,1,color(0,0,0));
		}break;
		case 2:
		{
			LCD_Fill(x1,y1,x2,y2,color(0xd4,0xd0,0xc8));
			LCD_DrawLine_Color(x1,y1,x2,y1,color(255,255,255));
			LCD_DrawLine_Color(x1,y1,x1,(y2-1),color(255,255,255));
			LCD_DrawLine_Color(x1,y2,x2,y2,color(0x40,0x40,0x40));
			LCD_DrawLine_Color(x2,y1,x2,y2,color(0x40,0x40,0x40));
			LCD_DrawLine_Color((x1+1),(y2-1),(x2-1),(y2-1),color(0x80,0x80,0x80));
			LCD_DrawLine_Color((x2-1),(y1+1),(x2-1),(y2-1),color(0x80,0x80,0x80));
			if(p!=NULL)
			{
				Show_HZ16_Color((x1+dx+1),(y1+dy+1),p,1,color(255,255,255));
				Show_HZ16_Color((x1+dx),(y1+dy),p,1,color(0x80,0x80,0x80));
			}
		}break;
	}
}
//按钮模型
//x1y1左上角,x2y2右下角，确定方框范围
//lon文本长度
//size文本大小
//p文本
//mode为按钮状态
void Button1(u16 x1,u16 y1,u16 x2,u16 y2,u8 mode,u8 *p,u16 lon,u8 size, u16 bg_color)
{
	u16 dx=(x2-x1-lon+2)/2;
	u16 dy=(y2-y1-size+2)/2;
	switch(mode)
	{
		case 0:
		{
			LCD_Fill(x1,y1,x2,y2,bg_color);
			LCD_DrawLine_Color((x1+1),(y1+1),(x2-1),(y1+1),color(255,255,255));
			LCD_DrawLine_Color((x1+1),(y1+1),(x1+1),(y2-1),color(255,255,255));
			LCD_DrawLine_Color(x1,y2,x2,y2,color(0x40,0x40,0x40));
			LCD_DrawLine_Color(x2,y1,x2,y2,color(0x40,0x40,0x40));
			LCD_DrawLine_Color((x1+1),(y2-1),(x2-1),(y2-1),color(0x80,0x80,0x80));
			LCD_DrawLine_Color((x2-1),(y1+1),(x2-1),(y2-1),color(0x80,0x80,0x80));
			if(p!=NULL)	Show_HZ16_Color((x1+dx),(y1+dy),p,1,color(0,0,0));
		}break;
		case 1:
		{
			LCD_Fill((x1+1),(y1+1),(x2-1),(y2-1),bg_color);
			LCD_DrawLine_Color((x1+1),(y1+1),(x2-1),(y1+1),color(0x80,0x80,0x80));
			LCD_DrawLine_Color((x1+1),(y1+1),(x1+1),(y2-1),color(0x80,0x80,0x80));
			LCD_DrawLine_Color(x1,y1,x2,y1,color(0x40,0x40,0x40));
			LCD_DrawLine_Color(x1,y1,x1,y2,color(0x40,0x40,0x40));
			LCD_DrawLine_Color(x2,y1,x2,y2,color(255,255,255));
			LCD_DrawLine_Color(x1,y2,x2,y2,color(255,255,255));
			if(p!=NULL)	Show_HZ16_Color((x1+dx+1),(y1+dy+1),p,1,color(0,0,0));
		}break;
		case 2:
		{
			LCD_Fill(x1,y1,x2,y2,bg_color);
			LCD_DrawLine_Color(x1,y1,x2,y1,color(255,255,255));
			LCD_DrawLine_Color(x1,y1,x1,(y2-1),color(255,255,255));
			LCD_DrawLine_Color(x1,y2,x2,y2,color(0x40,0x40,0x40));
			LCD_DrawLine_Color(x2,y1,x2,y2,color(0x40,0x40,0x40));
			LCD_DrawLine_Color((x1+1),(y2-1),(x2-1),(y2-1),color(0x80,0x80,0x80));
			LCD_DrawLine_Color((x2-1),(y1+1),(x2-1),(y2-1),color(0x80,0x80,0x80));
			if(p!=NULL)
			{
				Show_HZ16_Color((x1+dx+1),(y1+dy+1),p,1,color(255,255,255));
				Show_HZ16_Color((x1+dx),(y1+dy),p,1,color(0x80,0x80,0x80));
			}
		}break;
	}
}
