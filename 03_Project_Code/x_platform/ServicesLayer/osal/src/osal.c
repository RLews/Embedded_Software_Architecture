/*!
************************************************************************************************************************
* @file osal.c
* @details
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

#include "osal.h"
#include "srv_memory.h"

static FsDirAnaySta_t Fsal_AnaysisDir(const FSAL_CHAR *pDir, uint32_t dirLev, uint32_t len, FSAL_CHAR *pDest);


/*
************************************************************************************************************************
* uC OS III
************************************************************************************************************************
*/

/*!
************************************************************************************************************************
* Function Osal_OsInit
* @brief osal inital
* @param void
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Osal_OsInit(void)
{
    OS_ERR      err;

    Bsp_OsTickInit();

    OSInit(&err);
}

/*!
************************************************************************************************************************
* Function Osal_StartTaskConfig
* @brief uC/OS iii model initial.
* @param void
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Osal_StartTaskConfig(void)
{
    OS_ERR      err;

    CPU_Init();

    Mem_Init();                                                 /* Initialize Memory Management Module                  */

#if OS_CFG_STAT_TASK_EN > 0u
    /* First Create Start Task. Must!!! */
    /* if not create start task , then into hardfault. */
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif
#ifdef  CPU_CFG_INT_DIS_MEAS_EN
    (void)CPU_IntDisMeasMaxCurReset();
#endif

#if OS_CFG_SCHED_ROUND_ROBIN_EN
    OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);
#endif
}


