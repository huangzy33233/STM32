#ifndef  __EXTI_H
#define  __EXTI_H

#include "gd32e23x.h"
#include "systick.h"

void Init_EC11GPIO(void);
void Init_EC11_EXIT_GPIO(void);
void Init_EC11GPIO_1(void);
int8_t EC11_Scan(void);


#endif
