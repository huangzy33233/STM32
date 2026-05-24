#include "pwm.h"

void Init_PwmOut(void)
{
	//定时器输出参数结构体
	timer_oc_parameter_struct timer_ocinitpara;
	//定时器参数结构体
    timer_parameter_struct timer_initpara;
	
	//使能GPIOA时钟
    rcu_periph_clock_enable(RCU_GPIOA);
	
	//配置引脚复用功能
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_2);
    gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_2);
	
	//定时器14时钟使能
    rcu_periph_clock_enable(RCU_TIMER14);
	
    //复位定时器
    timer_deinit(TIMER14);
	
    //初始化参数结构体
    timer_struct_para_init(&timer_initpara);
	
    //配置定时器参数
    timer_initpara.prescaler         = 71;					//72_000_000/72=1000_000Hz
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;	
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 999;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER14, &timer_initpara);
	
	//初始话通道输出参数结构体
    timer_channel_output_struct_para_init(&timer_ocinitpara);
	
    //配置输出参数结构体
    timer_ocinitpara.outputstate  = TIMER_CCX_ENABLE;						//使能输出
    timer_ocinitpara.outputnstate = TIMER_CCXN_DISABLE;						//互补输出关闭
    timer_ocinitpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;					//有效电平输出-高电平
    timer_ocinitpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;				//互补有效电平输出-高电平
    timer_ocinitpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;				//空闲电平输出-低电平
    timer_ocinitpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;				//互补空闲电平输出-低电平
	
	//通道输出配置
    timer_channel_output_config(TIMER14, TIMER_CH_0, &timer_ocinitpara);
	
	//通道输出比较值配置
    timer_channel_output_pulse_value_config(TIMER14, TIMER_CH_0, 499);
	//通道模式配置
    timer_channel_output_mode_config(TIMER14, TIMER_CH_0, TIMER_OC_MODE_PWM0);
	//通道输出影子模式配置
    timer_channel_output_shadow_config(TIMER14, TIMER_CH_0, TIMER_OC_SHADOW_DISABLE);
	
	//使能自动重装载计数
    timer_auto_reload_shadow_enable(TIMER14);
	
	//定时器14输出通道使能
	timer_primary_output_config(TIMER14,ENABLE);
	
    //使能定时器14
    timer_enable(TIMER14);
}

