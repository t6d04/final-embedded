#include "stm32f4xx.h"
#include "gpio.h"

void clock_init(){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
}

int main(void){
	clock_init();
	led_init();
}



