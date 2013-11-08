#include "GUI.h"


extern void GUIPROP_X_DispChar(U16P c);
extern int GUIPROP_X_GetCharDistX(U16P c);

GUI_CONST_STORAGE GUI_CHARINFO GUI_HuaWenCaiYun32_CharInfo[2] =  
{     
    {  32,  32,  4, (void *)"0:/system/gui_font/ASCHuaWenCaiYun32x32.bin"},    
    {  32,  33,  5, (void *)"0:/system/gui_font/HuaWenCaiYun32x32.bin"},        
}; 
GUI_CONST_STORAGE GUI_FONT_PROP GUI_HuaWenCaiYun32_PropHZ= { 
      0xA1A1,  
      0xF7FE,  
      &GUI_HuaWenCaiYun32_CharInfo[1], 
      (void *)0,  
}; 
GUI_CONST_STORAGE  GUI_FONT_PROP GUI_HuaWenCaiYun32_PropASC= { 
      0x0000,  
      0x007F,  
      &GUI_HuaWenCaiYun32_CharInfo[0], 
      (void GUI_CONST_STORAGE *)&GUI_HuaWenCaiYun32_PropHZ,  
}; 
GUI_CONST_STORAGE  GUI_FONT GUI_HuaWenCaiYun32 =  
{ 
	GUI_FONTTYPE_PROP_USER,
	32,  
	33,  
	1,   
	1,   
	(void GUI_CONST_STORAGE *)&GUI_HuaWenCaiYun32_PropASC
}; 
GUI_CONST_STORAGE  GUI_FONT GUI_HuaWenCaiYun32x2 =  
{ 
	GUI_FONTTYPE_PROP_USER,
	32,  
	33,  
	2,   
	2,   
	(void GUI_CONST_STORAGE *)&GUI_HuaWenCaiYun32_PropASC 
};


