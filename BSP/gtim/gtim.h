#ifndef __GTIM_H__
#define __GTIM_H__

/* 为防止占用过多内存，不使用的功能直注释掉 */

#define TIM_UP
#define TIM_PWM

#include "sys.h"




/* 通用定时器 定义 */

/* TIMX 中断定义 
 * 默认是针对TIM2~TIM5
 * 注意: 通过修改这4个宏定义,可以支持TIM1~TIM8任意一个定时器.
 */
 
#define GTIM_TIMX_INT                       TIM3
#define GTIM_TIMX_INT_IRQn                  TIM3_IRQn
#define GTIM_TIMX_INT_IRQHandler            TIM3_IRQHandler
#define GTIM_TIMX_INT_CLK_ENABLE()          do{ __HAL_RCC_TIM3_CLK_ENABLE(); }while(0)  /* TIM3 时钟使能 */


/*********************************以下是通用定时器PWM输出实验相关宏定义*************************************/

/* TIMX PWM输出定义 
 * 这里输出的PWM控制LED0(RED)的亮度
 * 默认是针对TIM2~TIM5
 * 注意: 通过修改这几个宏定义,可以支持TIM1~TIM8任意一个定时器,任意一个IO口输出PWM
 */
#define GTIM_TIMX_PWM_CHY_GPIO_PORT         GPIOA
#define GTIM_TIMX_PWM_CHY_GPIO_PIN          GPIO_PIN_8
#define GTIM_TIMX_PWM_CHY_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PORT口时钟使能 */

/* 
 *如果不用设置重映射, 是不需要该函数的!
 */

#define GTIM_TIMX_PWM_CHY_GPIO_REMAP()      do{__HAL_RCC_AFIO_CLK_ENABLE();\
                                                __HAL_AFIO_REMAP_TIM3_PARTIAL();\
                                            }while(0)            /* 通道REMAP设置, 该函数不是必须的, 根据需要实现 */

#define GTIM_TIMX_PWM                       TIM1 
#define GTIM_TIMX_PWM_CHY                   TIM_CHANNEL_1                               /* 通道Y,  1<= Y <=4 */
#define GTIM_TIMX_PWM_CHY_CCRX              TIM1->CCR1                                  /* 通道Y的输出比较寄存器 */
#define GTIM_TIMX_PWM_CHY_CLK_ENABLE()      do{ __HAL_RCC_TIM1_CLK_ENABLE(); }while(0)  /* TIMx 时钟使能 */

#ifdef TIM_UP
void gtim_timx_int_init(uint16_t arr, uint16_t psc);
#endif

#ifdef TIM_PWM
void gtimx_chy_pwm_init(uint32_t psc,uint32_t arr);
void set_pwm_ccr(uint32_t ccr);
#endif

#endif
