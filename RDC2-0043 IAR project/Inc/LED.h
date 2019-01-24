/*
********************************************************************************
* COPYRIGHT(c) ��� ���� � ��ϻ, 2018
* 
* ����������� ����������� ��������������� �� �������� ���� ����� (as is).
* ��� ��������������� �������� ������ �����������.
********************************************************************************
*/


#ifndef __LED_H
#define __LED_H


#include "RDC2_0043_board.h"


//������
#define       LED_TIMER                    TIM16
#define       LED_TIMER_ENR                APB2ENR
#define       LED_TIMER_CLK_EN             RCC_APB2ENR_TIM16EN
#define       LED_TIMER_PSC                3999

#define       LED_TIMER_AF                 2

#define       LED_TIMER_INPUT_CLK          ((uint32_t)48000000)



void LED_Init();

void LED_ON();

void LED_OFF();

void LED_ONwithFreq(uint8_t Frequency);


#endif //__LED_H