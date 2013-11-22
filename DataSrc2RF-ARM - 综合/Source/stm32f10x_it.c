/**
  ******************************************************************************
  * @file    stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup USART_Interrupt
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern BOOL DATA_ACQUISITION_TASK_FLAG;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles USARTy global interrupt request.
  * @param  None
  * @retval None
  */
//void USARTy_IRQHandler(void)
//{
//  if(USART_GetITStatus(USARTy, USART_IT_RXNE) != RESET)
//  {
//    /* Read one byte from the receive data register */
//    RxBuffer1[RxCounter1++] = USART_ReceiveData(USARTy);

//    if(RxCounter1 == NbrOfDataToRead1)
//    {
//      /* Disable the USARTy Receive interrupt */
//      USART_ITConfig(USARTy, USART_IT_RXNE, DISABLE);
//    }
//  }
//  
//  if(USART_GetITStatus(USARTy, USART_IT_TXE) != RESET)
//  {   
//    /* Write one byte to the transmit data register */
//    USART_SendData(USARTy, TxBuffer1[TxCounter1++]);

//    if(TxCounter1 == NbrOfDataToTransfer1)
//    {
//      /* Disable the USARTy Transmit interrupt */
//      USART_ITConfig(USARTy, USART_IT_TXE, DISABLE);
//    }    
//  }
//}

/**
  * @brief  This function handles USARTz global interrupt request.
  * @param  None
  * @retval None
  */
//void USARTz_IRQHandler(void)
//{
//  if(USART_GetITStatus(USARTz, USART_IT_RXNE) != RESET)
//  {
//    /* Read one byte from the receive data register */
//    RxBuffer2[RxCounter2++] = USART_ReceiveData(USARTz);

//    if(RxCounter2 == NbrOfDataToRead1)
//    {
//      /* Disable the USARTz Receive interrupt */
//      USART_ITConfig(USARTz, USART_IT_RXNE, DISABLE);
//    }
//  }
//  
//  if(USART_GetITStatus(USARTz, USART_IT_TXE) != RESET)
//  {   
//    /* Write one byte to the transmit data register */
//    USART_SendData(USARTz, TxBuffer2[TxCounter2++]);

//    if(TxCounter2 == NbrOfDataToTransfer2)
//    {
//      /* Disable the USARTz Transmit interrupt */
//      USART_ITConfig(USARTz, USART_IT_TXE, DISABLE);
//    }
//  }
//}

/**
  * @brief  This function handles RTC global interrupt request.
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void)
{
//  if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
//  {
//    /* Clear the RTC Second interrupt */
//    RTC_ClearITPendingBit(RTC_IT_SEC);
//		//RTC_SetAlarm(RTC_GetCounter()+ 3);
//    /* Toggle LED1 */
//		LED1_OFF;Delay(0x5ff);LED1_ON;
//		/* 采集数据 */
//		//dataAcquistTask();
//    /* Wait until last write operation on RTC registers has finished */
//    RTC_WaitForLastTask();  
//  }
//	
//	if(RTC_GetITStatus(RTC_IT_ALR) != RESET)
//  {
//    RTC_ClearITPendingBit(RTC_IT_ALR);     //
//		/* Toggle LED1 */
//		LED1_OFF;Delay(0x5ff);LED1_ON;
//  /*Wait until last write operation on RTC registers has finished */
//    RTC_WaitForLastTask();
//  }
//	/* Reset RTC Counter when Time is 23:59:59 */
//	if(RTC_GetCounter() == 0x00015180)     //15180??24??????
//	{
//		RTC_SetCounter(0x0);
//		/* Wait until last write operation on RTC registers has finished */
//		RTC_WaitForLastTask();
//	}
}

void RTCAlarm_IRQHandler(void)
{
	if(RTC_GetITStatus(RTC_IT_ALR) != RESET)
  {
    /* Clear EXTI line17 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line17);

    /* Check if the Wake-Up flag is set */
    if(PWR_GetFlagStatus(PWR_FLAG_WU) != RESET)
    {
      /* Clear Wake Up flag */
      PWR_ClearFlag(PWR_FLAG_WU);
    }
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();   
    /* Clear RTC Alarm interrupt pending bit */
    RTC_ClearITPendingBit(RTC_IT_ALR);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
		/* Toggle LED2 */
    LED2_ON;//Delay(0xff);
		/* Enable data acquisition */
		DATA_ACQUISITION_TASK_FLAG = 1;
		LED2_OFF;
  }
	/* Reset RTC Counter when Time is 23:59:59 */
	if(RTC_GetCounter() == 0x00015180)     //15180??24??????
	{
		RTC_SetCounter(0x0);
		/* Wait until last write operation on RTC registers has finished */
		RTC_WaitForLastTask();
	}
}


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
