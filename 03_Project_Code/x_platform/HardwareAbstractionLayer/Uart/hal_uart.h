/*!
************************************************************************************************************************
* @file hal_uart.h
* @details 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/



#ifndef HAL_UART_H
#define HAL_UART_H

#include "hal_uart_pub.h"
#include "hal_int_pub.h"
#include "osal.h"


#define D_SYSTEM_ALL_UART_NUM			(uint8_t)EN_ALL_UART_NUM

#define D_SYS_UART_TX_BUFFER_SIZE		(320u)
#define D_SYS_UART_RX_BUFFER_SIZE		(256u)

#define D_SYS_UART_ENABLE_INT(ch)			do {\
	Drv_UartITRxEnable(ch); \
	Drv_UartITTxEnable(ch); \
}while (0)

#define D_SYS_UART_DISABLE_INT(ch)			do {\
	Drv_UartITRxDisable(ch); \
	Drv_UartITTxDisable(ch); \
}while (0)



#endif

