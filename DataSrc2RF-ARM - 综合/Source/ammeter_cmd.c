#include "ammeter_cmd.h"

u8 commandForAmt1Current[16] = {0x68, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x11, 0x04, 0x33, 0x34, 0x38, 0x35, 0xBD, 0x16};
u8 commandLength = 16;
u8 AMT_addr[6] = AMMETER_ADDR;

union
{
	u8 all[16];
	AmmeterCmdStruct ammeterCmdStruct;
}amtCmd;

extern u8 SerialBuffer[50];
extern u8 SerialDataLength;

/****************************************************************
* Function Name  : getCheckCode
* Description    : calculate the check code of ammeter command.
* Input          : None
* Output         : None
* Return         : u8 checkCode
****************************************************************/
u8 getCheckCode(void)
{
	u8 idx = 0;
	u8 sum = 0;
	for (idx = 0;idx < commandLength-2;idx++)
	{
		sum += amtCmd.all[idx];
	}
	amtCmd.ammeterCmdStruct.checkCode = sum;
	return sum;
}

/****************************************************************
* Function Name  : AMT_RecvData
* Description    : recieve data from the ammeter after sending require cmd
* Input          : None
* Output         : None
* Return         : None
****************************************************************/
void AMT_RecvData(void)
{
	USART_Recv();
}

/****************************************************************
* Function Name  : AMT_SendCmd
* Description    : Send require comand to ammeter
* Input          : None
* Output         : None
* Return         : None
****************************************************************/
void AMT_SendCmd(void)
{
	USART_Send();
}

/****************************************************************
* Function Name  : AMT_copyBuffer
* Description    : copy command to serial send buffer. Run this before send command
* Input          : None
* Output         : None
* Return         : None
****************************************************************/
void AMT_copyBuffer(void)
{
	int idx;
	for(idx = 0;idx < commandLength;idx++)
	{
		//SerialBuffer[idx] = commandForAmt1Current[idx];
		SerialBuffer[idx] = amtCmd.all[idx];
	}
	SerialDataLength = commandLength;
}

/****************************************************************
* Function Name  : AMT_getAmtPara
* Description    : AMT measurement schedule. 
* Input          : None
* Output         : None
* Return         : None
****************************************************************/
void AMT_getAmtPara(void)
{
	u8 idx = 0;
	for(idx = 0;idx < NUM_OF_PARAS; idx++)
	{
		amtCmd.ammeterCmdStruct = generateCmd(idx);
		AMT_copyBuffer();
		AMT_SendCmd();
		Delay(0xfff);
		AMT_RecvData();
	}	
}

/****************************************************************
* Function Name  : generateCmd
* Description    : Build require command for specific electical parameter.
* Input          : None
* Output         : None
* Return         : None
****************************************************************/
AmmeterCmdStruct generateCmd(AMTCmdType cmdType)
{
	u8 idx;
	union i
	{
		u32 code;
		u8  codeArr[4];
	}idCode;
	AmmeterCmdStruct cmdStruct;
	cmdStruct.startCode    =  START_CODE;
	cmdStruct.addrEndCode  =  START_CODE;
	cmdStruct.endCode      =  END_CODE;
	
	for(idx = 0;idx < ADDR_LENGTH;idx++)
	{
		cmdStruct.addr[idx]	 =  AMT_addr[idx];  //地址赋值。没有找到好的方法，只能先用数组。
	}
	
	cmdStruct.cmdCode      =  READ_CMD_CODE;
	
	switch(cmdType)
	{
		case READ_CURRENT:
			idCode.code = READ_CURRENT_CODE;
		case READ_VOLTAGE:
			idCode.code = READ_VOLTAGE_CODE;
		case READ_POWER:
			idCode.code = READ_POWER_CODE;
		case READ_POWER_FACTOR:
			idCode.code = READ_POWER_FACTOR_CODE;
		default:;
	}
	
	for(idx = 0;idx < ID_CODE_LENGTH;idx++)
	{
		cmdStruct.idCode[idx]= idCode.codeArr[idx];
	}
	
	cmdStruct.checkCode    =	getCheckCode();
	amtCmd.ammeterCmdStruct = cmdStruct;
	return cmdStruct;
}

