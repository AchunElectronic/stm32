#include "exti.h"
#include "usart.h"
#include "key.h"
#include "delay.h"
#include "led.h"

/**
 * @brief       �ⲿ�жϳ�ʼ������
 * @param       ��
 * @retval      ��
 */
void exti_init(void)
{
    GPIO_InitTypeDef gpio_struct = {0};
    
    KEY1_INT_GPIO_CLK_ENABLE();                     /* KEY1ʱ��ʹ�� */
    KEY2_INT_GPIO_CLK_ENABLE();                     /* KEY2ʱ��ʹ�� */
    WKUP_INT_GPIO_CLK_ENABLE();                     /* WKUPʱ��ʹ�� */
                                                    
    gpio_struct.Mode = GPIO_MODE_IT_FALLING;        /* �����ش��� */
    gpio_struct.Pin =  KEY1_INT_GPIO_PIN;           
    gpio_struct.Pull = GPIO_PULLUP;               
    
    HAL_GPIO_Init(KEY1_INT_GPIO_PORT,&gpio_struct); /* KEY1����Ϊ�½��ش����ж� */
                                                    
    gpio_struct.Mode = GPIO_MODE_IT_FALLING;        /* �����ش��� */
    gpio_struct.Pin =  KEY2_INT_GPIO_PIN;           
    gpio_struct.Pull = GPIO_PULLUP;                 
                                                    
    HAL_GPIO_Init(KEY2_INT_GPIO_PORT,&gpio_struct); /* KEY2����Ϊ�½��ش����ж� */
                                                    
    gpio_struct.Mode = GPIO_MODE_IT_RISING;         /* �����ش��� */
    gpio_struct.Pin =  WKUP_INT_GPIO_PIN;           
    gpio_struct.Pull = GPIO_PULLDOWN;               
                                                    
    HAL_GPIO_Init(WKUP_INT_GPIO_PORT,&gpio_struct); /* WKUP����Ϊ�����ش����ж� */
                                                    
                                                    
    HAL_NVIC_SetPriority(KEY1_INT_IRQn,2,2);        /* ��ռ2�������ȼ�2 */
    HAL_NVIC_EnableIRQ(KEY1_INT_IRQn);              /* ʹ���ж��� */
                                                    
    HAL_NVIC_SetPriority(KEY2_INT_IRQn,2,2);        /* ��ռ2�������ȼ�2 */
    HAL_NVIC_EnableIRQ(KEY2_INT_IRQn);              /* ʹ���ж��� */
                                                    
    HAL_NVIC_SetPriority(WKUP_INT_IRQn,2,2);        /* ��ռ2�������ȼ�2 */
    HAL_NVIC_EnableIRQ(WKUP_INT_IRQn);              /* ʹ���ж��� */
}                                                   
                                                    
                                                    
/**
 * @brief       WK_UP �ⲿ�жϷ������
 * @param       ��
 * @retval      ��
 */
void WKUP_INT_IRQHandler()
{
    HAL_GPIO_EXTI_IRQHandler(WKUP_INT_GPIO_PIN);
    __HAL_GPIO_EXTI_CLEAR_IT(WKUP_INT_GPIO_PIN);
}
void KEY1_INT_IRQHandler()
{
    HAL_GPIO_EXTI_IRQHandler(KEY1_INT_GPIO_PIN);
    __HAL_GPIO_EXTI_CLEAR_IT(KEY1_INT_GPIO_PIN);
}
void KEY2_INT_IRQHandler()
{
    HAL_GPIO_EXTI_IRQHandler(KEY2_INT_GPIO_PIN);
    __HAL_GPIO_EXTI_CLEAR_IT(KEY2_INT_GPIO_PIN);
}
/**
 * @brief       �жϷ����������Ҫ��������
                ��HAL�������е��ⲿ�жϷ�����������ô˺���
 * @param       GPIO_Pin:�ж����ź�
 * @retval      ��
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(20);      /* ���� */
    switch(GPIO_Pin)
    {
#ifdef __KEY_H__                /* ����Ƿ����ǰ���ļ���ֹ���� */
        case KEY1_INT_GPIO_PIN:
            if (KEY1 == 0)
            {
#ifdef __LED_H__                 /* ����Ƿ����ǰ���ļ���ֹ���� */
                LED0_TOGGLE();  /* LED0 ״̬ȡ�� */ 
#endif
            }
            break;
        case KEY2_INT_GPIO_PIN:
            if (KEY2 == 0)
            {
#ifdef __LED_H__                 /* ����Ƿ����ǰ���ļ���ֹ���� */
                LED1_TOGGLE();  /* LED1 ״̬ȡ�� */
#endif
            }
            break;
        case WKUP_INT_GPIO_PIN:
            if (KEY_UP == 1)
            {
                
#ifdef __LED_H__                 /* ����Ƿ����ǰ���ļ���ֹ���� */
                LED0_TOGGLE();
                LED1_TOGGLE(); 
#endif
            }
            break;
#endif
    }
}

