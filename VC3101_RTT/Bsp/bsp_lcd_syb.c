
#include "bsp_lcd_syb.h"
#include "bsp_lcd_syb_cfg.h"
#include <stdbool.h>

#define MAKE_COLOR(x)	((x) ^ m_Color)
typedef	unsigned char	uint8;	
typedef	unsigned int	uint16;	

#define SdCmd	LCD_WriteCommand
#define SdData	LCD_WriteData

#define	RdData


static u8 m_Color = 0xff;
static u8 DispBuff[128][120];


#define LCD_BYTES_X  			30 			//显示区宽度
#define TEXT_HOME_ADDRESS 		0x0000 		//文本显示区首地址
#define GRAPHIC_HOME_ADDRESS 	0x01E0 		//图形显示区首地址

#define	GPIO_SET(x)		{LCD_##x##_PORT -> BSRRL = LCD_##x##_PIN;}
#define	GPIO_RESET(x)	{LCD_##x##_PORT -> BSRRH = LCD_##x##_PIN;}

#define	LCD_WRITE_DATA(data)	LCD_DATA1_PORT -> BSRRH = 0x00FF;LCD_DATA1_PORT -> BSRRL = (data) ;		//写数据
#define	LCD_SET_DATA_OUT()		LCD_DATA1_PORT->MODER |= 0x00005555; 									//数据线设置为输出模式
#define	LCD_SET_DATA_IN()		  LCD_DATA1_PORT->MODER &= 0xffff0000; 									//数据线设置为输入模式

/****************************************************************************
* 名	称：u8 fLCD_ReadLEDstate(void)
* 功	能：读背光状态
* 入口参数：
* 出口参数：u8	1:背光已打开；	0：背光已关闭
* 说	明：无
****************************************************************************/
u8 fLCD_ReadLEDstate(void)
{
	return GPIO_ReadOutputDataBit(LCD_LED_PORT , LCD_LED_PIN);
}
/****************************************************************************
* 名	称：void fLCD_LEDON(void)
* 功	能：打开LCD背光
* 入口参数：
* 出口参数：
* 说	明：无
****************************************************************************/
void fLCD_LEDON(void)
{
	GPIO_SET(LED);
}
/****************************************************************************
* 名	称：void fLCD_LEDOFF(void)
* 功	能：关闭LCD背光
* 入口参数：
* 出口参数：
* 说	明：无
****************************************************************************/
void fLCD_LEDOFF(void)
{
	GPIO_RESET(LED);
}
/****************************************************************************
* 名	称：void fLCD_ReadData_Row(void)
* 功	能：读LCD数据，LCD数据线为连续递增排列
* 入口参数：无
* 出口参数：LCD data
* 说	明：无
****************************************************************************/
static u8 fLCD_ReadData_Row(void)
{
	u8 uTmp;							//IO口配置为输入模式
	GPIO_SET(AD_CTRL);
	uTmp = (u8)(LCD_DATA1_PORT ->IDR );	//读数据
	GPIO_RESET(AD_CTRL);				//IO口配置为输出模式
	return uTmp;
}

static void WhileDly(u32 nDly)
{
	while(nDly--);
}

static void LCD_PortInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);		//开启引脚时钟G
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);		//开启引脚时钟G

 	//配置读写控制为推挽输出
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;  
	GPIO_InitStructure.GPIO_Pin   = LCD_WR_PIN|LCD_RD_PIN|LCD_CE_PIN|LCD_CD_PIN|LCD_RST_PIN|LCD_FS_PIN|LCD_LED_PIN/
									LCD_DATA1_PIN|LCD_DATA2_PIN|LCD_DATA3_PIN|LCD_DATA4_PIN|LCD_DATA5_PIN|LCD_DATA6_PIN|LCD_DATA7_PIN|LCD_DATA8_PIN;		//LCD_WR
	GPIO_Init(LCD_WR_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin   = LCD_AD_CTRL_PIN ;					
	GPIO_Init(LCD_AD_CTRL_PORT, &GPIO_InitStructure);	
					
	GPIO_RESET(RST);
	
	GPIO_SET(CE);
	GPIO_SET(WR);
	GPIO_SET(AD_CTRL);
	GPIO_SET(RD);
	GPIO_SET(CD);
	GPIO_RESET(FS);		//使用8*8模式
	GPIO_SET(LED);		//打开背光
}

