/*!
************************************************************************************************************************
* @file hal.c
* @details
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/


#include "hal.h"


static HalInitSta_t HalInitSta = EN_HAL_UNINIT;

/*!
************************************************************************************************************************
* Function Hal_SysInit
* @brief 硬件抽象层初始化
* @param void
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Hal_SysInit(void)
{
    HalInitSta_t *pInitSta = &HalInitSta;
#if (D_SYS_WDG_ENABLE == D_STD_ON)
    D_HAL_WDG_INIT();
    *pInitSta = EN_HAL_WDG_INIT_FINISH;
#endif
    Hal_SysIntInit();
    *pInitSta = EN_HAL_INT_INIT_FINISH;

    Hal_IoInit();
    *pInitSta = EN_HAL_IO_INIT_FINISH;

    Hal_SysUartInit();
    *pInitSta = EN_HAL_UART_INIT_FINISH;

    Hal_RtcInit();
    *pInitSta = EN_HAL_RTC_INIT_FINISH;

#if (EXTERN_SRAM_ENABLE == D_STD_ENABLE)

    if(Hal_SramInit() == D_STD_FALSE)
    {
        *pInitSta = EN_HAL_SRAM_INIT_ERR;
    }
    else
#endif
    {
        *pInitSta = EN_HAL_ALL_INIT_FINISH;
    }

}

/*!
************************************************************************************************************************
* Function Hal_GetInitStatus
* @brief 获取抽象层初始化状态
* @param void
* @param void
* @returns halInitSta_t：初始化状态
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

HalInitSta_t Hal_GetInitStatus(void)
{
    return HalInitSta;
}



