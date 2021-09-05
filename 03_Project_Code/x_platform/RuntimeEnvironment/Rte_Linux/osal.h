/*!
************************************************************************************************************************
* @file osal.h
* @brief OS Abstration layer for linux
* @details 
* @author Lews Hammond
* @date 2021-8-19
************************************************************************************************************************
*/

#ifndef OSAL_H
#define OSAL_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/statfs.h>

#include <sys/time.h>
#include <time.h>

#include "platforms.h"



#define D_OSAL_SLEEP_US(us)             usleep(us)
#define D_OSAL_SLEEP_SEC(sec)           sleep(sec)


#endif

