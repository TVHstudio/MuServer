// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Dataserver.h"

#include "MainFrm.h"
#include "ServerPrc.h"
#include "WZIPCheck.h"
#include "BadSyntaxChk.h"
#include "MapServerManager_DS.h"
#include "RankingDBSet.h"
#include "SpotReturn.h"
#include "ZtGDManager.h"
#include "Marriage.h"
#include "DungeonSiege.h"
#include "OfflineMode.h"
#include "ZtWebManager.h"
#include "AccountSecurity.h"
#include "ReferralSystem.h"
#include "SocketManager.h"
#include "BanSystem.h"
#include "GuildBank.h"
#include "MultiChar.h"
#include "ItemMarket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char szVersion[] = DATASERVER_VERSION;

CActiveMng cAM;

char szKorSkillTextFileName[256];
char szKorItemTextFileName[256];
char szSkillTextFileName[256];
char szItemTextFileName[256];

int gLanguage;
int gNewAccountCreate;

unsigned __int32 gItemCount;
#if(CUSTOM_SAVE_PT==TRUE)
unsigned int g_PartyCount = 0;
#endif
CWZScriptEncode CWZSEncode;

CwsJoinServer wsjServer;

CMuNameCheck gMuName;

COptionDbSet gOptionDbSet;
CItemExtDbSet gItemExtDbSet;
CQuery GuildMemberQry;
CWarehouseDBSet CWhDBSet;
CZenEvenDb CZenEvenDBSet;
CCharPreviewDBSet gCharPreDBSet;
CPeriodItemDBSet PeriodItemDBSet;
CMasterLevelSystemDBSet MasterLevelSystemDBSet;
CQuestMonKillDBSet QuestMonKillDBSet;
CCrywolfDBSet CrywolfDBSet;
CCastleDBSet CastleDBSet;
CPetDBSet PetDBSet;
CCharDBSet gCharDbSet;
CAccountCharDBSet gACDbSet;

CGSDBSet gGSDbSet;
CDirPath gDirPath;
classdef DCInfo;

GensDBSet gGensDBSet;
#ifdef GAMESHOP
GameShopDBSet gGameShopDB;
#endif


CPeriodItemZtDBSet PeriodItemZtDBSet;
LuckyItemDBSet g_LuckyItemDBSet;

cWinQuest gWinQuest;

cRageSystem gRageSystem;

cRanking gRanking;

char szDbConnectID[52];
char szDbConnectPass[52];
char szDbConnectDsn[52];
char szDbConnectMemb[52];

#define WM_ASYNCSELECTMSG_CLIENT		(WM_USER+1001)

#define WM_ASYNCSELECTMSG_SERVERACCEPT	(WM_USER+1002)	// 서버의 접속을 기다리는 메시지

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_ASYNCSELECTMSG_SERVERACCEPT, OnAsyncSelectServerAccept)	
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

#if(ENABLE_RAM_MIN)
void RamOptimization(LPVOID lpThreadParameter) 
{ 
	HANDLE hCurrentProcess = NULL;

	while(TRUE) 
	{ 
		Sleep(5000);
		hCurrentProcess = GetCurrentProcess();
		SetProcessWorkingSetSize(hCurrentProcess, 0xFFFFFFFF, 0xFFFFFFFF); 
		SetThreadPriority(hCurrentProcess, THREAD_BASE_PRIORITY_MIN); 
	} 
}
#endif

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CDataserverApp* DataApp = (CDataserverApp*)AfxGetApp(); //0x08

	char szText[256]; //0x108
	WZSMDToken iTokenType; //0x10C

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		return -1;
	}
	
#if(!NEW_WIN)
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
#endif
#if(!NEW_WIN)
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
#endif

#if(ENABLE_RAM_MIN)
	CreateThread (0, 0, (LPTHREAD_START_ROUTINE)RamOptimization, 0, 0 , 0);
