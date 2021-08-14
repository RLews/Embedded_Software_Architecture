/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#include "srv_memory.h"
//#include "usbdisk.h"	/* Example: Header file of existing USB MSD control module */
//#include "atadrive.h"	/* Example: Header file of existing ATA harddisk control module */
//#include "sdcard.h"	/* Example: Header file of existing MMC/SDC contorl module */


///* Definitions of physical drive number for each drive */
//#define ATA		0	/* Example: Map ATA harddisk to physical drive 0 */
//#define MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
//#define USB		2	/* Example: Map USB MSD to physical drive 2 */
#define SD_CARD		0	//


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = RES_ERROR;
	uint8_t dat = 0;

	switch (pdrv) {
		case SD_CARD:
			stat = (DSTATUS)Hal_SDCardInit();
			if (stat != RES_OK)//STM32 SPI的bug,在sd卡操作失败的时候如果不执行下面的语句,可能导致SPI读写异常
			{
				D_SET_SD_CARD_LOW_SPD_MODE();
				(void)D_SD_CARD_WR_BYTE_FUNC(0xFF, &dat);//provide external 8 clock
				D_SET_SD_CARD_HIGH_SPD_MODE();
			}
			break;			
			
		default:
			stat = RES_ERROR;
			break;
	}
	
	return stat;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res = RES_ERROR;
	uint8_t dat;
	
	if (count == 0)
	{
		return RES_PARERR;//count cann`t is 0
	}
	
	switch (pdrv) {
		case SD_CARD:
			res = (DRESULT)Hal_SDCardReadDisk(buff,sector,count);
			if (res != RES_OK)
			{
				D_SET_SD_CARD_LOW_SPD_MODE();
				(void)D_SD_CARD_WR_BYTE_FUNC(0xFF, &dat);//provide external 8 clock
				D_SET_SD_CARD_HIGH_SPD_MODE();
			}
			break;
			
		default: 
			res = RES_ERROR;
			break;
	}
	
	return res;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT result = RES_ERROR;

	if (0 == count)
	{
		return RES_PARERR;//count cann`t is 0
	}
	
	switch (pdrv) {
		case SD_CARD:
			result = (DRESULT)Hal_SDCardWriteDisk((uint8_t*)buff,sector,count);
			break;
			
		default: 
			result = RES_ERROR;
			break;
	}

	return result;	 

}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res = RES_ERROR;

	switch (pdrv) {
		case SD_CARD:
			switch (cmd)
			{
				case CTRL_SYNC:
					D_SD_CARD_SPI_CS_SELECT();
					if (Drv_SDCardWaitReady() == EN_SD_OPT_OK)
					{
						res = RES_OK;
					}
					else
					{
						res = RES_ERROR;
					}
					D_SD_CARD_SPI_CS_CANCEL();
					break;
					
				case GET_SECTOR_SIZE:
					*(WORD*)buff = 512;
					res = RES_OK;
					break;
					
				case GET_BLOCK_SIZE:
					*(WORD*)buff = 8;
					res = RES_OK;
					break;
					
				case GET_SECTOR_COUNT:
					(void)Hal_SDCardGetSectorNum((uint32_t *)buff);
					res = RES_OK;
					break;
					
				default:
					res = RES_PARERR;
					break;
			}
			break;
					
		default:
			res = RES_PARERR;
			break;
	}

	return res;
}
#endif

//get time
/* User defined function to give a current time to fatfs module      */
/* 31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */                                                                                                                                                                                                                                          
/* 15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */                                                                                                                                                                                                                                                
DWORD get_fattime (void)
{
	DWORD time = 0;
	RtcTime_t sysTim = {0};

	Hal_RtcGetTime(&sysTim);
	sysTim.rtcYear = (sysTim.rtcYear >= 1980) ? (sysTim.rtcYear - 1980) : (0);
	time |= (DWORD)(sysTim.rtcYear << 25);
	time |= (DWORD)(sysTim.rtcMon << 21);
	time |= (DWORD)(sysTim.rtcDay << 16);
	time |= (DWORD)(sysTim.rtcHour << 11);
	time |= (DWORD)(sysTim.rtcMin << 5);
	time |= (sysTim.rtcSec / 2);
	
	return time;
}			 


//malloc memory
void *ff_memalloc (UINT size)			
{
	return (void*)Srv_Malloc(D_EX_SRAM, size);
}

//free memory
void ff_memfree (void* mf)		 
{
	Srv_Free(D_EX_SRAM, mf);
}

