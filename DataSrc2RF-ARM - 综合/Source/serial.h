//������ͨ��USART2�������ⷢ������
#ifndef __SERIAL_H
#define __SERIAL_H

#include "stm32f10x_lib.h"
#include "CPESchipdef.h"

/*****************ͨ�Ŵ��ڶ���******************/
//����ͨ�Ŷ˿�
#define RFPORT_BAUDRATE 					38400

//485ͨ�Ŷ˿�
#define DATASRCPORT_BAUDRATE      2400

/*****************ͨ�Ż�������******************/
#define SERIAL_END_CODE           0x16

/******************functions*******************/
void InitUSARTPort(USART_TypeDef* USARTx);

void USART_Configuration(USART_TypeDef* USARTx); //��ʼ��USARTx��������

void USART_SendCmd(void);
void USART_WaitForData(void);

#endif