#endif

	LogInit(LOG_PRINT);

	gDirPath.SetFirstPath("..\\data\\");

	if(CWZSEncode.Open(".\\dataserver.ini.dat") == FALSE)
	{
		AfxMessageBox("file 'dataserver.ini.dat' is not exist in local folder.", 16, 0);
	}

	CWZSEncode.GetToken();
	gNewAccountCreate = CWZSEncode.GetNumber();
	CWZSEncode.GetToken(); //??
	CWZSEncode.GetToken();
	strcpy(szDbConnectID, CWZSEncode.GetString());
	CWZSEncode.GetToken();
	strcpy(szDbConnectPass, CWZSEncode.GetString());
	CWZSEncode.GetToken();
	DCInfo.SetMabubBanjiOption( CWZSEncode.GetNumber() );

	iTokenType = CWZSEncode.GetToken();

	GetPrivateProfileStringA("Connect","DataBase","MuOnline",szDbConnectDsn,sizeof(szDbConnectDsn),".\\Connect.ini");
	GetPrivateProfileStringA("Connect","MembBase","MuOnline",szDbConnectMemb,sizeof(szDbConnectMemb),".\\Connect.ini");
	

	//if(iTokenType == T_END)
	//{
	//	strcpy(szDbConnectDsn, "MuOnline");
	//}
	//else
	//{
	//	strcpy(szDbConnectDsn, CWZSEncode.GetString());
	//}

	if(strcmp(szDbConnectDsn, "") == 0)
	{
		strcpy(szDbConnectDsn, "MuOnline");
	}

	//LogAddTD("szDbConnectDsn %s ", __FILE__, __LINE__);

	CWZSEncode.Close();

	gCharDbSet.SetSP_WZ_CreateCharacterGetVersion( GetPrivateProfileInt("DataServerInfo", "CreateCharacterSP_Ver", 1, "..\\data\\dataserver.ini") );

	gLanguage = 0;//GetPrivateProfileInt("GameServerInfo", "Language", 0, gDirPath.GetNewPath("commonserver.cfg") );

	strcpy(szKorItemTextFileName, gDirPath.GetNewPath("Items\\item.txt"));
	strcpy(szKorSkillTextFileName, gDirPath.GetNewPath("Skills\\Skill.txt"));
#if(NEW_WIN)
	SYSTEMTIME tmNowDate;
	GetLocalTime(&tmNowDate);
	wsprintf(szText, "ZtTeam :: Data Server :: 2012 - %d", tmNowDate.wYear);
#else
	wsprintf(szText, "Data Server Port:%d App ver : %s %s", DataApp->GetServerPort(), szVersion, DATASERVER_DATE);
#endif
	switch(gLanguage)
	{
	case 0:
		{
			strcpy(szItemTextFileName, gDirPath.GetNewPath("Items\\item.txt"));
			strcpy(szSkillTextFileName, gDirPath.GetNewPath("Skills\\Skill.txt"));
			//strcat(szText, "(Kor)");
		}
		break;
	case 1:
		{
			strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\eng\\item(eng).txt"));
			strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\eng\\Skill(eng).txt"));
			//strcat(szText, "(Eng)");
		}
		break;
	case 2:
		{
			strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\jpn\\item(jpn).txt"));
			strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\jpn\\Skill(jpn).txt"));
			//strcat(szText, "(Jpn)");
		}
		break;
	case 3:
		{
			strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\chs\\item(chs).txt"));
			strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\chs\\Skill(chs).txt"));
			//strcat(szText, "(Chs)");
		}
		break;
	case 4:
		{
			strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\tai\\item(tai).txt"));
			strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\tai\\Skill(tai).txt"));
			//strcat(szText, "(Tai)");
		}
		break;
	case 5:
		{
			strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\tha\\item(Tha).txt"));
			strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\tha\\Skill(Tha).txt"));
			//strcat(szText, "(Tha)");
		}
		break;
	case 6:
		{
			strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\phi\\item(phi).txt"));
			strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\phi\\Skill(phi).txt"));
			//strcat(szText, "(Phi)");
		}
		break;
	case 7:
		{
			strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\vtm\\item(vtm).txt"));
			strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\vtm\\Skill(vtm).txt"));
			//strcat(szText, "(Vtm)");
		}
		break;
	}

	if(OpenItemScript(szKorItemTextFileName) == FALSE)
	{
		MsgBox("Item FIle Not Found. (파일이 존재하지 않습니다.) %s", szKorItemTextFileName);
	}

	if(gLanguage == 0)
	{
		if(gMuName.NameLoad(szItemTextFileName) == FALSE)
		{
			MsgBox("Item File Not Found.");
		}
	}
	else if(gMuName.NameLoad(szKorItemTextFileName) == FALSE)
	{
		MsgBox("Item File Not Found.");
	}

	if(gMuName.NameLoad("..\\Data\\Monsters\\Monster.txt") == FALSE)
	{
		MsgBox("Monster File Not Found.");
	}

	if(gLanguage == 0)
	{
		if(gMuName.NameLoad(szSkillTextFileName) == FALSE)
		{
			MsgBox("Skill File Not Found.");
		}
	}
	else if(gMuName.NameLoad(szKorSkillTextFileName) == FALSE)
	{
		MsgBox("Skill File Not Found.");
	}

	DCInfo.Init();

	if(cBadStrChk.Load("..\\data\\badsyntax.txt") == FALSE)
	{
		MsgBox("badstring load error");
	}

	if(g_MapServerManager.LoadMapData( gDirPath.GetNewPath("Other\\MapServerInfo.dat") ) == FALSE)
	{
		MsgBox("Map Server Data load error");
	}

	CRect mWin;

	mWin.top = 0;
	mWin.bottom = GetSystemMetrics(SM_CYFULLSCREEN);

	if(DataApp->GetServerPosition() <= 1)
	{
		mWin.left = 0;
		mWin.right = GetSystemMetrics(SM_CXFULLSCREEN) / 2;
	}
	else
	{
		mWin.left = GetSystemMetrics(SM_CXFULLSCREEN) / 2;
		mWin.right = GetSystemMetrics(SM_CXFULLSCREEN);
	}

