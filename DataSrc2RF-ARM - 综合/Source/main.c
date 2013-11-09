//������ͨ��USART2�������ⷢ������

#include "rfcomm.h"
#include "dscomm.h"

extern u8 SerialBuffer[50];
extern u8 SerialDataLength;
extern u8 RFBuffer[50];
extern u8 RFDataLength;

u8 idx = 0;
AMTCmdType cmdType = READ_CURRENT;

void initBoard(void);
void copyBuffer(u8 src[], u8* srcLength, u8 dst[], u8* dstLength);


int main()
{
	
#ifdef DEBUG
  debug();
#endif

	initBoard();
	
	//����Դ���ڳ�ʼ��
	USART_Configuration(DataSrcPort);
	USART_Configuration(RFPort);
	
	//���������óɹ���־ָʾ��
	LED1_ON;
	LED2_ON;
	
	//ָ�����������ݽ���
	while(1)
	{
//		//����USART2�����ݷ��ͺͽ���  ͨ����������
//		USART_WaitForData();
//		
//		Delay(0xfffff);
//		
//		USART_SendCmd();

		
//		//����USART1�����ݷ��ͺͽ���    ͨ����������
//		RF_RecvCmd();
//		
//		Delay(0xffff);
//		
//		RF_SendData();

		
//		//��ȡ��ȱ����              ͨ������������
//		Delay(0xfff);
//		AMT_getAmtPara();
	
		
////			arm����RF����ͬ��ָ��    ͨ����������
//		RF_RecvCmd();
////			arm�����Ͳ���������arm���յ��������
//		Delay(0xfff); 
//		DS_getAMTData();	
////			arm���յ��ĵ�������͸�RF
////		Delay(0xffff);
//		copyBuffer(SerialBuffer, &SerialDataLength, RFBuffer, &RFDataLength);
//		RF_SendData();
		

//
	  //RF_RecvCmd();
		for(idx = 0;idx < NUM_OF_PARAS;idx++)
		{
			DS_getAMTPara(cmdType++);
			//arm���յ��ĵ�������͸�RF
			copyBuffer(SerialBuffer, &SerialDataLength, RFBuffer, &RFDataLength);
			RF_SendData();
		}			
		cmdType = READ_CURRENT;
	}
	
}

void initBoard(void)
{
		RCC_Configuration();

		NVIC_Configuration();

		GPIO_Configuration();
	//������BKP�ĺ󱸼Ĵ���1�У�����һ�������ַ�0xA5A5
    //��һ���ϵ��󱸵�Դ����󣬸üĴ������ݶ�ʧ��
    //����RTC���ݶ�ʧ����Ҫ��������
    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
    {
        //��������RTC
        RTC_Configuration();
        //������ɺ���󱸼Ĵ�����д�����ַ�0xA5A5
        BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
    }
    else
    {
//���󱸼Ĵ���û�е��磬��������������RTC
        //�������ǿ�������RCC_GetFlagStatus()�����鿴���θ�λ����
        if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
        {
            //�����ϵ縴λ
        }
        else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
        {
            //�����ⲿRST�ܽŸ�λ
        }
        //���RCC�и�λ��־
        RCC_ClearFlag();

        //��ȻRTCģ�鲻��Ҫ�������ã��ҵ���������󱸵����Ȼ����
        //����ÿ���ϵ�󣬻���Ҫʹ��RTCCLK???????
        //RCC_RTCCLKCmd(ENABLE);
        //�ȴ�RTCʱ����APB1ʱ��ͬ��
        //RTC_WaitForSynchro();

        //ʹ�����ж�
        RTC_ITConfig(RTC_IT_SEC, ENABLE);
        //�ȴ��������
        RTC_WaitForLastTask();
    }
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

#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

void SystemInit(){}



