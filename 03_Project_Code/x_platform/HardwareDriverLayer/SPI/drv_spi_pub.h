/*!
************************************************************************************************************************
* @file drv_spi_pub.h
* @brief
* @details
* @author Lews Hammond
* @date 2021-8-14
************************************************************************************************************************
*/

#ifndef DRV_SPI_PUB_H
#define DRV_SPI_PUB_H

#include "platforms.h"


/*
************************************************************************************************************************
* SPI Interface
************************************************************************************************************************
*/
typedef enum SPI_NAME_T
{
    EN_SD_CARD_CH = 0,
    EN_ALL_SPI_NUM
} SpiName_t;

typedef enum SPI_ERROR_T
{
    EN_OPERATION_SPI_OK = 0,
    EN_OPERATION_SPI_BUSY,
    EN_OPERATION_SPI_TIMEOUT,
    EN_OPERATION_SPI_ALL_STA
} SpiError_t;

void Drv_SpiInit(void);
StdBoolean_t Drv_GetSpiInitSta(void);
SpiError_t Drv_Spi2RWByte(const uint8_t txDat, uint8_t * rxDat);
void Drv_Spi2SetSpeed(uint8_t baudRatePre);


#endif

