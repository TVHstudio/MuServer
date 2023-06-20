#include "stdafx.h"
#include "Import.h"
#include "Interface.h"
#include "ChatSmile.h"
#include "Console.h"
#include "TMemory.h"
#include "ChatExpanded.h"

#if(ENABLE_CHAT_SMILE)

CChatSmile g_ChatSmile;

CChatSmile::CChatSmile()
{
	this->Init();
}

CChatSmile::~CChatSmile()
{
}

void CChatSmile::Init()
{
	this->m_OpenIcon = false;

	this->m_OnClickSmile = false;
	this->m_EventTickSmile = 0;

	memset(this->m_TextSmile, 0, sizeof(256));
	this->m_CountSmile = 0;

	this->BindButton();

	this->Hook();
}

void CChatSmile::Hook()
{
#if(ENABLE_1_04_05)
	SetOp((LPVOID)0x007890A4, this->RenderText, ASM::CALL);//007890A4
	SetOp((LPVOID)0x007890ED, this->RenderText, ASM::CALL);//007890ED

	SetOp((LPVOID)0x0078707F, this->SendChat, ASM::CALL);//0078707F
	SetOp((LPVOID)0x00599259, this->sub_597980, ASM::CALL);//ок
	SetOp((LPVOID)0x00599289, this->sub_9CF3B0, ASM::CALL);//ок
#else
	SetOp((LPVOID)0x00788F54, this->RenderText, ASM::CALL);//007890A4
	SetOp((LPVOID)0x00788F9D, this->RenderText, ASM::CALL);//007890ED

	SetOp((LPVOID)0x00786F2F, this->SendChat, ASM::CALL);//0078707F
	SetOp((LPVOID)0x00599259, this->sub_597980, ASM::CALL);//ок
	SetOp((LPVOID)0x00599289, this->sub_9CF3B0, ASM::CALL);//ок
#endif
}

void CChatSmile::Load()
{

}

void CChatSmile::BindButton()
{
	gInterface.BindObject(eCHAT_SMILE_BUTTON, zt_CHAT_SMILE_BUTTON, 26, 23, 280, 385);
}

void CChatSmile::LoadSmile()
{
	pLoadImage("ZtData\\Interface\\Smile\\smiles_icons.tga", zt_CHAT_SMILE_ICON, GL_LINEAR, GL_CLAMP, 1, 0); 
	pLoadImage("ZtData\\Interface\\Smile\\newui_Bt_Chat_smile.jpg", zt_CHAT_SMILE_BUTTON, GL_LINEAR, GL_CLAMP, 1, 0); 
	pLoadImage("Interface\\newui_chat_whisper.jpg", zt_CHAT_SMILE_BGLINE, GL_LINEAR, GL_CLAMP, 1, 0);
}

void CChatSmile::DrawButton()
{
	if(gInterface.CheckWindow(ObjWindow::ChatWindow))
	{
		if(!this->m_OpenIcon)
		{
			pDrawButton(zt_CHAT_SMILE_BUTTON, 280, 385, 26, 23, 0.0, 0 );
		}
		else
		{
			pDrawButton(zt_CHAT_SMILE_BUTTON, 280, 385, 26, 23, 0.0, 23 );
		}
		
		if(this->m_OpenIcon)
		{
			pSetCursorFocus = true;

			int X = 315;
			int Y = 225;
			int Column = 0;

			for(int i = 0; i < 100; i++)
			{
				this->DrawSmile(i, X, Y);

				X += 18;

				Column++;

				if(Column == 10)
				{
					X = 315;
					Y += 18;
					Column = 0;
				}
			}
		}

		if(this->m_OpenIcon)
		{
			pDrawButton(zt_CHAT_SMILE_BGLINE, 280, 385+24, 67, 21, 0.0, 0 );
			
			int iDrawSmileCount = 0;

			for(int i = 0; i < strlen(this->m_TextSmile); i++)
			{
				if(this->m_TextSmile[i] == '<' && this->m_TextSmile[i+4] == '>')
				{
					char szTextNum[256];
					sprintf(szTextNum, "%c%c%c", this->m_TextSmile[i+1], this->m_TextSmile[i+2], this->m_TextSmile[i+3]);

					int v6 = atoi(szTextNum);

					float High	= 18;
					float Whith = 18;

					int Model = zt_CHAT_SMILE_ICON;

					float CritX = (double)(v6 % 10) * Whith / 192;
					float CritY = (double)(v6 / 10) * High / 192;
					float standartWhith = Whith / 192;
					float standartHight = High / 192;

					int iXX = 280+1+3 + FULL_X_IN_GAME_X(iDrawSmileCount * 18);
					int iYY = 385-1+28;
					pDrawGUFULL(Model, GAME_X_IN_FULL_X(iXX), GAME_Y_IN_FULL_Y(iYY), Whith, High, CritX, CritY, standartWhith, standartHight, 0, 0, 0.0);
		
					iDrawSmileCount++;
				}
			}
		}
	}
}

