/*!
************************************************************************************************************************
* @file rte_bsw_hal_if.h
* @brief 
* @details 
* @author Lews Hammond
* @date 2021-8-14
************************************************************************************************************************
*/

#ifndef RTE_BSW_HAL_IF_H
#define RTE_BSW_HAL_IF_H



#ifdef __cplusplus
extern "C" {
#endif

/* TODO: 使用脚本获取pub模块接口，枚举等信息，导入宏替换规则 */

#include "hal.h"
#include "osal.h"


/*! @brief 交互接口使用宏替换 */
#define RTE_HAL_SYSINIT()						Hal_SysInit()

#define RTE_OSAL_OSINIT()						Osal_OsInit()

#define RTE_D_OSAL_ENTER_CRITICAL()				D_OSAL_ENTER_CRITICAL()

#define RTE_D_OSAL_EXIT_CRITICAL()				D_OSAL_EXIT_CRITICAL()
/* ...... */

#ifdef __cplusplus
}
#endif



#endif

