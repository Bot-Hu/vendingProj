#include "menu.h"
#include "button.h"
#include "touch.h"
#include "lcd.h"
#include "text.h"
#include "QRcode_main.h"
#include "rtc.h"

//界面布局
void Layout(void)
{
	Show_HZ16(row1,line1,(u8*)"【",1);LCD_ShowString(row1+20,line1,80,16,16,(u8*)"    -  -  ");LCD_ShowString(row1+116,line1,64,16,16,(u8*)"  :  :  ");Show_HZ16(row1+184,line1,(u8*)"】",1);
	Show_HZ16(row2,line2,(u8*)"欢迎使用",1);LCD_ShowString(row2+64,line2,40,16,16,(u8*)" 714 ");Show_HZ16(row2+104,line2,(u8*)"售货机",1);
	Show_HZ16(row3,line3,(u8*)"现有货物：",1);
	Show_HZ16(row4,line4,(u8*)"饮料×",1);LCD_ShowxNum(row4+48,line4,Quantity_1,2,16,0x80);Show_HZ16(row4+72,line4,(u8*)"瓶",1);
	Show_HZ16(row5,line5,(u8*)"纸巾×",1);LCD_ShowxNum(row5+48,line5,Quantity_2,2,16,0x80);Show_HZ16(row5+72,line5,(u8*)"包",1);
	Show_HZ16(row6,line6,(u8*)"您想购买些什么呢？",1);
	Show_HZ16(row7,line7,(u8*)"饮料×",1);LCD_ShowxNum(row7+48,line7,Total_1,2,16,0x80);Button1(row7+72+20,line7,row7+72+20+16+2+2,line7+16+2+2,UNPRESS,(u8*)"▲",16,16,color(181,233,157));Button1(row7+80+20+17,line7,row7+80+20+17+16+2+2,line7+16+2+2,UNPRESS,(u8*)"▼",16,16,color(181,233,157));
	Show_HZ16(row8,line8,(u8*)"纸巾×",1);LCD_ShowxNum(row8+48,line8,Total_2,2,16,0x80);Button1(row8+72+20,line8,row8+72+20+16+2+2,line8+16+2+2,UNPRESS,(u8*)"▲",16,16,color(181,233,157));Button1(row8+80+20+17,line8,row8+80+20+17+16+2+2,line8+16+2+2,UNPRESS,(u8*)"▼",16,16,color(181,233,157));
	Button1(row9,line9,row9+16*2+8+8,line9+16+2+2,UNPRESS,(u8*)"确定",32,16,color(73,130,234));Button1(row9+100,line9,row9+100+16*2+8+8,line9+16+2+2,UNPRESS,(u8*)"取消",32,16,color(181,233,157));
}

//刷新
void Refresh(void)
{
	//刷新时间
	LCD_ShowxNum(row1+20,line1,calendar.w_year,4,16,0x80);
	LCD_ShowxNum(row1+60,line1,calendar.w_month,2,16,0x80);
	LCD_ShowxNum(row1+84,line1,calendar.w_date,2,16,0x80);
	
	LCD_ShowxNum(row1+116,line1,calendar.hour,2,16,0x80);
	LCD_ShowxNum(row1+140,line1,calendar.min,2,16,0x80);
	LCD_ShowxNum(row1+164,line1,calendar.sec,2,16,0x80);
	
	if(en_refresh)
	{
		//刷新商品数量
		LCD_ShowNum(row4+48,line4,Quantity_1,2,16);
		LCD_ShowNum(row5+48,line5,Quantity_2,2,16);
		
		LCD_ShowNum(row7+48,line7,Total_1,2,16);
		LCD_ShowNum(row8+48,line8,Total_2,2,16);
	}
}

