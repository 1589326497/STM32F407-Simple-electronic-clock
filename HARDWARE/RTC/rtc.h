#ifndef __RTC_H
#define __RTC_H	 
#include "sys.h" 


extern 	RTC_TimeTypeDef RTC_TimeTypeInitStructurehms;
u8 My_RTC_Init(void);						//RTC��ʼ��
ErrorStatus RTC_Set_Time(u8 hour,u8 min,u8 sec,u8 ampm);			//RTCʱ������
ErrorStatus RTC_Set_Date(u8 year,u8 month,u8 date,u8 week); 		//RTC��������
void KeyDeal(void);






#endif

















