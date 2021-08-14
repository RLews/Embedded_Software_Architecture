/*!
************************************************************************************************************************
* @file drv_rtc.c
* @details rtc����
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/


#include "drv_rtc.h"


static void Drv_RtcDelay(uint32_t cnt);
static void Drv_RtcNvicInit(void);

/*!
************************************************************************************************************************
* Function Drv_RtcInit
* @brief RTC��ʼ��
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_RtcInit(void)
{
	uint8_t temp = 0;
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//ʹ��PWR��BKP����ʱ��   
	PWR_BackupAccessCmd(ENABLE);	//ʹ�ܺ󱸼Ĵ������� 
	
	if (BKP_ReadBackupRegister(BKP_DR1) != D_RTC_BACKUP_REG_DEFAULT_VAL)		//��ָ���ĺ󱸼Ĵ����ж�������:��������д���ָ�����ݲ����
	{	 			
		BKP_DeInit();	//��λ�������� 	
		RCC_LSEConfig(RCC_LSE_ON);	//�����ⲿ���پ���(LSE),ʹ��������پ���
		
		do {
			temp++;
			Drv_RtcDelay(10);
			if (temp >= 250U)
			{
				break;
			}
		}while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);	//���ָ����RCC��־λ�������,�ȴ����پ������
		
		if(temp >= 250U)
		{
			RCC_RTCCLKConfig(RCC_RTCCLKSource_HSE_Div128);
		}
		else
		{
			RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);		//����RTCʱ��(RTCCLK),ѡ��LSE��ΪRTCʱ��    
		}
		
		RCC_RTCCLKCmd(ENABLE);	//ʹ��RTCʱ��  
		RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
		RTC_WaitForSynchro();		//�ȴ�RTC�Ĵ���ͬ��  
		D_DRV_ENABLE_RTC_SEC_INT();		//ʹ��RTC���ж�
		RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
		RTC_EnterConfigMode();/// ��������	
		if (temp>=250U)
		{
			RTC_SetPrescaler(62500-1);
		}
		else
		{
			RTC_SetPrescaler(32767); //����RTCԤ��Ƶ��ֵ
		}
		
		RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
		Drv_RtcSetCount(D_RTC_DEFAULT_TIME_COUNTER);  //����ʱ��	
		RTC_ExitConfigMode(); //�˳�����ģʽ  
		BKP_WriteBackupRegister(BKP_DR1, D_RTC_BACKUP_REG_DEFAULT_VAL);	//��ָ���ĺ󱸼Ĵ�����д���û���������
	}
	else//ϵͳ������ʱ
	{
		RTC_WaitForSynchro();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
		D_DRV_ENABLE_RTC_SEC_INT();	//ʹ��RTC���ж�
		RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
	}
	
	Drv_RtcNvicInit();
}

/*!
************************************************************************************************************************
* Function Drv_RtcDelay
* @brief ����rtcʱ��Ҫ����ʱ
* @param uint32_t cnt����ʱ����
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static void Drv_RtcDelay(uint32_t cnt)
{
	uint32_t dly = 0;
	uint32_t i = 0;

	for (i = 0; i < cnt; i++)
	{
		dly = 0xFFUL;
		do{
			dly--;
		}while (dly != 0);
	}
}

/*!
************************************************************************************************************************
* Function Drv_RtcNvicInit
* @brief RTC�жϳ�ʼ��
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static void Drv_RtcNvicInit(void)
{
	NVIC_InitTypeDef NVIC_InitStructure = (NVIC_InitTypeDef){0};
	
	NVIC_InitStructure.NVIC_IRQChannel = (uint8_t)RTC_IRQn;		//RTCȫ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//��ռ���ȼ�1λ,�����ȼ�3λ
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	//��ռ���ȼ�0λ,�����ȼ�4λ
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//ʹ�ܸ�ͨ���ж�
	NVIC_Init(&NVIC_InitStructure);		//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}

/*!
************************************************************************************************************************
* Function Drv_RtcSetCount
* @brief ����rtcʱ��
* @param uint32_t secCnt�����õ������ֵ
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_RtcSetCount(uint32_t secCnt)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//ʹ��PWR��BKP����ʱ��  
	PWR_BackupAccessCmd(ENABLE);	//ʹ��RTC�ͺ󱸼Ĵ������� 
	RTC_SetCounter(secCnt);	//����RTC��������ֵ

	RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������  	
}

/*!
************************************************************************************************************************
* Function Drv_RtcGetCount
* @brief ��ȡrtc����ֵ
* @param void
* @param void
* @returns uint32_t��rtc����ֵ
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

uint32_t Drv_RtcGetCount(void)
{
	uint32_t count = 0;

	count = RTC->CNTH;
	count <<= 16;
	count += RTC->CNTL;

	return count;
}

/*!
************************************************************************************************************************
* Function Drv_RtcIsSecInt
* @brief �ж��Ƿ�Ϊrtc�����ж�
* @param void
* @param void
* @returns stdBoolean_t���Ƿ������ж�
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

StdBoolean_t Drv_RtcIsSecInt(void)
{
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
	{
		return D_STD_TRUE;
	}
	else
	{
		return D_STD_FALSE;
	}
}

/*!
************************************************************************************************************************
* Function Drv_RtcIsrHandle
* @brief rtc�жϴ���
* @param void
* @param void
* @returns void
* @note rtc�ж���ʹ��
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_RtcIsrHandle(void)
{
	RTC_ClearITPendingBit(RTC_IT_SEC|RTC_IT_OW);		//�������ж�
	RTC_WaitForLastTask();	
}



