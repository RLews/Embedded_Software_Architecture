/*!
************************************************************************************************************************
* @file debug_tp.h
* @brief debug transport layer for linux
* @details 
* @author Lews Hammond
* @date 2021-9-5
************************************************************************************************************************
*/

#ifndef DEBUG_TP_H
#define DEBUG_TP_H

/*! @brief socket消息文件路径 */
#define D_DEBUG_TP_MSG_FILE_PATH            "./.x_debug_server"

#define D_DEBUG_TP_BUF_SIZE                 1024U

#ifdef __cplusplus
extern "C" {
#endif


#include "rte.h"

typedef void (*DebugTp_ServersHandleFunc)(char pData[], uint16_t dataLen);

void DebugTp_Init(DebugTp_ServersHandleFunc pFunc);


#ifdef __cplusplus
}
#endif


#endif

