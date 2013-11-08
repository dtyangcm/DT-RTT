/*
******************************************************************
**                      uCGUIBuilder                            **
**                  Version:   4.0.0.0                          **
**                     2012 / 04                               **
**                   CpoyRight to: wyl                          **
**              Email:ucguibuilder@163.com                        **
**          This text was Created by uCGUIBuilder               **
******************************************************************/

#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"

#include "WM.h"
#include "BUTTON.h"
#include "CHECKBOX.h"
#include "DROPDOWN.h"
#include "EDIT.h"
#include "FRAMEWIN.h"
#include "LISTBOX.h"
#include "MULTIEDIT.h"
#include "RADIO.h"
#include "SLIDER.h"
#include "TEXT.h"
#include "PROGBAR.h"
#include "SCROLLBAR.h"
#include "LISTVIEW.h"





//EventsFunctionList
//EndofEventsFunctionList


/*********************************************************************
*
*       static data
*
**********************************************************************
*/

#define GUI_ID_TEXT10   GUI_ID_USER+1
#define GUI_ID_TEXT11   GUI_ID_USER+2
#define GUI_ID_TEXT12   GUI_ID_USER+3
#define GUI_ID_TEXT13   GUI_ID_USER+4
#define GUI_ID_TEXT14   GUI_ID_USER+5
#define GUI_ID_TEXT15   GUI_ID_USER+6


/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
    { FRAMEWIN_CreateIndirect,  "Dync Wet Ver 1.0.0",0,                       0,  0,  241,130,FRAMEWIN_CF_MOVEABLE,0},
    { BUTTON_CreateIndirect,    "标定",         GUI_ID_BUTTON0,          1,  90, 52, 22, 0,0},
    { BUTTON_CreateIndirect,    "标定参数",          GUI_ID_BUTTON1,          60, 90, 52, 22, 0,0},
    { BUTTON_CreateIndirect,    "系统参数",          GUI_ID_BUTTON2,          120,90, 52, 22, 0,0},
		{ BUTTON_CreateIndirect,    "AD通道",           GUI_ID_BUTTON3,          177,90, 52, 22, 0,0},
    { TEXT_CreateIndirect,      "总重:",         GUI_ID_TEXT0,            105,10,  54, 12, 0,0},
    { TEXT_CreateIndirect,      "轴数:",          GUI_ID_TEXT1,            105,25, 53, 12, 0,0},
    { TEXT_CreateIndirect,      "传感器：",          GUI_ID_TEXT2,            0, 1,  53, 12, 0,0},
    { TEXT_CreateIndirect,      "光幕：",              GUI_ID_TEXT3,            0, 13, 29, 12, 0,0},
    { TEXT_CreateIndirect,      "地感:",              GUI_ID_TEXT4,            0, 25, 29, 12, 0,0},
    { TEXT_CreateIndirect,      "AxisSt",            GUI_ID_TEXT5,            0, 41, 41, 12, 0,0},
    { TEXT_CreateIndirect,      "OK",                GUI_ID_TEXT6,            63, 1,  17, 12, 0,0},
    { TEXT_CreateIndirect,      "IN_COLSE",          GUI_ID_TEXT7,            33, 13, 53, 12, 0,0},
    { TEXT_CreateIndirect,      "IN_CLOSE",          GUI_ID_TEXT8,            33, 25, 53, 12, 0,0},
    { TEXT_CreateIndirect,      "Zero",              GUI_ID_TEXT9,            46, 41, 29, 12, 0,0},
    { TEXT_CreateIndirect,      "重量:",        GUI_ID_TEXT10,           105,53, 65, 12, 0,0},
    { TEXT_CreateIndirect,      "StaticSt:",         GUI_ID_TEXT11,           105,66, 59, 12, 0,0},
    //{ TEXT_CreateIndirect,      "25000",             GUI_ID_TEXT12,           171,10,  35, 12, 0,0},
    { TEXT_CreateIndirect,      "3",                 GUI_ID_TEXT13,           160,25, 11, 12, 0,0},
    { TEXT_CreateIndirect,      "12345",             GUI_ID_TEXT14,           177,53, 35, 12, 0,0},
    { TEXT_CreateIndirect,      "Zero",              GUI_ID_TEXT15,           177,66, 29, 12, 0,0}
 
};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void PaintDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    GUI_SetColor(0x000000);
    GUI_DrawLine(0,86,239,86);
    GUI_SetColor(0x000000);
    GUI_DrawLine(88,1,88,86);
	
		GUI_SetFont(GUI_FONT_24_ASCII);
		GUI_DispDecAt(12345, 160, 1, 5);
	
		GUI_SetFont(&GUI_FontHZ12);
		GUI_DispStringHCenterAt("我的", 0, 70);
	
}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    //
    //FRAMEWIN
    //
    FRAMEWIN_AddCloseButton(hWin, FRAMEWIN_BUTTON_RIGHT, 0);
    FRAMEWIN_AddMaxButton(hWin, FRAMEWIN_BUTTON_RIGHT, 1);
    FRAMEWIN_AddMinButton(hWin, FRAMEWIN_BUTTON_RIGHT, 2);
		//
    //GUI_ID_TEXT10
    //
		TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT10),&GUI_FontHZ12);
	
		TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT0),&GUI_FontHZ12);
		TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT1),&GUI_FontHZ12);
		TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT2),&GUI_FontHZ12);
		TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT3),&GUI_FontHZ12);
		TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT4),&GUI_FontHZ12);
	
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT11),GUI_FONT_8_ASCII);
		BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON0),&GUI_Font8_ASCII);
}




/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            PaintDialog(pMsg);
            break;
        case WM_INIT_DIALOG:
            InitDialog(pMsg);
            break;
        case WM_KEY:
            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
            {
                case GUI_KEY_ESCAPE:
                    GUI_EndDialog(hWin, 1);
                    break;
                case GUI_KEY_ENTER:
                    GUI_EndDialog(hWin, 0);
                    break;
            }
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc); 
            NCode = pMsg->Data.v;        
            switch (Id) 
            {
                case GUI_ID_OK:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;
                case GUI_ID_CANCEL:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;

            }
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}


/*********************************************************************
*
*       MainTask
*
**********************************************************************
*/
void MainTask(void) 
{ 
//     GUI_Init();
//     WM_SetDesktopColor(GUI_WHITE);      /* Automacally update desktop window */
//     WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */
    //PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
    //FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
    //PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
    //BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
    //CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
    //DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
    //SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
    //SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
    //HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
    //RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
    GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);
}

