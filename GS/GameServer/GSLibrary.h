#pragma once

#if(CUSTOM_LIBRARY)

class CGSLibrary
{
public:
		 CGSLibrary();
		 ~CGSLibrary();

	void Load();
	void MsgBox();

	HINSTANCE m_bHandle;

	void (*pMessage)();
};

extern CGSLibrary g_GSLibrary;

#endif