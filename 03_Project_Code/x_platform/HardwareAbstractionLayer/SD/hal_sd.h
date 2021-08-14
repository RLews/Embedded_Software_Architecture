/*!
************************************************************************************************************************
* @file hal_sd.h
* @details
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/


#ifndef HAL_SD_H
#define HAL_SD_H

#include "hal_sd_pub.h"

/* sd card type */
#define D_SD_TYPE_ERR                   0x00U
#define D_SD_TYPE_MMC                   0x01U
#define D_SD_TYPE_V1                    0x02U
#define D_SD_TYPE_V2                    0x04U
#define D_SD_TYPE_V2HC                  0x06U



#define D_SD_CARD_SECTOR_SIZE           512U
#define D_SD_CARD_CID_SIZE              16U
#define D_SD_CARD_CSD_SIZE              16U



#endif

