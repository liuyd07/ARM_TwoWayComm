
#include "rfcomm.h"

u8 RFBuffer[50];
u8 RFBufferSize = 50;
u8 RFDataLength = 0;

/*******************************************************************************
* Function Name  : RF_RecvCmd
* Description    : Save data from serial port.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RF_RecvCmd(void)
{
	u8 RFBufferIdx = 0;
	
	USART_ReceiveData(RFPort);
	while((RFBufferIdx < RFBufferSize) && (RFBuffer[RFBufferIdx-1] != SERIAL_END_CODE))
	{
		while(USART_GetFlagStatus(RFPort, USART_FLAG_RXNE) == RESET )
		{}
		RFBuffer[RFBufferIdx++] = USART_ReceiveData(RFPort);
	}
	RFDataLength = RFBufferIdx;
}

/*******************************************************************************
* Function Name  : RF_SendData
* Description    : Send Cmd from data source port.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RF_SendData(void)
{
	u8 RFBufferIdx = 0;
	
	//发送Buffer数据给终端
	while(RFBufferIdx < RFDataLength)
	{
		USART_SendData(RFPort, RFBuffer[RFBufferIdx++]);
		while(USART_GetFlagStatus(RFPort, USART_FLAG_TXE) == RESET){};		
	}
}
