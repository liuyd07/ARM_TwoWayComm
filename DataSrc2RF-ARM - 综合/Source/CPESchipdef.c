
#include "CPESchipdef.h"


ErrorStatus HSEStartUpStatus;//时钟设置状态位

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

  /*********************************串行接口初始化*************************************/
  //使能与USART2有关的引脚，采用重映射Remap实现
  GPIO_PinRemapConfig(GPIO_Remap_DataSrcPort, ENABLE);
  //配置USART2的Tx（PA2）为push-pull类型
  GPIO_InitStructure.GPIO_Pin = DATASRC_TX_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//Rx无此设置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //配置USART2的Rx（PA3）为input floating类型
  GPIO_InitStructure.GPIO_Pin = DATASRC_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_PinRemapConfig(GPIO_Remap_RFPort, ENABLE);
  //配置USART1的Tx（PA9）为push-pull类型
  GPIO_InitStructure.GPIO_Pin = RFPORT_TX_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//Rx无此设置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //配置USART1的Rx（PA10）为input floating类型
  GPIO_InitStructure.GPIO_Pin = RFPORT_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
  //输出引脚初始化
  //485输出引脚,LED1,LED2
  GPIO_InitStructure.GPIO_Pin = SERIAL485ENABLE_PIN | LED1_PIN | LED2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//模式设置，推挽输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);//GPIOA初始化

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
#ifdef  VECT_TAB_RAM  
  // Set the Vector Table base location at 0x20000000  
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  // VECT_TAB_FLASH  
  // Set the Vector Table base location at 0x08000000  
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif
}
void getNodeInfo(void)
{
	//print NODE_NUM
	//print AMMETER_ADDR
	//print AMMETER_NUM
}

void Delay(vu32 nCount)
{
	for(; nCount != 0; nCount--);
}

