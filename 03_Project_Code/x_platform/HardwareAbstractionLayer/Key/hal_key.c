/*!
************************************************************************************************************************
* @file hal_key.c
* @details 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/


#include "hal_key.h"

static KeyManage_t KeyManage[EN_KEY_ALL_TYPE] = {(StdBoolean_t)0};
static KeyShake_t KeyShake = {0};

static void Hal_KeyStateManage(uint8_t id);


/*!
************************************************************************************************************************
* Function Hal_KeyScan
* @brief 按键扫描
* @param void
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Hal_KeyScan(void)
{
	uint8_t i = 0;
	GpioName_t ioName = (GpioName_t)0;
	KeyShake_t *pShake = &KeyShake;

	for (i = 0; i < (uint8_t)EN_KEY_ALL_TYPE; i++)
	{
		ioName = (GpioName_t)(i + (uint8_t)EN_WIFI_KEY_IO);
		if (Drv_GpioNameIn(ioName) == EN_GPIO_LOW)
		{
			if (pShake->shakeBuf[i] < 255U)
			{
				pShake->shakeBuf[i]++;
			}
		}
		else
		{
			pShake->shakeBuf[i] = 0;
		}
		Hal_KeyStateManage(i);
	}
}

#if (D_ENABLE_KEY_DOUBLE_PRESS == D_STD_ON)
/*!
************************************************************************************************************************
* Function Hal_KeyStateManage
* @brief 按键状态管理，支持双击
* @param uint8_t id：按键id
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static void Hal_KeyStateManage(uint8_t id)
{
	KeyShake_t *pShake = &KeyShake;
	KeyManage_t *pKey = KeyManage;
	
	switch (pKey[id].keySta)
	{
		case EN_KEY_NONE:
			if (pShake->shakeBuf[id] >= D_KEY_PRESS_SHAKE_TIME)
			{
				pKey[id].keySta = EN_KEY_PRESS_DOWN;
				pShake->keyPrsTim[id] = Osal_GetCurTs();
			}
			break;
			
		case EN_KEY_PRESS_DOWN:
			if (pShake->shakeBuf[id] == 0)//release
			{
				pKey[id].keySta = EN_KEY_WAIT_PRESS_UP;
				pShake->keyPrsTim[id] = Osal_GetCurTs();
			}
			if (Osal_DiffTsToUsec(pShake->keyPrsTim[id]) >= D_KEY_REPEAT_TIME)
			{
				pKey[id].keySta = EN_KEY_REPEAT;
				pKey[id].newKeyFlg = D_STD_TRUE;
			}
			break;
			
		case EN_KEY_WAIT_PRESS_UP:
			if (Osal_DiffTsToUsec(pShake->keyPrsTim[id]) >= D_KEY_DOUBLE_PRESS_TIME)
			{
				pKey[id].keySta = EN_KEY_PRESS_UP;
				pKey[id].newKeyFlg = D_STD_TRUE;
			}
			if ((pShake->dblKeyLock[id] == D_STD_FALSE) && (pShake->shakeBuf[id] >= D_KEY_PRESS_SHAKE_TIME))
			{
				pKey[id].keySta = EN_KEY_DOUBLE_PRESS;
			}
			break;
			
		case EN_KEY_PRESS_UP:
			if (pKey[id].newKeyFlg == D_STD_FALSE)//up leyer handle completed
			{
				pKey[id].keySta = EN_KEY_NONE;
			}
			break;
			
		case EN_KEY_REPEAT:
			if (pShake->shakeBuf[id] == 0)//release
			{
				pKey[id].keySta = EN_KEY_NONE;//repeat none double press
			}
			break;
			
		case EN_KEY_DOUBLE_PRESS:			
			if (pShake->shakeBuf[id] == 0)//release
			{
				pKey[id].keySta = EN_KEY_DOUBLE_PRESS_UP;
				pKey[id].newKeyFlg = D_STD_TRUE;
			}
			break;

		case EN_KEY_DOUBLE_PRESS_UP:
			if (pKey[id].newKeyFlg == D_STD_FALSE)//up leyer handle completed
			{
				pKey[id].keySta = EN_KEY_NONE;
				pShake->dblKeyLock[id] = D_STD_TRUE;
				pShake->keydblPrsTim[id] = Osal_GetCurTs();
			}
			break;
		
		default: //exception
			break;
	}

	if ( (Osal_DiffTsToUsec(pShake->keydblPrsTim[id]) >= D_KEY_DOUBLE_PRESS_SPACE_TIME) 
	  && (pShake->dblKeyLock[id] == D_STD_TRUE) )
	{
		pShake->dblKeyLock[id] = D_STD_FALSE;
	}
}
#else

/*!
************************************************************************************************************************
* Function Hal_KeyStateManage
* @brief 按键状态管理
* @param uint8_t id：按键id
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

static void Hal_KeyStateManage(uint8_t id)
{
	KeyShake_t *pShake = &KeyShake;
	KeyManage_t *pKey = KeyManage;

	switch (pKey[id].keySta)
	{
		case EN_KEY_NONE:
			if (pShake->shakeBuf[id] >= D_KEY_PRESS_SHAKE_TIME)
			{
				pKey[id].keySta = EN_KEY_PRESS_DOWN;
				pShake->keyPrsTim[id] = Osal_GetCurTs();
			}
			break;
			
		case EN_KEY_PRESS_DOWN:
			if (pShake->shakeBuf[id] == 0)//release
			{
				pKey[id].keySta = EN_KEY_PRESS_UP;
				pKey[id].newKeyFlg = D_STD_TRUE;
			}
			if (Osal_DiffTsToUsec(pShake->keyPrsTim[id]) >= D_KEY_REPEAT_TIME)
			{
				pKey[id].keySta = EN_KEY_REPEAT;
				pKey[id].newKeyFlg = D_STD_TRUE;
			}
			break;

		case EN_KEY_PRESS_UP:
			if (pKey[id].newKeyFlg == D_STD_FALSE)
			{
				pKey[id].keySta = EN_KEY_NONE;
			}
			break;

		case EN_KEY_REPEAT:
			if (pShake->shakeBuf[id] == 0)//release
			{
				pKey[id].keySta = EN_KEY_NONE;
			}
			break;

		default:
			break;
	}
}

#endif

/*!
************************************************************************************************************************
* Function Hal_CheckNewKey
* @brief 检测是否有新按键状态
* @param uint8_t id：按键id
* @param void
* @returns stdBoolean_t：
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

StdBoolean_t Hal_CheckNewKey(uint8_t id)
{
	return KeyManage[id].newKeyFlg;
}

/*!
************************************************************************************************************************
* Function Hal_ClearNewKeyFlg
* @brief 清除新按键状态标志
* @param uint8_t id：按键id
* @param void
* @returns void
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

void Hal_ClearNewKeyFlg(uint8_t id)
{
	KeyManage[id].newKeyFlg = D_STD_FALSE;
}

/*!
************************************************************************************************************************
* Function Hal_GetKeySta
* @brief 获取按键状态
* @param uint8_t id：按键id
* @param void
* @returns keyState_t：按键状态
* @note 
* @author Lews Hammond
* @date 2019-7-17
************************************************************************************************************************
*/

KeyState_t Hal_GetKeySta(uint8_t id)
{
	return KeyManage[id].keySta;
}



