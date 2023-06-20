#ifndef PACKETENCRYPT_H
#define PACKETENCRYPT_H

#if(ENABLE_INDEV_NETWORK)

//#include <rijndael.h>
//#include <rsa.h>

#include "E:\ZtTeam\Season8Episode2\Source\GameServer\crypto\rijndael.h"
#include "E:\ZtTeam\Season8Episode2\Source\GameServer\crypto\rsa.h"
#pragma comment(lib, "E:\\ZtTeam\\Season8Episode2\\Source\\GameServer\\crypto\\Win32\\Output\\Release\\cryptlib.lib")

class CPacketEncrypt
{

public:

	CPacketEncrypt();
	virtual ~CPacketEncrypt();

	int Encrypt(BYTE * lpDest, BYTE * lpSource, int iSize);
	int Decrypt(BYTE * lpDest, BYTE * lpSource, int iSize);

private:
	CryptoPP::Rijndael::Encryption enc;
	CryptoPP::Rijndael::Decryption dec;
};

extern CPacketEncrypt g_PacketEncrypt;

#endif

#endif