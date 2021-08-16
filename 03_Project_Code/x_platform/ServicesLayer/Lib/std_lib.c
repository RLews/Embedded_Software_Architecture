/*!
************************************************************************************************************************
* @file std_lib.c
* @details
* @author Lews Hammond
* @date 2019-7-18
************************************************************************************************************************
*/


#include "std_lib.h"
#include "srv_memory.h"


const char Str_Space[] = " ";

const char EndOfString = '\0';

const char SpaceString = ' ';


#if (D_RTE_PLATFORM_CONFIG == D_RTE_PLATFORM_MCU)

/* need MicroLib */
int fputc(int ch, FILE *f)
{
    (void)Hal_UartWrite(EN_SYS_COM, (uint8_t *)&ch, 1);

    return ch;
}

#endif

/*!
************************************************************************************************************************
* @brief compare memory
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond
* @date 2019-9-3
************************************************************************************************************************
*/

StdBoolean_t Srv_MemCmp(const void * str, const void * des, uint32_t strLen, uint32_t desLen)
{
    StdBoolean_t isEqual = D_STD_TRUE;
    uint32_t i = 0;
    const char *srcStr = str;
    const char *desStr = des;

    if(strLen != desLen)
    {
        return D_STD_FALSE;
    }

    for(i = 0; i < strLen; i++)
    {
        if(*srcStr != *desStr)
        {
            isEqual = D_STD_FALSE;
            break;
        }

        srcStr++;
        desStr++;
    }

    return isEqual;
}

/*!
************************************************************************************************************************
* @brief 找出字符串中指定字符第一次出现的位置
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond
* @date 2019-9-3
************************************************************************************************************************
*/

uint32_t Srv_FindStringIndex(const void * str, const void * dest, uint32_t strLen, uint32_t destLen)
{
    uint32_t tIndex = 0xFFFFFFFFUL;
    uint32_t i = 0;
    const char *srcStr = str;

    if(strLen < destLen)
    {
        return tIndex;
    }

    for(i = 0; i < (strLen - destLen); i++)
    {
        if(Srv_MemCmp(srcStr, dest, destLen, destLen) == D_STD_TRUE)
        {
            tIndex = i; //find out
            break;
        }

        srcStr++;
    }

    return tIndex;
}

/*!
************************************************************************************************************************
* @brief 找出字符串中指定字符最后出现的位置
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond
* @date 2019-9-16
************************************************************************************************************************
*/

uint32_t Srv_FindStringEndIndex(const void * str, const void * dest, uint32_t strLen, uint32_t destLen)
{
    uint32_t tIndex = 0xFFFFFFFFUL;
    uint32_t i = 0;
    const char *srcStr = str;

    if(strLen < destLen)
    {
        return tIndex;
    }

    for(i = strLen - destLen; i > 0; i--)
    {
        if(Srv_MemCmp(&srcStr[i], dest, destLen, destLen) == D_STD_TRUE)
        {
            tIndex = i; //find out
            break;
        }
    }

    return tIndex;
}

/*!
************************************************************************************************************************
* @brief 移除字符串开头几个字节
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond
* @date 2019-9-3
************************************************************************************************************************
*/

void Srv_RemoveHeaderString(void * str, uint32_t removeLen, uint32_t strLen)
{
    char *newStr = NULL;
    char *srcStr = (char *)str;

    if(strLen == 0U)
    {
        return;
    }

    newStr = Srv_Malloc(D_IN_SRAM, (strLen * sizeof(char)));

    if(newStr == NULL)
    {
        return;
    }

    if(removeLen >= strLen)
    {
        Srv_MemSet(str, (uint8_t)EndOfString, strLen);
        Srv_Free(D_IN_SRAM, newStr);
        return;
    }

    Srv_MemCopy(newStr, &srcStr[removeLen], (strLen - removeLen));//获取保留的字符
    Srv_MemCopy(srcStr, newStr, (strLen - removeLen)); //更新字符
    Srv_MemSet(&srcStr[strLen - removeLen], (uint8_t)EndOfString, removeLen);

    Srv_Free(D_IN_SRAM, newStr);

}

/*!
************************************************************************************************************************
* @brief 移除字符串中最后几个字符
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond
* @date 2019-9-16
************************************************************************************************************************
*/

void Srv_RemoveEndString(void * str, uint32_t removeLen, uint32_t strLen)
{
    char *srcStr = (char *)str;

    if(strLen == 0U)
    {
        return;
    }

    if(removeLen >= strLen)
    {
        Srv_MemSet(str, (uint8_t)EndOfString, strLen);
    }
    else
    {
        Srv_MemSet(&srcStr[strLen - removeLen], (uint8_t)EndOfString, removeLen);
    }

}

/*!
************************************************************************************************************************
* @brief
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond
* @date 2019-9-16
************************************************************************************************************************
*/

void Srv_AppendString(void *original, void *appendStr, uint32_t appendLen, uint32_t strMaxLen)
{
    uint32_t originalLen = Srv_GetStringLen(original);
    uint32_t destStrLen = appendLen + originalLen;
    char *pOriginal = (char *)original;

    if(destStrLen >= strMaxLen)
    {
        appendLen = strMaxLen - originalLen;
    }

    Srv_MemCopy(&pOriginal[originalLen], appendStr, appendLen);
}

/*!
************************************************************************************************************************
* @brief get string length
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond
* @date 2019-9-5
************************************************************************************************************************
*/

uint32_t Srv_GetStringLen(const void * str)
{
    const char *tStr = (const char *)str;
    uint32_t tLen = 0;

    while((*tStr != EndOfString) && (str != NULL))
    {
        tLen++;
        tStr++;
    }

    return tLen;
}


