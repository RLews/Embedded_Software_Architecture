/*!
************************************************************************************************************************
* @file drv_gpio_pub.h
* @brief 
* @details 
* @author Lews Hammond
* @date 2021-8-14
************************************************************************************************************************
*/

#ifndef DRV_GPIO_PUB_H
#define DRV_GPIO_PUB_H

#include "platforms.h"

/*
************************************************************************************************************************
* GPIO Interface
************************************************************************************************************************
*/
typedef enum GPIO_NAME_T
{
	EN_SYSTEM_RUN_LED = 0,
	EN_WIFI_LED_GPIO,
	EN_WIFI_KEY_IO,
	EN_SYSTEM_UART_TX,
	EN_SYSTEM_UART_RX,
	EN_W25Q63_CS,
	EN_NRFxx_CS,
	EN_SD_CARD_CS,
	EN_SPI2_SCK,
	EN_SPI2_MISO,
	EN_SPI2_MOSI,
	EN_WIFI_UART_TX,
	EN_WIFI_UART_RX,
//	EN_FSMC_D2, 
//	EN_FSMC_D3, 
//	EN_FSMC_NOE,
//	EN_FSMC_NWE,
//	EN_FSMC_D13,
//	EN_FSMC_D14,
//	EN_FSMC_D15,
//	EN_FSMC_A16,
//	EN_FSMC_A17,
//	EN_FSMC_A18,
//	EN_FSMC_D0, 
//	EN_FSMC_D1, 
//	EN_FSMC_NBL0,
//	EN_FSMC_NBL1,
//	EN_FSMC_D4, 
//	EN_FSMC_D5, 
//	EN_FSMC_D6, 
//	EN_FSMC_D7, 
//	EN_FSMC_D8, 
//	EN_FSMC_D9, 
//	EN_FSMC_D10,
//	EN_FSMC_D11,
//	EN_FSMC_D12,
//	EN_FSMC_A0, 
//	EN_FSMC_A1, 
//	EN_FSMC_A2, 
//	EN_FSMC_A3, 
//	EN_FSMC_A4, 
//	EN_FSMC_A5, 
//	EN_FSMC_A6, 
//	EN_FSMC_A7, 
//	EN_FSMC_A8, 
//	EN_FSMC_A9, 
//	EN_FSMC_A10,
//	EN_FSMC_A11,
//	EN_FSMC_A12,
//	EN_FSMC_A13,
//	EN_FSMC_A14,
//	EN_FSMC_A15,
//	EN_FSMC_NE3,
	EN_ALL_GPIO_NUM
}GpioName_t;

typedef enum GPIO_STATE_T
{
	EN_GPIO_LOW = 0,
	EN_GPIO_HIGH,
	EN_GPIO_INPUT,
	EN_GPIO_NONE,
	EN_GPIO_ERR
}GpioState_t;

void Drv_GpioInit(void);
StdBoolean_t Drv_GetGpioInitSta(void);
void Drv_GpioNameOut(GpioName_t name, GpioState_t sta);
GpioState_t Drv_GpioNameIn(GpioName_t name);



#endif

