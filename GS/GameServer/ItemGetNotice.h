#pragma once
#define MAX_MESSAGE_SIZE 255
struct DATA_ITEMGET
{
	int IDItem;
	int SkillCheck;
	int LuckCheck;
	int OptionCheck;
	int ExcCheck;
	int AncCheck;
	int ColorMess;
	int TextID;
};
struct DATA_TEXT
{
	int Index;
	char Message[256];
};
class CItemGetNotice
{
public:
	CItemGetNotice();
	~CItemGetNotice();

	void Init();
	void Read();
	std::vector<DATA_ITEMGET> m_ItemGetNotice;
	DATA_ITEMGET* CheckItemGetNotice(CMapItem* lpMapItem);
	//===Mess
	std::map<int, DATA_TEXT> m_TextData;
	char* GetMessage(int index);
	void  ItemGetNotice(CMapItem* lpMapItem, int aIndex);
};

extern CItemGetNotice g_ItemGetNotice;