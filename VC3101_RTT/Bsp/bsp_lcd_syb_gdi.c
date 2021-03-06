#include "bsp_lcd_syb_gdi.h"
#include "string.h" 
#include "bsp_lcd_syb_init.h"

#define ASCIIFontAddr 		0x80A0000			//英文字库地址
#define GBFontAddr 				0x80C0000			//国标字库地址

static const u8 m_arrSmallNumber[] = {
	0x00,0x00,0x00,0x30,0x48,0x84,0x84,0x84,0x84,0x84,0x48,0x30,0x00,0x00,/*"0",0*/
	
	0x00,0x00,0x00,0x10,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00,/*"1",1*/
	
	0x00,0x00,0x00,0x38,0x44,0x44,0x04,0x08,0x10,0x20,0x44,0x7C,0x00,0x00,/*"2",2*/
	
	0x00,0x00,0x00,0x38,0x44,0x44,0x18,0x04,0x04,0x44,0x44,0x38,0x00,0x00,/*"3",3*/
	
	0x00,0x00,0x08,0x08,0x18,0x28,0x48,0x48,0x88,0x7C,0x08,0x1C,0x00,0x00,/*"4",4*/
	
	0x00,0x00,0x00,0x7C,0x40,0x40,0x78,0x44,0x04,0x44,0x44,0x38,0x00,0x00,/*"5",5*/
	
	0x00,0x00,0x00,0x3C,0x44,0x80,0xB8,0xC4,0x84,0x84,0x84,0x78,0x00,0x00,/*"6",6*/
	
	0x00,0x00,0x00,0x7C,0x44,0x48,0x08,0x10,0x10,0x10,0x10,0x10,0x00,0x00,/*"7",7*/
	
	0x00,0x00,0x00,0x78,0x84,0x84,0x48,0x78,0x84,0x84,0x84,0x78,0x00,0x00,/*"8",8*/
	
	0x00,0x00,0x00,0x78,0x84,0x84,0x84,0x8C,0x74,0x04,0x88,0xF0,0x00,0x00,/*"9",9*/

	0x00,0x00,0x00,0x44,0xA8,0xA8,0xB0,0x54,0x1A,0x2A,0x2A,0x44,0x00,0x00,/*"%",0*/

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x00,0x00,/*"."*/
	
	0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"-"*/
	
	0x00,0x00,0x00,0x00,0x10,0x10,0x7C,0x10,0x10,0x10,0x10,0x0C,0x00,0x00/*"t"*/
};

