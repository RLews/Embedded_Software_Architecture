/*!
************************************************************************************************************************
* @file drv_uart.h
* @details
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/



#ifndef DRV_UART_H
#define DRV_UART_H

#include "drv_uart_pub.h"



typedef struct UART_CONFIG_T
{
    UartName_t uartName;
    uint32_t uartClock;
    USART_TypeDef * uartReg;
    uint8_t uartIrqCh;
    uint8_t uartPriority;
    uint8_t uartSubPrioirity;
    uint32_t uartBaudRate;
    uint16_t uartWordLen;
    uint16_t uartStopBits;
    uint16_t uartParity;
    uint16_t uartHwFlowControl;
    uint16_t uartMode;
} UartConfig_t;

#define D_UART_CONFIG_TABLE     \
    {EN_SYS_COM, RCC_APB2Periph_USART1, USART1, USART1_IRQn, 1, 3, 115200, USART_WordLength_8b, \
     USART_StopBits_1, USART_Parity_No, USART_HardwareFlowControl_None, (USART_Mode_Rx | USART_Mode_Tx)}, \
    {EN_WIFI_COM, RCC_APB1Periph_USART3, USART3, USART3_IRQn, 2, 3, 9600, USART_WordLength_8b, \
     USART_StopBits_1, USART_Parity_No, USART_HardwareFlowControl_None, (USART_Mode_Rx | USART_Mode_Tx)}



#define D_DRV_UART_ITRX_ENABLE(reg)         USART_ITConfig(reg, USART_IT_RXNE, ENABLE)
#define D_DRV_UART_ITRX_DISABLE(reg)        USART_ITConfig(reg, USART_IT_RXNE, DISABLE)

#define D_DRV_UART_ITTX_ENABLE(reg)         USART_ITConfig(reg, USART_IT_TXE, ENABLE)
#define D_DRV_UART_ITTX_DISABLE(reg)        USART_ITConfig(reg, USART_IT_TXE, DISABLE)




#endif