/****************************************************************************
* 名	称：	bool CheckBusy(unsigned char nMask)
* 功	能：	LCD忙检测
* 入口参数：	u8:	判忙类型	
* 出口参数：	bool:	false--忙	;	true--不忙
* 说	明：	无
****************************************************************************/
static bool CheckBusy(unsigned char nMask)
{
	unsigned char nState;
	unsigned short int i = 0;

	GPIO_SET(CD);
	GPIO_RESET(RD);
	LCD_Delay(NS100_DLY(1));		 //延时

    do{
		nState = fLCD_ReadData_Row();
		if(++i > 10000)
		{
			GPIO_SET(RD);
			return false;
		}
	}while((nState & nMask) != nMask);

	GPIO_SET(RD);
	return true;
}
/****************************************************************************
* 名	称：	void LCD_WriteCommand(uint8 nCmd)
* 功	能：	写LCD命令
* 入口参数：u8	命令
* 出口参数：无
* 说	明：	无
****************************************************************************/
void LCD_WriteCommand(unsigned char nCmd)
{
	CheckBusy(0x03);
	
	GPIO_SET(CD);
	LCD_WRITE_DATA(nCmd);		//向MCU写入数据，准备向LCD输出数据
	
	GPIO_RESET(WR);
	LCD_SET_DATA_OUT();
	LCD_Delay(NS100_DLY(2));	//延时	

	GPIO_SET(WR);
	LCD_Delay(NS100_DLY(4));
	LCD_SET_DATA_IN();
}

void LCD_WriteData(unsigned char nData)
{
	CheckBusy(0x03);
	
	GPIO_RESET(CD);
	LCD_WRITE_DATA(nData);		//向MCU写入数据，准备向LCD输出数据

	GPIO_RESET(WR);
	LCD_SET_DATA_OUT();
	LCD_Delay(NS100_DLY(2));	//延时	

	GPIO_SET(WR);
	LCD_Delay(NS100_DLY(4));
	LCD_SET_DATA_IN();
}

static void LCD_WriteDataAuto(unsigned char nData)
{
	CheckBusy(0x08);
	
	GPIO_RESET(CD);
	LCD_WRITE_DATA(nData);		//向MCU写入数据，准备向LCD输出数据

	GPIO_RESET(WR);
	LCD_SET_DATA_OUT();
	LCD_Delay(NS100_DLY(2));	//延时	

	GPIO_SET(WR);
	LCD_Delay(NS100_DLY(4));
	LCD_SET_DATA_IN();
}

//写2个数据和1个命令到LCM..........
static void send_2data_and_1cmd_to_lcm(uint8 lcm_data_l,uint8 lcm_data_h,uint8 lcm_cmd)
{
	LCD_WriteData(lcm_data_l);
	LCD_WriteData(lcm_data_h);
	LCD_WriteCommand(lcm_cmd);
}
//写1个16进制数据和1个命令到LCM..........
static void send_1hex_data_and_1cmd_to_lcm(uint16 lcm_data,uint8 lcm_cmd)
{
	LCD_WriteData(lcm_data);
	LCD_WriteData(lcm_data>>8);
	LCD_WriteCommand(lcm_cmd);
}


void SetAddr(unsigned short int nAddr)
{
	send_1hex_data_and_1cmd_to_lcm(GRAPHIC_HOME_ADDRESS + nAddr, LCD_ADR_POS);
}

void ClearScreen(void)
{
	uint8 i,j;

	send_1hex_data_and_1cmd_to_lcm(TEXT_HOME_ADDRESS, LCD_ADR_POS);

	LCD_WriteCommand(LCD_AUT_WR);

	for(j=0; j<144; j++)	   //参数为144同时清除图形区部分
	{
		for(i=0; i<30; i++)
		{
			LCD_WriteDataAuto(0x00);
		}
	}

	LCD_WriteCommand(LCD_AUT_OVR);
}
/****************************************************************************
* 名	称：void LCD_Init(void)
* 功	能：初始化LCD
* 入口参数：无
* 出口参数：
* 说	明：无
****************************************************************************/
//void LCD_Init(void)

