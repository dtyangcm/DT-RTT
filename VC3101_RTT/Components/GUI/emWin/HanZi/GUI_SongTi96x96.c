#include "GUI.h"

extern void GUIPROP_X_DispChar(U16P c);
extern int GUIPROP_X_GetCharDistX(U16P c);

GUI_CONST_STORAGE GUI_CHARINFO GUI_SongTi96_CharInfo[2] =  
{     
    {  48,  48,  6, (void *)"0:/system/gui_font/ASCSongTi48x96.bin"},    
    {  96,  96,  12, (void *)"0:/system/gui_font/SongTi96x96.bin"},        
}; 
GUI_CONST_STORAGE GUI_FONT_PROP GUI_SongTi96_PropHZ= { 
      0xA1A1,  
      0xFEFE,  
      &GUI_SongTi96_CharInfo[1], 
      (void *)0,  
}; 
GUI_CONST_STORAGE  GUI_FONT_PROP GUI_SongTi96_PropASC= { 
      0x0000,  
      0x007F,  
      &GUI_SongTi96_CharInfo[0], 
      (void GUI_CONST_STORAGE *)&GUI_SongTi96_PropHZ,  
}; 
GUI_CONST_STORAGE  GUI_FONT GUI_SongTi96 =  
{ 
	GUI_FONTTYPE_PROP_USER,
	96,  
	96,  
	1,   
	1,   
	(void GUI_CONST_STORAGE *)&GUI_SongTi96_PropASC
}; 
GUI_CONST_STORAGE  GUI_FONT GUI_SongTi96x2 =  
{ 
	GUI_FONTTYPE_PROP_USER,
	96,  
	96,  
	2,   
	2,   
	(void GUI_CONST_STORAGE *)&GUI_SongTi96_PropASC 
};
