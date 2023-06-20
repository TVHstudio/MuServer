#include "stdafx.h"
#include "Import.h"
#include "CustomFontZt.h"
#include "Interface.h"

//#include "UltraDebuger.h"

#if(ENABLE_CUSTOMFONTZT)

#define pSetBackgroundTextColor	((void(__thiscall*)(LPVOID This, int r, int g, int b, int h)) 0x004200B0)
#define pSetTextSize			((int(__thiscall*)(LPVOID This, HFONT a2)) 0x00420120)
#define pSetTextFont			((int(__thiscall*)(LPVOID This, HFONT a2)) 0x00420120)
#define pSetTextColorZt			((void(__thiscall*)(LPVOID This, BYTE r, BYTE g, BYTE b, BYTE h)) 0x00420040)

CCustomFontZt g_CustomFontZt;

CCustomFontZt::CCustomFontZt()
{
	this->load();
}

CCustomFontZt::~CCustomFontZt()
{
}

void CCustomFontZt::load() 
{
	DWORD Width = 0;
	DWORD Italic = 0;
	DWORD UnderLine = 0;
	DWORD StrikeOut = 0;
	DWORD Quality = 3;

	this->FontNormal = CreateFontA(13, Width, 0, 0, 400, Italic, UnderLine, StrikeOut, 0x1, 0, 0, Quality, 0, "Tahoma");
	this->FontBold   = CreateFontA(13, Width, 0, 0, 700, Italic, UnderLine, StrikeOut, 0x1, 0, 0, Quality, 0, "Tahoma");
	this->FontBoldBG   = CreateFontA(13, Width, 0, 0, 400, Italic, UnderLine, StrikeOut, 0x1, 0, 0, Quality, 0, "Tahoma");
	this->FontSize15 = CreateFontA(15, Width, 0, 0, 400, Italic, UnderLine, StrikeOut, 0x1, 0, 0, Quality, 0, "Tahoma");
	this->FontSize18 = CreateFontA(18, Width, 0, 0, 800, Italic, UnderLine, StrikeOut, 0x1, 0, 0, Quality, 0, "Tahoma");
	//this->FontSize18 = CreateFontA(24, Width, 0, 0, 800, Italic, UnderLine, StrikeOut, 0x1, 0, 0, Quality, 0, "Tahoma");

}

eColor CCustomFontZt::SinWaveColor(float frc1, float frc2, float frc3, BYTE phs1, BYTE phs2, BYTE phs3, BYTE center, BYTE width, BYTE step) 
{
	eColor result;

	result.red = std::sin(frc1 * step + phs1) * width + center;
	result.grn = std::sin(frc2 * step + phs2) * width + center;
	result.blu = std::sin(frc3 * step + phs3) * width + center;
	result.opl = 0xff;

	return result;
}

void CCustomFontZt::Draw(HFONT font, int PosX, int PosY, DWORD color, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...) 
{
	char Buff[2048];
	int BuffLen = sizeof(Buff)-1;
	ZeroMemory(Buff, BuffLen);

	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);

	int LineCount = 0;

	char * Line = strtok(Buff, "\n");

	while (Line != NULL)
	{
		pSetTextSize(pTextThis(), font);
		//pSetTextColor(pTextThis(), (color & 0xff000000) >> 24, (color & 0x00ff0000) >> 16, (color & 0x0000ff00) >> 8, color & 0x000000ff);
		pSetTextColorZt(pTextThis(), (color & 0xff000000) >> 24, (color & 0x00ff0000) >> 16, (color & 0x0000ff00) >> 8, color & 0x000000ff);
		pSetBackgroundTextColor(pTextThis(), (bkcolor & 0xff000000) >> 24, (bkcolor & 0x00ff0000) >> 16, (bkcolor & 0x0000ff00) >> 8, bkcolor & 0x000000ff);
		pDrawText(pTextThis(), PosX, PosY, Line, Width, Height, (LPINT)Align, 0);
		PosY += 10;
		Line = strtok(NULL, "\n");
	}
}

