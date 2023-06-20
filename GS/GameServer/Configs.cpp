#include "StdAfx.h"
#include "Configs.h"
#include "Reset.h"
#include "OffExp.h"
#include "GrandReset.h"
#include "HappyHour.h"
#include "OffTrade.h"
#include "ZtQuestSystem.h"
#include "DropZenManager.h"
#include "MapExp.h"
#include "PvPMapSystem.h"
#include "PriceManager.h"
#include "DropEvent.h"
#include "SearchEvent.h"
#include "PremiumSystem.h"
#include "SystemOfRage.h"
#include "NewJewels.h"
#include "ItemDropManager.h"
#include "BlockMoveItem.h"
#include "OnlineBonus.h"
#include "JewelsBank.h"
#include "logproc.h"
#include "Voter.h"
#include "CreditDonate.h"
#include "WinQuestSystem.h"
#include "ExclusiveOptions.h"
#include "ZtLicense.h"
#include "TeleportManager.h"
#include "MaxPower.h"
#include "EventTimer.h"
#include "MonsterBonus.h"
#include "ChaosMixManager.h"
#include "ObjCalCharacter.h"
#include "MixOption.h"
#include "MonsterQuest.h"
#include "BloodHound.h"
#include "TvTEvent.h"
#if(GRAND_HERO_DEV)
#include "GrandHeroSystem.h"
#endif
#ifdef _BALANS_SYSTEM_
#include "BalanceSystem.h"
#endif
#include "Functions.h"
#ifdef DS_REWARD_ITEM
#include "DevilSquareRewardItem.h"
#include "BloodCastleRewardItem.h"
#endif // DS_REWARD_ITEM

#ifdef _WINGS_DAMAGE_
#include "WingsDamage.h"
#endif
#ifdef BOSS_REWARD_ITEM
#include "BossRewardItem.h"
#endif // BOSS_REWARD_ITEM
#ifdef PARTY_BONUS
#include "PartyBonus.h"
#endif
#include "MonsterSpawner.h"
#include "CustomNpc.h"
#include "AlertSystem.h"
#include "Brotherhood.h"
#include "TeleportShop.h"
#ifdef LORA_BATTLE_EVENT
#include "LoraBattle.h"
#endif // LORA_BATTLE_EVENT
#include "PandoraBoxEvent.h"
#include "NewsBoard.h"
#include "ComboCustom.h"
#include "Smithy.h"
#include "Marriage.h"
#include "DeviasBattle.h"
#include "ChaosCastleRewardItem.h"
#include "UserConfig.h"
#ifdef CALCULATOR_MANAGER
#include "CalculatorManager.h"
#endif

