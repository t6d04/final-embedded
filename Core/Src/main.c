#include "stm32f4xx.h"
#include "gpio.h"
#include "adc.h"

void clock_init(){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
}

int main(void){
	clock_init();
	led_init();
	button_init();
	button_interrupt_init();
	adc1_init();
	while(1){
		uint16_t mq6_adc_value = adc1_read_channel(10);
		if (mq6_adc_value > 200){
			led_on(BTN_PORT, 5);
			for (int i = 1; i< 1000000; i++);
			led_off(BTN_PORT, 5);
		}
	}
}



