/*!
************************************************************************************************************************
* @file drv_wdg.h
* @details 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/



#ifndef DRV_WATCHDOG_H
#define DRV_WATCHDOG_H

#include "drv_wdg_pub.h"


/* Toverflow = ((4 * (2 ^ PerscalerFactor)) * ReloadVal) / 40 */
#define D_DRV_WDG_RELOAD_VAL			(187u)//300ms overflow

#define D_DRV_WDG_PERSCALER_FACTOR		(4u)


#endif