static const u8 m_arrBigNumber30[] = 
// 0(0) 1(1) 2(2) 3(3) 4(4) 5(5) 6(6) 7(7) 8(8) 9(9) .(10) -(11) t(12)
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xC0,
0x0E,0x60,0x1C,0x30,0x38,0x38,0x38,0x38,0x30,0x1C,0x70,0x1C,0x70,0x1C,
0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x30,0x18,
0x38,0x38,0x38,0x38,0x1C,0x70,0x0E,0x60,0x07,0xC0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"0",0*/
/* (15 X 30 , 宋体, 加粗 )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,
0x01,0xC0,0x0F,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,
0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,
0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x0F,0xF8,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"1",1*/
/* (15 X 30 , 宋体, 加粗 )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xE0,
0x0C,0x78,0x18,0x38,0x30,0x1C,0x30,0x1C,0x38,0x1C,0x38,0x1C,0x00,0x18,
0x00,0x38,0x00,0x70,0x00,0x60,0x00,0xC0,0x01,0x80,0x03,0x00,0x06,0x00,
0x0C,0x0C,0x18,0x0C,0x30,0x1C,0x3F,0xFC,0x3F,0xF8,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"2",2*/
/* (15 X 30 , 宋体, 加粗 )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xC0,
0x1C,0xF0,0x38,0x70,0x38,0x38,0x38,0x38,0x38,0x38,0x00,0x38,0x00,0x70,
0x00,0xE0,0x03,0xC0,0x00,0x70,0x00,0x38,0x00,0x1C,0x00,0x1C,0x38,0x1C,
0x38,0x1C,0x38,0x1C,0x38,0x38,0x18,0x70,0x0F,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"3",3*/
/* (15 X 30 , 宋体, 加粗 )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x70,
0x00,0xF0,0x00,0xF0,0x01,0xF0,0x03,0x70,0x03,0x70,0x06,0x70,0x0C,0x70,
0x0C,0x70,0x18,0x70,0x18,0x70,0x30,0x70,0x60,0x70,0x3F,0xFC,0x00,0x70,
0x00,0x70,0x00,0x70,0x00,0x70,0x00,0xF0,0x03,0xFE,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"4",4*/
/* (15 X 30 , 宋体, 加粗 )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFC,
0x0F,0xFC,0x0C,0x00,0x0C,0x00,0x0C,0x00,0x18,0x00,0x18,0x00,0x1B,0xE0,
0x1E,0x78,0x1C,0x38,0x18,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x38,0x1C,
0x38,0x1C,0x38,0x38,0x30,0x38,0x18,0x70,0x0F,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"5",5*/
/* (15 X 30 , 宋体, 加粗 )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xE0,
0x0E,0x38,0x1C,0x38,0x18,0x38,0x38,0x00,0x30,0x00,0x70,0x00,0x77,0xE0,
0x7E,0x70,0x78,0x38,0x78,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,
0x30,0x1C,0x38,0x18,0x1C,0x38,0x1E,0x70,0x07,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"6",6*/
/* (15 X 30 , 宋体, 加粗 )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xFC,
0x1F,0xFC,0x38,0x18,0x30,0x30,0x30,0x30,0x00,0x60,0x00,0x60,0x00,0xC0,
0x00,0xC0,0x01,0x80,0x01,0x80,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,
0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"7",7*/
/* (15 X 30 , 宋体, 加粗 )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xE0,
0x3C,0x78,0x38,0x38,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x78,0x1C,0x3C,0x38,
0x1F,0x70,0x0F,0xC0,0x1D,0xF0,0x38,0x78,0x30,0x38,0x70,0x1C,0x70,0x1C,
0x70,0x1C,0x70,0x1C,0x38,0x38,0x1C,0x70,0x0F,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"8",8*/
/* (15 X 30 , 宋体, 加粗 )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xC0,
0x1C,0x70,0x38,0x38,0x70,0x38,0x70,0x18,0x70,0x1C,0x70,0x1C,0x70,0x1C,
0x70,0x3C,0x38,0x3C,0x3C,0xFC,0x0F,0xDC,0x00,0x1C,0x00,0x38,0x00,0x38,
0x00,0x38,0x38,0x70,0x38,0x70,0x38,0xE0,0x1F,0x80,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"9",9*/
/* (15 X 30 , 宋体, 加粗 )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x1C,0x00,0x3E,0x00,0x3E,0x00,0x1C,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*".",10*/
/* (15 X 30 , 宋体, 加粗 )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x7F,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"-",11*/
/* (15 X 30 , 宋体, 加粗 )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x07,0x00,0x0F,0x00,0x7F,0xF0,
0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,
0x07,0x00,0x07,0x18,0x07,0x18,0x03,0xB0,0x03,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"t",12*/
/* (15 X 30 , 宋体, 加粗 )*/
};


static s16 m_cxScreen = 240;							    //定义屏幕宽度(单位为像素)
static s16 m_cyScreen = 128;								//定义屏幕高度(单位为像素)

static s16 m_ViewPosX = 0;								//视图水平起点
static s16 m_ViewPosY = 0;								//视图垂直起点
static s16 m_ViewSizeX = 240;								//视图水平宽度
static s16 m_ViewSizeY = 128;								//视图垂直宽度
static u8 m_bUseView = 0;
									
static s16 m_nRedrawIndex = 0;
static u8	m_bScreenFlush = 1;
static u8 m_Color = 0x00;

#define GDI_MEM_ROW		128
#define GDI_MEM_COL		30
u8 GdiMem[GDI_MEM_ROW][GDI_MEM_COL];										//表示128×240屏的显存矩阵


