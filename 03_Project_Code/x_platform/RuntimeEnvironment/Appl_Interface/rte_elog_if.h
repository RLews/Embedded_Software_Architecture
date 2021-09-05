/*!
************************************************************************************************************************
* @file rte_elog_if.h
* @brief elog runtime interface
* @details 
* @author Lews Hammond
* @date 2021-9-2
************************************************************************************************************************
*/

#ifndef RTE_ELOG_IF_H
#define RTE_ELOG_IF_H


#ifdef __cplusplus
extern "C" {
#endif

#include "elog.h"
#include "elog_level_ctrl.h"
#include "elog_if.h"


#define RTE_LOG_A(...)      ELOG_A(__VA_ARGS__)
#define RTE_LOG_E(...)      ELOG_E(__VA_ARGS__)
#define RTE_LOG_W(...)      ELOG_W(__VA_ARGS__)
#define RTE_LOG_I(...)      ELOG_I(__VA_ARGS__)
#define RTE_LOG_D(...)      ELOG_D(__VA_ARGS__)
#define RTE_LOG_V(...)      ELOG_V(__VA_ARGS__)

#define RTE_ELOG_INIT()             Elog_Init()
#define RTE_ELOG_GET_LEVEL()        Elog_GetLevel()
#define RTE_ELOG_SET_LEVEL(lvl)     Elog_SetLevel(lvl)

#ifdef __cplusplus
}
#endif


#endif

