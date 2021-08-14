/*!
************************************************************************************************************************
* @file platforms.h
* @details 平台通用定义和驱动配置
* @author Lews Hammond
* @date 2019-7-18
************************************************************************************************************************
*/



#ifndef PLATFORMS_H
#define PLATFORMS_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#include "stm32f10x.h"

/*! @brief 布尔类型定义 */
typedef uint8_t StdBoolean_t;

#define D_STD_FALSE			(0U)
#define D_STD_TRUE			(1U)

#define D_STD_OFF			(0U)
#define D_STD_ON			(1U)
#define D_STD_ENABLE		(1U)
#define D_STD_DISABLE		(0U)

#ifndef NULL
    #define NULL        ((void *)0x00000000UL)
#endif

/*! @brief 驱动配置项 */
#define EXTERN_SRAM_ENABLE				D_STD_DISABLE 	/*!< 外部SRAM配置 */
#define D_SYS_WDG_ENABLE				D_STD_ON		/*!< 看门狗配置 */



#endif

