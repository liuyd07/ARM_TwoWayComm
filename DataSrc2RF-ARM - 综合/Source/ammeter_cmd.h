#ifndef __AMMETER_CMD_H
#define __AMMETER_CMD_H

#include <stdio.h>
#include "serial.h"

#define START_CODE          0x68
#define END_CODE            0x16
#define ADDR_LENGTH         6

//Comand List
#define READ_CMD_LENGTH          16
#define NUM_OF_PARAS				     4
#define ID_CODE_LENGTH					 4

#define READ_CURRENT						 0x01
#define READ_VOLTAGE						 0x02
#define READ_POWER               0x03
#define READ_POWER_FACTOR        0x04

#define READ_CMD_CODE				     0x11

#define READ_CURRENT_CODE        ((u32)0x33343535)
#define READ_VOLTAGE_CODE        ((u32)0x33343935)
#define READ_POWER_CODE          ((u32)0x33343435)
#define READ_POWER_FACTOR_CODE   ((u32)0x33343835)


typedef struct
{
	u8 startCode;
	u8 addr[6];
	u8 addrEndCode;
	u8 cmdCode;
	u8 idCode[4];
	u8 checkCode;
	u8 endCode;
}AmmeterCmdStruct;

typedef u8 AMTCmdType;

u8 getCheckCode(void);
void AMT_RecvData(void);
void AMT_SendCmd(void);
void AMT_getAmtPara(void);
void AMT_copyBuffer(void);
AmmeterCmdStruct generateCmd(AMTCmdType cmdType);

#endif

