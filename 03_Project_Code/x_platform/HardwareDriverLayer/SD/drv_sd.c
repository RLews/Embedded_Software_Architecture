/*!
************************************************************************************************************************
* @file drv_sd.c
* @details 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/



#include "drv_sd.h"




/*!
************************************************************************************************************************
* Function Drv_SDCardSpiInit
* @brief sd����spi�ӿڳ�ʼ��
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_SDCardSpiInit(void)
{
	uint8_t initTx = 0xFF;
	uint8_t initRx = 0;
	
	if (D_STD_FALSE == Drv_GetGpioInitSta())
	{
		Drv_GpioInit();
	}

	if (D_STD_FALSE == Drv_GetSpiInitSta())
	{
		Drv_SpiInit();
	}
	
	(void)D_SD_CARD_WR_BYTE_FUNC(initTx, &initRx);
	D_SD_CARD_SPI_CS_CANCEL();
}

/*!
************************************************************************************************************************
* Function Drv_SDCardCanelSelect
* @brief sd��Ƭѡѡ��
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_SDCardCanelSelect(void)
{
	uint8_t data = 0;
	
	D_SD_CARD_SPI_CS_CANCEL();
	(void)D_SD_CARD_WR_BYTE_FUNC(0xFF, &data);
}

/*!
************************************************************************************************************************
* Function Drv_SDCardWaitReady
* @brief ��sd��׼������
* @param void
* @param void
* @returns sdCardErr_t��sd��״̬
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

SdCardErr_t Drv_SDCardWaitReady(void)
{
	uint32_t timeOutCnt = 0;
	uint8_t rxDat = 0;

	do {
		(void)D_SD_CARD_WR_BYTE_FUNC(0xFFU, &rxDat);
		if (rxDat == 0xFFU)
		{
			return EN_SD_OPT_OK;
		}
	}while (timeOutCnt < 0xFFFFFFUL);

	return EN_SD_ERR_TIMEOUT;
}

/*!
************************************************************************************************************************
* Function Drv_SDCardSelect
* @brief ѡ��sd��
* @param void
* @param void
* @returns sdCardErr_t��sd��״̬
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

SdCardErr_t Drv_SDCardSelect(void)
{
	SdCardErr_t tOptRes = EN_SD_OPT_OK;
	
	D_SD_CARD_SPI_CS_SELECT();
	if (Drv_SDCardWaitReady() == EN_SD_OPT_OK)
	{
		tOptRes = EN_SD_OPT_OK;
	}
	else
	{
		D_SD_CARD_SPI_CS_CANCEL();
		tOptRes = EN_SD_ERR_TIMEOUT;
	}

	return tOptRes;
}

/*!
************************************************************************************************************************
* Function Drv_SDCardResponseIsCorrect
* @brief �ж���Ӧ�Ƿ���ȷ
* @param uint8_t resp����������Ӧ����
* @param void
* @returns uint8_t���жϽ��
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

uint8_t Drv_SDCardResponseIsCorrect(uint8_t resp)
{
	uint16_t waitCnt = 0xFFFFu;
	uint8_t rxDat = 0;

	do {
		(void)D_SD_CARD_WR_BYTE_FUNC(0xFF, &rxDat);
		waitCnt--;
	}while ((rxDat != resp) && (waitCnt != 0));

	if (waitCnt == 0)
	{
		return D_SD_MSD_RESPONSE_FAIL;
	}
	else
	{
		return D_SD_MSD_RESPONSE_NORMAL;
	}
}

/*!
************************************************************************************************************************
* Function Drv_SDCardRevDat
* @brief ����sd������
* @param uint8_t *pBuf����������ָ��
* @param uint16_t len���������ݳ���
* @returns sdCardErr_t��sd�������
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

SdCardErr_t Drv_SDCardRevDat(uint8_t *pBuf, uint16_t len)
{
	uint16_t i = 0;
	uint8_t tmp = 0;

	if (pBuf == NULL)
	{
		return EN_SD_ERR_OTHER;
	}
	
	if (Drv_SDCardResponseIsCorrect(D_SD_CARD_DATA_START_TOKEN) != D_SD_MSD_RESPONSE_NORMAL)
	{
		return EN_SD_ERR_RESPONSE_FAIL;
	}

	for (i = 0; i < len; i++)
	{
		(void)D_SD_CARD_WR_BYTE_FUNC(0xFF, pBuf);
		pBuf++;
	}

	/* Dummy CRC */
	(void)D_SD_CARD_WR_BYTE_FUNC(0xFF, &tmp);
	(void)D_SD_CARD_WR_BYTE_FUNC(0xFF, &tmp);

	return EN_SD_OPT_OK;
}

