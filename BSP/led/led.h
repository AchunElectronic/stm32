#ifndef __LED_H__
#define __LED_H__

#include "stm32f1xx.h"
/*
 *  这个文件存放led驱动文件
 *  在这个文件中GPIO输出高电平还是低电平是的led为on，由宏定义LED_ONSTATUS_LOW决定
 **/
#define LED_ONSTATUS_LOW    /* GPIO输出低电平led亮时LED_ONSTATUS_LOW */

#define LED1_GPIO           GPIOC
#define LED1_PIN            GPIO_PIN_13
#define LED1_CLK_ENABLE()   __HAL_RCC_GPIOC_CLK_ENABLE()

void led1_init(void);
void led1_on(void);
void led1_off(void);
GPIO_PinState led1_read(void);
void led1_toggle(void);

#endif
