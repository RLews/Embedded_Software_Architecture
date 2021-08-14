/*!
************************************************************************************************************************
* @file drv_spi.h
* @details
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/



#ifndef DRV_SPI_H
#define DRV_SPI_H


#include "drv_spi_pub.h"

#define D_SD_CARD_CRC_CONFIG            (7u)

#define D_SPI2_TIMEOUT_LIMIT_VAL        (300u)

typedef struct SPI_CONFIG_T
{
    SpiName_t spiName;
    SPI_TypeDef * spiDef;
    uint16_t spiDir;
    uint16_t spiMode;
    uint16_t spiDataSize;
    uint16_t spiCpol;/* Bus Idle clock wire is high or low */
    uint16_t spiCpha;/* Bus data capture is first edge or second edge */
    uint16_t spiNss;/* nss pin is hardware control or software control */
    uint16_t spiBaudRatePer;/* STM32F10x SPI BaudRate Max:18MHz. SPI BaudRate(MHz) = 36MHz / Per */
    uint16_t spiFirstBits;/* First Transmit MSB or LSB */
    uint16_t spiCrc;
    uint32_t spiRcc;
} SpiConfig_t;


#define D_SPI_CONFIG_ARRAY      \
    {EN_SD_CARD_CH, SPI2, SPI_Direction_2Lines_FullDuplex, SPI_Mode_Master, SPI_DataSize_8b, SPI_CPOL_High, SPI_CPHA_2Edge, \
     SPI_NSS_Soft, SPI_BaudRatePrescaler_256, SPI_FirstBit_MSB, D_SD_CARD_CRC_CONFIG, RCC_APB1Periph_SPI2}



#endif

