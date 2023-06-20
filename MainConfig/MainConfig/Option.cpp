#include "stdafx.h"
#include "MainConfig.h"
#include "Option.h"

COption g_Option;

COption::COption()
{
	this->m_RegWindowMode = 0;
	this->m_RegMusicOnOFF = 0;
	this->m_RegSoundOnOFF = 0;
	this->m_RegDisplayDeviceModeIndex = 0;
}

COption::~COption()
{
}

void COption::Load()
{
	this->LoadResolution();
	this->LoadMisc();
	this->LoadReg();
	this->SendCmd();
}

void COption::LoadResolution()
{
	this->m_ResCount = 0;
	int X = 40;
	int Y = 70;

	//CreateWindowExA(0, "BUTTON", "Window", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, X-10, Y, 130, 230, g_hWnd, NULL, 0, 0);
	CreateWindowExA(0, "BUTTON", "Window", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, X-10, Y, 130, 390, g_hWnd, NULL, 0, 0);
	Y += 20;


	Y = this->BindResoulution(CMD_640x480, "640x480", X, Y);
	Y = this->BindResoulution(CMD_800x600, "800x600", X, Y);
	Y = this->BindResoulution(CMD_1024x768, "1024x768", X, Y);
	Y = this->BindResoulution(CMD_1280x1024, "1280x1024", X, Y);
	Y = this->BindResoulution(CMD_1600x1200, "1600x1200", X, Y);
	Y = this->BindResoulution(CMD_1280x768, "1280x768", X, Y);
	Y = this->BindResoulution(CMD_1280x800, "1280x800", X, Y);
	Y = this->BindResoulution(CMD_1366x768, "1366x768", X, Y);
	Y = this->BindResoulution(CMD_1440x900, "1440x900", X, Y);
	Y = this->BindResoulution(CMD_1680x1050, "1680x1050", X, Y);
	Y = this->BindResoulution(CMD_1920x1080, "1920x1080", X, Y);
	Y = this->BindResoulution(CMD_1920x1200, "1920x1200", X, Y);
	Y = this->BindResoulution(CMD_1152x864, "1152x864", X, Y);
	Y = this->BindResoulution(CMD_1280x960, "1280x960", X, Y);
	Y = this->BindResoulution(CMD_1600x900, "1600x900", X, Y);
	Y = this->BindResoulution(CMD_1024x600, "1024x600", X, Y);
	Y = this->BindResoulution(CMD_1910x970, "1910x970", X, Y);
	Y = this->BindResoulution(CMD_1350x650, "1350x650", X, Y);

	/*
	this->m_hResolution[this->m_ResCount] = CreateWindowExA(0, "BUTTON", "800x600", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, X, Y, 100, 20, g_hWnd, (HMENU)CMD_800x600, 0, 0);
	this->m_ResCount++;
	Y += 20;

	this->m_hResolution[this->m_ResCount] = CreateWindowExA(0, "BUTTON", "1024x768", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, X, Y, 100, 20, g_hWnd, (HMENU)CMD_1024x768, 0, 0);
	this->m_ResCount++;
	Y += 20;

	this->m_hResolution[this->m_ResCount] = CreateWindowExA(0, "BUTTON", "1152x864", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, X, Y, 100, 20, g_hWnd, (HMENU)CMD_1152x864, 0, 0);
	this->m_ResCount++;
	Y += 20;

	this->m_hResolution[this->m_ResCount] = CreateWindowExA(0, "BUTTON", "1280x720", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, X, Y, 100, 20, g_hWnd, (HMENU)CMD_1280x720, 0, 0);
	this->m_ResCount++;
	Y += 20;

	this->m_hResolution[this->m_ResCount] = CreateWindowExA(0, "BUTTON", "1280x960", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, X, Y, 100, 20, g_hWnd, (HMENU)CMD_1280x800, 0, 0);
	this->m_ResCount++;
	Y += 20;

	this->m_hResolution[this->m_ResCount] = CreateWindowExA(0, "BUTTON", "1366x768", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, X, Y, 100, 20, g_hWnd, (HMENU)CMD_1280x960, 0, 0);
	this->m_ResCount++;
	Y += 20;

	this->m_hResolution[this->m_ResCount] = CreateWindowExA(0, "BUTTON", "1600x900", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, X, Y, 100, 20, g_hWnd, (HMENU)CMD_1600x900, 0, 0);
	this->m_ResCount++;
	Y += 20;

	this->m_hResolution[this->m_ResCount] = CreateWindowExA(0, "BUTTON", "1600x1200", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, X, Y, 100, 20, g_hWnd, (HMENU)CMD_1600x1200, 0, 0);
	this->m_ResCount++;
	Y += 20;

	this->m_hResolution[this->m_ResCount] = CreateWindowExA(0, "BUTTON", "1680x1050", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, X, Y, 100, 20, g_hWnd, (HMENU)CMD_1680x1050, 0, 0);
	this->m_ResCount++;
	Y += 20;

	this->m_hResolution[this->m_ResCount] = CreateWindowExA(0, "BUTTON", "1920x1080", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, X, Y, 100, 20, g_hWnd, (HMENU)CMD_1920x1080, 0, 0);
	this->m_ResCount++;
	Y += 20;
	*/
}

