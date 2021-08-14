/*!
************************************************************************************************************************
* @file drv_sram_pub.h
* @brief
* @details
* @author Lews Hammond
* @date 2021-8-14
************************************************************************************************************************
*/

#ifndef DRV_SRAM_PUB_H
#define DRV_SRAM_PUB_H

#include "platforms.h"

/*
************************************************************************************************************************
* Sram Interface
************************************************************************************************************************
*/
/*! @brief 使用NOR/SRAM的 Bank1.sector3,地址位HADDR[27,26]=10
           对IS61LV25616/IS62WV25616,地址线范围为A0~A17
           对IS61LV51216/IS62WV51216,地址线范围为A0~A18
*/
#define Bank1_SRAM3_ADDR    ((u32)(0x68000000))

void Drv_SramInit(void);
void Drv_SramWrite(uint8_t *pBuf, uint32_t addr, uint32_t size);
void Drv_SramRead(uint8_t *pBuf, uint32_t addr, uint32_t size);





#endif

