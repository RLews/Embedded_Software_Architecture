/*!
************************************************************************************************************************
* @file drv_uart_pub.h
* @brief
* @details
* @author Lews Hammond
* @date 2021-8-14
************************************************************************************************************************
*/

#ifndef DRV_UART_PUB_H
#define DRV_UART_PUB_H

#include "platforms.h"


/*
************************************************************************************************************************
* UART Interface
************************************************************************************************************************
*/
typedef enum UART_NAME_T
{
    EN_SYS_COM = 0,
    EN_WIFI_COM,
    EN_ALL_UART_NUM
} UartName_t;

void Drv_SysUartInit(void);
StdBoolean_t Drv_GetUartInitSta(void);
void Drv_UartTxByte(UartName_t name, const uint8_t dat);
void Drv_UartITRxEnable(UartName_t name);
void Drv_UartITRxDisable(UartName_t name);
void Drv_UartITTxEnable(UartName_t name);
void Drv_UartITTxDisable(UartName_t name);
StdBoolean_t Drv_IsUartTxInt(UartName_t name);
StdBoolean_t Drv_IsUartRxInt(UartName_t name);
uint8_t Drv_UartGetRevData(UartName_t name);





#endif

