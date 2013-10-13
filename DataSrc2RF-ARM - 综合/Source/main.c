//本程序通过USART2串口向外发送数据

#include "stm32f10x_lib.h"
//#include "stm32f10x_flash.h"
//#include "stm32f10x_nvic.h"
//#include "stm32f10x.h"
//#include "stm32_eval.h"
//#include "stm32f10x_crc.h"
#include <stdio.h>

#include "serial.h"
#include "rfcomm.h"

extern u8 SerialBuffer[50];
extern u8 SerialDataLength;
extern u8 RFBuffer[50];
extern u8 RFDataLength;

void initBoard(void);
void copyBuffer(u8 src[], u8* srcLength, u8 dst[], u8* dstLength);
void Delay(vu32 nCount)
{
	for(; nCount != 0; nCount--);
}

int main()
{
	
#ifdef DEBUG
  debug();
#endif

	initBoard();
	
	//数据源串口初始化
	USART_Configuration(DataSrcPort);
	USART_Configuration(RFPort);
	
	//波特率设置成功标志指示灯
	LED1_ON;
	LED2_ON;
	
	//指令发送与电能数据接收
	while(1)
	{
//		//测试USART2的数据发送和接收  通过！！！！
//		USART_WaitForData();
//		
//		Delay(0xffff);
//		
//		USART_SendCmd();
		
//		//测试USART1的数据发送和接收    通过！！！！
//		RF_RecvCmd();
//		
//		Delay(0xffff);
//		
//		RF_SendData();
		
		
//			arm接收RF发送同步指令
		RF_RecvCmd();
//			arm向电表发送参数测量指令
		  //DS_SendCmd();
		Delay(0xffff);
		copyBuffer(RFBuffer, &RFDataLength, SerialBuffer, &SerialDataLength);
		USART_SendCmd();
//			arm接收电表返回数据
		  //DS_RecvData();
		USART_WaitForData();
//			arm将收到的电参数发送给RF
		Delay(0xffff);
		copyBuffer(SerialBuffer, &SerialDataLength, RFBuffer, &RFDataLength);
		RF_SendData();
		
		
		
	}
	
}

void initBoard(void)
{
	RCC_Configuration();

	NVIC_Configuration();

	GPIO_Configuration();
}

void copyBuffer(u8 src[], u8* srcLength, u8 dst[], u8* dstLength)
{
	u8 idx;
	for(idx = 0; idx < *srcLength; idx++)
	{
		dst[idx] = src[idx];
	}
	*dstLength = *srcLength;
}

#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

void SystemInit(){}



