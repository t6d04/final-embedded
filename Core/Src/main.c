#include "stm32f4xx.h"
#include "gpio.h"

void clock_init(){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
}

int main(void){
	clock_init();
	led_init();
	button_init();
	button_interrupt_init();
	while(1);
}



