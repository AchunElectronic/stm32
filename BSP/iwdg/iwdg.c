#include "iwdg.h"

IWDG_HandleTypeDef g_iwdg_handle ={0};
/**
 * @brief       �������Ź���ʼ��
 * @param       ms���������Ź���λʱ�䣬�������ʱ�䲻ι��������λ�ź�
 *              ms���ֵΪ26,208����Լ26s
 * @retval      ��
 */
void iwdg_init(uint16_t ms)
{
    /*
    ms = reload * 256/40
    reload = ms * 40/256;
    */
    
    g_iwdg_handle.Instance = IWDG;
    g_iwdg_handle.Init.Prescaler = IWDG_PRESCALER_256;/* 256��Ƶ */
    g_iwdg_handle.Init.Reload = (ms * 5/32);
    
    HAL_IWDG_Init(&g_iwdg_handle);
}
/**
 * @brief       �������Ź�ι��
 * @param       ��
 * @retval      ��
 */
void iwdg_feed(void)
{
    HAL_IWDG_Refresh(&g_iwdg_handle);

}

