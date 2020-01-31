#ifndef __HTTP_H
#define __HTTP_H
#include "sys.h"

#define API_KEY     "tpbCanP4sZQ7t=rPkw7q=RodyZc="		//API
#define DEV_ID      "531511953"							//设备ID	售货机

uint32_t HTTP_PostPkt(char *pkt, char *key, char *devid, 
	char * Drink,char * Paper,
	char *Drink_NumStr,char *Paper_NumStr);


#endif 
