/*!
************************************************************************************************************************
* @file hal_sd.c
* @details 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

#include "hal_sd.h"


static uint8_t SdCardType = D_SD_TYPE_ERR;

static void Hal_SDCardInitPulse(void);
static uint8_t Hal_SDCardIntoIDLE(void);
static SdCardErr_t Hal_SDCardReadOCR(uint8_t *pBuf);


/*!
************************************************************************************************************************
* Function Hal_SDCardGetCID
* @brief read cid
* @param uint8_t *pCID
* @param void
* @returns sdCardErr_t：sd卡操作结果
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

SdCardErr_t Hal_SDCardGetCID(uint8_t *pCID)
{
	uint8_t revDat = 0;
	SdCardErr_t optRes = EN_SD_OPT_OK;

	revDat = Drv_SDCardSendCmd(D_SD_CMD10_READ_CID, 0, 0x01);
	if (revDat == D_SD_MSD_RESPONSE_NORMAL)
	{
		optRes = Drv_SDCardRevDat(pCID, D_SD_CARD_CID_SIZE);
	}
	Drv_SDCardCanelSelect();

	return optRes;
}


/*!
************************************************************************************************************************
* Function Hal_SDCardGetCSD
* @brief read csd
* @param uint8_t *pCSD
* @param void
* @returns SdCardErr_t
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

SdCardErr_t Hal_SDCardGetCSD(uint8_t *pCSD)
{
	uint8_t revDat = 0;
	SdCardErr_t optRes = EN_SD_OPT_OK;

	revDat = Drv_SDCardSendCmd(D_SD_CMD9_READ_CSD, 0, 0x01);
	if (revDat == D_SD_MSD_RESPONSE_NORMAL)
	{
		optRes = Drv_SDCardRevDat(pCSD, D_SD_CARD_CSD_SIZE);
	}
	else
	{
		optRes = EN_SD_ERR_RESPONSE_FAIL;
	}
	Drv_SDCardCanelSelect();

	return optRes;
}


/*!
************************************************************************************************************************
* Function Hal_SDCardGetSectorNum
* @brief 读取sd卡扇区数
* @param uint32_t *pSectorNum
* @param void
* @returns SdCardErr_t
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

SdCardErr_t Hal_SDCardGetSectorNum(uint32_t *pSectorNum)
{
	uint8_t csd[D_SD_CARD_CSD_SIZE] = {0};
	uint8_t n = 0;
	uint16_t cSize = 0;
	SdCardErr_t optErr = EN_SD_OPT_OK;
	
	if (pSectorNum == NULL)
	{
		return optErr;
	}

	optErr = Hal_SDCardGetCSD(csd);
	if (optErr != EN_SD_OPT_OK)
	{
		return optErr;
	}

	if ( (csd[0] & 0xC0U) == 0x40U )//SDHC V2.x
	{
		cSize = csd[9] + ((uint16_t)csd[8] << 8U) + 1;
		*pSectorNum = (uint32_t)cSize << 10U;
	}
	else //V1.xx
	{
		n = (csd[5] & 0x0FU) + ((csd[10] & 0x80U) >> 7U) + ((csd[9] & 0x03U) << 1U) + 2U;
		cSize = (uint16_t)(csd[8] >> 6U) + ((uint16_t)csd[7] << 2U) + ((uint16_t)(csd[6] & 0x03U) << 10U) + 1U;
		*pSectorNum = (uint32_t)cSize << (n - 9U);
	}

	return optErr;
}



/*!
************************************************************************************************************************
* Function Hal_SDCardReadDisk
* @brief read disk
* @param uint8_t *pBuf：读取指针
* @param uint32_t sector：扇区
* @param uint8_t cnt：
* @returns SdCardErr_t
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

SdCardErr_t Hal_SDCardReadDisk(uint8_t *pBuf, uint32_t sector, uint8_t cnt)
{
	SdCardErr_t optRes = EN_SD_OPT_OK;

	if (pBuf == NULL)
	{
		return EN_SD_ERR_OTHER;
	}

	if (SdCardType != D_SD_TYPE_V2HC)
	{
		sector <<= 9;//convert byte address
	}

	if (cnt == 1)
	{
		optRes = (SdCardErr_t)Drv_SDCardSendCmd(D_SD_CMD17_READ_SECTOR, sector, 0x01);
		if (optRes == EN_SD_OPT_OK)
		{
			optRes = Drv_SDCardRevDat(pBuf, D_SD_CARD_SECTOR_SIZE);
		}
	}
	else
	{
		optRes = (SdCardErr_t)Drv_SDCardSendCmd(D_SD_CMD18_READ_MULT_SECTOR, sector, 0x01);
		do {
			optRes = Drv_SDCardRevDat(pBuf, D_SD_CARD_SECTOR_SIZE);
			pBuf += D_SD_CARD_SECTOR_SIZE;
			cnt--;
		}while ( (cnt != 0) && (optRes == EN_SD_OPT_OK) );
		(void)Drv_SDCardSendCmd(D_SD_CMD12_STOP_TRANS, 0, 0x01);
	}

	Drv_SDCardCanelSelect();

	return optRes;
}


/*!
************************************************************************************************************************
* Function Hal_SDCardWriteDisk
* @brief write disk
* @param const uint8_t *pBuf
* @param uint32_t sector
* @param uint8_t cnt
* @returns SdCardErr_t
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

SdCardErr_t Hal_SDCardWriteDisk(const uint8_t *pBuf, uint32_t sector, uint8_t cnt)
{
	SdCardErr_t optRes = EN_SD_OPT_OK;
	uint8_t i = 0;

	if (pBuf == NULL)
	{
		return EN_SD_ERR_OTHER;
	}

	if (SdCardType != D_SD_TYPE_V2HC)
	{
		sector <<= 9;//convert byte address
	}

	if (cnt == 1)
	{
		optRes = (SdCardErr_t)Drv_SDCardSendCmd(D_SD_CMD24_WRITE_SECTOR, sector, 0x01);
		if (optRes == EN_SD_OPT_OK)
		{
			optRes = Drv_SDCardSendBlock(pBuf, 0xFE);
		}
	}
	else
	{
		if (SdCardType != D_SD_TYPE_MMC)
		{
			optRes = (SdCardErr_t)Drv_SDCardSendCmd(D_SD_CMD55, 0, 0x01);
			optRes = (SdCardErr_t)Drv_SDCardSendCmd(D_SD_CMD23_ERASE_BLOCK, cnt, 0x01);
		}
		optRes = (SdCardErr_t)Drv_SDCardSendCmd(D_SD_CMD25_WRITE_MULT_SECTOR, sector, 0x01);
		if (optRes == EN_SD_OPT_OK)
		{
			for (i = 0; i < cnt; i++)
			{
				optRes = Drv_SDCardSendBlock(pBuf, 0xFC);
				pBuf += D_SD_CARD_SECTOR_SIZE;
				if (optRes != EN_SD_OPT_OK)
				{
					break;
				}
			}

			optRes = Drv_SDCardSendBlock((uint8_t *)0, 0xFD);
		}
	}
	Drv_SDCardCanelSelect();

	return optRes;
}


/*!
************************************************************************************************************************
* Function Hal_SDCardInitPulse
* @brief transmit 74 pulse
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static void Hal_SDCardInitPulse(void)
{
	uint8_t i = 0;
	uint8_t rev = 0;
	
	for (i = 0; i < 10; i++)
	{/* transmit 74 pulse */
		(void)D_SD_CARD_WR_BYTE_FUNC(0xFF, &rev);
	}
}


