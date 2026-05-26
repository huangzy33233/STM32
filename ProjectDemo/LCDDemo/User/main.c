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
#include "pic.h"

int main(void)
{
    float t = 0;

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
    LCD_Fill(0, 0, LCD_W, LCD_H, WHITE);
    Open_LED();

    while(1)
    {
        LCD_ShowChinese(0, 0, (uint8_t *)"中景园电子", RED, WHITE, 24, 0);
        LCD_ShowString(24, 30, (const uint8_t *)"LCD W:", RED, WHITE, 16, 0);
        LCD_ShowIntNum(72, 30, LCD_W, 3, RED, WHITE, 16);
        LCD_ShowString(24, 50, (const uint8_t *)"LCD H:", RED, WHITE, 16, 0);
        LCD_ShowIntNum(72, 50, LCD_H, 3, RED, WHITE, 16);
        LCD_ShowFloatNum1(20, 80, t, 4, RED, WHITE, 16);
        t += 0.11f;
        LCD_ShowPicture(65, 80, 40, 40, gImage_1);
    }
}
