/*!
************************************************************************************************************************
* @file hal_rtc.c
* @details
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

#include "hal_rtc.h"


static RtcTime_t SysTime = {0};

static const uint8_t RtcMonTbl[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
static const uint8_t RtcWeekTbl[12] = {0,3,3,6,1,4,6,2,5,0,3,5};

static void Hal_RtcUpdate(void);
static StdBoolean_t Hal_RtcJudgeLeap(uint16_t year);
static uint8_t Hal_RtcGetWeek(uint16_t year, uint8_t mon, uint8_t day);
static void Hal_RtcIsrHandle(void);



/*!
************************************************************************************************************************
* Function Hal_RtcInit
* @brief rtc初始化
* @param void
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Hal_RtcInit(void)
{
    RtcTime_t *pTime = &SysTime;
    RtcTime_t defaultTime =
    {
        D_DEFAULT_SYS_TIME_YEAR,D_DEFAULT_SYS_TIME_MON,D_DEFAULT_SYS_TIME_DAY,
        D_DEFAULT_SYS_TIME_HOUR,D_DEFAULT_SYS_TIME_MIN,D_DEFAULT_SYS_TIME_SEC,D_DEFAULT_SYS_TIME_WEEK
    };

    Hal_SysISRSet(EN_RTC_ISR, Hal_RtcIsrHandle);
    Drv_RtcInit();
    Hal_RtcUpdate();

    if(pTime->rtcYear < D_DEFAULT_SYS_TIME_YEAR) //system rtc power off
    {
        Hal_RtcSetTime(defaultTime);
    }
}

/*!
************************************************************************************************************************
* Function Hal_RtcGetTime
* @brief 获取rtc时间
* @param RtcTime_t *pTime：rtc时间结构体
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Hal_RtcGetTime(RtcTime_t *pTime)
{
    D_DRV_DISABLE_RTC_SEC_INT();

    pTime->rtcYear = SysTime.rtcYear;
    pTime->rtcMon = SysTime.rtcMon;
    pTime->rtcDay = SysTime.rtcDay;
    pTime->rtcHour = SysTime.rtcHour;
    pTime->rtcMin = SysTime.rtcMin;
    pTime->rtcSec = SysTime.rtcSec;
    pTime->rtcWeek = SysTime.rtcWeek;

    D_DRV_ENABLE_RTC_SEC_INT();
}

/*!
************************************************************************************************************************
* Function Hal_RtcIsrHandle
* @brief rtc interrupt function
* @param void
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static void Hal_RtcIsrHandle(void)
{
    if(Drv_RtcIsSecInt() == D_STD_TRUE)
    {
        Hal_RtcUpdate();
    }

    Drv_RtcIsrHandle();
}

/*!
************************************************************************************************************************
* Function Hal_RtcJudgeLeap
* @brief 判断是否为闰年
* @param uint16_t year：年
* @param void
* @returns stdBoolean_t：是否是闰年
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static StdBoolean_t Hal_RtcJudgeLeap(uint16_t year)
{
    if(year % 4 == 0) //必须能被4整除
    {
        if(year % 100 == 0)
        {
            if(year % 400 == 0)
            {
                return D_STD_TRUE;//如果以00结尾,还要能被400整除
            }
            else
            {
                return D_STD_FALSE;
            }
        }
        else
        {
            return D_STD_TRUE;
        }
    }
    else
    {
        return D_STD_FALSE;
    }
}

/*!
************************************************************************************************************************
* Function Hal_RtcUpdate
* @brief 更新rtc时间
* @param void
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static void Hal_RtcUpdate(void)
{
    static uint16_t dayCnt = 0xFF;
    RtcTime_t *pTime = &SysTime;
    uint32_t timeCnt = Drv_RtcGetCount();
    uint32_t temp = 0;
    uint32_t temp1 = 0;

    temp = timeCnt / D_HAL_SEC_IN_A_DAY;

    if(dayCnt != temp)
    {
        dayCnt = (uint16_t)temp;
        temp1 = 1970;

        while(temp >= 365)
        {
            if(Hal_RtcJudgeLeap((uint16_t)temp1) == D_STD_TRUE)
            {
                if(temp >= 366)
                {
                    temp -= 366;
                }
                else
                {
                    temp1++;
                    break;
                }
            }
            else
            {
                temp -= 365;
            }

            temp1++;
        }

        pTime->rtcYear = (uint16_t)temp1;
        temp1 = 0;

        while(temp >= 28)
        {
            if((Hal_RtcJudgeLeap((uint16_t)temp1) == D_STD_TRUE) && (temp1==1))
            {
                if(temp >= 29)
                {
                    temp -= 29;
                }
                else
                {
                    break;
                }
            }
            else
            {
                if(temp >= RtcMonTbl[temp1])
                {
                    temp -= RtcMonTbl[temp1];
                }
                else
                {
                    break;
                }
            }

            temp1++;
        }

        pTime->rtcMon = (uint8_t)(temp1 + 1);
        pTime->rtcDay = (uint8_t)(temp + 1);
    }

    temp = timeCnt % D_HAL_SEC_IN_A_DAY;
    pTime->rtcHour = (uint8_t)(temp / D_HAL_SEC_IN_A_HOUR);
    pTime->rtcMin = (uint8_t)((temp % D_HAL_SEC_IN_A_HOUR) / D_HAL_TIME_SEC_IN_A_MIN);
    pTime->rtcSec = (uint8_t)((temp % D_HAL_SEC_IN_A_HOUR) % D_HAL_TIME_SEC_IN_A_MIN);
    pTime->rtcWeek = Hal_RtcGetWeek(pTime->rtcYear, pTime->rtcMon, pTime->rtcDay);
}

/*!
************************************************************************************************************************
* Function Hal_RtcSetTime
* @brief 设置rtc时间
* @param RtcTime_t times：设置的时间
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Hal_RtcSetTime(RtcTime_t times)
{
    uint16_t t = 0;
    uint32_t seccount = 0;

    if((times.rtcYear < 1970) || (times.rtcYear > 2099))
    {
        return;
    }

    for(t = 1970; t < times.rtcYear; t++)
    {
        if(Hal_RtcJudgeLeap(t) == D_STD_TRUE)
        {
            seccount += D_HAL_SEC_IN_LEAP_YEAR;
        }
        else
        {
            seccount += D_HAL_SEC_IN_NOR_YEAR;
        }
    }

    times.rtcMon -= 1;

    for(t = 0; t < times.rtcMon; t++)
    {
        seccount += (uint32_t)RtcMonTbl[t] * D_HAL_SEC_IN_A_DAY;

        if((Hal_RtcJudgeLeap(times.rtcYear) == D_STD_TRUE) && (t == 1))
        {
            seccount += D_HAL_SEC_IN_A_DAY;
        }
    }

    seccount += (uint32_t)(times.rtcDay - 1) * D_HAL_SEC_IN_A_DAY;
    seccount += (uint32_t)times.rtcHour * D_HAL_SEC_IN_A_HOUR;
    seccount += (uint32_t)times.rtcMin * D_HAL_TIME_SEC_IN_A_MIN;
    seccount += times.rtcSec;

    Drv_RtcSetCount(seccount);
}

/*!
************************************************************************************************************************
* Function Hal_RtcGetWeek
* @brief 计算周数
* @param uint16_t year
* @param uint8_t mon
* @param uint8_t day
* @returns uint8_t：周数
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static uint8_t Hal_RtcGetWeek(uint16_t year, uint8_t mon, uint8_t day)
{
    uint16_t temp2 = 0;
    uint8_t yearH = 0;
    uint8_t yearL = 0;

    if((mon == 0)
       || (mon > 12)
       || (day == 0)
       || (day > 31))
    {
        return 0xFFU;
    }

    yearH = (uint8_t)(year / 100U);
    yearL = (uint8_t)(year % 100U);

    // 如果为21世纪,年份数加100
    if(yearH > 19)
    {
        yearL+=100U;
    }

    // 所过闰年数只算1900年之后的
    temp2 = (uint16_t)(yearL + (yearL / 4U));
    temp2 = temp2 % 7U;
    temp2 = temp2 + day + RtcWeekTbl[mon-1];

    if((yearL % 4U == 0) && (mon < 3))
    {
        temp2--;
    }

    return (uint8_t)(temp2 % 7U);
}

