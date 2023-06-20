#include "StdAfx.h"
#include "GSLibrary.h"

#if(CUSTOM_LIBRARY)

CGSLibrary g_GSLibrary;

CGSLibrary::CGSLibrary()
{
	this->m_bHandle = NULL;
}

CGSLibrary::~CGSLibrary()
{
	if(this->m_bHandle != NULL)
	{
		FreeLibrary(this->m_bHandle);
	}
}

void CGSLibrary::Load()
{
	if(this->m_bHandle)
	{
		FreeLibrary(this->m_bHandle);
	}

	this->m_bHandle = LoadLibrary("GSLibrary.dll");

	if(!this->m_bHandle)
	{
		MessageBox(0, "GSLibrary.dll", "LOAD", 0);
		return;
	}

	this->pMessage = (void(*)())GetProcAddress(this->m_bHandle, "InjectMessage");

	this->MsgBox();
}

void CGSLibrary::MsgBox()
{
	this->pMessage();
}

#endif