/*!
************************************************************************************************************************
* @file rte_linux_if.h
* @brief 
* @details 
* @author Lews Hammond
* @date 2021-8-18
************************************************************************************************************************
*/

#ifndef RTE_LINUX_IF_H
#define RTE_LINUX_IF_H


#ifdef __cplusplus
extern "C" {
#endif


#include "osal.h"


#define RTE_OSAL_SLEEP_US(us)                                   D_OSAL_SLEEP_US(us)
#define RTE_OSAL_SLEEP_SEC(sec)                                 D_OSAL_SLEEP_SEC(sec)

#define RTE_OSAL_GET_CURRENT_TIME(pFormat, pTimes, timeLen)     Osal_GetCurrentTime(pFormat, pTimes, timeLen)



typedef Osal_Pthread_Mutex_t Rte_Pthread_Mutex_t;

#define RTE_OSAL_PTHREAD_MUTEX_INIT(pLockInfo)                  D_OSAL_PTHREAD_MUTEX_INIT(pLockInfo)        
#define RTE_OSAL_PTHREAD_MUTEX_LOCK(pLockInfo)                  D_OSAL_PTHREAD_MUTEX_LOCK(pLockInfo)        
#define RTE_OSAL_PTHREAD_MUTEX_UNLOCK(pLockInfo)                D_OSAL_PTHREAD_MUTEX_UNLOCK(pLockInfo)      
#define RTE_OSAL_PTHREAD_MUTEX_DESTORY(pLockInfo)               D_OSAL_PTHREAD_MUTEX_DESTORY(pLockInfo)     

#define RTE_OSAL_GET_PID()                                      D_OSAL_GET_PID()                            
#define RTE_OSAL_GET_TID()                                      D_OSAL_GET_TID()                            

#define RTE_OSAL_CREATE_THREAD_DEF(pFunc, pName)                Osal_CreateThreadDef(pFunc, pName)


#define RTE_OSAL_SOCKET_CLOSE(fd)                               D_OSAL_SOCKET_CLOSE(fd)

#define RTE_OSAL_SOCKET_RECV(fd, pBuf, bufLen)                  D_OSAL_SOCKET_RECV(fd, pBuf, bufLen)
#define RTE_OSAL_SOCKET_SEND(fd, pBuf, bufLen)                  D_OSAL_SOCKET_SEND(fd, pBuf, bufLen)

#define RTE_OSAL_SOCKET_RECV_ERROR_WAIT_COND                    D_OSAL_SOCKET_RECV_ERROR_WAIT_COND

#define RTE_OSAL_CREATE_AFLOCAL_SOCKET(pFile)                   Osal_CreateAFLocalSocket(pFile)

#define RTE_OSAL_ACCEPT(fd)                                     Osal_Accept(fd)



#ifdef __cplusplus
}
#endif




#endif

