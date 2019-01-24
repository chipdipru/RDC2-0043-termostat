/*
********************************************************************************
* COPYRIGHT(c) ��� ���� � ��ϻ, 2018
* 
* ����������� ����������� ��������������� �� �������� ���� ����� (as is).
* ��� ��������������� �������� ������ �����������.
********************************************************************************
*/


#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "RDC2_0043_board.h"


//������
#define       DISPLAY_TIMER                TIM3
#define       DISPLAY_TIMER_ENR            APB1ENR
#define       DISPLAY_TIMER_CLK_EN         RCC_APB1ENR_TIM3EN
#define       DISPLAY_TIMER_IRQ            TIM3_IRQn


//�������
#define       CHARACTER_0                  ((1 << SEGMENT_1_PIN) | (1 << SEGMENT_2_PIN) | (1 << SEGMENT_3_PIN) | \
                                            (1 << SEGMENT_4_PIN) | (1 << SEGMENT_5_PIN) | (1 << SEGMENT_6_PIN))
#define       CHARACTER_1                  ((1 << SEGMENT_2_PIN) | (1 << SEGMENT_3_PIN))
#define       CHARACTER_2                  ((1 << SEGMENT_1_PIN) | (1 << SEGMENT_2_PIN) | (1 << SEGMENT_4_PIN) | \
                                            (1 << SEGMENT_5_PIN) | (1 << SEGMENT_7_PIN))
#define       CHARACTER_3                  ((1 << SEGMENT_1_PIN) | (1 << SEGMENT_2_PIN) | (1 << SEGMENT_3_PIN) | \
                                            (1 << SEGMENT_4_PIN) | (1 << SEGMENT_7_PIN))
#define       CHARACTER_4                  ((1 << SEGMENT_2_PIN) | (1 << SEGMENT_3_PIN) | \
                                            (1 << SEGMENT_6_PIN) | (1 << SEGMENT_7_PIN))
#define       CHARACTER_5                  ((1 << SEGMENT_1_PIN) | (1 << SEGMENT_3_PIN) | (1 << SEGMENT_4_PIN) | \
                                            (1 << SEGMENT_6_PIN) | (1 << SEGMENT_7_PIN))
#define       CHARACTER_6                  ((1 << SEGMENT_1_PIN) | (1 << SEGMENT_3_PIN) | (1 << SEGMENT_4_PIN) | \
                                            (1 << SEGMENT_5_PIN) | (1 << SEGMENT_6_PIN) | (1 << SEGMENT_7_PIN))
#define       CHARACTER_7                  ((1 << SEGMENT_1_PIN) | (1 << SEGMENT_2_PIN) | (1 << SEGMENT_3_PIN))
#define       CHARACTER_8                  ((1 << SEGMENT_1_PIN) | (1 << SEGMENT_2_PIN) | (1 << SEGMENT_3_PIN) | (1 << SEGMENT_4_PIN) | \
                                            (1 << SEGMENT_5_PIN) | (1 << SEGMENT_6_PIN) | (1 << SEGMENT_7_PIN))
#define       CHARACTER_9                  ((1 << SEGMENT_1_PIN) | (1 << SEGMENT_2_PIN) | (1 << SEGMENT_3_PIN) | \
                                            (1 << SEGMENT_4_PIN) | (1 << SEGMENT_6_PIN) | (1 << SEGMENT_7_PIN))
#define       CHARACTER_SPACE              0
#define       CHARACTER_DP                 (1 << SEGMENT_8_PIN)
#define       CHARACTER_h                  ((1 << SEGMENT_3_PIN) | (1 << SEGMENT_5_PIN) | \
                                            (1 << SEGMENT_6_PIN) | (1 << SEGMENT_7_PIN))

#define       CHARACTER_LINE               (1 << SEGMENT_7_PIN)

#define       CHARACTER_d                  ((1 << SEGMENT_2_PIN) | (1 << SEGMENT_3_PIN) | (1 << SEGMENT_4_PIN) | \
                                            (1 << SEGMENT_5_PIN) | (1 << SEGMENT_7_PIN))

#define       CHARACTER_8_DP               (CHARACTER_8 | CHARACTER_DP)

#define       CHAR_h_INDEX                 10
#define       CHAR_LINE_INDEX              11
#define       CHAR_d_INDEX                 12
#define       CHAR_SPACE_INDEX             13
#define       CHAR_8_DP_INDEX              14

#define       DISPLAY_IS_OFF               0
#define       DISPLAY_IS_ON_TIME           1
#define       DISPLAY_IS_ON_EVENT          2

#define       POINT_OFF                    0
#define       POINT_ON                     1

#define       POINT_ALWAYS_ON_DURATION     0xFF


extern const uint16_t CHARACTERS[];
extern const uint8_t DIGITS_PINS[];

typedef struct
{
  uint8_t Position; //������� ����� �� ����������
  uint8_t Duration; //������������ ����� ���� (��� ��� ����)
  uint8_t Phase;    //���� (��� ��� ����)
  uint8_t Counter;  //������� ����
  
} DPointType;


void DISPLAY_TIMER_ISR(void);

void Display_SetValue(uint8_t *DisplayData);

void Display_Update(int16_t NewValue);

void Display_Init(uint8_t PointPos, uint8_t PointDuration);

void Display_PointSet(uint8_t PointPos, uint8_t PointDuration);

void Display_ON();

void Display_OFF();

uint8_t Display_State();

void Display_SetState(uint8_t NewState);


#endif //__DISPLAY_H


