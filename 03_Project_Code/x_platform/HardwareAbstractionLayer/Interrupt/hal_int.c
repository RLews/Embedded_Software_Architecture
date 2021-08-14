/*!
************************************************************************************************************************
* @file hal_int.c
* @details
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/



#include "hal_int.h"

static void Hal_SysIntConfig(void);
static void Hal_SysIntHandle(SysIntIsr_t isrId);
static void Hal_ExcptionHandle(void);

static FaultRecordFunc SysFaultFunc = D_HAL_INT_NULL;
static volatile SysIntIsr_t SysIntId = EN_ALL_SYS_ISR_NUM;
static SysISRFunc SysIntVectTbl[EN_ALL_SYS_ISR_NUM] = {D_HAL_INT_NULL};

/*!
************************************************************************************************************************
* Function Hal_SysIntConfig
* @brief 配置系统中断
* @param void
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static void Hal_SysIntConfig(void)
{
    //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

/*!
************************************************************************************************************************
* Function Hal_SysIntInit
* @brief mcu interrupt handler functoin initial
* @param void
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Hal_SysIntInit(void)
{
    uint8_t i = 0;

    Hal_SysIntConfig();

    for(i = 0; i < (uint8_t)EN_ALL_SYS_ISR_NUM; i++)
    {
        Hal_SysISRSet((SysIntIsr_t)i, Hal_ExcptionHandle);
    }
}

/*!
************************************************************************************************************************
* Function Hal_SysISRSet
* @brief set mcu interrupt handler functoin set
* @param SysIntIsr_t isrId. interrupt identifier
* @param SysISRFunc isrFunc. interrupt handler function pointer
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Hal_SysISRSet(SysIntIsr_t isrId, SysISRFunc isrFunc)
{
    D_OSAL_ALLOC_CRITICAL_SR();

    if(isrId < EN_ALL_SYS_ISR_NUM)
    {
        D_OSAL_ENTER_CRITICAL();
        SysIntVectTbl[isrId] = isrFunc;
        D_OSAL_EXIT_CRITICAL();
    }
}


/*!
************************************************************************************************************************
* Function Hal_ExcptionHandle
* @brief mcu interrupt exception handler.
* @param void
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static void Hal_ExcptionHandle(void)
{
    uint32_t Ts = 0;
    //uint8_t id = (uint8_t)(SysIntId + '0');

    /* 1. record ecu register and hardfault state */ /* 2. save to non-volatile memory */
    if(SysFaultFunc != D_HAL_INT_NULL)
    {
        SysFaultFunc();
    }

    /* 3. disable interrupt and wait watchdog reset */
    D_DISABLE_ALL_INTERRUPT();

    while(1)
    {
        if(Osal_DiffTsToUsec(Ts) >= D_SYS_EXCEPTION_OUTPUT_PERIOD)
        {
            Ts = Osal_GetCurTs();
            /* TODO: Do something */
        }
    }
}

/*!
************************************************************************************************************************
* Function Hal_SetFaultFunc
* @brief set fault record function
* @param FaultRecordFunc pFunc：function point
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Hal_SetFaultFunc(FaultRecordFunc pFunc)
{
    D_OSAL_ALLOC_CRITICAL_SR();
    D_OSAL_ENTER_CRITICAL();
    SysFaultFunc = pFunc;
    D_OSAL_EXIT_CRITICAL();
}

/*!
************************************************************************************************************************
* Function Hal_GetCurIntID
* @brief get current interrupt id
* @param void
* @param void
* @returns uint8_t：interrupt identified
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

uint8_t Hal_GetCurIntID(void)
{
    return (uint8_t)SysIntId;
}

/*!
************************************************************************************************************************
* Function Hal_SysIntHandle
* @brief mcu system interrupt function handler
* @param SysIntIsr_t isrId：isr id
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static void Hal_SysIntHandle(SysIntIsr_t isrId)
{
    SysISRFunc isr = D_HAL_INT_NULL;
    D_OSAL_ALLOC_CRITICAL_SR();

    D_OSAL_ENTER_CRITICAL();
    D_OSAL_INT_ENTER();/* Tell the OS that we are starting an ISR            */
    D_OSAL_EXIT_CRITICAL();

    SysIntId = isrId;//update current interrupt id

    if(isrId < EN_ALL_SYS_ISR_NUM)
    {
        isr = SysIntVectTbl[isrId];

        if(isr != D_HAL_INT_NULL)
        {
            isr();
        }
    }

    D_OSAL_INT_EXIT();/* Tell the OS that we are leaving the ISR            */
}

