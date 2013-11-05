/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.20                          *
*        Compiled Mar 19 2013, 15:01:00                              *
*        (c) 2013 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0            (GUI_ID_USER + 0x00)
#define ID_BUTTON_0            (GUI_ID_USER + 0x04)
#define ID_RADIO_0            (GUI_ID_USER + 0x06)
#define ID_MENU_0            (GUI_ID_USER + 0x07)
#define ID_LISTBOX_0            (GUI_ID_USER + 0x08)


// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/


/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
    { FRAMEWIN_CreateIndirect,  "  HV3101",            0,                       5,  1,  110,60,FRAMEWIN_CF_MOVEABLE,0},
    { BUTTON_CreateIndirect,    "Cancel",            GUI_ID_BUTTON0,          	2, 20, 44, 16, 0,0},
    { BUTTON_CreateIndirect,    "OK",            	 GUI_ID_BUTTON0,          	50,20, 44, 16, 0,0},
//    { SLIDER_CreateIndirect,     NULL,               GUI_ID_SLIDER0,          142,44, 53, 16, 0,0},
//    { MULTIEDIT_CreateIndirect, "MULTIEDIT",         GUI_ID_MULTIEDIT0,       1,  13, 73, 69, 0,0},
    { DROPDOWN_CreateIndirect,   NULL,               GUI_ID_DROPDOWN0,        0, 0, 90, 20, 0,0},
//    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT0,            142,13, 46, 20, 0,0}
};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void PaintDialog(WM_MESSAGE * pMsg)
{
//    WM_HWIN hWin = pMsg->hWin;

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
    FRAMEWIN_SetBarColor(hWin,1,0x000000);
	FRAMEWIN_SetFont(hWin, GUI_FONT_13_ASCII);
    FRAMEWIN_AddCloseButton(hWin, FRAMEWIN_BUTTON_RIGHT, 0);
//    FRAMEWIN_AddMaxButton(hWin, FRAMEWIN_BUTTON_RIGHT, 1);
//    FRAMEWIN_AddMinButton(hWin, FRAMEWIN_BUTTON_RIGHT, 2);
    FRAMEWIN_SetTitleHeight(hWin,15);
    //
    //GUI_ID_BUTTON0
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON0),&GUI_Font8_ASCII);
    //
    //GUI_ID_BUTTON0
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON0),&GUI_Font8_ASCII);
    //
    //GUI_ID_MULTIEDIT0
    //
    MULTIEDIT_SetAutoScrollH(WM_GetDialogItem(hWin,GUI_ID_MULTIEDIT0),1);
    MULTIEDIT_SetAutoScrollV(WM_GetDialogItem(hWin,GUI_ID_MULTIEDIT0),1);
    MULTIEDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_MULTIEDIT0),"wujialing");
    //
    //GUI_ID_DROPDOWN0
    //
    DROPDOWN_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_DROPDOWN0),0,0xffffff);

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
WM_HWIN  WinDialog(WM_HWIN hParent) 
{ 
	WM_HWIN hWin;
	
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbCallback, hParent, 0, 0);
	
	return hWin;
}
// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
