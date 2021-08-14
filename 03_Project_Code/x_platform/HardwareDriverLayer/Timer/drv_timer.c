/*!
************************************************************************************************************************
* @file drv_timer.c
* @details 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/



#include "drv_timer.h"

/*!
************************************************************************************************************************
* Function Drv_SysTickIntEnable
* @brief 使能systick中断
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_SysTickIntEnable(void)
{
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;   	//开启SYSTICK中断
}

/*!
************************************************************************************************************************
* Function Drv_SysTickIntDisable
* @brief 关闭systick中断
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_SysTickIntDisable(void)
{
	SysTick->CTRL &= (uint32_t)(~SysTick_CTRL_TICKINT_Msk);
}

/*!
************************************************************************************************************************
* Function Drv_SysTickOpen
* @brief 开启systick
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_SysTickOpen(void)
{
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;   	//开启SYSTICK  
}

/*!
************************************************************************************************************************
* Function Drv_SysTickClose
* @brief 关闭systick
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_SysTickClose(void)
{
	SysTick->CTRL &= (uint32_t)(~SysTick_CTRL_ENABLE_Msk);
}

/*!
************************************************************************************************************************
* Function Drv_SysTickSetReload
* @brief 设置systick重装值
* @param uint32_t val：重载值
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_SysTickSetReload(uint32_t val)
{
	SysTick->LOAD = val;
}


/*!
************************************************************************************************************************
* Function Drv_SysTickSetPriority
* @brief 设置systick为最低优先级
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_SysTickSetPriority(void)
{
	NVIC_SetPriority (SysTick_IRQn, (1U << __NVIC_PRIO_BITS) - 1U);  /* set Priority for Cortex-M0 System Interrupts */
}

