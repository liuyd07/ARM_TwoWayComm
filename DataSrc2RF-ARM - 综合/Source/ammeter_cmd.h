#ifndef __AMMETER_CMD_H
#define __AMMETER_CMD_H

#include <stdio.h>
#include "stm32f10x.h"
#include "type.h"

/*********************智能电表指令规范***************************/
#define START_CODE                   0x68
#define END_CODE                     0x16
#define ADDR_LENGTH                  6

//Comand List
#define NUM_OF_PARAS				         12 //指令个数

#define READ_CMD_LENGTH              16
#define ID_CODE_LENGTH					     4

#define READ_CURRENT						     0x01
#define READ_VOLTAGE						     0x02
#define READ_POWER                   0x03
#define READ_POWER_FACTOR            0x04
#define READ_HARMONIC_01						 0x05
#define READ_HARMONIC_03						 0x06         
#define READ_HARMONIC_05						 0x07         
#define READ_HARMONIC_07						 0x08         
#define READ_HARMONIC_09						 0x09         
#define READ_HARMONIC_11						 0x0A        
#define READ_HARMONIC_13						 0x0B        
#define READ_HARMONIC_15						 0x0C        

#define READ_CMD_CODE				         0x11

#define DATA_SECTION_LENGTH_CODE     0x04

/*
  这里指令采用正序，已经加上0x33，和union的数据类型相适应。
	每次修改指令需要改3个地方，下面的指令和上面的操作号，以及ammeter_cmd.c中的switch语句。
	比较繁琐，有待改进。
*/
#define IDENTITY_CODE_LENGTH         4
#define READ_CURRENT_CODE            ((u32)0x35353433)//02020100
#define READ_VOLTAGE_CODE            ((u32)0x35343433)//02010100
#define READ_POWER_CODE              ((u32)0x35383433)//02050100
#define READ_POWER_FACTOR_CODE       ((u32)0x35393433)//02060100
#define READ_HARMONIC_01_CODE        ((u32)0x353E3434)//A???1????? 020B0101
#define READ_HARMONIC_03_CODE        ((u32)0x353E3436)//A???3????? 020B0103
#define READ_HARMONIC_05_CODE        ((u32)0x353E3438)//A???5????? 020B0105
#define READ_HARMONIC_07_CODE        ((u32)0x353E343A)//A???7????? 020B0107
#define READ_HARMONIC_09_CODE        ((u32)0x353E343C)//A???9????? 020B0109
#define READ_HARMONIC_11_CODE        ((u32)0x353E343E)//A???11????? 020B010B
#define READ_HARMONIC_13_CODE        ((u32)0x353E3440)//A???13????? 020B010D
#define READ_HARMONIC_15_CODE        ((u32)0x353E3442)//A???15????? 020B010F

/*********************typedef***************************/

/*specific ammeter command structure-------------------*/
typedef struct __AmmeterCmdStruct{
	u8 startCode;
	u8 addr[ADDR_LENGTH];
	u8 addrEndCode;
	u8 cmdCode;
	u8 dataSectionLength;
	u8 idCode[IDENTITY_CODE_LENGTH];
	u8 checkCode;
	u8 endCode;
}AmmeterCmdStruct;

/*easy way to send ammeter command in array-------------*/
typedef union {
	u8 all[READ_CMD_LENGTH];
	AmmeterCmdStruct ammeterCmdStruct;
} AMTReadCmd;

/*identity code-----------------------------------------*/
typedef union {
	u32 code;
	u8  codeArr[IDENTITY_CODE_LENGTH];
} IdentityCode;

typedef u8 AMTCmdType;

typedef u8 AMT_Addr[ADDR_LENGTH];

/***********************function*************************/
u8 getCheckCode(AMTReadCmd cmd);
AMTReadCmd generateCmd(AMT_Addr addr, AMTCmdType cmdType);

#endif

