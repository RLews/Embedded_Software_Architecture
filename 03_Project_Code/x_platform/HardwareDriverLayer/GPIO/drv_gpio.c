/*!
************************************************************************************************************************
* @file drv_gpio.c
* @details mcu gpio驱动
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/



#include "drv_gpio.h"

static const GpioConfig_t GpioConfigArry[EN_ALL_GPIO_NUM] = {
	D_USED_GPIO_CONFIG
};

static StdBoolean_t GpioInitFinish = D_STD_FALSE;

/*!
************************************************************************************************************************
* Function Drv_GpioInit
* @brief 初始化gpio
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_GpioInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0};
	uint8_t i = 0;
	const GpioConfig_t *pIOConfig = GpioConfigArry;

	for (i = 0; i < (uint8_t)EN_ALL_GPIO_NUM; i++)
	{
		RCC_APB2PeriphClockCmd(pIOConfig[i].gpioPeriphClock, ENABLE);
		GPIO_InitStructure.GPIO_Pin = pIOConfig[i].gpioPin;
		GPIO_InitStructure.GPIO_Mode = pIOConfig[i].gpioMode;
		GPIO_InitStructure.GPIO_Speed = pIOConfig[i].gpioSpd;
		GPIO_Init(pIOConfig[i].gpioGruop, &GPIO_InitStructure);
		if (pIOConfig[i].initIOSta == EN_GPIO_HIGH)
		{
			GPIO_SetBits(pIOConfig[i].gpioGruop, pIOConfig[i].gpioPin);
		}
		else if (pIOConfig[i].initIOSta == EN_GPIO_LOW)
		{
			GPIO_ResetBits(pIOConfig[i].gpioGruop, pIOConfig[i].gpioPin);
		}
		else
		{/* do nothing */}
	}

	GpioInitFinish = D_STD_TRUE;
}


/*!
************************************************************************************************************************
* Function Drv_GetGpioInitSta
* @brief 获取gpio初始化状态
* @param void
* @param void
* @returns stdBoolean_t：是否完成初始化
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

StdBoolean_t Drv_GetGpioInitSta(void)
{
	return GpioInitFinish;
}


/*!
************************************************************************************************************************
* Function Drv_GpioNameOut
* @brief 指定io输出
* @param GpioName_t name：端口命名
* @param GpioState_t sta：输出状态
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Drv_GpioNameOut(GpioName_t name, GpioState_t sta)
{
	const GpioConfig_t *pIOConfig = GpioConfigArry;
	
	if (pIOConfig[name].initIOSta == EN_GPIO_INPUT)
	{
		return ;/* exception */
	}

	if (sta == EN_GPIO_HIGH)
	{
		GPIO_SetBits(pIOConfig[name].gpioGruop, pIOConfig[name].gpioPin);
	}
	else if (sta == EN_GPIO_LOW)
	{
		GPIO_ResetBits(pIOConfig[name].gpioGruop, pIOConfig[name].gpioPin);
	}
	else
	{
		
	}
}

/*!
************************************************************************************************************************
* Function Drv_GpioNameIn
* @brief 读取指定io的状态
* @param GpioName_t name：指定端口
* @param void
* @returns gpioState_t：端口状态
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

GpioState_t Drv_GpioNameIn(GpioName_t name)
{
	const GpioConfig_t *pIOConfig = GpioConfigArry;
	GpioState_t sta = EN_GPIO_LOW;

	if (pIOConfig[name].initIOSta != EN_GPIO_INPUT)
	{
		return EN_GPIO_ERR;/* exception */
	}

	sta = (GpioState_t)GPIO_ReadInputDataBit(pIOConfig[name].gpioGruop, pIOConfig[name].gpioPin);

	return sta;
}

