/*!
************************************************************************************************************************
* @file drv_dwt.c
* @details
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/



#include "drv_dwt.h"

static StdBoolean_t DwtInitFinished = D_STD_FALSE;


/*!
************************************************************************************************************************
* Function Drv_DwtInit
* @brief dwt��ʼ��
* @param void
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_DwtInit(void)
{
    DEM_CR |= (uint32_t)DEM_CR_TRCENA;/* enable dwt */
    DWT_CYCCNT = (uint32_t)0;/* clear counter */
    DWT_CR |= (uint32_t)DWT_CR_CYCCNTENA;
    DwtInitFinished = D_STD_TRUE;
}

/*!
************************************************************************************************************************
* Function Drv_GetDwtInitSta
* @brief ��ȡdwt��ʼ��״̬
* @param void
* @param void
* @returns stdBoolean_t���Ƿ��ʼ�����
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

StdBoolean_t Drv_GetDwtInitSta(void)
{
    return DwtInitFinished;
}


/*!
************************************************************************************************************************
* Function Drv_GetDwtCnt
* @brief ��ȡdwt����ֵ
* @param void
* @param void
* @returns uint32_t������ֵ
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

uint32_t Drv_GetDwtCnt(void)
{
    return ((uint32_t)DWT_CYCCNT);
}

/*!
************************************************************************************************************************
* Function Drv_GetCpuFreq
* @brief ��ȡcpu����Ƶ��
* @param void
* @param void
* @returns uint32_t��cpuƵ��
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

uint32_t Drv_GetCpuFreq(void)
{
    RCC_ClocksTypeDef  rccClock = {0};

    RCC_GetClocksFreq(&rccClock);

    return ((uint32_t)rccClock.HCLK_Frequency);
}

