/*!
************************************************************************************************************************
* @file hal_uart.c
* @details 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/


#include "hal_uart.h"

static volatile uint8_t SysUartTxBuf[D_SYSTEM_ALL_UART_NUM][D_SYS_UART_TX_BUFFER_SIZE] = {0};
static volatile uint8_t SysUartRxBuf[D_SYSTEM_ALL_UART_NUM][D_SYS_UART_RX_BUFFER_SIZE] = {0};
static volatile SrvQueue_t SysUartTxQueue[D_SYSTEM_ALL_UART_NUM] = {0};
static volatile SrvQueue_t SysUartRxQueue[D_SYSTEM_ALL_UART_NUM] = {0};

static void Hal_SysComIsrHandle(void);
static void Hal_WifiComIsrHandle(void);

static UartRxSemPost SysRxSemPostFunc = NULL;
static UartRxSemPost WifiRxSemPostFunc = NULL;

/*!
************************************************************************************************************************
* Function Hal_SysUartInit
* @brief 串口抽象层初始化
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Hal_SysUartInit(void)
{
	uint8_t i = 0;
	
	for (i = 0; i < D_SYSTEM_ALL_UART_NUM; i++)
	{
		Srv_QueueInit(&SysUartTxQueue[i], (volatile uint8_t *)&SysUartTxBuf[i], D_SYS_UART_TX_BUFFER_SIZE);
		Srv_QueueInit(&SysUartRxQueue[i], (volatile uint8_t *)&SysUartRxBuf[i], D_SYS_UART_RX_BUFFER_SIZE);
	}

	/* TODO: add uart interrupt function */
	Hal_SysISRSet(EN_USART1_ISR, Hal_SysComIsrHandle);
	Hal_SysISRSet(EN_USART3_ISR, Hal_WifiComIsrHandle);

	Drv_SysUartInit();
}

/*!
************************************************************************************************************************
* Function Hal_SetSysRxSemPostFunc
* @brief Set Rx Sem Post function
* @param UartRxSemPost pFunc : sem post function pointer
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Hal_SetSysRxSemPostFunc(UartRxSemPost pFunc)
{
	SysRxSemPostFunc = pFunc;
}

/*!
************************************************************************************************************************
* Function Hal_SetWifiRxSemPostFunc
* @brief set wifi sem post function
* @param UartRxSemPost pFunc : sem post function pointer
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Hal_SetWifiRxSemPostFunc(UartRxSemPost pFunc)
{
	WifiRxSemPostFunc = pFunc;
}

/*!
************************************************************************************************************************
* Function Hal_UartReadByte
* @brief uart read one byte data
* @param UartName_t name.	which one uart
* @param uint8_t *dat.		read data point
* @returns SrvQueueError_t.	read operation result
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

SrvQueueError_t Hal_UartReadByte(UartName_t name, uint8_t *dat)
{
	SrvQueueError_t opt = EN_QUEUE_OPT_OK;
	D_OSAL_ALLOC_CRITICAL_SR();

	D_OSAL_ENTER_CRITICAL();
	Drv_UartITRxDisable(name);

	opt = Srv_QueueOut(&SysUartRxQueue[name], dat);

	D_OSAL_EXIT_CRITICAL();
	Drv_UartITRxEnable(name);

	return opt;
}

/*!
************************************************************************************************************************
* Function Hal_UartWrite
* @brief uart write data
* @param UartName_t name.	which one uart
* @param uint8_t dat[].		read data point
* @param uint8_t len.		data length
* @returns SrvQueueError_t.	write operation result.
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

SrvQueueError_t Hal_UartWrite(UartName_t name, const uint8_t dat[], uint16_t len)
{
	SrvQueueError_t opt = EN_QUEUE_OPT_OK;
	uint8_t i = 0;
	volatile SrvQueue_t *pQueue = &SysUartTxQueue[name];
	StdBoolean_t txFlagTrigger = D_STD_FALSE;
	uint8_t firstDat = 0;
	D_OSAL_ALLOC_CRITICAL_SR();
	
	if ((len == 0) || (len > D_SYS_UART_TX_BUFFER_SIZE) || (dat == NULL))
	{
		opt = EN_QUEUE_OPT_NONE;
		return opt;
	}

	Drv_UartITTxDisable(name);
	D_OSAL_ENTER_CRITICAL();
	
	if (Srv_QueueIsEmpty(pQueue) == D_STD_TRUE)
	{
		txFlagTrigger = D_STD_TRUE;/* need trigger tx interrupt */
	}

	for (i = 0; i < len; i++)
	{
		opt = Srv_QueueIn(pQueue, dat[i]);
		if (opt != EN_QUEUE_OPT_OK)
		{
			break;/* exception */
		}
	}

	if (txFlagTrigger == D_STD_TRUE)
	{
		opt = Srv_ReadQueueHead(pQueue, &firstDat);
		if (opt == EN_QUEUE_OPT_OK)
		{
			Drv_UartTxByte(name, firstDat);/* Trigger new transfer */
		}
	}

	D_OSAL_EXIT_CRITICAL();
	Drv_UartITTxEnable(name);
	
	return opt;
}

