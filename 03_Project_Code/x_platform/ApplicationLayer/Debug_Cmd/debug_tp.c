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
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/un.h>


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
    pthread_t debugPro;
    int ret = 0;

    ret = pthread_create(&debugPro, NULL, (void *)&DebugTp_Handle, NULL);
    if (ret != 0)
    {
        RTE_LOG_E("Create debug transport layer thread fail!\n");
        return;
    }
    else
    {
        RTE_LOG_D("Create debug transport layer thread success.\n");
    }
    (void)pthread_detach(debugPro);

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
    struct sockaddr_un serv;
    struct sockaddr_in client_addr;
    socklen_t client_length = sizeof(client_addr);
    int clientfd = 0;
    int ret = 0;

    msg_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (msg_fd < 0)
    {
        perror("Socket Error ");
        RTE_LOG_E("socket create fail.\n");
        return ;
    }

    unlink(D_DEBUG_TP_MSG_FILE_PATH);

    (void)memset(&serv, 0, sizeof(serv));
    serv.sun_family = AF_LOCAL;
    strcpy(serv.sun_path, D_DEBUG_TP_MSG_FILE_PATH);

    ret = bind(msg_fd, (struct sockaddr *)&serv, sizeof(serv));
    if (ret < 0)
    {
        close(msg_fd);
        perror("Bind Error ");
        RTE_LOG_E("socket bind fail.\n");
        return ;
    }

    ret = listen(msg_fd, 1);
    if (ret < 0)
    {
        close(msg_fd);
        perror("Listen Error ");
        RTE_LOG_E("socket listen fail.\n");
        return ;
    }   

    while (1)
    {
        clientfd = accept(msg_fd, (struct sockaddr*)&client_addr, &client_length);
        if (clientfd > 0)
        {
            memset(DebugTp_RxBuf, 0, sizeof(DebugTp_RxBuf));
            ret = recv(clientfd, &DebugTp_RxBuf, sizeof(DebugTp_RxBuf), 0);
            if (ret < 0)
            {
                if ((errno == EINTR) || (errno == EWOULDBLOCK) || (errno == EAGAIN))
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

            close(clientfd);
        }
    }

    close(msg_fd);
}

