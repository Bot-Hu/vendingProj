#include "http.h"
#include "string.h"
#include "stdio.h"

uint32_t HTTP_PostPkt(char *pkt, char *key, char *devid, 
	char * Drink,char * Paper,
	char *Drink_NumStr,char *Paper_NumStr)
{
    char dataBuf[1024] = {0};
    char lenBuf[10] = {0};
    *pkt = 0;

    sprintf(dataBuf, "{\"datastreams\":\
	[{\"id\":\"%s\",\"datapoints\":[{\"value\":%s}]},\
		{\"id\":\"%s\",\"datapoints\":[{\"value\":%s}]}]}",
		Drink, Drink_NumStr,//浮点数
			Paper,Paper_NumStr); 

    //采用分割字符串格式:type = 5
    sprintf(lenBuf, "%d", strlen(dataBuf));

    strcat(pkt, "POST /devices/");
    strcat(pkt, devid);
    strcat(pkt, "/datapoints HTTP/1.1\r\n");

    strcat(pkt, "api-key:");
    strcat(pkt, key);
    strcat(pkt, "\r\n");

    strcat(pkt, "Host:api.heclouds.com\r\n");

    strcat(pkt, "Content-Length:");
    strcat(pkt, lenBuf);
    strcat(pkt, "\r\n\r\n");

    strcat(pkt, dataBuf);
	strcat(pkt, "\r\n");

    return strlen(pkt);
}
