#include "dscomm.h"

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
	for(idx = 0;idx < NUM_OF_PARAS; idx++)
	{
		generateCmd(cmdType++);
		AMT_copyBuffer();
		AMT_SendCmd();
		Delay(0xfff);
		AMT_RecvData();
	}	
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
* Description    : read thermoelectrical sensor data. 
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

