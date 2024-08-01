#ifndef __LED_H__
#define __LED_H__

#include "stm32f1xx.h"
/*
 *  ����ļ����led�����ļ�
 *  ������ļ���GPIO����ߵ�ƽ���ǵ͵�ƽ�ǵ�ledΪon���ɺ궨��LED_ONSTATUS_LOW����
 **/
#define LED_ONSTATUS_LOW    /* GPIO����͵�ƽled��ʱLED_ONSTATUS_LOW */

#define LED1_GPIO           GPIOC
#define LED1_PIN            GPIO_PIN_13
#define LED1_CLK_ENABLE()   __HAL_RCC_GPIOC_CLK_ENABLE()

void led1_init(void);
void led1_on(void);
void led1_off(void);
GPIO_PinState led1_read(void);
void led1_toggle(void);

#endif
