/*!
************************************************************************************************************************
* @file drv_uart.c
* @details
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/




#include "drv_uart.h"

static const UartConfig_t UartConfigTbl[EN_ALL_UART_NUM] =
{
    D_UART_CONFIG_TABLE
};

static StdBoolean_t UartInitFinished = D_STD_FALSE;

/*!
************************************************************************************************************************
* Function Drv_SysUartInit
* @brief ´®¿Ú³õÊ¼»¯
* @param
* @param
* @returns
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_SysUartInit(void)
{
    USART_InitTypeDef USART_InitStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};
    uint8_t i = 0;
    const UartConfig_t *pUartConfig = UartConfigTbl;

    for(i = 0; i < (uint8_t)EN_ALL_UART_NUM; i++)
    {
        if((pUartConfig[i].uartReg == USART2)
           || (pUartConfig[i].uartReg == USART3)
           || (pUartConfig[i].uartReg == UART4)
           || (pUartConfig[i].uartReg == UART5))
        {
            RCC_APB1PeriphClockCmd(pUartConfig[i].uartClock, ENABLE);
        }
        else
        {
            RCC_APB2PeriphClockCmd(pUartConfig[i].uartClock, ENABLE);
        }

        USART_DeInit(pUartConfig[i].uartReg);

        NVIC_InitStructure.NVIC_IRQChannel = pUartConfig[i].uartIrqCh;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = pUartConfig[i].uartPriority;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = pUartConfig[i].uartSubPrioirity;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

        USART_InitStructure.USART_BaudRate = pUartConfig[i].uartBaudRate;
        USART_InitStructure.USART_WordLength = pUartConfig[i].uartWordLen;
        USART_InitStructure.USART_StopBits = pUartConfig[i].uartStopBits;
        USART_InitStructure.USART_Parity = pUartConfig[i].uartParity;
        USART_InitStructure.USART_HardwareFlowControl = pUartConfig[i].uartHwFlowControl;
        USART_InitStructure.USART_Mode = pUartConfig[i].uartMode;
        USART_Init(pUartConfig[i].uartReg, &USART_InitStructure);
        D_DRV_UART_ITRX_ENABLE(pUartConfig[i].uartReg);
        USART_Cmd(pUartConfig[i].uartReg, ENABLE);
    }

    UartInitFinished = D_STD_TRUE;
}

/*!
************************************************************************************************************************
* Function Drv_GetUartInitSta
* @brief get uart initial status
* @param void
* @param void
* @returns StdBoolean_t : uart initial status
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

StdBoolean_t Drv_GetUartInitSta(void)
{
    return UartInitFinished;
}


/*!
************************************************************************************************************************
* Function Drv_UartITRxEnable
* @brief uart rx interrupt enable
* @param UartName_t name. which uarts.
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_UartITRxEnable(UartName_t name)
{
    D_DRV_UART_ITRX_ENABLE(UartConfigTbl[(uint8_t)name].uartReg);
}

/*!
************************************************************************************************************************
* Function Drv_UartITRxDisable
* @brief uart rx interrupt disable
* @param UartName_t name. which uarts.
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_UartITRxDisable(UartName_t name)
{
    D_DRV_UART_ITRX_DISABLE(UartConfigTbl[(uint8_t)name].uartReg);
}

/*!
************************************************************************************************************************
* Function Drv_UartITTxEnable
* @brief uart tx interrupt enable
* @param UartName_t name. which uarts.
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_UartITTxEnable(UartName_t name)
{
    D_DRV_UART_ITTX_ENABLE(UartConfigTbl[(uint8_t)name].uartReg);
}

/*!
************************************************************************************************************************
* Function Drv_UartITTxDisable
* @brief uart tx interrupt disable.
* @param UartName_t name. which uarts.
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_UartITTxDisable(UartName_t name)
{
    D_DRV_UART_ITTX_DISABLE(UartConfigTbl[(uint8_t)name].uartReg);
}

/*!
************************************************************************************************************************
* Function Drv_UartTxByte
* @brief uart transmit one byte of data.
* @param UartName_t name£º which uarts.
* @param const uint8_t dat£ºtransfer data
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_UartTxByte(UartName_t name, const uint8_t dat)
{
    USART_SendData(UartConfigTbl[(uint8_t)name].uartReg, (uint16_t)dat);
}

/*!
************************************************************************************************************************
* Function Drv_IsUartRxInt
* @brief if interrupt is transmit interrupt then return true
* @param UartName_t name. which uarts
* @param void
* @returns StdBoolean_t. true or false
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

StdBoolean_t Drv_IsUartRxInt(UartName_t name)
{
    StdBoolean_t isRx = D_STD_FALSE;

    if(USART_GetITStatus(UartConfigTbl[(uint8_t)name].uartReg, USART_IT_RXNE) != RESET)
    {
        isRx = D_STD_TRUE;
    }

    return isRx;
}

/*!
************************************************************************************************************************
* Function Drv_IsUartTxInt
* @brief if interrupt is receiver interrupt then return true.
* @param UartName_t name. which uarts.
* @param void
* @returns StdBoolean_t. true or false
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

StdBoolean_t Drv_IsUartTxInt(UartName_t name)
{
    StdBoolean_t isTx = D_STD_FALSE;

    if(USART_GetITStatus(UartConfigTbl[(uint8_t)name].uartReg, USART_IT_TXE) != RESET)
    {
        isTx = D_STD_TRUE;
    }

    return isTx;
}

/*!
************************************************************************************************************************
* Function Drv_UartGetRevData
* @brief read uart receiver data.
* @param UartName_t name
* @param void
* @returns uint8_t. one byte data
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

uint8_t Drv_UartGetRevData(UartName_t name)
{
    return (uint8_t)USART_ReceiveData(UartConfigTbl[(uint8_t)name].uartReg);
}