/*!
************************************************************************************************************************
* Function Osal_TaskStkChk
* @brief task stack useage check
* @param OSAL_TCB *tcb : , OSAL_CPU_STK_SIZE *free : , OSAL_CPU_STK_SIZE *used :
* @param void
* @returns OSAL_BOOL: if check successful then return DEF_OK
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

OSAL_BOOL Osal_TaskStkChk(OSAL_TCB *tcb, OSAL_CPU_STK_SIZE *pFree, OSAL_CPU_STK_SIZE *used)
{
    OSAL_ERROR err = (OSAL_ERROR)0;

    OSTaskStkChk((OSAL_TCB *)tcb,
                 (OSAL_CPU_STK_SIZE *)pFree,
                 (OSAL_CPU_STK_SIZE *)used,
                 (OSAL_ERROR *)&err
                );

    if(err != OS_ERR_NONE)
    {
        return DEF_FAIL;
    }

    return DEF_OK;
}

/*!
************************************************************************************************************************
* Function Osal_TmrCreate
* @brief Create software timer
* @param OSAL_TMR *pTmr, OSAL_CHAR *name, OSAL_TICK tick, OSAL_OPT opt, OSAL_TMR_CALLBACK_PTR callback
* @param void
* @returns OSAL_BOOL : if operation successful then return DEF_OK
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

OSAL_BOOL Osal_TmrCreate(OSAL_TMR *pTmr, OSAL_CHAR *name, OSAL_TICK tick, OSAL_OPT opt, OSAL_TMR_CALLBACK_PTR callback)
{
    OSAL_ERROR err = (OSAL_ERROR)0;

    OSTmrCreate((OSAL_TMR *)pTmr,
                (OSAL_CHAR *)name,
                (OSAL_TICK)0,
                (OSAL_TICK)tick,
                (OSAL_OPT)opt,
                (OSAL_TMR_CALLBACK_PTR)callback,
                (void *)0,
                (OSAL_ERROR *)&err
               );

    if(err != OS_ERR_NONE)
    {
        return DEF_FAIL;
    }

    return DEF_OK;
}

/*!
************************************************************************************************************************
* Function Osal_TmrStart
* @brief Start software timer
* @param OSAL_TMR *pTmr
* @param void
* @returns OSAL_BOOL : if operation successful then return DEF_OK
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

OSAL_BOOL Osal_TmrStart(OSAL_TMR *pTmr)
{
    OSAL_ERROR err = (OSAL_ERROR)0;

    (void)OSTmrStart(pTmr, &err);

    if(err != OS_ERR_NONE)
    {
        return DEF_FAIL;
    }

    return DEF_OK;
}

/*!
************************************************************************************************************************
* Function Osal_TmrStop
* @brief Stop software timer
* @param OSAL_TMR *pTmr, OSAL_OPT opt
* @param void
* @returns OSAL_BOOL : if operation successful then return DEF_OK
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

OSAL_BOOL Osal_TmrStop(OSAL_TMR *pTmr, OSAL_OPT opt)
{
    OSAL_ERROR err = (OSAL_ERROR)0;

    (void)OSTmrStop(pTmr, opt, (void *)0, &err);

    if(err != OS_ERR_NONE)
    {
        return DEF_FAIL;
    }

    return DEF_OK;
}

/*!
************************************************************************************************************************
* Function Osal_SemCreate
* @brief create sem
* @param OSAL_SEM *pSem, OSAL_SEM_CTR semVal, OSAL_CHAR *name
* @param void
* @returns OSAL_BOOL : if operation successful then return DEF_OK
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

OSAL_BOOL Osal_SemCreate(OSAL_SEM *pSem, OSAL_SEM_CTR semVal, OSAL_CHAR *name)
{
    OSAL_ERROR err = (OSAL_ERROR)0;

    OSSemCreate((OS_SEM    *)pSem,
                (CPU_CHAR  *)name,
                (OS_SEM_CTR)semVal,
                (OS_ERR    *)&err);

    if(err != OS_ERR_NONE)
    {
        return DEF_FAIL;
    }

    return DEF_OK;
}

/*!
************************************************************************************************************************
* Function Osal_SemWait
* @brief wait sem
* @param OSAL_SEM *pSem, OSAL_UINT32 ms
* @param void
* @returns OSAL_BOOL : if operation successful then return DEF_OK
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

OSAL_BOOL Osal_SemWait(OSAL_SEM *pSem, OSAL_UINT32 ms)
{
    OSAL_ERROR err = (OSAL_ERROR)0;
    OSAL_UINT32 tick = 0;

    tick = ((ms * DEF_TIME_NBR_mS_PER_SEC) / OSCfg_TickRate_Hz);

    (void)OSSemPend((OS_SEM *)pSem,
                    (OS_TICK)tick,
                    (OS_OPT)OS_OPT_PEND_BLOCKING,
                    (CPU_TS)0,
                    (OS_ERR *)&err);

    if(err != OS_ERR_NONE)
    {
        return DEF_FAIL;
    }

    return DEF_OK;
}

/*!
************************************************************************************************************************
* Function Osal_SemRead
* @brief Read sem
* @param OSAL_SEM * pSem
* @param void
* @returns OSAL_BOOL
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

OSAL_BOOL Osal_SemRead(OSAL_SEM * pSem)
{
    OSAL_ERROR err = (OSAL_ERROR)0;

    (void)OSSemPend((OS_SEM *)pSem,
                    (OS_TICK)1,
                    (OS_OPT)OS_OPT_PEND_NON_BLOCKING,
                    (CPU_TS)0,
                    (OS_ERR *)&err);

    if(err != OS_ERR_NONE)
    {
        return DEF_FAIL;
    }

    return DEF_OK;
}

/*!
************************************************************************************************************************
* Function Osal_SemPost
* @brief post sem
* @param OSAL_SEM *pSem
* @param void
* @returns OSAL_BOOL
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

OSAL_BOOL Osal_SemPost(OSAL_SEM *pSem)
{
    OSAL_ERROR err = (OSAL_ERROR)0;

    (void)OSSemPost((OS_SEM *)pSem,
                    (OS_OPT)OS_OPT_POST_1,
                    (OS_ERR *)&err);

    if(err != OS_ERR_NONE)
    {
        return DEF_FAIL;
    }

    return DEF_OK;
}

/*!
************************************************************************************************************************
* Function Osal_SemSet
* @brief set sem
* @param OSAL_SEM *pSem, OSAL_SEM_CTR cnt
* @param void
* @returns OSAL_BOOL
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

OSAL_BOOL Osal_SemSet(OSAL_SEM *pSem, OSAL_SEM_CTR cnt)
{
    OSAL_ERROR err = (OSAL_ERROR)0;

    OSSemSet((OS_SEM *)pSem,
             (OS_SEM_CTR)cnt,
             (OS_ERR *)&err);


    return DEF_OK;
}

/*!
************************************************************************************************************************
* Function Osal_DelayMs
* @brief delay function. unit: ms.
* @param OSAL_UINT32 ms.    delay ms number.
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Osal_DelayMs(OSAL_UINT32 ms)
{
    OSAL_UINT16 tMs = 0;
    OSAL_UINT32 tSec = 0;
    OSAL_ERROR tErr;

    if(ms > 10000u)
    {
        ms = 10000u;
    }

    if(ms >= 1000u)
    {
        tMs = (uint16_t)(ms % 1000u);
        tSec = ms / 1000u;
    }
    else
    {
        tSec = 0;
        tMs = (uint16_t)ms;
    }

    OSTimeDlyHMSM((OSAL_UINT16) 0u,
                  (OSAL_UINT16) 0u,
                  (OSAL_UINT16) tSec,
                  (OSAL_UINT16) tMs,
                  (OSAL_OPT)OS_OPT_TIME_HMSM_STRICT,
                  (OSAL_ERROR *)&tErr
                 );
}

/*!
************************************************************************************************************************
* Function Osal_GetCurTs
* @brief get current timestamp
* @param void
* @param void
* @returns uint32_t current timestamp
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

uint32_t Osal_GetCurTs(void)
{
    return CPU_TS_TmrRd();
}


/*!
************************************************************************************************************************
* Function Osal_DiffTsToUsec
* @brief calculate different time
* @param uint32_t lastTs : last timestamp
* @param void
* @returns uint32_t different time. unit:us
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

uint32_t Osal_DiffTsToUsec(uint32_t lastTs)
{
    uint32_t curTs = Osal_GetCurTs();

    /* counter up */
    if(curTs > lastTs)
    {
        curTs = curTs - lastTs;
    }
    else
    {
        curTs = (uint32_t)(((0xFFFFFFFFUL - lastTs) + curTs) + 1U);
    }

    return (uint32_t)CPU_TS32_to_uSec(curTs);
}


