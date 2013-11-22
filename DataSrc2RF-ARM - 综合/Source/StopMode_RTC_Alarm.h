
#ifndef __STOPMODE_RTC_Alarm_H
#define __STOPMODE_RTC_Alarm_H

#include  <math.h>

#include  <stm32f10x.h>
#include "CPESchipdef.h"

//�궨�壬��λs��0-4294967295s(71582788.25min)

//����ʱ��
#define STOPTIMES_H 2//2*60*60


void SYSCLKConfig_STOP(void);
void EXTI_Configuration(void);
void RTC_Configuration(void);
void RTC_NVIC_Configuration(void);
void SysTick_Configuration(void);

#endif 

