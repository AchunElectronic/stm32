#include "iwdg.h"

IWDG_HandleTypeDef g_iwdg_handle ={0};
/**
 * @brief       独立看门狗初始化
 * @param       ms：独立看门狗复位时间，超过这个时间不喂狗产生复位信号
 *              ms最大值为26,208，大约26s
 * @retval      无
 */
void iwdg_init(uint16_t ms)
{
    /*
    ms = reload * 256/40
    reload = ms * 40/256;
    */
    
    g_iwdg_handle.Instance = IWDG;
    g_iwdg_handle.Init.Prescaler = IWDG_PRESCALER_256;/* 256分频 */
    g_iwdg_handle.Init.Reload = (ms * 5/32);
    
    HAL_IWDG_Init(&g_iwdg_handle);
}
/**
 * @brief       独立看门狗喂狗
 * @param       无
 * @retval      无
 */
void iwdg_feed(void)
{
    HAL_IWDG_Refresh(&g_iwdg_handle);

}

