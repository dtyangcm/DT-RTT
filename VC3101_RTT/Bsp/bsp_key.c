#include <rthw.h>
#include <rtthread.h>

#include "stm32f4xx.h"

#include "bsp_key.h"




void KeyPort_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE );
	
	
	//IO配置
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	//5列
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;						//输入模式
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	 					//上拉输入 
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | 
									GPIO_Pin_8 | GPIO_Pin_9;		
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	
	
	//6行
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;	 					//输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;						//推挽
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;					//50MHZS 
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | 
									GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;	
	GPIO_Init(GPIOE, &GPIO_InitStructure);		
}



u32 Key_swap(void)
{
	u32 RowKey;
	
	GPIO_SetBits(GPIOE, GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	GPIO_ResetBits(GPIOE, GPIO_Pin_10);
	RowKey = GPIO_ReadInputData(GPIOE)&0x3E0;
	if (RowKey != 0x3E0) {
		
		return (RowKey>>5) + 0x3E00;
	}
	
	GPIO_SetBits(GPIOE, GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	GPIO_ResetBits(GPIOE, GPIO_Pin_11);	
	RowKey = GPIO_ReadInputData(GPIOE)&0x3E0;
	if (RowKey != 0x3E0) {
		
		return (RowKey>>5) + 0x3D00;
	}	
	GPIO_SetBits(GPIOE, GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	GPIO_ResetBits(GPIOE, GPIO_Pin_12);		
	RowKey = GPIO_ReadInputData(GPIOE)&0x3E0;
	if (RowKey != 0x3E0) {
		
		return (RowKey>>5) + 0x3B00;
	}	
	GPIO_SetBits(GPIOE, GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_15);
	GPIO_ResetBits(GPIOE, GPIO_Pin_13);	
	RowKey = GPIO_ReadInputData(GPIOE)&0x3E0;
	if (RowKey != 0x3E0) {
		
		return (RowKey>>5) + 0x3700;
	}	
	GPIO_SetBits(GPIOE, GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15);
	GPIO_ResetBits(GPIOE, GPIO_Pin_14);	
	RowKey = GPIO_ReadInputData(GPIOE)&0x3E0;
	if (RowKey != 0x3E0) {
		
		return (RowKey>>5) + 0x2F00;
	}	
	GPIO_SetBits(GPIOE, GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_10);
	GPIO_ResetBits(GPIOE, GPIO_Pin_15);	
	RowKey = GPIO_ReadInputData(GPIOE)&0x3E0;
	if (RowKey != 0x3E0) {
		
		return (RowKey>>5) + 0x1F00;
	}	
	
	return 0x3F00 + 0x1F;
}

