#ifndef __ADC_H
#define __ADC_H

#include "gd32e23x.h"
#include "systick.h"

void Init_ADC(void);
uint16_t adc_channel_sample(uint8_t channel);

#endif