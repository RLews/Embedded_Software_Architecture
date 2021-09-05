/*!
************************************************************************************************************************
* @file elog_if.c
* @brief elog interface
* @details 
* @author Lews Hammond
* @date 2021-9-2
************************************************************************************************************************
*/

#include "elog_if.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "elog.h"

static pthread_mutex_t OutputLock;
static pthread_mutex_t FileLock;

/*!
************************************************************************************************************************
* @brief elog初始化
* @param[in] void
* @param[out] void
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-2
************************************************************************************************************************
*/

void Elog_Init(void)
{
    /* initialize EasyLogger */
    elog_init();
    /* set EasyLogger log format */
    elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
    elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
    elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
#ifdef ELOG_COLOR_ENABLE
    elog_set_text_color_enabled(true);
#endif
    /* start EasyLogger */
    elog_start();

}

/*!
************************************************************************************************************************
* @brief Elog 输出互斥锁初始化
* @param[in] void
* @param[out] void
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-2
************************************************************************************************************************
*/

void Elog_OutputLockInit(void)
{
    (void)pthread_mutex_init(&OutputLock, NULL);
}

/*!
************************************************************************************************************************
* @brief 获取elog输出互斥锁
* @param[in] void
* @param[out] void
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-2
************************************************************************************************************************
*/

void Elog_OutputLock(void)
{
    (void)pthread_mutex_lock(&OutputLock);
}

/*!
************************************************************************************************************************
* @brief 释放elog输出互斥锁
* @param[in] void
* @param[out] void
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-2
************************************************************************************************************************
*/

void Elog_OutputUnlock(void)
{
    (void)pthread_mutex_unlock(&OutputLock);
}

/*!
************************************************************************************************************************
* @brief 销毁elog输出互斥锁
* @param[in] void
* @param[out] void
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-2
************************************************************************************************************************
*/

void Elog_OutputLockDeinit(void)
{
    (void)pthread_mutex_destroy(&OutputLock);
}

/*!
************************************************************************************************************************
* @brief 初始化elog文件互斥锁
* @param[in] void
* @param[out] void
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-2
************************************************************************************************************************
*/

void Elog_FileLockInit(void)
{
    (void)pthread_mutex_init(&FileLock, NULL);
}

/*!
************************************************************************************************************************
* @brief 获取elog文件互斥锁
* @param[in] void
* @param[out] void
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-2
************************************************************************************************************************
*/

void Elog_FileLock(void)
{
    (void)pthread_mutex_lock(&FileLock);
}

/*!
************************************************************************************************************************
* @brief 释放elog文件互斥锁
* @param[in] void
* @param[out] void
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-2
************************************************************************************************************************
*/

void Elog_FileUnlock(void)
{
    (void)pthread_mutex_unlock(&FileLock);
}

/*!
************************************************************************************************************************
* @brief 销毁elog互斥锁
* @param[in] void
* @param[out] void
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-2
************************************************************************************************************************
*/

void Elog_FileLockDeinit(void)
{
    (void)pthread_mutex_destroy(&FileLock);
}

/*!
************************************************************************************************************************
* @brief 获取当前时间戳
* @param[in] void
* @param[out] void
* @param[in,out] void
* @returns const char * 时间字符串
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-2
************************************************************************************************************************
*/

const char * Elog_GetCurrentTime(void)
{
    static char CurSysTime[D_ELOG_CURRENT_TIME_BUF_SIZE] = { 0 };

    time_t tCur;
    struct tm tmCur;

    time(&tCur);
    localtime_r(&tCur, &tmCur);

    strftime(CurSysTime, sizeof(CurSysTime), "%Y-%m-%d %T", &tmCur);

    return CurSysTime;
}

/*!
************************************************************************************************************************
* @brief 获取PID
* @param[in] void
* @param[out] void
* @param[in,out] void
* @returns const char * PID字符串
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-2
************************************************************************************************************************
*/

const char * Elog_GetPid(void)
{
    static char CurProcessInfo[D_ELOG_PID_BUF_SIZE] = { 0 };

    snprintf(CurProcessInfo, D_ELOG_PID_BUF_SIZE, "pid:%04d", getpid());

    return CurProcessInfo;
}

/*!
************************************************************************************************************************
* @brief 获取线程ID
* @param[in] void
* @param[out] void
* @param[in,out] void
* @returns const char * ThreadID字符串
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-2
************************************************************************************************************************
*/

const char * Elog_GetThreadId(void)
{
    static char CurThreadInfo[D_ELOG_TID_BUF_SIZE] = { 0 };

    snprintf(CurThreadInfo, D_ELOG_TID_BUF_SIZE, "tid:%04ld", pthread_self());

    return CurThreadInfo;
}

