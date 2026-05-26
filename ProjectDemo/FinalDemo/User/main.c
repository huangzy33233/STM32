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

#define EC11_SCAN_PERIOD_MS     1U
#define ADC_SAMPLE_PERIOD_MS    500U
#define WAVE_DRAW_PERIOD_MS     2U
#define LCD_DEMO_HOLD_MS        300U
#define WAVE_Y_OFFSET           80U

extern volatile uint32_t g_ms_tick;
extern __IO float fre;

static const uint8_t wave_data[120] = {
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    33,33,33,33,33,33,33,33,33,33,
    33,33,33,33,33,33,33,33,33,33,
    33,33,33,33,33,33,33,33,33,33,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    33,33,33,33,33,33,33,33,33,33,
    33,33,33,33,33,33,33,33,33,33,
    33,33,33,33,33,33,33,33,33,33
};

static void Demo_Init(void);
static void EC11_Task(uint32_t now);
static void ADC_Task(uint32_t now);
static void Wave_Task(uint32_t now);

int main(void)
{
    uint32_t now = 0;

    Demo_Init();

    while(1)
    {
        now = g_ms_tick;

        Scanf_Key();
        EC11_Task(now);
        ADC_Task(now);
        Wave_Task(now);

        (void)fre;
    }
}

static void Demo_Init(void)
{
    systick_config();

    Init_LEDGPIO();
    Init_Key();

    Init_USARTGPIO();
    USART_init();
    Send_String("886\r\n");

    Init_EC11GPIO();
    Init_EC11_EXIT_GPIO();
    Init_EC11GPIO_1();
    Send_String("EC11 debounce test\r\n");

    Init_ADC();
    Init_PwmOut();
    Init_FreqTimer();

    LCD_Init();
    LCD_Fill(0,0,LCD_W,LCD_H,BLUE);
    delay_1ms(LCD_DEMO_HOLD_MS);
    LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
    delay_1ms(LCD_DEMO_HOLD_MS);
    LCD_ShowUI();
}

static void EC11_Task(uint32_t now)
{
    static uint32_t last_ec11_time = 0;
    int8_t ec11_dir = 0;

    if((now - last_ec11_time) < EC11_SCAN_PERIOD_MS)
    {
        return;
    }

    last_ec11_time = now;
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

static void ADC_Task(uint32_t now)
{
    static uint32_t last_adc_time = 0;
    uint16_t adcValue = 0;
    float adcVoltage = 0;
    float V_in = 0;

    if((now - last_adc_time) < ADC_SAMPLE_PERIOD_MS)
    {
        return;
    }

    last_adc_time = now;

    adcValue = adc_channel_sample(ADC_CHANNEL_3);
    adcVoltage = (3.3f * (float)adcValue) / 4095.0f;
    V_in = (2.8f - adcVoltage) * 3.3f / 1.8f;
    printf("adcVoltage= %f,V_in = %.3f V\r\n", adcVoltage, V_in);
}

static void Wave_Task(uint32_t now)
{
    static uint32_t last_wave_time = 0;
    static uint16_t wave_index = 0;

    if((now - last_wave_time) < WAVE_DRAW_PERIOD_MS)
    {
        return;
    }

    last_wave_time = now;
    DrawCurve(WAVE_Y_OFFSET - wave_data[wave_index]);

    wave_index++;
    if(wave_index >= (sizeof(wave_data) / sizeof(wave_data[0])))
    {
        wave_index = 0;
    }
}
