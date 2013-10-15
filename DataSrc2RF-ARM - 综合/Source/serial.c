/**********************************************************************/

#include "serial.h"
#include "CPESchipdef.h"

/*
	serial buffer and data length local storage
*/
u8 SerialBuffer[SERIAL_BUFFER_SIZE];
u8 SerialDataLength = 0;  //记录每次收发数据的长度

SerialRxStatus RxFlag = RX_SUCCESS;

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
	u16 USART_Parity;
	u16 USART_WordLength;
	USART_InitTypeDef USART_InitStructure;
	
	if (USARTx == DataSrcPort)
	{
		USART_BaudRate = DATASRCPORT_BAUDRATE;
		USART_Parity = DATASRCPORT_PARITY;
		USART_WordLength = DATASRCPORT_WORDLENGTH;
	}
	else
	{
		if (USARTx == RFPort)
		{
			USART_BaudRate =  RFPORT_BAUDRATE;
			USART_Parity = RFPORT_PARITY;
			USART_WordLength = RFPORT_WORDLENGTH;
		}
	}
	USART_InitStructure.USART_BaudRate = USART_BaudRate;               //设置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength;  //设置数据位为8
	USART_InitStructure.USART_StopBits = USART_StopBits_1;     //设置停止位为1位
	USART_InitStructure.USART_Parity = USART_Parity;             //对于电表为偶校验，无线为无校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件流控
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //发送和接收
	
	USART_Init(USARTx, &USART_InitStructure);
	USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);//使能串口的发送
	USART_Cmd(USARTx,ENABLE);
}

/*******************************************************************************
* Function Name  : USART_Recv
* Description    : Save data from serial port.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART_Recv(void)
{
	u8 SerialBufferIdx = 0;
	
	SERIAL485_RX_ENABLE;
	
	USART_ReceiveData(DataSrcPort);
	while((SerialBufferIdx < SERIAL_BUFFER_SIZE) && (SerialBuffer[SerialBufferIdx-1] != SERIAL_END_CODE))
	{
		while(USART_GetFlagStatus(DataSrcPort, USART_FLAG_RXNE) == RESET )
		{
			// 不要等待太长，需要设置等待响应时间
		}
		SerialBuffer[SerialBufferIdx++] = USART_ReceiveData(DataSrcPort);
	}
	SerialDataLength = SerialBufferIdx;
	RxFlag = RX_SUCCESS;
}

/*******************************************************************************
* Function Name  : USART_Send
* Description    : Send Cmd from data source port.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART_Send(void)
{
	u8 SerialBufferIdx = 0;
	
	SERIAL485_TX_ENABLE;
	//发送TxBuffer数据给终端
	while(SerialBufferIdx < SerialDataLength+1)
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
