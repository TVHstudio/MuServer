#pragma once

#if(CUSTOM_ZTTEXT)

#define MAX_ZTTEXT	500

class CZtText
{
public:
		CZtText();
		~CZtText();

	void Init();
	void Load();
	void Read(char* filename);

	char* GetText(int number);

	char m_Text[MAX_ZTTEXT][128];
};

extern CZtText g_ZtText;

#endif