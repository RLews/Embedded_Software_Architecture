/*!
************************************************************************************************************************
* @file debug_client.c
* @brief debug test info send
* @details 
* @author Lews Hammond
* @date 2021-9-5
************************************************************************************************************************
*/

#include "debug_client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/poll.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <sys/un.h>

static char DebugTp_SendBuf[D_DEBUG_CLIENT_TP_SEND_BUF_SIZE] = {0};

/*!
************************************************************************************************************************
* @brief 发送调试命令
* @param[in] argc 传入参数个数
* @param[in] **argv 传入参数指针
* @param[out] void
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2021-9-5
************************************************************************************************************************
*/

int main(int argc, char *argv[])
{
	int ret = 0;
	int sockfd = 0;
	struct sockaddr_un serv;
	int i = 0;
	const char spaceStr = ' ';

	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("socket error");
		return -1;
	}

	bzero(&serv, sizeof(serv));
	serv.sun_family = AF_LOCAL;
	strcpy(serv.sun_path, D_DEBUG_TP_MSG_FILE_PATH);

	ret = connect(sockfd, (struct sockaddr *)&serv, sizeof(serv));
	if(ret < 0)
	{
		close(sockfd);
		perror("connect error");
		return -3;
	}

    for (i = 1; i < argc; i++)
    {
        ret = send(sockfd, argv[i], strlen(argv[i]), 0);
        if(ret < 0)
        {
        	perror("send error");
        	break;
        }
        ret = send(sockfd, &spaceStr, 1, 0);
        if(ret < 0)
        {
        	perror("send error");
        	break;
        }
    }
    
	close(sockfd);

	return 0;
}


