#include "GUI.h"


extern void GUIPROP_X_DispChar(U16P c);
extern int GUIPROP_X_GetCharDistX(U16P c);

GUI_CONST_STORAGE GUI_CHARINFO GUI_WeiRuanYaHei48x62_CharInfo[2] =  
{     
    {  48,  62,  8, (void *)"0:/system/gui_font/ASCWeiRuanYaHei48x62.bin"},    
    {  48,  62,  8, (void *)"0:/system/gui_font/WeiRuanYaHei48x62.bin"},        
}; 
GUI_CONST_STORAGE GUI_FONT_PROP GUI_WeiRuanYaHei48x62_PropHZ= { 
      0xA1A1,  
      0xFEFE,  
      &GUI_WeiRuanYaHei48x62_CharInfo[1], 
      (void *)0,  
}; 
GUI_CONST_STORAGE  GUI_FONT_PROP GUI_WeiRuanYaHei48x62_PropASC= { 
      0x0000,  
      0x007F,  
      &GUI_WeiRuanYaHei48x62_CharInfo[0], 
      (void GUI_CONST_STORAGE *)&GUI_WeiRuanYaHei48x62_PropHZ,  
}; 
GUI_CONST_STORAGE  GUI_FONT GUI_WeiRuanYaHei48x62 =  
{ 
	GUI_FONTTYPE_PROP_USER,
	48,  
	62,  
	1,   
	1,   
	(void GUI_CONST_STORAGE *)&GUI_WeiRuanYaHei48x62_PropASC
}; 
GUI_CONST_STORAGE  GUI_FONT GUI_WeiRuanYaHei48x62x2 =  
{ 
	GUI_FONTTYPE_PROP_USER,
	48,  
	62,  
	2,   
	2,   
	(void GUI_CONST_STORAGE *)&GUI_WeiRuanYaHei48x62_PropASC 
};

