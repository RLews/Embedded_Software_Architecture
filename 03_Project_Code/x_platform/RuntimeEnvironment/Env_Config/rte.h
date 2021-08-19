/*!
************************************************************************************************************************
* @file rte.h
* @brief 运行环境头文件
* @details
* @author Lews Hammond
* @date 2021-8-14
************************************************************************************************************************
*/

#ifndef RTE_H
#define RTE_H

#include "rte_config.h"


#ifdef __cplusplus
extern "C" {
#endif

#include "rte_bsw_srv_if.h"

/*! @brief rtos runtime header files */
#if (D_RTE_PLATFORM_CONFIG == D_RTE_PLATFORM_MCU)

#include "rte_bsw_hal_if.h"
#include "rte_bsw_rtos_if.h"

#endif

#if (D_RTE_OS_CONFIG == D_RTE_OS_LINUX)

#include "rte_linux_if.h"

#endif




#ifdef __cplusplus
}
#endif


#endif

