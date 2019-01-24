/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2018
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/


#ifndef __THERMISTOR_H
#define __THERMISTOR_H


#include "RDC2_0043_board.h"



#define       T_NOMINAL_C                  25
#define       T_0_K                        ((float) 273.15)
#define       T_NOMINAL_K                  ((float) (T_NOMINAL_C + T_0_K))



typedef struct
{
  uint32_t Rnom;
  uint16_t Bconst;
  float Rcurrent;
  
} ThermType;




void Therm_Init(uint32_t Rnom, uint16_t Bconst);

float Therm_GetRcurFromADC(float ADCValue);

float Therm_GetTempFromADC(float ADCValue);

float Therm_GetRcurFromTemp(float Temp);

uint16_t Therm_GetADCFromTemp(float Temp);


#endif //__THERMISTOR_H