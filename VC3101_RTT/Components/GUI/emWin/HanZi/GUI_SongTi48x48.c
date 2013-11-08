#include "GUI.h"

extern void GUIPROP_X_DispChar(U16P c);
extern int GUIPROP_X_GetCharDistX(U16P c);


GUI_CONST_STORAGE GUI_CHARINFO GUI_SongTi48_CharInfo[2] =  
{     
    {  24,  24,  3, (void *)"0:/system/gui_font/ASCSongTi24x48.bin"},    
    {  48,  48,  6, (void *)"0:/system/gui_font/SongTi48x48.bin"},        
}; 
GUI_CONST_STORAGE GUI_FONT_PROP GUI_SongTi48_PropHZ= { 
      0xB0A1,  
      0xF7FE,  
      &GUI_SongTi48_CharInfo[1], 
      (void *)0,  
}; 
GUI_CONST_STORAGE  GUI_FONT_PROP GUI_SongTi48_PropASC= { 
      0x0000,  
      0x007F,  
      &GUI_SongTi48_CharInfo[0], 
      (void GUI_CONST_STORAGE *)&GUI_SongTi48_PropHZ,  
}; 
GUI_CONST_STORAGE  GUI_FONT GUI_SongTi48 =  
{ 
	GUI_FONTTYPE_PROP_USER,
	48,  
	48,  
	1,   
	1,   
	(void GUI_CONST_STORAGE *)&GUI_SongTi48_PropASC
}; 
GUI_CONST_STORAGE  GUI_FONT GUI_SongTi48x2 =  
{ 
	GUI_FONTTYPE_PROP_USER,
	48,  
	48,  
	2,   
	2,   
	(void GUI_CONST_STORAGE *)&GUI_SongTi48_PropASC 
};


