#include "gtim.h"

#ifdef TIM_UP
TIM_HandleTypeDef g_timx_handle; /* ��ʱ��x��� */
/**
 * @brief       ͨ�ö�ʱ��TIMX��ʱ�жϳ�ʼ������
 * @note
 *              ͨ�ö�ʱ����ʱ������APB1,��PPRE1 �� 2��Ƶ��ʱ��
 *              ͨ�ö�ʱ����ʱ��ΪAPB1ʱ�ӵ�2��, ��APB1Ϊ36M, ���Զ�ʱ��ʱ�� = 72Mhz
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=��ʱ������Ƶ��,��λ:Mhz
 *
 * @param       arr: �Զ���װֵ��
 * @param       psc: ʱ��Ԥ��Ƶ��
 * @retval      ��
 */
void gtim_timx_int_init(uint16_t arr, uint16_t psc)
{
    GTIM_TIMX_INT_CLK_ENABLE();                                 /* ʹ��TIMxʱ�� */

    g_timx_handle.Instance = GTIM_TIMX_INT;                     /* ͨ�ö�ʱ��x */
    g_timx_handle.Init.Prescaler = psc;                         /* Ԥ��Ƶϵ�� */
    g_timx_handle.Init.CounterMode = TIM_COUNTERMODE_UP;        /* ��������ģʽ */
    g_timx_handle.Init.Period = arr;                            /* �Զ�װ��ֵ */
    HAL_TIM_Base_Init(&g_timx_handle);

    HAL_NVIC_SetPriority(GTIM_TIMX_INT_IRQn, 1, 3);             /* �����ж����ȼ�����ռ���ȼ�1�������ȼ�3 */
    HAL_NVIC_EnableIRQ(GTIM_TIMX_INT_IRQn);                     /* ����ITMx�ж� */

    HAL_TIM_Base_Start_IT(&g_timx_handle);                      /* ʹ�ܶ�ʱ��x�Ͷ�ʱ��x�����ж� */
}

/**
 * @brief       ��ʱ���жϷ�����
 * @param       ��
 * @retval      ��
 */
void GTIM_TIMX_INT_IRQHandler(void)
{
    static uint16_t cnt = 0;
    /* ���´���û��ʹ�ö�ʱ��HAL�⹲�ô���������������ֱ��ͨ���ж��жϱ�־λ�ķ�ʽ */
    if(__HAL_TIM_GET_FLAG(&g_timx_handle, TIM_FLAG_UPDATE) != RESET)
    {
        cnt ++;
        __HAL_TIM_CLEAR_IT(&g_timx_handle, TIM_IT_UPDATE);  /* �����ʱ������жϱ�־λ */
    }
}
#endif
#ifdef TIM_PWM
TIM_HandleTypeDef g_gtim_pwm_handle = {0};
TIM_OC_InitTypeDef g_tim_oc_handle = {0};
/**
 * @brief       ͨ�ö�ʱ��TIMX ͨ��Y PWM��� ��ʼ��������ʹ��PWMģʽ1��
 * @note
 *              ͨ�ö�ʱ����ʱ������APB1,��PPRE1 �� 2��Ƶ��ʱ��
 *              ͨ�ö�ʱ����ʱ��ΪAPB1ʱ�ӵ�2��, ��APB1Ϊ36M, ���Զ�ʱ��ʱ�� = 72Mhz
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=��ʱ������Ƶ��,��λ:Mhz
 *
 * @param       arr: �Զ���װֵ��
 * @param       psc: ʱ��Ԥ��Ƶ��
 * @retval      ��
 */
void gtimx_chy_pwm_init(uint32_t psc,uint32_t arr)
{
    g_gtim_pwm_handle.Instance = GTIM_TIMX_PWM;
    g_gtim_pwm_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    g_gtim_pwm_handle.Init.Prescaler = psc;
    g_gtim_pwm_handle.Init.Period = arr;
    
    HAL_TIM_PWM_Init(&g_gtim_pwm_handle);
    g_tim_oc_handle.OCMode = TIM_OCMODE_PWM1;
    g_tim_oc_handle.Pulse = arr/2;
    g_tim_oc_handle.OCPolarity = TIM_OCPOLARITY_LOW;
    HAL_TIM_PWM_ConfigChannel(&g_gtim_pwm_handle,&g_tim_oc_handle,GTIM_TIMX_PWM_CHY);
    
    HAL_TIM_PWM_Start(&g_gtim_pwm_handle,GTIM_TIMX_PWM_CHY);
}

/**
 * @brief       ��ʱ���ײ�������ʱ��ʹ�ܣ���������
                �˺����ᱻHAL_TIM_PWM_Init()����
 * @param       htim:��ʱ�����
 * @retval      ��
 */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == GTIM_TIMX_PWM)
    {
        GTIM_TIMX_PWM_CHY_CLK_ENABLE();
        GTIM_TIMX_PWM_CHY_GPIO_CLK_ENABLE();
        
        GPIO_InitTypeDef gpio_init_handle = {0};
        gpio_init_handle.Mode = GPIO_MODE_AF_PP;
        gpio_init_handle.Pin = GTIM_TIMX_PWM_CHY_GPIO_PIN;
        gpio_init_handle.Pull = GPIO_PULLUP;
        gpio_init_handle.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GTIM_TIMX_PWM_CHY_GPIO_PORT,&gpio_init_handle);
    }
}

/**
 * @brief       �޸� CCR �Ĵ�����ֵ���ı�ռ�ձ�
 * @param       ccr ���� CCR �Ĵ�����д���ֵ
 * @retval      ��
 */
void set_pwm_ccr(uint32_t ccr)
{
    GTIM_TIMX_PWM_CHY_CCRX = ccr;
}
#endif

