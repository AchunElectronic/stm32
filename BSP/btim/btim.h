#ifndef __BTIM_H__
#define __BTIM_H__

#include "sys.h"

//#define BTIM_TIMx_CLK_EN    
/* ������ʱ�� ���� */
/* TIMX �ж϶���
* Ĭ������� TIM6/TIM7.
* ע��: ͨ���޸��� 4 ���궨��,����֧�� TIM1~TIM8 ����һ����ʱ��.
*/
#define BTIM_TIMX                   TIM6
#define BTIM_TIMX_IRQn              TIM6_IRQn
#define BTIM_TIMX_IRQHandler        TIM6_IRQHandler
#define BTIM_TIMX_INT_CLK_ENABLE()  do{ __HAL_RCC_TIM6_CLK_ENABLE(); }while(0)

void btim_init(uint16_t arr,uint16_t psc);
#endif