#define MAKE_COLOR(x)	((x) ^ m_Color)
/****************************************************************************
* 名	称：u8 BeginPaint(void)
* 功	能：GUI初始化函数，包括对LCD的初始化
* 入口参数：无
* 出口参数：无
* 说	明：要使用LCD前必须调用该函数一次
****************************************************************************/	
extern LCD_Init(void);

void BeginPaint(void)
{
	LCD_Init();
	m_nRedrawIndex = 0;
	m_bScreenFlush = 1;	
}

void EnableGdiView(u8 bEnable)
{
	m_bUseView = bEnable;
}

void SetGdiView(s16 x, s16 y, s16 cx, s16 cy)
{
	m_ViewPosX = x;
	m_ViewPosY = y;
	m_ViewSizeX = cx;	
	m_ViewSizeY = cy;
}

void SetColor(u32 nColor)
{
	m_Color = (nColor == 0) ? 0 : 0xFF;
}

void InvertColor(void)
{
	//反转颜色
	m_Color = ~m_Color;
}

void EraseBuffer(void)
{
	memset(GdiMem, MAKE_COLOR(0), sizeof(GdiMem));
}

void EraseRect(s16 x, s16 y, s16 cx, s16 cy)
{
	u8 OldColor = m_Color;
	SetColor(0);
	FillRect(x, y, cx, cy);
	SetColor(OldColor);
}

/****************************************************************************
* 名	称：void EraseScreen(void)
* 功	能：清屏及MCU上的显存
* 入口参数：无
* 出口参数：无
* 说	明：
****************************************************************************/	
void EraseScreen(void)
{
	ClearScreen();
	memset(GdiMem, 0, sizeof(GdiMem));
}

//设置图形重绘
void SetRedraw(u8 bEnable)
{
	//如果禁止重绘
	if(bEnable == 0) 
	{	
		m_nRedrawIndex++;
		return;
	}

	//如果使能重绘
	if(m_nRedrawIndex > 0) m_nRedrawIndex--;

	//如果重绘被开启
	if(m_nRedrawIndex == 0)
	{
		//显示图像
		LCD_WriteCommand(LCD_DIS_GON); 
	}
}

//刷新屏幕指定区域，行取值范围[0,63]，列取值范围[0,7]
//sx: 缓存矩阵开始列	sy: 缓存矩阵开始行	ex: 缓存矩阵结束列	ey: 缓存矩阵结束行
void RefreshDC(s16 sx, s16 sy, s16 ex, s16 ey)
{
	u8 i, j;

	//如果禁止刷屏则返回
	if(m_bScreenFlush == 0) return;

	if(m_nRedrawIndex == 0)
	{
		LCD_WriteCommand(LCD_DIS_GON); 
	}
	else
	{
		LCD_WriteCommand(LCD_DIS_OFF); 
	}			 

	for(i = sy; i <= ey; i++)
	{
		//写地址
		SetAddr(i * GDI_MEM_COL + sx);
		
		//输出显存
		LCD_WriteCommand(LCD_AUT_WR);
		for(j = sx; j <= ex; j++)
		{
			LCD_WriteData(GdiMem[i][j]);
		} 
		LCD_WriteCommand(LCD_AUT_OVR);
	}
}

//使能禁止刷屏
void EnableScreenFlush(u8 bEnable)
{
	m_bScreenFlush = bEnable;	
}

//刷新整个屏幕
void FlushScreen(void)
{
	int i, j;

	//开关显示
	if(m_nRedrawIndex == 0)
	{
		LCD_WriteCommand(LCD_DIS_GON); 
	}
	else
	{
		LCD_WriteCommand(LCD_DIS_OFF); 
	}

	//刷屏
	SetAddr(0);
	LCD_WriteCommand(LCD_AUT_WR);

	for(i=0; i<GDI_MEM_ROW; i++)
	{
		//写数据
		for(j=0; j<GDI_MEM_COL; j++)
		{
			LCD_WriteData(GdiMem[i][j]);
		}
	}

	LCD_WriteCommand(LCD_AUT_OVR);
}

