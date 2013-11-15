//������ͨ��USART2�������ⷢ������

#include "dataAcquisitionTask.h"

void initBoard(void);


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
		RTC_ClearFlag(RTC_FLAG_SEC);
		while(RTC_GetFlagStatus(RTC_FLAG_SEC)==RESET);
		Delay(0x5ff);
		RTC_SetAlarm(RTC_GetCounter()+ 5); //��������ʱ��5s�� 
		RTC_WaitForLastTask();
		//PWR_EnterSTANDBYMode();
		PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
		//initBoard();
	}
	
}

void initBoard(void)
{
		RCC_Configuration();

		NVIC_Configuration();
	
		EXTI_Configuration();

		GPIO_Configuration();
	
		RTC_Configuration();
//	//������BKP�ĺ󱸼Ĵ���1�У�����һ�������ַ�0xA5A5
//    //��һ���ϵ��󱸵�Դ����󣬸üĴ������ݶ�ʧ��
//    //����RTC���ݶ�ʧ����Ҫ��������
//    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
//    {
//        //��������RTC
//        RTC_Configuration();
//        //������ɺ���󱸼Ĵ�����д�����ַ�0xA5A5
//        BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
//    }
//    else
//    {
////���󱸼Ĵ���û�е��磬��������������RTC
//        //�������ǿ�������RCC_GetFlagStatus()�����鿴���θ�λ����
//        if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
//        {
//            //�����ϵ縴λ
//        }
//        else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
//        {
//            //�����ⲿRST�ܽŸ�λ
//        }
//        //���RCC�и�λ��־
//        RCC_ClearFlag();

//        //��ȻRTCģ�鲻��Ҫ�������ã��ҵ���������󱸵����Ȼ����
//        //����ÿ���ϵ�󣬻���Ҫʹ��RTCCLK???????
//        //RCC_RTCCLKCmd(ENABLE);
//        //�ȴ�RTCʱ����APB1ʱ��ͬ��
//        //RTC_WaitForSynchro();

//        //ʹ�����ж�
//        RTC_ITConfig(RTC_IT_ALR, ENABLE);
//        //�ȴ��������
//        RTC_WaitForLastTask();
//    }
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



