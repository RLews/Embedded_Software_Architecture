/*!
************************************************************************************************************************
* @file bsp_os.c
* @details ucos iii�弶֧�ְ�
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/



#include "bsp_os.h"

static void Bsp_OsTimeStampInit(void);
static uint32_t Bsp_GetOsTimeStamp(void);
static uint32_t Bsp_GetCpuFreq(void);
static void Bsp_Os_SysTickHandler(void);


/*!
************************************************************************************************************************
* Function Bsp_OsTimeStampInit
* @brief ��ȡmcuʱ�����ʼ��
* @param void
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static void Bsp_OsTimeStampInit(void)
{
    Drv_DwtInit();
}

/*!
************************************************************************************************************************
* Function Bsp_GetOsTimeStamp
* @brief ��ȡmcu����ʱ���
* @param void
* @param void
* @returns uint32_t��ʱ���
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static uint32_t Bsp_GetOsTimeStamp(void)
{
    return Drv_GetDwtCnt();
}

/*!
************************************************************************************************************************
* Function Bsp_GetCpuFreq
* @brief ��ȡcpu����Ƶ��
* @param void
* @param void
* @returns uint32_t��cpuƵ��
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static uint32_t Bsp_GetCpuFreq(void)
{
    return Drv_GetCpuFreq();
}

/*!
************************************************************************************************************************
* Function Bsp_OsTickInit
* @brief ϵͳtick��ʼ��
* @param void
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Bsp_OsTickInit(void)
{
    uint32_t tReload = 0;
    const uint32_t *pSysCoreClock = &SystemCoreClock;
    const uint32_t *pOsTickRateHz = &OSCfg_TickRate_Hz;

    tReload = (*pSysCoreClock) / 8000000;//ÿ���ӵļ������� ��λΪK
    tReload *= 1000000 / (*pOsTickRateHz);//����delay_ostickspersec�趨���ʱ��

    Hal_SysISRSet(EN_SYS_TICK_ISR, Bsp_Os_SysTickHandler);
    Drv_SysTickSetPriority();
    Drv_SysTickIntEnable();
    Drv_SysTickSetReload(tReload);
    Drv_SysTickOpen();
}


#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
/*!
************************************************************************************************************************
* Function CPU_TS_TmrInit
* @brief ϵͳʱ��������ʼ��
* @param void
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void  CPU_TS_TmrInit(void)
{
    CPU_INT32U  tCpuFreq = 0u;

    Bsp_OsTimeStampInit();

    tCpuFreq = Bsp_GetCpuFreq();
    CPU_TS_TmrFreqSet(tCpuFreq);
}
#endif

#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
/*!
************************************************************************************************************************
* Function CPU_TS_TmrRd
* @brief ��ȡϵͳʱ���
* @param void
* @param void
* @returns CPU_TS_TMR��ϵͳʱ���
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

CPU_TS_TMR  CPU_TS_TmrRd(void)
{
    return Bsp_GetOsTimeStamp();
}
#endif


#if (CPU_CFG_TS_32_EN == DEF_ENABLED)
/*!
************************************************************************************************************************
* Function CPU_TS32_to_uSec
* @brief ��ϵͳʱ���ת����us
* @param CPU_TS32 ts_cnts����Ҫת����ʱ���
* @param void
* @returns CPU_INT64U��usʱ��
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

CPU_INT64U CPU_TS32_to_uSec(CPU_TS32 ts_cnts)
{
    CPU_INT64U tUs = 0u;
    CPU_INT64U tFreq = 0u;

    tFreq = Bsp_GetCpuFreq();
    tUs = ts_cnts / (tFreq / DEF_TIME_NBR_uS_PER_SEC);

    return tUs;
}
#endif

#if (CPU_CFG_TS_64_EN == DEF_ENABLED)
/*!
************************************************************************************************************************
* Function CPU_TS64_to_uSec
* @brief ��ϵͳʱ���ת����us
* @param CPU_TS32 ts_cnts����Ҫת����ʱ���
* @param void
* @returns CPU_INT64U��usʱ��
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/


CPU_INT64U CPU_TS64_to_uSec(CPU_TS64 ts_cnts)
{
    CPU_INT64U tUs = 0u;
    CPU_INT64U tFreq = 0u;

    tFreq = Bsp_GetCpuFreq();
    tUs = ts_cnts / (tFreq / DEF_TIME_NBR_uS_PER_SEC);

    return tUs;
}
#endif

/*!
************************************************************************************************************************
* Function Bsp_Os_SysTickHandler
* @brief tick�жϷ�����
* @param void
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static void Bsp_Os_SysTickHandler(void)
{
    if(OSRunning==1)
    {
        OS_CPU_SysTickHandler();
    }
}

