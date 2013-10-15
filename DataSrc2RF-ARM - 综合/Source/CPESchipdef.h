/*****************************************************
���ļ�������CPES����ƽ̨�Ļ��������������ܽš��˿ڡ�����ϵͳ������������ʼ�����������ݡ�
���ļ��ж��������������ļ��в����ظ��������ļ���ʵ�־��뱾��·���ʵ�������޹ء�
*****************************************************/
#ifndef __CPESCHIPDEF_H
#define __CPESCHIPDEF_H

#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "type.h"

/**************�˿ڶ���********************/
//data source port
#define DATASRC_TX_PIN            GPIO_Pin_2
#define DATASRC_RX_PIN            GPIO_Pin_3
//other ports
#define SERIAL485ENABLE_PIN       GPIO_Pin_4
#define LED1_PIN                  GPIO_Pin_5
#define LED2_PIN                  GPIO_Pin_6
//Sensor
#define TEMP_SENSOR_PORT					GPIO_Pin_7 //�¶ȴ�����
#define RADIO_SENSOR_PORT					GPIO_Pin_0 //���͵紫����
//RF transfer port
#define RFPORT_TX_PIN             GPIO_Pin_9
#define RFPORT_RX_PIN             GPIO_Pin_10

/****************����ͨ�Ų�������************/
//����ͨ�Ŷ˿�
#define RFPort       							USART1
#define GPIO_Remap_RFPort         GPIO_Remap_USART1

//485ͨ�Ŷ˿�
#define DataSrcPort  							USART2
#define GPIO_Remap_DataSrcPort    GPIO_Remap_USART2

/****************�ڵ������������************/
#define NODE_NUM									1  //ÿ���ڵ�ž�������sink�ڵ��Ϊ0
#define	AMMETER_ADDR              {0x04, 0x00, 0x00, 0x00, 0x00, 0x00}
#define AMMETER_NUM								1

/**************ϵͳ����********************/
#define LED1_ON                   GPIO_SetBits(GPIOA, LED1_PIN) //LED Test1 ����
#define LED1_OFF 			            GPIO_ResetBits(GPIOA, LED1_PIN) // LED Test1 ��
#define LED2_ON  			            GPIO_SetBits(GPIOA, LED2_PIN) //LED Test2 ����
#define LED2_OFF 			            GPIO_ResetBits(GPIOA, LED2_PIN) // LED Test2 ��

#define SERIAL485_TX_ENABLE 	    GPIO_SetBits(GPIOA, SERIAL485ENABLE_PIN)  //ʹ��485Tx��485CS�ø�
#define SERIAL485_RX_ENABLE 	    GPIO_ResetBits(GPIOA, SERIAL485ENABLE_PIN)  //ʹ��485Rx��485CS�õ�

/***************function******************/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);

void getNodeInfo(void);

void Delay(vu32 nCount);

#endif

