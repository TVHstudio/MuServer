#include "stdafx.h"
#include "giocp.h"
#include "PacketEncrypt.h"
//#include "Connection.h"
//#include "offsets.h"
#include "protocol.h"
//#include "ReconnectSystem.h"

#include "Protocol.h"

#include "TMemory.h"
#include "packetsend_hooks.h"
#include "Console.h"

#if(ENABLE_INDEV_NETWORK)

BYTE g_ProtoType = 0;

void EncXor32(BYTE headcode, unsigned char*Buff, int SizeOfHeader, int Len)
{
	BYTE byXorFilter[32] = { 0 };

	//byXorFilter[0] = 0xAB;
	//byXorFilter[1] = 0x11;
	//byXorFilter[2] = 0xCD;
	//byXorFilter[3] = 0xFE;
	//byXorFilter[4] = 0x18;
	//byXorFilter[5] = 0x23;
	//byXorFilter[6] = 0xC5;
	//byXorFilter[7] = 0xA3;
	//byXorFilter[8] = 0xCA;
	//byXorFilter[9] = 0x33;
	//byXorFilter[10] = 0xC1;
	//byXorFilter[11] = 0xCC;
	//byXorFilter[12] = 0x66;
	//byXorFilter[13] = 0x67;
	//byXorFilter[14] = 0x21;
	//byXorFilter[15] = 0xF3;
	//byXorFilter[16] = 0x32;
	//byXorFilter[17] = 0x12;
	//byXorFilter[18] = 0x15;
	//byXorFilter[19] = 0x35;
	//byXorFilter[20] = 0x29;
	//byXorFilter[21] = 0xFF;
	//byXorFilter[22] = 0xFE;
	//byXorFilter[23] = 0x1D;
	//byXorFilter[24] = 0x44;
	//byXorFilter[25] = 0xEF;
	//byXorFilter[26] = 0xCD;
	//byXorFilter[27] = 0x41;
	//byXorFilter[28] = 0x26;
	//byXorFilter[29] = 0x3C;
	//byXorFilter[30] = 0x4E;
	//byXorFilter[31] = 0x4D;

	byXorFilter[0] = 0x54;
	byXorFilter[1] = 0xAD;
	byXorFilter[2] = 0x65;
	byXorFilter[3] = 0x0F;
	byXorFilter[4] = 0x33;
	byXorFilter[5] = 0xFE;
	byXorFilter[6] = 0x31;
	byXorFilter[7] = 0xBB;
	byXorFilter[8] = 0x9A;
	byXorFilter[9] = 0x13;
	byXorFilter[10] = 0x56;
	byXorFilter[11] = 0xAC;
	byXorFilter[12] = 0x71;
	byXorFilter[13] = 0x83;
	byXorFilter[14] = 0x60;
	byXorFilter[15] = 0x2B;
	byXorFilter[16] = 0x13;
	byXorFilter[17] = 0x47;
	byXorFilter[18] = 0xBF;
	byXorFilter[19] = 0x28;
	byXorFilter[20] = 0xE9;
	byXorFilter[21] = 0x00;
	byXorFilter[22] = 0x7F;
	byXorFilter[23] = 0x10;
	byXorFilter[24] = 0x6F;
	byXorFilter[25] = 0x32;
	byXorFilter[26] = 0x65;
	byXorFilter[27] = 0xF6;
	byXorFilter[28] = 0x92;
	byXorFilter[29] = 0x1D;
	byXorFilter[30] = 0xD3;
	byXorFilter[31] = 0xEF;

		//byXorFilter[0] = 0xE7;
		//byXorFilter[1] = 0x6D;
		//byXorFilter[2] = 0x3A;
		//byXorFilter[3] = 0x89;
		//byXorFilter[4] = 0xBC;
		//byXorFilter[5] = 0xB2;
		//byXorFilter[6] = 0x9F;
		//byXorFilter[7] = 0x73;
		//byXorFilter[8] = 0x23;
		//byXorFilter[9] = 0xA8;
		//byXorFilter[10] = 0xFE;
		//byXorFilter[11] = 0xB6;
		//byXorFilter[12] = 0x49;
		//byXorFilter[13] = 0x5D;
		//byXorFilter[14] = 0x39;
		//byXorFilter[15] = 0x5D;
		//byXorFilter[16] = 0x8A;
		//byXorFilter[17] = 0xCB;
		//byXorFilter[18] = 0x63;
		//byXorFilter[19] = 0x8D;
		//byXorFilter[20] = 0xEA;
		//byXorFilter[21] = 0x7D;
		//byXorFilter[22] = 0x2B;
		//byXorFilter[23] = 0x5F;
		//byXorFilter[24] = 0xC3;
		//byXorFilter[25] = 0xB1;
		//byXorFilter[26] = 0xE9;
		//byXorFilter[27] = 0x83;
		//byXorFilter[28] = 0x29;
		//byXorFilter[29] = 0x51;
		//byXorFilter[30] = 0xE8;
		//byXorFilter[31] = 0x56;	

	for (int i = 0; i<Len; i++)
	{
		Buff[i] ^= (byXorFilter[(i + SizeOfHeader) & 31] ^ Buff[i - 1]);
	}
}

