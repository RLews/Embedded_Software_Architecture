/*!
************************************************************************************************************************
* @file osal_linux_time.c
* @brief linuxʱ����ӿڳ���
* @details 
* @author Lews Hammond
* @date 2021-9-9
************************************************************************************************************************
*/

#include "osal.h"


/*!
************************************************************************************************************************
* @brief ��ȡϵͳ��ǰʱ��
* @param[in] pFormatStr ʱ���ʽ�ַ���
* @param[in] timeBufLen ʱ���ַ��������С
* @param[out] pTimes ʱ���ַ���
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-9
************************************************************************************************************************
*/

void Osal_GetCurrentTime(const char pFormatStr[], char pTimes[], uint32_t timeBufLen)
{
    time_t tCur;
    struct tm tmCur;

    if ((pFormatStr == NULL) || pTimes == NULL)
    {
        return ;
    }
    
    time(&tCur);
    localtime_r(&tCur, &tmCur);

    strftime(pTimes, timeBufLen, pFormatStr, &tmCur);
}


