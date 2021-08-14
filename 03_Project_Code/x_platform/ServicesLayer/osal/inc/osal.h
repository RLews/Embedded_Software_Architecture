/*!
************************************************************************************************************************
* @file osal.h
* @details 
* @author Lews Hammond
* @date 2019-7-18
************************************************************************************************************************
*/



#ifndef OSAL_H
#define OSAL_H



#include  <cpu.h>
#include  <lib_def.h>
#include  <lib_ascii.h>
#include  <lib_math.h>
#include  <lib_mem.h>
#include  <lib_str.h>
#include  <os.h>

#include "bsp_os.h"
#include "hal_rtc_pub.h"


/*
************************************************************************************************************************
* uC OS III  Interface
************************************************************************************************************************
*/
/* uC/OS name type abstract */
typedef CPU_CHAR OSAL_CHAR;
typedef CPU_BOOLEAN OSAL_BOOL;
typedef CPU_INT32U OSAL_UINT32;
typedef CPU_INT16U OSAL_UINT16;
typedef CPU_INT08U OSAL_UINT8;

typedef OS_TASK_PTR OSAL_TASK_FUNC_PTR;
typedef OS_TCB OSAL_TCB;
typedef OS_PRIO OSAL_PRIO;
typedef CPU_STK OSAL_CPU_STACK;
typedef CPU_STK_SIZE OSAL_CPU_STK_SIZE;
typedef OS_MSG_QTY OSAL_MSG_QTY;
typedef OS_TICK OSAL_TICK;
typedef OS_OPT OSAL_OPT;
typedef OS_ERR OSAL_ERROR;
typedef OS_SEM OSAL_SEM;
typedef OS_SEM_CTR OSAL_SEM_CTR;
typedef OS_TMR OSAL_TMR;
typedef OS_TMR_CALLBACK_PTR OSAL_TMR_CALLBACK_PTR;


#define D_OSAL_OPT_TASK_NONE		OS_OPT_TASK_NONE/* No option selected                                 */
#define D_OSAL_OPT_TASK_STK_CHK 	OS_OPT_TASK_STK_CHK/* Enable stack checking for the task                 */
#define D_OSAL_OPT_TASK_STK_CLR 	OS_OPT_TASK_STK_CLR/* Clear the stack when the task is create            */
#define D_OSAL_OPT_TASK_SAVE_FP	 	OS_OPT_TASK_SAVE_FP/* Save the contents of any floating-point registers  */
#define D_OSAL_OPT_TASK_NO_TLS 		OS_OPT_TASK_NO_TLS/* Specifies the task DOES NOT require TLS support    */

#define D_OSAL_OPT_TMR_ONE_SHORT	OS_OPT_TMR_ONE_SHOT
#define D_OSAL_OPT_TMR_PERIODIC		OS_OPT_TMR_PERIODIC

/* uC/OS function */
#define D_OSAL_CREATE_TASK_FUNC(pTcb,  \
								pName, \
								pTask, \
								pArg,  \
								prio,  \
								pStk,  \
								stkLmt, \
								stkSize, \
								qSize, \
								timQuanta, \
								pExt, \
								opt, \
								pErr) \
					OSTaskCreate(pTcb,  \
								pName, \
								pTask, \
								pArg,  \
								prio,  \
								pStk,  \
								stkLmt, \
								stkSize, \
								qSize, \
								timQuanta, \
								pExt, \
								opt, \
								pErr)
								
#define D_OSAL_START_SCHE(pErr)		OSStart(pErr)

#define D_OSAL_DISABLE_ALL_INT()	CPU_IntDis()
#define D_OSAL_ENABLE_ALL_INT()		CPU_IntEn()

#define D_OSAL_TASK_SUSPEND_FUNC(pTcb,pErr)		OS_TaskSuspend(pTcb, pErr)
#define D_OSAL_TASK_DEL_FUNC(pTcb, pErr)		OSTaskDel(pTcb, pErr)
#define D_OSAL_GET_OS_VERSION(pErr)				OSVersion(pErr)

#define D_OSAL_ALLOC_CRITICAL_SR()	CPU_SR_ALLOC()
#define D_OSAL_ENTER_CRITICAL()		CPU_CRITICAL_ENTER()
#define D_OSAL_EXIT_CRITICAL()		CPU_CRITICAL_EXIT()

#define D_OSAL_INT_ENTER()		OSIntEnter()
#define D_OSAL_INT_EXIT()		OSIntExit()