void DecXor32(BYTE headcode, unsigned char*Buff, int SizeOfHeader, int Len)
{
	BYTE byXorFilter[32] = { 0 };

	//byXorFilter[0] = 0xAB;
	//byXorFilter[1] = 0x11;
	//byXorFilter[2] = 0xCD;
	//byXorFilter[3] = 0xFE;
	//byXorFilter[4] = 0x18;
	//byXorFilter[5] = 0x23;
	//byXorFilter[6] = 0xC5;
	//byXorFilter[7] = 0xA3;
	//byXorFilter[8] = 0xCA;
	//byXorFilter[9] = 0x33;
	//byXorFilter[10] = 0xC1;
	//byXorFilter[11] = 0xCC;
	//byXorFilter[12] = 0x66;
	//byXorFilter[13] = 0x67;
	//byXorFilter[14] = 0x21;
	//byXorFilter[15] = 0xF3;
	//byXorFilter[16] = 0x32;
	//byXorFilter[17] = 0x12;
	//byXorFilter[18] = 0x15;
	//byXorFilter[19] = 0x35;
	//byXorFilter[20] = 0x29;
	//byXorFilter[21] = 0xFF;
	//byXorFilter[22] = 0xFE;
	//byXorFilter[23] = 0x1D;
	//byXorFilter[24] = 0x44;
	//byXorFilter[25] = 0xEF;
	//byXorFilter[26] = 0xCD;
	//byXorFilter[27] = 0x41;
	//byXorFilter[28] = 0x26;
	//byXorFilter[29] = 0x3C;
	//byXorFilter[30] = 0x4E;
	//byXorFilter[31] = 0x4D;

	byXorFilter[0] = 0x54;
	byXorFilter[1] = 0xAD;
	byXorFilter[2] = 0x65;
	byXorFilter[3] = 0x0F;
	byXorFilter[4] = 0x33;
	byXorFilter[5] = 0xFE;
	byXorFilter[6] = 0x31;
	byXorFilter[7] = 0xBB;
	byXorFilter[8] = 0x9A;
	byXorFilter[9] = 0x13;
	byXorFilter[10] = 0x56;
	byXorFilter[11] = 0xAC;
	byXorFilter[12] = 0x71;
	byXorFilter[13] = 0x83;
	byXorFilter[14] = 0x60;
	byXorFilter[15] = 0x2B;
	byXorFilter[16] = 0x13;
	byXorFilter[17] = 0x47;
	byXorFilter[18] = 0xBF;
	byXorFilter[19] = 0x28;
	byXorFilter[20] = 0xE9;
	byXorFilter[21] = 0x00;
	byXorFilter[22] = 0x7F;
	byXorFilter[23] = 0x10;
	byXorFilter[24] = 0x6F;
	byXorFilter[25] = 0x32;
	byXorFilter[26] = 0x65;
	byXorFilter[27] = 0xF6;
	byXorFilter[28] = 0x92;
	byXorFilter[29] = 0x1D;
	byXorFilter[30] = 0xD3;
	byXorFilter[31] = 0xEF;

		//byXorFilter[0] = 0xE7;
		//byXorFilter[1] = 0x6D;
		//byXorFilter[2] = 0x3A;
		//byXorFilter[3] = 0x89;
		//byXorFilter[4] = 0xBC;
		//byXorFilter[5] = 0xB2;
		//byXorFilter[6] = 0x9F;
		//byXorFilter[7] = 0x73;
		//byXorFilter[8] = 0x23;
		//byXorFilter[9] = 0xA8;
		//byXorFilter[10] = 0xFE;
		//byXorFilter[11] = 0xB6;
		//byXorFilter[12] = 0x49;
		//byXorFilter[13] = 0x5D;
		//byXorFilter[14] = 0x39;
		//byXorFilter[15] = 0x5D;
		//byXorFilter[16] = 0x8A;
		//byXorFilter[17] = 0xCB;
		//byXorFilter[18] = 0x63;
		//byXorFilter[19] = 0x8D;
		//byXorFilter[20] = 0xEA;
		//byXorFilter[21] = 0x7D;
		//byXorFilter[22] = 0x2B;
		//byXorFilter[23] = 0x5F;
		//byXorFilter[24] = 0xC3;
		//byXorFilter[25] = 0xB1;
		//byXorFilter[26] = 0xE9;
		//byXorFilter[27] = 0x83;
		//byXorFilter[28] = 0x29;
		//byXorFilter[29] = 0x51;
		//byXorFilter[30] = 0xE8;
		//byXorFilter[31] = 0x56;	

	for (int i = Len - 1; i >= 0; i--)
	{
		Buff[i] ^= (byXorFilter[(i + SizeOfHeader) & 31] ^ Buff[i - 1]);
	}
}

