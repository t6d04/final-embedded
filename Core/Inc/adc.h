#ifndef __ADC_H__
#define __ADC_H__

#include "stm32f4xx.h"

void adc1_init(void);
uint16_t adc1_read_channel(uint8_t channel);

#endif // __ADC_H__
