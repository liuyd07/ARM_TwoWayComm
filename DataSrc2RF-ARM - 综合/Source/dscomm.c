#include "dscomm.h"

extern u8 SerialBuffer[50];
extern u8 SerialDataLength;



/****************************************************************
* Function Name  : DS_RecvData
* Description    : receive data from the ammeter after sending require command
* Input          : None
* Output         : None
* Return         : None
****************************************************************/
void DS_RecvData(void)
{
	USART_Recv();
}

/****************************************************************
* Function Name  : DS_SendCmd
* Description    : Send require command to ammeter
* Input          : None
* Output         : None
* Return         : None
****************************************************************/
void DS_SendCmd(void)
{
	USART_Send();
}

/****************************************************************
* Function Name  : DS_getAMTData
* Description    : get ammeter data measurement schedule. 
* Input          : None
* Output         : None
* Return         : None
****************************************************************/
void DS_getAMTData(void)
{
	u8 idx = 0;
	AMTCmdType cmdType = READ_CURRENT;
	AMTReadCmd cmd;
	AMT_Addr addr = AMMETER_ADDR;
	for(idx = 0;idx < NUM_OF_PARAS; idx++)
	{
		cmd = generateCmd(addr, cmdType++);
		DS_copyBuffer(cmd.all);
		DS_SendCmd();
		Delay(0xff);
		DS_RecvData();
		Delay(0xfff);
	}	
}

/****************************************************************
* Function Name  : DS_getAMTPara
* Description    : get specific ammeter para measurement result. 
* Input          : None
* Output         : None
* Return         : None
****************************************************************/
void DS_getAMTPara(AMTCmdType cmdType)
{
	AMTReadCmd cmd;
	AMT_Addr addr = AMMETER_ADDR;
	cmd = generateCmd(addr, cmdType++);
	DS_copyBuffer(cmd.all);
	DS_SendCmd();
	Delay(0xff);
	DS_RecvData();
	Delay(0xfff);
}

/****************************************************************
* Function Name  : DS_copyBuffer
* Description    : copy command to serial send buffer. Run this before send command
* Input          : None
* Output         : None
* Return         : None
****************************************************************/
void DS_copyBuffer(u8 command[])
{
	int idx;
	for(idx = 0;idx < READ_CMD_LENGTH;idx++)
	{
		SerialBuffer[idx] = command[idx];
	}
	SerialDataLength = READ_CMD_LENGTH;
}

/****************************************************************
* Function Name  : DS_getTempData
* Description    : read temperature sensor data. 
* Input          : None
* Output         : None
* Return         : None
****************************************************************/
void DS_getTempData(void)
{
}

/****************************************************************
* Function Name  : DS_getThermoElecData
* Description    : read thermoelectric sensor data. 
* Input          : None
* Output         : None
* Return         : None
****************************************************************/
void DS_getThermoElecData(void)
{
}

/****************************************************************
* Function Name  : DS_getSensorData
* Description    : read sensor data on board, not through serial ports. 
* Input          : None
* Output         : None
* Return         : None
****************************************************************/
void DS_getSensorData(SensorType sensorType)
{
	switch(sensorType)
	{
		case TEMP_SENSOR:
			DS_getTempData();
		case RADIO_SENSOR:
			DS_getThermoElecData();
		default:;
	}
}

