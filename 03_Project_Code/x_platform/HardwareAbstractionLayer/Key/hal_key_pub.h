/*!
************************************************************************************************************************
* @file hal_key_pub.h
* @brief
* @details
* @author Lews Hammond
* @date 2021-8-14
************************************************************************************************************************
*/

#ifndef HAL_KEY_PUB_H
#define HAL_KEY_PUB_H

#include "drv_gpio_pub.h"

/*
************************************************************************************************************************
* Key Hardware Abstraction Layer Interface
************************************************************************************************************************
*/
typedef enum KEY_NAME_T
{
    EN_KEY_WIFI = 0,
    EN_KEY_ALL_TYPE
} KeyName_t;

typedef enum KEY_STATE_T
{
    EN_KEY_NONE = 0,
    EN_KEY_PRESS_DOWN,
    EN_KEY_WAIT_PRESS_UP,
    EN_KEY_PRESS_UP,
    EN_KEY_REPEAT,  //hold press
    EN_KEY_DOUBLE_PRESS,
    EN_KEY_DOUBLE_PRESS_UP,
    EN_KEY_ALL_STATE
} KeyState_t;

typedef struct KEY_MANAGE_T
{
    StdBoolean_t newKeyFlg;
    KeyState_t keySta;
} KeyManage_t;

void Hal_KeyScan(void);
StdBoolean_t Hal_CheckNewKey(uint8_t id);
void Hal_ClearNewKeyFlg(uint8_t id);
KeyState_t Hal_GetKeySta(uint8_t id);




#endif