void LCD_Initilation(void)
{
	//LCD管脚初始化
	LCD_PortInit();	

	GPIO_RESET(RST);
	//SysTimeDly(2);	
	LCD_Delay(NS100_DLY(4));
	GPIO_SET(RST);
	//SysTimeDly(1);
LCD_Delay(NS100_DLY(4));
	//使能片选
	GPIO_RESET(CE);

	//初始化设置
	send_1hex_data_and_1cmd_to_lcm(TEXT_HOME_ADDRESS, LCD_TXT_STP);  	//文本显示区首地址
	send_2data_and_1cmd_to_lcm(LCD_BYTES_X, 0x00, LCD_TXT_WID);  		//文本显示区宽度
	send_1hex_data_and_1cmd_to_lcm(GRAPHIC_HOME_ADDRESS, LCD_GRH_STP); 	//图形显示区首地址
	send_2data_and_1cmd_to_lcm(LCD_BYTES_X, 0x00, LCD_GRH_WID);  		//图形显示区宽度
	send_2data_and_1cmd_to_lcm(0x02,0x00,LCD_CGR_POS);   				//CGRAM偏置地址设置
	LCD_WriteCommand(LCD_MOD_OR);      									//逻辑"或"

	//先清屏，再开显示
	ClearScreen();

	//开显示
	LCD_WriteCommand(LCD_DIS_GON);      								//启用图形显示
}


///////////////////////需要修改的/////////////////////////////////


unsigned char Rd_Data(void)  
{
	unsigned char Ddata;
	
	LCD_SET_DATA_IN();
	GPIO_SET(CD); 
	GPIO_RESET(CE);
	GPIO_RESET(RD);
	Ddata = GPIO_ReadInputData(GPIOG);
	GPIO_SET(RD);
	GPIO_SET(CE);
	
    return (Ddata);
}

void LCD_SetCursor(u32 x, u32 y)
{

}



void LCDRAM(uint16_t dp)
{

}
void DrawPoint(s16 x, s16 y);
void DrawClrPoint(s16 x, s16 y);
//-----绘点函数--------------------------
// 坐标(x,y)，x为水平方向像素点列；y为垂直方向像素点行
void Draw_Dot(int x, int y)
{
	DrawPoint(x,y);
} 
void Draw_ClrDot(int x, int y)
// 坐标(x,y)，x为水平方向像素点列；y为垂直方向像素点行
{
	DrawClrPoint(x,y);
}

void LCD_SetPoint(u32 x, u32 y, u32 Index1)
{
	if (!Index1) {
		Draw_ClrDot(x, y);
	} else {
		Draw_Dot(x, y);
	}
}
void DrawHoriLine(s16 x, s16 y, s16 cx);

void DrawVertLine(s16 x, s16 y, s16 cy);

void DrawRect(s16 x, s16 y, s16 cx, s16 cy)	;
void LCD_SYB_DrawHLine(int x1,int y1,int x2,int y2, int Index1)
{
	u8 OldColor = m_Color;
	if(!Index1)
	{
		SetColor(0);
		DrawHoriLine(x1,y1,x2);
		SetColor(OldColor);
	}	
	else
			DrawHoriLine(x1,y1,x2);
	
}
void LCD_SYB_DrawVLine(int x1,int y1,int x2,int y2, int Index1)
{
	u8 OldColor = m_Color;
	if(!Index1)
	{
		SetColor(0);
		DrawVertLine(x1,y1,y2);
		SetColor(OldColor);
	}	
	else
			DrawVertLine(x1,y1,y2);
}

void LCD_DrawLine(int x1,int y1,int x2,int y2, int Index1)
//  x为水平方向像素列；y为垂直方向像素点行
//  坐标(x1,y1)为线起始地址坐标；坐标(x2,y2)为线终止地址坐标。
{
			DrawRect(x1,y1,x2,y2);
}
void LCD_DrawRect(int x1,int y1,int x2,int y2, int Index1)
//  x为水平方向像素列；y为垂直方向像素点行
//  坐标(x1,y1)为线起始地址坐标；坐标(x2,y2)为线终止地址坐标。
{
	u8 OldColor = m_Color;
	if(!Index1)
	{
		SetColor(0);
		DrawRect(x1,y1,x2,y2);
		SetColor(OldColor);
	}	
	else	
			DrawRect(x1,y1,x2,y2);
}


void LCD_Test_Line()
{
	static int cnt = 0;
	int y0 = 23,y1= 23;
	
	cnt++;
	//LCD_SYB_DrawHLine(cnt,cnt,100,100,0);
	//LCD_SYB_DrawVLine(cnt,cnt,100,100,0);
	//LCD_DrawRect(cnt,cnt,100,100,0);
	
	for (; y0 <= y1; y0++) {
		LCD_SYB_DrawHLine( 23, y0, 23,y1,1);
	} 
}
// void SetColor(u32 nColor)
// {
// 	m_Color = (nColor == 0) ? 0 : 0xFF;
// }
/*
 *	刷新指定窗口缓存
 */
void LCD_SendBuffDC(int x, int y, int xl, int yl)
{

}

void Draw_LineToDispBuff(int xpos, int ypos, int xlen, int ylen)
{

}

