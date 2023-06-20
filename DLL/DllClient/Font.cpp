#include "stdafx.h"
#include "Font.h"
#include "Import.h"

cFont* gFont[100];

cFont::cFont(TCHAR* Name, int Size, int Weight, BOOL bItalic, BOOL bUnderline)
{
	//this->Font = CreateFontA(Size, 0, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 3u, 0, "Arial");
	this->m_Font = CreateFont(Size, 0, 0, 0, Weight, bItalic, bUnderline, FALSE,
		0xFDE9, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE|DEFAULT_PITCH,
		Name);

	//sub_7E3000
}