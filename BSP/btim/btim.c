#include "btim.h"
#include "stdio.h"

TIM_HandleTypeDef g_btim_handle ={0};
/**
 * @brief 基本定时器 TIMX 定时中断初始化函数
 * @note
 * 基本定时器的时钟来自 APB1,当 PPRE1 ≥ 2 分频的时候
 * 基本定时器的时钟为 APB1 时钟的 2 倍, 而 APB1 为 36M, 所以定时器时钟 = 72Mhz
 * 定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 * Ft=定时器工作频率,单位:Mhz
 *
 * @param arr: 自动重装值。
 * @param psc: 时钟预分频数
 * @retval 无
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
 * @brief 定时器底层驱动，开启时钟，设置中断优先级
 此函数会被 HAL_TIM_Base_Init()函数调用
 * @param 无
 * @retval 无
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
 * @brief 定时器中断服务函数
 * @param 无
 * @retval 无
 */
void BTIM_TIMX_IRQHandler()
{
    HAL_TIM_IRQHandler(&g_btim_handle);
}

/**
 * @brief 定时器更新中断回调函数
 * @param htim:定时器句柄指针
 * @retval 无
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == BTIM_TIMX)
    {
        printf("btim init complited \r\n");
    }
}
