/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2018
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/


#ifndef __OUTPUT_H
#define __OUTPUT_H

#include "RDC2_0043_board.h"


void Output_Init();

void Output_SetActiveLevel(uint8_t ActiveLevel);

void Output_High();

void Output_Low();

void Output_Activate();

void Output_DeActivate();


#endif //__OUTPUT_H