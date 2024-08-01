#include "led.h"

void led1_init(void)
{
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    GPIO_InitTypeDef led_init = {0};
    led_init.Pin = LED1_PIN;
    led_init.Mode = GPIO_MODE_OUTPUT_PP;
    led_init.Pull = GPIO_PULLUP;
    led_init.Speed = GPIO_SPEED_FREQ_LOW;
    
    HAL_GPIO_Init(LED1_GPIO,&led_init);
}

void led1_on(void)
{
#ifdef LED_ONSTATUS_LOW
    HAL_GPIO_WritePin(LED1_GPIO,LED1_PIN,GPIO_PIN_RESET);
#elif
    HAL_GPIO_WritePin(LED1_GPIO,LED1_PIN,GPIO_PIN_SET);
#endif
}

void led1_off(void)
{
#ifdef LED_ONSTATUS_LOW
    HAL_GPIO_WritePin(LED1_GPIO,LED1_PIN,GPIO_PIN_SET);
#else
    HAL_GPIO_WritePin(LED1_GPIO,LED1_PIN,GPIO_PIN_RESET);
#endif
}

GPIO_PinState led1_read(void)
{
    return HAL_GPIO_ReadPin(LED1_GPIO,LED1_PIN);
}

void led1_toggle(void)
{
    HAL_GPIO_TogglePin(LED1_GPIO,LED1_PIN);
}