#if(NEW_WIN==1)
	if(DataApp->GetServerPosition() >= 1)
	{
		CWnd::MoveWindow(100, 50+NEW_WIN_HEIGHT, NEW_WIN_WIDTH, NEW_WIN_HEIGHT);
	}
	else
	{
		CWnd::MoveWindow(100, 10, NEW_WIN_WIDTH, NEW_WIN_HEIGHT);
	}
#else
	CWnd::MoveWindow((LPRECT)mWin);
#endif
	CWnd::SetWindowText(szText);

	CWnd::SetTimer(1001, 1000, NULL);
	CWnd::SetTimer(1000, 100000, NULL);
	CWnd::SetTimer(1002, 60000, NULL);
	//CWnd::SetTimer(1003, 10000, NULL);	//DeBug

	if(ServerCreate() == FALSE)
	{
		return -1;
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0, 0, 0, 0);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

//----------------------------------------------------------------------------
// 서버의 접속 메시지를 처리
//----------------------------------------------------------------------------
LONG CMainFrame::OnAsyncSelectServerAccept(WPARAM wParam, LPARAM lParam)
{
	switch( (WORD)lParam & 0xFFFF )
	{
	case FD_ACCEPT :
		AcceptClient();
		break;
	case FD_CLOSE :
		closesocket(wParam);
		LogAdd("port check close");
		break;
	}
	return TRUE;
}

//----------------------------------------------------------------------------
// Join 서버에 사용자가 접속해 왔을때
//----------------------------------------------------------------------------
// type : 
// CLINETACCEPTTYPE : 클라이언트가(유저) 접속했을때 
// SERVERACCEPTTYPE : 서버가 접속했을때 
int CMainFrame::AcceptClient()
{
	LogAdd("port check accept");
	
	SOCKET		clientSocket;
	IN_ADDR		clientAddr;

	wsjServer.AcceptSocket(clientSocket, clientAddr);

	return TRUE;
}

int iTick = 0;

void CMainFrame::OnTimer(UINT nIDEvent)
{
	switch( nIDEvent )
	{
	case 1001 :
		{
			Invalidate(TRUE);

			if(iTick >= 60)
			{
				g_OfflineMode.Run();
			}

			iTick++;
		}
		break;
	case 1000 :
		LogDateChange();
		break;
	case 1002:
		if( !gGensDBSet.UpdateRanking() )
		{
			LogAddC(LOGC_RED, "[ERROR] GensRankingUpdate");
		}
		#if(DEV_PLAYERSHOP)
		#if(MARKET_ITEM_RECV)
		//g_ItemMarket.RunItemDate();
		#endif
		#endif
		break;
	//case 1003:
		//{
			//gRanking.CharacterRanking();
		//}
		//break;
	}
	CWnd::OnTimer( nIDEvent );
}