void CCustomFontZt::DrawZt(HFONT font, int PosX, int PosY, DWORD color, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...) 
{
	char Buff[2048];
	int BuffLen = sizeof(Buff)-1;
	ZeroMemory(Buff, BuffLen);

	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);

	int LineCount = 0;

	char * Line = strtok(Buff, "\n");

	/*
		CFont font;

	font.CreatePointFont(920, "Garamond");
	CFont *pFont = pDC->SelectObject(&font);

	pDC->SetBkMode(TRANSPARENT);	<<<<<<<<<<<<
	
	pDC->SetTextColor(RGB(110, 185, 250));
	pDC->TextOut(26, 24, "Christine", 9);

	pDC->SetTextColor(RGB(0, 0, 255));	<<<<<<<<<<<<
	pDC->TextOut(20, 18, "Christine", 9);	<<<<<<<<<<<<

	pDC->SelectObject(pFont);
	font.DeleteObject();
	*/

	while (Line != NULL)
	{
		pSetTextSize(pTextThis(), font);

		//SetBkMode((HDC)pTextThis(), TRANSPARENT);

		pSetTextColorZt(pTextThis(), (bkcolor & 0xff000000) >> 24, (bkcolor & 0x00ff0000) >> 16, (bkcolor & 0x0000ff00) >> 8, bkcolor & 0x000000ff);
		pDrawText(pTextThis(), (float)PosX + 0.5, (float)PosY + 0.5, Line, Width, Height, (LPINT)Align, 0);

		pSetTextColorZt(pTextThis(), (color & 0xff000000) >> 24, (color & 0x00ff0000) >> 16, (color & 0x0000ff00) >> 8, color & 0x000000ff);
		pDrawText(pTextThis(), PosX, PosY, Line, Width, Height, (LPINT)Align, 0);




	
		/*
		pSetTextSize(pTextThis(), font);
		SetBkMode((HDC)pTextThis(), TRANSPARENT);
		pSetTextColorZt(pTextThis(), (color & 0xff000000) >> 24, (color & 0x00ff0000) >> 16, (color & 0x0000ff00) >> 8, color & 0x000000ff);
		pSetBackgroundTextColor(pTextThis(), (bkcolor & 0xff000000) >> 24, (bkcolor & 0x00ff0000) >> 16, (bkcolor & 0x0000ff00) >> 8, bkcolor & 0x000000ff);
		pDrawText(pTextThis(), PosX, PosY, Line, Width, Height, (LPINT)Align, 0);
		*/


		PosY += 10;
		Line = strtok(NULL, "\n");

	}
}

void CCustomFontZt::DrawMultipleColor(HFONT font, int PosX, int PosY, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...) 
{
	char Buff[2048];
	int BuffLen = sizeof(Buff)-1;
	ZeroMemory(Buff, BuffLen);

	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);

	int LineCount = 0;

	char * Line = strtok(Buff, "\n");
	BYTE len = strlen(Line);

	char filter[10];
	char bufer[255];
	while (Line != NULL)
	{
		pSetTextSize(pTextThis(), font);

		pSetBackgroundTextColor(pTextThis(), (bkcolor & 0xff000000) >> 24, (bkcolor & 0x00ff0000) >> 16, (bkcolor & 0x0000ff00) >> 8, bkcolor & 0x000000ff);

		for (BYTE i = 0; i < len; i++) 
		{
			eColor mColor = g_CustomFontZt.SinWaveColor(0.1f, 0.1f, 0.1f, 0, 2, 4, 128, 127, i + GetTickCount() / 100 % 255);

			/*
			eColor mColor = g_CustomFontZt.SinWaveColor(
				g_UltraDebuger.GetNumber(eULTRA_1, 0.1), 
				g_UltraDebuger.GetNumber(eULTRA_2, 0.1), 
				g_UltraDebuger.GetNumber(eULTRA_3, 0.1), 
				(BYTE)g_UltraDebuger.GetNumber(eULTRA_4, 10), 
				(BYTE)g_UltraDebuger.GetNumber(eULTRA_5, 10), 
				(BYTE)g_UltraDebuger.GetNumber(eULTRA_6, 10),
				(BYTE)g_UltraDebuger.GetNumber(eULTRA_7, 10),
				(BYTE)g_UltraDebuger.GetNumber(eULTRA_8, 10),
				(BYTE)g_UltraDebuger.GetNumber(eULTRA_9, 10)
				);
			*/

			//pSetTextColor(pTextThis(), mColor.red, mColor.grn, mColor.blu, mColor.opl);
			pSetTextColorZt(pTextThis(), mColor.red, mColor.grn, mColor.blu, mColor.opl);
			sprintf(filter, "%%.%ds", len - i);
			sprintf(bufer, filter, Line);
			pDrawText(pTextThis(), PosX, PosY, bufer, Width, Height, (LPINT)Align, 0);
		}
		PosY += 10;
		Line = strtok(NULL, "\n");
	}
}

