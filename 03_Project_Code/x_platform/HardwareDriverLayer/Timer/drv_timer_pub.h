/*!
************************************************************************************************************************
* @file drv_timer_pub.h
* @brief
* @details
* @author Lews Hammond
* @date 2021-8-14
************************************************************************************************************************
*/

#ifndef DRV_TIMER_PUB_H
#define DRV_TIMER_PUB_H


#include "platforms.h"


/*
************************************************************************************************************************
* Timer Interface
************************************************************************************************************************
*/
void Drv_SysTickIntEnable(void);
void Drv_SysTickIntDisable(void);
void Drv_SysTickOpen(void);
void Drv_SysTickClose(void);
void Drv_SysTickSetReload(uint32_t val);
void Drv_SysTickSetPriority(void);




#endif

