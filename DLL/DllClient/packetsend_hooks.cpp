#include "stdafx.h"
#include "packetsend_hooks.h"
//#include "utils.h"
#include "ServerInfo.h"
#include "protocol.h"
//#include "ReconnectSystem.h"

#if(ENABLE_INDEV_NETWORK)

BYTE jmp[6] = { 0xe9,0x00, 0x00, 0x00, 0x00 ,0xc3 };  
DWORD pPrevious;

DWORD HookFunction(LPCSTR lpModule, LPCSTR lpFuncName, LPVOID lpFunction, unsigned char *lpBackup)
{  
      DWORD dwAddr = (DWORD)GetProcAddress(GetModuleHandle(lpModule), lpFuncName);
      ReadProcessMemory(GetCurrentProcess(), (LPVOID)dwAddr, lpBackup, 6, 0);
      DWORD dwCalc = ((DWORD)lpFunction - dwAddr - 5);

      VirtualProtect((void*) dwAddr, 6, PAGE_EXECUTE_READWRITE, &pPrevious);
      memcpy(&jmp[1], &dwCalc, 4);
      WriteProcessMemory(GetCurrentProcess(), (LPVOID)dwAddr, jmp, 6, 0);
      VirtualProtect((void*) dwAddr, 6, pPrevious, &pPrevious);
      FlushInstructionCache(GetCurrentProcess(),0,0);
      return dwAddr;
}   

BOOL UnHookFunction(LPCSTR lpModule, LPCSTR lpFuncName, unsigned char *lpBackup)
{
	DWORD dwAddr = (DWORD)GetProcAddress(GetModuleHandle(lpModule), lpFuncName);

	if (WriteProcessMemory(GetCurrentProcess(), (LPVOID)dwAddr, lpBackup, 6, 0))
        return TRUE;
        FlushInstructionCache(GetCurrentProcess(),0,0);
	return FALSE;  
}

// ------------------------------------------------------------------------------
struct PMSG_PIDSEND
{
	PBMSG_HEAD h; // C1 : F4 
	BYTE subcode; // 3D
	DWORD pid;
};

BYTE bServer[6];

BYTE hook[6];
CRITICAL_SECTION nSend_criti;
int __stdcall nSend(SOCKET s, const char *buf, int len,int flags){
	EnterCriticalSection(&nSend_criti);
	UnHookFunction("ws2_32.dll", "send", hook);

	int result;
	int hc = buf[0]&0xFF;
	int proto = buf[2]&0xFF;
	int subproto = buf[3]&0xFF;
	int sz = buf[1] & 0xFF;
	if(hc == 0xC1 || hc == 0xC3)
	{
		if (proto == 0xF4 && hc == 0xC1)
		{ 
			//if (g_ServerInfo->GetLauncher())
			{
				PMSG_PIDSEND pMsg;
				pMsg.h.c = 0xC1;
				pMsg.h.headcode = 0xF4;
				pMsg.h.size = sizeof(pMsg);
				pMsg.subcode = 0x3D;
				pMsg.pid = GetCurrentProcessId();
				send(s,(const char*)&pMsg,sizeof(pMsg),flags);
			}
			//if (proto == 0xF4 && hc == 0xC1 && sz == 0x06 && subproto == 0x03)
			//{
			//	memcpy(bServer, buf, buf[1]);
			//}
			result = send(s,buf,len,flags);
		}
		else {
			result = send(s, buf, len, flags);
		}
	}
	
	else if (hc == 0xC2 || hc == 0xC4)
	{
		result = send(s, buf, len, flags);
	}
	
	// result = send(s,buf,len,flags);
	HookFunction("ws2_32.dll", "send", (LPVOID) nSend, hook);
	LeaveCriticalSection(&nSend_criti);
	return result;
} 

void HookPacketSend()
{
	HookFunction("ws2_32.dll", "send", (LPVOID) nSend, hook);
}

#endif