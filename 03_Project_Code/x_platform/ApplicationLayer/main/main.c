/*!
************************************************************************************************************************
* @file main.c
* @brief Ӧ�����
* @details ����ܹ�demo
* @author Lews Hammond
* @date 2021-8-14
************************************************************************************************************************
*/

#include "main.h"

/*!
************************************************************************************************************************
* @brief Ӧ�ó������
* @param[in] void
* @param[out] void
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-8-14
************************************************************************************************************************
*/

int main(void)
{
#if defined(D_RTE_PLATFORM_MCU)
    RTE_HAL_SYSINIT();
    RTE_OSAL_OSINIT();
#endif

#if defined(D_RTE_PLATFORM_SOC)
    RTE_ELOG_INIT();
#endif


    while(1)
    {
        /* do nothing */
#if defined(D_RTE_PLATFORM_SOC)
        RTE_LOG_I("x platform demo running...\n");
        RTE_LOG_I("version: %s\n", D_SOFTWARE_VER);
        RTE_OSAL_SLEEP_SEC(1);
#endif
    }

    return 0;
}

