#pragma once

#include "stdafx.h"

#if(ENABLE_CHAT_SMILE)

#define ENABLE_1_04_05	0

#define MAX_COUNT_SMILE	4

class CChatSmile
{
public:
		 CChatSmile();
		 ~CChatSmile();
	void Init();
	void Hook();
	void Load();
	void BindButton();
	void LoadSmile();
	void DrawButton();
	void DrawSmile(int NumIco, int X, int Y);
	void ControllerSmile(DWORD Event);

	static void _TC  RenderText(LPVOID This, int iPos_x, int iPos_y, LPCTSTR pszText, int iBoxWidth, int iBoxHeight, LPINT iSort, SIZE* lpTextSize);

	static void _CD SendChat(char *a1);
	static BYTE *_CD sub_9D04E0(BYTE *a1, char *a2, unsigned int a3);
	static int _CD sub_40BCC0(char* a1);
	static int __cdecl AddChat(int a1, char *a2, int a3);

	static void __cdecl sub_9CF3B0(char * a1, char * a2);
	static int __cdecl sub_597980(LPCSTR lpMultiByteStr, BYTE *a2, BYTE *a3, int a4);

	bool m_OpenIcon;

	DWORD	m_EventTickSmile;
	bool	m_OnClickSmile;

	char	m_TextSmile[256];
	int		m_CountSmile;
};

extern CChatSmile g_ChatSmile;

#endif