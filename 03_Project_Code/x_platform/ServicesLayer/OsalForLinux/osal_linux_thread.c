/*!
************************************************************************************************************************
* @file osal_linux_thread.c
* @brief Linux线程创建
* @details 
* @author Lews Hammond
* @date 2021-9-9
************************************************************************************************************************
*/

#include "osal.h"
#include "rte_elog_if.h"


/*!
************************************************************************************************************************
* @brief 按照默认调度创建线程
* @param[in] pFunc 线程调度函数
* @param[in] pThreadName 线程名
* @param[out] void
* @param[in,out] void
* @returns int 创建结果
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-9
************************************************************************************************************************
*/

int Osal_CreateThreadDef(void (*pFunc)(void), const char pThreadName[])
{
    int ret = 0;
    pthread_t threadInfo;
    int createRes = D_STD_RETURN_TPYE_OK;

    ret = pthread_create(&threadInfo, NULL, pFunc, NULL);
    if (ret != 0)
    {
        RTE_LOG_E("Create thread %s fail.\n", pThreadName);
        createRes = D_STD_RETURN_TYPE_CREATE_FAIL;
    }
    else
    {
        RTE_LOG_D("Create thread %s success.\n", pThreadName);
        (void)pthread_detach(threadInfo);
    }

    return createRes;
}