/*!
************************************************************************************************************************
* Function Drv_SDCardSendBlock
* @brief sd���������ݿ�
* @param const uint8_t pBuf[]�����ݻ���
* @param uint8_t cmd������
* @returns sdCardErr_t��sd��״̬
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

SdCardErr_t Drv_SDCardSendBlock(const uint8_t pBuf[], uint8_t cmd)
{
	uint16_t i = 0;
	uint8_t tmp = 0;

	if (pBuf == NULL)
	{
		return EN_SD_ERR_OTHER;
	}

	if (Drv_SDCardWaitReady() != EN_SD_OPT_OK)
	{
		return EN_SD_ERR_TIMEOUT;
	}

	(void)D_SD_CARD_WR_BYTE_FUNC(cmd, &tmp);
	if (cmd != D_SD_CARD_DATA_END_CMD)
	{
		for (i = 0; i < D_SD_CARD_BLOCK_SIZE; i++)
		{
			(void)D_SD_CARD_WR_BYTE_FUNC(pBuf[i], &tmp);
		}
		/* Dummy CRC */
		(void)D_SD_CARD_WR_BYTE_FUNC(0xFF, &tmp);
		(void)D_SD_CARD_WR_BYTE_FUNC(0xFF, &tmp);
		/* receiver response */
		(void)D_SD_CARD_WR_BYTE_FUNC(0xFF, &tmp);
		if ((tmp & 0x1FU) != D_SD_MSD_DATA_OK)
		{
			return EN_SD_ERR_RESPONSE_FAIL;
		}
	}

	return EN_SD_OPT_OK;
}

/*!
************************************************************************************************************************
* Function Drv_SDCardSendCmd
* @brief ��������
* @param uint8_t cmd��sd������
* @param uint32_t arg������
* @param uint8_t crc��У��
* @returns uint8_t�����ͽ��
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

uint8_t Drv_SDCardSendCmd(uint8_t cmd, uint32_t arg, uint8_t crc)
{
	uint8_t reg = 0;
	uint8_t waitCnt = 0;

	Drv_SDCardCanelSelect();
	if (Drv_SDCardSelect() != EN_SD_OPT_OK)
	{
		return (uint8_t)EN_SD_ERR_TIMEOUT;
	}

	(void)D_SD_CARD_WR_BYTE_FUNC((cmd | 0x40U), &reg);
	(void)D_SD_CARD_WR_BYTE_FUNC((uint8_t)(arg >> 24U), &reg);
	(void)D_SD_CARD_WR_BYTE_FUNC((uint8_t)(arg >> 16U), &reg);
	(void)D_SD_CARD_WR_BYTE_FUNC((uint8_t)(arg >> 8U), &reg);
	(void)D_SD_CARD_WR_BYTE_FUNC((uint8_t)(arg), &reg);
	(void)D_SD_CARD_WR_BYTE_FUNC(crc, &reg);
	if (cmd == D_SD_CMD12_STOP_TRANS)
	{
		(void)D_SD_CARD_WR_BYTE_FUNC(0xFF, &reg);//Skip a stuff byte when stop reading
	}

	waitCnt = 0x1F;
	do {
		(void)D_SD_CARD_WR_BYTE_FUNC(0xFF, &reg);
		waitCnt--;
	}while ( ((reg & 0x80U) != 0U) && (waitCnt != 0U) );

	return reg;
}