void Osal_OsInit(void);

void Osal_DelayMs(OSAL_UINT32 ms);

void Osal_StartTaskConfig(void);

OSAL_BOOL Osal_SemCreate(OSAL_SEM *pSem, OSAL_SEM_CTR semVal, OSAL_CHAR *name);

OSAL_BOOL Osal_SemWait(OSAL_SEM *pSem, OSAL_UINT32 ms);

OSAL_BOOL Osal_SemRead(OSAL_SEM * pSem);

OSAL_BOOL Osal_SemPost(OSAL_SEM *pSem);

OSAL_BOOL Osal_SemSet(OSAL_SEM *pSem, OSAL_SEM_CTR cnt);

OSAL_BOOL Osal_TaskStkChk(OSAL_TCB *tcb, OSAL_CPU_STK_SIZE *pFree, OSAL_CPU_STK_SIZE *used);

OSAL_BOOL Osal_TmrCreate(OSAL_TMR *pTmr, OSAL_CHAR *name, OSAL_TICK tick, OSAL_OPT opt, OSAL_TMR_CALLBACK_PTR callback);

OSAL_BOOL Osal_TmrStart(OSAL_TMR *pTmr);

OSAL_BOOL Osal_TmrStop(OSAL_TMR *pTmr, OSAL_OPT opt);

uint32_t Osal_GetCurTs(void);

uint32_t Osal_DiffTsToUsec(uint32_t lastTs);


/*
************************************************************************************************************************
* FatFS  Interface
************************************************************************************************************************
*/
#include "ff.h"
#include "diskio.h"

typedef FRESULT FSAL_FRES;
typedef FATFS FSAL_FATFS;
typedef FILINFO FSAL_FILINFO;
typedef FIL FSAL_FIL;
typedef DIR	FSAL_DIR;
typedef TCHAR FSAL_CHAR;
typedef BYTE FSAL_BYTE;
typedef UINT FSAL_UINT;
typedef DWORD FSAL_DWORD;

#define D_FSAL_TIME_STRING_SIZE								21
#define D_OS_VERSION_STRING_SIZE							6
#define D_FSAL_MAX_ANAYSIS_DIR_SIZE							100

#define D_FSAL_MOUNT(pFs,path,opt)							f_mount(pFs,path,opt)
#define D_FSAL_WRITE(pFil,buf,bwt,bw)						f_write(pFil,buf,bwt,bw)
#define D_FSAL_READ(fp, buff, btr, br)						f_read(fp, buff, btr, br)
#define D_FSAL_CLOSE(pFil)									f_close(pFil)
#define D_FSAL_GET_FREE(path,nclst,fatfs)					f_getfree(path,nclst,fatfs)
#define D_FSAL_MKFS(path, sfd, au)							f_mkfs(path, sfd, au)
#define D_FSAL_PRINTF(pFil,ch,hex)							f_printf(pFil,ch,hex)
#define D_FSAL_LSEEK(pFil, ofs)								f_lseek(pFil, ofs)
#define D_FSAL_READ_DIR(dir,fno)							f_readdir(dir,fno)
#define D_FSAL_MK_DIR(dir)									f_mkdir(dir)
#define D_FSAL_OPEN_DIR(dir, path)							f_opendir(dir, path)
#define D_FSAL_CLOSE_DIR(dir)								f_closedir(dir)
#define D_FSAL_UNLINK(file)									f_unlink(file)

typedef enum FS_DIR_ANAY_STA_T
{
	EN_DIR_ANAYSIS_OK = 0,
	EN_DIR_NO_EXIST,
	EN_DIR_PARAMTER_ERR
}FsDirAnaySta_t;


FSAL_FRES Fsal_OpenR(FSAL_FIL *pFil, const FSAL_CHAR *pCh);
FSAL_FRES Fsal_OpenW(FSAL_FIL *pFil, const FSAL_CHAR *pPath, const FSAL_CHAR *pDir, uint32_t dirLen);
FSAL_FRES Fsal_DiskGetfree(uint8_t *pdrv, uint32_t *total, uint32_t *pFree);
void Fsal_Time2Str(FSAL_CHAR ch[]);
FSAL_FRES Fsal_MkDir(const FSAL_CHAR *pDir, uint32_t len);
FSAL_FRES Fsal_DelDir(const FSAL_CHAR *path);


#endif

