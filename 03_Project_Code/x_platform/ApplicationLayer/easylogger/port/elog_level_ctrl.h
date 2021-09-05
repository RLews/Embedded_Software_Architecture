/*!
************************************************************************************************************************
* @file elog_level_ctrl.h
* @brief 
* @details 
* @author Lews Hammond
* @date 2021-9-2
************************************************************************************************************************
*/

#ifndef ELOG_LEVEL_CTRL_H
#define ELOG_LEVEL_CTRL_H


#ifdef __cplusplus
extern "C" {
#endif

#include "rte.h"


void Elog_SetLevel(uint8_t lvl);

uint8_t Elog_GetLevel(void);

#define ELOG_A(...)                     do{ \
    if (Elog_GetLevel() >= ELOG_LVL_ASSERT) \
    {                                       \
        log_a(__VA_ARGS__);                 \
    }                                       \
}while (0)

#define ELOG_E(...)                     do{ \
    if (Elog_GetLevel() >= ELOG_LVL_ERROR)  \
    {                                       \
        log_e(__VA_ARGS__);                 \
    }                                       \
}while (0)

#define ELOG_W(...)                     do{ \
    if (Elog_GetLevel() >= ELOG_LVL_WARN)   \
    {                                       \
        log_w(__VA_ARGS__);                 \
    }                                       \
}while (0)

#define ELOG_I(...)                     do{ \
    if (Elog_GetLevel() >= ELOG_LVL_INFO)   \
    {                                       \
        log_i(__VA_ARGS__);                 \
    }                                       \
}while (0)

#define ELOG_D(...)                     do{ \
    if (Elog_GetLevel() >= ELOG_LVL_DEBUG)  \
    {                                       \
        log_d(__VA_ARGS__);                 \
    }                                       \
}while (0)

#define ELOG_V(...)                     do{ \
    if (Elog_GetLevel() >= ELOG_LVL_VERBOSE)\
    {                                       \
        log_v(__VA_ARGS__);                 \
    }                                       \
}while (0)




#ifdef __cplusplus
}
#endif




#endif