cZtConfigs ZtConfig;
#ifdef ZT_RELOAD_RAGE_SILVER
void cZtConfigs::LoadConfigs(bool isExReload)
#else
void cZtConfigs::LoadConfigs()
#endif
{
	g_UserConfig.Load();

#if(CUSTOM_SMITHY == TRUE)
	g_Smithy.Load();
#endif

	g_TeleportShop.Load();

	if(g_ZtLicense.user.BloodHound)
	{
		BloodHound.ReedConfig();
	}

	gResetSystem.Load();
	OffExp.LoadConfig();
	gGrandReset.Load();
	HappyHour.LoadConfig();

#ifdef _OFFTRADE_
	gOffTrade.Load();
#endif
	ZtQuestSystem.Loader();
	DropZenManager.LoadConfig();

	gMapExp.LoadConfig();

	PvPMapSystem.LoadConfig();

	PriceManager.LoadConfig();
	DropEvent.LoadFile();
	SearchEvent.LoadingEvent();
	Premium.Loader();
#ifdef ZT_RELOAD_RAGE_SILVER
	if(g_ZtLicense.CheckUser(eZtUB::Local3) || g_ZtLicense.CheckUser(SILVER1) || g_ZtLicense.CheckUser(SILVER2))
	{
		if(	g_ZtLicense.user.Rage && (!isExReload)	)
		{
			gSystemOfRage.Load();
		}
	}
	else
	{
		if(g_ZtLicense.user.Rage)
		{
			gSystemOfRage.Load();
		}
	}
#else
	if(g_ZtLicense.user.Rage)
		{
			gSystemOfRage.Load();
		}
#endif

	gBlockMoveIteml.Load();

	gItemDropManager.Init();

	gNewJewels.Load();

	gOnlineBonus.Load();
	gJewelsBank.Load();
#ifdef _VOTER_
	gVoter.Init();
#endif
	gCreditDonate.Load();

	if(g_ZtLicense.user.WinQuest)
	{
		gWinQuestSystem.Init();
	}

	gExclusiveOptions.Load();

	gTeleportManager.Load();

	gMaxPower.Load();

	gEventTimer.LoadTimer();

	gMonsterBonus.Load();

	ChaosMixManager.Init();

	g_MixOption.Load();
#ifdef PRIVATE_MODULE
	if(g_ZtLicense.user.MonsterQuest)
	{
		gMonsterQuest.Load();
	}
#endif

	if(g_ZtLicense.user.TvTEvent)
	{
		TvT.Load();
	}
#if(GRAND_HERO_DEV)
	GrandHero.Load();
#endif
#ifdef _BALANS_SYSTEM_
	gBalanceSystem.Load();
#endif

	
#ifdef CALCULATOR_MANAGER
	if (g_ZtLicense.CheckUser(eZtUB::ulasevich) || g_ZtLicense.CheckUser(eZtUB::ConflictNoCustom) || g_ZtLicense.CheckUser(eZtUB::ulasevich2))
	{
		CalculatorManager.Load();
	}
#endif
	


#ifdef DS_REWARD_ITEM
	gDevilSquareRewardItem.Load();
	gBloodCastleRewardItem.Load();
#endif // DS_REWARD_ITEM
	gChaosCastleRewardItem.Load();
#ifdef _WINGS_DAMAGE_
	gWingsDamage.Load();
#endif // _WINGS_DAMAGE_
#ifdef BOSS_REWARD_ITEM
	gBossRewardItem.Init();
#endif // BOSS_REWARD_ITEM
	gCustomNpc.Load();
#ifdef LORA_BATTLE_EVENT
	//if(g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2))
	{
		LoraBattle.LoadConfigs();
	}
#endif // LORA_BATTLE_EVENT

#if(EVENT_DEVIASBATTLE)
	if(g_ZtLicense.CheckUser(eZtUB::Gredy) || g_ZtLicense.CheckUser(eZtUB::GredyLocal) || g_ZtLicense.CheckUser(eZtUB::Gredy2))
	{
		g_DeviasBattle.LoadConfigs();
	}
#endif

	if(g_ZtLicense.CheckUser(eZtUB::ulasevich) || g_ZtLicense.CheckUser(eZtUB::ConflictNoCustom) || g_ZtLicense.CheckUser(eZtUB::ulasevich2))
	{
		gMonsterSpawner.Load();
#ifdef PARTY_BONUS
		gPartyBonus.Load();
#endif
	}
	#if(LICENSE_UKRAINE)
	else if(g_ZtLicense.CheckUser(eZtUB::AlterMU))
	{
		gMonsterSpawner.Load();
	}
#endif
	AlertSystem.Load();



#if(SYSTEMOF_BROTHER==TRUE)
	gBrotherhood.Load();
#endif
#ifdef PANDORA_EVENT
	if (g_ZtLicense.user.PandoraEvent)
	{
		gPandoraBoxEvent.Load();
	}
#endif // PANDORA_EVENT
#if(CUSTOM_NEWS==TRUE)
	g_NewsBoard.Load();
#endif // NEWS_BOARD

#if(DEV_COMBO_CUSTOM==TRUE)
	g_ComboCustom.Load();
#endif

#if(CUSTOM_MARRIAGE)
	g_Marriage.Load();
#endif
	//----------------

	this->ZtCustom.SwitchChar = GetPrivateProfileInt("ZtTeam","SwitchChar",0,ZtCustom_DIR);
	this->ZtCustom.HelperClickerLevel = GetPrivateProfileInt("ZtTeam","HelperClickerLevel",80,ZtCustom_DIR);

	this->ZtCustom.AutoParty = GetPrivateProfileInt("ZtTeam","AutoParty",1,ZtCustom_DIR);
	this->ZtCustom.Top100 = GetPrivateProfileInt("ZtTeam","Top100",1,ZtCustom_DIR);
	
	this->ZtCustom.MoveTargetPosEffect = GetPrivateProfileInt("ZtTeam","MoveTargetPosEffect",1,ZtCustom_DIR);
	this->ZtCustom.ClientAntiCheat = GetPrivateProfileInt("ZtTeam","ClientAntiCheat",0,ZtCustom_DIR);

	this->ZtCustom.EnableHPBar = GetPrivateProfileInt("ZtTeam","EnableHPBar",1,ZtCustom_DIR);
	
	this->ZtCustom.CreateMGLevel	= GetPrivateProfileInt("ZtTeam", "CreateMGLevel", 220, ZtCustom_DIR);
	this->ZtCustom.CreateDLLevel	= GetPrivateProfileInt("ZtTeam", "CreateDLLevel", 250, ZtCustom_DIR);
	this->ZtCustom.CreateSUMLevel	= GetPrivateProfileInt("ZtTeam", "CreateSUMLevel", 150, ZtCustom_DIR);
	this->ZtCustom.CreateMONKLevel	= GetPrivateProfileInt("ZtTeam", "CreateMONKLevel", 180, ZtCustom_DIR);
	
	this->ZtCustom.DLReflect = GetPrivateProfileInt("ZtTeam", "DLReflect", 0, ZtCustom_DIR);
	this->ZtCustom.MasterSkills = GetPrivateProfileInt("ZtTeam", "MasterSkills", 1, ZtCustom_DIR);
	this->ZtCustom.DivFireScreamSpeed = GetPrivateProfileInt("ZtTeam", "DivFireScreamSpeed", 1, ZtCustom_DIR);

	this->ZtCustom.PostItem = GetPrivateProfileInt("ZtTeam", "PostItem", 0, ZtCustom_DIR);
	this->ZtCustom.DonateShop = GetPrivateProfileInt("ZtTeam", "DonateShop", 0, ZtCustom_DIR);
	
	this->ZtCustom.MultiWarehouse = GetPrivateProfileInt("ZtTeam", "MultiWarehouse", 0, ZtCustom_DIR);

	this->ZtCustom.MaxLevel = GetPrivateProfileInt("ZtTeam", "MaxLevel", 400, ZtCustom_DIR);

	
	//----------------
	// CommonServer
	//----------------

	this->CommonServer.EnableCheckSum = GetPrivateProfileInt("ZtTeam","CheckSum",0,CommonServer_DIR);
	this->CommonServer.Zt_PersonalID = GetPrivateProfileInt("ZtTeam","PersonalID",0,CommonServer_DIR);
	this->CommonServer.DeleteLogs = GetPrivateProfileInt("ZtTeam","DeleteLogs",0,CommonServer_DIR);

	//this->CommonServer.Zt_LifeRate = GetPrivateProfileInt("JewelRates","LifeRate",50,CommonServer_DIR);
	//this->CommonServer.Zt_SoulRate = GetPrivateProfileInt("JewelRates","SoulRate",50,CommonServer_DIR);
	//this->CommonServer.Zt_SoulRateLuck = GetPrivateProfileInt("JewelRates","SoulRateLuck",20,CommonServer_DIR);
	
	this->CommonServer.ZtMixNormal10SuccessRate = GetPrivateProfileInt("ZtTeam","MixNormal10SuccessRate",60,CommonServer_DIR);
	this->CommonServer.ZtMix380AncExc10SuccessRate = GetPrivateProfileInt("ZtTeam","Mix380AncExc10SuccessRate",50,CommonServer_DIR);
	this->CommonServer.ZtMixSocket10SuccessRate = GetPrivateProfileInt("ZtTeam","MixSocket10SuccessRate",40,CommonServer_DIR);
	this->CommonServer.ZtMixNormal11SuccessRate = GetPrivateProfileInt("ZtTeam","MixNormal11SuccessRate",60,CommonServer_DIR);
	this->CommonServer.ZtMix380AncExc11SuccessRate = GetPrivateProfileInt("ZtTeam","Mix380AncExc11SuccessRate",50,CommonServer_DIR);
	this->CommonServer.ZtMixSocket11SuccessRate = GetPrivateProfileInt("ZtTeam","MixSocket11SuccessRate",40,CommonServer_DIR);
	this->CommonServer.ZtMixNormal12SuccessRate = GetPrivateProfileInt("ZtTeam","MixNormal12SuccessRate",60,CommonServer_DIR);
	this->CommonServer.ZtMix380AncExc12SuccessRate = GetPrivateProfileInt("ZtTeam","Mix380AncExc12SuccessRate",50,CommonServer_DIR);
	this->CommonServer.ZtMixSocket12SuccessRate = GetPrivateProfileInt("ZtTeam","MixSocket12SuccessRate",40,CommonServer_DIR);
	this->CommonServer.ZtMixNormal13SuccessRate = GetPrivateProfileInt("ZtTeam","MixNormal13SuccessRate",55,CommonServer_DIR);
	this->CommonServer.ZtMix380AncExc13SuccessRate = GetPrivateProfileInt("ZtTeam","Mix380AncExc13SuccessRate",50,CommonServer_DIR);
	this->CommonServer.ZtMixSocket13SuccessRate = GetPrivateProfileInt("ZtTeam","MixSocket13SuccessRate",35,CommonServer_DIR);

	//Season 5 +15 Items
	this->CommonServer.ZtMixNormal14SuccessRate = GetPrivateProfileInt("ZtTeam","MixNormal14SuccessRate",55,CommonServer_DIR);
	this->CommonServer.ZtMix380AncExc14SuccessRate = GetPrivateProfileInt("ZtTeam","Mix380AncExc14SuccessRate",50,CommonServer_DIR);
	this->CommonServer.ZtMixSocket14SuccessRate = GetPrivateProfileInt("ZtTeam","MixSocket14SuccessRate",35,CommonServer_DIR);
	this->CommonServer.ZtMixNormal15SuccessRate = GetPrivateProfileInt("ZtTeam","MixNormal15SuccessRate",55,CommonServer_DIR);
	this->CommonServer.ZtMix380AncExc15SuccessRate = GetPrivateProfileInt("ZtTeam","Mix380AncExc15SuccessRate",50,CommonServer_DIR);
	this->CommonServer.ZtMixSocket15SuccessRate = GetPrivateProfileInt("ZtTeam","MixSocket15SuccessRate",35,CommonServer_DIR);

	this->CommonServer.ZtMixLuckOptRateAdd = GetPrivateProfileInt("ZtTeam","MixLuckOptRateAdd",20,CommonServer_DIR);
	this->CommonServer.ZtMixMaxSuccessRate = GetPrivateProfileInt("ZtTeam","MixMaxSuccessRate",75,CommonServer_DIR);
	this->CommonServer.ZtWing2MaxSuccessRate = GetPrivateProfileInt("ZtTeam","Wing2MaxSuccessRate",90,CommonServer_DIR);
	this->CommonServer.ZtDarkHorseMixSuccessRate = GetPrivateProfileInt("ZtTeam","DarkHorseMixSuccessRate",60,CommonServer_DIR);
	this->CommonServer.ZtDarkSpiritMixSuccessRate = GetPrivateProfileInt("ZtTeam","DarkSpiritMixSuccessRate",60,CommonServer_DIR);
	this->CommonServer.ZtFeatherofCondorMixMaxPercent = GetPrivateProfileInt("ZtTeam","FeatherofCondorMixMaxPercent",60,CommonServer_DIR);
	this->CommonServer.ZtWingLv3MixMaxPercent = GetPrivateProfileInt("ZtTeam","WingLv3MixMaxPercent",40,CommonServer_DIR);
	this->CommonServer.ZtDinorantMixRate = GetPrivateProfileInt("ZtTeam","DinorantMixRate",70,CommonServer_DIR);

	this->CommonServer.Wing2_5MaxSuccessRate = GetPrivateProfileInt("ZtTeam","Wing2_5MaxSuccessRate",60,CommonServer_DIR);
	this->CommonServer.Wing4MaxSuccessRate = GetPrivateProfileInt("ZtTeam","Wing4MaxSuccessRate",40,CommonServer_DIR);
	this->CommonServer.Wing5MaxSuccessRate = GetPrivateProfileInt("ZtTeam","Wing5MaxSuccessRate",40,CommonServer_DIR);

	this->CommonServer.Zt_MasterDropZen = GetPrivateProfileInt("ZtTeam","MasterDropZen",100,CommonServer_DIR);

	GetPrivateProfileString("Guard", "GuardMessage","Welcome to Ex-Games",this->CommonServer.GuardMessage,50,CommonServer_DIR);

	this->CommonServer.KundunAncDrop = GetPrivateProfileInt("ZtTeam","KundunAncDrop",2500,CommonServer_DIR);

	this->CommonServer.DisatanceObjViewe = GetPrivateProfileInt("ZtTeam","DisatanceObjViewe",15,CommonServer_DIR);

	this->CommonServer.MarlonQuestReset = GetPrivateProfileInt("ZtTeam","MarlonQuestReset",0,CommonServer_DIR);

	this->CommonServer.MaxDropZen = GetPrivateProfileInt("ZtTeam","MaxDropZen",1000000,CommonServer_DIR);
	this->CommonServer.ProcentDropZen = GetPrivateProfileInt("ZtTeam", "ProcentDropZen", 100, CommonServer_DIR);
	if (this->CommonServer.ProcentDropZen <= 0)
	{
		this->CommonServer.ProcentDropZen = 0;
	}

	this->CommonServer.CountItemDropSelupan = GetPrivateProfileInt("ZtTeam","CountItemDropSelupan",10,CommonServer_DIR);
	this->CommonServer.CountItemDropKundun = GetPrivateProfileInt("ZtTeam","CountItemDropKundun",3,CommonServer_DIR);
	this->CommonServer.CountItemDropErohim = GetPrivateProfileInt("ZtTeam","CountItemDropErohim",1,CommonServer_DIR);

#if(_NEW_PT_SYSTEM_	==1)
	this->CommonServer.RePartyEnable = GetPrivateProfileInt("ZtTeam","RePartyEnable",0,CommonServer_DIR);
	this->CommonServer.RePartyTime = GetPrivateProfileInt("ZtTeam","RePartyTime",10,CommonServer_DIR) * 3600;
	this->CommonServer.AutoSetLeader = GetPrivateProfileInt("ZtTeam","AutoSetLeader",1,CommonServer_DIR);
	this->CommonServer.CommandSetLeader = GetPrivateProfileInt("ZtTeam","CommandSetLeader",1,CommonServer_DIR);
#endif

#if(_ARENA_ITEM_)
	this->CommonServer.ArenaItem = GetPrivateProfileInt("ZtTeam","ArenaItem",-1,CommonServer_DIR);
#endif

	this->CommonServer.ReConnect = GetPrivateProfileInt("ZtTeam","ReConnect",1,CommonServer_DIR);
	
	this->CommonServer.ExlDropRate = GetPrivateProfileInt("ZtTeam","ExlDropRate",10,CommonServer_DIR);
	this->CommonServer.PercentKillZen  = GetPrivateProfileInt("ZtTeam","PercentKillZen",10,CommonServer_DIR);

#if(CUSTOM_NOOBBUFF)
	this->CommonServer.bNoobBuffEnable = GetPrivateProfileInt("ZtTeam","NoobBuffEnable",0,CommonServer_DIR);
	this->CommonServer.iNoobBuffMaxReset = GetPrivateProfileInt("ZtTeam","NoobBuffMaxReset",1,CommonServer_DIR);
	this->CommonServer.m_NoobDamage = GetPrivateProfileInt("ZtTeam","NoobBuffDamagePercent",15,CommonServer_DIR);
	this->CommonServer.m_NoobDefence = GetPrivateProfileInt("ZtTeam","NoobBuffDefencePercent",15,CommonServer_DIR);
#endif

#if(CUSTOM_POTIONTICK)
	this->CommonServer.PotionDelay = GetPrivateProfileInt("ZtTeam","PotionDelay",0,CommonServer_DIR);
#endif

	this->CommonServer.MarlonTeleport = GetPrivateProfileInt("ZtTeam","MarlonTeleport",1,CommonServer_DIR);
	this->CommonServer.CheckOtherGuildLand = GetPrivateProfileInt("ZtTeam","CheckOtherGuildLand",0,CommonServer_DIR);
	
#if(WAITENI_CUSTOM)
	this->CommonServer.DurabilityEnable = GetPrivateProfileInt("ZtTeam","DurabilityEnable",1,CommonServer_DIR);
	this->CommonServer.DurabilityMaxCount = GetPrivateProfileInt("ZtTeam","DurabilityMaxCount",1,CommonServer_DIR);
	this->CommonServer.BloodCastleCount = GetPrivateProfileInt("ZtTeam","BloodCastleCount",4,CommonServer_DIR);
	this->CommonServer.DevilSqueryCount = GetPrivateProfileInt("ZtTeam","DevilSqueryCount",4,CommonServer_DIR);
#endif
#if(CUSTOM_FLAGS)
	this->CommonServer.Ringstrength = GetPrivateProfileInt("ZtTeam", "Ringstrength", 10, CommonServer_DIR);
#endif
#if(Negative_Number)
	this->CommonServer.MembItemLimit = GetPrivateProfileInt("ZtTeam", "MembItemLimit", 0, CommonServer_DIR);
	this->CommonServer.MembItemMixLimit = GetPrivateProfileInt("ZtTeam", "MembItemMixLimit", 0, CommonServer_DIR);
	this->CommonServer.MembItemWareLimit = GetPrivateProfileInt("ZtTeam", "MembItemWareLimit", 0, CommonServer_DIR);
	this->CommonServer.NorItemLimit = GetPrivateProfileInt("ZtTeam", "NorItemLimit", 0, CommonServer_DIR);
	this->CommonServer.NorItemLevel = GetPrivateProfileInt("ZtTeam", "NorItemLevel", 15, CommonServer_DIR);
	this->CommonServer.NorItemExt = GetPrivateProfileInt("ZtTeam", "NorItemLevel", 6, CommonServer_DIR);
#endif
	this->m_iBloodCastleMaxUser = GetPrivateProfileInt("ZtTeam","BloodCastleMaxUser",1,CommonServer_DIR);
	this->m_iGuildMaxUser = GetPrivateProfileInt("ZtTeam","GuildMaxUser",80,CommonServer_DIR);
	this->m_iAllianceMaxGuild = GetPrivateProfileInt("ZtTeam","AllianceMaxGuild",1,CommonServer_DIR);

	this->m_iExpPartyPlus = GetPrivateProfileInt("ZtTeam","ExpPartyPlus",0,CommonServer_DIR);

	//----------------
	//		Skills
	//----------------



	//----------------------
	//		Character
	//----------------------

	this->Character.NeedArrow = GetPrivateProfileInt("Common","NeedArrow",1,Character_DIR);
	this->Character.CastleSiegeSkillEnable = GetPrivateProfileInt("Common","CastleSiegeSkillEnable",1,Character_DIR);
	this->Character.CastleAttackByNPC = GetPrivateProfileInt("Common","CastleAttackByNPC",20,Character_DIR);
	this->Character.CastleAttackByPlayer = GetPrivateProfileInt("Common","CastleAttackByPlayer",40,Character_DIR);
	this->Character.PetCastleAttackByNPC = GetPrivateProfileInt("Common","PetCastleAttackByNPC",20,Character_DIR);
	this->Character.PetCastleAttackByPlayer = GetPrivateProfileInt("Common","PetCastleAttackByPlayer",40,Character_DIR);
	this->Character.MaxStats = GetPrivateProfileInt("Common", "MaxStats", 65535, Character_DIR);
	this->Character.CastleDamageByAlliance = GetPrivateProfileInt("Common", "CastleDamageByAlliance", 100, Character_DIR);
	this->Character.bReflectToReflect = GetPrivateProfileInt("Common", "ReflectToReflect", 1, Character_DIR);

	this->Character.ComboDamagePercent = GetPrivateProfileInt("Common", "ComboDamagePercent", 100, Character_DIR);
	this->Character.SoulBarrierAttackManaDown = GetPrivateProfileInt("Common", "SoulBarrierAttackManaDown", 1, Character_DIR);

	if(this->Character.CastleDamageByAlliance < 0)
	{
		this->Character.CastleDamageByAlliance = 0;
	}

	this->Character.ELFDamageMax_Bow_StrDexRight = GetPrivateProfileInt("Fairy_Elf","DamageMax_Bow_StrDexRight",4,Character_DIR);
	this->Character.ELFDamageMin_Bow_StrDexRight = GetPrivateProfileInt("Fairy_Elf","DamageMin_Bow_StrDexRight",7,Character_DIR);
	this->Character.ELFDamageMax_Bow_StrDexLeft = GetPrivateProfileInt("Fairy_Elf","DamageMax_Bow_StrDexLeft",4,Character_DIR);
	this->Character.ELFDamageMin_Bow_StrDexLeft = GetPrivateProfileInt("Fairy_Elf","DamageMin_Bow_StrDexLeft",7,Character_DIR);

	this->Character.ELFDamageMax_NoBow_StrRight = GetPrivateProfileInt("Fairy_Elf","DamageMax_NoBow_StrRight",8,Character_DIR);
	this->Character.ELFDamageMax_NoBow_DexRight = GetPrivateProfileInt("Fairy_Elf","DamageMax_NoBow_DexRight",4,Character_DIR);
	this->Character.ELFDamageMin_NoBow_StrRight = GetPrivateProfileInt("Fairy_Elf","DamageMin_NoBow_StrRight",14,Character_DIR);
	this->Character.ELFDamageMin_NoBow_DexRight = GetPrivateProfileInt("Fairy_Elf","DamageMin_NoBow_DexRight",7,Character_DIR);

	this->Character.ELFDamageMax_NoBow_StrLeft = GetPrivateProfileInt("Fairy_Elf","DamageMax_NoBow_StrLeft",8,Character_DIR);
	this->Character.ELFDamageMax_NoBow_DexLeft = GetPrivateProfileInt("Fairy_Elf","DamageMax_NoBow_DexLeft",4,Character_DIR);
	this->Character.ELFDamageMin_NoBow_StrLeft = GetPrivateProfileInt("Fairy_Elf","DamageMin_NoBow_StrLeft",14,Character_DIR);
	this->Character.ELFDamageMin_NoBow_DexLeft = GetPrivateProfileInt("Fairy_Elf","DamageMin_NoBow_DexLeft",7,Character_DIR);

	this->Character.ELFDamageMax_DexStrRight = GetPrivateProfileInt("Fairy_Elf","DamageMax_DexStrRight",4,Character_DIR);
	this->Character.ELFDamageMin_DexStrRight = GetPrivateProfileInt("Fairy_Elf","DamageMin_DexStrRight",7,Character_DIR);
	this->Character.ELFDamageMax_DexStrLeft = GetPrivateProfileInt("Fairy_Elf","DamageMax_DexStrLeft",4,Character_DIR);
	this->Character.ELFDamageMin_DexStrLeft = GetPrivateProfileInt("Fairy_Elf","DamageMin_DexStrLeft",7,Character_DIR);

	//----------------------
	this->Character.DKDamageMax_StrRight = GetPrivateProfileInt("Dark_Knight","DamageMax_StrRight",4,Character_DIR);
	this->Character.DKDamageMin_StrRight = GetPrivateProfileInt("Dark_Knight","DamageMin_StrRight",6,Character_DIR);
	this->Character.DKDamageMax_StrLeft = GetPrivateProfileInt("Dark_Knight","DamageMax_StrLeft",4,Character_DIR);
	this->Character.DKDamageMin_StrLeft = GetPrivateProfileInt("Dark_Knight","DamageMin_StrLeft",6,Character_DIR);
	//----------------------
	this->Character.MGDamageMax_StrRight = GetPrivateProfileInt("Magic_Gladiator","DamageMax_StrRight",4,Character_DIR);
	this->Character.MGDamageMax_EneRight = GetPrivateProfileInt("Magic_Gladiator","DamageMax_EneRight",8,Character_DIR);
	this->Character.MGDamageMin_StrRight = GetPrivateProfileInt("Magic_Gladiator","DamageMin_StrRight",6,Character_DIR);
	this->Character.MGDamageMin_EneRight = GetPrivateProfileInt("Magic_Gladiator","DamageMin_EneRight",12,Character_DIR);

	this->Character.MGDamageMax_StrLeft = GetPrivateProfileInt("Magic_Gladiator","DamageMax_StrLeft",4,Character_DIR);
	this->Character.MGDamageMax_EneLeft = GetPrivateProfileInt("Magic_Gladiator","DamageMax_EneLeft",8,Character_DIR);
	this->Character.MGDamageMin_StrLeft = GetPrivateProfileInt("Magic_Gladiator","DamageMin_StrLeft",6,Character_DIR);
	this->Character.MGDamageMin_EneLeft = GetPrivateProfileInt("Magic_Gladiator","DamageMin_EneLeft",12,Character_DIR);
	//----------------------
	this->Character.SUMDamageMax_StrRight = GetPrivateProfileInt("Summoner","DamageMax_StrRight",4,Character_DIR);
	this->Character.SUMDamageMin_StrRight = GetPrivateProfileInt("Summoner","DamageMin_StrRight",7,Character_DIR);
	this->Character.SUMDamageMax_StrLeft = GetPrivateProfileInt("Summoner","DamageMax_StrLeft",4,Character_DIR);
	this->Character.SUMDamageMin_StrLeft = GetPrivateProfileInt("Summoner","DamageMin_StrLeft",7,Character_DIR);
	//----------------------
	this->Character.DWDamageMax_StrRight = GetPrivateProfileInt("Dark_Wizard","DamageMax_StrRight",4,Character_DIR);
	this->Character.DWDamageMin_StrRight = GetPrivateProfileInt("Dark_Wizard","DamageMin_StrRight",6,Character_DIR);
	this->Character.DWDamageMax_StrLeft = GetPrivateProfileInt("Dark_Wizard","DamageMax_StrLeft",4,Character_DIR);
	this->Character.DWDamageMin_StrLeft = GetPrivateProfileInt("Dark_Wizard","DamageMin_StrLeft",6,Character_DIR);
	//------------------------
	this->Character.DLDamageMax_StrRight = GetPrivateProfileInt("Dark_Lord","DamageMax_StrRight",5,Character_DIR);
	this->Character.DLDamageMax_EneRight = GetPrivateProfileInt("Dark_Lord","DamageMax_EneRight",10,Character_DIR);
	this->Character.DLDamageMin_StrRight = GetPrivateProfileInt("Dark_Lord","DamageMin_StrRight",7,Character_DIR);
	this->Character.DLDamageMin_EneRight = GetPrivateProfileInt("Dark_Lord","DamageMin_EneRight",14,Character_DIR);

	this->Character.DLDamageMax_StrLeft = GetPrivateProfileInt("Dark_Lord","DamageMax_StrLeft",5,Character_DIR);
	this->Character.DLDamageMax_EneLeft = GetPrivateProfileInt("Dark_Lord","DamageMax_EneLeft",10,Character_DIR);
	this->Character.DLDamageMin_StrLeft = GetPrivateProfileInt("Dark_Lord","DamageMin_StrLeft",7,Character_DIR);
	this->Character.DLDamageMin_EneLeft = GetPrivateProfileInt("Dark_Lord","DamageMin_EneLeft",14,Character_DIR);
	//-------------------------

	this->Character.SUMMagicDamageMax = GetPrivateProfileInt("Summoner","MagicDamageMax",4,Character_DIR);
	this->Character.SUMMagicDamageMin = GetPrivateProfileInt("Summoner","MagicDamageMin",9,Character_DIR);

	this->Character.MGMagicDamageMax = GetPrivateProfileInt("Magic_Gladiator","MagicDamageMax",4,Character_DIR);
	this->Character.MGMagicDamageMin = GetPrivateProfileInt("Magic_Gladiator","MagicDamageMin",9,Character_DIR);

	this->Character.DWMagicDamageMax = GetPrivateProfileInt("Dark_Wizard","MagicDamageMax",4,Character_DIR);
	this->Character.DWMagicDamageMin = GetPrivateProfileInt("Dark_Wizard","MagicDamageMin",9,Character_DIR);

	//---------------------------------
	this->Character.ELFSuccessfulBlocking = GetPrivateProfileInt("Fairy_Elf","SuccessfulBlocking",4,Character_DIR);
	this->Character.DLSuccessfulBlocking = GetPrivateProfileInt("Dark_Lord","SuccessfulBlocking",7,Character_DIR);
	this->Character.SUMSuccessfulBlocking = GetPrivateProfileInt("Summoner","SuccessfulBlocking",4,Character_DIR);
	this->Character.DWSuccessfulBlocking = GetPrivateProfileInt("Dark_Wizard","SuccessfulBlocking",3,Character_DIR);
	this->Character.DKSuccessfulBlocking = GetPrivateProfileInt("Dark_Knight","SuccessfulBlocking",3,Character_DIR);
	this->Character.MGSuccessfulBlocking = GetPrivateProfileInt("Magic_Gladiator","SuccessfulBlocking",3,Character_DIR);
	//---------------------------------
	this->Character.ELFDefense = GetPrivateProfileInt("Fairy_Elf","Defense",10,Character_DIR);
	this->Character.DKDefense = GetPrivateProfileInt("Dark_Knight","Defense",3,Character_DIR);
	this->Character.DLDefense = GetPrivateProfileInt("Dark_Lord","Defense",7,Character_DIR);
	this->Character.SUMDefense = GetPrivateProfileInt("Summoner","Defense",3,Character_DIR);
	this->Character.MGDefense = GetPrivateProfileInt("Magic_Gladiator","Defense",4,Character_DIR);
	this->Character.DWDefense = GetPrivateProfileInt("Dark_Wizard","Defense",4,Character_DIR);

	this->Character.RFDamageMin_VitRight = GetPrivateProfileInt("RageFighter","DamageMin_VitRight",15,Character_DIR);
	this->Character.RFDamageMin_StrRight = GetPrivateProfileInt("RageFighter","DamageMin_StrRight",7,Character_DIR);
	this->Character.RFDamageMax_VitRight = GetPrivateProfileInt("RageFighter","DamageMax_VitRight",12,Character_DIR);
	this->Character.RFDamageMax_StrRight = GetPrivateProfileInt("RageFighter","DamageMax_StrRight",5,Character_DIR);

	this->Character.RFDamageMin_VitLeft = GetPrivateProfileInt("RageFighter","DamageMin_VitLeft",15,Character_DIR);
	this->Character.RFDamageMin_StrLeft = GetPrivateProfileInt("RageFighter","DamageMin_StrLeft",7,Character_DIR);
	this->Character.RFDamageMax_VitLeft = GetPrivateProfileInt("RageFighter","DamageMax_VitLeft",12,Character_DIR);
	this->Character.RFDamageMax_StrLeft = GetPrivateProfileInt("RageFighter","DamageMax_StrLeft",5,Character_DIR);

	this->Character.RFSuccessfulBlocking = GetPrivateProfileInt("RageFighter","SuccessfulBlocking",10,Character_DIR);

	this->Character.RFDefense = GetPrivateProfileInt("RageFighter","Defense",8,Character_DIR);

	this->Character.DKSkillDMGPercentMax = GetPrivateProfileInt("Dark_Knight","DKSkillDMGPercentMax",0,Character_DIR);
	this->Character.DLSkillDMGPercentMax = GetPrivateProfileInt("Dark_Lord","DLSkillDMGPercentMax",0,Character_DIR);

#ifdef FIX_BERSERK_SUM
	this->Character.BerserkAddMana = GetPrivateProfileInt("Summoner","BerserkAddMana",0,Character_DIR);
#endif

#if(CUSTOM_CW_ALTERELFDMG)
	this->Character.CWElfAlterDMGPercent = GetPrivateProfileInt("Common","CWElfAlterDMGPercent",100,Character_DIR);
#endif

	this->Character.DKPvPAttackRateFact1 = GetPrivateProfileInt("Dark_Knight","DKPvPAttackRateFact1",3,Character_DIR);
	this->Character.DKPvPAttackRateFact2 = GetPrivateProfileInt("Dark_Knight","DKPvPAttackRateFact2",45,Character_DIR);
	this->Character.DKPvPAttackRateDiv = GetPrivateProfileInt("Dark_Knight","DKPvPAttackRateDiv",10,Character_DIR);

	this->Character.DWPvPAttackRateFact1 = GetPrivateProfileInt("Dark_Wizard","DWPvPAttackRateFact1",3,Character_DIR);
	this->Character.DWPvPAttackRateFact2 = GetPrivateProfileInt("Dark_Wizard","DWPvPAttackRateFact2",4,Character_DIR);

	this->Character.EEPvPAttackRateFact1 = GetPrivateProfileInt("Fairy_Elf","EEPvPAttackRateFact1",3,Character_DIR);
	this->Character.EEPvPAttackRateFact2 = GetPrivateProfileInt("Fairy_Elf","EEPvPAttackRateFact2",6,Character_DIR);
	this->Character.EEPvPAttackRateDiv = GetPrivateProfileInt("Fairy_Elf","EEPvPAttackRateDiv",10,Character_DIR);

	this->Character.MGPvPAttackRateFact1 = GetPrivateProfileInt("Magic_Gladiator","MGPvPAttackRateFact1",3,Character_DIR);
	this->Character.MGPvPAttackRateFact2 = GetPrivateProfileInt("Magic_Gladiator","MGPvPAttackRateFact2",35,Character_DIR);
	this->Character.MGPvPAttackRateDiv = GetPrivateProfileInt("Magic_Gladiator","MGPvPAttackRateDiv",10,Character_DIR);

	this->Character.DLPvPAttackRateFact1 = GetPrivateProfileInt("Dark_Lord","DLPvPAttackRateFact1",3,Character_DIR);
	this->Character.DLPvPAttackRateFact2 = GetPrivateProfileInt("Dark_Lord","DLPvPAttackRateFact2",4,Character_DIR);

	this->Character.SUPvPAttackRateFact1 = GetPrivateProfileInt("Summoner","SUPvPAttackRateFact1",3,Character_DIR);
	this->Character.SUPvPAttackRateFact2 = GetPrivateProfileInt("Summoner","SUPvPAttackRateFact2",35,Character_DIR);
	this->Character.SUPvPAttackRateDiv = GetPrivateProfileInt("Summoner","SUPvPAttackRateDiv",10,Character_DIR);

	this->Character.RFPvPAttackRateFact1 = GetPrivateProfileInt("RageFighter","RFPvPAttackRateFact1",3,Character_DIR);
	this->Character.RFPvPAttackRateFact2 = GetPrivateProfileInt("RageFighter","RFPvPAttackRateFact2",36,Character_DIR);
	this->Character.RFPvPAttackRateDiv = GetPrivateProfileInt("RageFighter","RFPvPAttackRateDiv",10,Character_DIR);


	this->Character.AEAttackDamageStrengthMin = GetPrivateProfileInt("Fairy_Elf","AEAttackDamageStrengthMin",7,Character_DIR);
	this->Character.AEAttackDamageStrengthMax = GetPrivateProfileInt("Fairy_Elf","AEAttackDamageStrengthMax",4,Character_DIR);
	this->Character.AEAttackDamageDexterityMin = GetPrivateProfileInt("Fairy_Elf","AEAttackDamageDexterityMin",7,Character_DIR);
	this->Character.AEAttackDamageDexterityMax = GetPrivateProfileInt("Fairy_Elf","AEAttackDamageDexterityMax",4,Character_DIR);
	this->Character.AEAttackDamageVitalityMin = GetPrivateProfileInt("Fairy_Elf","AEAttackDamageVitalityMin",7,Character_DIR);
	this->Character.AEAttackDamageVitalityMax = GetPrivateProfileInt("Fairy_Elf","AEAttackDamageVitalityMax",4,Character_DIR);
	this->Character.AEAttackDamageEnergyMin = GetPrivateProfileInt("Fairy_Elf","AEAttackDamageEnergyMin",7,Character_DIR);
	this->Character.AEAttackDamageEnergyMax = GetPrivateProfileInt("Fairy_Elf","AEAttackDamageEnergyMax",4,Character_DIR);


	//---------------------------------
	//			Commands
	//---------------------------------
	 GetPrivateProfileString("Post", "PostName","/post",Command.CommandPost,100,Commands_DIR);
	 	 
	 GetPrivateProfileString("AddCommand", "StrName","/str",Command.CommandAddStr,100,Commands_DIR);
	 
	 GetPrivateProfileString("AddCommand", "AgiName","/agi",Command.CommandAddAgi,100,Commands_DIR);
	 
	 GetPrivateProfileString("AddCommand", "VitName","/vit",Command.CommandAddVit,100,Commands_DIR);
	 
	 GetPrivateProfileString("AddCommand", "EneName","/ene",Command.CommandAddEne,100,Commands_DIR);
	 
	 GetPrivateProfileString("AddCommand", "CmdName","/cmd",Command.CommandAddCmd,100,Commands_DIR);//snaker 5.11
	 
	 GetPrivateProfileString("PkClear", "PkClearName","/pkclear",Command.CommandPkClear,100,Commands_DIR);

	 /*GetPrivateProfileString("Reset", "cmd","/reset",Command.CommandReset,100,Reset_DIR);*/

	/* GetPrivateProfileString("GrandReset", "cmd","/grandreset",Command.CommandGrandReset,100,GrandReset_DIR);*/

	this->Command.PostLevel = GetPrivateProfileInt("Post","PostLevel",100,Commands_DIR);
	
	this->Command.PostMoney = GetPrivateProfileInt("Post","PostMoney",1000000,Commands_DIR);

	GetPrivateProfileString("Post", "PostPrist","[post]:",Command.PostPrist,100,Commands_DIR);

	this->Command.PostColor = GetPrivateProfileInt("Post","PostColor",1,Commands_DIR);
	this->Command.PostDelay = GetPrivateProfileInt("Post","PostDelay",0,Commands_DIR);
	
	this->Command.PostServer = GetPrivateProfileInt("Post","PostServer",0,Commands_DIR);
	

//#ifdef _CONFLICT_
//
//#else
	if(this->Command.PostColor < 1 || this->Command.PostColor > 9)
	{
		this->Command.PostColor = 3;
	}
//#endif
	this->Command.AddMoney = GetPrivateProfileInt("AddCommand","AddPriceZen",0,Commands_DIR);
	this->Command.AddLeveL = GetPrivateProfileInt("AddCommand","AddPointLevel",1,Commands_DIR);

	this->Command.Zt_PkClear_Enabled = GetPrivateProfileInt("PkClear","Enabled",1,Commands_DIR);
	this->Command.Zt_PkClearLevel = GetPrivateProfileInt("PkClear","PkClearLevel",0,Commands_DIR);
	this->Command.Zt_PkClearMoney = GetPrivateProfileInt("PkClear","PkClearMoney",0,Commands_DIR);
	this->Command.Zt_PKClearType = GetPrivateProfileInt("PkClear","PKClearType",0,Commands_DIR);
#ifdef PK_CLEAR_TO_CREDITS
	if(g_ZtLicense.CheckUser(eZtUB::Local3) || g_ZtLicense.CheckUser(SILVER1) || g_ZtLicense.CheckUser(SILVER2))
	{
		this->Command.Zt_PkClearCredits = GetPrivateProfileInt("PkClear","PkClearCredits",0,Commands_DIR);
	}
#endif // PK_CLEAR_TO_CREDITS

	this->Command.PostPCPoint = GetPrivateProfileInt("Post","PostPCPoint",1000000,Commands_DIR);
	this->Command.MoneyType = GetPrivateProfileInt("Post","MoneyType",1,Commands_DIR);
	
#ifdef _POST_CONFIG_
	 GetPrivateProfileString("Post", "AdminPostName","/gg",Command.AdminPostName,100,Commands_DIR);
#endif

	this->Command.GensColorEnable = GetPrivateProfileInt("Post","GensColorEnable",0,Commands_DIR);
	this->Command.GensColorRed = GetPrivateProfileInt("Post","GensColorRed",230,Commands_DIR);
	this->Command.GensColorGreen = GetPrivateProfileInt("Post","GensColorGreen",230,Commands_DIR);
	this->Command.GensColorBlue = GetPrivateProfileInt("Post","GensColorBlue",233,Commands_DIR);

	//---------------------------------
	//			Events
	//---------------------------------

	this->Event.Zt_IllusionTemplPlaerMin = GetPrivateProfileInt("IllusionTemple","ItMinPlayers",4,Events_DIR);
	this->Event.Zt_ItDropType	= GetPrivateProfileInt("IllusionTemple","ItDropType",12,Events_DIR);
	this->Event.Zt_ItDropID		= GetPrivateProfileInt("IllusionTemple","ItDropID",15,Events_DIR);
	this->Event.Zt_ItDropLevel	= GetPrivateProfileInt("IllusionTemple","ItDropLevel",0,Events_DIR);
	this->Event.Zt_ItDropSkill	= GetPrivateProfileInt("IllusionTemple","ItDropSkill",0,Events_DIR);
	this->Event.Zt_ItDropLuck	= GetPrivateProfileInt("IllusionTemple","ItDropLuck",0,Events_DIR);
	this->Event.Zt_ItDropOpt	= GetPrivateProfileInt("IllusionTemple","ItDropOpt",0,Events_DIR);
	this->Event.Zt_ItDropExcOpt	= GetPrivateProfileInt("IllusionTemple","ItDropExcOpt",0,Events_DIR);
	this->Event.Zt_ItDropAncOpt	= GetPrivateProfileInt("IllusionTemple","ItDropAncOpt",0,Events_DIR);

	this->Event.Zt_BCDropType	= GetPrivateProfileInt("BloodCastle","BCDropType",12,Events_DIR);
	this->Event.Zt_BCDropID		= GetPrivateProfileInt("BloodCastle","BCDropID",15,Events_DIR);
	this->Event.Zt_BCDropLevel	= GetPrivateProfileInt("BloodCastle","BCDropLevel",0,Events_DIR);
	this->Event.Zt_BCDropSkill	= GetPrivateProfileInt("BloodCastle","BCDropSkill",0,Events_DIR);
	this->Event.Zt_BCDropLuck	= GetPrivateProfileInt("BloodCastle","BCDropLuck",0,Events_DIR);
	this->Event.Zt_BCDropOpt	= GetPrivateProfileInt("BloodCastle","BCDropOpt",0,Events_DIR);
	this->Event.Zt_BCDropExcOpt	= GetPrivateProfileInt("BloodCastle","BCDropExcOpt",0,Events_DIR);
	this->Event.Zt_BCDropAncOpt	= GetPrivateProfileInt("BloodCastle","BCDropAncOpt",0,Events_DIR);
	this->Event.BCAllowPKPlayer	= GetPrivateProfileInt("BloodCastle","BCAllowPKPlayer",0,Events_DIR);

	this->Event.Zt_BCRewardLevelUp = GetPrivateProfileInt("BloodCastle","BCRewardLevelUp",0,Events_DIR);
	this->Event.Zt_CCRewardLevelUp = GetPrivateProfileInt("BloodCastle","CCRewardLevelUp",0,Events_DIR);
	

#ifdef BC_LVL_DROP
	if(g_ZtLicense.CheckUser(eZtUB::Local3) || g_ZtLicense.CheckUser(eZtUB::drynea) || g_ZtLicense.CheckUser(eZtUB::Local2) || g_ZtLicense.CheckUser(eZtUB::Local))
	{
		this->Event.Zt_BCDropType_DRYNEA[1]	= GetPrivateProfileInt("BloodCastle","BCDropType1",12,Events_DIR);
		this->Event.Zt_BCDropID_DRYNEA[1]		= GetPrivateProfileInt("BloodCastle","BCDropID1",15,Events_DIR);
		this->Event.Zt_BCDropLevel_DRYNEA[1]	= GetPrivateProfileInt("BloodCastle","BCDropLevel1",0,Events_DIR);
		this->Event.Zt_BCDropSkill_DRYNEA[1]	= GetPrivateProfileInt("BloodCastle","BCDropSkill1",0,Events_DIR);
		this->Event.Zt_BCDropLuck_DRYNEA[1]	= GetPrivateProfileInt("BloodCastle","BCDropLuck1",0,Events_DIR);
		this->Event.Zt_BCDropOpt_DRYNEA[1]	= GetPrivateProfileInt("BloodCastle","BCDropOpt1",0,Events_DIR);
		this->Event.Zt_BCDropExcOpt_DRYNEA[1]	= GetPrivateProfileInt("BloodCastle","BCDropExcOpt1",0,Events_DIR);
		this->Event.Zt_BCDropAncOpt_DRYNEA[1]	= GetPrivateProfileInt("BloodCastle","BCDropAncOpt1",0,Events_DIR);
		this->Event.BCAllowPKPlayer_DRYNEA[1]	= GetPrivateProfileInt("BloodCastle","BCAllowPKPlayer1",0,Events_DIR);

		this->Event.Zt_BCDropType_DRYNEA[2]	= GetPrivateProfileInt("BloodCastle","BCDropType2",12,Events_DIR);
		this->Event.Zt_BCDropID_DRYNEA[2]		= GetPrivateProfileInt("BloodCastle","BCDropID2",15,Events_DIR);
		this->Event.Zt_BCDropLevel_DRYNEA[2]	= GetPrivateProfileInt("BloodCastle","BCDropLevel2",0,Events_DIR);
		this->Event.Zt_BCDropSkill_DRYNEA[2]	= GetPrivateProfileInt("BloodCastle","BCDropSkill2",0,Events_DIR);
		this->Event.Zt_BCDropLuck_DRYNEA[2]	= GetPrivateProfileInt("BloodCastle","BCDropLuck2",0,Events_DIR);
		this->Event.Zt_BCDropOpt_DRYNEA[2]	= GetPrivateProfileInt("BloodCastle","BCDropOpt2",0,Events_DIR);
		this->Event.Zt_BCDropExcOpt_DRYNEA[2]	= GetPrivateProfileInt("BloodCastle","BCDropExcOpt2",0,Events_DIR);
		this->Event.Zt_BCDropAncOpt_DRYNEA[2]	= GetPrivateProfileInt("BloodCastle","BCDropAncOpt2",0,Events_DIR);
		this->Event.BCAllowPKPlayer_DRYNEA[2]	= GetPrivateProfileInt("BloodCastle","BCAllowPKPlayer2",0,Events_DIR);

		this->Event.Zt_BCDropType_DRYNEA[3]	= GetPrivateProfileInt("BloodCastle","BCDropType3",12,Events_DIR);
		this->Event.Zt_BCDropID_DRYNEA[3]		= GetPrivateProfileInt("BloodCastle","BCDropID3",15,Events_DIR);
		this->Event.Zt_BCDropLevel_DRYNEA[3]	= GetPrivateProfileInt("BloodCastle","BCDropLevel3",0,Events_DIR);
		this->Event.Zt_BCDropSkill_DRYNEA[3]	= GetPrivateProfileInt("BloodCastle","BCDropSkill3",0,Events_DIR);
		this->Event.Zt_BCDropLuck_DRYNEA[3]	= GetPrivateProfileInt("BloodCastle","BCDropLuck3",0,Events_DIR);
		this->Event.Zt_BCDropOpt_DRYNEA[3]	= GetPrivateProfileInt("BloodCastle","BCDropOpt3",0,Events_DIR);
		this->Event.Zt_BCDropExcOpt_DRYNEA[3]	= GetPrivateProfileInt("BloodCastle","BCDropExcOpt3",0,Events_DIR);
		this->Event.Zt_BCDropAncOpt_DRYNEA[3]	= GetPrivateProfileInt("BloodCastle","BCDropAncOpt3",0,Events_DIR);
		this->Event.BCAllowPKPlayer_DRYNEA[3]	= GetPrivateProfileInt("BloodCastle","BCAllowPKPlayer3",0,Events_DIR);

		this->Event.Zt_BCDropType_DRYNEA[4]	= GetPrivateProfileInt("BloodCastle","BCDropType4",12,Events_DIR);
		this->Event.Zt_BCDropID_DRYNEA[4]		= GetPrivateProfileInt("BloodCastle","BCDropID4",15,Events_DIR);
		this->Event.Zt_BCDropLevel_DRYNEA[4]	= GetPrivateProfileInt("BloodCastle","BCDropLevel4",0,Events_DIR);
		this->Event.Zt_BCDropSkill_DRYNEA[4]	= GetPrivateProfileInt("BloodCastle","BCDropSkill4",0,Events_DIR);
		this->Event.Zt_BCDropLuck_DRYNEA[4]	= GetPrivateProfileInt("BloodCastle","BCDropLuck4",0,Events_DIR);
		this->Event.Zt_BCDropOpt_DRYNEA[4]	= GetPrivateProfileInt("BloodCastle","BCDropOpt4",0,Events_DIR);
		this->Event.Zt_BCDropExcOpt_DRYNEA[4]	= GetPrivateProfileInt("BloodCastle","BCDropExcOpt4",0,Events_DIR);
		this->Event.Zt_BCDropAncOpt_DRYNEA[4]	= GetPrivateProfileInt("BloodCastle","BCDropAncOpt4",0,Events_DIR);
		this->Event.BCAllowPKPlayer_DRYNEA[4]	= GetPrivateProfileInt("BloodCastle","BCAllowPKPlayer4",0,Events_DIR);

		this->Event.Zt_BCDropType_DRYNEA[5]	= GetPrivateProfileInt("BloodCastle","BCDropType5",12,Events_DIR);
		this->Event.Zt_BCDropID_DRYNEA[5]		= GetPrivateProfileInt("BloodCastle","BCDropID5",15,Events_DIR);
		this->Event.Zt_BCDropLevel_DRYNEA[5]	= GetPrivateProfileInt("BloodCastle","BCDropLevel5",0,Events_DIR);
		this->Event.Zt_BCDropSkill_DRYNEA[5]	= GetPrivateProfileInt("BloodCastle","BCDropSkill5",0,Events_DIR);
		this->Event.Zt_BCDropLuck_DRYNEA[5]	= GetPrivateProfileInt("BloodCastle","BCDropLuck5",0,Events_DIR);
		this->Event.Zt_BCDropOpt_DRYNEA[5]	= GetPrivateProfileInt("BloodCastle","BCDropOpt5",0,Events_DIR);
		this->Event.Zt_BCDropExcOpt_DRYNEA[5]	= GetPrivateProfileInt("BloodCastle","BCDropExcOpt5",0,Events_DIR);
		this->Event.Zt_BCDropAncOpt_DRYNEA[5]	= GetPrivateProfileInt("BloodCastle","BCDropAncOpt5",0,Events_DIR);
		this->Event.BCAllowPKPlayer_DRYNEA[5]	= GetPrivateProfileInt("BloodCastle","BCAllowPKPlayer5",0,Events_DIR);

		this->Event.Zt_BCDropType_DRYNEA[6]	= GetPrivateProfileInt("BloodCastle","BCDropType6",12,Events_DIR);
		this->Event.Zt_BCDropID_DRYNEA[6]		= GetPrivateProfileInt("BloodCastle","BCDropID6",15,Events_DIR);
		this->Event.Zt_BCDropLevel_DRYNEA[6]	= GetPrivateProfileInt("BloodCastle","BCDropLevel6",0,Events_DIR);
		this->Event.Zt_BCDropSkill_DRYNEA[6]	= GetPrivateProfileInt("BloodCastle","BCDropSkill6",0,Events_DIR);
		this->Event.Zt_BCDropLuck_DRYNEA[6]	= GetPrivateProfileInt("BloodCastle","BCDropLuck6",0,Events_DIR);
		this->Event.Zt_BCDropOpt_DRYNEA[6]	= GetPrivateProfileInt("BloodCastle","BCDropOpt6",0,Events_DIR);
		this->Event.Zt_BCDropExcOpt_DRYNEA[6]	= GetPrivateProfileInt("BloodCastle","BCDropExcOpt6",0,Events_DIR);
		this->Event.Zt_BCDropAncOpt_DRYNEA[6]	= GetPrivateProfileInt("BloodCastle","BCDropAncOpt6",0,Events_DIR);
		this->Event.BCAllowPKPlayer_DRYNEA[6]	= GetPrivateProfileInt("BloodCastle","BCAllowPKPlayer6",0,Events_DIR);

		this->Event.Zt_BCDropType_DRYNEA[7]	= GetPrivateProfileInt("BloodCastle","BCDropType7",12,Events_DIR);
		this->Event.Zt_BCDropID_DRYNEA[7]		= GetPrivateProfileInt("BloodCastle","BCDropID7",15,Events_DIR);
		this->Event.Zt_BCDropLevel_DRYNEA[7]	= GetPrivateProfileInt("BloodCastle","BCDropLevel7",0,Events_DIR);
		this->Event.Zt_BCDropSkill_DRYNEA[7]	= GetPrivateProfileInt("BloodCastle","BCDropSkill7",0,Events_DIR);
		this->Event.Zt_BCDropLuck_DRYNEA[7]	= GetPrivateProfileInt("BloodCastle","BCDropLuck7",0,Events_DIR);
		this->Event.Zt_BCDropOpt_DRYNEA[7]	= GetPrivateProfileInt("BloodCastle","BCDropOpt7",0,Events_DIR);
		this->Event.Zt_BCDropExcOpt_DRYNEA[7]	= GetPrivateProfileInt("BloodCastle","BCDropExcOpt7",0,Events_DIR);
		this->Event.Zt_BCDropAncOpt_DRYNEA[7]	= GetPrivateProfileInt("BloodCastle","BCDropAncOpt7",0,Events_DIR);
		this->Event.BCAllowPKPlayer_DRYNEA[7]	= GetPrivateProfileInt("BloodCastle","BCAllowPKPlayer7",0,Events_DIR);

		this->Event.Zt_BCDropType_DRYNEA[8]	= GetPrivateProfileInt("BloodCastle","BCDropType8",12,Events_DIR);
		this->Event.Zt_BCDropID_DRYNEA[8]		= GetPrivateProfileInt("BloodCastle","BCDropID8",15,Events_DIR);
		this->Event.Zt_BCDropLevel_DRYNEA[8]	= GetPrivateProfileInt("BloodCastle","BCDropLevel8",0,Events_DIR);
		this->Event.Zt_BCDropSkill_DRYNEA[8]	= GetPrivateProfileInt("BloodCastle","BCDropSkill8",0,Events_DIR);
		this->Event.Zt_BCDropLuck_DRYNEA[8]	= GetPrivateProfileInt("BloodCastle","BCDropLuck8",0,Events_DIR);
		this->Event.Zt_BCDropOpt_DRYNEA[8]	= GetPrivateProfileInt("BloodCastle","BCDropOpt8",0,Events_DIR);
		this->Event.Zt_BCDropExcOpt_DRYNEA[8]	= GetPrivateProfileInt("BloodCastle","BCDropExcOpt8",0,Events_DIR);
		this->Event.Zt_BCDropAncOpt_DRYNEA[8]	= GetPrivateProfileInt("BloodCastle","BCDropAncOpt8",0,Events_DIR);
		this->Event.BCAllowPKPlayer_DRYNEA[8]	= GetPrivateProfileInt("BloodCastle","BCAllowPKPlayer8",0,Events_DIR);
	}
#endif

	this->Event.Zt_CCMinPlayer = GetPrivateProfileInt("ChaosCastle","CCMinPlayer",2,Events_DIR);
	this->Event.Zt_CCRewardLevelUp = GetPrivateProfileInt("ChaosCastle","CCRewardLevelUp",2,Events_DIR);

	this->Event.DSParty3ExpPercent = GetPrivateProfileInt("DevilSquare","DSParty3ExpPercent",230,Events_DIR);
	this->Event.DSParty4ExpPercent = GetPrivateProfileInt("DevilSquare","DSParty4ExpPercent",270,Events_DIR);
	this->Event.DSParty5ExpPercent = GetPrivateProfileInt("DevilSquare","DSParty5ExpPercent",300,Events_DIR);
	this->Event.DSPartyExpPercentOther = GetPrivateProfileInt("DevilSquare","DSPartyExpPercentOther",120,Events_DIR);
	this->Event.DSParty2ExpSetPercent = GetPrivateProfileInt("DevilSquare","DSParty2ExpSetPercent",160,Events_DIR);
	this->Event.DSParty3ExpSetPercent = GetPrivateProfileInt("DevilSquare","DSParty3ExpSetPercent",180,Events_DIR);
	this->Event.DSParty4ExpSetPercent = GetPrivateProfileInt("DevilSquare","DSParty4ExpSetPercent",200,Events_DIR);
	this->Event.DSParty5ExpSetPercent = GetPrivateProfileInt("DevilSquare","DSParty5ExpSetPercent",220,Events_DIR);
	this->Event.DSParty1ExpSetPercent = GetPrivateProfileInt("DevilSquare","DSParty1ExpSetPercent",150,Events_DIR);

	this->Event.DSAllowPKPlayer = GetPrivateProfileInt("DevilSquare","DSAllowPKPlayer",0,Events_DIR);

	this->Event.Zt_DSRewardLevelUp1 = GetPrivateProfileInt("DevilSquare","DSRewardLevelUp1",0,Events_DIR);
	this->Event.Zt_DSRewardLevelUp2 = GetPrivateProfileInt("DevilSquare","DSRewardLevelUp2",0,Events_DIR);
	this->Event.Zt_DSRewardLevelUp3 = GetPrivateProfileInt("DevilSquare","DSRewardLevelUp3",0,Events_DIR);

	//---------------------------------
	//			Reset
	//---------------------------------

	//this->Reset.EnableResetSystem = GetPrivateProfileInt("Reset","Enable",0,Reset_DIR);	
	//this->Reset.Maxres = GetPrivateProfileInt("Reset","Max.res",100,Reset_DIR);
	//this->Reset.ZenForm = GetPrivateProfileInt("Reset","ZenForm",0,Reset_DIR);
	//this->Reset.NeedZen = GetPrivateProfileInt("Reset","Need.Zen",0,Reset_DIR);
	//this->Reset.NeedLevel = GetPrivateProfileInt("Reset","Need.Level",0,Reset_DIR);
	//this->Reset.AddForm = GetPrivateProfileInt("Reset","Add.Form",0,Reset_DIR);
	//this->Reset.AddPointsDW = GetPrivateProfileInt("Reset","Add.PointsDW",0,Reset_DIR);
	//this->Reset.AddPointsDK = GetPrivateProfileInt("Reset","Add.PointsDK",0,Reset_DIR);
	//this->Reset.AddPointsELF = GetPrivateProfileInt("Reset","Add.PointsELF",0,Reset_DIR);
	//this->Reset.AddPointsSUM = GetPrivateProfileInt("Reset","Add.PointsSUM",0,Reset_DIR);
	//this->Reset.AddPointsMG = GetPrivateProfileInt("Reset","Add.PointsMG",0,Reset_DIR);
	//this->Reset.AddPointsDL = GetPrivateProfileInt("Reset","Add.PointsDL",0,Reset_DIR);
	//this->Reset.AddPcPoint = GetPrivateProfileInt("Reset","Add.PcPoint",0,Reset_DIR);
	//this->Reset.NeedEmptyInv = GetPrivateProfileInt("Reset","Need.EmptyInv",1,Reset_DIR);

	//---------------------------------
	//			Grand Reset
	//---------------------------------

	//this->GrandReset.EnableGrandResetSystem = GetPrivateProfileInt("GrandReset","Enable",0,GrandReset_DIR);	
	//this->GrandReset.MaxGrandRes = GetPrivateProfileInt("GrandReset","Max.GrandRes",100,GrandReset_DIR);
	//this->GrandReset.ZenForm = GetPrivateProfileInt("GrandReset","ZenForm",0,GrandReset_DIR);
	//this->GrandReset.NeedZen = GetPrivateProfileInt("GrandReset","Need.Zen",0,GrandReset_DIR);
	//this->GrandReset.NeedRes = GetPrivateProfileInt("GrandReset","Need.Res",0,GrandReset_DIR);
	//this->GrandReset.NeedLevel = GetPrivateProfileInt("GrandReset","Need.Level",0,GrandReset_DIR);
	//this->GrandReset.AddForm = GetPrivateProfileInt("GrandReset","Add.Form",0,GrandReset_DIR);
	//this->GrandReset.AddPointsDW = GetPrivateProfileInt("GrandReset","Add.PointsDW",0,GrandReset_DIR);
	//this->GrandReset.AddPointsDK = GetPrivateProfileInt("GrandReset","Add.PointsDK",0,GrandReset_DIR);
	//this->GrandReset.AddPointsELF = GetPrivateProfileInt("GrandReset","Add.PointsELF",0,GrandReset_DIR);
	//this->GrandReset.AddPointsSUM = GetPrivateProfileInt("GrandReset","Add.PointsSUM",0,GrandReset_DIR);
	//this->GrandReset.AddPointsMG = GetPrivateProfileInt("GrandReset","Add.PointsMG",0,GrandReset_DIR);
	//this->GrandReset.AddPointsDL = GetPrivateProfileInt("GrandReset","Add.PointsDL",0,GrandReset_DIR);
	//this->GrandReset.AddPcPoint = GetPrivateProfileInt("GrandReset","Add.PcPoint",0,GrandReset_DIR);
	//this->GrandReset.NeedEmptyInv = GetPrivateProfileInt("GrandReset","Need.EmptyInv",1,GrandReset_DIR);

	//---------------------------------
	//			Pets
	//---------------------------------

	this->Pet.Zt_PandaRingZen = GetPrivateProfileInt("PandaRing","Zen",30,Pets_DIR);
	this->Pet.Zt_PandaRingAttack = GetPrivateProfileInt("PandaRing","AttackDamage",30,Pets_DIR);
	this->Pet.Zt_PandaDef = GetPrivateProfileInt("Panda","Defense",50,Pets_DIR);
	this->Pet.Zt_PandaExp = GetPrivateProfileInt("Panda","Exp",50,Pets_DIR);

	this->Pet.RavenAttackDamageMinLvl = GetPrivateProfileInt("DarkSpirit","RavenAttackDamageMinLvl",15,Pets_DIR);
	this->Pet.RavenAttackDamageMaxLvl = GetPrivateProfileInt("DarkSpirit","RavenAttackDamageMaxLvl",15,Pets_DIR);

	this->Pet.RavenAttackDamageMinCmd = GetPrivateProfileInt("DarkSpirit","RavenAttackDamageMinCmd",8,Pets_DIR);
	this->Pet.RavenAttackDamageMaxCmd = GetPrivateProfileInt("DarkSpirit","RavenAttackDamageMaxCmd",4,Pets_DIR);

	this->Pet.RavenDurabilitySmall = GetPrivateProfileInt("DarkSpirit","RavenDurabilitySmall",800,Pets_DIR);

	this->Pet.SkeletonPetExp = GetPrivateProfileInt("SkeletonPet","Experience",30,Pets_DIR);
	this->Pet.SkeletonPetAndRingExp = GetPrivateProfileInt("SkeletonPetAndRing","Experience",60,Pets_DIR);

	this->Pet.RedFenrirProcDamage = GetPrivateProfileInt("Fenrir","RedFenrirProcDamage",10,Pets_DIR);
	this->Pet.RedFenrirProcAbsurd = GetPrivateProfileInt("Fenrir","RedFenrirProcAbsurd",10,Pets_DIR);
	this->Pet.RedFenrirProcLife = GetPrivateProfileInt("Fenrir","RedFenrirProcLife",10,Pets_DIR);
	this->Pet.RedFenrirProcDurability = GetPrivateProfileInt("Fenrir","RedFenrirProcDurability",100,Pets_DIR);

	this->Pet.BlueFenrirProcDamage = GetPrivateProfileInt("Fenrir","BlueFenrirProcDamage",10,Pets_DIR);
	this->Pet.BlueFenrirProcAbsurd = GetPrivateProfileInt("Fenrir","BlueFenrirProcAbsurd",10,Pets_DIR);
	this->Pet.BlueFenrirProcLife = GetPrivateProfileInt("Fenrir","BlueFenrirProcLife",10,Pets_DIR);
	this->Pet.BlueFenrirProcDurability = GetPrivateProfileInt("Fenrir","BlueFenrirProcDurability",100,Pets_DIR);

	this->Pet.BlackFenrirProcDamage = GetPrivateProfileInt("Fenrir","BlackFenrirProcDamage",10,Pets_DIR);
	this->Pet.BlackFenrirProcAbsurd = GetPrivateProfileInt("Fenrir","BlackFenrirProcAbsurd",10,Pets_DIR);
	this->Pet.BlackFenrirProcLife = GetPrivateProfileInt("Fenrir","BlackFenrirProcLife",10,Pets_DIR);
	this->Pet.BlackFenrirProcDurability = GetPrivateProfileInt("Fenrir","BlackFenrirProcDurability",100,Pets_DIR);

	this->Pet.GoldFenrirProcDamage = GetPrivateProfileInt("Fenrir","GoldFenrirProcDamage",10,Pets_DIR);
	this->Pet.GoldFenrirProcAbsurd = GetPrivateProfileInt("Fenrir","GoldFenrirProcAbsurd",10,Pets_DIR);
	this->Pet.GoldFenrirProcLife = GetPrivateProfileInt("Fenrir","GoldFenrirProcLife",10,Pets_DIR);
	this->Pet.GoldFenrirProcDurability = GetPrivateProfileInt("Fenrir","GoldFenrirProcDurability",100,Pets_DIR);

#if(CONFIG_PET_DURABILITY)
	this->Pet.AngelDurability = GetPrivateProfileInt("PetDurabilityDiv","AngelDurability",10,Pets_DIR);
	this->Pet.RudolfDurability = GetPrivateProfileInt("PetDurabilityDiv","RudolfDurability",10,Pets_DIR);
	this->Pet.SatanDurability = GetPrivateProfileInt("PetDurabilityDiv","SatanDurability",10,Pets_DIR);
	this->Pet.DemonDurability = GetPrivateProfileInt("PetDurabilityDiv","DemonDurability",10,Pets_DIR);
	this->Pet.GuardianDurability = GetPrivateProfileInt("PetDurabilityDiv","GuardianDurability",10,Pets_DIR);
	this->Pet.PandaDurability = GetPrivateProfileInt("PetDurabilityDiv","PandaDurability",10,Pets_DIR);
	this->Pet.SkeletonDurability = GetPrivateProfileInt("PetDurabilityDiv","SkeletonDurability",10,Pets_DIR);
	this->Pet.UnicornDurability = GetPrivateProfileInt("PetDurabilityDiv","UnicornDurability",10,Pets_DIR);
	this->Pet.UniriaDurability = GetPrivateProfileInt("PetDurabilityDiv","UniriaDurability",10,Pets_DIR);
	this->Pet.DinorantDurability = GetPrivateProfileInt("PetDurabilityDiv","DinorantDurability",10,Pets_DIR);
	this->Pet.RingPandaDurability = GetPrivateProfileInt("PetDurabilityDiv","RingPandaDurability",10,Pets_DIR);
	this->Pet.RingSkeletonDurability = GetPrivateProfileInt("PetDurabilityDiv","RingSkeletonDurability",10,Pets_DIR);
#endif

	//---------------------------------
	//			PVP 
	//---------------------------------

	this->PvP.ZtPkPartySystem = GetPrivateProfileInt("PK","PKPartyOn",0,PVP_DIR);
	this->PvP.ZtPkLimit = GetPrivateProfileInt("PK","PkLimit",6,PVP_DIR);

	this->PvP.DuelGate = GetPrivateProfileInt("Duel","Gate",294,PVP_DIR);

	if(g_ZtLicense.CheckUser(SILVER1) || g_ZtLicense.CheckUser(SILVER2))
	{
		this->PvP.DuelLevel = GetPrivateProfileInt("Duel","DuelLevel",30,PVP_DIR);
	}
	else
	{
		this->PvP.DuelLevel = 30;
	}
	

	//---------------------------------
	//			Golden Drop
	//---------------------------------

	this->GoldenDrop.ItemType44 = GetPrivateProfileInt("Dragon","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex44 = GetPrivateProfileInt("Dragon","ItemIndex",13,GoldenDrop_DIR);
	this->GoldenDrop.level44 = GetPrivateProfileInt("Dragon","ItemLevel",0,GoldenDrop_DIR);

	this->GoldenDrop.ItemType43 = GetPrivateProfileInt("GoldenBudgeDragon","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex43 = GetPrivateProfileInt("GoldenBudgeDragon","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level43 = GetPrivateProfileInt("GoldenBudgeDragon","ItemLevel",8,GoldenDrop_DIR);

	this->GoldenDrop.ItemType78 = GetPrivateProfileInt("GoldenGoblin","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex78 = GetPrivateProfileInt("GoldenGoblin","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level78 = GetPrivateProfileInt("GoldenGoblin","ItemLevel",8,GoldenDrop_DIR);

	this->GoldenDrop.ItemType493 = GetPrivateProfileInt("GoldenDarkKnight","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex493 = GetPrivateProfileInt("GoldenDarkKnight","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level493 = GetPrivateProfileInt("GoldenDarkKnight","ItemLevel",8,GoldenDrop_DIR);

	this->GoldenDrop.ItemType53 = GetPrivateProfileInt("GoldenTitan","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex53 = GetPrivateProfileInt("GoldenTitan","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level53 = GetPrivateProfileInt("GoldenTitan","ItemLevel",8,GoldenDrop_DIR);

	this->GoldenDrop.ItemType54 = GetPrivateProfileInt("GoldenSoldier","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex54 = GetPrivateProfileInt("GoldenSoldier","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level54 = GetPrivateProfileInt("GoldenSoldier","ItemLevel",8,GoldenDrop_DIR);

	this->GoldenDrop.ItemType80 = GetPrivateProfileInt("GoldenLizardKing","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex80 = GetPrivateProfileInt("GoldenLizardKing","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level80 = GetPrivateProfileInt("GoldenLizardKing","ItemLevel",9,GoldenDrop_DIR);

	this->GoldenDrop.ItemType81 = GetPrivateProfileInt("GoldenVepar","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex81 = GetPrivateProfileInt("GoldenVepar","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level81 = GetPrivateProfileInt("GoldenVepar","ItemLevel",9,GoldenDrop_DIR);

	this->GoldenDrop.ItemType494 = GetPrivateProfileInt("GoldenDevil","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex494 = GetPrivateProfileInt("GoldenDevil","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level494 = GetPrivateProfileInt("GoldenDevil","ItemLevel",9,GoldenDrop_DIR);

	this->GoldenDrop.ItemType82 = GetPrivateProfileInt("GoldenTantalos","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex82 = GetPrivateProfileInt("GoldenTantalos","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level82 = GetPrivateProfileInt("GoldenTantalos","ItemLevel",10,GoldenDrop_DIR);

	this->GoldenDrop.ItemType83 = GetPrivateProfileInt("GoldenWheel","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex83 = GetPrivateProfileInt("GoldenWheel","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level83 = GetPrivateProfileInt("GoldenWheel","ItemLevel",10,GoldenDrop_DIR);

	this->GoldenDrop.ItemType495 = GetPrivateProfileInt("GoldenGolem","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex495 = GetPrivateProfileInt("GoldenGolem","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level495 = GetPrivateProfileInt("GoldenGolem","ItemLevel",10,GoldenDrop_DIR);

	this->GoldenDrop.ItemType496 = GetPrivateProfileInt("GoldenCrust","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex496 = GetPrivateProfileInt("GoldenCrust","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level496 = GetPrivateProfileInt("GoldenCrust","ItemLevel",10,GoldenDrop_DIR);

	this->GoldenDrop.ItemType497 = GetPrivateProfileInt("GoldenSatyrus","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex497 = GetPrivateProfileInt("GoldenSatyrus","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level497 = GetPrivateProfileInt("GoldenSatyrus","ItemLevel",11,GoldenDrop_DIR);

	this->GoldenDrop.ItemType498 = GetPrivateProfileInt("GoldenTwinTale","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex498 = GetPrivateProfileInt("GoldenTwinTale","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level498 = GetPrivateProfileInt("GoldenTwinTale","ItemLevel",11,GoldenDrop_DIR);

	this->GoldenDrop.ItemType499 = GetPrivateProfileInt("GoldenIronKnight","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex499 = GetPrivateProfileInt("GoldenIronKnight","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level499 = GetPrivateProfileInt("GoldenIronKnight","ItemLevel",12,GoldenDrop_DIR);

	this->GoldenDrop.ItemType500 = GetPrivateProfileInt("GoldenNapin","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex500 = GetPrivateProfileInt("GoldenNapin","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level500 = GetPrivateProfileInt("GoldenNapin","ItemLevel",12,GoldenDrop_DIR);

	this->GoldenDrop.ItemType79 = GetPrivateProfileInt("GoldenDragon","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex79 = GetPrivateProfileInt("GoldenDragon","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.randlevel1_79 = GetPrivateProfileInt("GoldenDragon","randlevel1",8,GoldenDrop_DIR);
	this->GoldenDrop.randlevel2_79 = GetPrivateProfileInt("GoldenDragon","randlevel2",9,GoldenDrop_DIR);
	this->GoldenDrop.randlevel3_79 = GetPrivateProfileInt("GoldenDragon","randlevel3",10,GoldenDrop_DIR);
	this->GoldenDrop.countitem79 = GetPrivateProfileInt("GoldenDragon","countitem",5,GoldenDrop_DIR);

	this->GoldenDrop.ItemType501 = GetPrivateProfileInt("GoldenGreatDragon","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex501 = GetPrivateProfileInt("GoldenGreatDragon","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.randlevel1_501 = GetPrivateProfileInt("GoldenGreatDragon","randlevel1",11,GoldenDrop_DIR);
	this->GoldenDrop.randlevel2_501 = GetPrivateProfileInt("GoldenGreatDragon","randlevel2",12,GoldenDrop_DIR);
	this->GoldenDrop.countitem501 = GetPrivateProfileInt("GoldenGreatDragon","countitem",5,GoldenDrop_DIR);

	//---------------------------------
	//			Player Connect
	//---------------------------------

	this->PlayerConnect.EnablePlayerConnectSystem = GetPrivateProfileInt("Common","Enable",0,PlayerConnect_DIR);	
	this->PlayerConnect.ShowReset = GetPrivateProfileInt("Common","ShowReset",0,PlayerConnect_DIR);
	this->PlayerConnect.ShowGReset = GetPrivateProfileInt("Common","ShowGReset",0,PlayerConnect_DIR);
	this->PlayerConnect.ShowOnline = GetPrivateProfileInt("Common","ShowOnline",0,PlayerConnect_DIR);

	this->PlayerConnect.ShowNameAll = GetPrivateProfileInt("Common","ShowNameAll",0,PlayerConnect_DIR);
	this->PlayerConnect.ShowNameColor = GetPrivateProfileInt("Common","ShowNameColor",0,PlayerConnect_DIR);
	this->PlayerConnect.ShowGMAll = GetPrivateProfileInt("Common","ShowGMAll",0,PlayerConnect_DIR);

	this->PlayerConnect.ShowWcoinC = GetPrivateProfileInt("Common","ShowWcoinC",0,PlayerConnect_DIR);
	this->PlayerConnect.ShowGP = GetPrivateProfileInt("Common","ShowGP",0,PlayerConnect_DIR);
	this->PlayerConnect.ShowZtCredit = GetPrivateProfileInt("Common","ShowZtCredit",1,PlayerConnect_DIR);

	if(this->PlayerConnect.ShowNameColor < 1 || this->PlayerConnect.ShowNameColor > 9)
	{
		this->PlayerConnect.ShowNameColor = 3;
	}

	//=========================
	//			Message Config
	//===========================
#ifdef _MESSAGE_CONFIG_
	GetPrivateProfileString("MessageConfig", "HappyHour","[Happy Hour] Event Start For %d Minutes",MessageConfig.HappyHour,100,MessageConfig_DIR);
	GetPrivateProfileString("MessageConfig", "DropEvent","[Drop Event] Event Start For %d Minutes",MessageConfig.DropEvent,100,MessageConfig_DIR);
	GetPrivateProfileString("MessageConfig", "SearchEvent","[Search Event] Event Start For %d Minutes",MessageConfig.SearchEvent,100,MessageConfig_DIR);
#endif
#ifdef _CONFLICT_
		if(g_ZtLicense.CheckUser(eZtUB::drynea))
		{
		this->GmMap.GmMap	= GetPrivateProfileInt("GmMap","GmMap",0,"..\\Data\\ZtData\\GmMap.ini");
		this->GmMap.GmX		= GetPrivateProfileInt("GmMap","GmX",0,"..\\Data\\ZtData\\GmMap.ini");
		this->GmMap.GMY		= GetPrivateProfileInt("GmMap","GmY",0,"..\\Data\\ZtData\\GmMap.ini");
			
		}

#endif


#ifdef PRIDEMU_CONFIG
	if(g_ZtLicense.CheckUser(eZtUB::PrideMuLocal) || g_ZtLicense.CheckUser(eZtUB::PrideMu))
	{
		PrideMu.MasterMoney =  GetPrivateProfileInt("MasterZen","MasterMoney",0,PrideMuConfig_DIR);
		PrideMu.DiapasonMasterMoney =  GetPrivateProfileInt("MasterZen","DiapasonMasterMoney",1,PrideMuConfig_DIR);

		//Illusion Fenrir
		PrideMu.AddLife =  GetPrivateProfileInt("Fenrir","AddLife",0,PrideMuConfig_DIR);
		PrideMu.AddMana =  GetPrivateProfileInt("Fenrir","AddMana",0,PrideMuConfig_DIR);
		PrideMu.AttackDamageMin =  GetPrivateProfileInt("Fenrir","AttackDamageMin",0,PrideMuConfig_DIR);
		PrideMu.AttackDamageMax =  GetPrivateProfileInt("Fenrir","AttackDamageMax",0,PrideMuConfig_DIR);
		PrideMu.MagicDamageMin =  GetPrivateProfileInt("Fenrir","MagicDamageMin",0,PrideMuConfig_DIR);
		PrideMu.MagicDamageMax =  GetPrivateProfileInt("Fenrir","MagicDamageMax",0,PrideMuConfig_DIR);
		//Protect Fenrir
		PrideMu.DecPercent =  GetPrivateProfileInt("Fenrir","DecPercent",0,PrideMuConfig_DIR);
		//Destroy Fenrir
		PrideMu.IncPercent =  GetPrivateProfileInt("Fenrir","IncPercent",0,PrideMuConfig_DIR);

		PrideMu.OffDecreaseDur = GetPrivateProfileInt("Fenrir","OffDecreaseDur",0,PrideMuConfig_DIR);

		PrideMu.ComboBase = GetPrivateProfileInt("BK","ComboBase",100,PrideMuConfig_DIR);
		PrideMu.Fortitude = GetPrivateProfileInt("BK","Fortitude",100,PrideMuConfig_DIR);
		PrideMu.LevelLifeSM = GetPrivateProfileInt("MaxLife","LevelLifeSM",0,PrideMuConfig_DIR);
		PrideMu.VitalityToLifeSM = GetPrivateProfileInt("MaxLife","VitalityToLifeSM",0,PrideMuConfig_DIR);

		PrideMu.LevelLifeDK = GetPrivateProfileInt("MaxLife","LevelLifeDK",0,PrideMuConfig_DIR);
		PrideMu.VitalityToLifeDK = GetPrivateProfileInt("MaxLife","VitalityToLifeDK",0,PrideMuConfig_DIR);

		PrideMu.LevelLifeELF = GetPrivateProfileInt("MaxLife","LevelLifeELF",0,PrideMuConfig_DIR);
		PrideMu.VitalityToLifeELF = GetPrivateProfileInt("MaxLife","VitalityToLifeELF",0,PrideMuConfig_DIR);

		PrideMu.LevelLifeMG = GetPrivateProfileInt("MaxLife","LevelLifeMG",0,PrideMuConfig_DIR);
		PrideMu.VitalityToLifeMG = GetPrivateProfileInt("MaxLife","VitalityToLifeMG",0,PrideMuConfig_DIR);

		PrideMu.LevelLifeDL = GetPrivateProfileInt("MaxLife","LevelLifeDL",0,PrideMuConfig_DIR);
		PrideMu.VitalityToLifeDL = GetPrivateProfileInt("MaxLife","VitalityToLifeDL",0,PrideMuConfig_DIR);

		PrideMu.LevelLifeSUM = GetPrivateProfileInt("MaxLife","LevelLifeSUM",0,PrideMuConfig_DIR);
		PrideMu.VitalityToLifeSUM = GetPrivateProfileInt("MaxLife","VitalityToLifeSUM",0,PrideMuConfig_DIR);

		PrideMu.LevelLifeRF = GetPrivateProfileInt("MaxLife","LevelLifeRF",0,PrideMuConfig_DIR);
		PrideMu.VitalityToLifeRF = GetPrivateProfileInt("MaxLife","VitalityToLifeRF",0,PrideMuConfig_DIR);

	}

#endif
#ifdef DRYNEA_LIST_CUSTOM
		
	DryneaConfig.KundumItemsDrop =  GetPrivateProfileInt("ItemsDrop","KundumItemsDrop", 10000, DryneaMuConfig_DIR);
	DryneaConfig.ErohimItemsDrop =  GetPrivateProfileInt("ItemsDrop","ErohimItemsDrop", 10000, DryneaMuConfig_DIR);

	if(g_ZtLicense.CheckUser(eZtUB::drynea))
	{

		DryneaConfig.PostFloodProtect = GetPrivateProfileInt("FloodInPost","IsPostFloodProtect", 0, DryneaMuConfig_DIR);
		DryneaConfig.PostFloodProtectTime = GetPrivateProfileInt("FloodInPost","FloodProtectTime", 0, DryneaMuConfig_DIR);
		if(DryneaConfig.PostFloodProtectTime > 5000)
		{
			DryneaConfig.PostFloodProtectTime = 5000;
		}

		DryneaConfig.GMKillMap  =  GetPrivateProfileInt("GMMap","GMKillMap",0,DryneaMuConfig_DIR);
		DryneaConfig.GMKillMapX = GetPrivateProfileInt("GMMap","GMKillMapX",0,DryneaMuConfig_DIR);
		DryneaConfig.GMKillMapY =  GetPrivateProfileInt("GMMap","GMKillMapY",0,DryneaMuConfig_DIR);

		DryneaConfig.PartySystemEnable	=	GetPrivateProfileInt("PartySystem","PartySystemEnable",0,DryneaMuConfig_DIR);
		DryneaConfig.Silver				=	GetPrivateProfileInt("PartySystem","Silver",0,DryneaMuConfig_DIR);
		DryneaConfig.Gold				=	GetPrivateProfileInt("PartySystem","Gold",0,DryneaMuConfig_DIR);
		DryneaConfig.ExpMinus			=	GetPrivateProfileInt("PartySystem","ExpMinus",0,DryneaMuConfig_DIR);
		//DryneaConfig.StartDiapason1		=	GetPrivateProfileInt("PartySystem","StartDiapason1",0,DryneaMuConfig_DIR);
		//DryneaConfig.EndDiapason1		=	GetPrivateProfileInt("PartySystem","EndDiapason1",0,DryneaMuConfig_DIR);
		//DryneaConfig.StartDiapason2		=	GetPrivateProfileInt("PartySystem","StartDiapason2",0,DryneaMuConfig_DIR);
		//DryneaConfig.EndDiapason2		=	GetPrivateProfileInt("PartySystem","EndDiapason2",0,DryneaMuConfig_DIR);
		//DryneaConfig.StartDiapason3		=	GetPrivateProfileInt("PartySystem","StartDiapason3",0,DryneaMuConfig_DIR);
		//DryneaConfig.EndDiapason3		=	GetPrivateProfileInt("PartySystem","EndDiapason3",0,DryneaMuConfig_DIR);
			
		DryneaConfig.CountKundumItemsDrop =  GetPrivateProfileInt("ItemsDrop","CountKundumItemsDrop", 3, DryneaMuConfig_DIR);
		DryneaConfig.CountErohimItemsDrop =  GetPrivateProfileInt("ItemsDrop","CountErohimItemsDrop", 1, DryneaMuConfig_DIR);

		for(int i(0);i<MAXPARTY_DIAPASON;i++)
		{
			DryneaConfig.PartyDiapason[i].StartDiapason = 0;
			DryneaConfig.PartyDiapason[i].EndDiapason = 0;
		}
		FILE * file = fopen(DryneaMuConfig_DIR,"r");
		if(file == NULL)
		{
			MessageBoxA(0,DryneaMuConfig_DIR,"LOAD FILE ERROR",0);
			ExitProcess(0);
		}

		char Buff[256];
		int Flag = 0;
		DryneaConfig.CountPartyDiapason = 0;

		while(!feof(file))
		{
			fgets(Buff,256,file);
			if(Zt_IsBadFileLine(Buff, Flag))
				continue;
			if(Flag == 1)
			{
				if(DryneaConfig.CountPartyDiapason == MAXPARTY_DIAPASON) break;
				int n[2];
				sscanf(Buff, "%d %d", &n[0], &n[1]);
				DryneaConfig.PartyDiapason[DryneaConfig.CountPartyDiapason].StartDiapason = n[0];
				DryneaConfig.PartyDiapason[DryneaConfig.CountPartyDiapason].EndDiapason = n[1];
				DryneaConfig.CountPartyDiapason++;
			}
		}
		fclose(file);
	/*
			[PartySystem]
			Silver = 10; +10% опыта каждому
			Gold = +20% опыта каждому
			ExpMinus = 30 (штраф на опыт в диапазонах)

			1
			//[Start duapazon reset] [End diapazon reset]
			0 20
			21 80
			81 150
			end
		*/
	}

	if(g_ZtLicense.CheckUser(eZtUB::MedoniAndrei))
	{
		DryneaConfig.PostFloodProtect = GetPrivateProfileInt("FloodInPost","IsPostFloodProtect", 0, DryneaMuConfig_DIR);
		DryneaConfig.PostFloodProtectTime = GetPrivateProfileInt("FloodInPost","FloodProtectTime", 0, DryneaMuConfig_DIR);
		if(DryneaConfig.PostFloodProtectTime > 5000)
		{
			DryneaConfig.PostFloodProtectTime = 5000;
		}

		DryneaConfig.GMKillMap  =  GetPrivateProfileInt("GMMap","GMKillMap",0,DryneaMuConfig_DIR);
		DryneaConfig.GMKillMapX = GetPrivateProfileInt("GMMap","GMKillMapX",0,DryneaMuConfig_DIR);
		DryneaConfig.GMKillMapY =  GetPrivateProfileInt("GMMap","GMKillMapY",0,DryneaMuConfig_DIR);


	}
	

#endif


#ifdef LVL_UP_POINTS
		AddLvlPoint.DkLevelPoints  =  GetPrivateProfileInt("Common","DkLevelPoints",5,ADD_LVL_POINTS_DIR);
		AddLvlPoint.DwLevelPoints = GetPrivateProfileInt("Common","DwLevelPoints",5,ADD_LVL_POINTS_DIR);
		AddLvlPoint.ElfLevelPoints =  GetPrivateProfileInt("Common","ElfLevelPoints",5,ADD_LVL_POINTS_DIR);
		AddLvlPoint.SumLevelPoints =  GetPrivateProfileInt("Common","SumLevelPoints",5,ADD_LVL_POINTS_DIR);
		AddLvlPoint.MgLevelPoints =  GetPrivateProfileInt("Common","MgLevelPoints",7,ADD_LVL_POINTS_DIR);
		AddLvlPoint.DlLevelPoints =  GetPrivateProfileInt("Common","DlLevelPoints",7,ADD_LVL_POINTS_DIR);
		AddLvlPoint.RfLevelPoints =  GetPrivateProfileInt("Common","RfLevelPoints",7,ADD_LVL_POINTS_DIR);

		AddMasterLvlPoint.DkLevelPoints  =  GetPrivateProfileInt("Master","DkLevelPoints",1,ADD_LVL_POINTS_DIR);
		AddMasterLvlPoint.DwLevelPoints = GetPrivateProfileInt("Master","DwLevelPoints",1,ADD_LVL_POINTS_DIR);
		AddMasterLvlPoint.ElfLevelPoints =  GetPrivateProfileInt("Master","ElfLevelPoints",1,ADD_LVL_POINTS_DIR);
		AddMasterLvlPoint.SumLevelPoints =  GetPrivateProfileInt("Master","SumLevelPoints",1,ADD_LVL_POINTS_DIR);
		AddMasterLvlPoint.MgLevelPoints =  GetPrivateProfileInt("Master","MgLevelPoints",1,ADD_LVL_POINTS_DIR);
		AddMasterLvlPoint.DlLevelPoints =  GetPrivateProfileInt("Master","DlLevelPoints",1,ADD_LVL_POINTS_DIR);
		AddMasterLvlPoint.RfLevelPoints =  GetPrivateProfileInt("Master","RfLevelPoints",1,ADD_LVL_POINTS_DIR);

		AddMarlonPoint.DkLevelPoints  =  GetPrivateProfileInt("Marlon","DkLevelPoints",1,ADD_LVL_POINTS_DIR);
		AddMarlonPoint.DwLevelPoints = GetPrivateProfileInt("Marlon","DwLevelPoints",1,ADD_LVL_POINTS_DIR);
		AddMarlonPoint.ElfLevelPoints =  GetPrivateProfileInt("Marlon","ElfLevelPoints",1,ADD_LVL_POINTS_DIR);
		AddMarlonPoint.SumLevelPoints =  GetPrivateProfileInt("Marlon","SumLevelPoints",1,ADD_LVL_POINTS_DIR);
		AddMarlonPoint.MgLevelPoints =  GetPrivateProfileInt("Marlon","MgLevelPoints",1,ADD_LVL_POINTS_DIR);
		AddMarlonPoint.DlLevelPoints =  GetPrivateProfileInt("Marlon","DlLevelPoints",1,ADD_LVL_POINTS_DIR);
		AddMarlonPoint.RfLevelPoints =  GetPrivateProfileInt("Marlon","RfLevelPoints",1,ADD_LVL_POINTS_DIR);

		AddClass2rdPoint.DkLevelPoints  =  GetPrivateProfileInt("Class2rd","DkLevelPoints",5,ADD_LVL_POINTS_DIR);
		AddClass2rdPoint.DwLevelPoints = GetPrivateProfileInt("Class2rd","DwLevelPoints",5,ADD_LVL_POINTS_DIR);
		AddClass2rdPoint.ElfLevelPoints =  GetPrivateProfileInt("Class2rd","ElfLevelPoints",5,ADD_LVL_POINTS_DIR);
		AddClass2rdPoint.SumLevelPoints =  GetPrivateProfileInt("Class2rd","SumLevelPoints",5,ADD_LVL_POINTS_DIR);

		AddClass3rdPoint.DkLevelPoints  =  GetPrivateProfileInt("Class3rd","DkLevelPoints",5,ADD_LVL_POINTS_DIR);
		AddClass3rdPoint.DwLevelPoints = GetPrivateProfileInt("Class3rd","DwLevelPoints",5,ADD_LVL_POINTS_DIR);
		AddClass3rdPoint.ElfLevelPoints =  GetPrivateProfileInt("Class3rd","ElfLevelPoints",5,ADD_LVL_POINTS_DIR);
		AddClass3rdPoint.SumLevelPoints =  GetPrivateProfileInt("Class3rd","SumLevelPoints",5,ADD_LVL_POINTS_DIR);
		AddClass3rdPoint.MgLevelPoints =  GetPrivateProfileInt("Class3rd","MgLevelPoints",7,ADD_LVL_POINTS_DIR);
		AddClass3rdPoint.DlLevelPoints =  GetPrivateProfileInt("Class3rd","DlLevelPoints",7,ADD_LVL_POINTS_DIR);
		AddClass3rdPoint.RfLevelPoints =  GetPrivateProfileInt("Class3rd","RfLevelPoints",7,ADD_LVL_POINTS_DIR);
#endif
//---

	this->iTeleportMapForDieMap6 =  GetPrivateProfileInt("Common","TeleportMapForDieMap6",0,MAPDIE_PATH);
	this->iTeleportMapForDieMap40 =  GetPrivateProfileInt("Common","TeleportMapForDieMap40",0,MAPDIE_PATH);
	this->iTeleportMapForDieMap51 =  GetPrivateProfileInt("Common","TeleportMapForDieMap51",0,MAPDIE_PATH);

	this->DW_MapStart = GetPrivateProfileInt("ZtTeam","DW_MapStart",0,MAPSTART_PATH);
	this->DW_X = GetPrivateProfileInt("ZtTeam","DW_X",-1,MAPSTART_PATH);
	this->DW_Y = GetPrivateProfileInt("ZtTeam","DW_Y",-1,MAPSTART_PATH);
	this->DK_MapStart = GetPrivateProfileInt("ZtTeam","DK_MapStart",0,MAPSTART_PATH);
	this->DK_X = GetPrivateProfileInt("ZtTeam","DK_X",-1,MAPSTART_PATH);
	this->DK_Y = GetPrivateProfileInt("ZtTeam","DK_Y",-1,MAPSTART_PATH);
	this->EE_MapStart = GetPrivateProfileInt("ZtTeam","EE_MapStart",0,MAPSTART_PATH);
	this->EE_X = GetPrivateProfileInt("ZtTeam","EE_X",-1,MAPSTART_PATH);
	this->EE_Y = GetPrivateProfileInt("ZtTeam","EE_Y",-1,MAPSTART_PATH);
	this->SU_MapStart = GetPrivateProfileInt("ZtTeam","SU_MapStart",0,MAPSTART_PATH);
	this->SU_X = GetPrivateProfileInt("ZtTeam","SU_X",-1,MAPSTART_PATH);
	this->SU_Y = GetPrivateProfileInt("ZtTeam","SU_Y",-1,MAPSTART_PATH);
	this->MG_MapStart = GetPrivateProfileInt("ZtTeam","MG_MapStart",0,MAPSTART_PATH);
	this->MG_X = GetPrivateProfileInt("ZtTeam","MG_X",-1,MAPSTART_PATH);
	this->MG_Y = GetPrivateProfileInt("ZtTeam","MG_Y",-1,MAPSTART_PATH);
	this->DL_MapStart = GetPrivateProfileInt("ZtTeam","DL_MapStart",0,MAPSTART_PATH);
	this->DL_X = GetPrivateProfileInt("ZtTeam","DL_X",-1,MAPSTART_PATH);
	this->DL_Y = GetPrivateProfileInt("ZtTeam","DL_Y",-1,MAPSTART_PATH);
	this->RF_MapStart = GetPrivateProfileInt("ZtTeam","RF_MapStart",0,MAPSTART_PATH);
	this->RF_X = GetPrivateProfileInt("ZtTeam","RF_X",-1,MAPSTART_PATH);
	this->RF_Y = GetPrivateProfileInt("ZtTeam","RF_Y",-1,MAPSTART_PATH);

	if(g_ZtLicense.CheckUser(eZtUB::Local)  || g_ZtLicense.CheckUser(eZtUB::eternalmu) ||
	   g_ZtLicense.CheckUser(eZtUB::Artem)  || g_ZtLicense.CheckUser(eZtUB::Artem2)	|| 
	   g_ZtLicense.CheckUser(eZtUB::NSGames)|| 
	   g_ZtLicense.CheckUser(eZtUB::ulasevich)	|| g_ZtLicense.CheckUser(eZtUB::ulasevich2))
	{
		this->m_bNewBuffPremiumEnable = GetPrivateProfileInt("ZtTeam","NewBuffPremiumEnable",0,NEWBUFF_PATH);
		this->m_iNewBuffPremiumDamage = GetPrivateProfileInt("ZtTeam","NewBuffPremiumDamage",0,NEWBUFF_PATH);
		this->m_iNewBuffPremiumDefence = GetPrivateProfileInt("ZtTeam","NewBuffPremiumDefence",0,NEWBUFF_PATH);

		this->m_bNewBuffGuildEnable = GetPrivateProfileInt("ZtTeam","NewBuffGuildEnable",0,NEWBUFF_PATH);
		this->m_bNewBuffGuildMembOnline = GetPrivateProfileInt("ZtTeam","NewBuffGuildMembOnline",0,NEWBUFF_PATH);
		this->m_iNewBuffGuildDamage = GetPrivateProfileInt("ZtTeam","NewBuffGuildDamage",0,NEWBUFF_PATH);
		this->m_iNewBuffGuildDefence = GetPrivateProfileInt("ZtTeam","NewBuffGuildDefence",0,NEWBUFF_PATH);

		this->m_bNewBuffPartyEnable = GetPrivateProfileInt("ZtTeam","NewBuffPartyEnable",0,NEWBUFF_PATH);
		this->m_bNewBuffPartyMembCount = GetPrivateProfileInt("ZtTeam","NewBuffPartyMembCount",0,NEWBUFF_PATH);
		this->m_iNewBuffPartyDamage = GetPrivateProfileInt("ZtTeam","NewBuffPartyDamage",0,NEWBUFF_PATH);
		this->m_iNewBuffPartyDefence = GetPrivateProfileInt("ZtTeam","NewBuffPartyDefence",0,NEWBUFF_PATH);
	}
	else
	{
		this->m_bNewBuffPremiumEnable = false;
		this->m_bNewBuffGuildEnable = false;
		this->m_bNewBuffPartyEnable = false;
	}


	//---------------------------------
	//			All Character reload
	//---------------------------------

	for (int n=OBJ_STARTUSERINDZT;n<OBJMAX; n++)
	{
		LPOBJ lpObj = &gObj[n];
		if ( lpObj->Connected >= PLAYER_PLAYING)
		{
			gObjCalCharacter(n);
		}
	}

	

}