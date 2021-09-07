/*!
************************************************************************************************************************
* @file debug_cmd.c
* @brief debug cmd handle
* @details 
* @author Lews Hammond
* @date 2021-9-5
************************************************************************************************************************
*/

#include "debug_cmd.h"
#include "debug_tp.h"
#include "debug_elog_if.h"



/*! @brief elog…Ë÷√µ˜ ‘≈‰÷√ */
static const DebugCmdSubFuncCfg_t Debug_ElogSetFuncCfg[] = 
{
    {"on", DbgElog_OnHandle},
    {"off", DbgElog_OffHandle},
};

static const DebugCmdSubFuncCfg_t Debug_ElogSetLvlCfg[] = 
{
    {D_DEBUG_SUB_CMD_NONE_STR, DbgElog_SetLevelHandle},
};

/*! @brief µ˜ ‘√¸¡Ó≈‰÷√ */
static const DebugCmdCfg_t Debug_CmdCfg[] = 
{
    {"elog_set", Debug_ElogSetFuncCfg, D_DEBUG_ELOG_SET_SUB_FUNC_NUM},
    {"elog_set_level", Debug_ElogSetLvlCfg, D_DEBUG_ELOG_SET_LVL_FUNC_NUM},
};

static DebugCmdParse_t Debug_ParseStr = {0};


static void Debug_CmdHandle(char pData[], uint16_t dataLen);
static int Debug_ParseCmdType(char pData[], uint16_t dataLen);

/*!
************************************************************************************************************************
* @brief µ˜ ‘√¸¡Óƒ£øÈ≥ı ºªØ
* @param[in] void
* @param[out] void
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-6
************************************************************************************************************************
*/

void Debug_Init(void)
{
    DebugTp_Init(Debug_CmdHandle);
    (void)memset(&Debug_ParseStr, 0, sizeof(Debug_ParseStr));
}

/*!
************************************************************************************************************************
* @brief µ˜ ‘√¸¡Ó¥¶¿Ì
* @param[in] pData[] √¸¡Ó◊÷∑˚¥Æ
* @param[in] dataLen √¸¡Ó≥§∂»
* @param[out] void
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-6
************************************************************************************************************************
*/

static void Debug_CmdHandle(char pData[], uint16_t dataLen)
{
    uint16_t i = 0;
    uint16_t j = 0;
    
    if (Debug_ParseCmdType(pData, dataLen) != 0)
    {
        return; // parse fail
    }

    for (i = 0; i < ArrayLength(Debug_CmdCfg); i++)
    {
        if (strcmp(Debug_CmdCfg[i].Debug_CmdType, Debug_ParseStr.cmdType) == 0)
        { // match cmd type
            for (j = 0; j < (Debug_CmdCfg[i].cmdSubFuncNum); j++)
            {
                if (strcmp(Debug_CmdCfg[i].pDebug_CmdSubFuncCfg[j].Debug_CmdSubFunc, D_DEBUG_SUB_CMD_NONE_STR) == 0)
                { // not handle sub function type, is a parameter
                    Debug_CmdCfg[i].pDebug_CmdSubFuncCfg[j].Debug_CmdSubFuncPtr(Debug_ParseStr.cmdSubFuncCmd, strlen(Debug_ParseStr.cmdSubFuncCmd));
                    break;
                }
                
                if (strcmp(Debug_CmdCfg[i].pDebug_CmdSubFuncCfg[j].Debug_CmdSubFunc, Debug_ParseStr.cmdSubFuncCmd) == 0)
                { // match cmd sub function
                    Debug_CmdCfg[i].pDebug_CmdSubFuncCfg[j].Debug_CmdSubFuncPtr(Debug_ParseStr.cmdSubFuncCmd, strlen(Debug_ParseStr.cmdSubFuncCmd));
                    break;
                }
            }
        }
    }
}

/*!
************************************************************************************************************************
* @brief Ω‚Œˆ√¸¡Ó◊÷∑˚¥Æ
* @param[in] pData[] √¸¡Ó◊÷∑˚¥Æ
* @param[in] dataLen √¸¡Ó≥§∂»
* @param[out] void
* @param[in,out] void
* @returns int parse result. ==0: success <0: fail
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-6
************************************************************************************************************************
*/

static int Debug_ParseCmdType(char pData[], uint16_t dataLen)
{
    int ret = 0;
    uint16_t i = 0;
    StdBoolean_t cmdTypeInd = D_STD_FALSE;
    uint16_t readIndex = 0;

    if (pData == NULL)
    {
        ret = -1; // input buffer is null
        return ret;
    }

    if ((strlen(pData) == 0)
     || (dataLen == 0))
    {
        ret = -2; // length error
        return ret;
    }

    (void)memset(&Debug_ParseStr, 0, sizeof(Debug_ParseStr));
    for (i = 0; i < dataLen; i++)
    {
        if (pData[i] == ' ')
        {
            if (cmdTypeInd == D_STD_FALSE)
            {
                cmdTypeInd = D_STD_TRUE;
                readIndex = 0;
            }
            else
            {
                break; // parse completed
            }
        }
        else
        {
            if (cmdTypeInd == D_STD_FALSE)
            {
                Debug_ParseStr.cmdType[readIndex] = pData[i];
                readIndex++;
                if (readIndex >= D_DEBUG_CMD_STR_MAX_LEN)
                {
                    RTE_LOG_E("received cmd type too long!\n");
                    ret = -3; // cmd type too long.
                    return ret;
                }
            }
            else
            {
                Debug_ParseStr.cmdSubFuncCmd[readIndex] = pData[i];
                readIndex++;
                if (readIndex >= D_DEBUG_CMD_FUNC_STR_MAX_LEN)
                {
                    RTE_LOG_E("received cmd sub function string too long!\n");
                    ret = -4; // cmd sub function string too long
                    return ret;
                }
            }
            
        }
    }

    return ret;
}


