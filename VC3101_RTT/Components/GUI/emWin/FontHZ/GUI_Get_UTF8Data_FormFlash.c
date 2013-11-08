/*
件主要是用于从外部存储器读取字体点阵数据，并提供为emWin提供相应的接口函数

*/

#include <stddef.h>           /* needed for definition of NULL */ 
#include "GUI_Private.h" 
#include "ff.h" 
//#include "bsp.h"
//#include "MainTask.h"

#define FONT_DATA_FROM_FLASH	1

/* 字模数据的暂存数组,以单个字模的最大字节数为设定值 */ 
#define BYTES_PER_FONT      1024 
static U8 GUI_FontDataBuf[BYTES_PER_FONT];

FIL fsrc;         // 定义文件操作类  
FRESULT res;      // 定义操作结果变量  
UINT bw1;         // 定义读写数量变量 

///////////////////////////////////读STM32F4XX FLASH 里面的字库//////////////
#define ASCIIFontAddr 		0x80A0000			//英文字库地址
#define GBFontAddr 				0x80C0000			//国标字库地址

static void DrawGbChinesChar(U16P c, S16 x, S16 y)
{
	//中文字库开始位置为0x80C0000

	U8* pMatrix = (U8*)(((((c>>8) | 0x80) - 0xA1) * 94 + (((c & 0xff) | 0x80) - 0xA1)) * 28 + GBFontAddr);

	//DrawImage(pMatrix, x, y, 14, 14);
}

static void DrawGbAscChar(char Byte, S16 x, S16 y)
{
	//英文字库开始位置为0x80A0000

	U8* pMatrix = (U8*)(Byte * 14 + ASCIIFontAddr);

	//DrawImage(pMatrix, x, y, 7, 14);
}
void GUI_X_GetFontDataFromFlash(char* font,U16P c, U32 oft, U8 *ptr, U16 bytes) 
{
		//U16P c = *font;
		U8 *pDataStr;
		//pDataStr = (U8*)(((((c>>8) | 0x80) - 0xA1) * 94 + (((c & 0xff) | 0x80) - 0xA1)) * bytes + GBFontAddr);
	  pDataStr = (U8*)(((((c >> 8)-0xA1)) + ((c & 0xFF)-0xA1) * 94)* bytes + GBFontAddr); 
		memcpy(ptr,pDataStr,bytes + 1);
}								
/*---------------------------------------------------------------------------*/ 
/*字库外部函数部分-----读SD卡里面的字库------------------------------------------------------*/ 
void GUI_X_GetFontData(char* font, U32 oft, U8 *ptr, U16 bytes) 
{ 
    res = f_open(&fsrc, font, FA_OPEN_EXISTING | FA_READ);   //打开字库文件   
    if(res != FR_OK)   
    {   
       
    }   
    res = f_lseek(&fsrc,oft); //找到首地址  
    res = f_read(&fsrc, ptr, bytes, &bw1); //读取字库点阵数据 
    res = f_close(&fsrc); //关闭字体  

} 

static void GUI_GetDataFromMemory(const GUI_FONT_PROP GUI_UNI_PTR *pProp, U16P c) 
{ 
    U16 BytesPerFont; 
    U32 oft; 
    char *font = (char *)pProp->paCharInfo->pData; 

    /* 每个字模的数据字节数 */
    BytesPerFont = GUI_pContext->pAFont->YSize * pProp->paCharInfo->BytesPerLine; 
    if (BytesPerFont > BYTES_PER_FONT)
    {
        BytesPerFont = BYTES_PER_FONT;
    }
    /* 英文字符地址偏移算法 */ 
    if (c < 0x80)                                                                
    { 
        oft = (c-0x20) * BytesPerFont; 
    } 
    else                                                                           
    { 
        /* 用于读取12*12 和 16*16点阵字符 */
        if(font[21] == '1')
        {
            /* 中文字符地址偏移算法包括符号 */
            oft = ((((c >> 8)-0xA1)) + ((c & 0xFF)-0xA1) * 94)* BytesPerFont; 
        }
        /* 用于读取24*24 48*48 */
        else
        {
            /* 中文字符地址偏移算法包括符号 */
            oft = ((((c >> 8)-0xA1)) + ((c & 0xFF)-0xB0) * 94)* BytesPerFont;
        }

    }

	#if(FONT_DATA_FROM_FLASH)
	GUI_X_GetFontDataFromFlash(font,c, oft, GUI_FontDataBuf, BytesPerFont); 
	#else
	GUI_X_GetFontData(font, oft, GUI_FontDataBuf, BytesPerFont); 
	#endif
       
} 

void GUIPROP_X_DispChar(U16P c)  
{ 
    int BytesPerLine; 
    GUI_DRAWMODE DrawMode = GUI_pContext->TextMode; 
    const GUI_FONT_PROP GUI_UNI_PTR *pProp = GUI_pContext->pAFont->p.pProp; 
    //搜索定位字库数据信息  
    for (; pProp; pProp = pProp->pNext)                                          
    { 
        if ((c >= pProp->First) && (c <= pProp->Last))break; 
    } 
    if (pProp) 
    { 
        GUI_DRAWMODE OldDrawMode;
        const GUI_CHARINFO GUI_UNI_PTR * pCharInfo = pProp->paCharInfo;
        GUI_GetDataFromMemory(pProp, c);//取出字模数据
        BytesPerLine = pCharInfo->BytesPerLine;                
        OldDrawMode  = LCD_SetDrawMode(DrawMode);
        LCD_DrawBitmap(GUI_pContext->DispPosX, GUI_pContext->DispPosY,
                       pCharInfo->XSize, GUI_pContext->pAFont->YSize,
                       GUI_pContext->pAFont->XMag, GUI_pContext->pAFont->YMag,
                       1,     /* Bits per Pixel */
                       BytesPerLine,
                       &GUI_FontDataBuf[0],
                       &LCD_BKCOLORINDEX
                       );
        /* Fill empty pixel lines */
        if (GUI_pContext->pAFont->YDist > GUI_pContext->pAFont->YSize) 
        {
            int YMag = GUI_pContext->pAFont->YMag;
            int YDist = GUI_pContext->pAFont->YDist * YMag;
            int YSize = GUI_pContext->pAFont->YSize * YMag;
            if (DrawMode != LCD_DRAWMODE_TRANS) 
            {
                LCD_COLOR OldColor = GUI_GetColor();
                GUI_SetColor(GUI_GetBkColor());
                LCD_FillRect(GUI_pContext->DispPosX, GUI_pContext->DispPosY + YSize, 
                             GUI_pContext->DispPosX + pCharInfo->XSize, 
                             GUI_pContext->DispPosY + YDist);
                GUI_SetColor(OldColor);
            }
        }
        LCD_SetDrawMode(OldDrawMode); /* Restore draw mode */
//      if (!GUI_MoveRTL)
        GUI_pContext->DispPosX += pCharInfo->XDist * GUI_pContext->pAFont->XMag;
    }
} 

/*********************************************************************
*
*       GUIPROP_GetCharDistX
*/
int GUIPROP_X_GetCharDistX(U16P c) 
{
    const GUI_FONT_PROP GUI_UNI_PTR * pProp = GUI_pContext->pAFont->p.pProp;  
    for (; pProp; pProp = pProp->pNext)                                         
    {
        if ((c >= pProp->First) && (c <= pProp->Last))break;
    }
    return (pProp) ? (pProp->paCharInfo)->XSize * GUI_pContext->pAFont->XMag : 0;
}

