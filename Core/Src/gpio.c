#include "gpio.h"

void led_init(){
	GPIOB->MODER &= ~(3 << (LED1_PIN * 2));
	GPIOB->MODER |= (1 << (LED1_PIN * 2));

	GPIOB->MODER &= ~(3 << (LED2_PIN * 2));
	GPIOB->MODER |= (1 << (LED2_PIN * 2));

	GPIOB->MODER &= ~(3 << (LED3_PIN * 2));
	GPIOB->MODER |= (1 << (LED3_PIN * 2));

	GPIOA->MODER &= ~(3 << (5 * 2));
	GPIOA->MODER |= (1 << (5 * 2));
}

void button_init(){
	GPIOA->MODER &= ~(3 << (BTN1_PIN * 2));
	GPIOA->PUPDR &= ~(3 << (BTN1_PIN * 2));
	GPIOA->PUPDR |= 1 << (BTN1_PIN * 2);

	GPIOA->MODER &= ~(3 << (BTN2_PIN * 2));
	GPIOA->PUPDR &= ~(3 << (BTN2_PIN * 2));
	GPIOA->PUPDR |= 1 << (BTN2_PIN * 2);

	GPIOA->MODER &= ~(3 << (BTN3_PIN * 2));
	GPIOA->PUPDR &= ~(3 << (BTN3_PIN * 2));
	GPIOA->PUPDR |= 1 << (BTN3_PIN * 2);
}

void gas_sensor_init(){
	GAS_SENSOR_PORT->MODER &= ~(3UL << (GAS_SENSOR_PIN * 2));
	GAS_SENSOR_PORT->MODER |=  (3UL << (GAS_SENSOR_PIN * 2));
	GAS_SENSOR_PORT->PUPDR &= ~(3UL << (GAS_SENSOR_PIN * 2));
}

void buzzer_init(){
	BUZZER_PORT->MODER &= ~(3UL << (BUZZER_PIN * 2));
	BUZZER_PORT->MODER |=  (1UL << (BUZZER_PIN * 2));
	BUZZER_PORT->ODR &= ~(1UL << BUZZER_PIN);
}

void button_interrupt_init(void){
	SYSCFG->EXTICR[0] &= ~(0xFUL << (BTN2_PIN * 4)); // Xóa cấu hình cũ cho EXTI2 (PA2)
	SYSCFG->EXTICR[0] &= ~(0xFUL << (BTN1_PIN * 4)); // Xóa cấu hình cũ cho EXTI3 (PA3)
	SYSCFG->EXTICR[2] &= ~(0xFUL << ((BTN3_PIN % 4) * 4)); // Xóa cấu hình cũ cho EXTI10 (PA10)

	EXTI->RTSR &= ~(1UL << BTN1_PIN); // Không dùng Rising Trigger cho BTN1 (PA3)
	EXTI->FTSR |=  (1UL << BTN1_PIN); // Kích hoạt Falling Trigger cho BTN1 (PA3)

	EXTI->RTSR &= ~(1UL << BTN2_PIN); // Không dùng Rising Trigger cho BTN2 (PA2)
	EXTI->FTSR |=  (1UL << BTN2_PIN); // Kích hoạt Falling Trigger cho BTN2 (PA2)

	EXTI->RTSR &= ~(1UL << BTN3_PIN); // Không dùng Rising Trigger cho BTN3 (PA10)
	EXTI->FTSR |=  (1UL << BTN3_PIN);

    EXTI->IMR |= (1UL << BTN1_PIN);  // Unmask EXTI3
    EXTI->IMR |= (1UL << BTN2_PIN);  // Unmask EXTI2
    EXTI->IMR |= (1UL << BTN3_PIN);  // Unmask EXTI10

    NVIC_SetPriority(EXTI2_IRQn, 0); // Ưu tiên cao nhất (hoặc giá trị phù hợp)
	NVIC_SetPriority(EXTI3_IRQn, 0);
	NVIC_SetPriority(EXTI15_10_IRQn, 0); // EXTI10 thuộc group này

	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
};

void led_on(GPIO_TypeDef* GPIOx, uint16_t pin){
	GPIOx->BSRR = (1UL << pin); // Set pin
}

void led_off(GPIO_TypeDef* GPIOx, uint16_t pin){
	GPIOx->BSRR = (1UL << (pin + 16)); // Reset pin
}

void EXTI3_IRQHandler(void){
	if(EXTI->PR & (1UL << BTN1_PIN)){
		EXTI->PR = (1UL << BTN1_PIN);
		led_on(BTN_PORT, 5);
		for (int i = 1; i< 10000000; i++);
		led_off(BTN_PORT, 5);
	}
}

void EXTI2_IRQHandler(void){
	if(EXTI->PR & (1UL << BTN2_PIN)){
		EXTI->PR = (1UL << BTN2_PIN);
		led_on(BTN_PORT, 5);
		for (int i = 1; i< 10000000; i++);
		led_off(BTN_PORT, 5);
	}
}

void EXTI15_10_IRQHandler(void){
	if(EXTI->PR & (1UL << BTN3_PIN)){
		EXTI->PR = (1UL << BTN3_PIN);
		led_on(BTN_PORT, 5);
		for (int i = 1; i< 10000000; i++);
		led_off(BTN_PORT, 5);
	}
}
