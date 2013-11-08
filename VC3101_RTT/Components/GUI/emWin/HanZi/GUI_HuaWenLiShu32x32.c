#include "GUI.h"


extern void GUIPROP_X_DispChar(U16P c);
extern int GUIPROP_X_GetCharDistX(U16P c);

GUI_CONST_STORAGE GUI_CHARINFO GUI_HuaWenLiShu32_CharInfo[2] =  
{     
    {  32,  32,  4, (void *)"0:/system/gui_font/ASCHuaWenLiShu32x32.bin"},    
    {  32,  32,  4, (void *)"0:/system/gui_font/HuaWenLiShu32x32.bin"},        
}; 
GUI_CONST_STORAGE GUI_FONT_PROP GUI_HuaWenLiShu32_PropHZ= { 
      0xA1A1,  
      0xFEFE,  
      &GUI_HuaWenLiShu32_CharInfo[1], 
      (void *)0,  
}; 
GUI_CONST_STORAGE  GUI_FONT_PROP GUI_HuaWenLiShu32_PropASC= { 
      0x0000,  
      0x007F,  
      &GUI_HuaWenLiShu32_CharInfo[0], 
      (void GUI_CONST_STORAGE *)&GUI_HuaWenLiShu32_PropHZ,  
}; 
GUI_CONST_STORAGE  GUI_FONT GUI_HuaWenLiShu32 =  
{ 
	GUI_FONTTYPE_PROP_USER,
	32,  
	32,  
	1,   
	1,   
	(void GUI_CONST_STORAGE *)&GUI_HuaWenLiShu32_PropASC
}; 
GUI_CONST_STORAGE  GUI_FONT GUI_HuaWenLiShu32x2 =  
{ 
	GUI_FONTTYPE_PROP_USER,
	32,  
	32,  
	2,   
	2,   
	(void GUI_CONST_STORAGE *)&GUI_HuaWenLiShu32_PropASC 
};


