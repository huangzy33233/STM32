#include "exit.h"

void Init_EC11GPIO(void)
{
	rcu_periph_clock_enable(RCU_GPIOB);
	
	gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_9);
	gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_3);
	gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_4);
} 

void Init_EC11_EXIT_GPIO(void)
{
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_CFGCMP);
	
	gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_4);
	
	nvic_irq_enable(EXTI4_15_IRQn,0);
	
	syscfg_exti_line_config(EXTI_SOURCE_GPIOB,EXTI_SOURCE_PIN4);
	
	exti_init(EXTI_4,EXTI_INTERRUPT,EXTI_TRIG_FALLING);
	
	exti_interrupt_flag_clear(EXTI_4);
}


//消除抖动
static uint8_t ec11_last_state = 0;

static uint8_t EC11_ReadAB(void)
{
    uint8_t a;
    uint8_t b;

    a = gpio_input_bit_get(GPIOB, GPIO_PIN_4);
    b = gpio_input_bit_get(GPIOB, GPIO_PIN_3);

    a = (a == RESET) ? 0 : 1;
    b = (b == RESET) ? 0 : 1;

    return (a << 1) | b;
}

void Init_EC11GPIO_1(void)
{
    rcu_periph_clock_enable(RCU_GPIOB);

    gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_4); // A 相
    gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_3); // B 相
    gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_9); // 按下开关

    ec11_last_state = EC11_ReadAB();
}

int8_t EC11_Scan(void)
{
    uint8_t now_state;
    uint8_t transition;
    int8_t result = 0;

    now_state = EC11_ReadAB();

    if(now_state != ec11_last_state)
    {
        transition = (ec11_last_state << 2) | now_state;

        switch(transition)
        {
            /*
                一个方向：
                00 -> 01 -> 11 -> 10 -> 00
            */
            case 0x01:
            case 0x07:
            case 0x0E:
            case 0x08:
                result = 1;
                break;

            /*
                另一个方向：
                00 -> 10 -> 11 -> 01 -> 00
            */
            case 0x02:
            case 0x0B:
            case 0x0D:
            case 0x04:
                result = -1;
                break;

            /*
                非法跳变，认为是抖动
                例如 00 -> 11
            */
            default:
                result = 0;
                break;
        }

        ec11_last_state = now_state;
    }

    return result;
}