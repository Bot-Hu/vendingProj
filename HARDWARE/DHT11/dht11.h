#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板V3
//DHT11数字温湿度传感器驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/1/16
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
    
//IO方向设置
#define DHT11_IO_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
#define DHT11_IO_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}
////IO操作函数											   
#define	DHT11_DQ_OUT PBout(11) //数据端口	PG11 
#define	DHT11_DQ_IN  PBin(11)  //数据端口	PG11


u8 DHT11_Init(void);		//初始化DHT11
u8 DHT11_Read_Data(u8 *temp, u8 *temp1, u8 *humi, u8 *humi1 );
u8 DHT11_Read_Byte(void);	//读出一个字节
u8 DHT11_Read_Bit(void);	//读出一个位
u8 DHT11_Check(void);		//检测是否存在DHT11
void DHT11_Rst(void);		//复位DHT11    
#endif















