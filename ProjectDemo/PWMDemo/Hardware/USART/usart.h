#ifndef __USART_H
#define __USART_H

#include "gd32e23x.h"
#include "systick.h"
#include "stdio.h"

void Init_USARTGPIO(void);
void USART_init(void);
void Send_Byte(char ch);
void Send_String(char *str);

#endif