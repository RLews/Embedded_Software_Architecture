/*!
************************************************************************************************************************
* @file hal_uart_pub.h
* @brief
* @details
* @author Lews Hammond
* @date 2021-8-14
************************************************************************************************************************
*/

#ifndef HAL_UART_PUB_H
#define HAL_UART_PUB_H

#include "drv_uart_pub.h"
#include "srv_queue.h"

typedef void (*UartRxSemPost)(void);


/*
************************************************************************************************************************
* Uart  Interface
************************************************************************************************************************
*/
void Hal_SysUartInit(void);
void Hal_SetSysRxSemPostFunc(UartRxSemPost pFunc);
void Hal_SetWifiRxSemPostFunc(UartRxSemPost pFunc);

SrvQueueError_t Hal_UartWrite(UartName_t name, const uint8_t dat[], uint16_t len);
SrvQueueError_t Hal_UartReadByte(UartName_t name, uint8_t *dat);










#endif

