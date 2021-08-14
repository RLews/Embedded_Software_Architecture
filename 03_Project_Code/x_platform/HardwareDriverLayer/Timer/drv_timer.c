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
* @brief ʹ��systick�ж�
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
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;   	//����SYSTICK�ж�
}

/*!
************************************************************************************************************************
* Function Drv_SysTickIntDisable
* @brief �ر�systick�ж�
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
* @brief ����systick
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
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;   	//����SYSTICK  
}

/*!
************************************************************************************************************************
* Function Drv_SysTickClose
* @brief �ر�systick
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
* @brief ����systick��װֵ
* @param uint32_t val������ֵ
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
* @brief ����systickΪ������ȼ�
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

