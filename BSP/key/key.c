#include "key.h"
#include "delay.h"

void key_init(void)
{
    KEY1_CKL_EN();      /* 使能时钟 */
    KEY2_CKL_EN();
    KEY_UP_CKL_EN();
    /* 上拉输入 */
    GPIO_InitTypeDef gpio_struct_init = {0};
    gpio_struct_init.Pin = KEY1_PIN;        
    gpio_struct_init.Mode= GPIO_MODE_INPUT;
    gpio_struct_init.Pull= GPIO_PULLUP;
    gpio_struct_init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(KEY1_GPIO,&gpio_struct_init);
    
    gpio_struct_init.Pin = KEY2_PIN;
    HAL_GPIO_Init(KEY2_GPIO,&gpio_struct_init);
    /* 下拉输入 */
    gpio_struct_init.Pin = KEY_UP_PIN;
    gpio_struct_init.Pull= GPIO_PULLDOWN;
    HAL_GPIO_Init(KEY_UP_GPIO,&gpio_struct_init);
}
/**
 * @brief       按键扫描函数
 * @note        该函数有响应优先级(同时按下多个按键): WK_UP > KEY2 > KEY1
 * @param       mode:0 / 1, 具体含义如下:
 *   @arg       0,  不支持连续按(当按键按下不放时, 只有第一次调用会返回键值,
 *                  必须松开以后, 再次按下才会返回其他键值)
 *   @arg       1,  支持连续按(当按键按下不放时, 每次调用该函数都会返回键值)
 * @retval      键值, 定义如下:
 *              KEY1_DOWN,   1, KEY1按下
 *              KEY2_DOWN,   2, KEY2按下
 *              KEY_UP_DOWN, 3, WKUP按下
 */
uint8_t key_scan(uint8_t mode)
{
    static uint8_t key_up = 1;  /* 按键是否时抬起状态 */
    uint8_t key_num = 0;
    if(mode) key_up = 1;   /* 是否支持连按 */
    
    if(key_up&& (KEY1 == 0||KEY2 == 0||KEY_UP == 1))
    {
        
        delay_ms(10);
        key_up = 0;
        
        if(KEY1 == 0)key_num = KEY1_DOWN;

        if(KEY2 == 0)key_num = KEY2_DOWN;

        if(KEY_UP == 1)key_num = KEY_UP_DOWN;
            
    }
    else if(KEY1 == 1 && KEY2 == 1 && KEY_UP == 0)
    {
        key_up = 1;
    }
    return key_num;
}

