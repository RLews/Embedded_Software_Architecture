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


#include "stm32f10x.h"

/*! @brief �������Ͷ��� */
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

/*! @brief ���������� */
#define EXTERN_SRAM_ENABLE				D_STD_DISABLE 	/*!< �ⲿSRAM���� */
#define D_SYS_WDG_ENABLE				D_STD_ON		/*!< ���Ź����� */



#endif

