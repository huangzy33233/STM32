#include "usart.h"

void Init_USARTGPIO(void)
{
	/* 使能GPIOA时钟 */
    rcu_periph_clock_enable(RCU_GPIOA);

    /* 使用复用功能1--USARTO */
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_9);

    /* 使用复用功能1--USARTO */
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_10);

    /* 配置复用模式，上拉 */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_9);

    /* 配置复用模式，上拉 */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_10);
}

void USART_init(void)
{
    /* 使能串口0时钟 */
    rcu_periph_clock_enable(RCU_USART0);

    /* 串口参数配置 */
    usart_deinit(USART0);										//复位串口0
    usart_word_length_set(USART0, USART_WL_8BIT);		 		//设置数据位
    usart_stop_bit_set(USART0, USART_STB_1BIT);					//设置停止位-1位
    usart_parity_config(USART0, USART_PM_NONE);					//设置奇偶校验-无校验
    usart_baudrate_set(USART0, 115200U);						//波特率设置-115200
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);			//接受使能
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);		//发送使能
	
	//使能串口0
    usart_enable(USART0);
}

void Send_Byte(char ch)
{
	usart_data_transmit(USART0, (uint8_t) ch);
    while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
}


void Send_String(char *str)
{
    while(*str != '\0')
    {
        Send_Byte((uint8_t)(*str));
        str++;
    }
}

int fputc(int ch, FILE *f)
{
    usart_data_transmit(USART0, (uint8_t) ch);
    while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
    return ch;
}