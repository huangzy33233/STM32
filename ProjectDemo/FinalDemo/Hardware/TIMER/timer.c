#include "timer.h"

void timer15_config(void)
{
	//定时器参数结构体
    timer_parameter_struct timer_initpara;

    //使能定时器时钟
    rcu_periph_clock_enable(RCU_TIMER15);

    //复位定时器
    timer_deinit(TIMER15);
	
    //初始化定时器参数结构体
    timer_struct_para_init(&timer_initpara);
	
    //定时器参数配置
    timer_initpara.prescaler         = 7199;				//预分频系数
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;	//边沿对其模式
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;	//向上计数模式
    timer_initpara.period            = 4999;				//周期值
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;	//时钟分割
    timer_init(TIMER15, &timer_initpara);

    //定时器中断标志位清除
    timer_interrupt_flag_clear(TIMER15, TIMER_INT_FLAG_UP);
	
    //使能定时器
    timer_interrupt_enable(TIMER15, TIMER_INT_UP);
	
    //使能定时器15
    timer_enable(TIMER15);
	
	//定时器中断优先级配置
	nvic_irq_enable(TIMER15_IRQn, 0);
}