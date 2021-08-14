/*!
************************************************************************************************************************
* @file srv_queue.h
* @details
* @author Lews Hammond
* @date 2019-7-18
************************************************************************************************************************
*/


#ifndef SRV_QUEUE_H
#define SRV_QUEUE_H

#include "platforms.h"


typedef enum QUEUE_ERROR_T
{
    EN_QUEUE_OPT_OK = 0,
    EN_QUEUE_OPT_FULL,
    EN_QUEUE_OPT_EMPTY,
    EN_QUEUE_OPT_NONE
} SrvQueueError_t;

typedef struct SRV_QUEUE_T
{
    uint16_t frontInx;
    uint16_t rearInx;
    volatile uint8_t *qBuffer;
    uint16_t bufSize;
    uint16_t maxBufSize;
} SrvQueue_t;

void Srv_QueueInit(volatile SrvQueue_t *pQue, volatile uint8_t pBuf[], uint16_t bufSize);

SrvQueueError_t Srv_QueueIn(volatile SrvQueue_t *pQue, uint8_t dat);

SrvQueueError_t Srv_QueueOut(volatile SrvQueue_t *pQue, uint8_t *dat);

StdBoolean_t Srv_QueueIsEmpty(volatile SrvQueue_t *pQue);

StdBoolean_t Srv_QueueIsFull(volatile SrvQueue_t *pQue);

SrvQueueError_t Srv_ReadQueueHead(volatile SrvQueue_t *pQue, uint8_t *dat);

#endif