/*!
************************************************************************************************************************
* Function Hal_SDCardIntoIDLE
* @brief goto idle mode
* @param void
* @param void
* @returns uint8_t：
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static uint8_t Hal_SDCardIntoIDLE(void)
{
	uint8_t timeCnt = 20;
	uint8_t rev = 0;

	do {
		rev = Drv_SDCardSendCmd(D_SD_CMD0_RESET, 0, 0x95);
		timeCnt--;
	}while ( (timeCnt != 0) && (rev != D_SD_MSD_IN_IDLE_STATUS) );

	return rev;
}


/*!
************************************************************************************************************************
* Function Hal_SDCardReadOCR
* @brief read ocr
* @param uint8_t *pBuf
* @param void
* @returns SdCardErr_t
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static SdCardErr_t Hal_SDCardReadOCR(uint8_t *pBuf)
{
	uint8_t i = 0;
	
	if (Drv_SDCardSendCmd(D_SD_CMD58_READ_OCR, 0, 0x01) == D_SD_MSD_RESPONSE_NORMAL)
	{
		for (i = 0; i < 4; i++)
		{
			(void)D_SD_CARD_WR_BYTE_FUNC(0xFF, pBuf);
			pBuf++;
		}

		return EN_SD_OPT_OK;
	}
	else
	{
		return EN_SD_ERR_RESPONSE_FAIL;
	}
}


/*!
************************************************************************************************************************
* Function Hal_SDCardInit
* @brief sd card initial
* @param void
* @param void
* @returns SdCardErr_t
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

SdCardErr_t Hal_SDCardInit(void) 
{
	uint8_t rev = 0;
	uint16_t timeCnt = 0;
	uint8_t buf[4] = {0};
	uint8_t i = 0;
	
	Drv_SDCardSpiInit();
	D_SET_SD_CARD_LOW_SPD_MODE();
	Hal_SDCardInitPulse();
	
	if (Hal_SDCardIntoIDLE() == D_SD_MSD_IN_IDLE_STATUS)
	{
		if (Drv_SDCardSendCmd(D_SD_CMD8_TX_IF_COND, 0x1AA, 0x87) == 1)//SD v2.0
		{
			for (i = 0; i < 4; i++)
			{
				(void)D_SD_CARD_WR_BYTE_FUNC(0xFF, &buf[i]);//Get trailing return value of R7 resp
			}
			if ( (buf[2] == 0x01U) && (buf[3] == 0xAAU) )/* 2.7 - 3.6v */
			{
				timeCnt = 0xFFFE;
				do {
					rev = Drv_SDCardSendCmd(D_SD_CMD55, 0, 0x01);
					rev = Drv_SDCardSendCmd(D_SD_CMD41, 0x40000000, 0x01);
					timeCnt--;
				}while ( (rev != 0) && (timeCnt != 0) );

				if ( (Hal_SDCardReadOCR(buf) == EN_SD_OPT_OK) && (timeCnt != 0) )
				{
					if (0 != (buf[0] & 0x40U))
					{
						SdCardType = D_SD_TYPE_V2HC;
					}
					else
					{
						SdCardType = D_SD_TYPE_V2;
					}
				}
			}
		}
		else/* SD v1.x / MMC */
		{
			rev = Drv_SDCardSendCmd(D_SD_CMD55, 0, 0x01);
			rev = Drv_SDCardSendCmd(D_SD_CMD41, 0, 0x01);
			if (rev <= 1)
			{
				SdCardType = D_SD_TYPE_V1;
				timeCnt = 0xFFFE;
				do {
					rev = Drv_SDCardSendCmd(D_SD_CMD55, 0, 0x01);
					rev = Drv_SDCardSendCmd(D_SD_CMD41, 0, 0x01);
					timeCnt--;
				}while ( (timeCnt != 0) && (rev != D_SD_MSD_RESPONSE_NORMAL) );
			}
			else
			{
				SdCardType = D_SD_TYPE_MMC;
				timeCnt = 0xFFFE;
				do {
					rev = Drv_SDCardSendCmd(D_SD_CMD1, 0, 0x01);
				}while ( (timeCnt != 0) && (rev != D_SD_MSD_RESPONSE_NORMAL) );
			}
			if ((Drv_SDCardSendCmd(D_SD_CMD16_SECTOR_SIZE, D_SD_CARD_SECTOR_SIZE, 0x01) != 0) || (timeCnt == 0))
			{
				SdCardType = D_SD_TYPE_ERR;
			}
		}
	}

	Drv_SDCardCanelSelect();
	D_SET_SD_CARD_HIGH_SPD_MODE();

	if (SdCardType != D_SD_TYPE_ERR)
	{
		return EN_SD_OPT_OK;
	}
	else if (rev != 0)
	{
		return (SdCardErr_t)rev;
	}
	else
	{
		return EN_SD_ERR_OTHER;
	}
}


