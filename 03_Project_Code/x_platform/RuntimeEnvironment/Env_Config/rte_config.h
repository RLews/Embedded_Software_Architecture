/*!
************************************************************************************************************************
* @file rte_config.h
* @brief ���л�������
* @details
* @author Lews Hammond
* @date 2021-8-14
************************************************************************************************************************
*/

#ifndef RTE_CONFIG_H
#define RTE_CONFIG_H

/*! @brief ϵͳ���� */
#define D_OS_UC_RTOS            0U
#define D_OS_LINUX              1U
#define D_RTE_OS_CONFIG         D_OS_UC_RTOS

#include "rte_bsw_srv_if.h"

/*! @brief rtos runtime header files */
#if (D_RTE_OS_CONFIG == D_OS_UC_RTOS)

#include "rte_bsw_hal_if.h"

#endif

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif


#endif

