/*!
************************************************************************************************************************
* @file hal_rtc.h
* @details
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/


#ifndef HAL_RTC_H
#define HAL_RTC_H

#include "hal_rtc_pub.h"
#include "hal_int_pub.h"

#define D_DEFAULT_SYS_TIME_YEAR     2019U
#define D_DEFAULT_SYS_TIME_MON      6U
#define D_DEFAULT_SYS_TIME_DAY      6U
#define D_DEFAULT_SYS_TIME_HOUR     16U
#define D_DEFAULT_SYS_TIME_MIN      30U
#define D_DEFAULT_SYS_TIME_SEC      30U
#define D_DEFAULT_SYS_TIME_WEEK     4U

#define D_HAL_LEAP_YEAR             (366U)
#define D_HAL_NOR_YEAR              (365U)
#define D_HAL_TIME_HOUR_IN_A_DAY    (24U)
#define D_HAL_TIME_MIN_IN_A_HOUR    (60U)
#define D_HAL_TIME_SEC_IN_A_MIN     (60U)

#define D_HAL_SEC_IN_A_DAY          ( (uint32_t)((D_HAL_TIME_HOUR_IN_A_DAY * D_HAL_TIME_MIN_IN_A_HOUR) * D_HAL_TIME_SEC_IN_A_MIN) )
#define D_HAL_SEC_IN_A_HOUR         ( (uint32_t)(D_HAL_TIME_MIN_IN_A_HOUR * D_HAL_TIME_SEC_IN_A_MIN) )

#define D_HAL_SEC_IN_LEAP_YEAR      ( (uint32_t)((uint32_t)D_HAL_LEAP_YEAR * D_HAL_SEC_IN_A_DAY) )
#define D_HAL_SEC_IN_NOR_YEAR       ( (uint32_t)((uint32_t)D_HAL_NOR_YEAR * D_HAL_SEC_IN_A_DAY) )


#endif

