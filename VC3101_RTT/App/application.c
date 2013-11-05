/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

/**
 * @addtogroup STM32
 */
/*@{*/

#include <stdio.h>
#include "string.h"
#include "stm32f4xx.h"
#include <board.h>
#include <rtthread.h>
#include "bsp_led.h"


#include "gui.h"
#include "widget.h"
#include "WM.h"
#include "MULTIEDIT.h"


#define MSG_CHANGE_TEXT WM_USER+0


extern WM_HWIN  WinDialog(WM_HWIN hParent);


static WM_HWIN _hWindow1;
static WM_HWIN _hWindow2;
static WM_HWIN _hChild;


static char _acInfoText[40];
s32 g_iRunTime = 0;

ALIGN(RT_ALIGN_SIZE)
static char thread_Gui_stack[2048];
struct rt_thread thread_Gui;

static char thread_Key_stack[1024];
struct rt_thread thread_Key;
u32 KeyValue;



static void _cbBkWindow(WM_MESSAGE* pMsg) {
	switch (pMsg->MsgId) {
		case MSG_CHANGE_TEXT:
			strcpy(_acInfoText, pMsg->Data.p);
	  
		case WM_PAINT:
			GUI_SetBkColor(GUI_BLACK);
			GUI_Clear();
			GUI_SetColor(GUI_WHITE);
			GUI_SetFont(GUI_FONT_20_ASCII);
			GUI_DispStringHCenterAt("WindowManager - Sample", 120, 0);
			GUI_SetFont(GUI_FONT_8_ASCII);
			GUI_DispStringAt(_acInfoText, 0, 21);
			break;
			
		default:
			WM_DefaultProc(pMsg);
	}
}


static void _cbWindow1(WM_MESSAGE* pMsg) {
	int x, y;
	
	switch (pMsg->MsgId) {
		case WM_PAINT:
			GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
			GUI_SetColor(GUI_BLACK);
			GUI_SetFont(&GUI_Font20_ASCII);
			x = WM_GetWindowSizeX(pMsg->hWin);
			y = WM_GetWindowSizeY(pMsg->hWin);
			GUI_SetFont(&GUI_Font8_ASCII);
			GUI_DispStringAt("wujialing", 1, y-8);  
			GUI_DispDecAt(g_iRunTime, x-60, y-8, 10);
			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

static void _cbWindow2(WM_MESSAGE* pMsg) {
	int x, y;
	
	switch (pMsg->MsgId) {
		case WM_PAINT:
			GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
			GUI_SetColor(GUI_BLACK);
			GUI_SetFont(&GUI_Font13_ASCII);
			x = WM_GetWindowSizeX(pMsg->hWin);
			y = WM_GetWindowSizeY(pMsg->hWin);
			GUI_DispStringHCenterAt("Window 2", x / 2, y / 4);
		
			GUI_SetFont(GUI_FONT_8X15B_ASCII);
			GUI_DispHexAt(KeyValue, x-60, 0, 5);
			break;
		
		case WM_SIZE:
			WM_InvalidateWindow(_hChild);
			break;
		
		default:
			WM_DefaultProc(pMsg);
	}
}
void _ChangeInfoText(char* pStr) {
	WM_MESSAGE Message;
	
	Message.MsgId  = MSG_CHANGE_TEXT;
	Message.Data.p = pStr;
	WM_SendMessage(WM_HBKWIN, &Message);
	WM_InvalidateWindow(WM_HBKWIN);
}




rt_sem_t 		sem 	= RT_NULL;
rt_event_t 		event 	= RT_NULL;
rt_mailbox_t	mailbox = RT_NULL;
rt_mq_t			queue 	= RT_NULL;


static void rt_thread_entry_Gui(void* parameter)
{
	rt_uint32_t e;
	
	GUI_Init();
	GUI_SetBkColor(GUI_WHITE);
	GUI_Clear(); 
	
	WIDGET_SetDefaultEffect(&WIDGET_Effect_Simple);
	WM_SetCallback(WM_HBKWIN, _cbBkWindow);					/* Create windows */
//	_ChangeInfoText("WM_CreateWindow()");
	_hWindow1 = WM_CreateWindow( 3,   33, 120, 70, WM_CF_SHOW, _cbWindow1, 0);
	_hWindow2 = WM_CreateWindow( 1,  112, 238, 15, WM_CF_SHOW, _cbWindow2, 0);
	WinDialog(_hWindow1);	/* 对话框显示在窗口1上 */
    while (1) {
//		rt_sem_take(sem, RT_WAITING_FOREVER);
//		rt_event_recv(event, ((1 << 3)), RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &e);
//		rt_mb_recv(mailbox, (rt_uint32_t *)&e, RT_WAITING_FOREVER);	/* 变量中得到的是收到数据的地址 */
		rt_mq_recv(queue, &e, 4, RT_WAITING_FOREVER);				/* 队列会直接取到数据，返回到给定变量中 */				
		
		WM_MoveTo(_hWindow1,  e%100,  33);
		WM_InvalidateWindow(_hWindow2);		
		GUI_Delay(5);
    }
}

void KeyPort_init(void);
u32 Key_swap(void);

static void rt_thread_entry_Key(void* parameter)
{
	KeyPort_init();
	
    while(1) {
//		rt_sem_release(sem);
//		rt_event_send(event, (1 << 3));
//		rt_mb_send(mailbox, (rt_uint32_t)&g_iRunTime);		/* 将变量地址发送过去 */
		rt_mq_send(queue, &g_iRunTime, 4);					/* 直接将变量中的数据放到队列中 */
	
		KeyValue = Key_swap();
		LED_Tog();
		g_iRunTime+=1;
        rt_thread_delay(10);
    }
}



int rt_application_init()
{
	sem 	= rt_sem_create("sem", 0, RT_IPC_FLAG_FIFO);
	event 	= rt_event_create("event", RT_IPC_FLAG_FIFO);
	mailbox = rt_mb_create("mailbox", 1, RT_IPC_FLAG_FIFO);
	queue   = rt_mq_create("queue", 4, 20, RT_IPC_FLAG_FIFO);



    rt_thread_init(&thread_Gui,
                   "led1",
                   rt_thread_entry_Gui,
                   RT_NULL,
                   &thread_Gui_stack[0],
                   sizeof(thread_Gui_stack),11,5);
    rt_thread_startup(&thread_Gui);

	
    rt_thread_init(&thread_Key,
                   "Key",
                   rt_thread_entry_Key,
                   RT_NULL,
                   &thread_Key_stack[0],
                   sizeof(thread_Key_stack),11,5);
	
    rt_thread_startup(&thread_Key);

    return 0;
}

/*@}*/
