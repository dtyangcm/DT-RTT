#ifndef __LCD_CFG_H_
#define __LCD_CFG_H_

#include "stm32f4xx.h"

//whileѭ��= 3+n*5��ָ��,1uS=168��ָ��    һ��whileѭ��һ��Ϊ����ָ�����ڣ�һ��forѭ��������ָ������
#define NS100_DLY(x) ((uint16)(20*x))//����20������ֵ����Һ����ˢ����ʱ���ڱ������150ns
#define LCD_Delay(x) WhileDly(x)



// //��������
// static LCD_IO WR 			= {GPIOG,GPIO_Pin_8};		//LCD_WR			//д�ź�		L��Ч
// static LCD_IO RD 			= {GPIOG,GPIO_Pin_9};		//LCD_RD			//���ź�		L��Ч
// static LCD_IO CE 			= {GPIOG,GPIO_Pin_10};		//LCD_CE			//ʹ��			L��Ч
// static LCD_IO CD 			= {GPIOG,GPIO_Pin_11};		//LCD_CD			//����or����	H���� L����
// static LCD_IO RST 		    = {GPIOG,GPIO_Pin_12};		//LCD_RST			//��λ			L��Ч
// static LCD_IO FS 			= {GPIOG,GPIO_Pin_13};		//LCD_FS			//����				
// static LCD_IO LED 		    = {GPIOG,GPIO_Pin_15}; 		//LCD_LED			//����			H������ L������		
// static LCD_IO AD_CTRL        = {GPIOC,GPIO_Pin_8};		//LCD_AD_CTRL		//��������
#define LCD_DATA1_PORT		GPIOG
#define LCD_DATA1_PIN		GPIO_Pin_0
#define LCD_DATA2_PORT		GPIOG
#define LCD_DATA2_PIN		GPIO_Pin_1
#define LCD_DATA3_PORT		GPIOG
#define LCD_DATA3_PIN		GPIO_Pin_2
#define LCD_DATA4_PORT		GPIOG
#define LCD_DATA4_PIN		GPIO_Pin_3
#define LCD_DATA5_PORT		GPIOG
#define LCD_DATA5_PIN		GPIO_Pin_4
#define LCD_DATA6_PORT		GPIOG
#define LCD_DATA6_PIN		GPIO_Pin_5
#define LCD_DATA7_PORT		GPIOG
#define LCD_DATA7_PIN		GPIO_Pin_6
#define LCD_DATA8_PORT		GPIOG
#define LCD_DATA8_PIN		GPIO_Pin_7

#define LCD_WR_PORT			GPIOG
#define LCD_WR_PIN			GPIO_Pin_8
#define LCD_RD_PORT			GPIOG
#define LCD_RD_PIN			GPIO_Pin_9
#define LCD_CE_PORT			GPIOG
#define LCD_CE_PIN			GPIO_Pin_10
#define LCD_CD_PORT			GPIOG
#define LCD_CD_PIN			GPIO_Pin_11
#define LCD_RST_PORT		GPIOG
#define LCD_RST_PIN			GPIO_Pin_12
#define LCD_FS_PORT			GPIOG
#define LCD_FS_PIN			GPIO_Pin_13
#define LCD_LED_PORT		GPIOG
#define LCD_LED_PIN			GPIO_Pin_15
#define LCD_AD_CTRL_PORT	GPIOC
#define LCD_AD_CTRL_PIN		GPIO_Pin_8

#endif
