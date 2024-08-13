#include "oled.h"
#include "delay.h"
#include "font.h"
/* ����/���� ���� */
#define OLED_CMD        0       /* д���� */
#define OLED_DATA       1       /* д���� */

static uint8_t g_oled_gram[128*8][8];

void oled_gpio_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;

    OLED_I2C_SCL_CLK();
    OLED_I2C_SDA_CLK();
    
    gpio_initstruct.Pin = OLED_I2C_SCL_PIN;          
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;             
    gpio_initstruct.Pull = GPIO_PULLUP;                     
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;           
    HAL_GPIO_Init(OLED_I2C_SCL_PORT, &gpio_initstruct);
    
    gpio_initstruct.Pin = OLED_I2C_SDA_PIN;          
    HAL_GPIO_Init(OLED_I2C_SDA_PORT, &gpio_initstruct);
}

void oled_i2c_start(void)
{
    OLED_SCL_SET();
    OLED_SDA_SET();
    OLED_SDA_RESET();
    OLED_SCL_RESET();
}

void oled_i2c_stop(void)
{
    OLED_SCL_SET();
    OLED_SDA_RESET();
    OLED_SDA_SET();
}

void oled_i2c_ack(void)
{
    OLED_SCL_SET();
    OLED_SCL_RESET();
}

void oled_i2c_write_byte(uint8_t data)
{
    uint8_t i, tmp;
    tmp = data;
    
    for(i = 0; i < 8; i++)
    {
        if((tmp & 0x80) == 0x80)
            OLED_SDA_SET();
        else
            OLED_SDA_RESET();
        tmp = tmp << 1;
        OLED_SCL_SET();
        OLED_SCL_RESET();
    }
}
static void oled_wr_byte(uint8_t data, uint8_t cmd)
{
    switch( cmd )
    {
        case OLED_CMD:
        {
            oled_i2c_start();
            oled_i2c_write_byte(0x78);
            oled_i2c_ack();
            oled_i2c_write_byte(0x00);
            oled_i2c_ack();
            oled_i2c_write_byte(data);
            oled_i2c_ack();
            oled_i2c_stop();
            break;
        }
        case OLED_DATA :
        {
            oled_i2c_start();
            oled_i2c_write_byte(0x78);
            oled_i2c_ack();
            oled_i2c_write_byte(0x40);
            oled_i2c_ack();
            oled_i2c_write_byte(data);
            oled_i2c_ack();
            oled_i2c_stop();
            break;
        }
    }

}
/**
 * @brief       ����OLED��ʾ
 * @param       ��
 * @retval      ��
 */
void oled_display_on(void)
{
    oled_wr_byte(0X8D, OLED_CMD);   /* SET DCDC���� */
    oled_wr_byte(0X14, OLED_CMD);   /* DCDC ON */
    oled_wr_byte(0XAF, OLED_CMD);   /* DISPLAY ON */
}

/**
 * @brief       �ر�OLED��ʾ
 * @param       ��
 * @retval      ��
 */
void oled_display_off(void)
{
    oled_wr_byte(0X8D, OLED_CMD);   /* SET DCDC���� */
    oled_wr_byte(0X10, OLED_CMD);   /* DCDC OFF */
    oled_wr_byte(0XAE, OLED_CMD);   /* DISPLAY OFF */
}
void oled_write_cmd(uint8_t cmd)
{
    oled_i2c_start();
    oled_i2c_write_byte(0x78);
    oled_i2c_ack();
    oled_i2c_write_byte(0x00);
    oled_i2c_ack();
    oled_i2c_write_byte(cmd);
    oled_i2c_ack();
    oled_i2c_stop();
}

void oled_write_data(uint8_t data)
{
    oled_i2c_start();
    oled_i2c_write_byte(0x78);
    oled_i2c_ack();
    oled_i2c_write_byte(0x40);
    oled_i2c_ack();
    oled_i2c_write_byte(data);
    oled_i2c_ack();
    oled_i2c_stop();
}

