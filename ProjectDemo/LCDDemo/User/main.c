#include "gd32e23x.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "exit.h"
#include "adc.h"
#include "timer.h"
#include "pwm.h"
#include "freq.h"
#include "spi.h"
#include "lcdinit.h"
#include "lcdshow.h"

int main(void)
{
    uint16_t adcValue=0;
    float adcVoltage=0;

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

    //EC11普通引脚初始化
    Init_EC11GPIO();

    //EC11中断引脚初始化
    Init_EC11_EXIT_GPIO();

    //初始化ADC引脚
    Init_ADC();

    //定时器15配置
    //timer15_config();

    //初始化PWM输出
    Init_PwmOut();

    //初始化输入捕获
    //Init_FreqTimer();

    LCD_Init();


    while(1){
    }
}