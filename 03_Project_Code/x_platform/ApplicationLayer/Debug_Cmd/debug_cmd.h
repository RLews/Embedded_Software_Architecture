/*!
************************************************************************************************************************
* @file debug_cmd.h
* @brief 
* @details 
* @author Lews Hammond
* @date 2021-9-5
************************************************************************************************************************
*/

#ifndef DEBUG_CMD_H
#define DEBUG_CMD_H



#ifdef __cplusplus
extern "C" {
#endif

#include "rte.h"

#define D_DEBUG_CMD_STR_MAX_LEN                 64U
#define D_DEBUG_CMD_FUNC_STR_MAX_LEN            64U

/*! @brief 命令子功能不匹配子功能参数 */
#define D_DEBUG_SUB_CMD_NONE_STR                "NoneSubFuncParam"

#define D_DEBUG_ELOG_SET_SUB_FUNC_NUM           2
#define D_DEBUG_ELOG_SET_LVL_FUNC_NUM           1

typedef void (*Debug_SubFuncPtr)(char pData[], uint16_t dataLen);

typedef struct 
{
    char Debug_CmdSubFunc[D_DEBUG_CMD_FUNC_STR_MAX_LEN];    /*!< 命令子功能字符串 */
    Debug_SubFuncPtr Debug_CmdSubFuncPtr;                   /*!< 命令子功能处理函数 */
}DebugCmdSubFuncCfg_t;

typedef struct 
{
    char Debug_CmdType[D_DEBUG_CMD_STR_MAX_LEN];            /*!< 命令类型字符串 */
    const DebugCmdSubFuncCfg_t *pDebug_CmdSubFuncCfg;       /*!< 子功能配置 */
    uint8_t cmdSubFuncNum;                                  /*!< 子功能数量 */
}DebugCmdCfg_t;

typedef struct 
{
    char cmdType[D_DEBUG_CMD_STR_MAX_LEN];                  /*!< 解析命令类型 */
    char cmdSubFuncCmd[D_DEBUG_CMD_FUNC_STR_MAX_LEN];       /*!< 解析命令子功能 */
}DebugCmdParse_t;

void Debug_Init(void);


#ifdef __cplusplus
}
#endif


#endif

