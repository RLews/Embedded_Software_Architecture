/*!
************************************************************************************************************************
* @file srv_memory.h
* @brief
* @details
* @author Lews Hammond
* @date 2019-8-9
************************************************************************************************************************
*/

#ifndef SRV_MEMORY_H
#define SRV_MEMORY_H

#include "rte_config.h"

#if defined(D_RTE_PLATFORM_MCU)

#include "hal_sram_pub.h"
/*! @brief 是否使用自定义动态内存管理机制 */
#define USER_MEMORY_MANAGE_ENABLE       D_STD_DISABLE

#else

#include "platforms.h"
/*! @brief 是否使用自定义动态内存管理机制 */
#define USER_MEMORY_MANAGE_ENABLE       D_STD_DISABLE

#endif

#define D_IN_SRAM   0U  //内部内存池
#define D_EX_SRAM   1U  //外部内存池

#if (USER_MEMORY_MANAGE_ENABLE == D_STD_ENABLE)

//mem1内存参数设定.mem1完全处于内部SRAM里面
#define MEM1_BLOCK_SIZE         32U                                 //内存块大小为32字节
#define MEM1_MAX_SIZE           (4U * 1024U)                        //最大管理内存
#define MEM1_ALLOC_TABLE_SIZE   (MEM1_MAX_SIZE / MEM1_BLOCK_SIZE)   //内存表大小

//mem2内存参数设定.mem2的内存池处于外部SRAM里面,其他的处于内部SRAM里面
#define MEM2_BLOCK_SIZE         32U                                 //内存块大小为32字节
#define MEM2_MAX_SIZE           (680U * 1024U)                      //最大管理内存         total 1M
#define MEM2_ALLOC_TABLE_SIZE   (MEM2_MAX_SIZE / MEM2_BLOCK_SIZE)   //内存表大小


//内存管理控制器
struct _m_mallco_dev
{
    void (*init)(u8);                   //初始化
    u8(*perused)(u8);                   //内存使用率
    u8  *membase[2];                    //内存池 管理2个区域的内存
    u16 *memmap[2];                     //内存管理状态表
    u8  memrdy[2];                      //内存管理是否就绪
};



#endif

#ifdef __cplusplus
extern "C" {
#endif


void Srv_MemInit(uint8_t memx);

void Srv_MemCopy(void *des, const void *src, uint32_t len);

void Srv_MemSet(void *s,u8 c,u32 count);

uint8_t Srv_MemPerused(uint8_t memx);

void * Srv_Malloc(uint8_t memx, uint32_t size);

void * Srv_Realloc(uint8_t memx, void *ptr, uint32_t size);

void Srv_Free(uint8_t memx, void *ptr);

#ifdef __cplusplus
}
#endif


#endif


