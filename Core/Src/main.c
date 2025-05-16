#include "stm32f4xx.h"

void clock_init();
void led_init();
void button_init();
void lcd_init();
void buzzer_init();
void gasSensor_init();

int main(void){
	clock_init();
	led_init();
}

void clock_init(){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
}

void led_init(){
	//pb3
	GPIOB->MODER &= ~(3 << (3*2));
	GPIOB->MODER |= (1 << (3*2));

	//pb4
	GPIOB->MODER &= ~(3 << (4*2));
	GPIOB->MODER |= (1 << (4*2));

	//pb5
	GPIOB->MODER &= ~(3 << (5*2));
	GPIOB->MODER |= (1 << (5*2));
}

void button_init(){
	//pull-down
	//pa3
	GPIOA->MODER &= ~(3 << (3 * 2));
	GPIOA->PUPDR &= ~(3 << (3 * 2));
	GPIOA->PUPDR |= 2 << (3 * 2);

	//pa2
	GPIOA->MODER &= ~(3 << (2 * 2));
	GPIOA->PUPDR &= ~(3 << (2 * 2));
	GPIOA->PUPDR |= 2 << (2 * 2);

	//pa10
	GPIOA->MODER &= ~(3 << (10 * 2));
	GPIOA->PUPDR &= ~(3 << (10 * 2));
	GPIOA->PUPDR |= 2 << (10 * 2);
}

