/*!
************************************************************************************************************************
* @file drv_sd.h
* @details 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/



#ifndef DRV_SD_H
#define DRV_SD_H

#include "drv_sd_pub.h"
#include "drv_gpio_pub.h"



#define D_SD_CARD_BLOCK_SIZE			512U

#define D_SD_CARD_DATA_START_TOKEN		0xFEu
#define D_SD_CARD_DATA_END_CMD			0xFDu


/* data write response define */
#define D_SD_MSD_DATA_OK				0x05U
#define D_SD_MSD_DATA_CRC_ERR			0x0BU
#define D_SD_MSD_DATA_WRITE_ERR			0x0DU
#define D_SD_MSD_DATA_OTHER_ERR			0xFFU


#endif

