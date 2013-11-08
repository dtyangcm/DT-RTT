#include "GUI.h"


extern void GUIPROP_X_DispChar(U16P c);
extern int GUIPROP_X_GetCharDistX(U16P c); 

GUI_CONST_STORAGE GUI_CHARINFO GUI_HuaWenXingKai25_CharInfo[2] =  
{     
    {  25,  25,  4, (void *)"0:/system/gui_font/ASCHuaWenXingKai25x25.bin"},    
    {  25,  25,  4, (void *)"0:/system/gui_font/HuaWenXingKai25x25.bin"},        
}; 
GUI_CONST_STORAGE GUI_FONT_PROP GUI_HuaWenXingKai25_PropHZ= { 
      0xA1A1,  
      0xFEFE,  
      &GUI_HuaWenXingKai25_CharInfo[1], 
      (void *)0,  
}; 
GUI_CONST_STORAGE  GUI_FONT_PROP GUI_HuaWenXingKai25_PropASC= { 
      0x0000,  
      0x007F,  
      &GUI_HuaWenXingKai25_CharInfo[0], 
      (void GUI_CONST_STORAGE *)&GUI_HuaWenXingKai25_PropHZ,  
}; 
GUI_CONST_STORAGE  GUI_FONT GUI_HuaWenXingKai25 =  
{ 
	GUI_FONTTYPE_PROP_USER,
	25,  
	25,  
	1,   
	1,   
	(void GUI_CONST_STORAGE *)&GUI_HuaWenXingKai25_PropASC
}; 
GUI_CONST_STORAGE  GUI_FONT GUI_HuaWenXingKai25x2 =  
{ 
	GUI_FONTTYPE_PROP_USER,
	25,  
	25,  
	2,   
	2,   
	(void GUI_CONST_STORAGE *)&GUI_HuaWenXingKai25_PropASC 
};


