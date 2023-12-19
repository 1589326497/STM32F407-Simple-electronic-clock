/*
8位数码管 ：位选低电平有效
					段选低电平有效 高电平熄灭
可以仿照跑马灯显示数组完成数码管的数组调用
*/

#include "SEG_8.h"
#include "delay.h"
#include "sys.h"

u8 seg_8[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
//u8 *p_ge  = &seg_8[9];
u8 t; 

u8 t_ge = 0;
u8 t_shi = 0;
u8 t_bai = 0;
u8 t_qian = 0;

u32 cnt = 0;


int seg_key_buf[] = {0,1,2,3,4,5,6,7,8,9,};

//int  *p_ge = &seg_key_buf[10];
//int *p_shi = &seg_key_buf[10];
//int  *p_bai = &seg_key_buf[10];
//int *p_qian = &seg_key_buf[10];



int  *p_ge = &seg_key_buf[0];
int *p_shi = &seg_key_buf[0];
int  *p_bai = &seg_key_buf[0];
int *p_qian = &seg_key_buf[0];



void SEG_Init(void)
{    	 
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOE时钟
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//上拉
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;//100MHz
	GPIO_Init(GPIOE,&GPIO_InitStructure);//初始化
	GPIO_SetBits(GPIOE,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	
}


void seg_cnt(void)
{
	u16 i;

	GPIO_SetBits(GPIOE,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	GPIO_ResetBits(GPIOE,GPIO_Pin_3);//位选第一个数码管
	SEG_Data_Write(t_ge);
	for(i = 25000; i > 0; i--);
	
	
	GPIO_SetBits(GPIOE,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	GPIO_ResetBits(GPIOE,GPIO_Pin_2);//位选第2个数码管
	
	SEG_Data_Write(t_shi);
	for(i = 25000; i > 0; i--);
	ShowDp();
	GPIO_SetBits(GPIOE,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	GPIO_ResetBits(GPIOE,GPIO_Pin_1);//3
	
	SEG_Data_Write(t_bai);
	
	for(i = 25000; i > 0; i--);
	
	GPIO_SetBits(GPIOE,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	GPIO_ResetBits(GPIOE,GPIO_Pin_0);//4
	SEG_Data_Write(t_qian);
	
}


void ShowDp(void)
{
	u16 i;
	GPIO_SetBits(GPIOE,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	GPIO_ResetBits(GPIOE,GPIO_Pin_1);
	PEout(15) = 0;
	for(i = 8800; i > 0; i--);
	PEout(15) = 1;
	
}








