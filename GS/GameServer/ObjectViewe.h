#pragma once

#if(FIX_OBJECT_VIEWE)

struct PMSG_OBJECT_LIVE
{
	PBMSG_HEAD2 h;
	int ObjectIndex;
	WORD ObjectType;
	BYTE ObjectLive;
};

class CObjectViewe
{
public:
		CObjectViewe();
		~CObjectViewe();

	void Load();
	
	void GCIndexLive(int UserIndex, int ObjectIndex, WORD ObjectType, BYTE ObjectLive);

	bool m_Active;
};

extern CObjectViewe g_ObjectViewe;


#endif