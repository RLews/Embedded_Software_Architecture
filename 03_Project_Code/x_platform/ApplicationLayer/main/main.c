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
#if (D_RTE_OS_CONFIG == D_OS_UC_RTOS)
    RTE_HAL_SYSINIT();
    RTE_OSAL_OSINIT();
#endif

    while(1)
    {
        /* do nothing */
    }

    return 0;
}

