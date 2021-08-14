/*!
************************************************************************************************************************
* @file drv_sd_pub.h
* @brief 
* @details 
* @author Lews Hammond
* @date 2021-8-14
************************************************************************************************************************
*/

#ifndef DRV_SD_PUB_H
#define DRV_SD_PUB_H

#include "platforms.h"
#include "drv_spi_pub.h"

/*
************************************************************************************************************************
* SD Card Interface
************************************************************************************************************************
*/
typedef enum SD_CARD_ERR_T

{
	EN_SD_OPT_OK = 0,
	EN_SD_ERR_TIMEOUT,
	EN_SD_ERR_RESPONSE_FAIL,
	EN_SD_ERR_OTHER,
	EN_SD_OPT_ERR_ALL_TYPE
}SdCardErr_t;

/* sd card command */
#define D_SD_CMD0_RESET					0
#define D_SD_CMD1						1
#define D_SD_CMD8_TX_IF_COND			8
#define D_SD_CMD9_READ_CSD				9
#define D_SD_CMD10_READ_CID				10
#define D_SD_CMD12_STOP_TRANS			12
#define D_SD_CMD16_SECTOR_SIZE			16
#define D_SD_CMD17_READ_SECTOR			17
#define D_SD_CMD18_READ_MULT_SECTOR		18
#define D_SD_CMD23_ERASE_BLOCK			23
#define D_SD_CMD24_WRITE_SECTOR			24
#define D_SD_CMD25_WRITE_MULT_SECTOR	25
#define D_SD_CMD41						41
#define D_SD_CMD55						55
#define D_SD_CMD58_READ_OCR				58
#define D_SD_CMD59_CRC_CTRL				59

/* sd card response identifer define */
#define D_SD_MSD_RESPONSE_NORMAL		0x00
#define D_SD_MSD_IN_IDLE_STATUS			0x01
#define D_SD_MSD_ERASE_RESET			0x02
#define D_SD_MSD_ILLEGAL_COMMAND		0x04
#define D_SD_MSD_CRC_ERR				0x08
#define D_SD_MSD_ERASE_SEQUENCE_ERR		0x10
#define D_SD_MSD_ADDRESS_ERR			0x20
#define D_SD_MSD_PARAMETER_ERR			0x40
#define D_SD_MSD_RESPONSE_FAIL			0xFF

#define D_SD_CARD_HIGH_SPEED			SPI_BaudRatePrescaler_2
#define D_SD_CARD_LOW_SPEED				SPI_BaudRatePrescaler_256

#define D_SET_SD_CARD_HIGH_SPD_MODE()	Drv_Spi2SetSpeed(D_SD_CARD_HIGH_SPEED)
#define D_SET_SD_CARD_LOW_SPD_MODE()	Drv_Spi2SetSpeed(D_SD_CARD_LOW_SPEED)
#define D_SD_CARD_WR_BYTE_FUNC(tx, rx)	Drv_Spi2RWByte(tx, rx)

#define D_SD_CARD_SPI_CS_SELECT()		Drv_GpioNameOut(EN_SD_CARD_CS, EN_GPIO_LOW)
#define D_SD_CARD_SPI_CS_CANCEL()		Drv_GpioNameOut(EN_SD_CARD_CS, EN_GPIO_HIGH)

void Drv_SDCardSpiInit(void);
void Drv_SDCardCanelSelect(void);
SdCardErr_t Drv_SDCardSelect(void);
uint8_t Drv_SDCardResponseIsCorrect(uint8_t resp);
SdCardErr_t Drv_SDCardRevDat(uint8_t *pBuf, uint16_t len);
SdCardErr_t Drv_SDCardSendBlock(const uint8_t pBuf[], uint8_t cmd);
uint8_t Drv_SDCardSendCmd(uint8_t cmd, uint32_t arg, uint8_t crc);
SdCardErr_t Drv_SDCardWaitReady(void);




#endif

