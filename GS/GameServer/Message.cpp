#include "StdAfx.h"
#include "user.h"
#include "..\common\winutil.h"
#include "ZtLicenseProtocol.h"

//Message Exp
//===========
void MsgNormal(int aIndex,char* szMsg,...)
{
#if(ENABLE_TEXTCHANGE)
	if(g_ZtLicense.CheckUser(eZtUB::masonX) || g_ZtLicense.CheckUser(eZtUB::Local))
	{
		szMsg = g_Text.Change(szMsg);
	}
#endif

	char szTemp[1024];
	va_list pArguments;
	va_start(pArguments,szMsg);
	vsprintf(szTemp,szMsg,pArguments);
	va_end(pArguments);
	
	GCServerMsgStringSend(szTemp, aIndex,1); // 0 = Global MSG; 1 = System information; 2 = Guild notice
}
//Chat Message
//============
void MessageChat(int aIndex,char* szMsg,...)
{
#if(ENABLE_TEXTCHANGE)
	if(g_ZtLicense.CheckUser(eZtUB::masonX) || g_ZtLicense.CheckUser(eZtUB::Local))
	{
		szMsg = g_Text.Change(szMsg);
	}
#endif

	char Message[1024];
	va_list pArguments;
    va_start(pArguments,szMsg);
	//vsprintf_s(Message,sizeof(Message), szMsg, pArguments);
	vsprintf(Message,szMsg,pArguments);
	va_end(pArguments);
	BYTE *Packet;
	Packet = (BYTE*) malloc(200);
	memset(Packet, 0x00, 200);
	*Packet = 0xC1;
	*(Packet+2) = 0x00;
	memcpy((Packet+13), Message, strlen(Message));
	int Len = (strlen(Message) + 0x13);
	*(Packet+1) = Len;
	DataSend(aIndex,Packet, Len);
	free (Packet);
}
//ChatSend(LPOBJ lpObj, char* szChat);
//================
void MessageAllChat(int aIndex,char* szMsg,...)
{
	char Message[1024];
	va_list pArguments;
    va_start(pArguments,szMsg);
	//vsprintf_s(Message,sizeof(Message), szMsg, pArguments);
	vsprintf(Message,szMsg,pArguments);
	va_end(pArguments);
	BYTE *Packet;
	Packet = (BYTE*) malloc(200);
	memset(Packet, 0x00, 200);
	*Packet = 0xC1;
	*(Packet+2) = 0x00;
	memcpy((Packet+13), Message, strlen(Message));
	int Len = (strlen(Message) + 0x13);
	*(Packet+1) = Len;
	DataSendAll(Packet, Len);
	free (Packet);
}
//Message All Global
//==================
void MessaageAllGlobal(char* szMsg,...)
{
#if(ENABLE_TEXTCHANGE)
	if(g_ZtLicense.CheckUser(eZtUB::masonX) || g_ZtLicense.CheckUser(eZtUB::Local))
	{
		szMsg = g_Text.Change(szMsg);
	}
#endif
	char szTemp[1024];
	va_list pArguments;
	va_start(pArguments,szMsg);
	vsprintf(szTemp,szMsg,pArguments);
	va_end(pArguments);
	AllSendServerMsg(szTemp);
}

void ChatMessageOne(int aIndex, char * msg, ...)
{
	PMSG_CHATDATA pWhisper;
	PHeadSetB((LPBYTE)&pWhisper, 0x00, sizeof(pWhisper));
	strcpy(pWhisper.chatid, gObj[aIndex].Name);
	memcpy(pWhisper.chatmsg, msg, sizeof(pWhisper.chatmsg));
	int len = strlen(pWhisper.chatmsg);

	if ( len > 0 )
	{
		pWhisper.h.size -= sizeof(pWhisper.chatmsg);
		pWhisper.h.size += len + 1;

		DataSendAll((LPBYTE)&pWhisper, pWhisper.h.size);
	}
}

void ChatMessageTwo(int aIndex, char * msg, ...)
{
	PMSG_CHATDATA_WHISPER pWhisper;
	PHeadSetB((LPBYTE)&pWhisper, 0x02, sizeof(pWhisper));
	strcpy(pWhisper.id, gObj[aIndex].Name);
	memcpy(pWhisper.chatmsg, msg, sizeof(pWhisper.chatmsg));
	int len = strlen(pWhisper.chatmsg);

	if ( len > 0 )
	{
		pWhisper.h.size -= sizeof(pWhisper.chatmsg);
		pWhisper.h.size += len + 1;

		DataSendAll((LPBYTE)&pWhisper, pWhisper.h.size);
	}
}

#pragma pack(push, 1)
struct CHAT_WHISPER_EX
{
	PBMSG_HEAD	Head;
	char		Name[10];
	char		Message[90];
	BYTE		Type;
};
#pragma pack(pop)

void MessageSendEx(int aIndex, int Type, char * Sender, char * Message, ...)
{
#if(ENABLE_TEXTCHANGE)
	if(g_ZtLicense.CheckUser(eZtUB::masonX) || g_ZtLicense.CheckUser(eZtUB::Local))
	{
		Message = g_Text.Change(Message);
	}
#endif

	char szTemp[1024];
	
#ifdef FIX_CRASH_PROCENT_IN_PRIVATE_CHAT
	strcpy(szTemp, Message);
#else
	va_list pArguments;
	va_start(pArguments, Message);
	vsprintf(szTemp, Message, pArguments);
	va_end(pArguments);
#endif // FIX_CRASH_PROCENT_IN_PRIVATE_CHAT

	// ----
	CHAT_WHISPER_EX pMessage;
	memcpy(pMessage.Name, Sender, 10);
	memcpy(pMessage.Message, szTemp, 90);
	pMessage.Type = Type;	//Test na Crash
	pMessage.Head.set((LPBYTE)&pMessage, 2, sizeof(CHAT_WHISPER_EX));
	DataSend(aIndex,(LPBYTE)&pMessage, pMessage.Head.size);
}

void MessageSendAllEx(int Type, char * Sender, char * Message, ...)
{
#if(ENABLE_TEXTCHANGE)
	if(g_ZtLicense.CheckUser(eZtUB::masonX) || g_ZtLicense.CheckUser(eZtUB::Local))
	{
		Message = g_Text.Change(Message);
	}
#endif

	char szTemp[1024];
	va_list pArguments;
	va_start(pArguments, Message);
	vsprintf(szTemp, Message, pArguments);
	va_end(pArguments);
	// ----
	CHAT_WHISPER_EX pMessage;
	memcpy(pMessage.Name, Sender, 10);
	memcpy(pMessage.Message, szTemp, 90);
	pMessage.Type = Type;	//Test na Crash
	pMessage.Head.set((LPBYTE)&pMessage, 2, sizeof(CHAT_WHISPER_EX));
	DataSendAll((LPBYTE)&pMessage, pMessage.Head.size);

#if(ZTLICENSE_SERVER)
	//g_ZtLicenseProtocol.GLChatMessage(pMessage.Name, pMessage.Message);
#endif
}