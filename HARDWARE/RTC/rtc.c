#include "rtc.h"
#include "delay.h"
#include "key.h"
#include "SEG_8.h"
#include "timer.h"



u8 key = 0;
RTC_TimeTypeDef RTC_TimeTypeInitStructurehms;

//RTCʱ������
//hour,min,sec:Сʱ,����,����
//ampm:@RTC_AM_PM_Definitions  :RTC_H12_AM/RTC_H12_PM
//����ֵ:SUCEE(1),�ɹ�
//       ERROR(0),�����ʼ��ģʽʧ�� 
ErrorStatus RTC_Set_Time(u8 hour,u8 min,u8 sec,u8 ampm)
{

	
	RTC_TimeTypeInitStructurehms.RTC_Hours=hour;
	RTC_TimeTypeInitStructurehms.RTC_Minutes=min;
	RTC_TimeTypeInitStructurehms.RTC_Seconds=sec;
	RTC_TimeTypeInitStructurehms.RTC_H12=ampm;
	
	return RTC_SetTime(RTC_Format_BIN,&RTC_TimeTypeInitStructurehms);
	
}


//RTC��������
//year,month,date:��(0~99),��(1~12),��(0~31)
//week:����(1~7,0,�Ƿ�!)
//����ֵ:SUCEE(1),�ɹ�
//       ERROR(0),�����ʼ��ģʽʧ�� 
ErrorStatus RTC_Set_Date(u8 year,u8 month,u8 date,u8 week)
{
	
	RTC_DateTypeDef RTC_DateTypeInitStructure;
	RTC_DateTypeInitStructure.RTC_Date=date;
	RTC_DateTypeInitStructure.RTC_Month=month;
	RTC_DateTypeInitStructure.RTC_WeekDay=week;
	RTC_DateTypeInitStructure.RTC_Year=year;
	return RTC_SetDate(RTC_Format_BIN,&RTC_DateTypeInitStructure);
}

//RTC��ʼ��
//����ֵ:0,��ʼ���ɹ�;
//       1,LSE����ʧ��;
//       2,�����ʼ��ģʽʧ��;
u8 My_RTC_Init(void)
{
	RTC_InitTypeDef RTC_InitStructure;
	u16 retry=0X1FFF; 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);//ʹ��PWRʱ��
	PWR_BackupAccessCmd(ENABLE);	//ʹ�ܺ󱸼Ĵ������� 
	
	if(RTC_ReadBackupRegister(RTC_BKP_DR0)!=0x0051)		//�Ƿ��һ������?
	{
		RCC_LSEConfig(RCC_LSE_ON);//LSE ����    
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)	//���ָ����RCC��־λ�������,�ȴ����پ������
			{
			retry++;
			delay_ms(10);
			}
		if(retry==0)return 1;		//LSE ����ʧ��. 
			
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);		//����RTCʱ��(RTCCLK),ѡ��LSE��ΪRTCʱ��    
		RCC_RTCCLKCmd(ENABLE);	//ʹ��RTCʱ�� 

    RTC_InitStructure.RTC_AsynchPrediv = 0x7F;//RTC�첽��Ƶϵ��(1~0X7F)
    RTC_InitStructure.RTC_SynchPrediv  = 0xFF;//RTCͬ����Ƶϵ��(0~7FFF)
    RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;//RTC����Ϊ,24Сʱ��ʽ
    RTC_Init(&RTC_InitStructure);
 
		RTC_Set_Time(21,21,21,RTC_H12_AM);	//����ʱ��
		RTC_Set_Date(17,8,17,1);		//��������
	 
		RTC_WriteBackupRegister(RTC_BKP_DR0,0x0051);	//����Ѿ���ʼ������
	} 
 
	return 0;
}


void KeyDeal(void)
{
  u8 shift_val = 0;
	
  u8 i0 = 0;
  u8 i1 = 0;
  u8 i2 = 0;
  u8 i3 = 0;
	
	t_ge = 0;
	t_shi = 0;
	t_bai = 0;
	t_qian = 0;
	
	
	
	TIM_Cmd(TIM3,DISABLE);  //�ض�ʱ��  ���ö�ʱ��ˢ�������
	
	//�������ʾ�ĸ���
	GPIO_SetBits(GPIOE,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	GPIO_ResetBits(GPIOE,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
	SEG_Data_Write(seg_8[0]); 
				
	t_ge = seg_8[i0];
	t_shi = seg_8[i1];
	t_bai = seg_8[i2];
	t_qian = seg_8[i3];		
				
	while(1)
	{
		key = KEY_SCAN();	
		if(key == 2) //KEY1���� 
		{
				if(shift_val == 0) //ͨ��shift_val��ֵ�жϲ�����һ�������
				{				
					i0++;				
					t_ge  = seg_8[i0];
					while(1)
					{
						seg_cnt();
						delay_ms(1);
						key = KEY_SCAN();
						if(key == 2)
						{
							i0++;
							if(i0 > 9)
								i0 = 0;
							t_ge = seg_8[i0];
						}
						if(key == 4 || key == 3)
							break;								
					}
				}	
				if(shift_val == 1)
				{
					i1++;			
					t_shi  = seg_8[i1];
					while(1)
					{
						seg_cnt();
						delay_ms(1);
						key = KEY_SCAN();
						if(key == 2)
						{
							i1++;
							if(i1 > 5)
								i1 = 0;
							t_shi = seg_8[i1];
						}
						if(key == 4 || key == 3)
							break;
					}
				}
				if(shift_val == 2)
				{
					i2++;			
					t_bai  = seg_8[i2];
					while(1)
					{
						seg_cnt();
						delay_ms(1);
						key = KEY_SCAN();
						if(key == 2)
						{
							i2++;
							if(i2 > 9)
								i2 = 0;
							t_bai = seg_8[i2];
						}
						if(key == 4 || key == 3)
							break;
					}
				}
				if(shift_val == 3)
				{		
					i3++;			
					t_qian  = seg_8[i3];
					while(1)
					{
						seg_cnt();
						delay_ms(1);
						key = KEY_SCAN();
						if(key == 2)
						{
							i3++;
							if(i3 > 5)
								i3 = 0;
							t_qian = seg_8[i3];
						}
						if(key == 4 || key == 3)
							break;
					}									
				}				
			}
			if(key == 4)	 //λѡ�����
			{			
				shift_val++;
				if(shift_val > 3)
					shift_val = 0;
			}		
			if(key == 3)	//�������� ���˳�ʱ��У׼ģʽ
			{				
				RTC_TimeTypeInitStructurehms.RTC_Minutes = i3 * 10 + i2;
				RTC_TimeTypeInitStructurehms.RTC_Seconds = i1 * 10 + i0;
				RTC_SetTime(RTC_Format_BIN,&RTC_TimeTypeInitStructurehms);	
				TIM_Cmd(TIM3,ENABLE);		// ����ʱ�� �ö�ʱ���ж�ˢ�������
				break;
		}
		seg_cnt();
		delay_ms(1);
	}
}