//菜单
void Menu(void)
{
	static u8 key=0;	//无按键按下
	static u8 last_key=0;
	
	/****************  触摸按键扫描  ******************/
	tp_dev.scan(0);
	if(tp_dev.sta&TP_PRES_DOWN)	// 按键按下
	{
		last_key = 1;
		
		if(Is_In_Area(row9,line9,row9+16*2+8+8,line9+16+2+2))						key=1;	//确定按钮
		else if(Is_In_Area(row9+100,line9,row9+100+16*2+8+8,line9+16+2+2))			key=2;	//取消按钮
		else if(Is_In_Area(row7+72+20,line7,row7+72+20+16+2+2,line7+16+2+2))		key=3;	//饮料+1
		else if(Is_In_Area(row7+80+20+17,line7,row7+80+20+17+16+2+2,line7+16+2+2))	key=4;	//饮料-1
		else if(Is_In_Area(row8+72+20,line8,row8+72+20+16+2+2,line8+16+2+2))		key=5;	//纸巾+1
		else if(Is_In_Area(row8+80+20+17,line8,row8+80+20+17+16+2+2,line8+16+2+2))	key=6;	//纸巾-1
		else 																		key=0;	//无商品被选择
		
		switch(key)	//显示被按下按键图标
		{
			case 1:	Button(row9,line9,row9+16*2+8+8,line9+16+2+2,PRESS,(u8*)"确定",32,16);break;//确定
			case 2:	Button(row9+100,line9,row9+100+16*2+8+8,line9+16+2+2,PRESS,(u8*)"取消",32,16);break;//取消
			case 3: Button(row7+72+20,line7,row7+72+20+16+2+2,line7+16+2+2,PRESS,(u8*)"▲",16,16);break;//饮料+1
			case 4: Button(row7+80+20+17,line7,row7+80+20+17+16+2+2,line7+16+2+2,PRESS,(u8*)"▼",16,16);break;//饮料-1
			case 5: Button(row8+72+20,line8,row8+72+20+16+2+2,line8+16+2+2,PRESS,(u8*)"▲",16,16);break;//纸巾+1
			case 6: Button(row8+80+20+17,line8,row8+80+20+17+16+2+2,line8+16+2+2,PRESS,(u8*)"▼",16,16);break;//纸巾-1
			default:break;
		}
	}
	else if(last_key)
	{
		last_key = 0;
	
		switch(key)	//执行相应按键功能
		{
			case 1:	Confirm();break;//确定
			case 2:	Cancel();break;//取消
			case 3: Total_1=(Total_1>=Quantity_1)?Quantity_1:Total_1+1;break;//饮料+1
			case 4: Total_1=(Total_1<=0)?0:Total_1-1;break;//饮料-1
			case 5: Total_2=(Total_2>=Quantity_2)?Quantity_2:Total_2+1;break;//纸巾+1
			case 6: Total_2=(Total_2<=0)?0:Total_2-1;	break;//纸巾-1
			default:break;
		}
		
		//恢复原图标
		Button1(row9,line9,row9+16*2+8+8,line9+16+2+2,UNPRESS,(u8*)"确定",32,16,color(73,130,234));
		Button1(row9+100,line9,row9+100+16*2+8+8,line9+16+2+2,UNPRESS,(u8*)"取消",32,16,color(181,233,157));
		Button1(row7+72+20,line7,row7+72+20+16+2+2,line7+16+2+2,UNPRESS,(u8*)"▲",16,16,color(181,233,157));
		Button1(row7+80+20+17,line7,row7+80+20+17+16+2+2,line7+16+2+2,UNPRESS,(u8*)"▼",16,16,color(181,233,157));
		Button1(row8+72+20,line8,row8+72+20+16+2+2,line8+16+2+2,UNPRESS,(u8*)"▲",16,16,color(181,233,157));
		Button1(row8+80+20+17,line8,row8+80+20+17+16+2+2,line8+16+2+2,UNPRESS,(u8*)"▼",16,16,color(181,233,157));
	}
}

//确定处理
void Confirm(void)
{
	extern u8 EN_BUY;
	en_refresh=0;	//禁止刷新
	LCD_Fill(0,30,239,202,WHITE);
	QRGenerator(40,40,6,"https://www.baidu.com/");
	EN_BUY = 1;
}

//取消处理
void Cancel(void)
{
	extern u8 EN_BUY;
	EN_BUY = 0;
	LCD_Fill(0,30,239,202,WHITE);
	en_refresh=1;	//允许刷新
	
	Total_1=0;
	Total_2=0;
	Layout();
}

