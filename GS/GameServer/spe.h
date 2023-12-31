#ifndef SPE_H
#define SPE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logproc.h"

class CStreamPacketEngine_Server
{

public:

	CStreamPacketEngine_Server()
	{
		this->Clear();
	};

	virtual ~CStreamPacketEngine_Server()
	{
		return;
	};

	void Clear() 
	{
		this->m_wSize = 0;
	};

protected:

	void XorData(int iStart, int iEnd, int iDir)
	{
		if ( iStart < iEnd  )
		{
			LogAddC(2, "CStreamPacketEngine XorData Error %d,%d", iStart, iEnd);
			return;
		}

		BYTE byXorFilter[32];

		//byXorFilter[0]	= 0xAB;
		//byXorFilter[1]	= 0x11; 
		//byXorFilter[2]	= 0xCD;
		//byXorFilter[3]	= 0xFE; 
		//byXorFilter[4]	= 0x18;
		//byXorFilter[5]	= 0x23;
		//byXorFilter[6]	= 0xC5;
		//byXorFilter[7]	= 0xA3;
		//byXorFilter[8]	= 0xCA; 
		//byXorFilter[9]	= 0x33;
		//byXorFilter[10]	= 0xC1; 
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

		#if(ENABLE_ENCDEC_EVOMU)

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

		#else

		//ZtTeam Packet

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

		#endif

#if(ZTTEAM_GAMECLIENT_DEV)
		byXorFilter[0] = 0xE7;
		byXorFilter[1] = 0x6D;
		byXorFilter[2] = 0x3A;
		byXorFilter[3] = 0x89;
		byXorFilter[4] = 0xBC;
		byXorFilter[5] = 0xB2;
		byXorFilter[6] = 0x9F;
		byXorFilter[7] = 0x73;
		byXorFilter[8] = 0x23;
		byXorFilter[9] = 0xA8;
		byXorFilter[10] = 0xFE;
		byXorFilter[11] = 0xB6;
		byXorFilter[12] = 0x49;
		byXorFilter[13] = 0x5D;
		byXorFilter[14] = 0x39;
		byXorFilter[15] = 0x5D;
		byXorFilter[16] = 0x8A;
		byXorFilter[17] = 0xCB;
		byXorFilter[18] = 0x63;
		byXorFilter[19] = 0x8D;
		byXorFilter[20] = 0xEA;
		byXorFilter[21] = 0x7D;
		byXorFilter[22] = 0x2B;
		byXorFilter[23] = 0x5F;
		byXorFilter[24] = 0xC3;
		byXorFilter[25] = 0xB1;
		byXorFilter[26] = 0xE9;
		byXorFilter[27] = 0x83;
		byXorFilter[28] = 0x29;
		byXorFilter[29] = 0x51;
		byXorFilter[30] = 0xE8;
		byXorFilter[31] = 0x56;	
#endif

		for ( int i = iStart ; i != iEnd ; i+=iDir )
		{
			this->m_byBuffer[i] ^= this->m_byBuffer[i-1] ^ byXorFilter[ i%32 ];
		}
	}

public:

	BOOL AddData(void* pSrc, WORD wSize ) 
	{
		if ( ((this->m_wSize + wSize) >=  2048) ||  (wSize == 0) )
		{
			LogAddC(2,"CStreamPacketEngine Adding Buffer Size Error %d", this->m_wSize + wSize);
			int iSize = 2048;
			return FALSE;
		}

		memcpy((void*)&this->m_byBuffer[this->m_wSize], pSrc, wSize);
		this->m_wSize += wSize;
		return TRUE;
	}

	BOOL ExtractPacket(void* pTar)
	{
		WORD wSize;
		BYTE byXorFilter[32];

		BYTE byTemp[2048];

		

		switch ( this->m_byBuffer[0] )
		{
			case 0xC1:
			#if(ENABLE_INDEV_NETWORK)
			case 0xC3:
			#endif
				wSize = this->m_byBuffer[1];
				break;

			case 0xC2:
			#if(ENABLE_INDEV_NETWORK)
			case 0xC4:
			#endif
				wSize = this->m_byBuffer[1] * 256 + this->m_byBuffer[2];
				break;

			default:
				return true;
				break;
		}

		if ( this->m_wSize < wSize )
		{
			return 2;
		}

//#if(ENABLE_INDEV_NETWORK)
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
//#else
//
//		byXorFilter[0] = 0xE7;
//		byXorFilter[1] = 0x6D;
//		byXorFilter[2] = 0x3A;
//		byXorFilter[3] = 0x89;
//		byXorFilter[4] = 0xBC;
//		byXorFilter[5] = 0xB2;
//		byXorFilter[6] = 0x9F;
//		byXorFilter[7] = 0x73;
//		byXorFilter[8] = 0x23;
//		byXorFilter[9] = 0xA8;
//		byXorFilter[10] = 0xFE;
//		byXorFilter[11] = 0xB6;
//		byXorFilter[12] = 0x49;
//		byXorFilter[13] = 0x5D;
//		byXorFilter[14] = 0x39;
//		byXorFilter[15] = 0x5D;
//		byXorFilter[16] = 0x8A;
//		byXorFilter[17] = 0xCB;
//		byXorFilter[18] = 0x63;
//		byXorFilter[19] = 0x8D;
//		byXorFilter[20] = 0xEA;
//		byXorFilter[21] = 0x7D;
//		byXorFilter[22] = 0x2B;
//		byXorFilter[23] = 0x5F;
//		byXorFilter[24] = 0xC3;
//		byXorFilter[25] = 0xB1;
//		byXorFilter[26] = 0xE9;
//		byXorFilter[27] = 0x83;
//		byXorFilter[28] = 0x29;
//		byXorFilter[29] = 0x51;
//		byXorFilter[30] = 0xE8;
//		byXorFilter[31] = 0x56;	
//
//#endif

		#if(ENABLE_INDEV_NETWORK)
		if(this->m_byBuffer[0] == 0xC1 || this->m_byBuffer[0] == 0xC3)
		{
			this->XorData(wSize-1, 2, -1);
			//if(!this->XorData(wSize-1, 2, -1))
			{
			//	return true;
			}
		}
		else if(this->m_byBuffer[0] == 0xC2 || this->m_byBuffer[0] == 0xC4)
		{
			this->XorData(wSize-1, 3, -1);
			//if(!this->XorData(wSize-1, 3, -1))
			{
			//	return true;
			}
		}
		#else
		this->XorData(wSize-1, (this->m_byBuffer[0] == 0xC1 ? 2 : 3), -1);
		#endif

		memcpy(pTar, this->m_byBuffer, wSize);
		this->m_wSize-=wSize;
		memcpy(byTemp, &this->m_byBuffer[wSize], this->m_wSize);
		memcpy(this->m_byBuffer, byTemp, this->m_wSize);
		return false;
	}

private:
	WORD m_wSize;	// 4
	BYTE m_byBuffer[2048];	// 6
	
};

#endif