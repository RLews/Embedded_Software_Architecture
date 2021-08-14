/*!
************************************************************************************************************************
* @file hal_led.c
* @details 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/



#include "hal_led.h"

static uint8_t WifiLedSta = D_STD_OFF;

/*!
************************************************************************************************************************
* Function Hal_IoInit
* @brief io端口初始化
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Hal_IoInit(void)
{
	Drv_GpioInit();
}

/*!
************************************************************************************************************************
* Function Hal_RunLedOn
* @brief 系统led点亮
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Hal_RunLedOn(void)
{
	Drv_GpioNameOut(EN_SYSTEM_RUN_LED, EN_GPIO_LOW);
}

/*!
************************************************************************************************************************
* Function Hal_RunLedOff
* @brief 系统led熄灭
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Hal_RunLedOff(void)
{
	Drv_GpioNameOut(EN_SYSTEM_RUN_LED, EN_GPIO_HIGH);
}

/*!
************************************************************************************************************************
* Function Hal_WifiLedOn
* @brief wifi led点亮
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Hal_WifiLedOn(void)
{
	Drv_GpioNameOut(EN_WIFI_LED_GPIO, EN_GPIO_LOW);
	
	WifiLedSta = D_STD_ON;
}

/*!
************************************************************************************************************************
* Function Hal_WifiLedOff
* @brief wifi led熄灭
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Hal_WifiLedOff(void)
{
	Drv_GpioNameOut(EN_WIFI_LED_GPIO, EN_GPIO_HIGH);
	
	WifiLedSta = D_STD_OFF;
}


/*!
************************************************************************************************************************
* Function Hal_GetWifiLedSta
* @brief get wifi led state
* @param void
* @param void
* @returns uint8_t：led状态
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

uint8_t Hal_GetWifiLedSta(void)
{
	return WifiLedSta;
}

