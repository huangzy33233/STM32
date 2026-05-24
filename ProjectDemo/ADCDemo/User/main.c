#include "gd32e23x.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "exit.h"
#include "adc.h"

extern volatile uint32_t g_ms_tick;

int main(void)
{	
	uint16_t adcValue=0;
	float adcVoltage=0;
	float V_in=0;
		
	uint32_t last_ec11_time = 0;
	uint32_t last_adc_time = 0;
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
	
	Init_ADC();
	
	
    while(1){
      Scanf_Key();
	
    if(g_ms_tick - last_ec11_time >= 1)
    {
        last_ec11_time = g_ms_tick;

       
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
    }

    /*
        ADC 每 500ms 采样一次
    */
    if(g_ms_tick - last_adc_time >= 500)
		{
        last_adc_time = g_ms_tick;

        adcValue = adc_channel_sample(ADC_CHANNEL_3);

		adcVoltage=(3.3*adcValue)/4095.0;
		V_in = (2.8f - adcVoltage) * 3.3f / 1.8f;
		printf("adcVoltage= %f,V_in = %.3f V\r\n",adcVoltage,V_in);
		}
	}
}

