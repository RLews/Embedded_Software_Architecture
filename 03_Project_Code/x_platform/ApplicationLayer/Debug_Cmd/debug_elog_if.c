/*!
************************************************************************************************************************
* @file debug_elog_if.c
* @brief ����elog���ýӿ�
* @details 
* @author Lews Hammond
* @date 2021-9-6
************************************************************************************************************************
*/

#include "debug_elog_if.h"

/*!
************************************************************************************************************************
* @brief ����elog����
* @param[in] pData[] �����ַ���
* @param[in] dataLen �����
* @param[out] void
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-6
************************************************************************************************************************
*/

void DbgElog_OnHandle(char pData[], uint16_t dataLen)
{
    (void)pData;
    (void)dataLen;
    RTE_ELOG_SET_LEVEL(ELOG_LVL_VERBOSE);
}

/*!
************************************************************************************************************************
* @brief ����elog�ر�
* @param[in] pData[] �����ַ���
* @param[in] dataLen �����
* @param[out] void
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-6
************************************************************************************************************************
*/

void DbgElog_OffHandle(char pData[], uint16_t dataLen)
{
    (void)pData;
    (void)dataLen;
    RTE_ELOG_SET_LEVEL(ELOG_LVL_ASSERT);
}

/*!
************************************************************************************************************************
* @brief ����elog�ȼ�
* @param[in] pData[] �����ַ���
* @param[in] dataLen �����
* @param[out] void
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-6
************************************************************************************************************************
*/

void DbgElog_SetLevelHandle(char pData[], uint16_t dataLen)
{
    int num = 0;
    
    if ((pData == NULL)
     || (dataLen == 0))
    {
        RTE_LOG_E("set elog level input parameter error.\n");
        return;
    }

    num = atoi(pData);

    if (num > ELOG_LVL_VERBOSE)
    {
        RTE_LOG_E("set elog level input parameter out of range.\n");
        return;
    }

    RTE_ELOG_SET_LEVEL((uint8_t)num);
}


