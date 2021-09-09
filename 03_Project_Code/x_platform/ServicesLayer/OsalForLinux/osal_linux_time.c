/*!
************************************************************************************************************************
* @file osal_linux_time.c
* @brief linux时间类接口抽象
* @details 
* @author Lews Hammond
* @date 2021-9-9
************************************************************************************************************************
*/

#include "osal.h"


/*!
************************************************************************************************************************
* @brief 获取系统当前时间
* @param[in] pFormatStr 时间格式字符串
* @param[in] timeBufLen 时间字符串缓存大小
* @param[out] pTimes 时间字符串
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


