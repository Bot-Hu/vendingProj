#ifndef _QRCODE_MAIN
#define _QRCODE_MAIN
#include "stm32f10x.h"

void QRGenerator(u8 x,u8 y,u8 display_size,char *input);
void displayQRCode(u8 x,u8 y,u8 display_size,int side,uint8_t *bitdata);

#endif
