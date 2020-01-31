#ifndef __TEXT_H__
#define __TEXT_H__	 
#include <stm32f10x.h>
#include "fontupd.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK MiniSTM32������
//������ʾ ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/14
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
					     
void Get_HzMat(unsigned char *code,unsigned char *mat,u8 size);			//�õ����ֵĵ�����
void Show_Font(u16 x,u16 y,u8 *font,u8 size,u8 mode);					//��ָ��λ����ʾһ������
void Show_Str(u16 x,u16 y,u16 width,u16 height,u8*str,u8 size,u8 mode);	//��ָ��λ����ʾһ���ַ��� 

void Show_Font_Color(u16 x,u16 y,u8 *font,u8 size,u8 mode,u16 color);					//��ָ��λ����ʾһ�����ִ���ɫ
void Show_Str_Color(u16 x,u16 y,u16 width,u16 height,u8*str,u8 size,u8 mode,u16 color);	//��ָ��λ����ʾһ���ַ�������ɫ 

void Show_Str_Mid(u16 x,u16 y,u8*str,u8 size,u8 len);

/***********************************************/
void PutHZ16(u16 x,u16 y,u8 c[],u8 mode);
void Show_HZ16(u16 x,u16 y,u8*str,u8 mode);

void PutHZ16_Color(u16 x,u16 y,u8 c[],u8 mode,u16 color);
void Show_HZ16_Color(u16 x,u16 y,u8*str,u8 mode,u16 color);
/***********************************************/

#endif
