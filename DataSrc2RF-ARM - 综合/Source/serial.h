//本程序通过USART2串口向外发送数据
#ifndef __SERIAL_H
#define __SERIAL_H

#include "stm32f10x_lib.h"
#include "CPESchipdef.h"

/*****************通信串口定义******************/
//无线通信端口
#define RFPORT_BAUDRATE 					38400

//485通信端口
#define DATASRCPORT_BAUDRATE      2400

/*****************通信基本定义******************/
#define SERIAL_END_CODE           0x16

/******************functions*******************/
void InitUSARTPort(USART_TypeDef* USARTx);

void USART_Configuration(USART_TypeDef* USARTx); //初始化USARTx串口设置

void USART_SendCmd(void);
void USART_WaitForData(void);

#endif
