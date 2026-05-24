#include "led.h"

/*
	函数内容;
	函数参数;
	返回值;
*/

void Init_LEDGPIO(void)
{
	rcu_periph_clock_enable(RCU_GPIOC);
	
	gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_14);
	gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_15);
	
	gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_14);
	gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_15);
}

void Open_LED(void)
{
	gpio_bit_reset(GPIOC,GPIO_PIN_14);
	gpio_bit_reset(GPIOC,GPIO_PIN_15);
}

void Close_LED(void)
{
	gpio_bit_set(GPIOC,GPIO_PIN_14);
	gpio_bit_set(GPIOC,GPIO_PIN_15);
}
}