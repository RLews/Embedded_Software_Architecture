/*!
************************************************************************************************************************
* @file srv_algor.h
* @brief 
* @details 
* @author Lews Hammond
* @date 2019-8-17
************************************************************************************************************************
*/

#ifndef SRV_ALGOR_H
#define SRV_ALGOR_H




#include "platforms.h"





uint16_t Srv_GetRand16(void);

uint16_t Srv_FirstOrderFilter(uint16_t curDat, uint16_t lastDat, uint16_t filterFactor);




#endif

