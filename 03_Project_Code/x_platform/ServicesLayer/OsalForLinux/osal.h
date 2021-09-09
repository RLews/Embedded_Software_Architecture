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

#ifdef __cplusplus
extern "C" {
#endif

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

#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/un.h>

#include "platforms.h"


/*! @brief 时间类 */

#define D_OSAL_SLEEP_US(us)                         usleep(us)
#define D_OSAL_SLEEP_SEC(sec)                       sleep(sec)

void Osal_GetCurrentTime(const char pFormatStr[], char pTimes[], uint32_t timeBufLen);


/*! @brief 线程、进程类 */

typedef pthread_mutex_t Osal_Pthread_Mutex_t;

#define D_OSAL_PTHREAD_MUTEX_INIT(pLockInfo)        pthread_mutex_init(pLockInfo, NULL)
#define D_OSAL_PTHREAD_MUTEX_LOCK(pLockInfo)        pthread_mutex_lock(pLockInfo)
#define D_OSAL_PTHREAD_MUTEX_UNLOCK(pLockInfo)      pthread_mutex_unlock(pLockInfo)
#define D_OSAL_PTHREAD_MUTEX_DESTORY(pLockInfo)     pthread_mutex_destroy(pLockInfo)

#define D_OSAL_GET_PID()                            getpid()
#define D_OSAL_GET_TID()                            pthread_self()

int Osal_CreateThreadDef(void (*pFunc)(void), const char pThreadName[]);


/*! @brief socket */
#define D_OSAL_SOCKET_CLOSE(fd)                     close(fd)

#define D_OSAL_SOCKET_RECV(fd, pBuf, bufLen)        recv(fd, pBuf, bufLen, 0)
#define D_OSAL_SOCKET_SEND(fd, pBuf, bufLen)        send(fd, pBuf, bufLen, 0)

#define D_OSAL_SOCKET_RECV_ERROR_WAIT_COND          ((errno == EINTR) || (errno == EWOULDBLOCK) || (errno == EAGAIN))

int Osal_CreateAFLocalSocket(const char pFilePath[]);

int Osal_Accept(int socketFd);


#ifdef __cplusplus
}
#endif

#endif

