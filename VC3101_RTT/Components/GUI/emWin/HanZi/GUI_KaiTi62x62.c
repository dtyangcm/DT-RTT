#include "GUI.h"


extern void GUIPROP_X_DispChar(U16P c);
extern int GUIPROP_X_GetCharDistX(U16P c);

GUI_CONST_STORAGE GUI_CHARINFO GUI_KaiTi62_CharInfo[2] =  
{     
    {  32,  32,  4, (void *)"0:/system/gui_font/ASCKaiTi32x64.bin"},    
    {  64,  64,  8, (void *)"0:/system/gui_font/KaiTi64x64.bin"},        
}; 
GUI_CONST_STORAGE GUI_FONT_PROP GUI_KaiTi62_PropHZ= { 
      0xA1A1,  
      0xFEFE,  
      &GUI_KaiTi62_CharInfo[1], 
      (void *)0,  
}; 
GUI_CONST_STORAGE  GUI_FONT_PROP GUI_KaiTi62_PropASC= { 
      0x0000,  
      0x007F,  
      &GUI_KaiTi62_CharInfo[0], 
      (void GUI_CONST_STORAGE *)&GUI_KaiTi62_PropHZ,  
}; 
GUI_CONST_STORAGE  GUI_FONT GUI_KaiTi62 =  
{ 
	GUI_FONTTYPE_PROP_USER,
	64,  
	64,  
	1,   
	1,   
	(void GUI_CONST_STORAGE *)&GUI_KaiTi62_PropASC
}; 
GUI_CONST_STORAGE  GUI_FONT GUI_KaiTi62x2 =  
{ 
	GUI_FONTTYPE_PROP_USER,
	64,  
	64,  
	2,   
	2,   
	(void GUI_CONST_STORAGE *)&GUI_KaiTi62_PropASC 
};

