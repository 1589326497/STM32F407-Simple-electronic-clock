#include "rtc.h"
#include "delay.h"
#include "key.h"
#include "SEG_8.h"
#include "timer.h"



u8 key = 0;
RTC_TimeTypeDef RTC_TimeTypeInitStructurehms;

//RTC时间设置
//hour,min,sec:小时,分钟,秒钟
//ampm:@RTC_AM_PM_Definitions  :RTC_H12_AM/RTC_H12_PM
//返回值:SUCEE(1),成功
//       ERROR(0),进入初始化模式失败 
ErrorStatus RTC_Set_Time(u8 hour,u8 min,u8 sec,u8 ampm)
{

	
	RTC_TimeTypeInitStructurehms.RTC_Hours=hour;
	RTC_TimeTypeInitStructurehms.RTC_Minutes=min;
	RTC_TimeTypeInitStructurehms.RTC_Seconds=sec;
	RTC_TimeTypeInitStructurehms.RTC_H12=ampm;
	
	return RTC_SetTime(RTC_Format_BIN,&RTC_TimeTypeInitStructurehms);
	
}


//RTC日期设置
//year,month,date:年(0~99),月(1~12),日(0~31)
//week:星期(1~7,0,非法!)
//返回值:SUCEE(1),成功
//       ERROR(0),进入初始化模式失败 
ErrorStatus RTC_Set_Date(u8 year,u8 month,u8 date,u8 week)
{
	
	RTC_DateTypeDef RTC_DateTypeInitStructure;
	RTC_DateTypeInitStructure.RTC_Date=date;
	RTC_DateTypeInitStructure.RTC_Month=month;
	RTC_DateTypeInitStructure.RTC_WeekDay=week;
	RTC_DateTypeInitStructure.RTC_Year=year;
	return RTC_SetDate(RTC_Format_BIN,&RTC_DateTypeInitStructure);
}

//RTC初始化
//返回值:0,初始化成功;
//       1,LSE开启失败;
//       2,进入初始化模式失败;
u8 My_RTC_Init(void)
{
	RTC_InitTypeDef RTC_InitStructure;
	u16 retry=0X1FFF; 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);//使能PWR时钟
	PWR_BackupAccessCmd(ENABLE);	//使能后备寄存器访问 
	
	if(RTC_ReadBackupRegister(RTC_BKP_DR0)!=0x0051)		//是否第一次配置?
	{
		RCC_LSEConfig(RCC_LSE_ON);//LSE 开启    
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)	//检查指定的RCC标志位设置与否,等待低速晶振就绪
			{
			retry++;
			delay_ms(10);
			}
		if(retry==0)return 1;		//LSE 开启失败. 
			
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);		//设置RTC时钟(RTCCLK),选择LSE作为RTC时钟    
		RCC_RTCCLKCmd(ENABLE);	//使能RTC时钟 

    RTC_InitStructure.RTC_AsynchPrediv = 0x7F;//RTC异步分频系数(1~0X7F)
    RTC_InitStructure.RTC_SynchPrediv  = 0xFF;//RTC同步分频系数(0~7FFF)
    RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;//RTC设置为,24小时格式
    RTC_Init(&RTC_InitStructure);
 
		RTC_Set_Time(21,21,21,RTC_H12_AM);	//设置时间
		RTC_Set_Date(17,8,17,1);		//设置日期
	 
		RTC_WriteBackupRegister(RTC_BKP_DR0,0x0051);	//标记已经初始化过了
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
	
	
	
	TIM_Cmd(TIM3,DISABLE);  //关定时器  不用定时器刷新数码管
	
	//数码管显示四个零
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
		if(key == 2) //KEY1按下 
		{
				if(shift_val == 0) //通过shift_val的值判断操作哪一个数码管
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
			if(key == 4)	 //位选数码管
			{			
				shift_val++;
				if(shift_val > 3)
					shift_val = 0;
			}		
			if(key == 3)	//保存数据 并退出时间校准模式
			{				
				RTC_TimeTypeInitStructurehms.RTC_Minutes = i3 * 10 + i2;
				RTC_TimeTypeInitStructurehms.RTC_Seconds = i1 * 10 + i0;
				RTC_SetTime(RTC_Format_BIN,&RTC_TimeTypeInitStructurehms);	
				TIM_Cmd(TIM3,ENABLE);		// 开定时器 用定时器中断刷新数码管
				break;
		}
		seg_cnt();
		delay_ms(1);
	}
}








