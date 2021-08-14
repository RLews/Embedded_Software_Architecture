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
* @brief dwt初始化
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
* @brief 获取dwt初始化状态
* @param void
* @param void
* @returns stdBoolean_t：是否初始化完成
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
* @brief 获取dwt计数值
* @param void
* @param void
* @returns uint32_t：计数值
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
* @brief 获取cpu运行频率
* @param void
* @param void
* @returns uint32_t：cpu频率
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

