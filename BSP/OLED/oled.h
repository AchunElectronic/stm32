#ifndef __OLED_H__
#define __OLED_H__

#include "stdlib.h" 
#include "./SYSTEM/sys/sys.h"

/*  */
#define brightness 0x7f     /* �������� 1-0xff ����Ϊ0ʱ���� */
#define opposition 0        /* 0:������  1������  ע��������ָ�ڰ��෴*/
#define reverse_direction 1 /* 0�������� 1������ I2C�����FPS26->25*/

/* OLEDģʽ���� */
#define OLED_MODE       2   /* 2��2��I2Cģʽ  1������8080����ģʽ  0��4�ߴ���SPIģʽ */

/******************************************************************************************/
/* OLED I2Cģʽ���� ���� */
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/* ����ʹ��ǰ����I2C����һ���ܷ�����ʹ�� */
/* ע��:����������� OLED 2��I2Cģʽ���������� �������ģ��I2C������ѡ���������ż�������OLED */
#define OLED_I2C_SCL_CLK()      __HAL_RCC_GPIOB_CLK_ENABLE();
#define OLED_I2C_SCL_PORT       GPIOB
#define OLED_I2C_SCL_PIN        GPIO_PIN_6

#define OLED_I2C_SDA_CLK()      __HAL_RCC_GPIOB_CLK_ENABLE();
#define OLED_I2C_SDA_PORT       GPIOB
#define OLED_I2C_SDA_PIN        GPIO_PIN_7

#define OLED_SCL_RESET()        HAL_GPIO_WritePin(OLED_I2C_SCL_PORT, OLED_I2C_SCL_PIN, GPIO_PIN_RESET)
#define OLED_SCL_SET()          HAL_GPIO_WritePin(OLED_I2C_SCL_PORT, OLED_I2C_SCL_PIN, GPIO_PIN_SET)

#define OLED_SDA_RESET()        HAL_GPIO_WritePin(OLED_I2C_SDA_PORT, OLED_I2C_SDA_PIN, GPIO_PIN_RESET)
#define OLED_SDA_SET()          HAL_GPIO_WritePin(OLED_I2C_SDA_PORT, OLED_I2C_SDA_PIN, GPIO_PIN_SET)

/* OLED SPIģʽ���� ���� */
/* ע��:����������� OLED 4��SPIģʽ����ʱ�� ���Ŷ���. 8λ���ڷ���, ��������̫��,�Ͳ�����������. */

#define OLED_SPI_RST_PORT               GPIOG
#define OLED_SPI_RST_PIN                GPIO_PIN_15
#define OLED_SPI_RST_CLK_ENABLE()       do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)   /* PG��ʱ��ʹ�� */

#define OLED_SPI_CS_PORT                GPIOD
#define OLED_SPI_CS_PIN                 GPIO_PIN_6
#define OLED_SPI_CS_CLK_ENABLE()        do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)   /* PD��ʱ��ʹ�� */

#define OLED_SPI_RS_PORT                GPIOD
#define OLED_SPI_RS_PIN                 GPIO_PIN_3
#define OLED_SPI_RS_CLK_ENABLE()        do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)   /* PD��ʱ��ʹ�� */

#define OLED_SPI_SCLK_PORT              GPIOC
#define OLED_SPI_SCLK_PIN               GPIO_PIN_0
#define OLED_SPI_SCLK_CLK_ENABLE()      do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* PC��ʱ��ʹ�� */

#define OLED_SPI_SDIN_PORT              GPIOC
#define OLED_SPI_SDIN_PIN               GPIO_PIN_1
#define OLED_SPI_SDIN_CLK_ENABLE()      do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* PC��ʱ��ʹ�� */

/******************************************************************************************/

/* OLED SPIģʽ��ض˿ڿ��ƺ��� ���� 
 * ע��:OLED_RST/OLED_CS/OLED_RS,�������Ǻ�80����ģʽ���õ�,��80ģʽҲ����ʵ����3������!
 */