/*
************************************************************************************************************************
* FatFS
************************************************************************************************************************
*/

/*!
************************************************************************************************************************
* Function Fsal_AnaysisDir
* @brief anaysis file dir
* @param const FSAL_CHAR *pDir, uint32_t dirLev, uint32_t len, FSAL_CHAR *pDest
* @param void
* @returns fsDirAnaySta_t：分析结果
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static FsDirAnaySta_t Fsal_AnaysisDir(const FSAL_CHAR *pDir, uint32_t dirLev, uint32_t len, FSAL_CHAR *pDest)
{
    uint32_t i = 0;
    uint32_t volcnt = 0;

    if(len == 0)
    {
        return EN_DIR_PARAMTER_ERR;
    }

    dirLev += 1;/* root dir is 0 */

    for(i = 0; i < len; i++)
    {
        if(*pDir == '/')
        {
            volcnt++;

            if(volcnt == dirLev)
            {
                break;
            }
        }

        *pDest = *pDir;
        pDest++;
        pDir++;
    }

    if((i == len) && (pDir[len-1] != '/')) /* search all string finish. last dir not / */
    {
        volcnt++;
    }

    if(volcnt == dirLev)
    {
        return EN_DIR_ANAYSIS_OK;
    }
    else
    {
        return EN_DIR_NO_EXIST;
    }
}

/*!
************************************************************************************************************************
* Function Fsal_MkDir
* @brief create files dir
* @param const FSAL_CHAR *pDir
* @param uint32_t len
* @returns FSAL_FRES
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/


FSAL_FRES Fsal_MkDir(const FSAL_CHAR *pDir, uint32_t len)
{
    uint32_t i = 1;
    FsDirAnaySta_t anaySta = EN_DIR_ANAYSIS_OK;
    FSAL_CHAR pVol[D_FSAL_MAX_ANAYSIS_DIR_SIZE] = "";
    FSAL_FRES mkRes = FR_OK;

    if(len > D_FSAL_MAX_ANAYSIS_DIR_SIZE)
    {
        return FR_INVALID_NAME;
    }

    do
    {
        anaySta = Fsal_AnaysisDir(pDir, i, len, pVol);

        if(anaySta == EN_DIR_ANAYSIS_OK)
        {
            i++;
            mkRes = f_mkdir(pVol);

            if((mkRes == FR_OK) || (mkRes == FR_EXIST))
            {
                /* create successful */
            }
            else
            {
                return mkRes;
            }
        }
    }
    while(anaySta == EN_DIR_ANAYSIS_OK);

    return mkRes;
}

