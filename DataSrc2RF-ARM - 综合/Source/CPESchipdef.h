/*****************************************************
本文件定义了CPES测试平台的基本参数，包括管脚、端口、基本系统操作、基本初始化函数等内容。
本文件中定义内容在其他文件中不再重复，其他文件的实现均与本电路板的实际配置无关。
*****************************************************/
#ifndef __CPESCHIPDEF_H
#define __CPESCHIPDEF_H

#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "type.h"

/**************端口定义********************/
//data source port
#define DATASRC_TX_PIN            GPIO_Pin_2
#define DATASRC_RX_PIN            GPIO_Pin_3
//other ports
#define SERIAL485ENABLE_PIN       GPIO_Pin_4
#define LED1_PIN                  GPIO_Pin_5
#define LED2_PIN                  GPIO_Pin_6
//Sensor
#define TEMP_SENSOR_PORT					GPIO_Pin_7 //温度传感器
#define RADIO_SENSOR_PORT					GPIO_Pin_0 //热释电传感器
//RF transfer port
#define RFPORT_TX_PIN             GPIO_Pin_9
#define RFPORT_RX_PIN             GPIO_Pin_10

/****************串口通信参数定义************/
//无线通信端口
#define RFPort       							USART1
#define GPIO_Remap_RFPort         GPIO_Remap_USART1

//485通信端口
#define DataSrcPort  							USART2
#define GPIO_Remap_DataSrcPort    GPIO_Remap_USART2

/****************节点外设参数定义************/
#define NODE_NUM									1  //每个节点号均独立，sink节点号为0
#define	AMMETER_ADDR              {0x04, 0x00, 0x00, 0x00, 0x00, 0x00}
#define AMMETER_NUM								1

/**************系统操作********************/
#define LED1_ON                   GPIO_SetBits(GPIOA, LED1_PIN) //LED Test1 点亮
#define LED1_OFF 			            GPIO_ResetBits(GPIOA, LED1_PIN) // LED Test1 灭
#define LED2_ON  			            GPIO_SetBits(GPIOA, LED2_PIN) //LED Test2 点亮
#define LED2_OFF 			            GPIO_ResetBits(GPIOA, LED2_PIN) // LED Test2 灭

#define SERIAL485_TX_ENABLE 	    GPIO_SetBits(GPIOA, SERIAL485ENABLE_PIN)  //使能485Tx，485CS置高
#define SERIAL485_RX_ENABLE 	    GPIO_ResetBits(GPIOA, SERIAL485ENABLE_PIN)  //使能485Rx，485CS置低

/***************function******************/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);

void getNodeInfo(void);

void Delay(vu32 nCount);

#endif