void FlushRect(s16 x, s16 y, s16 cx, s16 cy)
{
	s16	xAlign, xEndAlign;

	//先进行规则化
	if(cx < 0)
	{
		x += cx;
		cx = -cx;
	}
	if(cy < 0)
	{
		y += cy;
		cy = -cy;	
	}

	//视图到窗口转换==============================================================================
	if(m_bUseView == 1)
	{
		//使绘图处于视图内
		if((x >= m_ViewSizeX) || (y >= m_ViewSizeY))	return;	//绘图不能超出视图
		if(((x + cx) < 0) || (y + cy < 0)) return;		//绘图区没进入视图

		//如果绘图起点没到达屏幕
		if(x < 0)
		{
			//取屏幕内区域
			cx += x;
			x = 0;
		}
	
		//如果绘图起点没到达屏幕
		if(y < 0)
		{
			//取屏幕内区域
			cy += y;
			y = 0;
		}

		//如果绘图范围超出视图
		if((x+cx) > m_ViewSizeX) cx = m_ViewSizeX - x;
		if((y+cy) > m_ViewSizeY) cy = m_ViewSizeY - y;

		//视图到屏幕转换
		x += m_ViewPosX;		
		y += m_ViewPosY; 
	}
										 
	//参数有效性检查
	if((x >= m_cxScreen) || (y >= m_cyScreen))	return;		//绘图超出屏幕
	if(((x + cx) < 0) || ((y + cy) < 0)) return;	 		//绘图未进入屏幕

	if(x < 0)
	{
		cx += x;
		x = 0;
	}
	if(y < 0)
	{
		cy += y;
		y = 0;
	}

	//保留可显示区域
	if((x+cx) > m_cxScreen) cx = m_cxScreen - x;
	if((y+cy) > m_cyScreen) cy = m_cyScreen - y;

	//求x在显存矩阵中的起点
	xAlign = (x >> 3);

	//求x在显存矩阵中的结束点
	xEndAlign = (x + cx) >> 3;

	//刷新屏幕指定区域
	RefreshDC(xAlign, y, (xEndAlign >= GDI_MEM_COL) ? (GDI_MEM_COL-1) : xEndAlign, y + cy -1);
}


void DrawGbChinesChar(char HiByte, char LoByte, s16 x, s16 y)
{
	//中文字库开始位置为0x80C0000

	u8* pMatrix = (u8*)((((HiByte | 0x80) - 0xA1) * 94 + ((LoByte | 0x80) - 0xA1)) * 28 + GBFontAddr);

	DrawImage(pMatrix, x, y, 14, 14);
}

void DrawGbAscChar(char Byte, s16 x, s16 y)
{
	//英文字库开始位置为0x80A0000

	u8* pMatrix = (u8*)(Byte * 14 + ASCIIFontAddr);

	DrawImage(pMatrix, x, y, 7, 14);

}

//文字输出
void DrawGbText(char *s, s16 x, s16 y) 
{
	while(*s != 0)
	{
		if((*s & 0x80) == 0)
		{
			//英文
			DrawGbAscChar(*s, x, y);
			
			s += 1;
			x += 7;
		}
		else
		{
			//中文
			DrawGbChinesChar(*s, *(s+1), x, y);
	
			s += 2;
			x += 14;
		}
	}	 
}

