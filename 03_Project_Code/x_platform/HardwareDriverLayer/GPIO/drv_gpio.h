/*!
************************************************************************************************************************
* @file drv_gpio.h
* @details 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/



#ifndef DRV_GPIO_H
#define DRV_GPIO_H

#include "drv_gpio_pub.h"




typedef struct DRV_GPIO_CONFIG_T
{
	GpioName_t gpioName;
	GPIO_TypeDef * gpioGruop;
	GPIOMode_TypeDef gpioMode;
	uint16_t gpioPin;
	GpioState_t initIOSta;
	GPIOSpeed_TypeDef gpioSpd;
	uint32_t gpioPeriphClock;
}GpioConfig_t;

#define D_USED_GPIO_CONFIG		\
	{EN_SYSTEM_RUN_LED, GPIOB, GPIO_Mode_Out_PP, GPIO_Pin_5, EN_GPIO_HIGH, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOB}, \
	{EN_WIFI_LED_GPIO, GPIOE, GPIO_Mode_Out_PP, GPIO_Pin_5, EN_GPIO_HIGH, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOE}, \
	{EN_WIFI_KEY_IO, GPIOE, GPIO_Mode_IPU, GPIO_Pin_4, EN_GPIO_INPUT, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOE}, \
	{EN_SYSTEM_UART_TX, GPIOA, GPIO_Mode_AF_PP, GPIO_Pin_9, EN_GPIO_HIGH, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOA}, \
	{EN_SYSTEM_UART_RX, GPIOA, GPIO_Mode_IN_FLOATING, GPIO_Pin_10, EN_GPIO_INPUT, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOA}, \
	{EN_W25Q63_CS, GPIOB, GPIO_Mode_Out_PP, GPIO_Pin_12, EN_GPIO_HIGH, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOB}, \
	{EN_NRFxx_CS, GPIOG, GPIO_Mode_Out_PP, GPIO_Pin_7, EN_GPIO_HIGH, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOG}, \
	{EN_SD_CARD_CS, GPIOD, GPIO_Mode_Out_PP, GPIO_Pin_2, EN_GPIO_HIGH, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOD}, \
	{EN_SPI2_SCK, GPIOB, GPIO_Mode_AF_PP, GPIO_Pin_13, EN_GPIO_HIGH, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOB}, \
	{EN_SPI2_MISO, GPIOB, GPIO_Mode_AF_PP, GPIO_Pin_14, EN_GPIO_HIGH, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOB}, \
	{EN_SPI2_MOSI, GPIOB, GPIO_Mode_AF_PP, GPIO_Pin_15, EN_GPIO_HIGH, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOB}, \
	{EN_WIFI_UART_TX, GPIOB, GPIO_Mode_AF_PP, GPIO_Pin_10, EN_GPIO_HIGH, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOB}, \
	{EN_WIFI_UART_RX, GPIOB, GPIO_Mode_IN_FLOATING, GPIO_Pin_11, EN_GPIO_INPUT, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOB}, \
//	{EN_FSMC_D2, GPIOD, GPIO_Mode_AF_PP, GPIO_Pin_0, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOD}, \
//	{EN_FSMC_D3, GPIOD, GPIO_Mode_AF_PP, GPIO_Pin_1, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOD}, \
//	{EN_FSMC_NOE, GPIOD, GPIO_Mode_AF_PP, GPIO_Pin_4, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOD}, \
//	{EN_FSMC_NWE, GPIOD, GPIO_Mode_AF_PP, GPIO_Pin_5, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOD}, \
//	{EN_FSMC_D13, GPIOD, GPIO_Mode_AF_PP, GPIO_Pin_8, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOD}, \
//	{EN_FSMC_D14, GPIOD, GPIO_Mode_AF_PP, GPIO_Pin_9, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOD}, \
//	{EN_FSMC_D15, GPIOD, GPIO_Mode_AF_PP, GPIO_Pin_10, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOD}, \
//	{EN_FSMC_A16, GPIOD, GPIO_Mode_AF_PP, GPIO_Pin_11, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOD}, \
//	{EN_FSMC_A17, GPIOD, GPIO_Mode_AF_PP, GPIO_Pin_12, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOD}, \
//	{EN_FSMC_A18, GPIOD, GPIO_Mode_AF_PP, GPIO_Pin_13, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOD}, \
//	{EN_FSMC_D0, GPIOD, GPIO_Mode_AF_PP, GPIO_Pin_14, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOD}, \
//	{EN_FSMC_D1, GPIOD, GPIO_Mode_AF_PP, GPIO_Pin_15, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOD}, \
//	{EN_FSMC_NBL0, GPIOE, GPIO_Mode_AF_PP, GPIO_Pin_0, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOE}, \
//	{EN_FSMC_NBL1, GPIOE, GPIO_Mode_AF_PP, GPIO_Pin_1, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOE}, \
//	{EN_FSMC_D4, GPIOE, GPIO_Mode_AF_PP, GPIO_Pin_7, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOE}, \
//	{EN_FSMC_D5, GPIOE, GPIO_Mode_AF_PP, GPIO_Pin_8, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOE}, \
//	{EN_FSMC_D6, GPIOE, GPIO_Mode_AF_PP, GPIO_Pin_9, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOE}, \
//	{EN_FSMC_D7, GPIOE, GPIO_Mode_AF_PP, GPIO_Pin_10, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOE}, \
//	{EN_FSMC_D8, GPIOE, GPIO_Mode_AF_PP, GPIO_Pin_11, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOE}, \
//	{EN_FSMC_D9, GPIOE, GPIO_Mode_AF_PP, GPIO_Pin_12, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOE}, \
//	{EN_FSMC_D10, GPIOE, GPIO_Mode_AF_PP, GPIO_Pin_13, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOE}, \
//	{EN_FSMC_D11, GPIOE, GPIO_Mode_AF_PP, GPIO_Pin_14, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOE}, \
//	{EN_FSMC_D12, GPIOE, GPIO_Mode_AF_PP, GPIO_Pin_15, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOE}, \
//	{EN_FSMC_A0, GPIOF, GPIO_Mode_AF_PP, GPIO_Pin_0, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOF}, \
//	{EN_FSMC_A1, GPIOF, GPIO_Mode_AF_PP, GPIO_Pin_1, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOF}, \
//	{EN_FSMC_A2, GPIOF, GPIO_Mode_AF_PP, GPIO_Pin_2, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOF}, \
//	{EN_FSMC_A3, GPIOF, GPIO_Mode_AF_PP, GPIO_Pin_3, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOF}, \
//	{EN_FSMC_A4, GPIOF, GPIO_Mode_AF_PP, GPIO_Pin_4, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOF}, \
//	{EN_FSMC_A5, GPIOF, GPIO_Mode_AF_PP, GPIO_Pin_5, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOF}, \
//	{EN_FSMC_A6, GPIOF, GPIO_Mode_AF_PP, GPIO_Pin_12, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOF}, \
//	{EN_FSMC_A7, GPIOF, GPIO_Mode_AF_PP, GPIO_Pin_13, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOF}, \
//	{EN_FSMC_A8, GPIOF, GPIO_Mode_AF_PP, GPIO_Pin_14, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOF}, \
//	{EN_FSMC_A9, GPIOF, GPIO_Mode_AF_PP, GPIO_Pin_15, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOF}, \
//	{EN_FSMC_A10, GPIOG, GPIO_Mode_AF_PP, GPIO_Pin_0, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOG}, \
//	{EN_FSMC_A11, GPIOG, GPIO_Mode_AF_PP, GPIO_Pin_1, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOG}, \
//	{EN_FSMC_A12, GPIOG, GPIO_Mode_AF_PP, GPIO_Pin_2, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOG}, \
//	{EN_FSMC_A13, GPIOG, GPIO_Mode_AF_PP, GPIO_Pin_3, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOG}, \
//	{EN_FSMC_A14, GPIOG, GPIO_Mode_AF_PP, GPIO_Pin_4, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOG}, \
//	{EN_FSMC_A15, GPIOG, GPIO_Mode_AF_PP, GPIO_Pin_5, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOG}, \
//	{EN_FSMC_NE3, GPIOG, GPIO_Mode_AF_PP, GPIO_Pin_10, EN_GPIO_NONE, GPIO_Speed_50MHz, RCC_APB2Periph_GPIOG}

#endif

