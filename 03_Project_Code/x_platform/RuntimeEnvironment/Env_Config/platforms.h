/*!
************************************************************************************************************************
* @file platforms.h
* @details ƽ̨ͨ�ö������������
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

#include "rte_config.h"

#if defined(D_RTE_PLATFORM_MCU)

#include "stm32f10x.h"

#endif

#if defined(D_RTE_PLATFORM_SOC)

#include <stdint.h>

typedef int32_t s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  /*!< Read Only */
typedef const int16_t sc16;  /*!< Read Only */
typedef const int8_t sc8;   /*!< Read Only */

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  /*!< Read Only */
typedef const uint16_t uc16;  /*!< Read Only */
typedef const uint8_t uc8;   /*!< Read Only */


#endif

/*! @brief �������Ͷ��� */
typedef uint8_t StdBoolean_t;

#define D_STD_FALSE         (0U)
#define D_STD_TRUE          (1U)

#define D_STD_OFF           (0U)
#define D_STD_ON            (1U)
#define D_STD_ENABLE        (1U)
#define D_STD_DISABLE       (0U)

#ifndef NULL
#define NULL        ((void *)0x00000000UL)
#endif

#define ArrayLength(Array) (sizeof(Array) / sizeof(Array[0]))


/*! @brief ���������� */
#define EXTERN_SRAM_ENABLE              D_STD_DISABLE   /*!< �ⲿSRAM���� */
#define D_SYS_WDG_ENABLE                D_STD_ON        /*!< ���Ź����� */



#endif

