#include "gd32e23x.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"
#include "led.h"
#include "key.h"
#include "usart.h"

int main(void)
{
    //系统时钟配置
	systick_config(); 

	//初始化LED灯GPIO
	Init_LEDGPIO();
	
	//初始化按键GPIO
	Init_Key();
	
	//串口引脚定义
	Init_USARTGPIO();
	
	//串口参数定义
	USART_init();

	Send_String("886\r\n");
	//Send_Byte('6');
	//printf("666\r\n");
    while(1){
      Scanf_Key();
    }
}


