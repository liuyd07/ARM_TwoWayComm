#ifndef __AMMETER_CMD_H
#define __AMMETER_CMD_H

#include <stdio.h>
#include "stm32f10x_map.h"

#define START_CODE          0x68
#define END_CODE            0x68
#define ADDR_LENGTH         12

//Comand List
#define READ_VOLTAGE        ((u32)0x00010204)

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


void decodeCmd(void);
void encodeCmd(void);

#endif