void CCustomFontZt::DrawMultipleColorZt(HFONT font, int PosX, int PosY, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...) 
{
	char Buff[2048];
	int BuffLen = sizeof(Buff)-1;
	ZeroMemory(Buff, BuffLen);

	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);

	int LineCount = 0;

	char * Line = strtok(Buff, "\n");
	BYTE len = strlen(Line);

	char filter[10];
	char bufer[255];

	while (Line != NULL)
	{
		pSetTextSize(pTextThis(), font);

		pSetBackgroundTextColor(pTextThis(), (bkcolor & 0xff000000) >> 24, (bkcolor & 0x00ff0000) >> 16, (bkcolor & 0x0000ff00) >> 8, bkcolor & 0x000000ff);

		for (BYTE i = 0; i < len; i++) 
		{
			//eColor mColor = CustomFont.SinWaveColor(0.1f, 0.1f, 0.1f, 0, 2, 4, 128, 127, i + GetTickCount() / 100 % 255);
			//eColor mColor = CustomFont.SinWaveColor(0.1f, 0.1f, 0.1f, 0, 2, 4, 50, 255, 255);
			//eColor mColor = CustomFont.SinWaveColor(0.1f, 0.1f, 0.1f, i + GetTickCount() / 100 % 255, 2, 4, 128, 128, 128);
			eColor mColor = g_CustomFontZt.SinWaveColor(1.0f, 1.0f, 1.0f, 0, 2, 4, 128, 128, 128);

			//pSetTextColor(pTextThis(), mColor.red, mColor.grn, mColor.blu, mColor.opl);

			pSetTextColorZt(pTextThis(), mColor.red, mColor.grn, mColor.blu, mColor.opl);
			sprintf(filter, "%%.%ds", len - i);
			sprintf(bufer, filter, Line);
			pDrawText(pTextThis(), PosX, PosY, bufer, Width, Height, (LPINT)Align, 0);
		}

		PosY += 10;
		Line = strtok(NULL, "\n");
	}
}

void CCustomFontZt::Draw2(HFONT font, int PosX, int PosY, DWORD color, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...) 
{
	char Buff[2048];
	int BuffLen = sizeof(Buff)-1;
	ZeroMemory(Buff, BuffLen);

	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);

	int LineCount = 0;

	char * Line = strtok(Buff, "\n");

	while (Line != NULL)
	{
		pSetTextSize(pTextThis(), font);
		//pSetTextColor(pTextThis(), (color & 0xff000000) >> 24, (color & 0x00ff0000) >> 16, (color & 0x0000ff00) >> 8, color & 0x000000ff);
		pSetTextColorZt(pTextThis(), (color & 0xff000000) >> 24, (color & 0x00ff0000) >> 16, (color & 0x0000ff00) >> 8, color & 0x000000ff);
		pSetBackgroundTextColor(pTextThis(), (bkcolor & 0xff000000) >> 24, (bkcolor & 0x00ff0000) >> 16, (bkcolor & 0x0000ff00) >> 8, bkcolor & 0x000000ff);
		pDrawText(pTextThis(), PosX, PosY, Line, Width, Height, (LPINT)Align, 0);
		PosY += 10;
		Line = strtok(NULL, "\n");
	}
}

#endif