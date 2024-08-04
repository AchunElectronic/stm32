#include "wwdg.h"
#include "usart.h"

WWDG_HandleTypeDef g_wwdg_handle = {0};

/**
 * @brief   窗口看门狗初始化
 * @param   psc     ：预分频系数 它的值可以为  WWDG_PRESCALER_1  WWDG_PRESCALER_2
                    WWDG_PRESCALER_4  WWDG_PRESCALER_8 中的一个。
 * @param   counter ：计数值 0x40 - 0x7f
 * @param   window  ：窗口值 在窗口值和0x40之间才能喂狗，过早过晚都会引起复位
 * @retval  无
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
 * @brief   窗口看门狗回调函数
 * @param   hwwdg   ：句柄
 * @retval  无
 */
void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg)
{
    __HAL_RCC_WWDG_CLK_ENABLE();
    
    HAL_NVIC_SetPriority(WWDG_IRQn ,2,2);
    HAL_NVIC_EnableIRQ(WWDG_IRQn);
}
/**
 * @brief   窗口看门狗提前唤醒中断函数
 * @param   无
 * @retval  无
 */
void WWDG_IRQHandler(void)
{
    HAL_WWDG_IRQHandler(&g_wwdg_handle);
}
/**
 * @brief   窗口看门狗提前唤醒中断回调函数
 * @param   hwwdg   ：句柄
 * @retval  无
 */
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg)
{
    wwdg_feed();
}
/**
 * @brief   喂狗
 * @param   无
 * @retval  无
 */
void wwdg_feed(void)
{
    HAL_WWDG_Refresh(&g_wwdg_handle);
}