//画实心矩形，单位为像素
void FillRect(s16 x, s16 y, s16 cx, s16 cy)		//x:[0,127]		y:[0,63]
{
	u8	sMask, eMask;
	s16	xAlign, xMod, xEndAlign, xEndMod, i, j;

	//先进行规则化
	if(cx < 0)
	{
		x += cx;
		cx = -cx;
	}
	if(cy < 0)
	{
		y += cy;
		cy = -cy;	
	}


	//视图到窗口转换==============================================================================
	if(m_bUseView == 1)
	{
		//使绘图处于视图内
		if((x >= m_ViewSizeX) || (y >= m_ViewSizeY))	return;	//绘图不能超出视图
		if(((x + cx) < 0) || (y + cy < 0)) return;		//绘图区没进入视图

		//如果绘图起点没到达屏幕
		if(x < 0)
		{
			//取屏幕内区域
			cx += x;
			x = 0;
		}
	
		//如果绘图起点没到达屏幕
		if(y < 0)
		{
			//取屏幕内区域
			cy += y;
			y = 0;
		}

		//如果绘图范围超出视图
		if((x+cx) > m_ViewSizeX) cx = m_ViewSizeX - x;
		if((y+cy) > m_ViewSizeY) cy = m_ViewSizeY - y;

		//视图到屏幕转换
		x += m_ViewPosX;		
		y += m_ViewPosY; 
	}
										 
	//参数有效性检查
	if((x >= m_cxScreen) || (y >= m_cyScreen))	return;		//绘图超出屏幕
	if(((x + cx) < 0) || ((y + cy) < 0)) return;	 		//绘图未进入屏幕

	if(x < 0)
	{
		cx += x;
		x = 0;
	}
	if(y < 0)
	{
		cy += y;
		y = 0;
	}

	//保留可显示区域
	if((x+cx) > m_cxScreen) cx = m_cxScreen - x;
	if((y+cy) > m_cyScreen) cy = m_cyScreen - y;

	//求x在显存矩阵中的起点
	xAlign = (x >> 3);
	xMod =  x % 8;
	sMask = 0xFF << (8 - xMod);

	//求x在显存矩阵中的结束点
	xEndAlign = (x + cx) >> 3;
	xEndMod =  (x + cx) % 8;
	eMask = (0xFF >> xEndMod);
	
	//起点和结束点在同一字节上重合处理
	if(xAlign == xEndAlign)								   	
	{
		sMask = sMask | eMask;
	}

	//更新显存中被影响区域
	for(i = 0; i < cy; i++)
	{
		for(j = xAlign; (j <= xEndAlign) && (j < GDI_MEM_COL); j++)	
		{
			if(j == xAlign)
			{
				GdiMem[y + i][xAlign] &= sMask;
				GdiMem[y + i][xAlign] |= MAKE_COLOR(~sMask) & ~sMask;
			}
			else if(j == xEndAlign)
			{
				GdiMem[y + i][xEndAlign] &= eMask;
				GdiMem[y + i][xEndAlign] |= MAKE_COLOR(~eMask) & ~eMask;
			}
			else
				GdiMem[y + i][j] = MAKE_COLOR(0xFF);
		}
	}

	//刷新屏幕指定区域
	RefreshDC(xAlign, y, (xEndAlign >= GDI_MEM_COL) ? (GDI_MEM_COL-1) : xEndAlign, y + cy -1);
}

//x:[0,127]		y:[0,63]
void DrawImage(const u8* pImage, s16 x, s16 y, s16 cx, s16 cy)
{
	SupperDrawImage(pImage, x, y, 0, 0, cx, cy, cx, cy);
}

