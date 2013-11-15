//本程序通过USART2串口向外发送数据

#include "dataAcquisitionTask.h"

void initBoard(void);


int main()
{
	
#ifdef DEBUG
  debug();
#endif

	initBoard();
	
	//数据源串口初始化
	USART_Configuration(DataSrcPort);
	USART_Configuration(RFPort);
	
	//波特率设置成功标志指示灯
	LED1_ON;
	LED2_ON;
	
	//指令发送与电能数据接收
	while(1)
	{
		RTC_ClearFlag(RTC_FLAG_SEC);
		while(RTC_GetFlagStatus(RTC_FLAG_SEC)==RESET);
		Delay(0x5ff);
		RTC_SetAlarm(RTC_GetCounter()+ 5); //设置闹钟时间5s后 
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
//	//我们在BKP的后备寄存器1中，存了一个特殊字符0xA5A5
//    //第一次上电或后备电源掉电后，该寄存器数据丢失，
//    //表明RTC数据丢失，需要重新配置
//    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
//    {
//        //重新配置RTC
//        RTC_Configuration();
//        //配置完成后，向后备寄存器中写特殊字符0xA5A5
//        BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
//    }
//    else
//    {
////若后备寄存器没有掉电，则无需重新配置RTC
//        //这里我们可以利用RCC_GetFlagStatus()函数查看本次复位类型
//        if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
//        {
//            //这是上电复位
//        }
//        else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
//        {
//            //这是外部RST管脚复位
//        }
//        //清除RCC中复位标志
//        RCC_ClearFlag();

//        //虽然RTC模块不需要重新配置，且掉电后依靠后备电池依然运行
//        //但是每次上电后，还是要使能RTCCLK???????
//        //RCC_RTCCLKCmd(ENABLE);
//        //等待RTC时钟与APB1时钟同步
//        //RTC_WaitForSynchro();

//        //使能秒中断
//        RTC_ITConfig(RTC_IT_ALR, ENABLE);
//        //等待操作完成
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



