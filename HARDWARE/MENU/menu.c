#include "menu.h"
#include "button.h"
#include "touch.h"
#include "lcd.h"
#include "text.h"
#include "QRcode_main.h"
#include "rtc.h"

//���沼��
void Layout(void)
{
	Show_HZ16(row1,line1,(u8*)"��",1);LCD_ShowString(row1+20,line1,80,16,16,(u8*)"    -  -  ");LCD_ShowString(row1+116,line1,64,16,16,(u8*)"  :  :  ");Show_HZ16(row1+184,line1,(u8*)"��",1);
	Show_HZ16(row2,line2,(u8*)"��ӭʹ��",1);LCD_ShowString(row2+64,line2,40,16,16,(u8*)" 714 ");Show_HZ16(row2+104,line2,(u8*)"�ۻ���",1);
	Show_HZ16(row3,line3,(u8*)"���л��",1);
	Show_HZ16(row4,line4,(u8*)"���ϡ�",1);LCD_ShowxNum(row4+48,line4,Quantity_1,2,16,0x80);Show_HZ16(row4+72,line4,(u8*)"ƿ",1);
	Show_HZ16(row5,line5,(u8*)"ֽ���",1);LCD_ShowxNum(row5+48,line5,Quantity_2,2,16,0x80);Show_HZ16(row5+72,line5,(u8*)"��",1);
	Show_HZ16(row6,line6,(u8*)"���빺��Щʲô�أ�",1);
	Show_HZ16(row7,line7,(u8*)"���ϡ�",1);LCD_ShowxNum(row7+48,line7,Total_1,2,16,0x80);Button1(row7+72+20,line7,row7+72+20+16+2+2,line7+16+2+2,UNPRESS,(u8*)"��",16,16,color(181,233,157));Button1(row7+80+20+17,line7,row7+80+20+17+16+2+2,line7+16+2+2,UNPRESS,(u8*)"��",16,16,color(181,233,157));
	Show_HZ16(row8,line8,(u8*)"ֽ���",1);LCD_ShowxNum(row8+48,line8,Total_2,2,16,0x80);Button1(row8+72+20,line8,row8+72+20+16+2+2,line8+16+2+2,UNPRESS,(u8*)"��",16,16,color(181,233,157));Button1(row8+80+20+17,line8,row8+80+20+17+16+2+2,line8+16+2+2,UNPRESS,(u8*)"��",16,16,color(181,233,157));
	Button1(row9,line9,row9+16*2+8+8,line9+16+2+2,UNPRESS,(u8*)"ȷ��",32,16,color(73,130,234));Button1(row9+100,line9,row9+100+16*2+8+8,line9+16+2+2,UNPRESS,(u8*)"ȡ��",32,16,color(181,233,157));
}

//ˢ��
void Refresh(void)
{
	//ˢ��ʱ��
	LCD_ShowxNum(row1+20,line1,calendar.w_year,4,16,0x80);
	LCD_ShowxNum(row1+60,line1,calendar.w_month,2,16,0x80);
	LCD_ShowxNum(row1+84,line1,calendar.w_date,2,16,0x80);
	
	LCD_ShowxNum(row1+116,line1,calendar.hour,2,16,0x80);
	LCD_ShowxNum(row1+140,line1,calendar.min,2,16,0x80);
	LCD_ShowxNum(row1+164,line1,calendar.sec,2,16,0x80);
	
	if(en_refresh)
	{
		//ˢ����Ʒ����
		LCD_ShowNum(row4+48,line4,Quantity_1,2,16);
		LCD_ShowNum(row5+48,line5,Quantity_2,2,16);
		
		LCD_ShowNum(row7+48,line7,Total_1,2,16);
		LCD_ShowNum(row8+48,line8,Total_2,2,16);
	}
}

