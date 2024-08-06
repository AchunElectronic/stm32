#ifndef __IC_H__
#define __IC_H__

#include "./SYSTEM/sys/sys.h"


/*********************************������ͨ�ö�ʱ�����벶��ʵ����غ궨��*************************************/

 /* 
 * ע��: ͨ���޸��⼸���궨��,����֧��TIM1~TIM8����һ����ʱ��,����һ��IO�������벶��
 *       �ر�Ҫע��:Ĭ���õ�PA6,���õ�����������!���������IO,��Ӧ����������ʽҲ�ø�!
 */
#define GTIM_TIMX_CAP_CHY_GPIO_PORT            GPIOA
#define GTIM_TIMX_CAP_CHY_GPIO_PIN             GPIO_PIN_6
#define GTIM_TIMX_CAP_CHY_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PA��ʱ��ʹ�� */

#define GTIM_TIMX_CAP                          TIM3                       
#define GTIM_TIMX_CAP_IRQn                     TIM3_IRQn
#define GTIM_TIMX_CAP_IRQHandler               TIM3_IRQHandler
#define GTIM_TIMX_CAP_CHY                      TIM_CHANNEL_1                                 /* ͨ��Y,  1<= Y <=4 */
#define GTIM_TIMX_CAP_CHY_CCRX                 TIM3->CCR1                                    /* ͨ��Y������ȽϼĴ��� */
#define GTIM_TIMX_CAP_CHY_CLK_ENABLE()         do{ __HAL_RCC_TIM3_CLK_ENABLE(); }while(0)    /* TIM3 ʱ��ʹ�� */

/******************************************************************************************/

void gtim_timx_cap_chy_init(uint16_t arr, uint16_t psc);    /* ͨ�ö�ʱ�� ���벶���ʼ������ */
uint8_t tim_cpt_key(uint32_t *ptitm);                       /* ���������µ�ʱ�丳ֵ������ָ�� */

#endif

















