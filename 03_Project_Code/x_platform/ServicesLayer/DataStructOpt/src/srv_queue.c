/*!
************************************************************************************************************************
* @file srv_queue.c
* @details 
* @author Lews Hammond
* @date 2019-7-18
************************************************************************************************************************
*/


#include "srv_queue.h"

/*!
************************************************************************************************************************
* Function Srv_QueueInit
* @brief queue inital.
* @param volatile SrvQueue_t *pQue.	queue data structure pointer.
* @param volatile uint8_t pBuf[].	queue data buffer pointer.
* @param uint8_t bufSize.			queue data buffer size.
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-18
************************************************************************************************************************
*/

void Srv_QueueInit(volatile SrvQueue_t *pQue, volatile uint8_t pBuf[], uint16_t bufSize)
{
	pQue->frontInx = 0;
	pQue->rearInx = 0;
	pQue->qBuffer = pBuf;
	pQue->bufSize = 0;
	pQue->maxBufSize = bufSize;
}

/*!
************************************************************************************************************************
* Function Srv_QueueIsEmpty
* @brief determine if the queue is emtry
* @param volatile SrvQueue_t *pQue.	queue data structure pointer
* @param void
* @returns StdBoolean_t.				if the emtry then return true.
* @note 
* @author Lews Hammond
* @date 2019-7-18
************************************************************************************************************************
*/

StdBoolean_t Srv_QueueIsEmpty(volatile SrvQueue_t *pQue)
{
	StdBoolean_t isEmpty = D_STD_FALSE;

	if (pQue->bufSize == 0)
	{
		isEmpty = D_STD_TRUE;
	}

	return isEmpty;
}

/*!
************************************************************************************************************************
* Function Srv_QueueIsFull
* @brief determine if the queue is full.
* @param volatile SrvQueue_t *pQue.	queue data structure pointer.
* @param void
* @returns StdBoolean_t.				if the full then return true.
* @note 
* @author Lews Hammond
* @date 2019-7-18
************************************************************************************************************************
*/

StdBoolean_t Srv_QueueIsFull(volatile SrvQueue_t *pQue)
{
	StdBoolean_t isFull = D_STD_FALSE;
    
    if (pQue == NULL)
    {
        return isFull;
    }

	if (pQue->bufSize == pQue->maxBufSize)
	{
		isFull = D_STD_TRUE;
	}

	return isFull;
}

/*!
************************************************************************************************************************
* Function Srv_QueueIn
* @brief add one queue element.
* @param volatile SrvQueue_t *pQue.	queue data structure pointer.
* @param uint8_t dat.				need add data
* @returns StdBoolean_t.				operation reuslt.
* @note 
* @author Lews Hammond
* @date 2019-7-18
************************************************************************************************************************
*/

SrvQueueError_t Srv_QueueIn(volatile SrvQueue_t *pQue, uint8_t dat)
{
	SrvQueueError_t opt = EN_QUEUE_OPT_OK;

	if (pQue->bufSize < pQue->maxBufSize)
	{
		pQue->qBuffer[pQue->rearInx] = dat;
		pQue->bufSize++;
		pQue->rearInx++;
		if (pQue->rearInx >= pQue->maxBufSize)
		{
			pQue->rearInx = 0;
		}
	}
	else
	{
		opt = EN_QUEUE_OPT_FULL;
	}

	return opt;
}

/*!
************************************************************************************************************************
* Function Srv_QueueOut
* @brief out one queue element.
* @param volatile SrvQueue_t *pQue.	queue data structure pointer.
* @param uint8_t dat.				need out queue data
* @returns StdBoolean_t.				operation reuslt.
* @note 
* @author Lews Hammond
* @date 2019-7-18
************************************************************************************************************************
*/

SrvQueueError_t Srv_QueueOut(volatile SrvQueue_t *pQue, uint8_t *dat)
{
	SrvQueueError_t opt = EN_QUEUE_OPT_OK;

	if (pQue->bufSize != 0)
	{
		*dat = pQue->qBuffer[pQue->frontInx];
		pQue->frontInx++;
		pQue->bufSize--;
		if (pQue->frontInx >= pQue->maxBufSize)
		{
			pQue->frontInx = 0;
		}
	}
	else
	{
		opt = EN_QUEUE_OPT_EMPTY;
	}

	return opt;
}

/*!
************************************************************************************************************************
* Function Srv_ReadQueueHead
* @brief read queue header element.
* @param volatile SrvQueue_t *pQue.	queue data structure pointer.
* @param uint8_t *dat.				read data pointer.
* @returns StdBoolean_t.				operation reuslt.
* @note 
* @author Lews Hammond
* @date 2019-7-18
************************************************************************************************************************
*/

SrvQueueError_t Srv_ReadQueueHead(volatile SrvQueue_t *pQue, uint8_t *dat)
{
	SrvQueueError_t opt = EN_QUEUE_OPT_OK;

	if (pQue->bufSize != 0)
	{
		*dat = pQue->qBuffer[pQue->frontInx];
	}
	else
	{
		opt = EN_QUEUE_OPT_EMPTY;
	}

	return opt;
}



