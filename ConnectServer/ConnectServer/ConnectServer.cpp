#include "stdafx.h"
#include "ConnectServer.h"
#include "Window.h"
#include "zTWindow.h"
// -----------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return g_WindowZt.ProcessMain(hWnd, uMsg, wParam, lParam);
}
// -----------------------------------------------------------------------

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#if(ENABLE_NEW_WINDOW)
	g_WindowZt.CreateMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
#else
    g_Window.InitInstance(hInstance);
#endif

    return 0;
}
// -----------------------------------------------------------------------