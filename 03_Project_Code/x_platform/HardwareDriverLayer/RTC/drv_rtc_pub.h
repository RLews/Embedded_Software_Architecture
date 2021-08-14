/*!
************************************************************************************************************************
* @file drv_rtc_pub.h
* @brief 
* @details 
* @author Lews Hammond
* @date 2021-8-14
************************************************************************************************************************
*/

#ifndef DRV_RTC_PUB_H
#define DRV_RTC_PUB_H

#include "platforms.h"

/*
************************************************************************************************************************
* RTC Interface
************************************************************************************************************************
*/
typedef enum DRV_RTC_ERR_T
{
	EN_RTC_OPT_OK = 0,
	EN_RTC_OPT_ERR_TIMROUT,
	EN_RTC_OPT_ERR_PARAMETER,
	EN_RTC_OPT_ERR_ALL_TYPE
}DrvRtcErr_t;

#define D_DRV_ENABLE_RTC_SEC_INT()		RTC_ITConfig(RTC_IT_SEC, ENABLE)
#define D_DRV_DISABLE_RTC_SEC_INT()		RTC_ITConfig(RTC_IT_SEC, DISABLE)

void Drv_RtcInit(void);
void Drv_RtcSetCount(uint32_t secCnt);
uint32_t Drv_RtcGetCount(void);
StdBoolean_t Drv_RtcIsSecInt(void);
void Drv_RtcIsrHandle(void);


#endif