//�˵�
void Menu(void)
{
	static u8 key=0;	//�ް�������
	static u8 last_key=0;
	
	/****************  ��������ɨ��  ******************/
	tp_dev.scan(0);
	if(tp_dev.sta&TP_PRES_DOWN)	// ��������
	{
		last_key = 1;
		
		if(Is_In_Area(row9,line9,row9+16*2+8+8,line9+16+2+2))						key=1;	//ȷ����ť
		else if(Is_In_Area(row9+100,line9,row9+100+16*2+8+8,line9+16+2+2))			key=2;	//ȡ����ť
		else if(Is_In_Area(row7+72+20,line7,row7+72+20+16+2+2,line7+16+2+2))		key=3;	//����+1
		else if(Is_In_Area(row7+80+20+17,line7,row7+80+20+17+16+2+2,line7+16+2+2))	key=4;	//����-1
		else if(Is_In_Area(row8+72+20,line8,row8+72+20+16+2+2,line8+16+2+2))		key=5;	//ֽ��+1
		else if(Is_In_Area(row8+80+20+17,line8,row8+80+20+17+16+2+2,line8+16+2+2))	key=6;	//ֽ��-1
		else 																		key=0;	//����Ʒ��ѡ��
		
		switch(key)	//��ʾ�����°���ͼ��
		{
			case 1:	Button(row9,line9,row9+16*2+8+8,line9+16+2+2,PRESS,(u8*)"ȷ��",32,16);break;//ȷ��
			case 2:	Button(row9+100,line9,row9+100+16*2+8+8,line9+16+2+2,PRESS,(u8*)"ȡ��",32,16);break;//ȡ��
			case 3: Button(row7+72+20,line7,row7+72+20+16+2+2,line7+16+2+2,PRESS,(u8*)"��",16,16);break;//����+1
			case 4: Button(row7+80+20+17,line7,row7+80+20+17+16+2+2,line7+16+2+2,PRESS,(u8*)"��",16,16);break;//����-1
			case 5: Button(row8+72+20,line8,row8+72+20+16+2+2,line8+16+2+2,PRESS,(u8*)"��",16,16);break;//ֽ��+1
			case 6: Button(row8+80+20+17,line8,row8+80+20+17+16+2+2,line8+16+2+2,PRESS,(u8*)"��",16,16);break;//ֽ��-1
			default:break;
		}
	}
	else if(last_key)
	{
		last_key = 0;
	
		switch(key)	//ִ����Ӧ��������
		{
			case 1:	Confirm();break;//ȷ��
			case 2:	Cancel();break;//ȡ��
			case 3: Total_1=(Total_1>=Quantity_1)?Quantity_1:Total_1+1;break;//����+1
			case 4: Total_1=(Total_1<=0)?0:Total_1-1;break;//����-1
			case 5: Total_2=(Total_2>=Quantity_2)?Quantity_2:Total_2+1;break;//ֽ��+1
			case 6: Total_2=(Total_2<=0)?0:Total_2-1;	break;//ֽ��-1
			default:break;
		}
		
		//�ָ�ԭͼ��
		Button1(row9,line9,row9+16*2+8+8,line9+16+2+2,UNPRESS,(u8*)"ȷ��",32,16,color(73,130,234));
		Button1(row9+100,line9,row9+100+16*2+8+8,line9+16+2+2,UNPRESS,(u8*)"ȡ��",32,16,color(181,233,157));
		Button1(row7+72+20,line7,row7+72+20+16+2+2,line7+16+2+2,UNPRESS,(u8*)"��",16,16,color(181,233,157));
		Button1(row7+80+20+17,line7,row7+80+20+17+16+2+2,line7+16+2+2,UNPRESS,(u8*)"��",16,16,color(181,233,157));
		Button1(row8+72+20,line8,row8+72+20+16+2+2,line8+16+2+2,UNPRESS,(u8*)"��",16,16,color(181,233,157));
		Button1(row8+80+20+17,line8,row8+80+20+17+16+2+2,line8+16+2+2,UNPRESS,(u8*)"��",16,16,color(181,233,157));
	}
}

//ȷ������
void Confirm(void)
{
	extern u8 EN_BUY;
	en_refresh=0;	//��ֹˢ��
	LCD_Fill(0,30,239,202,WHITE);
	QRGenerator(40,40,6,"https://www.baidu.com/");
	EN_BUY = 1;
}

//ȡ������
void Cancel(void)
{
	extern u8 EN_BUY;
	EN_BUY = 0;
	LCD_Fill(0,30,239,202,WHITE);
	en_refresh=1;	//����ˢ��
	
	Total_1=0;
	Total_2=0;
	Layout();
}

