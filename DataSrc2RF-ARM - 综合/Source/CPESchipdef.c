
#include "CPESchipdef.h"


ErrorStatus HSEStartUpStatus;//ʱ������״̬λ

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

	/* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
	/* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
    
  /* Enable USART1, GPIOA, GPIOD and AFIO clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA 
  			|RCC_APB2Periph_GPIOB , ENABLE);//| RCC_APB2Periph_AFIO
 
  /* Enable USART2 clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; 

  /*********************************���нӿڳ�ʼ��*************************************/
  //ʹ����USART2�йص����ţ�������ӳ��Remapʵ��
  GPIO_PinRemapConfig(GPIO_Remap_DataSrcPort, ENABLE);
  //����USART2��Tx��PA2��Ϊpush-pull����
  GPIO_InitStructure.GPIO_Pin = DATASRC_TX_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//Rx�޴�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //����USART2��Rx��PA3��Ϊinput floating����
  GPIO_InitStructure.GPIO_Pin = DATASRC_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_PinRemapConfig(GPIO_Remap_RFPort, ENABLE);
  //����USART1��Tx��PA9��Ϊpush-pull����
  GPIO_InitStructure.GPIO_Pin = RFPORT_TX_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//Rx�޴�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //����USART1��Rx��PA10��Ϊinput floating����
  GPIO_InitStructure.GPIO_Pin = RFPORT_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
  //������ų�ʼ��
  //485�������,LED1,LED2
  GPIO_InitStructure.GPIO_Pin = SERIAL485ENABLE_PIN | LED1_PIN | LED2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//ģʽ���ã��������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);//GPIOA��ʼ��

}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{  
	NVIC_InitTypeDef NVIC_InitStructure;
	
#ifdef  VECT_TAB_RAM  
  // Set the Vector Table base location at 0x20000000  
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  // VECT_TAB_FLASH  
  // Set the Vector Table base location at 0x08000000  
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif
  
	/* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	/* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = RTCAlarm_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  
}

void EXTI_Configuration(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
  //GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);
//  /* Configure Key Button EXTI Line to generate an interrupt on falling edge */  
//  EXTI_InitStructure.EXTI_Line = EXTI_Line5;
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  EXTI_Init(&EXTI_InitStructure);

  /*����EXTI_Line17(RTC_Alarm)Ϊ�����ش���*/
  EXTI_ClearITPendingBit(EXTI_Line17);
  EXTI_InitStructure.EXTI_Line = EXTI_Line17 ;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_Init(&EXTI_InitStructure);
}

/**
  * @brief  Configures the RTC.
  * @param  None
  * @retval None
  */
void RTC_Configuration(void)
{
	
	
  /* Enable PWR and BKP clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	
	/* Enable WKUP pin */
  //PWR_WakeUpPinCmd(ENABLE);
	
  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

  /* Reset Backup Domain */
  BKP_DeInit();

//  /* Enable the LSE OSC ��ʱ��*/
//  RCC_LSEConfig(RCC_LSE_ON);
//  
//  /* Wait till LSE is ready */
//  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
//  {} //��Ȼ����1���Ӳ�����ɹ������������⡣ò��LSE��Ӧ���ⲿ����Ӧ����32.768kHz��8MHz��Ӧ��Ӧ����HSE��HSE�Ѿ���RCC_Configure���ʼ�����ˡ�

  /* Select HSE_Div128 as RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_HSE_Div128); //�ⲿ����Ϊ8MHz

  /* Enable RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC registers synchronization */
  RTC_WaitForSynchro();

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Enable the RTC Second */
  RTC_ITConfig(RTC_IT_SEC, ENABLE);

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Set RTC prescaler: set RTC period to 1sec */
  RTC_SetPrescaler(62499); /* RTC period = RTCCLK/RTC_PR = (62.500 KHz)/(62499+1) */
	
	/* Enable the RTC Alarm */ 
	RTC_ITConfig(RTC_IT_ALR, ENABLE);	
	
	/* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
	
	RTC_SetAlarm(RTC_GetCounter()+ 5); //��������ʱ��5s�� 
	
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
	
	
}

void getNodeInfo(void)
{
	//print NODE_NUM
	//print AMMETER_ADDR
	//print AMMETER_NUM
}

void Delay(vu32 nCount)
{
	int i,j;
	for(i = 0; i < nCount; i++)
		for(j = 0; j < nCount; j++);
}