void CChatSmile::DrawSmile(int NumIco, int X, int Y)
{
	float High	= 18;
	float Whith = 18;

	int Model = zt_CHAT_SMILE_ICON;
	int v6 = NumIco;

	float CritX = (double)(v6 % 10) * Whith / 192;
	float CritY = (double)(v6 / 10) * High / 192;
	float standartWhith = Whith / 192;
	float standartHight = High / 192;

	pDrawGUFULL(Model, X, Y, Whith, High, CritX, CritY, standartWhith, standartHight, 1, 1, 0.0);
}

void CChatSmile::ControllerSmile(DWORD Event)
{
	if(gInterface.CheckWindow(ObjWindow::ChatWindow))
	{
		if(gInterface.ButtonZt(Event, eCHAT_SMILE_BUTTON, false))
		{
			this->m_OpenIcon = !this->m_OpenIcon;
		}

		if(this->m_OpenIcon)
		{
			int X = 315;
			int Y = 225;
			int Column = 0;

			for(int i = 0; i < 100; i++)
			{
				if(gInterface.IsWorkZone(X, Y, X+18, Y+18))
				{
					DWORD CurrentTick	= GetTickCount();
					DWORD Delay			= (CurrentTick - this->m_EventTickSmile);

					if( Event == WM_LBUTTONDOWN  && this->m_OnClickSmile == false)
					{
						this->m_OnClickSmile = true;
					}

					if(Event == WM_LBUTTONUP && this->m_OnClickSmile == true)
					{
						this->m_OnClickSmile = false;
						break;
					}
					if( Delay < 200 )
					{
						break;
					}

					this->m_OnClickSmile = false;

					this->m_EventTickSmile = GetTickCount();


					if(this->m_CountSmile < MAX_COUNT_SMILE)
					{
						char szAddSmile[8] = { 0 };
						sprintf(szAddSmile, "<%03d>", i);
						strcat(this->m_TextSmile, szAddSmile);

						gConsole.Output(cGREEN, "[Smile] = %s", szAddSmile);

						this->m_CountSmile++;
					}
					break;
				}

				this->DrawSmile(i, X, Y);

				X += 18;

				Column++;

				if(Column == 10)
				{
					X = 315;
					Y += 18;
					Column = 0;
				}
			}
		}
	}
}

#define pDrawTextEx	((int(__thiscall*)(LPVOID This, int PosX, int PosY, char * Text, int Arg4, int Arg5, int * Arg6, SIZE* Arg7)) 0x00420150)

void CChatSmile::RenderText(LPVOID This, int iPos_x, int iPos_y, LPCTSTR pszText, int iBoxWidth, int iBoxHeight, LPINT iSort, SIZE* lpTextSize)
{
	char szTextSmile[256] = { 0 };
	memcpy(szTextSmile, pszText, strlen(pszText));

	for(int i = 0; i < strlen(pszText); i++)
	{
		if(pszText[i] == '<' && pszText[i+4] == '>')
		{
			memset((LPVOID)&pszText[i], 0, 5);
		}
	}

	SIZE RealTextSize = {TRUE};
	pDrawTextEx(This, iPos_x, iPos_y, (char*)pszText, iBoxWidth, iBoxHeight, iSort,  (SIZE*)&RealTextSize);

	int iDrawSmileCount = 0;

	for(int i = 0; i < strlen(szTextSmile); i++)
	{
		if(szTextSmile[i] == '<' && szTextSmile[i+4] == '>')
		{
			char szTextNum[256];
			sprintf(szTextNum, "%c%c%c", szTextSmile[i+1], szTextSmile[i+2], szTextSmile[i+3]);

			int v6 = atoi(szTextNum);

			float High	= 18;
			float Whith = 18;

			int Model = zt_CHAT_SMILE_ICON;

			float CritX = (double)(v6 % 10) * Whith / 192;
			float CritY = (double)(v6 / 10) * High / 192;
			float standartWhith = Whith / 192;
			float standartHight = High / 192;

			int iXX = iPos_x+RealTextSize.cx+1 + FULL_X_IN_GAME_X(iDrawSmileCount * 18);
			int iYY = iPos_y-1;
			pDrawGUFULL(Model, GAME_X_IN_FULL_X(iXX), GAME_Y_IN_FULL_Y(iYY), Whith, High, CritX, CritY, standartWhith, standartHight, 0, 0, 0.0);
		
			iDrawSmileCount++;
		}
	}

	gConsole.Output(cGREEN, "[Smile] [%d] [%d] [%s] size: %d %d", iPos_x, iPos_y, (char*)pszText, RealTextSize.cx, RealTextSize.cy);
}