void __declspec(naked) muSendPacket(BYTE* buff, int len)
{
	__asm {
		PUSH EBP;
		MOV EBP, ESP;
		MOV EAX, len;
		PUSH EAX;
		PUSH buff;
		MOV ECX, DWORD PTR DS:[MU_SENDER_CLASS];
		MOV EDX, MU_SEND_PACKET;
		CALL EDX;
		MOV ESP, EBP;
		POP EBP;
		RETN;
	}
}

void ParsePacket(void* PackStream, int unk1, int unk2)
{
	BYTE* buff;
	g_ProtoType = 1;
	while (true)
	{
		__asm {
			MOV ECX, PackStream;
			MOV EDX, PARSE_PACKET_STREAM;
			CALL EDX;
			MOV buff, EAX;
		}

		if (!buff)
			break;

		//ConvertProtoType(buff);
		//g_ProtoType = 0;
		//ConvertProtoType(buff);

		BYTE DecBuff[7024];
		unsigned int DecSize;

		int proto;
		int size;
		int enc;

		//if (g_Connection == GS_CONNECTED)
		{
			//ConvertProtoType(buff);
		}

		switch (buff[0])
		{
			case 0xC1:
				proto = buff[2];
				size = buff[1];
				enc = 0;
				break;
			case 0xC2:
				proto = buff[3];
				size = *(WORD*)&buff[1];
				enc = 0;
				break;
			case 0xC3:
				enc = 1;
				size = buff[1];
				DecSize = g_PacketEncrypt.Decrypt(&DecBuff[1], &buff[2], size-2);
				DecBuff[0] = 0xC1;
				DecBuff[1] = DecSize+2;
				size = DecSize+2;
				buff = DecBuff;
				proto = DecBuff[2];
				break;
			case 0xC4:
				enc = 1;
				size = MAKEWORD(buff[2], buff[1]);
				DecSize = g_PacketEncrypt.Decrypt(&DecBuff[2], &buff[3], size - 3);
				DecBuff[0] = 0xC2;
				DecBuff[2] = HIBYTE(DecSize+3);
				DecBuff[1] = LOBYTE(DecSize+3);
				size =  DecSize+3;
				buff = DecBuff;
				proto = buff[3];
				break;
		}
		
		if (unk1 == 1)
		{
			typedef int (*tProtocolCore2)(int, int, BYTE*, int, int);
			tProtocolCore2 ProtocolCore2 = (tProtocolCore2)PROTOCOL_CORE1;
			ProtocolCore2(unk2, proto, buff, size, enc);
		}
		else
		{
			//typedef int (*tProtocolCore)(int, BYTE*, int, int);
			//tProtocolCore ProtocolCore = (tProtocolCore)PROTOCOL_CORE2;
			//ProtocolCore(proto, buff, size, enc);
			gProtocol.DataRecv(proto, buff, size, enc);
		}
	}
}
void SendPacket(BYTE* buff, int len, int enc, int unk1)
{
	g_ProtoType = 0;

	//if (g_Connection == GS_CONNECTED)
	{
		// ConvertProtoType(buff);
	}

	if (buff[0] == 0xC1)
	{
		DecXor32(buff[2], &buff[3], 3, len - 3);
	}
	else if (buff[0] == 0xC2)
	{
		DecXor32(buff[3], &buff[4], 4, len - 4);
	}

	if (buff[2] == 0xF3 && buff[3] == 0x03)
	{
		//memcpy(bCharacter, buff, buff[1]);
		//EncXor32(bCharacter[2], &bCharacter[3], 3, buff[1] - 3);
	}

	if(buff[2] == 0xB1 && buff[3] == 0x01)
	{
		//if (g_ReconnectProcess >= 2 && g_ReconnectProcess != 6)
		//	return;
	}

	
	if (buff[0] == 0xC1)
	{
		EncXor32(buff[2], &buff[3], 3, len - 3);
	}
	else if (buff[0] == 0xC2)
	{
		EncXor32(buff[3], &buff[4], 4, len - 4);
	}

	
	
	if (enc)
	{
		BYTE EncBuff[7024];
		unsigned int EncSize;

		if (buff[0] == 0xC1)
		{
			gConsole.Output(cGREY, "0x%X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X", 
				buff[0], buff[1], buff[2], buff[3], buff[4], buff[5]);

			EncSize = g_PacketEncrypt.Encrypt(&EncBuff[2], &buff[2], len-2);
			//memcpy(&EncBuff[2], &buff[2], len-2);

			EncBuff[0] = 0xC3;
			EncBuff[1] = EncSize+2;
			buff = EncBuff;
			len = EncSize+2;

			//gConsole.Output(cGREEN, "0x%02X 0x%02X 0x%02X 0x%02X 0x%02X", EncBuff[0], EncBuff[1], EncBuff[2], EncBuff[3], EncBuff[4]);
		}
		else if (buff[0] == 0xC2)
		{
			EncSize = g_PacketEncrypt.Encrypt(&EncBuff[3], &buff[3], len - 3);
			EncBuff[0] = 0xC4;
			EncBuff[1] = HIBYTE(EncSize+3);
			EncBuff[2] = LOBYTE(EncSize+3);
			buff = EncBuff;
			len = EncSize+3;
		}
	}
	if (buff[0] == 0xC1 && buff[2] == 0x0E)
	{
	/*	PMSG_CLIENTTIME * data = (PMSG_CLIENTTIME*)buff;
		data->h.len = sizeof(PMSG_CLIENTTIME);
		data->IsModifiedGameSpeed = CheckSH();
		data->IsModifiedAttackSpeed = 2;
		data->IsModifiedMagicSpeed = 2;
		for(int i=0;i<15;i++)
		{
			data->dump1[i] = rand()%0xFF;
			data->dump2[i] = rand()%0xFF;
			data->dump3[i] = rand()%0xFF;
		}
		buff = (PBYTE)data;
		len = sizeof(PMSG_CLIENTTIME);*/
	}

	

	muSendPacket(buff, len);
	//send(pActiveSocket, (char*)buff, len, 0);
}

