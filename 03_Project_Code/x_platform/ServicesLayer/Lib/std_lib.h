/*!
************************************************************************************************************************
* @file std_lib.h
* @details
* @author Lews Hammond
* @date 2019-7-18
************************************************************************************************************************
*/


#ifndef STD_LIB_H
#define STD_LIB_H

#include "rte_config.h"

#if defined(D_RTE_PLATFORM_MCU)
#include "hal_uart_pub.h"
#else
#include "platforms.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif


extern const char Str_Space[];

extern const char EndOfString;

extern const char SpaceString;

StdBoolean_t Srv_MemCmp(const void * str, const void * des, uint32_t strLen, uint32_t desLen);

uint32_t Srv_FindStringIndex(const void * str, const void * dest, uint32_t strLen, uint32_t destLen);

uint32_t Srv_FindStringEndIndex(const void * str, const void * dest, uint32_t strLen, uint32_t destLen);

void Srv_RemoveHeaderString(void * str, uint32_t removeLen, uint32_t strLen);

void Srv_RemoveEndString(void * str, uint32_t removeLen, uint32_t strLen);

void Srv_AppendString(void *original, void *appendStr, uint32_t appendLen, uint32_t strMaxLen);

uint32_t Srv_GetStringLen(const void * str);

#ifdef __cplusplus
}
#endif


#endif

