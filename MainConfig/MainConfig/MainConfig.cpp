#include "stdafx.h"
#include "MainConfig.h"
#include "Option.h"

HWND g_hWnd;
HINSTANCE g_hInst;

char szTitle[] = WINDOW_TITLE;
char szWindowClass[] = WINDOW_CLASS;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	#if(ENABLE_DEBUGGER)
	g_Debugger.Load();
	#endif

	MyRegisterClass(hInstance);

	if(!InitInstance(hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	g_Option.Load();

    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);

	//g_Option.LoadReg();

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0))
	{
		//if (!TranslateAccelerator(msg.hwnd, 0, &msg))
		{
		    TranslateMessage(&msg);
		    DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

WNDCLASSEX wcex;

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	//WNDCLASSEX wcex;

	wcex.cbSize			= sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_ICON1);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)5;// hBrushDrakGray;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_ICON1);

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   g_hInst = hInstance;

   g_hWnd = CreateWindowEx(0, szWindowClass, szTitle,  
	   WS_OVERLAPPED+WS_CAPTION+WS_SYSMENU+WS_MINIMIZEBOX+WS_VISIBLE,
	   //WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZE,
       CW_USEDEFAULT, 0, 
	   WINDOW_WIDTH, WINDOW_HEIGHT, 
	   NULL, NULL, hInstance, NULL);

   if(!g_hWnd)
   {
      return FALSE;
   }

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message) 
	{
		case WM_COMMAND:
			g_Option.CmdProc(LOWORD(wParam));
			break;
		case WM_DESTROY:
			PostQuitMessage (0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }

   return FALSE;
}