void DataSend(void* pData, int size, int Enc)
{
	BYTE* pack = (BYTE*)pData;

	if (pack[0] == 0xC1)
	{
		EncXor32(pack[2], &pack[3], 3, size - 3);
	}

	else if (pack[0] == 0xC2)
	{
		EncXor32(pack[3], &pack[4], 4, size - 4);
	}

	SendPacket((BYTE*)pData, size, 1, 0);
}

bool ProtocolCore(int protocol, BYTE* aRecv, int len)
{
	//gProtocol.DataRecv(protocol, aRecv, len, 0);

	return 0;
}

void __declspec(naked) ProtocolCoreASM()
{
	__asm {
		PUSH EBP;
		MOV EBP, ESP;

//		PUSH DWORD PTR SS:[EBP+0x10];
//		PUSH DWORD PTR SS:[EBP+0xC];
//		CALL DecPack;

		PUSH DWORD PTR SS:[EBP+0x10];
		PUSH DWORD PTR SS:[EBP+0xC];
		PUSH DWORD PTR SS:[EBP+0x8];

		CALL ProtocolCore;
		//Protocol::DataRecv

		TEST AL, AL;
		JE False;

		MOV ESP, EBP;
		POP EBP;
		RETN;

False:
		MOV ESP, EBP;
		POP EBP;
		PUSH EBP;
		MOV EBP,ESP;
		SUB ESP,0x274;
		MOV EDX, PROTOCOL_CORE_BACK_JMP;
		JMP EDX;
	}
}


