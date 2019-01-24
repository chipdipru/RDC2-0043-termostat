/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2018
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/




#ifndef __RDC2_0043_BOARD_H
#define __RDC2_0043_BOARD_H

#include "stm32f042x6.h"


//сегменты индикатора
#define       SEGMENTS_GPIO                GPIOA
#define       SEGMENT_1_PIN                7
#define       SEGMENT_2_PIN                6
#define       SEGMENT_3_PIN                3
#define       SEGMENT_4_PIN                1
#define       SEGMENT_5_PIN                5
#define       SEGMENT_6_PIN                8
#define       SEGMENT_7_PIN                9
#define       SEGMENT_8_PIN                4
#define       SEGMENTS_MASK                ((1 << SEGMENT_1_PIN) | (1 << SEGMENT_2_PIN) | (1 << SEGMENT_3_PIN) | (1 << SEGMENT_4_PIN) | \
                                            (1 << SEGMENT_5_PIN) | (1 << SEGMENT_6_PIN) | (1 << SEGMENT_7_PIN) | (1 << SEGMENT_8_PIN))

//разряды
#define       DIGITS_GPIO                  GPIOB
#define       DIGIT_1_PIN                  0
#define       DIGIT_2_PIN                  1
#define       DIGIT_3_PIN                  6
#define       DIGIT_4_PIN                  7
#define       DIGITS_MASK                  ((1 << DIGIT_1_PIN) | (1 << DIGIT_2_PIN) | (1 << DIGIT_3_PIN) | (1 << DIGIT_4_PIN))
#define       DIGITS_NUM                   4

//реле
#define       OUTPUT_GPIO                  GPIOA
#define       OUTPUT_PIN                   10

//светодиод
#define       LED_GPIO                     GPIOB
#define       LED_PIN                      8

//управление
#define       MENU_KEY_GPIO                GPIOF
#define       MENU_KEY_PIN                 0
#define       ON_OFF_KEY_GPIO              GPIOF
#define       ON_OFF_KEY_PIN               1
#define       MENU_ON_OFF_KEYS_IRQ         EXTI0_1_IRQn
#define       ENABLE_IN_GPIO               GPIOA
#define       ENABLE_IN_PIN                2
#define       ENABLE_IN_IRQ                EXTI2_3_IRQn
#define       MINUS_KEY_GPIO               GPIOA
#define       MINUS_KEY_PIN                13
#define       PLUS_KEY_GPIO                GPIOA
#define       PLUS_KEY_PIN                 14
#define       PLUS_MINUS_KEYS_IRQ          EXTI4_15_IRQn
#define       KEYS_COUNT                   5

//АЦП
#define       ADC_GPIO                     GPIOA
#define       ADC_PIN                      0
#define       ADC_USED                     ADC1
#define       ADC_ENR                      APB2ENR
#define       ADC_CLK_EN                   RCC_APB2ENR_ADCEN
#define       ADC_IRQ                      ADC1_IRQn
#define       ADC_CHANNEL                  ADC_CHSELR_CHSEL0

//SPI
#define       SPI_GPIO                     GPIOB
#define       SPI_PORT                     SPI1
#define       SPI_SCK_PIN                  3
#define       SPI_SCK_AF                   0
#define       SPI_MISO_PIN                 4
#define       SPI_MISO_AF                  0
#define       SPI_MOSI_PIN                 5
#define       SPI_MOSI_AF                  0
#define       SPI_NSS_GPIO                 GPIOA
#define       SPI_NSS_PIN                  15

//таймеры
#define       DATA_UPDATE_TIMER            TIM17
#define       DATA_UPDATE_TIMER_ENR        APB2ENR
#define       DATA_UPDATE_TIMER_CLK_EN     RCC_APB2ENR_TIM17EN
#define       DATA_UPDATE_TIMER_PSC        3999
#define       DATA_UPDATE_TIMER_ARR        599
#define       DATA_UPDATE_TIMER_IRQ        TIM17_IRQn

#define       KEY_EVENT_GEN_TIMER          TIM1
#define       KEY_EVENT_GEN_TIMER_ENR      APB2ENR
#define       KEY_EVENT_GEN_TIMER_CLK_EN   RCC_APB2ENR_TIM1EN
#define       KEY_EVENT_GEN_TIMER_PSC      3999
#define       KEY_EVENT_GEN_TIMER_ARR      2999
#define       KEY_EVENT_GEN_TIMER_IRQ      TIM1_BRK_UP_TRG_COM_IRQn

