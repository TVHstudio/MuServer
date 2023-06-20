#pragma once
// ----------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "Protocol.h"

#if(CUSTOM_ZT_TELEPORT==TRUE)
// ----------------------------------------------------------------------------------------------

#define MAXZTTELEPORT	10
// ----------------------------------------------------------------------------------------------

struct ZtTeleportData
{
	BYTE result;
	BYTE map;
	BYTE x;
	BYTE y;
	WORD level;
	BYTE ok_level;
	WORD reset;
	BYTE ok_reset;
	WORD grand;
	BYTE ok_grand;
	BYTE premium;
	BYTE ok_premium;
	DWORD zen;
	BYTE ok_zen;
	WORD bonus;
	BYTE ok_bonus;
	WORD credit;
	BYTE ok_credit;
	BYTE Master;
	BYTE ok_Master;
};
// ----------------------------------------------------------------------------------------------

struct PMSG_GC_TELEPORTWIN
{
	PWMSG_HEAD2	h;
	BYTE count;
	ZtTeleportData tdata[MAXZTTELEPORT];
};
// ----------------------------------------------------------------------------------------------

struct PMSG_CG_TELEPORTWINRES
{
	PBMSG_HEAD2	h;
	BYTE result;
};
// ----------------------------------------------------------------------------------------------

struct ZtTeleportDATA
{
	BYTE result;
	BYTE map;
	BYTE x;
	BYTE y;
	WORD level;
	BYTE ok_level;
	WORD reset;
	BYTE ok_reset;
	WORD grand;
	BYTE ok_grand;
	BYTE premium;
	BYTE ok_premium;
	DWORD zen;
	BYTE ok_zen;
	WORD bonus;
	BYTE ok_bonus;
	WORD credit;
	BYTE ok_credit;
	BYTE Master;
	BYTE ok_Master;
};
// ----------------------------------------------------------------------------------------------

class ZtTeleport
{
public:
	ZtTeleport();
	~ZtTeleport();
	void Init();
	void Load();

	void LoadImages();
	void BindImages();
	void Draw();

	void GCWindows(PMSG_GC_TELEPORTWIN* aRecv);
	void CGResult(BYTE num);
	void Button(DWORD Event);
	void SpeedCalc(int number, int &countplus);
	char* ActiveText(int status);
	int ClickPage;
	int LenCount;

	ZtTeleportDATA data[MAXZTTELEPORT];
	int iLoadedCount;
};
// ----------------------------------------------------------------------------------------------
extern ZtTeleport g_ZtTeleport;
// ----------------------------------------------------------------------------------------------

#endif