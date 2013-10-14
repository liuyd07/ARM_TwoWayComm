#include "dscomm.h"


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

void DS_getTempData(void)
{
}

void DS_getRadioData(void)
{
}

void DS_getSensorData(SensorType sensorType)
{
	switch(sensorType)
	{
		case TEMP_SENSOR:
			DS_getTempData();
		case RADIO_SENSOR:
			DS_getRadioData();
		default:;
	}
}

