#include "timer.h"
#include "usart.h"
#include "SEG_8.h"
#include "delay.h"
#include "rtc.h"


//ͨ�ö�ʱ��3�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������ʱ��Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��3!
//��������Ft = 84Mhz;

RTC_TimeTypeDef RTC_TimeStruct;


void TIM3_init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
	{
		
		RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);  //��ȡRTCʱ�䡡
		t_ge  = seg_8[RTC_TimeStruct.RTC_Seconds % 10];
		t_shi = seg_8[RTC_TimeStruct.RTC_Seconds / 10];
		t_bai = seg_8[RTC_TimeStruct.RTC_Minutes % 10];
		t_qian = seg_8[RTC_TimeStruct.RTC_Minutes / 10];	
		seg_cnt();    //��ʼˢ�������
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}
