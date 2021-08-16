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

#include "rte_bsw_srv_if.h"

/*! @brief Ӳ��ƽ̨���� */
#define D_RTE_PLATFORM_MCU      0x0000U /*!< MCUƽ̨������RTOS */
#define D_RTE_PLATFORM_SOC      0x0001U /*!< Socƽ̨������Linux */

#define D_RTE_PLATFORM_CONFIG   D_RTE_PLATFORM_MCU

/*! @brief ����ϵͳ���� */
#define D_RTE_OS_UC_III_RTOS    0x0000U /*!< ��C/OS III + FatFs  */
#define D_RTE_OS_LINUX          0x0001U /*!< Linux */

#define D_RTE_OS_CONFIG         D_RTE_OS_UC_RTOS


/*! @brief rtos runtime header files */
#if (D_RTE_PLATFORM_CONFIG == D_RTE_PLATFORM_MCU)

#include "rte_bsw_hal_if.h"
#include "rte_bsw_rtos_if.h"

#endif

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif


#endif

