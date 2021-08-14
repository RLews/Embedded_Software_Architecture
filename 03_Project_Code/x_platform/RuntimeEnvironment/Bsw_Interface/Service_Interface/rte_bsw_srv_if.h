/*!
************************************************************************************************************************
* @file rte_bsw_srv_if.h
* @brief 基础服务接口
* @details 
* @author Lews Hammond
* @date 2021-8-14
************************************************************************************************************************
*/

#ifndef RTE_BSW_SRV_IF_H
#define RTE_BSW_SRV_IF_H


#ifdef __cplusplus
extern "C" {
#endif

#include "srv_memory.h"
#include "std_lib.h"
#include "srv_algor.h"

/* TODO: 使用脚本获取pub模块接口，枚举等信息，导入宏替换规则 */

/*! @brief 交互接口使用宏替换 */
#define RTE_SRV_GETRAND16()				Srv_GetRand16()

/* ...... */

#ifdef __cplusplus
}
#endif


#endif

