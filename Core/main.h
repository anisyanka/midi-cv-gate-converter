#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

void Error_Handler(void);

/* Private defines -----------------------------------------------------------*/
#define SPI1_NSS1_Pin		GPIO_PIN_13
#define SPI1_NSS1_GPIO_Port	GPIOC
#define SPI1_NSS2_Pin		GPIO_PIN_14
#define SPI1_NSS2_GPIO_Port	GPIOC
#define SPI1_NSS3_Pin		GPIO_PIN_15
#define SPI1_NSS3_GPIO_Port	GPIOC
#define ADC1_IN0_Pin		GPIO_PIN_0
#define ADC1_IN0_GPIO_Port	GPIOA
#define ADC1_IN1_Pin		GPIO_PIN_1
#define ADC1_IN1_GPIO_Port	GPIOA
#define KEY_LEARN_Pin		GPIO_PIN_4
#define KEY_LEARN_GPIO_Port	GPIOA
#define GATE_IN1_Pin		GPIO_PIN_0
#define GATE_IN1_GPIO_Port	GPIOB
#define GATE_IN2_Pin		GPIO_PIN_1
#define GATE_IN2_GPIO_Port	GPIOB
#define SPI1_LDAC_Pin 		GPIO_PIN_2
#define SPI1_LDAC_GPIO_Port	GPIOB
#define SWITCH_IN1_Pin		GPIO_PIN_12
#define SWITCH_IN1_GPIO_Port	GPIOB
#define SWITCH_IN2_Pin		GPIO_PIN_13
#define SWITCH_IN2_GPIO_Port	GPIOB
#define SWITCH_IN3_Pin		GPIO_PIN_14
#define SWITCH_IN3_GPIO_Port	GPIOB
#define SWITCH_IN4_Pin		GPIO_PIN_15
#define SWITCH_IN4_GPIO_Port	GPIOB
#define LED_NOTE_ON_Pin		GPIO_PIN_8
#define LED_NOTE_ON_GPIO_Port	GPIOA
#define GATE_OUT1_Pin		GPIO_PIN_6
#define GATE_OUT1_GPIO_Port	GPIOB
#define GATE_OUT2_Pin		GPIO_PIN_7
#define GATE_OUT2_GPIO_Port	GPIOB
#define GATE_OUT3_Pin		GPIO_PIN_8
#define GATE_OUT3_GPIO_Port	GPIOB
#define GATE_OUT4_Pin		GPIO_PIN_9
#define GATE_OUT4_GPIO_Port	GPIOB

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
