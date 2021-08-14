/*!
************************************************************************************************************************
* @file hal_key.h
* @details
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/


#ifndef HAL_KEY_H
#define HAL_KEY_H

#include "hal_key_pub.h"
#include "osal.h"

#define D_ENABLE_KEY_DOUBLE_PRESS       D_STD_ON

#define D_KEY_SCAN_PEROID_MS            5

#define D_KEY_DOUBLE_PRESS_TIME         (150*1000ul)
#define D_KEY_DOUBLE_PRESS_SPACE_TIME   (2000*1000ul)
#define D_KEY_REPEAT_TIME               (1000*1000ul)//1s

#define D_KEY_PRESS_SHAKE_TIME          (15/D_KEY_SCAN_PEROID_MS) //15ms


typedef struct KEY_SHAKE_T
{
    uint8_t shakeBuf[EN_KEY_ALL_TYPE];
    uint32_t keyPrsTim[EN_KEY_ALL_TYPE];
    uint32_t keydblPrsTim[EN_KEY_ALL_TYPE];
    StdBoolean_t dblKeyLock[EN_KEY_ALL_TYPE];
} KeyShake_t;

#endif


