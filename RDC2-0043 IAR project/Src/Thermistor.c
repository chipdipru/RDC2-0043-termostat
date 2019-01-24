/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2018
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/


#include "Thermistor.h"
#include <math.h>
#include "ADC.h"


ThermType Thermistor;



//------------------------------------------------------------------------------
void Therm_Init(uint32_t Rnom, uint16_t Bconst)
{
  Thermistor.Rnom = Rnom;
  Thermistor.Bconst = Bconst;
}
//------------------------------------------------------------------------------
float Therm_GetRcurFromADC(float ADCValue)
{
  return ((float)SERIAL_RESISTANCE / ((float)ADC_MAX_VALUE / ADCValue - 1));
}
//------------------------------------------------------------------------------
float Therm_GetTempFromADC(float ADCValue)
{
  Thermistor.Rcurrent = Therm_GetRcurFromADC(ADCValue);
  float Temperature = 1 / (1 / T_NOMINAL_K + logf(Thermistor.Rcurrent / Thermistor.Rnom) / Thermistor.Bconst) - T_0_K;
  return Temperature;
}
//------------------------------------------------------------------------------
float Therm_GetRcurFromTemp(float Temp)
{
  return (Thermistor.Rnom * expf(Thermistor.Bconst * ((1 / (Temp + T_0_K)) - 1 / T_NOMINAL_K)));
}
//------------------------------------------------------------------------------
uint16_t Therm_GetADCFromTemp(float Temp)
{
  float Rtemp = Therm_GetRcurFromTemp(Temp);
  float ADCValue = (Rtemp * (float)ADC_MAX_VALUE) / ((float)(SERIAL_RESISTANCE + Rtemp));
  
  return ((uint16_t)ADCValue);
}


