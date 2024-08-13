#include "oled.h"
#include "delay.h"
#include "font.h"
/* 命令/数据 定义 */
#define OLED_CMD        0       /* 写命令 */
#define OLED_DATA       1       /* 写数据 */

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
 * @brief       开启OLED显示
 * @param       无
 * @retval      无
 */
void oled_display_on(void)
{
    oled_wr_byte(0X8D, OLED_CMD);   /* SET DCDC命令 */
    oled_wr_byte(0X14, OLED_CMD);   /* DCDC ON */
    oled_wr_byte(0XAF, OLED_CMD);   /* DISPLAY ON */
}

/**
 * @brief       关闭OLED显示
 * @param       无
 * @retval      无
 */
void oled_display_off(void)
{
    oled_wr_byte(0X8D, OLED_CMD);   /* SET DCDC命令 */
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
    
    oled_write_cmd(0xAE);   /* 关闭显示 */
    oled_write_cmd(0xD5);   /* 设置时钟分频因子,震荡频率 */
    oled_write_cmd(0x80);    /* [3:0],分频因子;[7:4],震荡频率 */
    oled_write_cmd(0xA8);   /* 设置驱动路数 */
    oled_write_cmd(0X3F);   /* 默认0X3F(1/64) */
    oled_write_cmd(0xD3);   /* 设置显示偏移 */
    oled_write_cmd(0X00);   /* 默认为0 */

    oled_write_cmd(0x40);   /* 设置显示开始行 [5:0],行数. */

    oled_write_cmd(0x8D);   /* 电荷泵设置 */
    oled_write_cmd(0x14);   /* bit2，开启/关闭 */
    oled_write_cmd(0x20);   /* 设置内存地址模式 */
    oled_write_cmd(0x02);   /* [1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10; */
    oled_write_cmd(0xA1);   /* 段重定义设置,bit0:0,0->0;1,0->127; */
    oled_write_cmd(0xC8);   /* 设置COM扫描方向;bit3:0,普通模式;1,重定义模式 COM[N-1]->COM0;N:驱动路数 */
    oled_write_cmd(0xDA);   /* 设置COM硬件引脚配置 */
    oled_write_cmd(0x12);   /* [5:4]配置 */
 
    oled_write_cmd(0x81);   /* 对比度设置 */
    oled_write_cmd(0xEF);   /* 1~255;默认0X7F (亮度设置,越大越亮) */
    oled_write_cmd(0xD9);   /* 设置预充电周期 */
    oled_write_cmd(0xf1);   /* [3:0],PHASE 1;[7:4],PHASE 2; */
    oled_write_cmd(0xDB);   /* 设置VCOMH 电压倍率 */
    oled_write_cmd(0x30);   /* [6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc; */

    oled_write_cmd(0xA4);   /* 全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏) */
    oled_write_cmd(0xA6);   /* 设置显示方式;bit0:1,反相显示;0,正常显示 */
    oled_write_cmd(0xAF);   /* 开启显示 */
    
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
 * @brief       更新显存到OLED
 * @param       无
 * @retval      无
 */
void oled_refresh_gram(void)
{
    uint8_t i, n;

    for (i = 0; i < 8; i++)
    {
        oled_wr_byte (0xb0 + i, OLED_CMD); /* 设置页地址（0~7） */
        oled_wr_byte (0x00, OLED_CMD);     /* 设置显示位置—列低地址 */
        oled_wr_byte (0x10, OLED_CMD);     /* 设置显示位置—列高地址 */
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
