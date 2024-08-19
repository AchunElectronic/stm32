#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "LED.H"
#include "stdio.h"
uint8_t RxData;			//定义用于接收串口数据的变量

int main(void)
{
	/*模块初始化*/
//	OLED_Init();		//OLED初始化
	/*显示静态字符串*/
//	OLED_ShowString(1, 1, "RxData:");

	/*串口初始化*/
	Serial_Init(9600);		//串口初始化
    Serial_2_Init(115200);
    Serial_Printf("UART1");
    Serial_2_SendArray("UART2",5);
    uint8_t temp = 0;
	while (1)
	{
        data_process();

	}
}
