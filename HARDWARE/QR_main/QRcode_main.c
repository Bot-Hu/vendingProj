#include "QRcode_main.h"
#include "string.h"
#include "qr_encode.h"
#include "lcd.h"

//获取二维码数据
void QRGenerator(u8 x,u8 y,u8 display_size,char *input)
{
	int qr_side;
	uint8_t bitdata[QR_MAX_BITDATA];
	
	//remove newline
	if(input[strlen(input)-1] == '\n')	input[strlen(input)-1] = 0;
	
	qr_side = qr_encode(QR_LEVEL_L,0,input,0,bitdata);
	displayQRCode(x,y,display_size,qr_side,bitdata);
}

//显示二维码数据
void displayQRCode(u8 x,u8 y,u8 display_size,int qr_side,uint8_t *bitdata)
{
	int i=0;
	int j=0;
	int a=0;
	int l=0;
	int n=0;
	int OUT_FILE_PIXEL_PRESCALER=display_size;
	
	if(qr_side == 21)	OUT_FILE_PIXEL_PRESCALER=display_size;
	for(i=0;i<qr_side;i++){
		for(j=0;j<qr_side;j++){
			a = j*qr_side + i;
			if( (bitdata[a/8] & ( 1<<(7-a%8) ) ) ){
				for(l=0;l<OUT_FILE_PIXEL_PRESCALER;l++){
					for(n=0;n<OUT_FILE_PIXEL_PRESCALER;n++){
						LCD_Fast_DrawPoint(OUT_FILE_PIXEL_PRESCALER*i+l+x,OUT_FILE_PIXEL_PRESCALER*j+n+y,BLACK);
					}
				}
			}
		}
	}
}
