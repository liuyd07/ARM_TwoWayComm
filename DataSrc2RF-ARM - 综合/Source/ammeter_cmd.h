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
#define READ_CMD_LENGTH              16
#define NUM_OF_PARAS				         4
#define ID_CODE_LENGTH					     4

#define READ_CURRENT						     0x01
#define READ_VOLTAGE						     0x02
#define READ_POWER                   0x03
#define READ_POWER_FACTOR            0x04

#define READ_CMD_CODE				         0x11

#define DATA_SECTION_LENGTH_CODE     0x04

/*
  这里指令采用正序，已经加上0x33，和union的数据类型相适应。
*/
#define IDENTITY_CODE_LENGTH         4
#define READ_CURRENT_CODE            ((u32)0x35353433)
#define READ_VOLTAGE_CODE            ((u32)0x35393433)
#define READ_POWER_CODE              ((u32)0x35343433)
#define READ_POWER_FACTOR_CODE       ((u32)0x35383433)

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

