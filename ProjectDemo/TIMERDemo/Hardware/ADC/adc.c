#include "adc.h"

void Init_ADC(void)
{
    /* enable GPIOC clock */
    rcu_periph_clock_enable(RCU_GPIOA);
    /* enable ADC clock */
    rcu_periph_clock_enable(RCU_ADC);;
    /* config ADC clock */
    rcu_adc_clock_config(RCU_ADCCK_AHB_DIV3);
	
	gpio_mode_set(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_3);
	
	//数据对齐方式-右对齐
    adc_data_alignment_config(ADC_DATAALIGN_RIGHT);
    //通道长度-1
    adc_channel_length_config( ADC_REGULAR_CHANNEL, 1U);
    
    //ADC外部触发源配置-软件触发
    adc_external_trigger_source_config( ADC_REGULAR_CHANNEL, ADC_EXTTRIG_REGULAR_NONE); 
    //外部触发使能
    adc_external_trigger_config(ADC_REGULAR_CHANNEL, ENABLE);

    //使能ADC
    adc_enable();
    delay_1ms(1U);
	
    //ADC校准
    adc_calibration_enable();
}	

uint16_t adc_channel_sample(uint8_t channel)
{
    //ADC通道配置
    adc_regular_channel_config(0U, channel, ADC_SAMPLETIME_239POINT5);
    //使能转换
    adc_software_trigger_enable(ADC_REGULAR_CHANNEL);

    //等待转换完成
    while(!adc_flag_get(ADC_FLAG_EOC));
    //清除标志位
    adc_flag_clear(ADC_FLAG_EOC);
    //返回采样值
    return (adc_regular_data_read());
}
