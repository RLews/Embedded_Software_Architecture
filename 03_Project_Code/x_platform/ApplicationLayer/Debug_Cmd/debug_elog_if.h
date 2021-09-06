/*!
************************************************************************************************************************
* @file debug_elog_if.h
* @brief 
* @details 
* @author Lews Hammond
* @date 2021-9-6
************************************************************************************************************************
*/

#ifndef DEBUG_ELOG_IF_H
#define DEBUG_ELOG_IF_H


#ifdef __cplusplus
extern "C" {
#endif

#include "rte.h"


void DbgElog_OnHandle(char pData[], uint16_t dataLen);
void DbgElog_OffHandle(char pData[], uint16_t dataLen);
void DbgElog_SetLevelHandle(char pData[], uint16_t dataLen);


#ifdef __cplusplus
}
#endif


#endif

