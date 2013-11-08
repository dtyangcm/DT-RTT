#include "bsp_lcd_syb_gdi.h"
#include "string.h" 
#include "bsp_lcd_syb_init.h"

#define ASCIIFontAddr 		0x80A0000			//Ӣ���ֿ��ַ
#define GBFontAddr 				0x80C0000			//�����ֿ��ַ

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
/* (15 X 30 , ����, �Ӵ� )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,
0x01,0xC0,0x0F,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,
0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,
0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x0F,0xF8,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"1",1*/
/* (15 X 30 , ����, �Ӵ� )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xE0,
0x0C,0x78,0x18,0x38,0x30,0x1C,0x30,0x1C,0x38,0x1C,0x38,0x1C,0x00,0x18,
0x00,0x38,0x00,0x70,0x00,0x60,0x00,0xC0,0x01,0x80,0x03,0x00,0x06,0x00,
0x0C,0x0C,0x18,0x0C,0x30,0x1C,0x3F,0xFC,0x3F,0xF8,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"2",2*/
/* (15 X 30 , ����, �Ӵ� )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xC0,
0x1C,0xF0,0x38,0x70,0x38,0x38,0x38,0x38,0x38,0x38,0x00,0x38,0x00,0x70,
0x00,0xE0,0x03,0xC0,0x00,0x70,0x00,0x38,0x00,0x1C,0x00,0x1C,0x38,0x1C,
0x38,0x1C,0x38,0x1C,0x38,0x38,0x18,0x70,0x0F,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"3",3*/
/* (15 X 30 , ����, �Ӵ� )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x70,
0x00,0xF0,0x00,0xF0,0x01,0xF0,0x03,0x70,0x03,0x70,0x06,0x70,0x0C,0x70,
0x0C,0x70,0x18,0x70,0x18,0x70,0x30,0x70,0x60,0x70,0x3F,0xFC,0x00,0x70,
0x00,0x70,0x00,0x70,0x00,0x70,0x00,0xF0,0x03,0xFE,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"4",4*/
/* (15 X 30 , ����, �Ӵ� )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFC,
0x0F,0xFC,0x0C,0x00,0x0C,0x00,0x0C,0x00,0x18,0x00,0x18,0x00,0x1B,0xE0,
0x1E,0x78,0x1C,0x38,0x18,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x38,0x1C,
0x38,0x1C,0x38,0x38,0x30,0x38,0x18,0x70,0x0F,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"5",5*/
/* (15 X 30 , ����, �Ӵ� )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xE0,
0x0E,0x38,0x1C,0x38,0x18,0x38,0x38,0x00,0x30,0x00,0x70,0x00,0x77,0xE0,
0x7E,0x70,0x78,0x38,0x78,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x70,0x1C,
0x30,0x1C,0x38,0x18,0x1C,0x38,0x1E,0x70,0x07,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"6",6*/
/* (15 X 30 , ����, �Ӵ� )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xFC,
0x1F,0xFC,0x38,0x18,0x30,0x30,0x30,0x30,0x00,0x60,0x00,0x60,0x00,0xC0,
0x00,0xC0,0x01,0x80,0x01,0x80,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,
0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"7",7*/
/* (15 X 30 , ����, �Ӵ� )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xE0,
0x3C,0x78,0x38,0x38,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x78,0x1C,0x3C,0x38,
0x1F,0x70,0x0F,0xC0,0x1D,0xF0,0x38,0x78,0x30,0x38,0x70,0x1C,0x70,0x1C,
0x70,0x1C,0x70,0x1C,0x38,0x38,0x1C,0x70,0x0F,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"8",8*/
/* (15 X 30 , ����, �Ӵ� )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xC0,
0x1C,0x70,0x38,0x38,0x70,0x38,0x70,0x18,0x70,0x1C,0x70,0x1C,0x70,0x1C,
0x70,0x3C,0x38,0x3C,0x3C,0xFC,0x0F,0xDC,0x00,0x1C,0x00,0x38,0x00,0x38,
0x00,0x38,0x38,0x70,0x38,0x70,0x38,0xE0,0x1F,0x80,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"9",9*/
/* (15 X 30 , ����, �Ӵ� )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x1C,0x00,0x3E,0x00,0x3E,0x00,0x1C,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*".",10*/
/* (15 X 30 , ����, �Ӵ� )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x7F,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"-",11*/
/* (15 X 30 , ����, �Ӵ� )*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x07,0x00,0x0F,0x00,0x7F,0xF0,
0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,
0x07,0x00,0x07,0x18,0x07,0x18,0x03,0xB0,0x03,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,/*"t",12*/
/* (15 X 30 , ����, �Ӵ� )*/
};


