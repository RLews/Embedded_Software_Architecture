/*!
************************************************************************************************************************
* @file hal_sd_pub.h
* @brief 
* @details 
* @author Lews Hammond
* @date 2021-8-14
************************************************************************************************************************
*/

#ifndef HAL_SD_PUB_H
#define HAL_SD_PUB_H

#include "drv_sd_pub.h"

/*
************************************************************************************************************************
* SD Card  Interface
************************************************************************************************************************
*/
SdCardErr_t Hal_SDCardGetCID(uint8_t *pCID);
SdCardErr_t Hal_SDCardGetCSD(uint8_t *pCSD);
SdCardErr_t Hal_SDCardGetSectorNum(uint32_t *pSectorNum);
SdCardErr_t Hal_SDCardReadDisk(uint8_t *pBuf, uint32_t sector, uint8_t cnt);
SdCardErr_t Hal_SDCardWriteDisk(const uint8_t *pBuf, uint32_t sector, uint8_t cnt);
SdCardErr_t Hal_SDCardInit(void);




#endif

