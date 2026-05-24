#include "gd32e23x.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"
#include "led.h"
#include "key.h"


int main(void)
{
    //系统时钟配置
	systick_config(); 

	//初始化LED灯GPIO
	Init_LEDGPIO();
	
	//初始化按键GPIO
	Init_Key();
	
    while(1){
       Scanf_Key();
    }
}