static s16 m_cxScreen = 240;							    //������Ļ���(��λΪ����)
static s16 m_cyScreen = 128;								//������Ļ�߶�(��λΪ����)

static s16 m_ViewPosX = 0;								//��ͼˮƽ���
static s16 m_ViewPosY = 0;								//��ͼ��ֱ���
static s16 m_ViewSizeX = 240;								//��ͼˮƽ���
static s16 m_ViewSizeY = 128;								//��ͼ��ֱ���
static u8 m_bUseView = 0;
									
static s16 m_nRedrawIndex = 0;
static u8	m_bScreenFlush = 1;
static u8 m_Color = 0x00;

#define GDI_MEM_ROW		128
#define GDI_MEM_COL		30
u8 GdiMem[GDI_MEM_ROW][GDI_MEM_COL];										//��ʾ128��240�����Դ����


#define MAKE_COLOR(x)	((x) ^ m_Color)
/****************************************************************************
* ��	�ƣ�u8 BeginPaint(void)
* ��	�ܣ�GUI��ʼ��������������LCD�ĳ�ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵	����Ҫʹ��LCDǰ������øú���һ��
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
	//��ת��ɫ
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
* ��	�ƣ�void EraseScreen(void)
* ��	�ܣ�������MCU�ϵ��Դ�
* ��ڲ�������
* ���ڲ�������
* ˵	����
****************************************************************************/	
void EraseScreen(void)
{
	ClearScreen();
	memset(GdiMem, 0, sizeof(GdiMem));
}

//����ͼ���ػ�
void SetRedraw(u8 bEnable)
{
	//�����ֹ�ػ�
	if(bEnable == 0) 
	{	
		m_nRedrawIndex++;
		return;
	}

	//���ʹ���ػ�
	if(m_nRedrawIndex > 0) m_nRedrawIndex--;

	//����ػ汻����
	if(m_nRedrawIndex == 0)
	{
		//��ʾͼ��
		LCD_WriteCommand(LCD_DIS_GON); 
	}
}

//ˢ����Ļָ��������ȡֵ��Χ[0,63]����ȡֵ��Χ[0,7]
//sx: �������ʼ��	sy: �������ʼ��	ex: ������������	ey: ������������
void RefreshDC(s16 sx, s16 sy, s16 ex, s16 ey)
{
	u8 i, j;

	//�����ֹˢ���򷵻�
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
		//д��ַ
		SetAddr(i * GDI_MEM_COL + sx);
		
		//����Դ�
		LCD_WriteCommand(LCD_AUT_WR);
		for(j = sx; j <= ex; j++)
		{
			LCD_WriteData(GdiMem[i][j]);
		} 
		LCD_WriteCommand(LCD_AUT_OVR);
	}
}

//ʹ�ܽ�ֹˢ��
void EnableScreenFlush(u8 bEnable)
{
	m_bScreenFlush = bEnable;	
}

