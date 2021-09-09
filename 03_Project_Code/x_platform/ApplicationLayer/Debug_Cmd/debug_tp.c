/*!
************************************************************************************************************************
* @file debug_tp.c
* @brief debug transport layer for linux
* @details 
* @author Lews Hammond
* @date 2021-9-5
************************************************************************************************************************
*/

#include "debug_tp.h"


static char DebugTp_RxBuf[D_DEBUG_TP_BUF_SIZE] = {0};

static DebugTp_ServersHandleFunc DebugTp_ServersHandle = NULL;

static void DebugTp_Handle(void);

/*!
************************************************************************************************************************
* @brief debug tp layer init
* @param[in] pFunc 调试数据处理回调
* @param[out] void
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-5
************************************************************************************************************************
*/

void DebugTp_Init(DebugTp_ServersHandleFunc pFunc)
{
    int ret = 0;

    ret = RTE_OSAL_CREATE_THREAD_DEF(DebugTp_Handle, "Debug Tp Thread");

    if (ret < 0)
    {
        RTE_LOG_E("Debug Tp layer initial fail.\n");
        return;
    }

    DebugTp_ServersHandle = pFunc;
}

/*!
************************************************************************************************************************
* @brief debug tp layer handle
* @param[in] void
* @param[out] void
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-5
************************************************************************************************************************
*/

void DebugTp_Handle(void)
{
    int msg_fd = 0;
    int clientfd = 0;
    int ret = 0;

    msg_fd = RTE_OSAL_CREATE_AFLOCAL_SOCKET(D_DEBUG_TP_MSG_FILE_PATH);
    
    while (1)
    {
        clientfd = RTE_OSAL_ACCEPT(msg_fd);
        if (clientfd > 0)
        {
            memset(DebugTp_RxBuf, 0, sizeof(DebugTp_RxBuf));
            ret = RTE_OSAL_SOCKET_RECV(clientfd, &DebugTp_RxBuf, sizeof(DebugTp_RxBuf));
            if (ret < 0)
            {
                if (RTE_OSAL_SOCKET_RECV_ERROR_WAIT_COND)
                {
                    RTE_LOG_I("rev wait.\n");
                    continue;
                }
                else
                {
                    RTE_LOG_E("rev error.\n");
                }
            }
            else if (ret == 0)
            {
                RTE_LOG_E("socket has been closed.\n");
            }
            else
            {
                RTE_LOG_D("rev len = %d\n", ret);
                RTE_LOG_V("rev string: %s\n", DebugTp_RxBuf);
                // send to cmd parse
                if (DebugTp_ServersHandle != NULL)
                {
                    DebugTp_ServersHandle(DebugTp_RxBuf, ret);
                }
            }

            RTE_OSAL_SOCKET_CLOSE(clientfd);
        }
    }

    RTE_OSAL_SOCKET_CLOSE(msg_fd);
}

