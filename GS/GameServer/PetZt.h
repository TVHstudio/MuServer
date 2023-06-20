#pragma once

#if(ENABLE_PETZT)

#define MAX_PETZT_COUNT		100
#define MAX_PETZT_OPTION	5

enum
{
	ePET_NONE,
	ePET_DAMAGE,
	ePET_DEFENCE,
	ePET_IGNOREDEFENCE,
	ePET_CRITICALDAMAGE,
	ePET_EXELLENTDAMAGEe,
	ePET_DOUBLEDAMAGE,
	ePET_DECRISEDAMAGE,
	ePET_REFLECTDAMAGE,
	ePET_SD,
	ePET_LIFE,
	ePET_MAGICDAMAGE, 
	ePET_EXPERIENCE,
	ePET_ZENMONEY,
};

struct PETZT_OPTION
{
	int Type;
	int Value;
};

struct PETZT_DATA
{
	int Active;
	int ItemType;
	int ItemIndex;
	PETZT_OPTION Option[MAX_PETZT_OPTION];
};

struct PETZT_IMMORTAL
{
	int Active;
	int ItemType;
	int ItemIndex;
};

class CPetZt
{
public:
		 CPetZt();
		 ~CPetZt();

	void Init();
	void Load();
	void Read(char* filename);
	bool IsPet(int ItemType);
	bool IsPetImmortal(int ItemType);
	PETZT_DATA* GetPetData(int ItemID);
	bool PetLife(int aIndex);
	void Calc(int aIndex);
	void Exp(int aIndex, __int64 & exp);
	void Zen (int aIndex, float & money);

	int m_Enable;
	int m_PetCount;
	int m_ImmortalCount;
	PETZT_DATA m_Data[MAX_PETZT_COUNT];
	PETZT_IMMORTAL m_Immoirtal[MAX_PETZT_COUNT];
};

extern CPetZt g_PetZt;

#endif