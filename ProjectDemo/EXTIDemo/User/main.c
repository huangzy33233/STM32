#include "gd32e23x.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "exit.h"

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
	
	//EC11普通引脚初始化
	Init_EC11GPIO();
	
	//EC11中断引脚初始化
	Init_EC11_EXIT_GPIO();
	
	//消除抖动
	int8_t ec11_dir = 0;
	Init_EC11GPIO_1();
	 Send_String("EC11 debounce test\r\n");
	
	
	
	
	
	
	
    while(1){
      Scanf_Key();
	  ec11_dir = EC11_Scan();

        if(ec11_dir == 1)
        {
            Open_LED();
            Send_String("EC11 direction 1\r\n");
        }
        else if(ec11_dir == -1)
        {
            Close_LED();
            Send_String("EC11 direction 2\r\n");
        }

        delay_1ms(1);
    }
}



