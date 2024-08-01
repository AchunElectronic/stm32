#ifndef __KEY_H__
#define __KEY_H__

#include "./SYSTEM/sys/sys.h"

/* ���� ���� */
#define KEY1_GPIO           GPIOE
#define KEY1_PIN            GPIO_PIN_3
#define KEY1_CKL_EN();      do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)             /* PE��ʱ��ʹ�� */


#define KEY2_GPIO           GPIOE
#define KEY2_PIN            GPIO_PIN_4
#define KEY2_CKL_EN();      do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)             /* PE��ʱ��ʹ�� */

#define KEY_UP_GPIO         GPIOA
#define KEY_UP_PIN          GPIO_PIN_0
#define KEY_UP_CKL_EN();    do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)             /* PA��ʱ��ʹ�� */

#define KEY1                HAL_GPIO_ReadPin(KEY1_GPIO,KEY1_PIN)        /* ��ȡKEY1���� */
#define KEY2                HAL_GPIO_ReadPin(KEY2_GPIO,KEY2_PIN)        /* ��ȡKEY2���� */
#define KEY_UP              HAL_GPIO_ReadPin(KEY_UP_GPIO,KEY_UP_PIN)    /* ��ȡWKUP���� */

#define KEY1_DOWN       1       /* KEY1���� */
#define KEY2_DOWN       2       /* KEY2���� */
#define KEY_UP_DOWN     3       /* KEY_UP���� */

void key_init(void);
uint8_t key_scan(uint8_t mode);

#endif