BOOL CMainFrame::ServerCreate()
{
	CDataserverApp* DataApp = (CDataserverApp*)AfxGetApp();

	gSObjInit();

	//DbSet
	if(gGSDbSet.Connect() == FALSE)
	{
		return FALSE;
	}

	if(gACDbSet.Connect() == FALSE)
	{
		return FALSE;
	}

	if(gCharDbSet.Connect() == FALSE)
	{
		return FALSE;
	}

	if(gCharPreDBSet.Conenect() == FALSE)
	{
		return FALSE;
	}

	CZenEvenDBSet.Connect();

	if(CWhDBSet.Connect() == FALSE)
	{
		return FALSE;
	}

	if(gItemExtDbSet.Connect() == FALSE)
	{
		return FALSE;
	}

	if(gOptionDbSet.Connect() == FALSE)
	{
		return FALSE;
	}

	if(gGSDbSet.CheckMuDBIdentification() == FALSE)
	{
		MsgBox("☆ Unknow MuDB Id.");
	}
	else
	{
#if(!NEW_WIN)
		CString szTitle;
		CString szNewTitle;
		GetWindowText(szTitle);
		szNewTitle.Format("%s - ☆ %s", szTitle, g_szDBID_DESC);
		SetWindowText(szNewTitle);
#endif
	}

	gItemCount = gGSDbSet.GetCount();

	//DbSet New
	if(PetDBSet.Connect() == FALSE)
	{
		return FALSE;
	}

	if(CastleDBSet.Connect() == FALSE)
	{
		return FALSE;
	}

	if(CrywolfDBSet.Connect() == FALSE)
	{
		return FALSE;
	}

	if(QuestMonKillDBSet.Connect() == FALSE)
	{
		return FALSE;
	}

	if(MasterLevelSystemDBSet.Connect() == FALSE)
	{
		return FALSE;
	}

	if(PeriodItemDBSet.Connect() == FALSE
		|| PeriodItemZtDBSet.Connect() == FALSE
		|| g_LuckyItemDBSet.Connect() == FALSE)
	{
		return false;
	}

	if( !gGensDBSet.Connect())
	{
		return false;
	}
#ifdef GAMESHOP
	if( !gGameShopDB.Connect())
	{
		return false;
	}
#endif
	if( !gWinQuest.Connect())
	{
		return false;
	}

	if( !gRageSystem.Connect())
	{
		return false;
	}

	if( !gRanking.Connect())
	{
		return false;
	}

#if(CUSTOM_RETURNSPOT==TRUE)
	if(!g_SpotReturn.Connect())
	{
		return false;
	}
#endif

	if(!g_ZtGDManager.Connect())
	{
		return false;
	}
	
	if(!g_OfflineMode.Connect())
	{
		return false;
	}
	
	if(!g_Marriage.Connect())
	{
		return false;
	}
#if(EVENT_DUNGEON_SIEGE)
	if(!g_DungeonSiege.Connect())
	{
		return false;
	}
#endif

	if(!g_ZtWebManager.Connect())
	{
		return false;
	}

	if(!g_AccountSecurity.Connect())
	{
		return false;
	}

	if(!g_ReferralSystem.Connect())
	{
		return false;
	}

	#if(DEV_BANSYSTEM)
	if(!g_BanSystem.Connect())
	{
		return false;
	}
	#endif

	//#if(DEV_BANSYSTEM)
	if(!g_GuildBank.Connect())
	{
		return false;
	}
	//#endif

	#if(ENABLE_MULTI_CHAR)
	g_MultiChar.Connect();
	#endif	

	#if(DEV_PLAYERSHOP)
	g_ItemMarket.Connect();
	#endif

	if(strcmp(szVersion, "4.1") == 0)
	{
		MsgBox("4.0 버젼에선 VER_CHATWINDOW_OPTION 이 추가될시 문제가 발생합니다");
	}

	cAM.StartThread();

	g_WZIPCheck.Init();

	LogAdd("DataServer Run");

#if(ENABLE_SOCKET_MANAGER)

	WSADATA wsa;

	if(WSAStartup(MAKEWORD(2,2),&wsa) == 0)
	{
		gSocketManager.Start(DataApp->GetServerPort());
	}

#else

	CreateGIocp(DataApp->GetServerPort());

	wsjServer.MyWinsockBase::CreateSocket(m_hWnd);
	wsjServer.CreateServer(NULL, DataApp->GetServerPort()+1, 2026, 0);

#endif


	return TRUE;
}

void CMainFrame::OnClose()
{
	int n, count = 0;

	for(n = 0; n < MAX_SERVEROBJECT; n++)
	{
		if(gSObj[n].Connected != 0)
		{
			LogAdd(" %s GameServer Conneting... ", &gSObj[n].ServerCode);
			count++;
		}
	}

	char szTemp[256] = "Server Close?";

	if ( count > 0 )
	{
		wsprintf(szTemp, "%d 개의 게임서버가 접속 중 입니다. 강제 종료를 하실 경우엔 데이터 손실이 될 수 있습니다.", count);
		AfxMessageBox(szTemp, 16, 0);
	}

	if ( AfxMessageBox("close?", 36, 0) == 7 )
	{
		return;
	}

	for(n = 0; n < MAX_SERVEROBJECT; n++)
	{
		gSObjDel(n);
	}

	CFrameWnd::OnClose();
}

DWORD WINAPI GuildLoadThread(LPVOID p)
{
	return 1;
}
#if(!NEW_WIN)
void CMainFrame::DisplayStatusBar(char *szString)
{
	m_wndStatusBar.SetWindowText(szString);
}
#endif