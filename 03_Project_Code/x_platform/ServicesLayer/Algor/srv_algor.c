/*!
************************************************************************************************************************
* @file srv_algor.c
* @brief
* @details
* @author Lews Hammond
* @date 2019-8-17
************************************************************************************************************************
*/

#include "srv_algor.h"



/*!
************************************************************************************************************************
* @brief 获取16bit随机数
* @param[in] seed 随机数种子
* @param[out]
* @returns uint16_t
* @pre none
* @note 线性同余算法
* @author Lews Hammond
* @date 2019-8-17
************************************************************************************************************************
*/

uint16_t Srv_GetRand16(uint16_t seed)
{
    uint16_t randValue = 0;
    uint16_t tRandSeed = seed;

    randValue = (uint16_t)(((0x17U*tRandSeed) + 0x31U) % 0xFFF3U);

    return randValue;
}

/*!
************************************************************************************************************************
* @brief first-order filter
* @param[in] uint16_t curDat: the new data
* @param[in] uint16_t lastDat: the last data
* @param[in] uint16_t filterFactor: first-order filter factor
* @param[out] void
* @returns uint16_t: filter result
* @pre none
* @note filterFactor: reference value 128
* @author Lews Hammond
* @date 2019-8-20
************************************************************************************************************************
*/

uint16_t Srv_FirstOrderFilter(uint16_t curDat, uint16_t lastDat, uint16_t filterFactor)
{
    uint16_t tFilterRes = 0;
    uint32_t temp = 0;

    if(curDat > lastDat)
    {
        temp = ((uint32_t)(curDat - lastDat))*((uint32_t)filterFactor);
        tFilterRes = lastDat + (uint16_t)(temp / 256U);
    }
    else
    {
        temp = ((uint32_t)(lastDat - curDat))*((uint32_t)filterFactor);
        tFilterRes = (uint16_t)(lastDat - (uint32_t)(temp / 256U));
    }

    return tFilterRes;
}