//x, y: 在屏幕上的起点
//xImg, yImg：绘制图像上的起点
//cxImg, cyImg: 绘制图像上的区域
//Width, Height: 图像的长宽
//void _SupperDrawImage(u8* pImage, s16 _x, s16 _y, s16 _xImg, s16 _yImg, s16 _cxImg, s16 _cyImg, s16 _Width, s16 _Height)
void SupperDrawImage(const u8* pImage, s16 x, s16 y, s16 xImg, s16 yImg, s16 cxImg, s16 cyImg, s16 Width, s16 Height)
{
	u8	sMask, eMask;
	s16	xAlign, xMod, xEndAlign, i, j, xImgAlign;

//	s16 x = _x;
//	s16 y = _y;
//	s16 xImg = _xImg;
//	s16 yImg = _yImg;
//	s16 cxImg = _cxImg;
//	s16 cyImg = _cyImg;
//	s16 Width = _Width;
//	s16 Height = _Height;

	//检查图像内参数==============================================================================
	if((cxImg <= 0) || (cyImg <= 0)) return;			//图像长宽不能小于零
	if((xImg < 0) || (yImg < 0)) return;				//图像中的绘图起点不能小于零
	if((xImg >= Width) || (yImg >= Height)) return;		//图像中的绘图起点不能不能超出图像
	if((xImg + cxImg) > Width) cxImg = Width - xImg;	//图像中的绘图区不能超出图像
	if((yImg + cyImg) > Height) cyImg = Height - yImg;	//图像中的绘图区不能超出图像


	//视图到窗口转换==============================================================================
	if(m_bUseView == 1)
	{
		//使绘图处于视图内
		if((x >= m_ViewSizeX) || (y >= m_ViewSizeY))	return;	//绘图不能超出视图
		if(((x + cxImg) < 0) || (y + cyImg < 0)) return;		//绘图区没进入视图

		//如果绘图起点没到达屏幕
		if(x < 0)
		{
			//取屏幕内区域
			xImg -= x;
			cxImg += x;
			x = 0;
		}
	
		//如果绘图起点没到达屏幕
		if(y < 0)
		{
			//取屏幕内区域
			yImg -= y;
			cyImg += y;
			y = 0;
		}

		//如果绘图范围超出视图
		if((x+cxImg) > m_ViewSizeX) cxImg = m_ViewSizeX - x;
		if((y+cyImg) > m_ViewSizeY) cyImg = m_ViewSizeY - y;

		//视图到屏幕转换
		x += m_ViewPosX;		
		y += m_ViewPosY; 
	}
	
	//参数有效性检查，使绘图处于物理窗口内=================================================
	if((x >= m_cxScreen) || (y >= m_cyScreen))	return;	//绘图不能超出屏幕
	if(((x + cxImg) < 0) || (y + cyImg < 0)) return;	//绘图区没进入屏幕	
	
	//如果绘图起点没到达屏幕
	if(x < 0)
	{
		//取屏幕内区域
		xImg -= x;
		cxImg += x;
		x = 0;
	}

	//如果绘图起点没到达屏幕
	if(y < 0)
	{
		//取屏幕内区域
		yImg -= y;
		cyImg += y;
		y = 0;
	}

	//如果绘图范围超出屏幕
	if((x+cxImg) > m_cxScreen) cxImg = m_cxScreen - x;
	if((y+cyImg) > m_cyScreen) cyImg = m_cyScreen - y;

	//求x在显存矩阵中的起点
	xAlign = (x >> 3);
	sMask = 0xFF << (8 - (x % 8));
	xMod =  (8 + (x % 8) - (xImg % 8)) % 8;


	//求x在显存矩阵中的结束点
	xEndAlign = (x + cxImg) >> 3;
	eMask = (0xFF >> ((x + cxImg) % 8));
	//xEndMod =  (((xImg + cxImg) % 8) + xMod) % 8;	  
	

	//求图片起点关于图片原点的前的像素占的字节数
	xImgAlign = (xImg>>3);
	if((xImg %8) != 0) xImgAlign = xImgAlign + 1;
	
	//起点和结束点在同一字节上重合处理
	if(xAlign == xEndAlign)								   	
	{
		sMask = sMask | eMask;
	}
	
	//Width按8位对齐，取字模时所决定的
	if((Width & 0x0007) != 0)
	{
		Width = (Width & (~0x0007)) + 8;
	}
			  
	//更新显存中被影响区域
	for(i = 0; i < cyImg; i++)
	{
		for(j = xAlign; (j <= xEndAlign) && (j < GDI_MEM_COL); j++)	
		{
			if(j == xAlign)
			{
				GdiMem[y + i][j] &= sMask;
				 
  				if(xImg > 0)
				{
					GdiMem[y + i][j] |= (MAKE_COLOR((pImage[(i + yImg) * Width / 8 + j - 1 - xAlign + xImgAlign] << (8-xMod)) | (pImage[(i + yImg) * Width / 8 + xImgAlign] >> xMod)) & ~sMask);
				}
				else
				{
					GdiMem[y + i][j] |= MAKE_COLOR(pImage[(i + yImg) * Width / 8 + xImgAlign] >> xMod) & (~sMask);
				}
			}			
			else if(j == xEndAlign)
			{

				GdiMem[y + i][j] &= eMask;
				GdiMem[y + i][j] |= MAKE_COLOR((pImage[(i + yImg) * Width / 8 + j - 1 - xAlign + xImgAlign] << (8-xMod)) | (pImage[(i + yImg) * Width / 8 + j - xAlign + xImgAlign] >> xMod)) & (~eMask);
			}
			else
			{
				GdiMem[y + i][j] = MAKE_COLOR((pImage[(i + yImg) * Width / 8 + j - 1 - xAlign + xImgAlign] << (8-xMod)) | (pImage[(i + yImg) * Width / 8 + j - xAlign + xImgAlign] >> xMod));
			}
		}
	}

	//刷新屏幕指定区域
	RefreshDC(xAlign, y, (xEndAlign >= GDI_MEM_COL) ? (GDI_MEM_COL-1) : xEndAlign, y + cyImg -1);
}