void oled_init(void)
{
    oled_gpio_init();
    
    delay_ms(100);
    
    oled_write_cmd(0xAE);   /* �ر���ʾ */
    oled_write_cmd(0xD5);   /* ����ʱ�ӷ�Ƶ����,��Ƶ�� */
    oled_write_cmd(0x80);    /* [3:0],��Ƶ����;[7:4],��Ƶ�� */
    oled_write_cmd(0xA8);   /* ��������·�� */
    oled_write_cmd(0X3F);   /* Ĭ��0X3F(1/64) */
    oled_write_cmd(0xD3);   /* ������ʾƫ�� */
    oled_write_cmd(0X00);   /* Ĭ��Ϊ0 */

    oled_write_cmd(0x40);   /* ������ʾ��ʼ�� [5:0],����. */

    oled_write_cmd(0x8D);   /* ��ɱ����� */
    oled_write_cmd(0x14);   /* bit2������/�ر� */
    oled_write_cmd(0x20);   /* �����ڴ��ַģʽ */
    oled_write_cmd(0x02);   /* [1:0],00���е�ַģʽ;01���е�ַģʽ;10,ҳ��ַģʽ;Ĭ��10; */
    oled_write_cmd(0xA1);   /* ���ض�������,bit0:0,0->0;1,0->127; */
    oled_write_cmd(0xC8);   /* ����COMɨ�跽��;bit3:0,��ͨģʽ;1,�ض���ģʽ COM[N-1]->COM0;N:����·�� */
    oled_write_cmd(0xDA);   /* ����COMӲ���������� */
    oled_write_cmd(0x12);   /* [5:4]���� */
 
    oled_write_cmd(0x81);   /* �Աȶ����� */
    oled_write_cmd(0xEF);   /* 1~255;Ĭ��0X7F (��������,Խ��Խ��) */
    oled_write_cmd(0xD9);   /* ����Ԥ������� */
    oled_write_cmd(0xf1);   /* [3:0],PHASE 1;[7:4],PHASE 2; */
    oled_write_cmd(0xDB);   /* ����VCOMH ��ѹ���� */
    oled_write_cmd(0x30);   /* [6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc; */

    oled_write_cmd(0xA4);   /* ȫ����ʾ����;bit0:1,����;0,�ر�;(����/����) */
    oled_write_cmd(0xA6);   /* ������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ */
    oled_write_cmd(0xAF);   /* ������ʾ */
    
}

void oled_set_cursor(uint8_t x, uint8_t y)
{
    oled_write_cmd(0xB0 + y);
    oled_write_cmd((x & 0x0F) | 0x00);
    oled_write_cmd(((x & 0xF0) >> 4) | 0x10);
}

void oled_fill(uint8_t data)
{
    uint8_t i, j;
    for(i = 0; i < 8; i++)
    {
        oled_set_cursor(0, i);
        for(j = 0; j < 128; j++)
            oled_write_data(data);
    }
}

void oled_show_char(uint8_t x, uint8_t y, uint8_t num, uint8_t size)
{
    uint8_t i, j, page;
    
    num = num - ' ';
    page = size / 8;
    if(size % 8)
        page++;
    
    for(j = 0; j < page; j++)
    {
        oled_set_cursor(x, y + j);
        for(i = size / 2 * j; i < size /2 * (j + 1); i++)
        {
            if(size == 12)
                oled_write_data(ascii_6X12[num][i]);
            else if(size == 16)
                oled_write_data(ascii_8X16[num][i]);
            else if(size == 24)
                oled_write_data(ascii_12X24[num][i]);
                
        }
    }
}

void oled_show_string(uint8_t x, uint8_t y, char *p, uint8_t size)
{
    while(*p != '\0')
    {
        oled_show_char(x, y, *p, size);
        x += size/2;
        p++;
    }
}

void oled_show_chinese(uint8_t x, uint8_t y, uint8_t N, uint8_t size)
{
    uint16_t i, j;
    for(j = 0; j < size/8; j++)
    {
        oled_set_cursor(x, y + j);
        for(i = size *j; i < size * (j + 1); i++)
        {
            if(size == 16)
                oled_write_data(chinese_16x16[N][i]);
            else if(size == 24)
                oled_write_data(chinese_24x24[N][i]);
        }
    }
}

//void oled_show_image(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t *bmp)
//{
//    uint8_t i, j;
//    for(j = 0; j < height; j++)
//    {
//        oled_set_cursor(x, y + j);
//        for(i = 0; i < width; i++)
//            oled_write_data(bmp[width * j + i]);
//    }
//}
void oled_show_image(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t *bmp)
{
    uint8_t i, j;
    for(j = 0; j < height; j++)
    {
        oled_set_cursor(x, y + j);
        for(i = 0; i < width; i++)
            g_oled_gram[i][j] = bmp[width * j + i];
    }
}
/**
 * @brief       �����Դ浽OLED
 * @param       ��
 * @retval      ��
 */
void oled_refresh_gram(void)
{
    uint8_t i, n;

    for (i = 0; i < 8; i++)
    {
        oled_wr_byte (0xb0 + i, OLED_CMD); /* ����ҳ��ַ��0~7�� */
        oled_wr_byte (0x00, OLED_CMD);     /* ������ʾλ�á��е͵�ַ */
        oled_wr_byte (0x10, OLED_CMD);     /* ������ʾλ�á��иߵ�ַ */
        for (n = 0; n < 128; n++)
        {
            oled_wr_byte(g_oled_gram[n][i], OLED_DATA);
        }
    }
}

//void oled_temp(void)
//{
//    uint8_t i, j;
//    for(j = 0; j < 8; j++)
//    {
//        oled_set_cursor(0, 0 + j);
//        for(i = 0; i < 128; i++)
//            oled_write_data(g_oled_gram[i][j]);
//    }
//}
