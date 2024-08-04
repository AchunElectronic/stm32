#include "wwdg.h"
#include "usart.h"

WWDG_HandleTypeDef g_wwdg_handle = {0};

/**
 * @brief   ���ڿ��Ź���ʼ��
 * @param   psc     ��Ԥ��Ƶϵ�� ����ֵ����Ϊ  WWDG_PRESCALER_1  WWDG_PRESCALER_2
                    WWDG_PRESCALER_4  WWDG_PRESCALER_8 �е�һ����
 * @param   counter ������ֵ 0x40 - 0x7f
 * @param   window  ������ֵ �ڴ���ֵ��0x40֮�����ι�����������������λ
 * @retval  ��
 */
void wwdg_init(uint32_t psc,uint8_t counter, uint8_t window)
{
    
    g_wwdg_handle.Instance = WWDG;
    g_wwdg_handle.Init.Counter = counter;
    g_wwdg_handle.Init.EWIMode = WWDG_EWI_ENABLE;
    g_wwdg_handle.Init.Prescaler = psc;
    g_wwdg_handle.Init.Window = window;
    
    HAL_WWDG_Init(&g_wwdg_handle);
}
/**
 * @brief   ���ڿ��Ź��ص�����
 * @param   hwwdg   �����
 * @retval  ��
 */
void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg)
{
    __HAL_RCC_WWDG_CLK_ENABLE();
    
    HAL_NVIC_SetPriority(WWDG_IRQn ,2,2);
    HAL_NVIC_EnableIRQ(WWDG_IRQn);
}
/**
 * @brief   ���ڿ��Ź���ǰ�����жϺ���
 * @param   ��
 * @retval  ��
 */
void WWDG_IRQHandler(void)
{
    HAL_WWDG_IRQHandler(&g_wwdg_handle);
}
/**
 * @brief   ���ڿ��Ź���ǰ�����жϻص�����
 * @param   hwwdg   �����
 * @retval  ��
 */
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg)
{
    wwdg_feed();
}
/**
 * @brief   ι��
 * @param   ��
 * @retval  ��
 */
void wwdg_feed(void)
{
    HAL_WWDG_Refresh(&g_wwdg_handle);
}
