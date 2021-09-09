/*!
************************************************************************************************************************
* @file osal_linux_socket.c
* @brief linux socket网络接口抽象
* @details 
* @author Lews Hammond
* @date 2021-9-9
************************************************************************************************************************
*/

#include "osal.h"
#include "rte_elog_if.h"

/*!
************************************************************************************************************************
* @brief 创建本地socket通讯
* @param[in] pFilePath 本地文件路径
* @param[out] void
* @param[in,out] void
* @returns int 创建结果
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-9
************************************************************************************************************************
*/

int Osal_CreateAFLocalSocket(const char pFilePath[])
{
    int sockFd = 0;
    int ret = 0;
    struct sockaddr_un serv;

    if (pFilePath == NULL)
    {
        return D_STD_RETURN_TYPE_PARAM_NULL;
    }

    sockFd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockFd < 0)
    {
        perror("Socket Error ");
        RTE_LOG_E("socket create fail.\n");
        return D_STD_RETURN_TYPE_CREATE_FAIL;
    }

    unlink(pFilePath);

    (void)memset(&serv, 0, sizeof(serv));
    serv.sun_family = AF_LOCAL;
    strcpy(serv.sun_path, pFilePath);

    ret = bind(sockFd, (struct sockaddr *)&serv, sizeof(serv));
    if (ret < 0)
    {
        close(sockFd);
        perror("Bind Error ");
        RTE_LOG_E("socket bind fail.\n");
        return D_STD_RETURN_TYPE_CREATE_FAIL;
    }

    ret = listen(sockFd, 1);
    if (ret < 0)
    {
        close(sockFd);
        perror("Listen Error ");
        RTE_LOG_E("socket listen fail.\n");
        return D_STD_RETURN_TYPE_CREATE_FAIL;
    }   

    return sockFd;
}

/*!
************************************************************************************************************************
* @brief 等待socket客户端连接
* @param[in] socketFd socket 创建时的句柄
* @param[out] void
* @param[in,out] void
* @returns int 客户端socket句柄
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-9
************************************************************************************************************************
*/

int Osal_Accept(int socketFd)
{
    struct sockaddr_in client_addr;
    socklen_t client_length = sizeof(client_addr);

    return accept(socketFd, (struct sockaddr*)&client_addr, &client_length);
}

