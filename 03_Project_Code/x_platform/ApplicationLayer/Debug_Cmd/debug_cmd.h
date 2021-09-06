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

/*! @brief �����ӹ��ܲ�ƥ���ӹ��ܲ��� */
#define D_DEBUG_SUB_CMD_NONE_STR                "NoneSubFuncParam"

#define D_DEBUG_ELOG_SET_SUB_FUNC_NUM           2
#define D_DEBUG_ELOG_SET_LVL_FUNC_NUM           1

typedef void (*Debug_SubFuncPtr)(char pData[], uint16_t dataLen);

typedef struct 
{
    char Debug_CmdSubFunc[D_DEBUG_CMD_FUNC_STR_MAX_LEN];    /*!< �����ӹ����ַ��� */
    Debug_SubFuncPtr Debug_CmdSubFuncPtr;                   /*!< �����ӹ��ܴ����� */
}DebugCmdSubFuncCfg_t;

typedef struct 
{
    char Debug_CmdType[D_DEBUG_CMD_STR_MAX_LEN];            /*!< ���������ַ��� */
    const DebugCmdSubFuncCfg_t *pDebug_CmdSubFuncCfg;       /*!< �ӹ������� */
    uint8_t cmdSubFuncNum;                                  /*!< �ӹ������� */
}DebugCmdCfg_t;

typedef struct 
{
    char cmdType[D_DEBUG_CMD_STR_MAX_LEN];                  /*!< ������������ */
    char cmdSubFuncCmd[D_DEBUG_CMD_FUNC_STR_MAX_LEN];       /*!< ���������ӹ��� */
}DebugCmdParse_t;

void Debug_Init(void);


#ifdef __cplusplus
}
#endif


#endif