/*!
************************************************************************************************************************
* Function Fsal_OpenW
* @brief open file. if file isn`t exsit then create
* @param FSAL_FIL *pFil: file, const FSAL_CHAR *pPath, const FSAL_CHAR *pDir, uint32_t dirLen
* @param void
* @returns FSAL_FRES: operation result
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

FSAL_FRES Fsal_OpenW(FSAL_FIL *pFil, const FSAL_CHAR *pPath, const FSAL_CHAR *pDir, uint32_t dirLen)
{
    FSAL_FRES res = FR_OK;

    res = f_open(pFil, pPath, FA_WRITE);/* try open */

    if(res != FR_OK)
    {
        res = f_open(pFil, pPath, FA_CREATE_ALWAYS | FA_WRITE);/* try create file and open */

        if(res != FR_OK)
        {
            res = Fsal_MkDir(pDir, dirLen);/* try create dir, create file and open */

            if(res == FR_OK)
            {
                res = f_open(pFil, pPath, FA_CREATE_ALWAYS | FA_WRITE);
            }
        }
    }

    return res;
}

/*!
************************************************************************************************************************
* Function Fsal_OpenR
* @brief read file
* @param FSAL_FIL *pFil
* @param const FSAL_CHAR *pCh
* @returns FSAL_FRES
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

FSAL_FRES Fsal_OpenR(FSAL_FIL *pFil, const FSAL_CHAR *pCh)
{
    FSAL_FRES res = FR_OK;

    res = f_open(pFil, pCh, FA_OPEN_ALWAYS | FA_READ);

    return res;
}

/*!
************************************************************************************************************************
* @brief delete folder or files
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond
* @date 2019-9-7
************************************************************************************************************************
*/

FSAL_FRES Fsal_DelDir(const FSAL_CHAR *path)
{
    FRESULT res;
    DIR   dir;     /* 文件夹对象 */ //36  bytes
    FILINFO fno;   /* 文件属性 */   //32  bytes
    TCHAR *file = NULL;

    file = Srv_Malloc(D_IN_SRAM, (_MAX_LFN + 2));

    if(file == NULL)
    {
        return FR_INT_ERR;
    }

#if _USE_LFN
    fno.lfsize = _MAX_LFN;
    fno.lfname = Srv_Malloc(D_IN_SRAM, (_MAX_LFN + 2));    //必须赋初值

    if(fno.lfname == NULL)
    {
        Srv_Free(D_IN_SRAM, file);
        return FR_INT_ERR;
    }

#endif
    //打开文件夹
    res = f_opendir(&dir, path);

    //持续读取文件夹内容
    while((res == FR_OK) && (FR_OK == f_readdir(&dir, &fno)))
    {
        //若是"."或".."文件夹，跳过
        if(0 == strlen(fno.fname))
        {
            break;      //若读到的文件名为空
        }

        if(0 == strcmp(fno.fname, "."))
        {
            continue;   //若读到的文件名为当前文件夹
        }

        if(0 == strcmp(fno.fname, ".."))
        {
            continue;   //若读到的文件名为上一级文件夹
        }

        memset(file, 0, (_MAX_LFN + 2));
#if _USE_LFN
        sprintf((char*)file, "%s/%s", path, (*fno.lfname) ? fno.lfname : fno.fname);
#else
        sprintf((char*)file, "%s/%s", path, fno.fname);
#endif

        if(fno.fattrib & AM_DIR)
        {
            //若是文件夹，递归删除
            res = Fsal_DelDir(file);
        }
        else
        {
            //若是文件，直接删除
            res = f_unlink(file);
        }
    }

    //删除本身
//    if(res == FR_OK)    若为空文件夹或文件，fatfs在opendir时会返回FR_NO_PATH
//    {
    res = f_unlink(path);
//    }


    Srv_Free(D_IN_SRAM, fno.lfname);
    Srv_Free(D_IN_SRAM, file);

    return res;
}


