#include "key.h"
#include "delay.h"

void key_init(void)
{
    KEY1_CKL_EN();      /* ʹ��ʱ�� */
    KEY2_CKL_EN();
    KEY_UP_CKL_EN();
    /* �������� */
    GPIO_InitTypeDef gpio_struct_init = {0};
    gpio_struct_init.Pin = KEY1_PIN;        
    gpio_struct_init.Mode= GPIO_MODE_INPUT;
    gpio_struct_init.Pull= GPIO_PULLUP;
    gpio_struct_init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(KEY1_GPIO,&gpio_struct_init);
    
    gpio_struct_init.Pin = KEY2_PIN;
    HAL_GPIO_Init(KEY2_GPIO,&gpio_struct_init);
    /* �������� */
    gpio_struct_init.Pin = KEY_UP_PIN;
    gpio_struct_init.Pull= GPIO_PULLDOWN;
    HAL_GPIO_Init(KEY_UP_GPIO,&gpio_struct_init);
}
/**
 * @brief       ����ɨ�躯��
 * @note        �ú�������Ӧ���ȼ�(ͬʱ���¶������): WK_UP > KEY2 > KEY1
 * @param       mode:0 / 1, ���庬������:
 *   @arg       0,  ��֧��������(���������²���ʱ, ֻ�е�һ�ε��û᷵�ؼ�ֵ,
 *                  �����ɿ��Ժ�, �ٴΰ��²Ż᷵��������ֵ)
 *   @arg       1,  ֧��������(���������²���ʱ, ÿ�ε��øú������᷵�ؼ�ֵ)
 * @retval      ��ֵ, ��������:
 *              KEY1_DOWN,   1, KEY1����
 *              KEY2_DOWN,   2, KEY2����
 *              KEY_UP_DOWN, 3, WKUP����
 */
uint8_t key_scan(uint8_t mode)
{
    static uint8_t key_up = 1;  /* �����Ƿ�ʱ̧��״̬ */
    uint8_t key_num = 0;
    if(mode) key_up = 1;   /* �Ƿ�֧������ */
    
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

