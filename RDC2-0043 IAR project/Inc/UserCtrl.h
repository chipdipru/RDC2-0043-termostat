/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2018
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/



#ifndef __USER_CTRL_H
#define __USER_CTRL_H


#include "RDC2_0043_board.h"


//таймер
#define       DEBOUNCE_TIMER               TIM14
#define       DEBOUNCE_TIMER_ENR           APB1ENR
#define       DEBOUNCE_TIMER_CLK_EN        RCC_APB1ENR_TIM14EN
#define       DEBOUNCE_TIMER_IRQ           TIM14_IRQn
#define       DEBOUNCE_TIMER_PSC           1999
#define       DEBOUNCE_TIMER_ARR           1599

#define       EVENT_PENDING                (1 << 0)

#define       KEY_PRESSED                  0
#define       KEY_RELEASED                 1


typedef struct
{
  volatile uint8_t State;
  uint8_t Pin;
  GPIO_TypeDef* GPIO;
  volatile uint8_t Level;  
  
} KeyType;

enum KeysNames
{
  MENU_KEY,
  ON_OFF_KEY,
  ENABLE_IN,
  MINUS_KEY,
  PLUS_KEY, 
};

void DEBOUNCE_TIMER_ISR(void);

void KEYS_ISR(void);

void ENABLE_IN_ISR(void);

void UserCtrl_Init(void (*KeysCallback)(uint8_t, uint8_t), void (*EnableChangedCallback)(uint8_t));

uint8_t GetInputLevel(GPIO_TypeDef* InGPIO, uint8_t InPin);

void UserCtrlResume();

void UserCtrlPause();

void UserCtrlDisable();


#endif //__USER_CTRL_H


