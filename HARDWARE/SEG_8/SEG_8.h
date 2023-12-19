#ifndef __seg_8_h
#define __seg_8_h
#include "sys.h"

#define SEG_Data_Write(num) PEout(8)=(num&0x01);PEout(9)=(num>>1)&0x01;PEout(10)=(num>>2)&0x01;PEout(11)=(num>>3)&0x01;PEout(12)=(num>>4)&0x01;PEout(13)=(num>>5)&0x01;PEout(14)=(num>>6)&0x01;PEout(15)=(num>>7)&0x01;


extern u8 seg_8[];


extern u8 t_ge;
extern u8 t_shi;
extern u8 t_bai;
extern u8 t_qian;


extern int  *p_ge;
extern int *p_shi;
extern int  *p_bai;
extern int *p_qian;


void SEG_Init(void);
void seg_cnt(void);
void ShowDp(void);









#endif
