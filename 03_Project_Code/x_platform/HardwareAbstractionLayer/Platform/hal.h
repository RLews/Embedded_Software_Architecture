/*!
************************************************************************************************************************
* @file hal.h
* @details 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/



#ifndef HAL_H
#define HAL_H



#include "hal_int_pub.h"
#include "hal_key_pub.h"
#include "hal_led_pub.h"
#include "hal_rtc_pub.h"
#include "hal_sd_pub.h"
#include "hal_sram_pub.h"
#include "hal_timer_pub.h"
#include "hal_uart_pub.h"
#include "hal_wdg_pub.h"


/*
************************************************************************************************************************
* Hardware Abstraction Layer initial Interface
************************************************************************************************************************
*/
typedef enum HAL_INIT_STA_T
{
	EN_HAL_UNINIT = 0,
	EN_HAL_WDG_INIT_FINISH,
	EN_HAL_INT_INIT_FINISH,
	EN_HAL_IO_INIT_FINISH,
	EN_HAL_UART_INIT_FINISH,
	EN_HAL_RTC_INIT_FINISH,
	EN_HAL_SRAM_INIT_FINISH,
	EN_HAL_SRAM_INIT_ERR,
	EN_HAL_ALL_INIT_FINISH
}HalInitSta_t;

void Hal_SysInit(void);
HalInitSta_t Hal_GetInitStatus(void);



#endif
