#ifndef __GTIM_H__
#define __GTIM_H__

/* Ϊ��ֹռ�ù����ڴ棬��ʹ�õĹ���ֱע�͵� */

#define TIM_UP
#define TIM_PWM

#include "sys.h"




/* ͨ�ö�ʱ�� ���� */

/* TIMX �ж϶��� 
 * Ĭ�������TIM2~TIM5
 * ע��: ͨ���޸���4���궨��,����֧��TIM1~TIM8����һ����ʱ��.
 */
 
#define GTIM_TIMX_INT                       TIM3
#define GTIM_TIMX_INT_IRQn                  TIM3_IRQn
#define GTIM_TIMX_INT_IRQHandler            TIM3_IRQHandler
#define GTIM_TIMX_INT_CLK_ENABLE()          do{ __HAL_RCC_TIM3_CLK_ENABLE(); }while(0)  /* TIM3 ʱ��ʹ�� */


/*********************************������ͨ�ö�ʱ��PWM���ʵ����غ궨��*************************************/

/* TIMX PWM������� 
 * ���������PWM����LED0(RED)������
 * Ĭ�������TIM2~TIM5
 * ע��: ͨ���޸��⼸���궨��,����֧��TIM1~TIM8����һ����ʱ��,����һ��IO�����PWM
 */
#define GTIM_TIMX_PWM_CHY_GPIO_PORT         GPIOA
#define GTIM_TIMX_PWM_CHY_GPIO_PIN          GPIO_PIN_8
#define GTIM_TIMX_PWM_CHY_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PORT��ʱ��ʹ�� */

/* 
 *�������������ӳ��, �ǲ���Ҫ�ú�����!
 */

#define GTIM_TIMX_PWM_CHY_GPIO_REMAP()      do{__HAL_RCC_AFIO_CLK_ENABLE();\
                                                __HAL_AFIO_REMAP_TIM3_PARTIAL();\
                                            }while(0)            /* ͨ��REMAP����, �ú������Ǳ����, ������Ҫʵ�� */

#define GTIM_TIMX_PWM                       TIM1 
#define GTIM_TIMX_PWM_CHY                   TIM_CHANNEL_1                               /* ͨ��Y,  1<= Y <=4 */
#define GTIM_TIMX_PWM_CHY_CCRX              TIM1->CCR1                                  /* ͨ��Y������ȽϼĴ��� */
#define GTIM_TIMX_PWM_CHY_CLK_ENABLE()      do{ __HAL_RCC_TIM1_CLK_ENABLE(); }while(0)  /* TIMx ʱ��ʹ�� */

#ifdef TIM_UP
void gtim_timx_int_init(uint16_t arr, uint16_t psc);
#endif

#ifdef TIM_PWM
void gtimx_chy_pwm_init(uint32_t psc,uint32_t arr);
void set_pwm_ccr(uint32_t ccr);
#endif

#endif
