//本程序通过USART2串口向外发送数据

#include "dataAcquisitionTask.h"
#include "StopMode_RTC_Alarm.h"

#define STOP_PERIOD_SEC     30
#ifdef NODE1
	#define START_DELAY       0
#endif

#ifdef NODE2
	#define START_DELAY       0x12C0  //3s
#endif

#ifdef NODE3
	#define START_DELAY       0x2580  //6s
#endif

#ifdef NODE4
	#define START_DELAY       0x383F  //9s
#endif

#ifdef NODE5
	#define START_DELAY       0x4B00  //12s
#endif

#ifdef NODE6
	#define START_DELAY       0x5DC0  //15s
#endif

#ifdef NODE7
	#define START_DELAY       0x707F  //18s
#endif

#ifdef NODE8
	#define START_DELAY       0x8340  //21s
#endif

BOOL DATA_ACQUISITION_TASK_FLAG = 0;

void initBoard(void);


int main()
{
	
#ifdef DEBUG
  debug();
#endif

	initBoard();
	
//	//数据源串口初始化
//	USART_Configuration(DataSrcPort);
//	USART_Configuration(RFPort);
	
	//波特率设置成功标志指示灯
	LED1_ON;
	
	/* Insert delay */
	Delay( START_DELAY );
	
  while (1)
  {
    /* Wait till RTC Second event occurs */
    RTC_ClearFlag(RTC_FLAG_SEC);
    while(RTC_GetFlagStatus(RTC_FLAG_SEC) == RESET);

    /* Alarm in 20 second */
    RTC_SetAlarm(RTC_GetCounter()+ STOP_PERIOD_SEC);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* Turn off LED1 */
    LED1_OFF;

    /* Request to enter STOP mode with regulator in low power mode*/
    PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
    
    /* At this stage the system has resumed from STOP mode -------------------*/
    /* Turn on LED1 */
    LED1_ON;

    /* Configures system clock after wake-up from STOP: enable HSE, PLL and select 
       PLL as system clock source (HSE and PLL are disabled in STOP mode) */
    SYSCLKConfig_STOP();
		
		/* 数据传输 */
		if (DATA_ACQUISITION_TASK_FLAG)
		{
			dataAcquistTask();
			DATA_ACQUISITION_TASK_FLAG = 0;
		}
		
		/*other tasks*/
  }
	
}

void initBoard(void)
{
		RCC_Configuration();

		NVIC_Configuration();
	
		/* Configure EXTI Line to generate an interrupt on falling edge */
		EXTI_Configuration();

		/* Configure RTC clock source and prescaler */
		RTC_Configuration();

		GPIO_Configuration();

		/* NVIC configuration */
		RTC_NVIC_Configuration();

		/* Configure the SysTick to generate an interrupt each 1 millisecond */
		SysTick_Configuration();

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




