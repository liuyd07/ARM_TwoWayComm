//本程序通过USART2串口向外发送数据
#ifndef __SERIAL_H
#define __SERIAL_H

#include "stm32f10x.h"
#include "CPESchipdef.h"

/*****************通信串口定义******************/
//无线通信端口
#define RFPORT_BAUDRATE 					38400
#define RFPORT_PARITY							USART_Parity_No
#define RFPORT_WORDLENGTH         USART_WordLength_8b

//485通信端口
#define DATASRCPORT_BAUDRATE      2400
#define DATASRCPORT_PARITY				USART_Parity_Even
#define DATASRCPORT_WORDLENGTH    USART_WordLength_9b //注意，奇偶校验时数据位9位，无校验时数据位是8位

/*****************通信基本定义******************/
#define SERIAL_END_CODE           0x16
#define SERIAL_BUFFER_SIZE        50         //串口缓存大小在此更改

/******************typedef*********************/
typedef  struct
{
	u8* strData;
	u8  strLength;
}serialString;

typedef enum {RX_FAILED = 0, RX_SUCCESS = !RX_FAILED} SerialRxStatus;

/******************functions*******************/
void InitUSARTPort(USART_TypeDef* USARTx);

void USART_Configuration(USART_TypeDef* USARTx); //初始化USARTx串口设置

void USART_Send(void);
void USART_Recv(void);

#endif
