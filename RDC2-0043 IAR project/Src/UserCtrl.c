/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2018
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/


#include "UserCtrl.h"


void (*KeyStateChanged)(uint8_t, uint8_t);
void (*EnableChanged)(uint8_t);

KeyType Keys[KEYS_COUNT];


void DEBOUNCE_TIMER_ISR(void)
{
  DEBOUNCE_TIMER->SR &= ~TIM_SR_UIF;
  DEBOUNCE_TIMER->CR1 &= ~TIM_CR1_CEN;
  
  uint8_t KeyFlag = 0;
  for(uint8_t key = 0; key < KEYS_COUNT; key++)
  {
    if (Keys[key].State == EVENT_PENDING)     
    {
      if (GetInputLevel(Keys[key].GPIO, Keys[key].Pin) == Keys[key].Level)
      {
        if (key == ENABLE_IN)
          EnableChanged(Keys[key].Level);
        else if (KeyFlag == 0)
        {
          KeyFlag = key;
          KeyStateChanged(key, Keys[key].Level);
        }
      }
      
      Keys[key].State = 0;
      EXTI->IMR |= 1 << Keys[key].Pin;
    }
  }
    
  DEBOUNCE_TIMER->CNT = 0;
  RCC->DEBOUNCE_TIMER_ENR &= ~DEBOUNCE_TIMER_CLK_EN;
}
//------------------------------------------------------------------------------
void KEYS_ISR(void)
{
  uint8_t ActiveKey;
  
  for(uint8_t i = 0; i < KEYS_COUNT; i++)
  {
    if (((EXTI->PR & (1 << Keys[i].Pin)) == (1 << Keys[i].Pin)) && (i != ENABLE_IN))
    {
      ActiveKey = i;
      break;
    }
  }
  
  EXTI->PR |= 1 << Keys[ActiveKey].Pin;
  
  if ((DEBOUNCE_TIMER->CR1 & TIM_CR1_CEN) != TIM_CR1_CEN)
  {    
    EXTI->IMR &= ~(1 << Keys[ActiveKey].Pin);
    
    Keys[ActiveKey].Level = GetInputLevel(Keys[ActiveKey].GPIO, Keys[ActiveKey].Pin);
    Keys[ActiveKey].State = EVENT_PENDING;
    
    RCC->DEBOUNCE_TIMER_ENR |= DEBOUNCE_TIMER_CLK_EN;
    DEBOUNCE_TIMER->CR1 |= TIM_CR1_CEN;
  }
}
//------------------------------------------------------------------------------
void ENABLE_IN_ISR(void)
{
  EXTI->IMR &= ~(1 << Keys[ENABLE_IN].Pin);
  EXTI->PR |= 1 << Keys[ENABLE_IN].Pin;
  
  Keys[ENABLE_IN].Level = GetInputLevel(Keys[ENABLE_IN].GPIO, Keys[ENABLE_IN].Pin);
  Keys[ENABLE_IN].State = EVENT_PENDING;
  
  if ((DEBOUNCE_TIMER->CR1 & TIM_CR1_CEN) != TIM_CR1_CEN)
  {
    RCC->DEBOUNCE_TIMER_ENR |= DEBOUNCE_TIMER_CLK_EN;
    DEBOUNCE_TIMER->CR1 |= TIM_CR1_CEN;
  }  
  else
  {
    DEBOUNCE_TIMER->CR1 &= ~TIM_CR1_CEN;
    DEBOUNCE_TIMER->CNT = 0;
    DEBOUNCE_TIMER->SR = 0;
    DEBOUNCE_TIMER->CR1 |= TIM_CR1_CEN;
  }
}
//------------------------------------------------------------------------------
void UserCtrl_Init(void (*KeysCallback)(uint8_t, uint8_t), void (*EnableChangedCallback)(uint8_t))
{   
  Keys[MENU_KEY].Pin = MENU_KEY_PIN;
  Keys[MENU_KEY].GPIO = MENU_KEY_GPIO;
  Keys[ON_OFF_KEY].Pin = ON_OFF_KEY_PIN;
  Keys[ON_OFF_KEY].GPIO = ON_OFF_KEY_GPIO;
  Keys[ENABLE_IN].Pin = ENABLE_IN_PIN;
  Keys[ENABLE_IN].GPIO = ENABLE_IN_GPIO;
  Keys[MINUS_KEY].Pin = MINUS_KEY_PIN;
  Keys[MINUS_KEY].GPIO = MINUS_KEY_GPIO;
  Keys[PLUS_KEY].Pin = PLUS_KEY_PIN;
  Keys[PLUS_KEY].GPIO = PLUS_KEY_GPIO;
  
  for(uint8_t i = 0; i < KEYS_COUNT; i++)
    Keys[i].State = 0;
  
  //таймер, период  мс
  RCC->DEBOUNCE_TIMER_ENR |= DEBOUNCE_TIMER_CLK_EN;
  DEBOUNCE_TIMER->PSC = DEBOUNCE_TIMER_PSC;
  DEBOUNCE_TIMER->ARR = DEBOUNCE_TIMER_ARR;
  DEBOUNCE_TIMER->DIER = TIM_DIER_UIE;
  RCC->DEBOUNCE_TIMER_ENR &= ~DEBOUNCE_TIMER_CLK_EN;
  NVIC_EnableIRQ(DEBOUNCE_TIMER_IRQ);
  NVIC_SetPriority(DEBOUNCE_TIMER_IRQ, KEYS_PRIORITY);
  
  KeyStateChanged = KeysCallback;
  EnableChanged = EnableChangedCallback;
  
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;
  SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PF | SYSCFG_EXTICR1_EXTI1_PF;
  PLUS_KEY_GPIO->MODER &= ~((3 << (2 * PLUS_KEY_PIN)) | (3 << (2 * MINUS_KEY_PIN)));
  PLUS_KEY_GPIO->PUPDR = 0;
  
  EXTI->FTSR |= (1 << MENU_KEY_PIN) | (1 << ON_OFF_KEY_PIN) | (1 << ENABLE_IN_PIN) | \
                (1 << MINUS_KEY_PIN) | (1 << PLUS_KEY_PIN);
  
  EXTI->RTSR |= (1 << MENU_KEY_PIN)  | (1 << ENABLE_IN_PIN) | \
                (1 << MINUS_KEY_PIN) | (1 << PLUS_KEY_PIN);
  
  NVIC_EnableIRQ(MENU_ON_OFF_KEYS_IRQ);
  NVIC_SetPriority(MENU_ON_OFF_KEYS_IRQ, KEYS_PRIORITY);
  NVIC_EnableIRQ(ENABLE_IN_IRQ);
  NVIC_SetPriority(ENABLE_IN_IRQ, ENABLE_PIN_PRIORITY);
  NVIC_EnableIRQ(PLUS_MINUS_KEYS_IRQ);
  NVIC_SetPriority(PLUS_MINUS_KEYS_IRQ, KEYS_PRIORITY);
    
  EXTI->IMR |= (1 << MENU_KEY_PIN) | (1 << ON_OFF_KEY_PIN) | (1 << ENABLE_IN_PIN) | \
               (1 << MINUS_KEY_PIN) | (1 << PLUS_KEY_PIN);
}
//------------------------------------------------------------------------------
uint8_t GetInputLevel(GPIO_TypeDef* InGPIO, uint8_t InPin)
{
  return ((InGPIO->IDR & (1 << InPin)) >> InPin);
}
//------------------------------------------------------------------------------
void UserCtrlResume()
{
  EXTI->IMR |= (1 << MENU_KEY_PIN)  | (1 << ENABLE_IN_PIN) | \
               (1 << MINUS_KEY_PIN) | (1 << PLUS_KEY_PIN);
}
//------------------------------------------------------------------------------
void UserCtrlPause()
{
  EXTI->IMR &= ~((1 << MENU_KEY_PIN) | (1 << ENABLE_IN_PIN) | \
                (1 << MINUS_KEY_PIN) | (1 << PLUS_KEY_PIN));
}
//------------------------------------------------------------------------------
void UserCtrlDisable()
{
  EXTI->IMR &= ~((1 << MENU_KEY_PIN) | (1 << ON_OFF_KEY_PIN) | (1 << ENABLE_IN_PIN) | \
                (1 << MINUS_KEY_PIN) | (1 << PLUS_KEY_PIN));
  
  RCC->DEBOUNCE_TIMER_ENR &= ~DEBOUNCE_TIMER_CLK_EN;
}