/*!
************************************************************************************************************************
* Function Hal_SysComIsrHandle
* @brief uart interrupt hander function.
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static void Hal_SysComIsrHandle(void)
{
	volatile SrvQueue_t *pTxQueue = &SysUartTxQueue[EN_SYS_COM];
	volatile SrvQueue_t *pRxQueue = &SysUartRxQueue[EN_SYS_COM];
	uint8_t uartDat = 0;
	
	if (Drv_IsUartTxInt(EN_SYS_COM) == D_STD_TRUE)
	{
		/* Make sure to queue out after the send completed */
		if (EN_QUEUE_OPT_EMPTY == Srv_QueueOut(pTxQueue, &uartDat))
		{
			Drv_UartITTxDisable(EN_SYS_COM);/* send finish */
		}
		else
		{
			(void)Srv_ReadQueueHead(pTxQueue, &uartDat);
			Drv_UartTxByte(EN_SYS_COM, uartDat);
		}
	}

	if (Drv_IsUartRxInt(EN_SYS_COM) == D_STD_TRUE)
	{
		uartDat = Drv_UartGetRevData(EN_SYS_COM);
		(void)Srv_QueueIn(pRxQueue, uartDat);
		if (SysRxSemPostFunc != NULL)
		{
			SysRxSemPostFunc();
		}
	}
}

/*!
************************************************************************************************************************
* Function Hal_WifiComIsrHandle
* @brief wifi uart interrupt handle
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static void Hal_WifiComIsrHandle(void)
{
	volatile SrvQueue_t *pTxQueue = &SysUartTxQueue[EN_WIFI_COM];
	volatile SrvQueue_t *pRxQueue = &SysUartRxQueue[EN_WIFI_COM];
	uint8_t uartDat = 0;
	
	if (Drv_IsUartTxInt(EN_WIFI_COM) == D_STD_TRUE)
	{
		/* Make sure to queue out after the send completed */
		if (EN_QUEUE_OPT_EMPTY == Srv_QueueOut(pTxQueue, &uartDat))
		{
			Drv_UartITTxDisable(EN_WIFI_COM);/* send finish */
		}
		else
		{
			(void)Srv_ReadQueueHead(pTxQueue, &uartDat);
			Drv_UartTxByte(EN_WIFI_COM, uartDat);
		}
	}

	if (Drv_IsUartRxInt(EN_WIFI_COM) == D_STD_TRUE)
	{
		uartDat = Drv_UartGetRevData(EN_WIFI_COM);
		(void)Srv_QueueIn(pRxQueue, uartDat);
		if (WifiRxSemPostFunc != NULL)
		{
			WifiRxSemPostFunc();
		}
	}
}

