#include "gtim.h"

#ifdef TIM_UP
TIM_HandleTypeDef g_timx_handle; /* 定时器x句柄 */
/**
 * @brief       通用定时器TIMX定时中断初始化函数
 * @note
 *              通用定时器的时钟来自APB1,当PPRE1 ≥ 2分频的时候
 *              通用定时器的时钟为APB1时钟的2倍, 而APB1为36M, 所以定时器时钟 = 72Mhz
 *              定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=定时器工作频率,单位:Mhz
 *
 * @param       arr: 自动重装值。
 * @param       psc: 时钟预分频数
 * @retval      无
 */
void gtim_timx_int_init(uint16_t arr, uint16_t psc)
{
    GTIM_TIMX_INT_CLK_ENABLE();                                 /* 使能TIMx时钟 */

    g_timx_handle.Instance = GTIM_TIMX_INT;                     /* 通用定时器x */
    g_timx_handle.Init.Prescaler = psc;                         /* 预分频系数 */
    g_timx_handle.Init.CounterMode = TIM_COUNTERMODE_UP;        /* 递增计数模式 */
    g_timx_handle.Init.Period = arr;                            /* 自动装载值 */
    HAL_TIM_Base_Init(&g_timx_handle);

    HAL_NVIC_SetPriority(GTIM_TIMX_INT_IRQn, 1, 3);             /* 设置中断优先级，抢占优先级1，子优先级3 */
    HAL_NVIC_EnableIRQ(GTIM_TIMX_INT_IRQn);                     /* 开启ITMx中断 */

    HAL_TIM_Base_Start_IT(&g_timx_handle);                      /* 使能定时器x和定时器x更新中断 */
}

/**
 * @brief       定时器中断服务函数
 * @param       无
 * @retval      无
 */
void GTIM_TIMX_INT_IRQHandler(void)
{
    static uint16_t cnt = 0;
    /* 以下代码没有使用定时器HAL库共用处理函数来处理，而是直接通过判断中断标志位的方式 */
    if(__HAL_TIM_GET_FLAG(&g_timx_handle, TIM_FLAG_UPDATE) != RESET)
    {
        cnt ++;
        __HAL_TIM_CLEAR_IT(&g_timx_handle, TIM_IT_UPDATE);  /* 清除定时器溢出中断标志位 */
    }
}
#endif
#ifdef TIM_PWM
TIM_HandleTypeDef g_gtim_pwm_handle = {0};
TIM_OC_InitTypeDef g_tim_oc_handle = {0};
/**
 * @brief       通用定时器TIMX 通道Y PWM输出 初始化函数（使用PWM模式1）
 * @note
 *              通用定时器的时钟来自APB1,当PPRE1 ≥ 2分频的时候
 *              通用定时器的时钟为APB1时钟的2倍, 而APB1为36M, 所以定时器时钟 = 72Mhz
 *              定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=定时器工作频率,单位:Mhz
 *
 * @param       arr: 自动重装值。
 * @param       psc: 时钟预分频数
 * @retval      无
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
 * @brief       定时器底层驱动，时钟使能，引脚配置
                此函数会被HAL_TIM_PWM_Init()调用
 * @param       htim:定时器句柄
 * @retval      无
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
 * @brief       修改 CCR 寄存器的值，改变占空比
 * @param       ccr ：向 CCR 寄存器中写入的值
 * @retval      无
 */
void set_pwm_ccr(uint32_t ccr)
{
    GTIM_TIMX_PWM_CHY_CCRX = ccr;
}
#endif

