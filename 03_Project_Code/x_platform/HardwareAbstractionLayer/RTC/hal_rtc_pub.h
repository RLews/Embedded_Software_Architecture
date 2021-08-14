/*!
************************************************************************************************************************
* @file hal_rtc_pub.h
* @brief 
* @details 
* @author Lews Hammond
* @date 2021-8-14
************************************************************************************************************************
*/

#ifndef HAL_RTC_PUB_H
#define HAL_RTC_PUB_H

#include "drv_rtc_pub.h"

/*
************************************************************************************************************************
* RTC  Interface
************************************************************************************************************************
*/
typedef struct RTC_TIME_T
{
	uint16_t rtcYear;
	uint8_t rtcMon;
	uint8_t rtcDay;
	uint8_t rtcHour;
	uint8_t rtcMin;
	uint8_t rtcSec;
	uint8_t rtcWeek;
}RtcTime_t;

void Hal_RtcInit(void);
void Hal_RtcGetTime(RtcTime_t *pTime);
void Hal_RtcSetTime(RtcTime_t times);






#endif

