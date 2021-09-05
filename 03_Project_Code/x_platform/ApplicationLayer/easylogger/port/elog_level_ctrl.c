/*!
************************************************************************************************************************
* @file elog_level_ctrl.c
* @brief elog level control set
* @details 
* @author Lews Hammond
* @date 2021-9-2
************************************************************************************************************************
*/

#include "elog_level_ctrl.h"

static uint8_t Elog_LevelCfg = ELOG_LVL_VERBOSE;

/*!
************************************************************************************************************************
* @brief ����ELOG����ȼ�
* @param[in] lvl ��־�ȼ�
* @param[out] void
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-2
************************************************************************************************************************
*/

void Elog_SetLevel(uint8_t lvl)
{
    if (lvl > ELOG_LVL_VERBOSE)
    {
        return;
    }

    Elog_LevelCfg = lvl;
}

/*!
************************************************************************************************************************
* @brief ��ȡelog��־�ȼ�
* @param[in] void
* @param[out] void
* @param[in,out] void
* @returns uint8_t ��־�ȼ�
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-2
************************************************************************************************************************
*/

uint8_t Elog_GetLevel(void)
{
    return Elog_LevelCfg;
}


