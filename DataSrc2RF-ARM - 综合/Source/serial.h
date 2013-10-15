//������ͨ��USART2�������ⷢ������
#ifndef __SERIAL_H
#define __SERIAL_H

#include "stm32f10x.h"
#include "CPESchipdef.h"

/*****************ͨ�Ŵ��ڶ���******************/
//����ͨ�Ŷ˿�
#define RFPORT_BAUDRATE 					38400
#define RFPORT_PARITY							USART_Parity_No
#define RFPORT_WORDLENGTH         USART_WordLength_8b

//485ͨ�Ŷ˿�
#define DATASRCPORT_BAUDRATE      2400
#define DATASRCPORT_PARITY				USART_Parity_Even
#define DATASRCPORT_WORDLENGTH    USART_WordLength_9b //ע�⣬��żУ��ʱ����λ9λ����У��ʱ����λ��8λ

/*****************ͨ�Ż�������******************/
#define SERIAL_END_CODE           0x16
#define SERIAL_BUFFER_SIZE        50         //���ڻ����С�ڴ˸���

/******************typedef*********************/
typedef  struct
{
	u8* strData;
	u8  strLength;
}serialString;

typedef enum {RX_FAILED = 0, RX_SUCCESS = !RX_FAILED} SerialRxStatus;

/******************functions*******************/
void InitUSARTPort(USART_TypeDef* USARTx);

void USART_Configuration(USART_TypeDef* USARTx); //��ʼ��USARTx��������

void USART_Send(void);
void USART_Recv(void);

#endif
