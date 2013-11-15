

#include "dataAcquisitionTask.h"

extern u8 SerialBuffer[50];
extern u8 SerialDataLength;
extern u8 RFBuffer[50];
extern u8 RFDataLength;



void dataAcquistTask(void)
{
	u8 idx = 0;
	AMTCmdType cmdType = READ_CURRENT;
	
	for(idx = 0;idx < NUM_OF_PARAS;idx++)
	{
		DS_getAMTPara(cmdType++);
		//arm将收到的电参数发送给RF
		copyBuffer(SerialBuffer, &SerialDataLength, RFBuffer, &RFDataLength);
		RF_SendData();
	}			
	cmdType = READ_CURRENT;
}		
		
		
void copyBuffer(u8 src[], u8* srcLength, u8 dst[], u8* dstLength)
{
	u8 idx;
	for(idx = 0; idx < *srcLength; idx++)
	{
		dst[idx] = src[idx];
	}
	*dstLength = *srcLength;
}

