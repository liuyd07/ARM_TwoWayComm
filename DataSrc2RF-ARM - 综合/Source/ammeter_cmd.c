#include "ammeter_cmd.h"

u8 commandForAmt1Current[16] = {0x68, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x11, 0x04, 0x33, 0x34, 0x38, 0x35, 0xBD, 0x16};
u8 commandLength = 16;

AMTReadCmd amtCmd;

/****************************************************************
* Function Name  : getCheckCode
* Description    : calculate the check code of ammeter command.
* Input          : None
* Output         : None
* Return         : u8 checkCode
****************************************************************/
u8 getCheckCode(AMTReadCmd cmd)
{
	u8 idx = 0;
	u8 sum = 0;
	for (idx = 0;idx < commandLength-2;idx++)
	{
		sum += cmd.all[idx];
	}
	cmd.ammeterCmdStruct.checkCode = sum;
	return sum;
}

/****************************************************************
* Function Name  : generateCmd
* Description    : Build require command for specific electical parameter.
* Input          : None
* Output         : None
* Return         : None
****************************************************************/
AMTReadCmd generateCmd(AMT_Addr addr, AMTCmdType cmdType)
{
	u8 idx;
	IdentityCode idCode;
	AMTReadCmd cmd;
	
	cmd.ammeterCmdStruct.startCode         =  START_CODE;
	cmd.ammeterCmdStruct.addrEndCode       =  START_CODE;
	cmd.ammeterCmdStruct.endCode           =  END_CODE;
	
	for(idx = 0;idx < ADDR_LENGTH;idx++)
	{
		cmd.ammeterCmdStruct.addr[idx]	     =  addr[idx];  //地址赋值。没有找到好的方法，只能先用数组。
	}
	
	cmd.ammeterCmdStruct.cmdCode           =  READ_CMD_CODE;
	cmd.ammeterCmdStruct.dataSectionLength = DATA_SECTION_LENGTH_CODE;
	
	switch(cmdType)                           //这种方法扩展性很好，但比较冗长，有待改进
	{
		case READ_CURRENT:
			idCode.code = READ_CURRENT_CODE;break;
		case READ_VOLTAGE:
			idCode.code = READ_VOLTAGE_CODE;break;
		case READ_POWER:
			idCode.code = READ_POWER_CODE;break;
		case READ_POWER_FACTOR:
			idCode.code = READ_POWER_FACTOR_CODE;break;
		default: break;
	}
	
	for(idx = 0;idx < ID_CODE_LENGTH;idx++)
	{
		cmd.ammeterCmdStruct.idCode[idx]     = idCode.codeArr[idx];
	}
	
	cmd.ammeterCmdStruct.checkCode         =	getCheckCode(cmd);
	amtCmd = cmd;
	return cmd;
}

