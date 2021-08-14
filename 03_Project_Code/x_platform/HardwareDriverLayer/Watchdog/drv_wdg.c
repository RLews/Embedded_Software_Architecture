/*!
************************************************************************************************************************
* @file drv_wdg.c
* @details 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/



#include "drv_wdg.h"

static StdBoolean_t WdgInitFinished = D_STD_FALSE;


/*!
************************************************************************************************************************
* Function Drv_WdgInit
* @brief 看门狗初始化
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_WdgInit(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	
	IWDG_SetPrescaler(D_DRV_WDG_PERSCALER_FACTOR);
	
	IWDG_SetReload(D_DRV_WDG_RELOAD_VAL);
	
	IWDG_ReloadCounter();
	
	IWDG_Enable();

	WdgInitFinished = D_STD_TRUE;
}

/*!
************************************************************************************************************************
* Function Drv_GetWdgInitSta
* @brief get watchdog initial status
* @param void
* @param void
* @returns StdBoolean_t : watchdog initial state
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

StdBoolean_t Drv_GetWdgInitSta(void)
{
	return WdgInitFinished;
}

/*!
************************************************************************************************************************
* Function Drv_WdgFeed
* @brief feed watchdog
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_WdgFeed(void)
{
	IWDG_ReloadCounter();
}

