/*!
************************************************************************************************************************
* @file rte_bsw_rtos_if.h
* @brief rtos file system...
* @details 
* @author Lews Hammond
* @date 2021-8-16
************************************************************************************************************************
*/

#ifndef RTE_BSW_RTOS_IF_H
#define RTE_BSW_RTOS_IF_H


#ifdef __cplusplus
extern "C" {
#endif

/* TODO: 使用脚本获取pub模块接口，枚举等信息，导入宏替换规则 */

#include "osal.h"


#define RTE_OSAL_OSINIT()                       Osal_OsInit()

#define RTE_D_OSAL_ENTER_CRITICAL()             D_OSAL_ENTER_CRITICAL()

#define RTE_D_OSAL_EXIT_CRITICAL()              D_OSAL_EXIT_CRITICAL()

/* ...... */

#ifdef __cplusplus
}
#endif


#endif

