/*
********************************************************************************
* COPYRIGHT(c) ��� ���� � ��ϻ, 2018
* 
* ����������� ����������� ��������������� �� �������� ���� ����� (as is).
* ��� ��������������� �������� ������ �����������.
********************************************************************************
*/


#ifndef __ADC_H
#define __ADC_H


#include "RDC2_0043_board.h"



//��� (DMA)
#define       DMA_FOR_ADC                  DMA1
#define       DMA_FOR_ADC_ENR              AHBENR
#define       DMA_FOR_ADC_CLK_EN           RCC_AHBENR_DMAEN
#define       DMA_CNL_FOR_ADC              DMA1_Channel1
#define       DMA_CNL_FOR_ADC_IRQ          DMA1_Channel1_IRQn

#define       ADC_CHANNELS_COUNT           1

#define       ADC_MAX_VALUE                4095


void ADC_Init();

uint16_t ADC_GetData();


#endif //__ADC_H


