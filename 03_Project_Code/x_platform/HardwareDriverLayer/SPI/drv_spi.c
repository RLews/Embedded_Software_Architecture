/*!
************************************************************************************************************************
* @file drv_spi.c
* @details 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/



#include "drv_spi.h"

static const SpiConfig_t SpiConfigArr[EN_ALL_SPI_NUM] = {
	D_SPI_CONFIG_ARRAY
};

static StdBoolean_t SpiInitFinished = D_STD_FALSE;

static SpiError_t Drv_Spi2IsBusy(void);

/*!
************************************************************************************************************************
* Function Drv_SpiInit
* @brief spi初始化
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_SpiInit(void)
{
	uint8_t i = 0;
	SPI_InitTypeDef SPI_InitStructure = {0};
	const SpiConfig_t *pConfig = SpiConfigArr;

	for (i = 0; i < (uint8_t)EN_ALL_SPI_NUM; i++)
	{
		RCC_APB1PeriphClockCmd(pConfig[i].spiRcc,ENABLE);
		SPI_InitStructure.SPI_Direction = pConfig[i].spiDir;
		SPI_InitStructure.SPI_Mode = pConfig[i].spiMode;
		SPI_InitStructure.SPI_DataSize = pConfig[i].spiDataSize;
		SPI_InitStructure.SPI_CPOL = pConfig[i].spiCpol;
		SPI_InitStructure.SPI_CPHA = pConfig[i].spiCpha;
		SPI_InitStructure.SPI_NSS = pConfig[i].spiNss;
		SPI_InitStructure.SPI_BaudRatePrescaler = pConfig[i].spiBaudRatePer;
		SPI_InitStructure.SPI_FirstBit = pConfig[i].spiFirstBits;
		SPI_InitStructure.SPI_CRCPolynomial = pConfig[i].spiCrc;
		SPI_Init(pConfig[i].spiDef, &SPI_InitStructure);
		SPI_Cmd(pConfig[i].spiDef, ENABLE);
	}

	SpiInitFinished = D_STD_TRUE;
}

/*!
************************************************************************************************************************
* Function Drv_GetSpiInitSta
* @brief 获取spi初始化状态
* @param void
* @param void
* @returns stdBoolean_t：是否初始化完成
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

StdBoolean_t Drv_GetSpiInitSta(void)
{
	return SpiInitFinished;
}


/*!
************************************************************************************************************************
* Function Drv_Spi2SetSpeed
* @brief 设置spi速度
* @param uint8_t baudRatePre：spi速率
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_Spi2SetSpeed(uint8_t baudRatePre)
{
	SPI2->CR1 &= 0xFFC7U;
	SPI2->CR1 |= baudRatePre;
	SPI_Cmd(SPI2,ENABLE);
}

/*!
************************************************************************************************************************
* Function Drv_Spi2IsBusy
* @brief 判断spi是否忙
* @param void
* @param void
* @returns spiError_t：spi状态
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static SpiError_t Drv_Spi2IsBusy(void)
{
	uint16_t timeCount = 0;
	
	do {
		timeCount++;
		if (timeCount >= D_SPI2_TIMEOUT_LIMIT_VAL)
		{
			return EN_OPERATION_SPI_BUSY;
		}
	}while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

	return EN_OPERATION_SPI_OK;
}

/*!
************************************************************************************************************************
* Function Drv_Spi2RWByte
* @brief 读写spi一个字节
* @param const uint8_t txDat：发送的数据
* @param uint8_t * rxDat：接收的数据
* @returns spiError_t：spi状态
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

SpiError_t Drv_Spi2RWByte(const uint8_t txDat, uint8_t * rxDat)
{
	uint16_t timeCount = 0;

	if (Drv_Spi2IsBusy() == EN_OPERATION_SPI_BUSY)
	{
		return EN_OPERATION_SPI_BUSY;
	}

	SPI_I2S_SendData(SPI2, txDat);

	do {
		timeCount++;
		if (timeCount >= D_SPI2_TIMEOUT_LIMIT_VAL)
		{
			return EN_OPERATION_SPI_TIMEOUT;
		}
	}while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	
	*rxDat = (uint8_t)SPI_I2S_ReceiveData(SPI2);

	return EN_OPERATION_SPI_OK;
}

