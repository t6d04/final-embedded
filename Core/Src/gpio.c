#include "gpio.h"

void led_init(){
	GPIOB->MODER &= ~(3 << (LED1_PIN * 2));
	GPIOB->MODER |= (1 << (LED1_PIN * 2));

	GPIOB->MODER &= ~(3 << (LED2_PIN * 2));
	GPIOB->MODER |= (1 << (LED2_PIN * 2));

	GPIOB->MODER &= ~(3 << (LED3_PIN * 2));
	GPIOB->MODER |= (1 << (LED3_PIN * 2));
}

void button_init(){
	GPIOA->MODER &= ~(3 << (BTN1_PIN * 2));
	GPIOA->PUPDR &= ~(3 << (BTN1_PIN * 2));
	GPIOA->PUPDR |= 2 << (BTN1_PIN * 2);

	GPIOA->MODER &= ~(3 << (BTN2_PIN * 2));
	GPIOA->PUPDR &= ~(3 << (BTN2_PIN * 2));
	GPIOA->PUPDR |= 2 << (BTN2_PIN * 2);

	GPIOA->MODER &= ~(3 << (BTN3_PIN * 2));
	GPIOA->PUPDR &= ~(3 << (BTN3_PIN * 2));
	GPIOA->PUPDR |= 2 << (BTN3_PIN * 2);
}

void gas_sensor_init(){
	//TODO
}

void buzzer_init(){
	//TODO
};


