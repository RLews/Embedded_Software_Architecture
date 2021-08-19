/*!
************************************************************************************************************************
* @file hal_int_pub.h
* @brief
* @details
* @author Lews Hammond
* @date 2021-8-14
************************************************************************************************************************
*/

#ifndef HAL_INT_PUB_H
#define HAL_INT_PUB_H

#include "drv_int_pub.h"

#define D_HAL_INT_NULL      ((void *)0)


typedef void (*SysISRFunc)(void);
typedef void (*FaultRecordFunc)(void);


/*
************************************************************************************************************************
* Interrupt  Interface
************************************************************************************************************************
*/
typedef enum SYS_INT_ISR_T
{
    EN_NMI_ISR = 0,
    EN_HARD_FAULT_ISR,
    EN_MEM_MANAGE_ISR,
    EN_BUS_FAULT_ISR,
    EN_SUAGE_FAULT_ISR,
    EN_SVC_ISR,
    EN_DEBUG_MON_ISR,
    //EN_PENDSV_ISR,  this uC/OS manage 
    EN_SYS_TICK_ISR,
    EN_WWDG_ISR,
    EN_PVD_ISR,
    EN_TAMPER_ISR,
    EN_RTC_ISR,
    EN_FLASH_ISR,
    EN_RCC_ISR,
    EN_EXTI0_ISR,
    EN_EXTI1_ISR,
    EN_EXTI2_ISR,
    EN_EXTI3_ISR,
    EN_EXTI4_ISR,
    EN_DMA1_CH1_ISR,
    EN_DMA1_CH2_ISR,
    EN_DMA1_CH3_ISR,
    EN_DMA1_CH4_ISR,
    EN_DMA1_CH5_ISR,
    EN_DMA1_CH6_ISR,
    EN_DMA1_CH7_ISR,
    EN_ADC1_2_ISR,
    EN_USB_HP_CAN1_TX_ISR,
    EN_USB_LP_CAN1_RX0_ISR,
    EN_CAN1_RX1_ISR,
    EN_CAN1_SCE_ISR,
    EN_EXTI9_5_ISR,
    EN_TIM1_BRK_ISR,
    EN_TIM1_UP_ISR,
    EN_TIM1_TRG_COM_ISR,
    EN_TIM1_CC_ISR,
    EN_TIM2_ISR,
    EN_TIM3_ISR,
    EN_TIM4_ISR,
    EN_I2C1_EV_ISR,
    EN_I2C1_ER_ISR,
    EN_I2C2_EV_ISR,
    EN_I2C2_ER_ISR,
    EN_SPI1_ISR,
    EN_SPI2_ISR,
    EN_USART1_ISR,
    EN_USART2_ISR,
    EN_USART3_ISR,
    EN_EXTI15_10_ISR,
    EN_RTCAlarm_ISR,
    EN_USBWakeUp_ISR,
    EN_TIM8_BRK_ISR,
    EN_TIM8_UP_ISR,
    EN_TIM8_TRG_COM_ISR,
    EN_TIM8_CC_ISR,
    EN_ADC3_ISR,
    EN_FSMC_ISR,
    EN_SDIO_ISR,
    EN_TIM5_ISR,
    EN_SPI3_ISR,
    EN_UART4_ISR,
    EN_UART5_ISR,
    EN_TIM6_ISR,
    EN_TIM7_ISR,
    EN_DMA2_CH1_ISR,
    EN_DMA2_CH2_ISR,
    EN_DMA2_CH3_ISR,
    EN_DMA2_CH4_5_ISR,
    EN_ALL_SYS_ISR_NUM
} SysIntIsr_t;

void Hal_SysIntInit(void);
void Hal_SysISRSet(SysIntIsr_t isrId, SysISRFunc isrFunc);
uint8_t Hal_GetCurIntID(void);
void Hal_SetFaultFunc(FaultRecordFunc pFunc);





#endif

