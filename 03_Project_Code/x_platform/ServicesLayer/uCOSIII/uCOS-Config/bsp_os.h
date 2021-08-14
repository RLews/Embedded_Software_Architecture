/*!
************************************************************************************************************************
* @file bsp_os.h
* @details 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/



#ifndef _BSP_OS_H
#define _BSP_OS_H

#include "os.h"
#include "os_cpu.h"
#include "os_cfg.h"

#include "cpu_core.h"
#include "drv_timer_pub.h"
#include "drv_dwt_pub.h"
#include "hal_int_pub.h"

void Bsp_OsTickInit(void);

#endif

