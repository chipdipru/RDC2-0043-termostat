/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2018
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/


#include "Output.h"


void (*Activate)(void);
void (*DeActivate)(void);


void Output_Init()
{
  OUTPUT_GPIO->MODER |= (1 << (2 * OUTPUT_PIN));
}
//------------------------------------------------------------------------------
void Output_SetActiveLevel(uint8_t ActiveLevel)
{
  if (ActiveLevel == 0)
  {
    Activate = Output_Low;
    DeActivate = Output_High;
  }
  
  else
  {
    Activate = Output_High;
    DeActivate = Output_Low;
  }
}
//------------------------------------------------------------------------------
void Output_High()
{
  OUTPUT_GPIO->ODR |= (1 << OUTPUT_PIN);
}
//------------------------------------------------------------------------------
void Output_Low()
{
  OUTPUT_GPIO->ODR &= ~(1 << OUTPUT_PIN);
}
//------------------------------------------------------------------------------
void Output_Activate()
{
  Activate();
}
//------------------------------------------------------------------------------
void Output_DeActivate()
{
  DeActivate();
}


