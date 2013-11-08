#include "GUI.h"

extern void GUIPROP_X_DispChar(U16P c);
extern int GUIPROP_X_GetCharDistX(U16P c);


GUI_CONST_STORAGE GUI_CHARINFO GUI_KaiTi32_CharInfo[2] =  
{     
    {  16,  16,  2, (void *)"0:/system/gui_font/ASCKaiTi16x32.bin"},    
    {  32,  32,  4, (void *)"0:/system/gui_font/KaiTi32x32.bin"},        
}; 
GUI_CONST_STORAGE GUI_FONT_PROP GUI_KaiTi32_PropHZ= { 
      0xA1A1,  
      0xFEFE,  
      &GUI_KaiTi32_CharInfo[1], 
      (void *)0,  
}; 
GUI_CONST_STORAGE  GUI_FONT_PROP GUI_KaiTi32_PropASC= { 
      0x0000,  
      0x007F,  
      &GUI_KaiTi32_CharInfo[0], 
      (void GUI_CONST_STORAGE *)&GUI_KaiTi32_PropHZ,  
}; 
GUI_CONST_STORAGE  GUI_FONT GUI_KaiTi32 =  
{ 
	GUI_FONTTYPE_PROP_USER,
	32,  
	32,  
	1,   
	1,   
	(void GUI_CONST_STORAGE *)&GUI_KaiTi32_PropASC
}; 
GUI_CONST_STORAGE  GUI_FONT GUI_KaiTi32x2 =  
{ 
	GUI_FONTTYPE_PROP_USER,
	32,  
	32,  
	2,   
	2,   
	(void GUI_CONST_STORAGE *)&GUI_KaiTi32_PropASC 
};

