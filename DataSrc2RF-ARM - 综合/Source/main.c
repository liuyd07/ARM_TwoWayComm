//本程序通过USART2串口向外发送数据

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
	
	//数据源串口初始化
	USART_Configuration(DataSrcPort);
	USART_Configuration(RFPort);
	
	//波特率设置成功标志指示灯
	LED1_ON;
	LED2_ON;
	
	//指令发送与电能数据接收
	while(1)
	{
//		//测试USART2的数据发送和接收  通过！！！！
//		USART_WaitForData();
//		
//		Delay(0xfffff);
//		
//		USART_SendCmd();

		
//		//测试USART1的数据发送和接收    通过！！！！
//		RF_RecvCmd();
//		
//		Delay(0xffff);
//		
//		RF_SendData();

		
//		//获取电度表参数              通过！！！！！
//		Delay(0xfff);
//		AMT_getAmtPara();
	
		
////			arm接收RF发送同步指令    通过！！！！
//		RF_RecvCmd();
////			arm向电表发送参数测量，arm接收电表返回数据
//		Delay(0xfff); 
//		DS_getAMTData();	
////			arm将收到的电参数发送给RF
////		Delay(0xffff);
//		copyBuffer(SerialBuffer, &SerialDataLength, RFBuffer, &RFDataLength);
//		RF_SendData();
		

//
	  //RF_RecvCmd();
		for(idx = 0;idx < NUM_OF_PARAS;idx++)
		{
			DS_getAMTPara(cmdType++);
			//arm将收到的电参数发送给RF
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
	//我们在BKP的后备寄存器1中，存了一个特殊字符0xA5A5
    //第一次上电或后备电源掉电后，该寄存器数据丢失，
    //表明RTC数据丢失，需要重新配置
    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
    {
        //重新配置RTC
        RTC_Configuration();
        //配置完成后，向后备寄存器中写特殊字符0xA5A5
        BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
    }
    else
    {
//若后备寄存器没有掉电，则无需重新配置RTC
        //这里我们可以利用RCC_GetFlagStatus()函数查看本次复位类型
        if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
        {
            //这是上电复位
        }
        else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
        {
            //这是外部RST管脚复位
        }
        //清除RCC中复位标志
        RCC_ClearFlag();

        //虽然RTC模块不需要重新配置，且掉电后依靠后备电池依然运行
        //但是每次上电后，还是要使能RTCCLK???????
        //RCC_RTCCLKCmd(ENABLE);
        //等待RTC时钟与APB1时钟同步
        //RTC_WaitForSynchro();

        //使能秒中断
        RTC_ITConfig(RTC_IT_SEC, ENABLE);
        //等待操作完成
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



