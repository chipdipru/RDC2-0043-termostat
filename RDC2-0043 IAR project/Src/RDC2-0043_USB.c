/*
********************************************************************************
* COPYRIGHT(c) ��� ���� � ��ϻ, 2018
* 
* ����������� ����������� ��������������� �� �������� ���� ����� (as is).
* ��� ��������������� �������� ������ �����������.
********************************************************************************
*/


#include "RDC2_0043_USB.h"
#include "usbd_custom_hid_core.h"
#include "usbd_usr.h"


USB_CORE_HANDLE  USB_Device_dev;
uint8_t PrevXferDone = 1;
static volatile uint8_t USBStatus = RDC2_0043_USB_IDLE;
static volatile uint8_t USBDataBuf[USB_MESSAGE_LENGTH];


void RDC2_0043_USB_Init()
{
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;
  SYSCFG->CFGR1 |= 1 << 4;
  USBD_Init(&USB_Device_dev, &USR_desc, &USBD_HID_cb, &USR_cb);  
}
//------------------------------------------------------------------------------
void RDC2_0043_USB_RecPacket(uint8_t *Packet)
{
  for (uint8_t i = 0; i < USB_MESSAGE_LENGTH; i++)
    USBDataBuf[i] = *(Packet + i);
  
  switch(*(USBDataBuf + USB_CMD_POS))
  {
    case USB_CMD_EEPROM_READ:
      USBStatus |= RDC2_0043_USB_READ_CONFIG;
    break;
    
    case USB_CMD_EEPROM_WRITE:
      USBStatus |= RDC2_0043_USB_WRITE_CONFIG;
    break;
        
    default:
    break;
  }  
}
//------------------------------------------------------------------------------
void RDC2_0043_USB_SendData(uint8_t *Data)
{  
  if (PrevXferDone)
  {    
    USBD_HID_SendReport(&USB_Device_dev, Data, USB_MESSAGE_LENGTH);
    PrevXferDone = 0;
  } 
}
//------------------------------------------------------------------------------
volatile uint8_t* RDC2_0043_USB_GetStatus()
{
  return &USBStatus;
}
//------------------------------------------------------------------------------
void RDC2_0043_USB_ClearStatus(uint8_t StatusFlag)
{
  USBStatus &= ~StatusFlag;
}
//------------------------------------------------------------------------------
void RDC2_0043_USB_SetStatus(uint8_t StatusFlag)
{
  USBStatus |= StatusFlag;
}
//------------------------------------------------------------------------------
volatile uint8_t* RDC2_0043_USB_GetPacket()
{
  return USBDataBuf;
}
//------------------------------------------------------------------------------
void RDC2_0043_USB_WhileNotReadyToSend()
{
  while(PrevXferDone != 1);
}


