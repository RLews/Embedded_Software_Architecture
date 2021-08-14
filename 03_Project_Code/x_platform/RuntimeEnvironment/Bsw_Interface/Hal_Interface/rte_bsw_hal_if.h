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

/* TODO: ʹ�ýű���ȡpubģ��ӿڣ�ö�ٵ���Ϣ��������滻���� */

#include "hal.h"
#include "osal.h"


/*! @brief �����ӿ�ʹ�ú��滻 */
#define RTE_HAL_SYSINIT()						Hal_SysInit()

#define RTE_OSAL_OSINIT()						Osal_OsInit()

#define RTE_D_OSAL_ENTER_CRITICAL()				D_OSAL_ENTER_CRITICAL()

#define RTE_D_OSAL_EXIT_CRITICAL()				D_OSAL_EXIT_CRITICAL()
/* ...... */

#ifdef __cplusplus
}
#endif



#endif

