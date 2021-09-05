/*!
************************************************************************************************************************
* @file elog_if.h
* @brief elog interface
* @details 
* @author Lews Hammond
* @date 2021-9-2
************************************************************************************************************************
*/

#ifndef ELOG_IF_H
#define ELOG_IF_H

#define D_ELOG_CURRENT_TIME_BUF_SIZE            24U

#define D_ELOG_PID_BUF_SIZE                     10U

#define D_ELOG_TID_BUF_SIZE                     10U


#ifdef __cplusplus
extern "C" {
#endif

void Elog_Init(void);


void Elog_OutputLockInit(void);

void Elog_OutputLock(void);

void Elog_OutputUnlock(void);

void Elog_OutputLockDeinit(void);


void Elog_FileLockInit(void);

void Elog_FileLock(void);

void Elog_FileUnlock(void);

void Elog_FileLockDeinit(void);

const char * Elog_GetCurrentTime(void);

const char * Elog_GetPid(void);

const char * Elog_GetThreadId(void);


#ifdef __cplusplus
}
#endif


#endif