void COption::LoadMisc()
{
	int X = 40;
	int Y = 10;

	CreateWindowExA(0, "BUTTON", "Misc", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, X-10, Y, 130, 50, g_hWnd, NULL, 0, 0);
	Y += 20;

	this->m_hWinMode = CreateWindowExA(0, "BUTTON", "Window mode", WS_CHILD | WS_VISIBLE | BS_CHECKBOX, X, Y, 110, 20, g_hWnd, (HMENU)CMD_WIN_MODE, g_hInst, 0);
	Y += 20;
}

void COption::CmdProc(DWORD Cmd)
{
	switch(Cmd)
	{
	case CMD_640x480:	this->m_RegDisplayDeviceModeIndex = 0;	break;
	case CMD_800x600:	this->m_RegDisplayDeviceModeIndex = 1;	break;
	case CMD_1024x768:	this->m_RegDisplayDeviceModeIndex = 2;	break;
	case CMD_1280x1024: this->m_RegDisplayDeviceModeIndex = 3;	break;
	case CMD_1600x1200:	this->m_RegDisplayDeviceModeIndex = 4;	break;

	case CMD_1280x768:	this->m_RegDisplayDeviceModeIndex = 5;	break;
	case CMD_1280x800:	this->m_RegDisplayDeviceModeIndex = 6;	break;
	case CMD_1366x768:	this->m_RegDisplayDeviceModeIndex = 7;	break;
	case CMD_1440x900:	this->m_RegDisplayDeviceModeIndex = 8;	break;
	case CMD_1680x1050:	this->m_RegDisplayDeviceModeIndex = 9;	break;
	case CMD_1920x1080:	this->m_RegDisplayDeviceModeIndex = 10;	break;
	case CMD_1920x1200:	this->m_RegDisplayDeviceModeIndex = 11;	break;

	case CMD_1152x864:	this->m_RegDisplayDeviceModeIndex = 12;	break;
	case CMD_1280x960:	this->m_RegDisplayDeviceModeIndex = 13;	break;
	case CMD_1600x900:	this->m_RegDisplayDeviceModeIndex = 14;	break;
	case CMD_1024x600:	this->m_RegDisplayDeviceModeIndex = 15;	break;
	case CMD_1910x970:	this->m_RegDisplayDeviceModeIndex = 16;	break;
	case CMD_1350x650:	this->m_RegDisplayDeviceModeIndex = 17;	break;

	case CMD_WIN_MODE:	
		this->m_RegWindowMode = !this->m_RegWindowMode;	
			break;
	}

	this->SendCmd();
	this->SaveReg();
}

int COption::BindResoulution(int hMenu, char* ResText, int X, int Y)
{
	this->m_hResolution[this->m_ResCount] = CreateWindowExA(0, "BUTTON", ResText, WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, X, Y, 100, 20, g_hWnd, (HMENU)hMenu, 0, 0);
	this->m_ResCount++;
	Y += 20;

	return Y;
}

bool COption::SetReg(LPCTSTR name, INT value)
{
	HKEY hkey;
	bool ret = FALSE;

	if (RegCreateKeyA(HKEY_CURRENT_USER, "SOFTWARE\\Webzen\\Mu\\Config", &hkey)!=ERROR_SUCCESS)
		return ret;

	if (RegSetValueExA(hkey, name, 0, REG_DWORD, (const BYTE*)&value, sizeof(INT))==ERROR_SUCCESS)
		ret = TRUE;

	RegCloseKey(hkey);

	return ret;
}

DWORD COption::GetRegDword(LPCTSTR name)
{
	DWORD Result = 0;
	int cbData = 4;
	HKEY hKey;
	DWORD dwDisposition;

	if(!RegCreateKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Webzen\\Mu\\Config", 0, 0, 0, 0xF003F, 0, &hKey, (LPDWORD)&dwDisposition))
	{
		if(RegQueryValueExA(hKey, name, 0, 0, (LPBYTE)&Result, (LPDWORD)&cbData))
		{
			 
		}
	}

	 RegCloseKey(hKey);


	 return Result;
}

void COption::LoadReg()
{
	this->m_RegWindowMode = this->GetRegDword("WindowMode");
	//this->m_RegMusicOnOFF = this->GetRegDword("MusicOnOFF");
	//this->m_RegSoundOnOFF = this->GetRegDword("SoundOnOFF");
	this->m_RegDisplayDeviceModeIndex = this->GetRegDword("Resolution");
}

void COption::SaveReg()
{
	this->SetReg("WindowMode", this->m_RegWindowMode);
	//this->SetReg("MusicOnOFF", this->m_RegMusicOnOFF);
	//this->SetReg("SoundOnOFF", this->m_RegSoundOnOFF);
	this->SetReg("Resolution", this->m_RegDisplayDeviceModeIndex);
}

void COption::SendCmd()
{
	SendMessage(this->m_hWinMode, VK_OEM_FINISH, this->m_RegWindowMode, 0);
	SendMessage(this->m_hMusic, VK_OEM_FINISH, this->m_RegMusicOnOFF, 0);
	SendMessage(this->m_hSound, VK_OEM_FINISH, this->m_RegSoundOnOFF, 0);

	for(int i = 0; i < this->m_ResCount; i++)
	{
		if(this->m_RegDisplayDeviceModeIndex == i)
		{
			SendMessage(this->m_hResolution[i], VK_OEM_FINISH, TRUE, 0);
		}
		else
		{
			SendMessage(this->m_hResolution[i], VK_OEM_FINISH, FALSE, 0);
		}
	}
}