#include "key.h"
#include "sys.h"
#include "delay.h"


void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体类型变量
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);//开启IO口时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//开启IO口时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

 u8 KEY_SCAN(void)//按键检测
{	
	static u8 key_up=1;
	if((KEY1==0 || KEY_UP==1 || KEY0 == 0 || KEY2 == 0)&&key_up)
	{
		delay_ms(10);
		key_up=0;
		if(KEY0==0)//延时后消抖
		{
			return 1;
		}
		else if(KEY1 == 0)
		{
			return 2;
		}
		else if(KEY2 ==0)
		{
			return 3;
		}
		else if(KEY_UP==1)
		{
			return 4;
		}
	}
	else if (KEY0==1&&KEY1==1&&KEY2==1&&KEY_UP==0)
	{
		key_up=1;
	}
	return 0;	
}
