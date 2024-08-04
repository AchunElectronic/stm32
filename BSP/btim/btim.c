#include "btim.h"
#include "stdio.h"

TIM_HandleTypeDef g_btim_handle ={0};
/**
 * @brief ������ʱ�� TIMX ��ʱ�жϳ�ʼ������
 * @note
 * ������ʱ����ʱ������ APB1,�� PPRE1 �� 2 ��Ƶ��ʱ��
 * ������ʱ����ʱ��Ϊ APB1 ʱ�ӵ� 2 ��, �� APB1 Ϊ 36M, ���Զ�ʱ��ʱ�� = 72Mhz
 * ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 * Ft=��ʱ������Ƶ��,��λ:Mhz
 *
 * @param arr: �Զ���װֵ��
 * @param psc: ʱ��Ԥ��Ƶ��
 * @retval ��
 */
void btim_init(uint16_t arr,uint16_t psc)
{
    g_btim_handle.Instance = BTIM_TIMX;
    g_btim_handle.Init.Period = arr;
    g_btim_handle.Init.Prescaler = psc;
    g_btim_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_Base_Init(&g_btim_handle);
    HAL_TIM_Base_Start_IT(&g_btim_handle);
}

/**
 * @brief ��ʱ���ײ�����������ʱ�ӣ������ж����ȼ�
 �˺����ᱻ HAL_TIM_Base_Init()��������
 * @param ��
 * @retval ��
 */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == BTIM_TIMX)
    {
        BTIM_TIMX_INT_CLK_ENABLE();
        
        HAL_NVIC_SetPriority(BTIM_TIMX_IRQn,2,2);
        HAL_NVIC_EnableIRQ(BTIM_TIMX_IRQn);
    }
    
}

/**
 * @brief ��ʱ���жϷ�����
 * @param ��
 * @retval ��
 */
void BTIM_TIMX_IRQHandler()
{
    HAL_TIM_IRQHandler(&g_btim_handle);
}

/**
 * @brief ��ʱ�������жϻص�����
 * @param htim:��ʱ�����ָ��
 * @retval ��
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == BTIM_TIMX)
    {
        printf("btim init complited \r\n");
    }
}
