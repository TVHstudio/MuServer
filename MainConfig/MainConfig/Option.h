#pragma once
// -------------------------------------------------------------------------------
#define VERSION_SEASON_6	0
#define VERISON_SEASON_10	1
#define VERSION_ZTGAME		2
#define VERSION_SILVER		3
// -------------------------------------------------------------------------------
#define VERSION_ACTIVE		VERSION_SEASON_6
// -------------------------------------------------------------------------------


#define MAX_RESOLUTION	18

enum CMD_TYPE
{
	CMD_640x480,
	CMD_800x600,
	CMD_1024x768,
	CMD_1280x1024,
	CMD_1600x1200,
	CMD_1280x768,
	CMD_1280x800,
	CMD_1366x768,
	CMD_1440x900,
	CMD_1680x1050,
	CMD_1920x1080,
	CMD_1920x1200,
	CMD_1152x864,
	CMD_1280x960,
	CMD_1600x900,
	CMD_1024x600,
	CMD_1910x970,
	CMD_1350x650,
	CMD_WIN_MODE,
};

class COption
{
public:
		COption();
		~COption();

	void Load();
	void LoadResolution();
	void LoadMisc();
	int BindResoulution(int hMenu, char * ResText, int X, int Y);
	void CmdProc(DWORD Cmd);
	bool SetReg(LPCTSTR name, INT value);
	DWORD GetRegDword(LPCTSTR name); 
	void LoadReg();
	void SaveReg();
	void SendCmd();

	int m_ResCount;
	HWND m_hResolution[MAX_RESOLUTION];
	HWND m_hWinMode;
	HWND m_hMusic;
	HWND m_hSound;

	DWORD m_RegWindowMode;
	DWORD m_RegMusicOnOFF;
	DWORD m_RegSoundOnOFF;
	DWORD m_RegDisplayDeviceModeIndex;
};

extern COption g_Option;