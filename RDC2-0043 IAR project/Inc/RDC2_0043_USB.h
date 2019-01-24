/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2017
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/




#ifndef __RDC2_0043_USB_H
#define __RDC2_0043_USB_H

#include "RDC2_0043_board.h"


#define       USB_MESSAGE_LENGTH           0x40 //длина пакета USB, максимум 64 байта для USB HID


#define       USB_CMD_POS                  0x01 //индекс команды в посылке
#define       USB_DATA_POS                 0x03

//команды
#define       USB_CMD_EEPROM_WRITE         0
#define       USB_CMD_EEPROM_READ          1

//Status
#define       RDC2_0043_USB_IDLE           0
#define       RDC2_0043_USB_WRITE_CONFIG   (1 << 1)
#define       RDC2_0043_USB_READ_CONFIG    (1 << 2)




void RDC2_0043_USB_Init();

void RDC2_0043_USB_RecPacket(uint8_t *Packet);

void RDC2_0043_USB_SendData(uint8_t *Data);

volatile uint8_t* RDC2_0043_USB_GetStatus();

void RDC2_0043_USB_ClearStatus(uint8_t StatusFlag);

void RDC2_0043_USB_SetStatus(uint8_t StatusFlag);

volatile uint8_t* RDC2_0043_USB_GetPacket();

void RDC2_0043_USB_WhileNotReadyToSend();


#endif //__RDC2_0043_USB_H


