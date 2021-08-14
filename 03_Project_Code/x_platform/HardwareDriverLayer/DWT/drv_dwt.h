/*!
************************************************************************************************************************
* @file drv_dwt.h
* @details
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/



#ifndef DRV_DWT_H
#define DRV_DWT_H

#include "drv_dwt_pub.h"

#define  DWT_CR      *(__IO uint32_t *)0xE0001000
#define  DWT_CYCCNT  *(__IO uint32_t *)0xE0001004
#define  DEM_CR      *(__IO uint32_t *)0xE000EDFC


#define  DEM_CR_TRCENA                   (1 << 24)
#define  DWT_CR_CYCCNTENA                (1 <<  0)



#endif
