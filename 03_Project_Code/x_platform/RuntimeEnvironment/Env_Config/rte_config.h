/*!
************************************************************************************************************************
* @file rte_config.h
* @brief 运行环境配置
* @details
* @author Lews Hammond
* @date 2021-8-14
************************************************************************************************************************
*/

#ifndef RTE_CONFIG_H
#define RTE_CONFIG_H


/*! @brief 硬件平台类型 */
#define D_RTE_PLATFORM_MCU      0x0000U /*!< MCU平台，配置RTOS */
#define D_RTE_PLATFORM_SOC      0x0001U /*!< Soc平台，配置Linux */

#define D_RTE_PLATFORM_CONFIG   D_RTE_PLATFORM_SOC

/*! @brief 操作系统类型 */
#define D_RTE_OS_UC_III_RTOS    0x0000U /*!< μC/OS III + FatFs  */
#define D_RTE_OS_LINUX          0x0001U /*!< Linux */

#define D_RTE_OS_CONFIG         D_RTE_OS_LINUX



#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif


#endif

