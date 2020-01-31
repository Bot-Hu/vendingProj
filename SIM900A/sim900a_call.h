#ifndef __CALL_H
#define __CALL_H
#include "sys.h"

void CALL_Init(u8 num);

void CALL_Temp_Scanf(u8 air_temp,u8 fun_temp,u8 room_temp);
void CALL_Humi_Scanf(u8 room_humi);
void CALL_Close_Scanf(u8 water_leakage,u8 smoke_detector,u8 room_door_isClose,u8 cabinet_door_isClose);

#endif
