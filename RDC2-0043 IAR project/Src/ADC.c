/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2018
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/


#include "ADC.h"


static uint16_t ADCData;


//------------------------------------------------------------------------------
void ADC_Init()
{
  ADC_GPIO->MODER |= 3 << (2 * ADC_PIN);
  
  //ПДП (DMA)
  RCC->DMA_FOR_ADC_ENR |= DMA_FOR_ADC_CLK_EN;
  DMA_CNL_FOR_ADC->CPAR = (uint32_t) (&(ADC_USED->DR));
  DMA_CNL_FOR_ADC->CMAR = (uint32_t)(&ADCData);
  DMA_CNL_FOR_ADC->CNDTR = ADC_CHANNELS_COUNT;
  DMA_CNL_FOR_ADC->CCR = DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0 | DMA_CCR_CIRC;
  DMA_CNL_FOR_ADC->CCR |= DMA_CCR_EN;
  
  RCC->ADC_ENR |= ADC_CLK_EN;  
  ADC_USED->CR |= ADC_CR_ADCAL;
  while(((ADC_USED->CR) & ADC_CR_ADCAL) == ADC_CR_ADCAL);
  
  ADC_USED->CFGR2 = ADC_CFGR2_CKMODE_1;
  ADC_USED->SMPR = ADC_SMPR_SMP_1 | ADC_SMPR_SMP_0;
  ADC_USED->CHSELR = ADC_CHANNEL;
  ADC_USED->CFGR1 = ADC_CFGR1_CONT | ADC_CFGR1_DMAEN | ADC_CFGR1_DMACFG;
  ADC_USED->CR |= ADC_CR_ADEN;
  while(((ADC_USED->ISR) & ADC_ISR_ADRDY) != ADC_ISR_ADRDY);
    
  ADC_USED->CR |= ADC_CR_ADSTART;
}
//------------------------------------------------------------------------------
uint16_t ADC_GetData()
{
  return ADCData;
}