void DrawPoint(s16 x, s16 y)
{
	FillRect(x, y, 1, 1);
}
void DrawClrPoint(s16 x, s16 y)
{
	EraseRect(x, y, 1, 1);
}
void DrawHoriLine(s16 x, s16 y, s16 cx)
{
	//画横线
	FillRect(x, y, cx  , 1);
}

void DrawVertLine(s16 x, s16 y, s16 cy)
{
	//画竖线
	FillRect(x, y, 1, cy );
}

void DrawRect(s16 x, s16 y, s16 cx, s16 cy)		//x:[0,127]		y:[0,63]
{
	FillRect(x, y, cx, 1);
 	FillRect(x, y + cy - 1, cx, 1);
	FillRect(x, y, 1, cy);
	FillRect(x + cx - 1, y, 1, cy);
}

void DrawSmallChar(char c, s16 x, s16 y)
{
	if((c >= '0') && (c <= '9'))
	{
		DrawImage(&m_arrSmallNumber[(c-0x30)*14], x, y, 7, 14);
	}
//		else if(c == 'E')
//		{
//			DrawImage(&m_arrSmallNumber[sizeof(m_arrSmallNumber)-14*5], x, y, 7, 14);		
//		}
	else if(c == '%')
	{
		DrawImage(&m_arrSmallNumber[sizeof(m_arrSmallNumber)-14*4], x, y, 7, 14);
	}
	else if(c == '.')
	{
		DrawImage(&m_arrSmallNumber[sizeof(m_arrSmallNumber)-14*3], x, y, 7, 14);
	}
	else if(c == '-')
	{
		DrawImage(&m_arrSmallNumber[sizeof(m_arrSmallNumber)-14*2], x, y, 7, 14);
	}
	else if(c == 't')
	{
		DrawImage(&m_arrSmallNumber[sizeof(m_arrSmallNumber)-14], x, y, 7, 14);
	}
}

void DrawSmallText(char *sNum, s16 x, s16 y)
{
	int i, nLen;
	nLen = strlen(sNum);
	for(i = 0; i < nLen; i++)
	{
		if((sNum[i] >= '0') && (sNum[i] <= '9'))
		{
			DrawImage(&m_arrSmallNumber[(sNum[i]-0x30)*14], x + i*7, y, 7, 14);
		}
//		else if(sNum[i] == 'E')
//		{
//			DrawImage(&m_arrSmallNumber[sizeof(m_arrSmallNumber)-14*5], x + i*7, y, 7, 14);		
//		}
		else if(sNum[i] == '%')
		{
			DrawImage(&m_arrSmallNumber[sizeof(m_arrSmallNumber)-14*4], x + i*7, y, 7, 14);
		}
		else if(sNum[i] == '.')
		{
			DrawImage(&m_arrSmallNumber[sizeof(m_arrSmallNumber)-14*3], x + i*7, y, 7, 14);
		}
		else if(sNum[i] == '-')
		{
			DrawImage(&m_arrSmallNumber[sizeof(m_arrSmallNumber)-14*2], x + i*7, y, 7, 14);
		}
		else if(sNum[i] == 't')
		{
			DrawImage(&m_arrSmallNumber[sizeof(m_arrSmallNumber)-14], x + i*7, y, 7, 14);
		}
	}
}

