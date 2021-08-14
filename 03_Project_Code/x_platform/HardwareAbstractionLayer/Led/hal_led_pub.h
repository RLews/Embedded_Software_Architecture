/*!
************************************************************************************************************************
* @file hal_led_pub.h
* @brief
* @details
* @author Lews Hammond
* @date 2021-8-14
************************************************************************************************************************
*/

#ifndef HAL_LED_PUB_H
#define HAL_LED_PUB_H

#include "drv_gpio_pub.h"


/*
************************************************************************************************************************
* Led  Interface
************************************************************************************************************************
*/
void Hal_IoInit(void);
void Hal_RunLedOn(void);
void Hal_RunLedOff(void);
void Hal_WifiLedOn(void);
void Hal_WifiLedOff(void);
uint8_t Hal_GetWifiLedSta(void);



#endif

