#ifndef __IC_H__
#define __IC_H__

#include "./SYSTEM/sys/sys.h"


/*********************************以下是通用定时器输入捕获实验相关宏定义*************************************/

 /* 
 * 注意: 通过修改这几个宏定义,可以支持TIM1~TIM8任意一个定时器,任意一个IO口做输入捕获
 *       特别要注意:默认用的PA6,设置的是下拉输入!如果改其他IO,对应的上下拉方式也得改!
 */
#define GTIM_TIMX_CAP_CHY_GPIO_PORT            GPIOA
#define GTIM_TIMX_CAP_CHY_GPIO_PIN             GPIO_PIN_6
#define GTIM_TIMX_CAP_CHY_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PA口时钟使能 */

#define GTIM_TIMX_CAP                          TIM3                       
#define GTIM_TIMX_CAP_IRQn                     TIM3_IRQn
#define GTIM_TIMX_CAP_IRQHandler               TIM3_IRQHandler
#define GTIM_TIMX_CAP_CHY                      TIM_CHANNEL_1                                 /* 通道Y,  1<= Y <=4 */
#define GTIM_TIMX_CAP_CHY_CCRX                 TIM3->CCR1                                    /* 通道Y的输出比较寄存器 */
#define GTIM_TIMX_CAP_CHY_CLK_ENABLE()         do{ __HAL_RCC_TIM3_CLK_ENABLE(); }while(0)    /* TIM3 时钟使能 */

/******************************************************************************************/

void gtim_timx_cap_chy_init(uint16_t arr, uint16_t psc);    /* 通用定时器 输入捕获初始化函数 */
uint8_t tim_cpt_key(uint32_t *ptitm);                       /* 将按键按下的时间赋值给传入指针 */

#endif

