#define OLED_RST(x)     do{ x ? \
                                  HAL_GPIO_WritePin(OLED_SPI_RST_PORT, OLED_SPI_RST_PIN, GPIO_PIN_SET) : \
                                  HAL_GPIO_WritePin(OLED_SPI_RST_PORT, OLED_SPI_RST_PIN, GPIO_PIN_RESET); \
                        }while(0)       /* ����RST���� */

#define OLED_CS(x)      do{ x ? \
                                  HAL_GPIO_WritePin(OLED_SPI_CS_PORT, OLED_SPI_CS_PIN, GPIO_PIN_SET) : \
                                  HAL_GPIO_WritePin(OLED_SPI_CS_PORT, OLED_SPI_CS_PIN, GPIO_PIN_RESET); \
                        }while(0)       /* ����CS���� */
#define OLED_RS(x)      do{ x ? \
                                  HAL_GPIO_WritePin(OLED_SPI_RS_PORT, OLED_SPI_RS_PIN, GPIO_PIN_SET) : \
                                  HAL_GPIO_WritePin(OLED_SPI_RS_PORT, OLED_SPI_RS_PIN, GPIO_PIN_RESET); \
                        }while(0)       /* ����RS���� */
                              
#define OLED_SCLK(x)    do{ x ? \
                                  HAL_GPIO_WritePin(OLED_SPI_SCLK_PORT, OLED_SPI_SCLK_PIN, GPIO_PIN_SET) : \
                                  HAL_GPIO_WritePin(OLED_SPI_SCLK_PORT, OLED_SPI_SCLK_PIN, GPIO_PIN_RESET); \
                        }while(0)       /* ����SCLK���� */
#define OLED_SDIN(x)    do{ x ? \
                                  HAL_GPIO_WritePin(OLED_SPI_SDIN_PORT, OLED_SPI_SDIN_PIN, GPIO_PIN_SET) : \
                                  HAL_GPIO_WritePin(OLED_SPI_SDIN_PORT, OLED_SPI_SDIN_PIN, GPIO_PIN_RESET); \
                        }while(0)       /* ����SDIN���� */

/* OLED 80����ģʽWR,RD�˿ڿ��ƺ��� ���� */
#define OLED_WR(x)      do{ x ? \
                                  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET) :  \
                                  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET); \
                        } while (0)     /* ����WR���� */

#define OLED_RD(x)      do{ x ? \
                                  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET) : \
                                  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET); \
                        }while(0)       /* ����RD���� */

/* ����/���� ���� */
#define OLED_CMD        0       /* д���� */
#define OLED_DATA       1       /* д���� */

/******************************************************************************************/
    
static void oled_wr_byte(uint8_t data, uint8_t cmd);    /* дһ���ֽڵ�OLED */
static uint32_t oled_pow(uint8_t m, uint8_t n);         /* OLED��ƽ������ */


void oled_init(void);           /* OLED��ʼ�� */
void oled_clear(void);          /* OLED���� */
void oled_display_on(void);     /* ����OLED��ʾ */
void oled_display_off(void);    /* �ر�OLED��ʾ */
void oled_refresh_gram(void);   /* �����Դ浽OLED */ 
void oled_draw_point(uint8_t x, uint8_t y, uint8_t dot);    /* OLED���� */
void oled_fill(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t dot);                /* OLED������� */
void oled_show_char(uint8_t x, uint8_t y, uint8_t chr, uint8_t size, uint8_t mode);         /* OLED��ʾ�ַ� */
void oled_show_num(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size);          /* OLED��ʾ���� */
void oled_show_string(uint8_t x, uint8_t y, const char *p, uint8_t size);                   /*OLED��ʾ�ַ���*/
void oled_show_image(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t *bmp);     /* OLED��ʾͼƬ */
void oled_show_logo(void);                                                                  /* ��ʾlogo */

#endif




