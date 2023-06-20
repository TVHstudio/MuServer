#include "stdafx.h"
#include "ZtText.h"

#if(CUSTOM_ZTTEXT)

CZtText g_ZtText;

CZtText::CZtText()
{
	this->Init();
}

CZtText::~CZtText()
{
}

void CZtText::Init()
{
	memset(this->m_Text, 0, sizeof(this->m_Text));
}

void CZtText::Load()
{
	this->Init();
	this->Read(".\\Data\\ZtData\\ZtTextC.dat");
}

void CZtText::Read(char* filename)
{
	GetPrivateProfileString("ZtTeam", "Text0", "Open Menu", this->m_Text[0], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text1", "3D Camera [Reset]", this->m_Text[1], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text2", "3D Camera [Switch]", this->m_Text[2], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text3", "JewelsBank", this->m_Text[3], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text4", "Graphics Effect", this->m_Text[4], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text5", "Party Hp Bar", this->m_Text[5], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text6", "User Hp Bar", this->m_Text[6], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text7", "Monster Hp Bar", this->m_Text[7], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text8", "Rage System", this->m_Text[8], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text9", "Offline Attack", this->m_Text[9], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text10", "Top 100 Player", this->m_Text[10], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text11", "Events Timer", this->m_Text[11], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text12", "Party Show", this->m_Text[12], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text13", "Auto Party", this->m_Text[13], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text14", "Party Search List", this->m_Text[14], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text15", "Close Menu", this->m_Text[15], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text16", "Local:", this->m_Text[16], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text17", "L:%d HP:%d", this->m_Text[17], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text18", "HP: %d", this->m_Text[18], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text19", "L:%d R:%d G:%d", this->m_Text[19], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text20", "HP : %d0%%", this->m_Text[20], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text21", "Lvl:%d | R:%d | GR:%d", this->m_Text[21], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text22", "Level: %d | Reset: %d", this->m_Text[22], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text23", "Auto Party List", this->m_Text[23], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text24", "Close", this->m_Text[24], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text25", "Hello Player", this->m_Text[25], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text26", "It is a system to search for the party", this->m_Text[26], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text27", "N", this->m_Text[27], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text28", "Player", this->m_Text[28], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text29", "Level", this->m_Text[29], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text30", "Map", this->m_Text[30], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text31", "X", this->m_Text[31], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text32", "Y", this->m_Text[32], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text33", "Count", this->m_Text[33], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text34", "Page: %d/%d", this->m_Text[34], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text35", "Blood Castle:", this->m_Text[35], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text36", "Devil Square:", this->m_Text[36], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text37", "Chaos Castle:", this->m_Text[37], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text38", "Golden Dragon:", this->m_Text[38], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text39", "White Wizard:", this->m_Text[39], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text40", "Premium:", this->m_Text[40], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text41", "Chaos:", this->m_Text[41], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text42", "Bless:", this->m_Text[42], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text43", "Soul:", this->m_Text[43], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text44", "Life:", this->m_Text[44], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text45", "Createon:", this->m_Text[45], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text46", "Credit:", this->m_Text[46], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text47", "Zen:", this->m_Text[47], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text48", "(N)", this->m_Text[48], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text49", "Name", this->m_Text[49], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text50", "Class", this->m_Text[50], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text51", "Level", this->m_Text[51], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text52", "Reset", this->m_Text[52], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text53", "Grand", this->m_Text[53], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text54", "Strength", this->m_Text[54], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text55", "Agility", this->m_Text[55], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text56", "Vitality", this->m_Text[56], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text57", "Energy", this->m_Text[57], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text58", "Command", this->m_Text[58], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text59", "Guild", this->m_Text[59], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text60", "Dark Wizard", this->m_Text[60], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text61", "Soul Master", this->m_Text[61], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text62", "Grand Master", this->m_Text[62], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text63", "Dark Knight", this->m_Text[63], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text64", "Blade Knight", this->m_Text[64], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text65", "Blade Master", this->m_Text[65], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text66", "Fairy Elf", this->m_Text[66], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text67", "Muse Elf", this->m_Text[67], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text68", "High Elf", this->m_Text[68], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text69", "Magic Gladiator", this->m_Text[69], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text70", "Duel Master", this->m_Text[70], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text71", "Dark Lord", this->m_Text[71], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text72", "Lord Emperial", this->m_Text[72], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text73", "Summoner", this->m_Text[73], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text74", "Bloody Summoner", this->m_Text[74], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text75", "Dimension Master", this->m_Text[75], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text76", "Rage Fighter", this->m_Text[76], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text77", "Fist Master", this->m_Text[77], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text78", "News", this->m_Text[78], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text79", "Back", this->m_Text[79], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text80", "Life: %d/%d", this->m_Text[80], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text81", "Mana: %d/%d", this->m_Text[81], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text82", "SD: %d/%d", this->m_Text[82], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text83", "AG: %d/%d", this->m_Text[83], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text84", "Ignor opponent's defensive power by %d%%", this->m_Text[84], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text85", "Return's the enemy's attack power in %d%%", this->m_Text[85], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text86", "Complete recoy of life in %d%% rate", this->m_Text[86], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text87", "Complete reco of Mana in %d%% rate", this->m_Text[87], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text88", "Sell Price: %s Zen", this->m_Text[88], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text89", "Sell Price: %s Credit", this->m_Text[89], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text90", "Sell Price: %s WCoin", this->m_Text[90], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text91", "Sell Price: %s WCoin(P)", this->m_Text[91], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text92", "Sell Price: %s Goblin Point", this->m_Text[92], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text93", "Buy Price: %s Zen", this->m_Text[93], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text94", "Buy Price: %d Zen", this->m_Text[94], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text95", "Buy Price: %d,%03d Zen", this->m_Text[95], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text96", "Buy Price: %d,%03d,%03d Zen", this->m_Text[96], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text97", "Buy Price: %d,%03d,%03d,%03d Zen", this->m_Text[97], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text98", "Buy Price: %d Credit", this->m_Text[98], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text99", "Buy Price: %d,%03d Credit", this->m_Text[99], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text100", "Buy Price: %d,%03d,%03d Credit", this->m_Text[100], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text101", "Buy Price: %d,%03d,%03d,%03d Credit", this->m_Text[101], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text102", "Buy Price: %d WCoin", this->m_Text[102], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text103", "Buy Price: %d,%03d WCoin", this->m_Text[103], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text104", "Buy Price: %d,%03d,%03d WCoin", this->m_Text[104], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text105", "Buy Price: %d,%03d,%03d,%03d WCoin", this->m_Text[105], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text106", "Buy Price: %d WCoin(P)", this->m_Text[106], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text107", "Buy Price: %d,%03d WCoin(P)", this->m_Text[107], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text108", "Buy Price: %d,%03d,%03d WCoin(P)", this->m_Text[108], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text109", "Buy Price: %d,%03d,%03d,%03d WCoin(P)", this->m_Text[109], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text106", "Buy Price: %d Goblin Points", this->m_Text[110], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text107", "Buy Price: %d,%03d Goblin Points", this->m_Text[111], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text108", "Buy Price: %d,%03d,%03d Goblin Points", this->m_Text[112], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text109", "Buy Price: %d,%03d,%03d,%03d Goblin Points", this->m_Text[113], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text114", "Reconnecting...", this->m_Text[114], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text115", "Relogin...", this->m_Text[115], 128, filename);

	//

	GetPrivateProfileString("ZtTeam", "Text116", "Active System", this->m_Text[116], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text117", "Max Level", this->m_Text[117], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text118", "Auto Party", this->m_Text[118], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text119", "Only One Class (Gold)", this->m_Text[119], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text120", "Ok", this->m_Text[120], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text121", "[SELL]", this->m_Text[121], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text122", "Add Points", this->m_Text[122], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text123", "Free Points:", this->m_Text[123], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text124", "Strength:", this->m_Text[124], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text125", "Agility:", this->m_Text[125], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text126", "Vitality:", this->m_Text[126], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text127", "Energy:", this->m_Text[127], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text128", "Command:", this->m_Text[128], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text129", "Cancel", this->m_Text[129], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text130", "Grand Reset", this->m_Text[130], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text131", "Quick add stats", this->m_Text[131], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text132", "Reset Stats", this->m_Text[132], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text133", "Reset stats Premium free", this->m_Text[133], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text134", "Reset stats for %d WCoin", this->m_Text[134], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text135", "Reset stats for %d Credits", this->m_Text[135], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text136", "Reward Stats", this->m_Text[136], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text137", "Accept", this->m_Text[137], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text138", "Personal Shop Search", this->m_Text[138], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text139", "Price", this->m_Text[139], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text140", "Wcoin:", this->m_Text[140], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text141", "Party Search", this->m_Text[141], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text142", "join", this->m_Text[142], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text143", "Need to Party:", this->m_Text[143], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text144", "Dark Wizard", this->m_Text[144], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text145", "Dark Knight", this->m_Text[145], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text146", "Elf", this->m_Text[146], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text147", "Magic Gladiator", this->m_Text[147], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text148", "Dark Lord", this->m_Text[148], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text149", "Summoner", this->m_Text[149], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text150", "Rage Fighter", this->m_Text[150], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text151", "Premium System", this->m_Text[151], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text152", "Premium Status:", this->m_Text[152], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text153", "Premium Time:", this->m_Text[153], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text154", "Bronze Premium Buff", this->m_Text[154], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text155", "Silver Premium Buff", this->m_Text[155], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text156", "Gold Premium Buff", this->m_Text[156], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text157", "Premium Day", this->m_Text[157], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text158", "Required WCoin:", this->m_Text[158], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text159", "Premium Day", this->m_Text[159], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text160", "Buy Premium", this->m_Text[160], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text161", "Level: %d", this->m_Text[161], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text162", "Bronze", this->m_Text[162], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text163", "Silver", this->m_Text[163], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text164", "Gold", this->m_Text[164], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text165", "No", this->m_Text[165], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text166", "Day: %2d Hour: %2d Minutes: %2d Seconds: %2d", this->m_Text[166], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text167", "Day: %2d Hour: %2d Min: %2d", this->m_Text[167], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text168", "Day: %2d Hour: %2d", this->m_Text[168], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text169", "Hour: %2d Minutes: %2d Seconds: %2d", this->m_Text[169], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text170", "Hour: %2d Min: %2d", this->m_Text[170], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text171", "Hour: %2d", this->m_Text[171], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text172", "Minutes: %2d Seconds: %2d", this->m_Text[172], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text173", "Min: %2d", this->m_Text[173], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text174", "Seconds: %2d", this->m_Text[174], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text175", "Sec: %2d", this->m_Text[175], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text176", "Price: %s Zen", this->m_Text[176], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text177", "Price: %d Credit", this->m_Text[177], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text178", "Price: %d WCoin", this->m_Text[178], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text179", "Price: %d Bless", this->m_Text[179], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text180", "Price: %d Soul", this->m_Text[180], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text181", "Price: %d Chaos", this->m_Text[181], 128, filename);
	GetPrivateProfileString("ZtTeam", "Text182", "Price: %d Life", this->m_Text[182], 128, filename);

	GetPrivateProfileString("ZtTeam", "Text183", "Cash Shop", this->m_Text[183], 128, filename);
}

char* CZtText::GetText(int number)
{
	if(number < 0 || number >= MAX_ZTTEXT)
	{
		return "Error";
	}

	return this->m_Text[number];
}


/*
g_ZtText.GetText(number)
*/

#endif