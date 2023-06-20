#pragma once

#if(ENABLE_CUSTOMFONTZT)

struct eColor 
{
	BYTE red;
	BYTE grn;
	BYTE blu;
	BYTE opl;
};

class CCustomFontZt
{
public:
	CCustomFontZt();
	~CCustomFontZt();

	void load();

	eColor	SinWaveColor(float frc1, float frc2, float frc3, BYTE phs1, BYTE phs2, BYTE phs3, BYTE center, BYTE width, BYTE step);
	void Draw(HFONT font, int PosX, int PosY, DWORD color, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...);
	void DrawZt(HFONT font, int PosX, int PosY, DWORD color, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...);
	
	void DrawMultipleColor(HFONT font, int PosX, int PosY, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...);
	void DrawMultipleColorZt(HFONT font, int PosX, int PosY, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...);

	void Draw2(HFONT font, int PosX, int PosY, DWORD color, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...);
	
	

	HFONT	FontNormal;
	HFONT	FontBold;
	HFONT	FontBoldBG;
	HFONT	FontSize15;
	HFONT	FontSize18;
};

extern CCustomFontZt g_CustomFontZt;


#endif