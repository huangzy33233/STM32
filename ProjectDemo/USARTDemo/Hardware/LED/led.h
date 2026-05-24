#ifndef __LED_H
#define __LED_H

#include "gd32e23x.h"
#include "systick.h"

void Init_LEDGPIO(void);
void Open_LED(void);
void Close_LED(void);
	
#endif