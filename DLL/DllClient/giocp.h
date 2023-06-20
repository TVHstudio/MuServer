#ifndef GIOCP_H
#define GIOCP_H

#if(ENABLE_INDEV_NETWORK)

/* 1.04D */
#define PARSE_PACKET_HOOK		0x0065F9B0
#define PARSE_PACKET_STREAM		0x0063A840
#define PROTOCOL_CORE1			0x006660A0
#define PROTOCOL_CORE2			0x006639D0

#define SEND_PACKET_HOOK		0x00404DB0
#define MU_SEND_PACKET			0x00405110
#define MU_SENDER_CLASS			0x0E61F84

#define PROTOCOL_CORE_HOOK		0x006639D0
#define PROTOCOL_CORE_BACK_JMP	0x006639D9
/***/

void SendPacket(BYTE* buff, int len, int enc, int unk1);
void ParsePacket(void* PackStream, int unk1, int unk2);
void DataSend(void* pData, int size, int enc);
void ProtocolCoreASM();

void NetworkLoad();

#endif

#endif