/*!
************************************************************************************************************************
* Function Fsal_DiskGetfree
* @brief calculate disk all free memory
* @param uint8_t *pdrv
* @param uint32_t *total, uint32_t *free
* @returns FSAL_FRES
* @note
* @author Lews Hammond
* @date 2019-7-18
************************************************************************************************************************
*/

FSAL_FRES Fsal_DiskGetfree(uint8_t *pdrv, uint32_t *total, uint32_t *pFree)
{
    FSAL_FATFS *fs1 = NULL;
    FSAL_DWORD fre_clust=0;
    FSAL_DWORD fre_sect=0;
    FSAL_DWORD tot_sect=0;
    FSAL_FRES res = FR_OK;

    if((pdrv == NULL)
       || (total == NULL)
       || (pFree == NULL))
    {
        return FR_INVALID_PARAMETER;
    }

    res = D_FSAL_GET_FREE((const TCHAR*)pdrv,&fre_clust,&fs1);

    tot_sect = (fs1->n_fatent-2) * fs1->csize;  //get all sector number
    fre_sect = fre_clust * fs1->csize;          //get free sector number
#if _MAX_SS!=512        //if sector isn`t 512 then covert 512 
    tot_sect *= fs1->ssize/512;
    fre_sect *= fs1->ssize/512;
#endif
    *total = tot_sect >> 1; //unit: KB
    *pFree = fre_sect >> 1; //unit: KB

    return res;
}

/*!
************************************************************************************************************************
* Function Fsal_Time2Str
* @brief get system time convert to string
* @param FSAL_CHAR ch[]: 21 byte
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-18
************************************************************************************************************************
*/

void Fsal_Time2Str(FSAL_CHAR ch[])
{
    RtcTime_t tTim = {0};
    uint8_t cnt = 0;

    Hal_RtcGetTime(&tTim);
    ch[cnt] = '\n';//new line
    cnt++;
    /* year convert to string */
    ch[cnt] = (FSAL_CHAR)(((tTim.rtcYear / 1000) % 10) + '0');
    cnt++;
    ch[cnt] = (FSAL_CHAR)(((tTim.rtcYear / 100) % 10) + '0');
    cnt++;
    ch[cnt] = (FSAL_CHAR)(((tTim.rtcYear / 10) % 10) + '0');
    cnt++;
    ch[cnt] = (FSAL_CHAR)(((tTim.rtcYear / 1) % 10) + '0');
    cnt++;
    ch[cnt] = '-';
    cnt++;
    /* month convert to string */
    ch[cnt] = (FSAL_CHAR)(((tTim.rtcMon / 10) % 10) + '0');
    cnt++;
    ch[cnt] = (FSAL_CHAR)(((tTim.rtcMon / 1) % 10) + '0');
    cnt++;
    ch[cnt] = '-';
    cnt++;
    /* day convert to string */
    ch[cnt] = (FSAL_CHAR)(((tTim.rtcDay / 10) % 10) + '0');
    cnt++;
    ch[cnt] = (FSAL_CHAR)(((tTim.rtcDay / 1) % 10) + '0');
    cnt++;
    ch[cnt] = ' ';
    cnt++;
    /* hour convert to string */
    ch[cnt] = (FSAL_CHAR)(((tTim.rtcHour / 10) % 10) + '0');
    cnt++;
    ch[cnt] = (FSAL_CHAR)(((tTim.rtcHour / 1) % 10) + '0');
    cnt++;
    ch[cnt] = ':';
    cnt++;
    /* min convert to string */
    ch[cnt] = (FSAL_CHAR)(((tTim.rtcMin / 10) % 10) + '0');
    cnt++;
    ch[cnt] = (FSAL_CHAR)(((tTim.rtcMin / 1) % 10) + '0');
    cnt++;
    ch[cnt] = ':';
    cnt++;
    /* sec convert to string */
    ch[cnt] = (FSAL_CHAR)(((tTim.rtcSec / 10) % 10) + '0');
    cnt++;
    ch[cnt] = (FSAL_CHAR)(((tTim.rtcSec / 1) % 10) + '0');
    cnt++;
    ch[cnt] = '\0';
//  cnt++;
}

