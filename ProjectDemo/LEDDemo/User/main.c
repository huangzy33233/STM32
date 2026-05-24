#include "gd32e23x.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"
#include "led.h"


int main(void)
{
    systick_config(); 
	
	Init_LEDGPIO();
	
	Open_LED();
    while(1){
       
    }
}