void NetworkLoad()
{
	//HookManager.MakeJmpHook(PROTOCOL_CORE_HOOK, ProtocolCoreASM);
	//SetOp((LPVOID)PROTOCOL_CORE_HOOK, (LPVOID)ProtocolCoreASM, ASM::JMP);

	//HookManager.MakeJmpHook(PARSE_PACKET_HOOK, ParsePacket);
	SetOp((LPVOID)PARSE_PACKET_HOOK, (LPVOID)ParsePacket, ASM::JMP);

	//HookManager.MakeJmpHook(SEND_PACKET_HOOK, SendPacket);
	SetOp((LPVOID)SEND_PACKET_HOOK, (LPVOID)SendPacket, ASM::JMP);

	//HookPacketSend();

	BYTE byXorFilter[32] = { 0 };

	byXorFilter[0] = 0x54;
	byXorFilter[1] = 0xAD;
	byXorFilter[2] = 0x65;
	byXorFilter[3] = 0x0F;
	byXorFilter[4] = 0x33;
	byXorFilter[5] = 0xFE;
	byXorFilter[6] = 0x31;
	byXorFilter[7] = 0xBB;
	byXorFilter[8] = 0x9A;
	byXorFilter[9] = 0x13;
	byXorFilter[10] = 0x56;
	byXorFilter[11] = 0xAC;
	byXorFilter[12] = 0x71;
	byXorFilter[13] = 0x83;
	byXorFilter[14] = 0x60;
	byXorFilter[15] = 0x2B;
	byXorFilter[16] = 0x13;
	byXorFilter[17] = 0x47;
	byXorFilter[18] = 0xBF;
	byXorFilter[19] = 0x28;
	byXorFilter[20] = 0xE9;
	byXorFilter[21] = 0x00;
	byXorFilter[22] = 0x7F;
	byXorFilter[23] = 0x10;
	byXorFilter[24] = 0x6F;
	byXorFilter[25] = 0x32;
	byXorFilter[26] = 0x65;
	byXorFilter[27] = 0xF6;
	byXorFilter[28] = 0x92;
	byXorFilter[29] = 0x1D;
	byXorFilter[30] = 0xD3;
	byXorFilter[31] = 0xEF;

	for( int i = 0; i < 32; i++ )
	{
		SetByte((PVOID)((oXORFilterStart + 4 * i) + 3), byXorFilter[i]);
	}

}

#endif