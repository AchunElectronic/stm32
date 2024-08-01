#include "exti.h"
#include "usart.h"
#include "key.h"
#include "delay.h"
#include "led.h"

/**
 * @brief       外部中断初始化程序
 * @param       无
 * @retval      无
 */
void exti_init(void)
{
    GPIO_InitTypeDef gpio_struct = {0};
    
    KEY1_INT_GPIO_CLK_ENABLE();                     /* KEY1时钟使能 */
    KEY2_INT_GPIO_CLK_ENABLE();                     /* KEY2时钟使能 */
    WKUP_INT_GPIO_CLK_ENABLE();                     /* WKUP时钟使能 */
                                                    
    gpio_struct.Mode = GPIO_MODE_IT_FALLING;        /* 下升沿触发 */
    gpio_struct.Pin =  KEY1_INT_GPIO_PIN;           
    gpio_struct.Pull = GPIO_PULLUP;               
    
    HAL_GPIO_Init(KEY1_INT_GPIO_PORT,&gpio_struct); /* KEY1配置为下降沿触发中断 */
                                                    
    gpio_struct.Mode = GPIO_MODE_IT_FALLING;        /* 下升沿触发 */
    gpio_struct.Pin =  KEY2_INT_GPIO_PIN;           
    gpio_struct.Pull = GPIO_PULLUP;                 
                                                    
    HAL_GPIO_Init(KEY2_INT_GPIO_PORT,&gpio_struct); /* KEY2配置为下降沿触发中断 */
                                                    
    gpio_struct.Mode = GPIO_MODE_IT_RISING;         /* 上升沿触发 */
    gpio_struct.Pin =  WKUP_INT_GPIO_PIN;           
    gpio_struct.Pull = GPIO_PULLDOWN;               
                                                    
    HAL_GPIO_Init(WKUP_INT_GPIO_PORT,&gpio_struct); /* WKUP配置为上升沿触发中断 */
                                                    
                                                    
    HAL_NVIC_SetPriority(KEY1_INT_IRQn,2,2);        /* 抢占2，子优先级2 */
    HAL_NVIC_EnableIRQ(KEY1_INT_IRQn);              /* 使能中断线 */
                                                    
    HAL_NVIC_SetPriority(KEY2_INT_IRQn,2,2);        /* 抢占2，子优先级2 */
    HAL_NVIC_EnableIRQ(KEY2_INT_IRQn);              /* 使能中断线 */
                                                    
    HAL_NVIC_SetPriority(WKUP_INT_IRQn,2,2);        /* 抢占2，子优先级2 */
    HAL_NVIC_EnableIRQ(WKUP_INT_IRQn);              /* 使能中断线 */
}                                                   
                                                    
                                                    
/**
 * @brief       WK_UP 外部中断服务程序
 * @param       无
 * @retval      无
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
 * @brief       中断服务程序中需要做的事情
                在HAL库中所有的外部中断服务函数都会调用此函数
 * @param       GPIO_Pin:中断引脚号
 * @retval      无
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(20);      /* 消抖 */
    switch(GPIO_Pin)
    {
#ifdef __KEY_H__                /* 检测是否包含前置文件防止报错 */
        case KEY1_INT_GPIO_PIN:
            if (KEY1 == 0)
            {
#ifdef __LED_H__                 /* 检测是否包含前置文件防止报错 */
                LED0_TOGGLE();  /* LED0 状态取反 */ 
#endif
            }
            break;
        case KEY2_INT_GPIO_PIN:
            if (KEY2 == 0)
            {
#ifdef __LED_H__                 /* 检测是否包含前置文件防止报错 */
                LED1_TOGGLE();  /* LED1 状态取反 */
#endif
            }
            break;
        case WKUP_INT_GPIO_PIN:
            if (KEY_UP == 1)
            {
                
#ifdef __LED_H__                 /* 检测是否包含前置文件防止报错 */
                LED0_TOGGLE();
                LED1_TOGGLE(); 
#endif
            }
            break;
#endif
    }
}

