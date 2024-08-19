#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>

#define RING_BUF_DATA_TYPE     unsigned char
void Serial_2_Init(uint32_t baudrate);
void Serial_Init(uint32_t baudrate);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_2_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_Printf(char *format, ...);

uint8_t Serial_GetRxFlag(void);
uint8_t Serial_GetRxData(void);

uint8_t ring_buf_read(RING_BUF_DATA_TYPE* pdata);
void data_process(void);

#endif