/*!
************************************************************************************************************************
* Function xxx_Handler
* @brief all mcu system interrupt function.
* @param void
* @param void
* @returns void
* @note
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void NMI_Handler(void)
{
    Hal_SysIntHandle(EN_NMI_ISR);
}
void HardFault_Handler(void)
{
    Hal_SysIntHandle(EN_HARD_FAULT_ISR);
}
void MemManage_Handler(void)
{
    Hal_SysIntHandle(EN_MEM_MANAGE_ISR);
}
void BusFault_Handler(void)
{
    Hal_SysIntHandle(EN_BUS_FAULT_ISR);
}
void UsageFault_Handler(void)
{
    Hal_SysIntHandle(EN_SUAGE_FAULT_ISR);
}
void SVC_Handler(void)
{
    Hal_SysIntHandle(EN_SVC_ISR);
}
void DebugMon_Handler(void)
{
    Hal_SysIntHandle(EN_DEBUG_MON_ISR);
}
void SysTick_Handler(void)
{
    Hal_SysIntHandle(EN_SYS_TICK_ISR);
}
void WWDG_IRQHandler(void)
{
    Hal_SysIntHandle(EN_WWDG_ISR);
}
void PVD_IRQHandler(void)
{
    Hal_SysIntHandle(EN_PVD_ISR);
}
void TAMPER_IRQHandler(void)
{
    Hal_SysIntHandle(EN_TAMPER_ISR);
}
void RTC_IRQHandler(void)
{
    Hal_SysIntHandle(EN_RTC_ISR);
}
void FLASH_IRQHandler(void)
{
    Hal_SysIntHandle(EN_FLASH_ISR);
}
void RCC_IRQHandler(void)
{
    Hal_SysIntHandle(EN_RCC_ISR);
}
void EXTI0_IRQHandler(void)
{
    Hal_SysIntHandle(EN_EXTI0_ISR);
}
void EXTI1_IRQHandler(void)
{
    Hal_SysIntHandle(EN_EXTI1_ISR);
}
void EXTI2_IRQHandler(void)
{
    Hal_SysIntHandle(EN_EXTI2_ISR);
}
void EXTI3_IRQHandler(void)
{
    Hal_SysIntHandle(EN_EXTI3_ISR);
}
void EXTI4_IRQHandler(void)
{
    Hal_SysIntHandle(EN_EXTI4_ISR);
}
void DMA1_Channel1_IRQHandler(void)
{
    Hal_SysIntHandle(EN_DMA1_CH1_ISR);
}
void DMA1_Channel2_IRQHandler(void)
{
    Hal_SysIntHandle(EN_DMA1_CH2_ISR);
}
void DMA1_Channel3_IRQHandler(void)
{
    Hal_SysIntHandle(EN_DMA1_CH3_ISR);
}
void DMA1_Channel4_IRQHandler(void)
{
    Hal_SysIntHandle(EN_DMA1_CH4_ISR);
}
void DMA1_Channel5_IRQHandler(void)
{
    Hal_SysIntHandle(EN_DMA1_CH5_ISR);
}
void DMA1_Channel6_IRQHandler(void)
{
    Hal_SysIntHandle(EN_DMA1_CH6_ISR);
}
void DMA1_Channel7_IRQHandler(void)
{
    Hal_SysIntHandle(EN_DMA1_CH7_ISR);
}
void ADC1_2_IRQHandler(void)
{
    Hal_SysIntHandle(EN_ADC1_2_ISR);
}
void USB_HP_CAN1_TX_IRQHandler(void)
{
    Hal_SysIntHandle(EN_USB_HP_CAN1_TX_ISR);
}
void USB_LP_CAN1_RX0_IRQHandler(void)
{
    Hal_SysIntHandle(EN_USB_LP_CAN1_RX0_ISR);
}
void CAN1_RX1_IRQHandler(void)
{
    Hal_SysIntHandle(EN_CAN1_RX1_ISR);
}
void CAN1_SCE_IRQHandler(void)
{
    Hal_SysIntHandle(EN_CAN1_SCE_ISR);
}
void EXTI9_5_IRQHandler(void)
{
    Hal_SysIntHandle(EN_EXTI9_5_ISR);
}
void TIM1_BRK_IRQHandler(void)
{
    Hal_SysIntHandle(EN_TIM1_BRK_ISR);
}
void TIM1_UP_IRQHandler(void)
{
    Hal_SysIntHandle(EN_TIM1_UP_ISR);
}
void TIM1_TRG_COM_IRQHandler(void)
{
    Hal_SysIntHandle(EN_TIM1_TRG_COM_ISR);
}
void TIM1_CC_IRQHandler(void)
{
    Hal_SysIntHandle(EN_TIM1_CC_ISR);
}
void TIM2_IRQHandler(void)
{
    Hal_SysIntHandle(EN_TIM2_ISR);
}
void TIM3_IRQHandler(void)
{
    Hal_SysIntHandle(EN_TIM3_ISR);
}
void TIM4_IRQHandler(void)
{
    Hal_SysIntHandle(EN_TIM4_ISR);
}
void I2C1_EV_IRQHandler(void)
{
    Hal_SysIntHandle(EN_I2C1_EV_ISR);
}
void I2C1_ER_IRQHandler(void)
{
    Hal_SysIntHandle(EN_I2C1_ER_ISR);
}
void I2C2_EV_IRQHandler(void)
{
    Hal_SysIntHandle(EN_I2C2_EV_ISR);
}
void I2C2_ER_IRQHandler(void)
{
    Hal_SysIntHandle(EN_I2C2_ER_ISR);
}
void SPI1_IRQHandler(void)
{
    Hal_SysIntHandle(EN_SPI1_ISR);
}
void SPI2_IRQHandler(void)
{
    Hal_SysIntHandle(EN_SPI2_ISR);
}
void USART1_IRQHandler(void)
{
    Hal_SysIntHandle(EN_USART1_ISR);
}
void USART2_IRQHandler(void)
{
    Hal_SysIntHandle(EN_USART2_ISR);
}
void USART3_IRQHandler(void)
{
    Hal_SysIntHandle(EN_USART3_ISR);
}
void EXTI15_10_IRQHandler(void)
{
    Hal_SysIntHandle(EN_EXTI15_10_ISR);
}
void RTCAlarm_IRQHandler(void)
{
    Hal_SysIntHandle(EN_RTCAlarm_ISR);
}
void USBWakeUp_IRQHandler(void)
{
    Hal_SysIntHandle(EN_USBWakeUp_ISR);
}
void TIM8_BRK_IRQHandler(void)
{
    Hal_SysIntHandle(EN_TIM8_BRK_ISR);
}
void TIM8_UP_IRQHandler(void)
{
    Hal_SysIntHandle(EN_TIM8_UP_ISR);
}
void TIM8_TRG_COM_IRQHandler(void)
{
    Hal_SysIntHandle(EN_TIM8_TRG_COM_ISR);
}
void TIM8_CC_IRQHandler(void)
{
    Hal_SysIntHandle(EN_TIM8_CC_ISR);
}
void ADC3_IRQHandler(void)
{
    Hal_SysIntHandle(EN_ADC3_ISR);
}
void FSMC_IRQHandler(void)
{
    Hal_SysIntHandle(EN_FSMC_ISR);
}
void SDIO_IRQHandler(void)
{
    Hal_SysIntHandle(EN_SDIO_ISR);
}
void TIM5_IRQHandler(void)
{
    Hal_SysIntHandle(EN_TIM5_ISR);
}
void SPI3_IRQHandler(void)
{
    Hal_SysIntHandle(EN_SPI3_ISR);
}
void UART4_IRQHandler(void)
{
    Hal_SysIntHandle(EN_UART4_ISR);
}
void UART5_IRQHandler(void)
{
    Hal_SysIntHandle(EN_UART5_ISR);
}
void TIM6_IRQHandler(void)
{
    Hal_SysIntHandle(EN_TIM6_ISR);
}
void TIM7_IRQHandler(void)
{
    Hal_SysIntHandle(EN_TIM7_ISR);
}
void DMA2_Channel1_IRQHandler(void)
{
    Hal_SysIntHandle(EN_DMA2_CH1_ISR);
}
void DMA2_Channel2_IRQHandler(void)
{
    Hal_SysIntHandle(EN_DMA2_CH2_ISR);
}
void DMA2_Channel3_IRQHandler(void)
{
    Hal_SysIntHandle(EN_DMA2_CH3_ISR);
}
void DMA2_Channel4_5_IRQHandler(void)
{
    Hal_SysIntHandle(EN_DMA2_CH4_5_ISR);
}