void DrawBigChar(char c, s16 x, s16 y)
{
    #if 0
	if(c == '.')
	{
		DrawImage(&m_arrBigNumber[sizeof(m_arrBigNumber)-108], x, y, 9, 18);
	}
	else if(c == '-')
	{
		DrawImage(&m_arrBigNumber[sizeof(m_arrBigNumber)-72], x, y, 9, 18);
	}
	else if(c == 't')
	{
		DrawImage(&m_arrBigNumber[sizeof(m_arrBigNumber)-36], x, y, 9, 18);
	}
	else if( (c >= '0') && (c <= '9'))
	{
		DrawImage(&m_arrBigNumber[(c-0x30)*36], x, y, 9, 18);
	}
    #else
	if(c == '.')
	{
		DrawImage(&m_arrBigNumber30[sizeof(m_arrBigNumber30)-180], x, y, 15, 30);
	}
	else if(c == '-')
	{
		DrawImage(&m_arrBigNumber30[sizeof(m_arrBigNumber30)-120], x, y, 15, 30);
	}
	else if(c == 't')
	{
		DrawImage(&m_arrBigNumber30[sizeof(m_arrBigNumber30)-60], x, y, 15, 30);
	}
	else if( (c >= '0') && (c <= '9'))
	{
		DrawImage(&m_arrBigNumber30[(c-0x30)*60], x, y, 15, 30);
	}
    #endif
}

void DrawBigText(char *sNum, s16 x, s16 y)
{
	int i, nLen;
	nLen = strlen(sNum);
    #if 0
	for(i = 0; i < nLen; i++)
	{
		if(sNum[i] == '.')
		{
			DrawImage(&m_arrBigNumber[sizeof(m_arrBigNumber)-108], x + i*9, y, 9, 18);
		}
		else if(sNum[i] == '-')
		{
			DrawImage(&m_arrBigNumber[sizeof(m_arrBigNumber)-72], x + i*9, y, 9, 18);
		}
		else if(sNum[i] == 't')
		{
			DrawImage(&m_arrBigNumber[sizeof(m_arrBigNumber)-36], x + i*9, y, 9, 18);
		}
		else if( (sNum[i] >= '0') && (sNum[i] <= '9'))
		{
			DrawImage(&m_arrBigNumber[(sNum[i]-0x30)*36], x + i*9, y, 9, 18);
		}
	}
    #else
	for(i = 0; i < nLen; i++)
	{
		if(sNum[i] == '.')
		{
			DrawImage(&m_arrBigNumber30[sizeof(m_arrBigNumber30)-180], x + i*15, y, 15, 30);
		}
		else if(sNum[i] == '-')
		{
			DrawImage(&m_arrBigNumber30[sizeof(m_arrBigNumber30)-120], x + i*15, y, 15, 30);
		}
		else if(sNum[i] == 't')
		{
			DrawImage(&m_arrBigNumber30[sizeof(m_arrBigNumber30)-60], x + i*15, y, 15, 30);
		}
		else if( (sNum[i] >= '0') && (sNum[i] <= '9'))
		{
			DrawImage(&m_arrBigNumber30[(sNum[i]-0x30)*60], x + i*15, y, 15, 30);
		}
	}
    #endif
}

#ifdef LCD_DEBUG

u8 dispBuf[128];
char *pTkn;

int LCD_Debug(void)
{
	int n;
	u8 cmd, nDataFlag = 0, nDataInHex = 0;
	memset(dispBuf, 0, 20);
	n = Usart3_RecvData(dispBuf, 128);
	if(n < 2)return dispBuf[0];

	pTkn = strtok((char*)dispBuf, ",");
	while(pTkn != NULL)
	{
		if(0 == memcmp(pTkn, "\r\n", 2))
		{
			nDataFlag = 1;
			pTkn += 2;
		}
		if(nDataFlag) 		
		{
			if(0 == memcmp(pTkn, "hex\0", 4))
			{
				nDataInHex = 1;
			}
			else if(nDataInHex)
			{
				BufferAsciiToHex(pTkn, &cmd, 2);
				LCD_WriteData(cmd);
				LCD_Delay(US_DLY(100));
			}
			else
			{
				while(*pTkn != 0)
				{
					LCD_WriteData(*pTkn++);
					LCD_Delay(US_DLY(100));
				}
			}
		}
		else
		{
			BufferAsciiToHex(pTkn, &cmd, 2);
			LCD_WriteCommand(cmd);
			LCD_Delay(US_DLY(100));
		}
		pTkn = strtok(NULL, ",");
	}
	return 0;
}
#endif


