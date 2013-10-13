/**********************************************************************/

#include "serial.h"
#include "CPESchipdef.h"
#include <stdio.h>

GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;

u8 TxBuffer[16] = {0x68,0x04,0x00,0x00,0x00,0x00,0x00,0x68,0x11,0x04,0x33,0x34,0x34,0x35,0xB9,0x16};//测试缓存
u8 TxBufferSize = 16;
u8 RxBuffer[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
u8 RxBufferSize = 16;

u8 SerialBufferSize = 50; //串口缓存大小可更改
u8 SerialBuffer[50];
u8 SerialDataLength = 0;  //记录每次收发数据的长度

u8 TxCounter = 0, RxCounter = 0;



/*******************************************************************************
* Function Name  : USART_Configuration
* Description    : Configures the different serial USART port.
* Input          : USART_TypeDef* USARTx
* Output         : None
* Return         : None
*******************************************************************************/
void USART_Configuration(USART_TypeDef* USARTx)
{
	u32 USART_BaudRate;
	if (USARTx == DataSrcPort)
		USART_BaudRate = DATASRCPORT_BAUDRATE;
	else
		if (USARTx == RFPort)
			USART_BaudRate =  RFPORT_BAUDRATE;
	USART_InitStructure.USART_BaudRate = USART_BaudRate;               //设置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //设置数据位为8
	USART_InitStructure.USART_StopBits = USART_StopBits_1;     //设置停止位为1位
	USART_InitStructure.USART_Parity = USART_Parity_No;             //无奇偶校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件流控
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //发送和接收
	
	USART_Init(USARTx, &USART_InitStructure);
	USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);//使能串口的发送
	USART_Cmd(USARTx,ENABLE);
}

/*******************************************************************************
* Function Name  : USART_WaitForData
* Description    : Save data from serial port.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART_WaitForData(void)
{
	u8 SerialBufferIdx = 0;
	
	SERIAL485_RX_ENABLE;
	
	USART_ReceiveData(DataSrcPort);
	while((SerialBufferIdx < SerialBufferSize) && (SerialBuffer[SerialBufferIdx-1] != SERIAL_END_CODE))
	{
		while(USART_GetFlagStatus(DataSrcPort, USART_FLAG_RXNE) == RESET )
		{}
		SerialBuffer[SerialBufferIdx++] = USART_ReceiveData(DataSrcPort);
	}
	SerialDataLength = SerialBufferIdx;
}

/*******************************************************************************
* Function Name  : USART_SendCmd
* Description    : Send Cmd from data source port.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART_SendCmd(void)
{
	u8 SerialBufferIdx = 0;
	
	SERIAL485_TX_ENABLE;
	//发送TxBuffer数据给终端
	while(SerialBufferIdx < SerialDataLength)
	{
		USART_SendData(DataSrcPort, SerialBuffer[SerialBufferIdx++]);
		while(USART_GetFlagStatus(DataSrcPort, USART_FLAG_TXE) == RESET){};		
	}
}

/*******************************************************************************
* Function Name  : initUSARTPort
* Description    : Configures the different serial USART port.
* Input          : USART_TypeDef* USARTx
* Output         : None
* Return         : None
*******************************************************************************/
void InitUSARTPort(USART_TypeDef* USARTx)
{
	RCC_Configuration();

	NVIC_Configuration();

	GPIO_Configuration();
	
	USART_Configuration(RFPort);
}