#define       PROTECTION_TIMER             TIM2
#define       PROTECTION_TIMER_ENR         APB1ENR
#define       PROTECTION_TIMER_CLK_EN      RCC_APB1ENR_TIM2EN
#define       PROTECTION_TIMER_PSC         (64000 - 1)
#define       PROTECTION_TIMER_ARR_MINUTE  45000
#define       PROTECTION_TIMER_IRQ         TIM2_IRQn

//приоритеты прерываний
#define       ENABLE_PIN_PRIORITY          0
#define       PROTECTION_PRIORITY          0
#define       KEYS_PRIORITY                1
#define       DISPLAY_PRIORITY             2
#define       DATA_UPDATE_PRIORITY         0
#define       KEY_EVENT_GEN_PRIORITY       (KEYS_PRIORITY + 1)

#define       SMA_SAMPLES                  8//16

#define       DATA_UPDATE_THRESHOLD        1.0

#define       MODE_HEAT                    0
#define       MODE_COOL                    1

#define       PROTECTION_DISABLED          0
#define       PROTECTION_ENABLED           1

#define       SERIAL_RESISTANCE            4700 //Ом

#define       MODE_DEFAULT                 MODE_HEAT
#define       ACTIVE_LEVEL_DEFAULT         1
#define       THERMISTOR_R_NOMINAL_DEFAULT 6800
#define       THERMISTOR_B_CONSTANT_DEFAULT 4200
#define       TEMP_DELTA_LOW_DEFAULT       0xFFFF
#define       TEMP_DELTA_HIGH_DEFAULT      0xFFFF
#define       TEMP_NOMINAL_DEFAULT         0xFFFF

#define       TEMP_LOWER                   0
#define       TEMP_HIGHER                  1


#define       STATE_SENSOR_FAILURE         (1 << 0)
#define       STATE_MODE_BIT               (1 << 1)
#define       STATE_OUT_ACTIVE             (1 << 2)
#define       STATE_DATA_UPD               (1 << 3)
#define       STATE_OUT_ENABLED            (1 << 4)
#define       STATE_OUT_ENABLE_EVENT       (1 << 5)
#define       STATE_DEVICE_ON              (1 << 6)
#define       STATE_KEY_PRESSED_EVENT      (1 << 7)
#define       STATE_KEYS_VALUE_OFFSET      8
#define       STATE_KEYS_VALUE             (0x1F << STATE_KEYS_VALUE_OFFSET)//(0x07 << STATE_KEYS_VALUE_OFFSET)
#define       STATE_MENU_ACTIVE            (1 << 13)
#define       STATE_DEVICE_CONFIGURED      (1 << 14)
#define       STATE_RANDOM_KEYS_PRESS      (1 << 15)


#define       STATE_MASK_EXCEPT_MODE       (STATE_OUT_ACTIVE | STATE_DATA_UPD | STATE_OUT_ENABLED | STATE_OUT_ENABLE_EVENT | \
                                            STATE_DEVICE_ON | STATE_KEY_PRESSED_EVENT | STATE_KEYS_VALUE | STATE_MENU_ACTIVE)

#define       STATE_MODE_BIT_OFFSET        0

#define       OUT_DISABLED                 0
#define       OUT_ENABLED                  1

#define       EEPROM_ERROR_LED_FREQ        4 //Hz
#define       ON_TIME_ERROR_LED_FREQ       6 //Hz

#define       ERROR_EEPROM                 0
#define       ERROR_ON_TIME                1

#define       TEMP_POINT_POSITION          2
#define       TEMP_SET_POINT_DURATION      30

#define       TEMP_FLOAT_TO_INT_VALUE      10

#define       SENSOR_FAILURE_LOW_THRESHOLD  ((int16_t) -25)
#define       SENSOR_FAILURE_HIGH_THRESHOLD ((int16_t) 125)

#define       FIRMWARE_VERSION             0x20



typedef struct
{
  int16_t DeltaLow;
  int16_t Tnom;
  int16_t DeltaHigh;
  
} TempSetType;


typedef struct
{
  float Data[SMA_SAMPLES + 1];
  volatile float Result;
    
} SMAType;


void RDC2_0043_Init();

void BoardTest();

void TempEventHandler(uint8_t TempFlag);

void OutEnableChangedEvent(uint8_t EnableState);

void KeyEvent(uint8_t Key, uint8_t KeyState);

void KeyPressedEventHandler();

void ShowNoData();

void DATA_UPDATE_TIMER_ISR(void);

void KEY_EVENT_GEN_TIMER_ISR(void);

void PROTECTION_TIMER_ISR(void);

void SetOutNotActive();

void SMA_Init();

void ActivateConfiguration(uint8_t *Configuration);

void ResetProtection();

void ErrorHandler(uint8_t ErrorType);



#endif //__RDC2_0043_BOARD_H

