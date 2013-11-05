
#ifndef _LCD_H_
#define _LCD_H_

#define NS100_DLY(x) 		((unsigned int)(20*x))
#define LCD_Delay(x) 		WhileDly(x)


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


#define MAKE_COLOR(x)	((x) ^ m_Color)


/****************************************************************************
* 名	称：
* 功	能：GUI用到的函数
* 入口参数：无
* 出口参数：无
* 说	明：
****************************************************************************/
void LCD_WriteCommand(unsigned char nCmd);
void LCD_WriteData(unsigned char nData);
void LCD_Initilation(void);
void SetAddr(unsigned int x, unsigned int y, unsigned int width, unsigned int high);
void Draw_Dot(int x,int y);
void Draw_ClrDot(int x, int y);

void LCD_ShowBMP(int x, int y, int width, int high, const unsigned char bmp[]);

void LCD_DrawLine(int x1,int y1,int x2,int y2, int Index1);
void LCD_SetPoint(u32 x, u32 y, u32 Index1);
void LCDRAM(uint16_t dp);
void LCD_SetCursor(u32 x, u32 y);

void LCD_SendBuffDC(int x, int y, int xl, int yl);
void Draw_LineToDispBuff(int xpos, int ypos, int xlen, int ylen);
void SetColor(u32 nColor);

/*
以下为LCM的驱动层,主要负责发送T6963C的各种命令,提供设置显示地址等功能  
在发送命令前会检测其状态字  
带参数命令的发送模式:   先参数->后命令;  
            操作模式:   先命令->后参数;  
  
T6963C命令的定义  
********************************************************************/   
//指针设置指令    
#define LCD_CUR_POS 0X21    //光标位置设置(只有设置到有效显示地址并打开显示才看到),双参数(D1水平位置,D2垂直位置)    
#define LCD_CGR_POS 0X22    //CGRAM偏置地址设置(用来增加自己的符号),双参数(D1低5位有效,D2=00)    
#define LCD_ADR_POS 0x24    //地址指针位置(设置读写操作打针)    

//显示区域设置指令    
#define LCD_TXT_STP 0X40    //文本区首址(从此地址开始向屏幕左上角显示字符)    
#define LCD_TXT_WID 0X41    //文本区宽度(设置显示宽度,N/6式N/8,其中N为X轴的点数)    
#define LCD_GRH_STP 0X42    //图型区首址(从此地址开始向屏幕左上角显示点,((有等进一步确认))为文本方式显示时,显示为文本显示特性    
#define LCD_GRH_WID 0X43    //图形区宽度(设置显示宽度,N/6式N/8,其中N为X轴的点数)    

//显示方式设置指令,当CG(D3)为0启用CGROM    
#define LCD_MOD_OR  0X80    //显示方式:逻辑或    
#define LCD_MOD_XOR 0X81    //显示方式:逻辑异或    
#define LCD_MOD_AND 0x83    //显示方式:逻辑与    
#define LCD_MOD_TCH 0x84    //显示方式:文本    

//显示开关设置指令,(D0,D1,D2,D3)=1/0  ==========>  (光标闪烁,光标显示,文本显示,图形显示)启用/禁用    
#define LCD_DIS_SW  0x90    //显示开关设置
#define LCD_DIS_OFF	0xAC	//关显示	UC1698
#define LCD_DIS_GON	0xAD	//开图形	UC1698
#define LCD_DIS_TON	0x94	//开文本    

//光标开头设置指令    
#define LCD_CUR_SHP 0xA0    //光标型形状选择:0xA0-0xA7代表光标占的行数    

//自动读写设置指令    
#define LCD_AUT_WR  0xB0    //自动写设置    
#define LCD_AUT_RD  0xB1    //自动读设置    
#define LCD_AUT_OVR 0xB2    //自动读写结束    

//数据一次读写设置指令    
#define LCD_INC_WR  0xC0    //数据一次写,地址加1    
#define LCD_INC_RD  0xC1    //数据一次读,地址加1    
#define LCD_DEC_WR  0xC2    //数据一次写,地址减1    
#define LCD_DEC_RD  0xC3    //数据一次读,地址减1    
#define LCD_ZER_WR  0xc4    //数据一次写,地址不变    
#define LCE_ZER_RD  0xc5    //数据一次读,地址不变    

//屏读设置指令    
#define LCD_SCN_RD  0xE0    //屏读,屏读只能在图形显示区内;该指令是把屏上的内容取出来作为数据使用.    

//屏拷贝    
#define LCD_SCN_CP  0xE8    //屏拷贝,该指令将屏上当前地址指针(图形)处开妈的一行合成显示内容拷贝到相对应的图形显示区的一级单元    

//位操作指令    
#define LCD_BIT_OP  0xF0    //该指令可将显示缓冲区单无的某位清零或置位.D0-D1---定义D0-D7位;D3--1为置位,D3--0为复位   



/****************************************************************************
* 名	称：u8 fLCD_ReadLEDstate(void)
* 功	能：读取当前LCD背光的状态
* 入口参数：无
* 出口参数：0	关闭
						1	开启
* 说	明：
****************************************************************************/
unsigned char fLCD_ReadLEDstate(void);

/****************************************************************************
* 名	称：void fLCD_LEDON(void)
* 功	能：开启LCD背光
* 入口参数：无
* 出口参数：无
* 说	明：
****************************************************************************/
void fLCD_LEDON(void);

/****************************************************************************
* 名	称：void fLCD_LEDOFF(void)
* 功	能：关闭LCD背光
* 入口参数：无
* 出口参数：无
* 说	明：
****************************************************************************/
void fLCD_LEDOFF(void);
/****************************************************************************
* 名	称：void ClearScreen(void)
* 功	能：清除屏幕
* 入口参数：无
* 出口参数：无
* 说	明：
****************************************************************************/
void ClearScreen(void);

#endif