//ˢ��������Ļ
void FlushScreen(void)
{
	int i, j;

	//������ʾ
	if(m_nRedrawIndex == 0)
	{
		LCD_WriteCommand(LCD_DIS_GON); 
	}
	else
	{
		LCD_WriteCommand(LCD_DIS_OFF); 
	}

	//ˢ��
	SetAddr(0);
	LCD_WriteCommand(LCD_AUT_WR);

	for(i=0; i<GDI_MEM_ROW; i++)
	{
		//д����
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

	//�Ƚ��й���
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

	//��ͼ������ת��==============================================================================
	if(m_bUseView == 1)
	{
		//ʹ��ͼ������ͼ��
		if((x >= m_ViewSizeX) || (y >= m_ViewSizeY))	return;	//��ͼ���ܳ�����ͼ
		if(((x + cx) < 0) || (y + cy < 0)) return;		//��ͼ��û������ͼ

		//�����ͼ���û������Ļ
		if(x < 0)
		{
			//ȡ��Ļ������
			cx += x;
			x = 0;
		}
	
		//�����ͼ���û������Ļ
		if(y < 0)
		{
			//ȡ��Ļ������
			cy += y;
			y = 0;
		}

		//�����ͼ��Χ������ͼ
		if((x+cx) > m_ViewSizeX) cx = m_ViewSizeX - x;
		if((y+cy) > m_ViewSizeY) cy = m_ViewSizeY - y;

		//��ͼ����Ļת��
		x += m_ViewPosX;		
		y += m_ViewPosY; 
	}
										 
	//������Ч�Լ��
	if((x >= m_cxScreen) || (y >= m_cyScreen))	return;		//��ͼ������Ļ
	if(((x + cx) < 0) || ((y + cy) < 0)) return;	 		//��ͼδ������Ļ

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

	//��������ʾ����
	if((x+cx) > m_cxScreen) cx = m_cxScreen - x;
	if((y+cy) > m_cyScreen) cy = m_cyScreen - y;

	//��x���Դ�����е����
	xAlign = (x >> 3);

	//��x���Դ�����еĽ�����
	xEndAlign = (x + cx) >> 3;

	//ˢ����Ļָ������
	RefreshDC(xAlign, y, (xEndAlign >= GDI_MEM_COL) ? (GDI_MEM_COL-1) : xEndAlign, y + cy -1);
}


void DrawGbChinesChar(char HiByte, char LoByte, s16 x, s16 y)
{
	//�����ֿ⿪ʼλ��Ϊ0x80C0000

	u8* pMatrix = (u8*)((((HiByte | 0x80) - 0xA1) * 94 + ((LoByte | 0x80) - 0xA1)) * 28 + GBFontAddr);

	DrawImage(pMatrix, x, y, 14, 14);
}

void DrawGbAscChar(char Byte, s16 x, s16 y)
{
	//Ӣ���ֿ⿪ʼλ��Ϊ0x80A0000

	u8* pMatrix = (u8*)(Byte * 14 + ASCIIFontAddr);

	DrawImage(pMatrix, x, y, 7, 14);

}

//�������
void DrawGbText(char *s, s16 x, s16 y) 
{
	while(*s != 0)
	{
		if((*s & 0x80) == 0)
		{
			//Ӣ��
			DrawGbAscChar(*s, x, y);
			
			s += 1;
			x += 7;
		}
		else
		{
			//����
			DrawGbChinesChar(*s, *(s+1), x, y);
	
			s += 2;
			x += 14;
		}
	}	 
}

//��ʵ�ľ��Σ���λΪ����
void FillRect(s16 x, s16 y, s16 cx, s16 cy)		//x:[0,127]		y:[0,63]
{
	u8	sMask, eMask;
	s16	xAlign, xMod, xEndAlign, xEndMod, i, j;

	//�Ƚ��й���
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


	//��ͼ������ת��==============================================================================
	if(m_bUseView == 1)
	{
		//ʹ��ͼ������ͼ��
		if((x >= m_ViewSizeX) || (y >= m_ViewSizeY))	return;	//��ͼ���ܳ�����ͼ
		if(((x + cx) < 0) || (y + cy < 0)) return;		//��ͼ��û������ͼ

		//�����ͼ���û������Ļ
		if(x < 0)
		{
			//ȡ��Ļ������
			cx += x;
			x = 0;
		}
	
		//�����ͼ���û������Ļ
		if(y < 0)
		{
			//ȡ��Ļ������
			cy += y;
			y = 0;
		}

		//�����ͼ��Χ������ͼ
		if((x+cx) > m_ViewSizeX) cx = m_ViewSizeX - x;
		if((y+cy) > m_ViewSizeY) cy = m_ViewSizeY - y;

		//��ͼ����Ļת��
		x += m_ViewPosX;		
		y += m_ViewPosY; 
	}
										 
	//������Ч�Լ��
	if((x >= m_cxScreen) || (y >= m_cyScreen))	return;		//��ͼ������Ļ
	if(((x + cx) < 0) || ((y + cy) < 0)) return;	 		//��ͼδ������Ļ

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

	//��������ʾ����
	if((x+cx) > m_cxScreen) cx = m_cxScreen - x;
	if((y+cy) > m_cyScreen) cy = m_cyScreen - y;

	//��x���Դ�����е����
	xAlign = (x >> 3);
	xMod =  x % 8;
	sMask = 0xFF << (8 - xMod);

	//��x���Դ�����еĽ�����
	xEndAlign = (x + cx) >> 3;
	xEndMod =  (x + cx) % 8;
	eMask = (0xFF >> xEndMod);
	
	//���ͽ�������ͬһ�ֽ����غϴ���
	if(xAlign == xEndAlign)								   	
	{
		sMask = sMask | eMask;
	}

	//�����Դ��б�Ӱ������
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

	//ˢ����Ļָ������
	RefreshDC(xAlign, y, (xEndAlign >= GDI_MEM_COL) ? (GDI_MEM_COL-1) : xEndAlign, y + cy -1);
}

//x:[0,127]		y:[0,63]
void DrawImage(const u8* pImage, s16 x, s16 y, s16 cx, s16 cy)
{
	SupperDrawImage(pImage, x, y, 0, 0, cx, cy, cx, cy);
}

//x, y: ����Ļ�ϵ����
//xImg, yImg������ͼ���ϵ����
//cxImg, cyImg: ����ͼ���ϵ�����
//Width, Height: ͼ��ĳ���
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

	//���ͼ���ڲ���==============================================================================
	if((cxImg <= 0) || (cyImg <= 0)) return;			//ͼ�񳤿���С����
	if((xImg < 0) || (yImg < 0)) return;				//ͼ���еĻ�ͼ��㲻��С����
	if((xImg >= Width) || (yImg >= Height)) return;		//ͼ���еĻ�ͼ��㲻�ܲ��ܳ���ͼ��
	if((xImg + cxImg) > Width) cxImg = Width - xImg;	//ͼ���еĻ�ͼ�����ܳ���ͼ��
	if((yImg + cyImg) > Height) cyImg = Height - yImg;	//ͼ���еĻ�ͼ�����ܳ���ͼ��


	//��ͼ������ת��==============================================================================
	if(m_bUseView == 1)
	{
		//ʹ��ͼ������ͼ��
		if((x >= m_ViewSizeX) || (y >= m_ViewSizeY))	return;	//��ͼ���ܳ�����ͼ
		if(((x + cxImg) < 0) || (y + cyImg < 0)) return;		//��ͼ��û������ͼ

		//�����ͼ���û������Ļ
		if(x < 0)
		{
			//ȡ��Ļ������
			xImg -= x;
			cxImg += x;
			x = 0;
		}
	
		//�����ͼ���û������Ļ
		if(y < 0)
		{
			//ȡ��Ļ������
			yImg -= y;
			cyImg += y;
			y = 0;
		}

		//�����ͼ��Χ������ͼ
		if((x+cxImg) > m_ViewSizeX) cxImg = m_ViewSizeX - x;
		if((y+cyImg) > m_ViewSizeY) cyImg = m_ViewSizeY - y;

		//��ͼ����Ļת��
		x += m_ViewPosX;		
		y += m_ViewPosY; 
	}
	
	//������Ч�Լ�飬ʹ��ͼ������������=================================================
	if((x >= m_cxScreen) || (y >= m_cyScreen))	return;	//��ͼ���ܳ�����Ļ
	if(((x + cxImg) < 0) || (y + cyImg < 0)) return;	//��ͼ��û������Ļ	
	
	//�����ͼ���û������Ļ
	if(x < 0)
	{
		//ȡ��Ļ������
		xImg -= x;
		cxImg += x;
		x = 0;
	}

	//�����ͼ���û������Ļ
	if(y < 0)
	{
		//ȡ��Ļ������
		yImg -= y;
		cyImg += y;
		y = 0;
	}

	//�����ͼ��Χ������Ļ
	if((x+cxImg) > m_cxScreen) cxImg = m_cxScreen - x;
	if((y+cyImg) > m_cyScreen) cyImg = m_cyScreen - y;

	//��x���Դ�����е����
	xAlign = (x >> 3);
	sMask = 0xFF << (8 - (x % 8));
	xMod =  (8 + (x % 8) - (xImg % 8)) % 8;


	//��x���Դ�����еĽ�����
	xEndAlign = (x + cxImg) >> 3;
	eMask = (0xFF >> ((x + cxImg) % 8));
	//xEndMod =  (((xImg + cxImg) % 8) + xMod) % 8;	  
	

	//��ͼƬ������ͼƬԭ���ǰ������ռ���ֽ���
	xImgAlign = (xImg>>3);
	if((xImg %8) != 0) xImgAlign = xImgAlign + 1;
	
	//���ͽ�������ͬһ�ֽ����غϴ���
	if(xAlign == xEndAlign)								   	
	{
		sMask = sMask | eMask;
	}
	
	//Width��8λ���룬ȡ��ģʱ��������
	if((Width & 0x0007) != 0)
	{
		Width = (Width & (~0x0007)) + 8;
	}
			  
	//�����Դ��б�Ӱ������
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

	//ˢ����Ļָ������
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
	//������
	FillRect(x, y, cx  , 1);
}

void DrawVertLine(s16 x, s16 y, s16 cy)
{
	//������
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


