#ifndef __GPIO_H__
#define __GPIO_H__

#include "stm32f4xx.h"

// Cac chan button
#define BTN_PORT GPIOA
#define BTN1_PIN 3
#define BTN2_PIN 2
#define BTN3_PIN 10

// Cac chan led
#define LED_PORT GPIOB
#define LED1_PIN 3
#define LED2_PIN 5
#define LED3_PIN 4

// Chan gas sensor
#define GAS_SENSOR_PORT GPIOC
#define GAS_SENSOR_PIN 0

// Chan buzzer
#define BUZZER_PORT GPIOA
#define BUZZER_PIN 8

void button_init(void);
void led_init(void);
void gas_sensor_init(void);
void buzzer_init(void);

#endif __GPIO_H__
