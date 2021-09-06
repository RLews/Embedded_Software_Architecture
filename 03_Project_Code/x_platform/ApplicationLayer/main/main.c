/*!
************************************************************************************************************************
* @file main.c
* @brief 应用入口
* @details 软件架构demo
* @author Lews Hammond
* @date 2021-8-14
************************************************************************************************************************
*/

#include "main.h"
#include "rte_debug_if.h"

/*!
************************************************************************************************************************
* @brief 应用程序入口
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
    RTE_DEBUG_INIT();

    RTE_LOG_I("version: %s\n", D_SOFTWARE_VER);
#endif

    while(1)
    {
        /* do nothing */
#if defined(D_RTE_PLATFORM_SOC)
        RTE_LOG_V("x platform demo running...\n");
        RTE_OSAL_SLEEP_SEC(5);
#endif
    }

    return 0;
}

