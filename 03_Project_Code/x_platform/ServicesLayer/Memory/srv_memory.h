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
/*! @brief �Ƿ�ʹ���Զ��嶯̬�ڴ������� */
#define USER_MEMORY_MANAGE_ENABLE       D_STD_DISABLE

#else

#include "platforms.h"
/*! @brief �Ƿ�ʹ���Զ��嶯̬�ڴ������� */
#define USER_MEMORY_MANAGE_ENABLE       D_STD_DISABLE

#endif

#define D_IN_SRAM   0U  //�ڲ��ڴ��
#define D_EX_SRAM   1U  //�ⲿ�ڴ��

#if (USER_MEMORY_MANAGE_ENABLE == D_STD_ENABLE)

//mem1�ڴ�����趨.mem1��ȫ�����ڲ�SRAM����
#define MEM1_BLOCK_SIZE         32U                                 //�ڴ���СΪ32�ֽ�
#define MEM1_MAX_SIZE           (4U * 1024U)                        //�������ڴ�
#define MEM1_ALLOC_TABLE_SIZE   (MEM1_MAX_SIZE / MEM1_BLOCK_SIZE)   //�ڴ���С

//mem2�ڴ�����趨.mem2���ڴ�ش����ⲿSRAM����,�����Ĵ����ڲ�SRAM����
#define MEM2_BLOCK_SIZE         32U                                 //�ڴ���СΪ32�ֽ�
#define MEM2_MAX_SIZE           (680U * 1024U)                      //�������ڴ�         total 1M
#define MEM2_ALLOC_TABLE_SIZE   (MEM2_MAX_SIZE / MEM2_BLOCK_SIZE)   //�ڴ���С


//�ڴ���������
struct _m_mallco_dev
{
    void (*init)(u8);                   //��ʼ��
    u8(*perused)(u8);                   //�ڴ�ʹ����
    u8  *membase[2];                    //�ڴ�� ����2��������ڴ�
    u16 *memmap[2];                     //�ڴ����״̬��
    u8  memrdy[2];                      //�ڴ�����Ƿ����
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


