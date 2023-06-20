#include "StdAfx.h"
#include "DSProtocol.h"
#include "protocol.h"
#include "user.h"
#include "PartyClass.h"

struct ZTINFO_UPDATE
{
	PBMSG_HEAD2 h;
	int PremiumTime;
	int Chaos;
	int Bless;
	int Soul;
	int Life;
	float ZtCred;
	int Zen;
	int WCoinC;
	int WCoinP;
	int WCoinG;
	int CreateonBank;
	int PremiumType;
	int DonateCredit;
	int GuardianBank;
	int HarmonyBank;
	int LowStoneBank;
	int HighStoneBank;
	int GemStoneBank;
	int PCPoint;
};

struct GC_RESET_CHAR_UPDATE
{
	PBMSG_HEAD2	h;
	WORD Level;
	DWORD Exp;
	DWORD MaxExp;
	WORD Str;
	WORD Agi;
	WORD Vit;
	WORD Ene;
	WORD Cmd;
	DWORD UpPoint;
	WORD Reset;
	WORD Grand;
};
// ------------------------------------------------------------------------------

void ZtUserDataSend(int aIndex);
void ZtUserVieweport(int aIndex);
void ResetSystemGC_CharUpdate(LPOBJ lpUser);
bool ZtUserInSafeZone(int aIndex);
// -------------------------------------------------------------------------------

#if(CUSTOM_ADD_POINTS==TRUE)
struct PMSG_ADD_POINTS
{
	PBMSG_HEAD2 h;
	WORD Strength;
	WORD Dexterity;
	WORD Vitality;
	WORD Energy;
	WORD Leadership;
};
#endif

struct PMSG_ADD_POINTSRESET
{
	PBMSG_HEAD2 h;
	bool Result;
};

struct GC_RESET_POINT_CFG
{
	PBMSG_HEAD2 h;
	int iResetStatsPriceBonus;
	int iResetStatsPriceCredit;
};

#if(CUSTOM_SERVER_TIME)
struct PMSG_SERVER_TIME
{
	PBMSG_HEAD2 h;
    WORD Hour;
    WORD Minute;
    WORD Second;
};
#endif

struct PARTY_MAP_DATA
{
	char Name[10];
	BYTE Map;
	BYTE X;
	BYTE Y;
};

struct PMSG_PARTY_MINIMAP
{
	PBMSG_HEAD2 h;
	int Count;
	PARTY_MAP_DATA Data[MAX_USER_IN_PARTY];
};

struct PMSG_CONTROLLER_CTRL
{
	PBMSG_HEAD2 h;
	BYTE CtrlKey;
};


struct CG_MINIMAP_PARTY
{
	PBMSG_HEAD2 h;
	BYTE MiniMap;
};

#if(DEV_PLAYERINFO)
struct INFOPLAYER_DATA
{
	int aIndex;
	WORD Strength;
	WORD Agility;
	WORD Vitality;
	WORD Energy;
	WORD Command;
	WORD Reset;
	WORD GReset;
	WORD PKLevel;
	BYTE Vip;
};

struct PMSG_REQ_INFOPLAYER
{
	PBMSG_HEAD2 h;
	int aIndex;
};

struct PMSG_ANS_INFOPLAYER
{
	PBMSG_HEAD2 h;
	INFOPLAYER_DATA Data;
};
#endif

#if(DEV_DAMAGE_TABLE)
struct PMSG_DAMAGE_TABLE
{
	PBMSG_HEAD2 h;
	int SecondDamage;
	int SecondDefence;
	int SecondReflect;
};
#endif

#if(CUSTOM_VALUE_MENU)

struct PMSG_REQ_VALUE_MENU
{
	PBMSG_HEAD2 h;
	int ValueOpen;
};

struct PMSG_ANS_VALUE_MENU
{
	PBMSG_HEAD2 h;
	int ValueOpen;
	int ValueNumber;
};

#endif

#if(FIX_VIEWE_MONSTER)

struct PMSG_REQ_REVIEWE
{
	PBMSG_HEAD2 h;
	int TargetAttackIndex;
	int TargetAttackCount;
};

#endif

#if(ENABLR_DEN_DEV)

struct MINIMAP_SPOT_DATA
{
	BYTE X;
	BYTE Y;
};

struct MINIMAP_SPOT_SEND
{
	PWMSG_HEAD2 h;
	int Count;
	MINIMAP_SPOT_DATA Spot[300];
};

#endif

class ZtUser
{
public:
	ZtUser();
	~ZtUser();
	void Load();
	bool InSafeZone(int aIndex);
	bool CheckAlliancePlayer(int aIndex, int aTarget);

	void GCDataClient(int aIndex);

#if(CUSTOM_ADD_POINTS==TRUE)
	void CGAddPoints(int aIndex, PMSG_ADD_POINTS* aRecv);
	void CGResetPoints(int aIndex, PMSG_ADD_POINTSRESET* aRecv);
	void ResetPointsLoad();
	void ResetPointSend(int aIndex);
	int ResetStatsPriceWCoin;
	int ResetStatsPriceCredit;
#endif
#if(CUSTOM_SERVER_TIME)
	void GCServerTime();
#endif

	void TickCountClientDataSend();
	void AutoHPClick();
	void CG_RecvAutoHPClicker(PMSG_PROTOCOL_RESULT* lpMsg, int aIndex);
	bool m_bActiveAutoHP;

	void PlayerKillInfoMail(int aIndex, int aTargetIndex);

	void PartyMiniMapInfo();
#if(ADD_CTRL_KEY)
	void CGCtrlKey(int aIndex, PMSG_CONTROLLER_CTRL* aRecv);
#endif
	void RecvConfig(CG_MINIMAP_PARTY* lpMsg, int aIndex);
	#if(DEV_PLAYERINFO)
	bool EnableInfoPlayer;
	void RecvInfoPlayer(PMSG_REQ_INFOPLAYER* lpMsg, int aIndex);
	#endif
	#if(DEV_DAMAGE_TABLE)
	bool EnableTable;
	void ResetDamageTable();
	void GCDamageTable(int aIndex);
	#endif
	#if(CUSTOM_VALUE_MENU)
	bool GCSendValueMenu(int aIndex, int Type);
	void CGRecvValueMenu(PMSG_ANS_VALUE_MENU* lpMsg, int aIndex);
	#endif
	int GetGuildMemberOnline(int GuildNumber);
	#if(FIX_VIEWE_MONSTER)
	void CGReqReViewe(PMSG_REQ_REVIEWE* lpMsg, int aIndex);
	#endif
#if(ENABLR_DEN_DEV)
	void MiniMapSpotProc(int aIndex);


#endif
};
extern ZtUser g_ZtUser;
// -------------------------------------------------------------------------------