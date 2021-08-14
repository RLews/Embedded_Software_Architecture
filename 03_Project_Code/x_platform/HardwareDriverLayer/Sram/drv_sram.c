/*!
************************************************************************************************************************
* @file drv_sram.c
* @brief sram driver
* @details
* @author Lews Hammond
* @date 2019-8-9
************************************************************************************************************************
*/

#include "drv_sram.h"

#if (EXTERN_SRAM_ENABLE == D_STD_ENABLE)


/*!
************************************************************************************************************************
* @brief SRAM initial
* @param[in] void
* @param[out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2019-8-9
************************************************************************************************************************
*/

void Drv_SramInit(void)
{
    FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef  readWriteTiming;
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG,ENABLE);

    GPIO_InitStructure.GPIO_Pin = 0xFF33;               //PORTD复用推挽输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;          //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);


    GPIO_InitStructure.GPIO_Pin = 0xFF83;               //PORTE复用推挽输出
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = 0xF03F;               //PORTD复用推挽输出
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = 0x043F;               //PORTD复用推挽输出
    GPIO_Init(GPIOG, &GPIO_InitStructure);

    readWriteTiming.FSMC_AddressSetupTime = 0x00;    //地址建立时间（ADDSET）为1个HCLK 1/36M=27ns
    readWriteTiming.FSMC_AddressHoldTime = 0x00;     //地址保持时间（ADDHLD）模式A未用到
    readWriteTiming.FSMC_DataSetupTime = 0x03;       //数据保持时间（DATAST）为3个HCLK 4/72M=55ns(对EM的SRAM芯片)
    readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
    readWriteTiming.FSMC_CLKDivision = 0x00;
    readWriteTiming.FSMC_DataLatency = 0x00;
    readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;     //模式A

    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM3;//  这里我们使用NE3 ，也就对应BTCR[4],[5]。
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//存储器数据宽度为16bit
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable; //存储器写使能
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable; // 读写使用相同的时序
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &readWriteTiming; //读写同样时序

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //初始化FSMC配置

    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3, ENABLE);  // 使能BANK3
}

/*!
************************************************************************************************************************
* @brief Sram write data
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond
* @date 2019-8-9
************************************************************************************************************************
*/

void Drv_SramWrite(uint8_t *pBuf, uint32_t addr, uint32_t size)
{
    uint32_t i = 0;

    for(i = 0; i < size; i++)
    {
        *(vu8*)(Bank1_SRAM3_ADDR + addr) = *pBuf;
        addr += 2;//这里需要加2，是因为STM32的FSMC地址右移一位对其.加2相当于加1.
        pBuf++;
    }
}

/*!
************************************************************************************************************************
* @brief Sram read data
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond
* @date 2019-8-9
************************************************************************************************************************
*/

void Drv_SramRead(uint8_t *pBuf, uint32_t addr, uint32_t size)
{
    uint32_t i = 0;

    for(i = 0; i < size; i++)
    {
        *pBuf++ = *(vu8*)(Bank1_SRAM3_ADDR + addr);
        addr += 2;//这里需要加2，是因为STM32的FSMC地址右移一位对其.加2相当于加1.
    }
}

#endif