#define pSendChat	((void(__cdecl*)(char *a1)) 0x5BDE40)

void CChatSmile::SendChat(char *a1)
{
	char szBuffer[256];

	sprintf(szBuffer, "%s %s", a1, g_ChatSmile.m_TextSmile);

	pSendChat(szBuffer);

	memset(g_ChatSmile.m_TextSmile, 0, sizeof(256));
	g_ChatSmile.m_CountSmile = 0;
}
#if(ENABLE_1_04_05)
#define pstrncpy	((BYTE*(__cdecl*)(BYTE *a1, char *a2, unsigned int a3)) 0x009D0660)//009D0660
#else
#define pstrncpy	((BYTE*(__cdecl*)(BYTE *a1, char *a2, unsigned int a3)) 0x9D04E0)//009D0660
#endif

BYTE * CChatSmile::sub_9D04E0(BYTE *a1, char *a2, unsigned int a3)
{
	char szBuffer[256] = { 0 };

	sprintf(szBuffer, "%s %s", a2, g_ChatSmile.m_TextSmile);

	BYTE* Result = pstrncpy((BYTE*)a1, g_ChatSmile.m_TextSmile, a3);

	return Result;
}

#define pstrlen	((int(__cdecl*)(char* a1)) 0x40BCC0)

int __cdecl CChatSmile::sub_40BCC0(char* a1)
{
	char szBuffer[256] = { 0 };

	sprintf(szBuffer, "%s %s", a1, g_ChatSmile.m_TextSmile);

	return 1;// pstrlen(szBuffer);
}

#define pAddChat	((int(__cdecl*)(int a1, char *a2, int a3)) 0x599180)//ок

int CChatSmile::AddChat(int a1, char *a2, int a3)
{
	for(int i = 0; i < strlen(a2); i++)
	{
		if(a2[i] == '<' && a2[i+4] == '>')
		{
			memset((LPVOID)&a2[i], 0, 5);
		}
	}

	return pAddChat(a1, a2, a3);
}

#define p_9CF3B0	((void(__cdecl*)(char * a1)) 0x9CF3B0)

void CChatSmile::sub_9CF3B0(char * a1, char * a2)
{
	strcpy(a1, a2);

	for(int i = 0; i < strlen(a1); i++)
	{
		if(a1[i] == '<' && a1[i+4] == '>')
		{
			memset((LPVOID)&a1[i], 0, 5);
		}
	}
}

#define P_597980	((int(__cdecl*)(LPCSTR lpMultiByteStr, BYTE *a2, BYTE *a3, int a4)) 0x597980)//ок

int CChatSmile::sub_597980(LPCSTR lpMultiByteStr, BYTE *a2, BYTE *a3, int a4)
{
	//for(int i = 0; i < strlen((char*)a3); i++)
	//{
	//	if(a3[i] == '<' && a3[i+4] == '>')
	//	{
	//		memset((LPVOID)&a3[i], 0, 5);
	//	}
	//}


	int Result = P_597980(lpMultiByteStr, a2, a3, a4);

	for(int i = 0; i < strlen((char*)a2); i++)
	{
		if(a2[i] == '<' && a2[i+4] == '>')
		{
			memset((LPVOID)&a2[i], 0, 5);
		}
	}

	for(int i = 0; i < strlen((char*)a3); i++)
	{
		if(a3[i] == '<' && a3[i+4] == '>')
		{
			memset((LPVOID)&a3[i], 0, 5);
		}
	}

	return Result;


}

#endif