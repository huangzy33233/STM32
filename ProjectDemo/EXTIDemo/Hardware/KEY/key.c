#include "key.h"
#include "led.h"

void Init_Key(void)
{
	rcu_periph_clock_enable(RCU_GPIOB);
	
	gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_13);
	gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_14);
}

void Scanf_Key(void)
{
	if(gpio_input_bit_get(GPIOB,GPIO_PIN_13) == RESET)
	{
		delay_1ms(10);
		if(gpio_input_bit_get(GPIOB,GPIO_PIN_13) == RESET)
		{ 
		  while(gpio_input_bit_get(GPIOB,GPIO_PIN_13) == RESET);
		  Open_LED();
		}
	}
	
	if(gpio_input_bit_get(GPIOB,GPIO_PIN_14) == RESET)
	{
		delay_1ms(10);
		if(gpio_input_bit_get(GPIOB,GPIO_PIN_14) == RESET)
		{
		  while(gpio_input_bit_get(GPIOB,GPIO_PIN_14) == RESET);
		  Close_LED();
		}
	}
}

