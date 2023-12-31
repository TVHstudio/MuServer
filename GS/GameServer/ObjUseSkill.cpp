//GameServer 1.00.90 JPN - Completed
#include "StdAfx.h"
#include "ObjUseSkill.h"
#include "ObjCalCharacter.h"
#include "GameMain.h"
#include "ChaosCastle.h"
#include "GameServer.h"
#include "WzAG.h"
#include "user.h"
#include "zzzmathlib.h"
#include "SkillHitBox.h"
#include "MoveCommand.h"
#include "SkillAdditionInfo.h"
#include "IllusionTempleEvent.h"
#include "NewMasterLevelSkillTreeSystem.h"
#include "BuffManager.h"
#include "LogProc.h"
#include "..\common\winutil.h"
#include "Raklion.h"
#include "RaklionBattleUserMng.h"
#include "Configs.h"
#include "GensSystem.h"
#include "ItemAddOption.h"
#ifdef IMPERIAL_CONFLICT_NEW
#include "ImperialGuardian.h"
#endif 
#include "ZtLicense.h"
#include "TeleportManager.h"
#include "PandoraBoxEvent.h"
#include "ZtTeleport.h"
#include "ZtTeleportEvo.h"

CObjUseSkill gObjUseSkill;

CObjUseSkill::CObjUseSkill()
{

}

CObjUseSkill::~CObjUseSkill()
{

}

int CObjUseSkill::GetTargetLinePath(int sx, int sy, int tx, int ty, int * PathX, int * PathY, int distance) //004E97F0
{
	int x,y;
	int delta_x,delta_y;
	int half;

	int error = 0;

	int incx = 1,incy = 1;
	int dis;
	int count;

	if(sx > tx)
	{
		incx = -1;
		delta_x = sx - tx;
	}
	else
	{
		delta_x = tx - sx;
	}

	if(sy > ty)
	{
		incy = -1;
		delta_y = sy - ty;
	}
	else
	{
		delta_y = ty - sy;
	}

	dis = (int)(sqrt((float)(delta_x * delta_x + delta_y * delta_y)));
	dis = distance - dis;

	count = 0;
	PathX[count] = sx;
	PathY[count] = sy;
	count++;

	if(delta_x > delta_y)
	{
		y = sy;
		half = delta_x / 2;

		if(incx > 0)
		{
			for(x = (sx+1); x <= (tx + dis); x++)
			{
				error += delta_y;

				if(error > half)
				{
					y += incy;
					error -= delta_x;
				}

				PathX[count] = x;
				PathY[count] = y;

				count++;
			}
		}
		else
		{
			for(x = (sx-1); x >= (tx - dis);x--)
			{
				error += delta_y;

				if(error > half)
				{
					y += incy;
					error -= delta_x;
				}

				PathX[count] = x;
				PathY[count] = y;

				count++;
			}
		}
	}
	else
	{
		x = sx;
		half = delta_y / 2;

		if(incy > 0)
		{
			for(y = (sy+1); y <= (ty + dis);y++)
			{
				error += delta_x;

				if(error > half)
				{
					x += incx;
					error -= delta_y;
				}

				PathX[count] = x;
				PathY[count] = y;
				count++;
			}
		}
		else
		{
			for(y = (sy-1);y >= (ty - dis);y--)
			{
				error += delta_x;

				if(error > half)
				{
					x += incx;
					error -= delta_y;
				}

				PathX[count] = x;
				PathY[count] = y;
				count++;
			}
		}
	}
	return count;
}

BOOL CObjUseSkill::SpeedHackCheck(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	int iTimeCalc = GetTickCount() - lpObj->m_LastAttackTime;

	if(lpObj->Type != OBJ_USER)
	{
		return TRUE;
	}

	if(iTimeCalc < lpObj->m_DetectSpeedHackTime)
	{
		lpObj->m_DetectCount++;
		lpObj->m_SumLastAttackTime += iTimeCalc;

		if(lpObj->m_DetectCount > gHackCheckCount)
		{
			lpObj->m_DetectedHackKickCount++;

			if(gIsKickDetecHackCountLimit != 0 && lpObj->m_DetectedHackKickCount > gDetectedHackKickCount)
			{
				LogAddTD("[%s][%s] %s Kick DetecHackCountLimit Over User (%d)", lpObj->AccountID,lpObj->Name,lMsg.Get(lpObj->Class+1900),lpObj->m_DetectedHackKickCount);
#ifndef SPEEDHACK_DEBUG
				CloseClient(aIndex);
#endif
				return false;
			}

			lpObj->m_SpeedHackPenalty = gSpeedHackPenalty;
			LogAddTD("[%s][%s] %s Attack Speed Is Wrong MagicSkill (%d)(%d) Penalty %d", lpObj->AccountID,lpObj->Name,lMsg.Get(lpObj->Class+1900),lpObj->m_DetectSpeedHackTime,lpObj->m_SumLastAttackTime / lpObj->m_DetectCount,lpObj->m_SpeedHackPenalty);
		}
	}
	else
	{
		lpObj->m_SumLastAttackTime = 0;
		lpObj->m_DetectCount = 0;
	}

	lpObj->m_LastAttackTime = GetTickCount();

	if(bIsIgnorePacketSpeedHackDetect != 0 && lpObj->m_SpeedHackPenalty > 0)
	{
		lpObj->m_SpeedHackPenalty--;
		LogAddTD("[%s][%s] %s Apply Attack Speed Penalty (%d left)", lpObj->AccountID,lpObj->Name,lMsg.Get(lpObj->Class + 1900),lpObj->m_SpeedHackPenalty);
		return false;
	}
	return true;
}

//Identical
BOOL CObjUseSkill::EnableSkill(DWORD Skill, int Level) //004E9E10
{
	if(g_MasterSkillSystem.CheckRequireStatus(Skill) != FALSE) //Season3 add-on
	{
		int GetBaseMasterLevelSkill = g_MasterSkillSystem.GetBaseMasterLevelSkill(Skill);

#ifdef DEBUG_CODE
		LogAddC(5,"GetBaseMasterLevelSkill: %d",GetBaseMasterLevelSkill);
#endif

		if(	 GetBaseMasterLevelSkill != 403
          && GetBaseMasterLevelSkill != 388
          && GetBaseMasterLevelSkill != 330
          && GetBaseMasterLevelSkill != 413
          && GetBaseMasterLevelSkill != 414
          && GetBaseMasterLevelSkill != 481
          && GetBaseMasterLevelSkill != 356
          && GetBaseMasterLevelSkill != 382
          && GetBaseMasterLevelSkill != 512
          && GetBaseMasterLevelSkill != 508
          && GetBaseMasterLevelSkill != 385
          && GetBaseMasterLevelSkill != 391
          && GetBaseMasterLevelSkill != 336
          && GetBaseMasterLevelSkill != 331
          && GetBaseMasterLevelSkill != 417
          && GetBaseMasterLevelSkill != 420
          && GetBaseMasterLevelSkill != 490
          && GetBaseMasterLevelSkill != 482
          && GetBaseMasterLevelSkill != 518
          && GetBaseMasterLevelSkill != 487
          && GetBaseMasterLevelSkill != 454
          && GetBaseMasterLevelSkill != 455
          && GetBaseMasterLevelSkill != 456
          && GetBaseMasterLevelSkill != 458
          && GetBaseMasterLevelSkill != 326
          && GetBaseMasterLevelSkill != 327
          && GetBaseMasterLevelSkill != 328
          && GetBaseMasterLevelSkill != 329
          && GetBaseMasterLevelSkill != 332
          && GetBaseMasterLevelSkill != 333
          && GetBaseMasterLevelSkill != 337
          && GetBaseMasterLevelSkill != 339
          && GetBaseMasterLevelSkill != 340
          && GetBaseMasterLevelSkill != 342
          && GetBaseMasterLevelSkill != 343
          && GetBaseMasterLevelSkill != 344
          && GetBaseMasterLevelSkill != 346
          && GetBaseMasterLevelSkill != 360
          && GetBaseMasterLevelSkill != 363
          && GetBaseMasterLevelSkill != 376
          && GetBaseMasterLevelSkill != 378
          && GetBaseMasterLevelSkill != 379
          && GetBaseMasterLevelSkill != 380
          && GetBaseMasterLevelSkill != 381
          && GetBaseMasterLevelSkill != 383
          && GetBaseMasterLevelSkill != 384
          && GetBaseMasterLevelSkill != 386
          && GetBaseMasterLevelSkill != 387
          && GetBaseMasterLevelSkill != 389
          && GetBaseMasterLevelSkill != 390
          && GetBaseMasterLevelSkill != 392
          && GetBaseMasterLevelSkill != 393
          && GetBaseMasterLevelSkill != 394
          && GetBaseMasterLevelSkill != 395
          && GetBaseMasterLevelSkill != 396
          && GetBaseMasterLevelSkill != 404
          && GetBaseMasterLevelSkill != 406
          && GetBaseMasterLevelSkill != 411
          && GetBaseMasterLevelSkill != 415
          && GetBaseMasterLevelSkill != 416
          && GetBaseMasterLevelSkill != 418
          && GetBaseMasterLevelSkill != 419
          && GetBaseMasterLevelSkill != 425
          && GetBaseMasterLevelSkill != 426
          && GetBaseMasterLevelSkill != 427
          && GetBaseMasterLevelSkill != 428
          && GetBaseMasterLevelSkill != 429
          && GetBaseMasterLevelSkill != 430
          && GetBaseMasterLevelSkill != 431
          && GetBaseMasterLevelSkill != 432
          && GetBaseMasterLevelSkill != 433
          && GetBaseMasterLevelSkill != 434
          && GetBaseMasterLevelSkill != 441
          && GetBaseMasterLevelSkill != 459
          && GetBaseMasterLevelSkill != 460
          && GetBaseMasterLevelSkill != 461
          && GetBaseMasterLevelSkill != 462
          && GetBaseMasterLevelSkill != 466
          && GetBaseMasterLevelSkill != 468
          && GetBaseMasterLevelSkill != 469
          && GetBaseMasterLevelSkill != 470
          && GetBaseMasterLevelSkill != 472
          && GetBaseMasterLevelSkill != 477
          && GetBaseMasterLevelSkill != 479
          && GetBaseMasterLevelSkill != 480
          && GetBaseMasterLevelSkill != 483
          && GetBaseMasterLevelSkill != 484
          && GetBaseMasterLevelSkill != 486
          && GetBaseMasterLevelSkill != 488
          && GetBaseMasterLevelSkill != 489
          && GetBaseMasterLevelSkill != 491
          && GetBaseMasterLevelSkill != 492
          && GetBaseMasterLevelSkill != 493
          && GetBaseMasterLevelSkill != 494
          && GetBaseMasterLevelSkill != 495
          && GetBaseMasterLevelSkill != 497
          && GetBaseMasterLevelSkill != 498
          && GetBaseMasterLevelSkill != 499
          && GetBaseMasterLevelSkill != 500
          && GetBaseMasterLevelSkill != 501
          && GetBaseMasterLevelSkill != 502
          && GetBaseMasterLevelSkill != 509
          && GetBaseMasterLevelSkill != 510
          && GetBaseMasterLevelSkill != 514
          && GetBaseMasterLevelSkill != 515
          && GetBaseMasterLevelSkill != 516
          && GetBaseMasterLevelSkill != 519
          && GetBaseMasterLevelSkill != 520
          && GetBaseMasterLevelSkill != 521
          && GetBaseMasterLevelSkill != 523
          && GetBaseMasterLevelSkill != 539
		  && GetBaseMasterLevelSkill != 551
          && GetBaseMasterLevelSkill != 552
          && GetBaseMasterLevelSkill != 554
          && GetBaseMasterLevelSkill != 555
          && GetBaseMasterLevelSkill != 558
		  && GetBaseMasterLevelSkill != 559
		  && GetBaseMasterLevelSkill != 560
		  && GetBaseMasterLevelSkill != 558
			)
		{
			return false;
		}
		else
		{
			return true;
		}
		
	}
	else if(Skill != AT_SKILL_STORM
		&& Skill != AT_SKILL_EVIL
		&& Skill != AT_SKILL_FLAME
		&& Skill != AT_SKILL_HELL
		&& Skill != AT_SKILL_BLAST
		&& Skill != AT_SKILL_INFERNO
		&& Skill != AT_SKILL_CROSSBOW
		&& Skill != AT_SKILL_DEVILFIRE
		&& Skill != AT_SKILL_FLASH
		&& Skill != AT_SKILL_WHEEL
		&& Skill != AT_SKILL_SWORD6
		&& Skill != AT_SKILL_KNIGHTSPEAR
		&& Skill != AT_SKILL_KNIGHTADDLIFE
		&& Skill != AT_SKILL_STRIKE
		&& Skill != AT_SKILL_KNIGHTDINORANT
		&& Skill != AT_SKILL_ELFHARDEN
		&& Skill != AT_SKILL_PENETRATION
		&& Skill != AT_SKILL_DEFENSEDOWN
		&& Skill != AT_SKILL_MAGICDEFENSE
		&& Skill != AT_SKILL_BLOWOFFURY
		&& Skill != AT_SKILL_EXPPOISON
		&& Skill != AT_SKILL_EXPICE
		&& Skill != AT_SKILL_EXPHELL
		&& Skill != AT_SKILL_ELECTRICSPARK
		&& Skill != AT_SKILL_DARKHORSE_ATTACK
		&& Skill != AT_SKILL_BRAND_OF_SKILL
		&& Skill != AT_SKILL_STUN
		&& Skill != AT_SKILL_REMOVAL_STUN
		&& Skill != AT_SKILL_ADD_MANA
		&& Skill != AT_SKILL_INVISIBLE 
		&& Skill != AT_SKILL_REMOVAL_INVISIBLE
		&& Skill != AT_SKILL_REMOVAL_MAGIC
		&& Skill != AT_SKILL_FENRIR_ATTACK
		&& Skill != AT_SKILL_INFINITY_ARROW
		&& Skill != AT_SKILL_FIRESCREAM
		&& Skill != 214
		&& Skill != 215
		&& Skill != 216
		&& Skill != 217
		&& Skill != 219
		&& Skill != 220
		&& Skill != 223
		&& Skill != 224
		&& Skill != 221
		&& Skill != 222
		//Season4 add-on
		&& Skill != 225
		&& Skill != 230
		&& Skill != 218
		&& Skill != 232
		&& Skill != 233
		&& Skill != 234
		&& Skill != 235
		&& Skill != 236
		&& Skill != 237
		&& Skill != 238
		&& Skill != 239
		&& Skill != 260
		&& Skill != 261
		&& Skill != 262
		&& Skill != 263
		&& Skill != 264
		&& Skill != 265
		&& Skill != 266
		&& Skill != 267
		&& Skill != 268
		&& Skill != 270
		)
	{
		return false;
	}
	return true;
}

int CObjUseSkill::GetUseMana(int aIndex, CMagicInf * lpMagic)
{
	LPOBJ lpObj =&gObj[aIndex];
	float mana = lpObj->Mana;

	if ( lpObj->Type != OBJ_USER )
	{
		return 0;
	}

	if ( lpMagic == NULL )
	{
		return 0;
	}

	float loc4 = 0;

	loc4 = (float)(MagicDamageC.SkillGetMana(lpMagic->m_Skill) + this->GetAddUseMana(lpObj,lpMagic));

	loc4 -= lpObj->m_MPSkillOpt.MpsDecreaseMana * loc4 / 100.0f;

	if(loc4 < 1.0f)
	{
		loc4 = 1.0f;
	}

	mana -= loc4;

	if(mana < 0.0f)
	{
		return -1;
	}
	return (int)mana;
}

int CObjUseSkill::GetAddUseMana(LPOBJ lpObj,CMagicInf * lpMagic) //
{
	int iRetValue = 0;

	if(lpObj->Class == CLASS_ELF && lpObj->Type == OBJ_USER && lpObj->ChangeUP == 1)
	{
		if(gObjSearchActiveEffect(lpObj, AT_INFINITY_ARROW) == 1 || gObjSearchActiveEffect(lpObj,BUFF_INFINITY_ARROW2)==TRUE)
		{
			if(lpMagic->m_Skill == AT_SKILL_CROSSBOW
				|| lpMagic->m_Skill == AT_SKILL_BOW
				|| lpMagic->m_Skill == AT_SKILL_ELFHARDEN
				|| lpMagic->m_Skill == AT_SKILL_PENETRATION
				|| lpMagic->m_Skill == AT_SKILL_5CROSSBOW
				|| g_MasterSkillSystem.GetBaseMasterLevelSkill(lpMagic->m_Skill) == 490)
			{
				int iArrowLevel = 0;

				CItem * Right = &lpObj->pInventory[0];
				CItem * Left = &lpObj->pInventory[1];

				if(Right->m_Type >= ITEMGET(4,8) && Right->m_Type <= ITEMGET(4,14)
					|| Right->m_Type == ITEMGET(4,16)
					|| Right->m_Type == ITEMGET(4,18)
					|| Right->m_Type == ITEMGET(4,19))
				{
					if(Left->m_Type == ITEMGET(4,7))
					{
						iArrowLevel = Left->m_Level;
					}
				}
				else if(Left->m_Type >= ITEMGET(4,0) && Left->m_Type <= ITEMGET(4,6)
					|| Left->m_Type == ITEMGET(4,17)
					|| Left->m_Type == ITEMGET(4,20)
					|| Left->m_Type == ITEMGET(4,21)
					|| Left->m_Type == ITEMGET(4,22)
					|| Left->m_Type == ITEMGET(4,23)) //Season4 add-on
				{
					if(Right->m_Type == ITEMGET(4,15))
					{
						iArrowLevel = Right->m_Level;
					}
				}

				if(iArrowLevel == 0)
				{
					iRetValue = g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus0();
				}
				else if(iArrowLevel == 1)
				{
					iRetValue = g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus1();
				}
				else if(iArrowLevel == 2)
				{
					iRetValue = g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus2();
				}
				else if(iArrowLevel == 3) //season 4.5 add-on
				{
					iRetValue = g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus3();
				}
			}
		}
	}
	return iRetValue;
}

int  CObjUseSkill::GetUseBP(int aIndex, CMagicInf * lpMagic) //
{
	LPOBJ lpObj = &gObj[aIndex]; //2

	int bp = lpObj->BP; //3

	if(lpObj->Type != OBJ_USER)
	{
		return 0;
	}

	if(lpMagic == 0)
	{
		return 0;
	}

	int usingbp = MagicDamageC.SkillGetBP(lpMagic->m_Skill); //4

	usingbp -= usingbp * lpObj->SetOpDecreaseAG / 100;

	if(lpObj->m_btSocketOpDecreaseAG > 0)
	{
		usingbp -= usingbp * lpObj->m_btSocketOpDecreaseAG / 100;
	}

	bp -= usingbp;

	if(bp < 0)
	{
		return -1;
	}

	return bp;
}

int bFixFenrirPetTwister = 0;

void CObjUseSkill::UseSkill(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex) //004BECB0
{
	LPOBJ lpObj = &gObj[aIndex];

	int bCombo = 0;

	if(gComboAttack.CheckCombo(aIndex,lpMagic->m_Skill))
	{
		bCombo = 1;
	}

#if(DEV_COMBO_CUSTOM==TRUE)
	if(g_ZtLicense.user.ComboCustom)
	{
		lpObj->NewCombo = bCombo;
	}
#endif

	if(lpObj->SkillHellFire2State && lpMagic->m_Skill != AT_SKILL_EXPHELL)
	{
		CMagicInf * lpMagic = gObjGetMagicSearch(lpObj,AT_SKILL_EXPHELL);

		if(lpMagic != 0)
		{
			gObjUseSkill.RunningSkill(lpObj->m_Index,0,lpMagic,0);
		}

		return;
	}

	int usemana = this->GetUseMana(aIndex,lpMagic);

	if(lpMagic->m_Skill == AT_SKILL_DARKHORSE_ATTACK) //season4 add-on
	{
		usemana = (int)gObj[aIndex].Mana;
	}

	PMSG_DURATION_MAGIC_SEND pMsg;

	if(usemana >= 0)
	{
		if(!gObj[aIndex].SkillDelay.Check(lpMagic->m_Skill))
		{
			LogAddTD("[%] 스킬 딜레이시간 오버",gObj[aIndex].AccountID);
			return;
		}

		int usebp = gObjMagicBPUse(&gObj[aIndex],lpMagic);

		if(usebp >= 0)
		{
			lpObj->UseMagicNumber = lpMagic->m_Skill;
			lpObj->UseMagicTime = GetTickCount();
			lpObj->UseMagicCount = 0;

			lpObj->Mana = (float)usemana;
			lpObj->BP = usebp;

			GCManaSend(lpObj->m_Index,lpObj->Mana,0xFF,0,lpObj->BP);

			PHeadSetBE((LPBYTE)&pMsg,0x1E,sizeof(pMsg));

			pMsg.MagicNumberH = SET_NUMBERH(lpMagic->m_Skill);
			pMsg.MagicNumberL = SET_NUMBERL(lpMagic->m_Skill);

			pMsg.X = x;
			pMsg.Y = y;
			pMsg.Dir = dir;
			pMsg.NumberH = SET_NUMBERH(aIndex);
			pMsg.NumberL = SET_NUMBERL(aIndex);

			if(lpObj->Type == OBJ_USER)
			{
				DataSend(lpObj->m_Index,(LPBYTE)&pMsg,pMsg.h.size);
			}

			if(CC_MAP_RANGE(lpObj->MapNumber))
			{
				if(g_MasterSkillSystem.CheckRequireStatus(lpMagic->m_Skill) != FALSE) //Season3 add-on
				{
					int GetBaseMasterLevelSkill = g_MasterSkillSystem.GetBaseMasterLevelSkill(lpMagic->m_Skill);
					switch ( GetBaseMasterLevelSkill )
					{
						case 356:	//1.01.00
						case 360:
						case 363:
						case 403:
						case 404:
						case 406:
						case 413:
						case 417:
						case 420:
							break;
						default:
							MsgSendV2(lpObj,(LPBYTE)&pMsg,pMsg.h.size);
					}
				}
				else
				{
					switch ( lpMagic->m_Skill )
					{
						case 16:
						case 26:
						case 27:
						case 28:
						case 48:
							break;
						default:
							MsgSendV2(lpObj,(LPBYTE)&pMsg,pMsg.h.size);
					}
				}
			}
			else
			{
				MsgSendV2(lpObj,(LPBYTE)&pMsg,pMsg.h.size);
			}
		}
		
		if(g_MasterSkillSystem.CheckRequireStatus(lpMagic->m_Skill) != FALSE) //Season3 add-on
		{
			g_MasterSkillSystem.RunningSkill(lpObj, aTargetIndex, lpMagic, bCombo, x, y, dir, TargetPos);
			return;
		}

		if(lpMagic->m_Skill == AT_SKILL_SWORD6)
		{
			this->SkillPowerSlash(aIndex,lpMagic,x,y,dir,TargetPos,aTargetIndex);
		}

		if(lpMagic->m_Skill == AT_SKILL_EXPPOISON)
		{
//			this->SkillDeathPoison(aIndex,lpMagic,x,y,dir,TargetPos,aTargetIndex);
			if( lpObj->Class == 561 )	//Medusa, 1.01.00 update
			{
				this->SkillDeathPoisonForMeDusa(aIndex, lpMagic, x, y, aTargetIndex);
			}
			else
			{
				this->SkillDeathPoison(aIndex,lpMagic,x,y,dir,TargetPos,aTargetIndex);
			}
		}
		else if(lpMagic->m_Skill == AT_SKILL_EXPICE)
		{
			this->SkillSuddenIce(aIndex,lpMagic,x,y,dir,TargetPos,aTargetIndex);
		}
		else if(lpMagic->m_Skill == AT_SKILL_BLOWOFFURY)
		{
			this->SkillBlowOfFury(aIndex,lpMagic,x,y,dir,TargetPos,aTargetIndex,bCombo);
		}
		else if(lpMagic->m_Skill == AT_SKILL_WHEEL)
		{
			this->SkillWheel(aIndex,lpMagic,aTargetIndex,bCombo);
		}
		else if(lpMagic->m_Skill == AT_SKILL_ELECTRICSPARK)
		{
			this->SkillElectricSpark(aIndex,lpMagic,x,y,dir,TargetPos,aTargetIndex);
		}
		else if(lpMagic->m_Skill == AT_SKILL_DARKHORSE_ATTACK)
		{
			this->SkillDarkHorseAttack(lpObj->m_Index,aTargetIndex,lpMagic);
		}
		else if(lpMagic->m_Skill == AT_SKILL_STUN)
		{
			this->SkillStun(aIndex,aTargetIndex,lpMagic,x,y,dir,TargetPos);
		}
		else if(lpMagic->m_Skill == AT_SKILL_FENRIR_ATTACK)
		{
			this->SkillFenrirAttack(aIndex,aTargetIndex,lpMagic);
		}
		//Summoner Next
		else if(lpMagic->m_Skill == 216)
		{
			this->SkillEletrictSurge(aIndex,aTargetIndex,lpMagic);
		}
		else if(lpMagic->m_Skill == 214)
		{
			this->SkillDrainLife(aIndex,aTargetIndex,lpMagic);
		}
		else if(lpMagic->m_Skill == 215)
		{
			this->SkillChainLightning(aIndex,aTargetIndex,lpMagic);
		}
		else if(lpMagic->m_Skill == 223 || lpMagic->m_Skill == 224)
		{
			this->SkillSummonerBook(aIndex,lpMagic,x,y,aTargetIndex);
		}
		else if(lpMagic->m_Skill == 221)
		{
			this->SkillWeakness(aIndex,lpMagic,x,y,aTargetIndex);
		}
		else if(lpMagic->m_Skill == 222)
		{
			this->SkillInnovation(aIndex,lpMagic,x,y,aTargetIndex);
		}
		else if(lpMagic->m_Skill == 225) //season 4 add-on
		{
			this->SkillPollutionStart(aIndex,lpMagic,x,y,aTargetIndex,59);
		}
		else if(lpMagic->m_Skill == 230) //season 4 add-on
		{
			this->SkillLightningShock(aIndex,aTargetIndex,lpMagic);
		}
		else if(lpMagic->m_Skill == 232) //season 4 add-on
		{
			this->SkillStrikeOfDestructionStart(aIndex,lpMagic,x,y,aTargetIndex);
		}
		else if(lpMagic->m_Skill == 236) //season 4 add-on
		{
			this->SkillFlameStrike(aIndex,lpMagic,TargetPos,aTargetIndex);
		}
		else if(lpMagic->m_Skill == 237) //season 4 add-on
		{
			this->SkillGiganticStormStart(aIndex,lpMagic,x,y,aTargetIndex);
		}
		else if(lpMagic->m_Skill == 235) //season 4 add-on
		{
			this->SkillMultiShot(aIndex,lpMagic,TargetPos,aTargetIndex);
		}
		else if(lpMagic->m_Skill == 238) //season 4 add-on
		{
			this->SkillChaoticDiseier(aIndex,lpMagic,TargetPos,aTargetIndex);
		}
		else if(lpMagic->m_Skill == 9)
		{
			if( gObj[aIndex].Class == 561 )	//Medusa, 1.01.00
			{
				this->SkillEvilMonster(aIndex, aTargetIndex, lpMagic);
			}
		}
		else if(lpMagic->m_Skill == 264)
		{
			if( !OBJMAX_RANGE(aTargetIndex) )
			{
				LogAddTD("[InvalidTargetIndex][CObjUseSkill.UseSkill][AT_SKILL_DRAGON_ROAR] Index :%d , AccountID : %s ",
					aIndex, gObj[aIndex].AccountID);
				return;
			}
			// ----
			this->SkillAreaMonsterAttack(aIndex, lpMagic, gObj[aTargetIndex].X, gObj[aTargetIndex].Y, aTargetIndex, 3, 1, 0);
		}
			// --
		else if(lpMagic->m_Skill == 270)	//-> AT_SKILL_PHOENIXSHOT
		{
			if( !OBJMAX_RANGE(aTargetIndex) )
			{
				LogAddTD("[InvalidTargetIndex][CObjUseSkill.UseSkill][AT_SKILL_PHOENIXSHOT] Index :%d , AccountID : %s ",
					aIndex, gObj[aIndex].AccountID);
				return;
			}
			// ----
			this->SkillAreaMonsterAttack(aIndex, lpMagic, gObj[aTargetIndex].X, gObj[aTargetIndex].Y, aTargetIndex, 2, 1, 0);
		}
	}
}

//Identical
void CObjUseSkill::UseSkill(int aIndex, int aTargetIndex, CMagicInf * lpMagic) //
{
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	int bCombo = 0;

	if(gComboAttack.CheckCombo(aIndex,lpMagic->m_Skill))
	{
		bCombo = 1;
	}

#if(DEV_COMBO_CUSTOM==TRUE)
	if(g_ZtLicense.user.ComboCustom)
	{
		lpObj->NewCombo = bCombo;
	}
#endif

	if(lpObj->SkillHellFire2State && lpMagic->m_Skill != AT_SKILL_EXPHELL)
	{
		CMagicInf * lpMagic = gObjGetMagicSearch(lpObj,AT_SKILL_EXPHELL);

		if(lpMagic != 0)
		{
			gObjUseSkill.RunningSkill(lpObj->m_Index,0,lpMagic,0);
		}

		return;
	}

	if(lpMagic->m_Skill == AT_SKILL_EXPHELL && aTargetIndex != 58)
	{
		this->RunningSkill(aIndex,aTargetIndex,lpMagic,bCombo);
		lpObj->UseMagicNumber = lpMagic->m_Skill;
		lpObj->UseMagicTime = GetTickCount();
		lpObj->UseMagicCount = 0;
		return;
	}

	int usemana = this->GetUseMana(aIndex,lpMagic);

#ifdef DEBUG_CODE
	LogAddC(4,"usemana: %d ",usemana);
#endif

	if(usemana >= 0)
	{
		if(!gObj[aIndex].SkillDelay.Check(lpMagic->m_Skill))
		{
			LogAddTD("[%] 스킬 딜레이시간 오버",gObj[aIndex].AccountID); //HermeX Fix
			return;
		}

		int usebp = this->GetUseBP(aIndex,lpMagic);

		if(usebp >= 0)
		{
			if(this->RunningSkill(aIndex,aTargetIndex,lpMagic,bCombo)==1)
			{
				lpObj->UseMagicNumber = lpMagic->m_Skill;
				lpObj->UseMagicTime = GetTickCount();
				lpObj->UseMagicCount = 0;

				lpObj->Mana = (float)usemana;
				lpObj->BP = usebp;

#ifdef DEBUG_CODE
				LogAddC(2,"lpObj->Mana: %d",lpObj->Mana);
#endif

				GCManaSend(aIndex,lpObj->Mana,0xFF,0,lpObj->BP);
			}
		}
	}
}

BOOL CObjUseSkill::RunningSkill(int aIndex, int aTargetIndex, CMagicInf * lpMagic, BOOL bCombo) //
{
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];
	DWORD MagicNumber = lpMagic->m_Skill;

	lpObj->m_SkillNumber = MagicNumber;

	if( (gObjSearchActiveEffect(lpObj, AT_INVISIBILITY) == TRUE) && ((lpObj->Authority&32) != 32) ) //season3 add-on
	{
		this->RemoveCloakingEffect(lpObj->m_Index);
	}

	if(g_MasterSkillSystem.CheckRequireStatus(lpMagic->m_Skill) != FALSE) //Season3 add-on
	{
		return g_MasterSkillSystem.RunningSkill(lpObj, aTargetIndex, lpMagic, bCombo, 0, 0, 0, 0);
	}

	switch(MagicNumber)
	{
	case AT_SKILL_BLOCKING:
		if(lpObj->pInventory[1].IsItem() == 1)
		{
			if(lpObj->pInventory[1].m_Type >= ITEMGET(6,4) && lpObj->pInventory[1].m_Type < ITEMGET(7,0))
			{
				if(lpObj->pInventory[1].m_Option1 != 0)
				{
					lpObj->m_SkillTime = GetTickCount() + 4000;
					GCActionSend(lpObj,18,lpObj->m_Index,aTargetIndex);
				}
			}
		}
		break;
	case AT_SKILL_POISON:
	case AT_SKILL_METEO:
	case AT_SKILL_THUNDER:
	case AT_SKILL_FIREBALL:
	case AT_SKILL_FLAME:
	case AT_SKILL_SLOW:
	case AT_SKILL_ENERGYBALL:
	case AT_SKILL_SWORD1:
	case AT_SKILL_SWORD2:
	case AT_SKILL_SWORD3:
	case AT_SKILL_SWORD4:
	case AT_SKILL_SWORD5:
	case AT_SKILL_CROSSBOW:
	case AT_SKILL_BOW:
	case AT_SKILL_WHEEL:
	case AT_SKILL_BLOWOFFURY:
	case AT_SKILL_KNIGHTSPEAR:
	case AT_SKILL_PENETRATION:
	case AT_SKILL_SWORD6:
		{
			gObjAttack(lpObj,lpTargetObj,lpMagic,1,0,0,0,0,0);
			break;
		}
	case AT_SKILL_HEALING:	this->SkillHealing(aIndex,aTargetIndex,lpMagic->m_Level);break;
	case AT_SKILL_MAGICDEFENSE:	this->WizardMagicDefense(aIndex,aTargetIndex,lpMagic->m_Level);break;
	case AT_SKILL_KNIGHTADDLIFE:	this->KnightSkillAddLife(aIndex,lpMagic->m_Level);break;
	case AT_SKILL_DEFENSE:	this->SkillDefense(aIndex,aTargetIndex,lpMagic->m_Level);break;
	case AT_SKILL_ATTACK:	this->SkillAttack(aIndex,aTargetIndex,lpMagic->m_Level);break;

	case AT_SKILL_CALLMON1:	return this->SkillMonsterCall(lpObj->m_Index,26,lpObj->X-1,lpObj->Y+1);
	case AT_SKILL_CALLMON2:	return this->SkillMonsterCall(lpObj->m_Index,32,lpObj->X-1,lpObj->Y+1);
	case AT_SKILL_CALLMON3:	return this->SkillMonsterCall(lpObj->m_Index,21,lpObj->X-1,lpObj->Y+1);
	case AT_SKILL_CALLMON4:	return this->SkillMonsterCall(lpObj->m_Index,20,lpObj->X-1,lpObj->Y+1);
	case AT_SKILL_CALLMON5:	return this->SkillMonsterCall(lpObj->m_Index,10,lpObj->X-1,lpObj->Y+1);
	case AT_SKILL_CALLMON6:	return this->SkillMonsterCall(lpObj->m_Index,150,lpObj->X-1,lpObj->Y+1);
	case AT_SKILL_CALLMON7:	return this->SkillMonsterCall(lpObj->m_Index,151,lpObj->X-1,lpObj->Y+1);

	case AT_SKILL_EXPHELL:	return this->SkillHellFire2(lpObj->m_Index,aTargetIndex,lpMagic);
	case AT_SKILL_STRIKE:	return this->SkillKnightBlow(lpObj->m_Index,aTargetIndex,lpMagic,bCombo);

	case AT_SKILL_SPEAR:	return this->SkillSpear(lpObj->m_Index,aTargetIndex,lpMagic);
	case AT_SKILL_FIREBURST:	return this->SkillFireBurst(lpObj->m_Index,aTargetIndex,lpMagic);
	case AT_SKILL_DARKHORSE_ATTACK:	return this->SkillDarkHorseAttack(lpObj->m_Index,aTargetIndex,lpMagic);
	case AT_SKILL_RECALL_PARTY:	this->SkillRecallParty(aIndex,lpMagic->m_Level);break;
	case AT_SKILL_ADD_CRITICALDAMAGE:	this->SkillAddCriticalDamage(aIndex,lpMagic->m_Level);break;

	case AT_SKILL_DEFENSEDOWN:	this->MaGumSkillDefenseDown(lpObj->m_Index,aTargetIndex,1);break;

	case AT_SKILL_SUMMON:	this->SkillSummon(lpObj->m_Index,aTargetIndex,lpMagic);break;
	case AT_SKILL_IMMUNE_TO_MAGIC:	this->SkillImmuneToMagic(lpObj->m_Index,lpMagic);break;
	case AT_SKILL_IMMUNE_TO_HARM:	this->SkillImmuneToHarm(lpObj->m_Index,lpMagic);break;

	case AT_SKILL_RUSH:	this->SkillKnightRush(lpObj->m_Index,aTargetIndex,lpMagic);break;
	case AT_SKILL_JAVALIN:	this->SkillWizardJavalin(lpObj->m_Index,aTargetIndex,lpMagic);break;
	case AT_SKILL_DEEPIMPACT:	this->SkillElfRush(lpObj->m_Index,aTargetIndex,lpMagic);break;
	case AT_SKILL_ONE_FLASH:	this->SkillMagumOneFlash(lpObj->m_Index,aTargetIndex,lpMagic);break;
	case AT_SKILL_DEATH_CANNON:	this->SkillMagumDeathCannon(lpObj->m_Index,aTargetIndex,lpMagic);break;
	case AT_SKILL_SPACE_SPLIT:	this->SkillDarklordSpaceSplit(lpObj->m_Index,aTargetIndex,lpMagic);break;

	case AT_SKILL_BRAND_OF_SKILL:	this->SkillBrandOfSkill(aIndex,aTargetIndex,lpMagic);break;

	case AT_SKILL_REMOVAL_STUN:	this->SkillRemoveStun(aIndex,aTargetIndex,lpMagic);break;
	case AT_SKILL_ADD_MANA:	this->SkillAddMana(aIndex,aTargetIndex,lpMagic);break;
	case AT_SKILL_INVISIBLE:	this->SkillCloaking(aIndex,aTargetIndex,lpMagic);break;
	case AT_SKILL_REMOVAL_INVISIBLE:	this->SkillRemoveCloaking(aIndex,aTargetIndex,lpMagic);break;
	case AT_SKILL_REMOVAL_MAGIC:	this->SkillRemoveMagic(aIndex,aTargetIndex,lpMagic);break;

	case AT_SKILL_INFINITY_ARROW:	this->SkillInfinityArrow(aIndex,aTargetIndex,lpMagic);break;

	case 217: this->SkillDamageReflection(aIndex,aTargetIndex,lpMagic);break; //Summoner Damage Reflection
	case 219: this->SkillSleep(aIndex,aTargetIndex,lpMagic);break;
	case 220: this->SkillBlind(aIndex,aTargetIndex,lpMagic);break;

		//Season4 add-on
	case 218: this->SkillBerserker(lpObj->m_Index,lpMagic);break;
	case 234: this->SkillSDRecovery(aIndex,aTargetIndex,lpMagic);break;
	case 233: this->SkillExpansionWizardry(aIndex,aTargetIndex,lpMagic);break;

	case 266:
		{
			this->SkillMonkBuff(aIndex, lpMagic);
		}
		break;
		// --
	case 267:
	case 268:
		{
			this->SkillMonkBuffApplyParty(aIndex, lpMagic);
		}
		break;
		// --
	case 260:
	case 261:
	case 262:
	case 263:
		{
			this->SkillMonkBarrageJustOneTarget(aIndex, lpMagic, aTargetIndex);
		}
		break;
		// --
	case 265:
		{
			gObjAttack(lpObj, lpTargetObj, lpMagic, 1, 0, 0, 0, 0, 0);
		}
		break;
		// --
	case 269:
		{
			this->SkillCharge(aIndex, lpMagic, aTargetIndex);
		}
		break;
		// ----
	default:	gObjAttack(lpObj,lpTargetObj,lpMagic,1,0,0,0,0,0);break;
	}

	return true;
}

void CObjUseSkill::MaGumSkillDefenseDown(int aIndex, int aTargetIndex, int skill_level) //
{
	int skillSuccess = 1;
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(lpObj->Type == OBJ_USER && lpObj->Class != CLASS_MAGUMSA)
	{
		return;
	}

	LogAdd("마검사 몬스터방어력감소 : %d",10); // HermeX Fix

	if(retCalcSkillResistance(lpTargetObj,1))
	{
		gObjApplyBuffEffectDuration(lpTargetObj, AT_REDUCE_DEFENSE, 23, 10, 0, 0, 10); //Season3 add-on
		GCMagicAttackNumberSend(lpObj,AT_SKILL_DEFENSEDOWN,lpTargetObj->m_Index,skillSuccess);
	}
}

void CObjUseSkill::KnightSkillAddLife(int aIndex, int skill_level) //
{


	int skillSuccess = true;
	LPOBJ lpObj = &gObj[aIndex];

	if (szAuthKey[14] != AUTHKEY14 )
	{
		DestroyGIocp();
	}

	if(lpObj->Type != OBJ_USER && lpObj->m_RecallMon == -1)
	{
		return;
	}

	if(lpObj->Class != CLASS_KNIGHT && lpObj->Class != CLASS_MAGUMSA)
	{
		return;
	}

	int number;
	int partynum = 0;
	int totallevel = 0;
	int partycount;
	int dis;

	int ApplyPartyIndex[MAX_USER_IN_PARTY];

	int viewplayer = 0;
	int viewpercent = 0;

	LPOBJ lpPartyObj;

	memset(ApplyPartyIndex,-1,sizeof(ApplyPartyIndex));

	partynum = lpObj->PartyNumber;

	if(partynum != -1)
	{
		partycount = gParty.m_PartyS[partynum].Count;

		for(int n = 0; n < MAX_USER_IN_PARTY; n++)
		{
			number = gParty.m_PartyS[partynum].Number[n];

			if(number >= 0)
			{
				lpPartyObj = &gObj[number];

				if(lpObj->MapNumber == lpPartyObj->MapNumber)
				{
					dis = gObjCalDistance(lpObj,&gObj[number]);

					if(dis < 10)
					{
						ApplyPartyIndex[n] = lpPartyObj->m_Index;
						viewplayer++;
					}
				}
			}
		}
	}

	if(viewplayer > 1)
	{
		if(viewplayer == 2)
		{
			viewpercent = 1;
		}
		else if(viewplayer == 3)
		{
			viewpercent = 2;
		}
		else if(viewplayer == 4)
		{
			viewpercent = 3;
		}
		else
		{
			viewpercent = 4;
		}
	}
	int iaddlife;
	int iaddLifepower	= g_SkillAdditionInfo.SwellLifeEffectStart + (lpObj->Vitality + lpObj->AddVitality) / g_SkillAdditionInfo.SwellLifeEffectDiv1 + (lpObj->Energy + lpObj->AddEnergy)/ g_SkillAdditionInfo.SwellLifeEffectDiv2 + viewpercent;

	if( g_SkillAdditionInfo.SwellLifeEffectMax > 0 && iaddLifepower > g_SkillAdditionInfo.SwellLifeEffectMax )
	{
		iaddLifepower = g_SkillAdditionInfo.SwellLifeEffectMax;
	}

	int iLifeTime		= g_SkillAdditionInfo.SwellLifeTimeStart + (lpObj->Energy + lpObj->AddEnergy) / g_SkillAdditionInfo.SwellLifeTimeDiv;

	if( g_SkillAdditionInfo.SwellLifeTimeMax > 0 && iLifeTime > g_SkillAdditionInfo.SwellLifeTimeMax )
	{
		iLifeTime = g_SkillAdditionInfo.SwellLifeTimeMax;
	}
	// ----
	if(partynum == -1)
	{
#ifdef PRIDEMU_CONFIG
		if(g_ZtLicense.CheckUser(eZtUB::PrideMuLocal) || g_ZtLicense.CheckUser(eZtUB::PrideMu) || g_ZtLicense.CheckUser(eZtUB::Local3))
		{
			iaddlife = int(lpObj->MaxLife) * iaddLifepower / 100;
			iaddlife *= ZtConfig.PrideMu.Fortitude / 100;
		}
		else
		{
			iaddlife = int(lpObj->MaxLife) * iaddLifepower / 100;
		}
#else
		iaddlife = int(lpObj->MaxLife) * iaddLifepower / 100;
#endif
		gObjApplyBuffEffectDuration(lpObj, AT_SWELL_LIFE, 4, iaddlife, 0, 0, iLifeTime);
		GCMagicAttackNumberSend(lpObj,AT_SKILL_KNIGHTADDLIFE,lpObj->m_Index,skillSuccess);
	}
	else
	{
		for(int n = 0; n < MAX_USER_IN_PARTY; n++)
		{
			if(ApplyPartyIndex[n]!= -1)
			{
				lpPartyObj = &gObj[ApplyPartyIndex[n]];
				iaddlife = int(lpPartyObj->MaxLife) * iaddLifepower / 100;

				gObjApplyBuffEffectDuration(lpPartyObj, AT_SWELL_LIFE, 4, iaddlife, 0, 0, iLifeTime); //season3 add-on
				GCMagicAttackNumberSend(lpObj,AT_SKILL_KNIGHTADDLIFE,lpPartyObj->m_Index,skillSuccess);
			}
		}
	}
}

//Identical
void CObjUseSkill::WizardMagicDefense(int aIndex, int aTargetIndex, int skill_level) //004C0560
{
	//int skillSuccess = true;

	//LPOBJ lpObj = &gObj[aIndex];
	//LPOBJ lpTargetObj = &gObj[aTargetIndex];

	//if(lpObj->Type != OBJ_USER && lpObj->m_RecallMon== -1)
	//{
	//	return;
	//}

	//if(lpObj->Class != CLASS_WIZARD && lpObj->Class != CLASS_MAGUMSA)
	//{
	//	return;
	//}

	//if(lpObj->PartyNumber != lpTargetObj->PartyNumber)
	//{
	//	return;
	//}

	//int WizardSkillDefense = 0;
	//int WizardSkillDefenseTime = 0;

	////int ExMSStartPower = GetPrivateProfileInt("DarkWizard","MSStartPower",10,"..\\Data\\ZtData\\Skills.ini");
	////int ExMSAgility = GetPrivateProfileInt("DarkWizard","MSAgility",50,"..\\Data\\ZtData\\Skills.ini");
	////int ExMSEnergy = GetPrivateProfileInt("DarkWizard","MSEnergy",200,"..\\Data\\ZtData\\Skills.ini");
	////int ExMSMaxPower = GetPrivateProfileInt("DarkWizard","MSMaxPower",50,"..\\Data\\ZtData\\Skills.ini");

	//WizardSkillDefense = ZtConfig.Skills.ExMSStartPower + (lpObj->Dexterity + lpObj->AddDexterity) / ZtConfig.Skills.ExMSAgility + (lpObj->Energy + lpObj->AddEnergy) / ZtConfig.Skills.ExMSEnergy;
	//WizardSkillDefenseTime = 60 + (lpObj->Energy + lpObj->AddEnergy) / 40;

	//if(WizardSkillDefense > ZtConfig.Skills.ExMSMaxPower)
	//	WizardSkillDefense = ZtConfig.Skills.ExMSMaxPower;

	//gObjApplyBuffEffectDuration(lpTargetObj, AT_WIZARD_DEFENSE, 21, WizardSkillDefense, 28, 20, WizardSkillDefenseTime); //season3 add-on
	//GCMagicAttackNumberSend(lpObj,AT_SKILL_MAGICDEFENSE,lpTargetObj->m_Index,skillSuccess);

	int skillSuccess	= true;
	// ----
	LPOBJ lpObj			= &gObj[aIndex];
	LPOBJ lpTargetObj	= &gObj[aTargetIndex];
	// ----
	if( lpObj->Type != OBJ_USER && lpObj->m_RecallMon == -1 )
	{
		return;
	}
	// ----
	if( lpObj->Class != CLASS_WIZARD && lpObj->Class != CLASS_MAGUMSA )
	{
		return;
	}
	// ----
	if( lpObj->PartyNumber != lpTargetObj->PartyNumber )
	{
		return;
	}
	// ----
	int WizardManaRate			= 20;
	int WizardSkillDefense		= g_SkillAdditionInfo.SoulBarrierDefenseStart + ((lpObj->Dexterity + lpObj->AddDexterity) / g_SkillAdditionInfo.SoulBarrierDefenseDiv1) + ((lpObj->Energy + lpObj->AddEnergy) / g_SkillAdditionInfo.SoulBarrierDefenseDiv2);
	// ----
	if( g_SkillAdditionInfo.SoulBarrierDefenseMax > 0 && WizardSkillDefense > g_SkillAdditionInfo.SoulBarrierDefenseMax )
	{
		WizardSkillDefense = g_SkillAdditionInfo.SoulBarrierDefenseMax;
	}
	// ----
	int WizardSkillDefenseTime	= g_SkillAdditionInfo.SoulBarrierTimeStart + (lpObj->Energy + lpObj->AddEnergy) / g_SkillAdditionInfo.SoulBarrierTimeDiv;
	// ----
	if( g_SkillAdditionInfo.SoulBarrierTimeMax > 0 && WizardSkillDefenseTime > g_SkillAdditionInfo.SoulBarrierTimeMax )
	{
		WizardSkillDefenseTime = g_SkillAdditionInfo.SoulBarrierTimeMax;
	}

	//LogAddC(2,"WizardSkillDefense: %d.",WizardSkillDefense);

	// ----
	gObjApplyBuffEffectDuration(lpTargetObj, AT_WIZARD_DEFENSE, 21, WizardSkillDefense, 28, WizardManaRate, WizardSkillDefenseTime);
	GCMagicAttackNumberSend(lpObj, AT_SKILL_MAGICDEFENSE, lpTargetObj->m_Index, skillSuccess);
}

void CObjUseSkill::SkillDefense(int aIndex, int aTargetIndex, int skill_level) //
{
	//int skillSuccess = true;
	//LPOBJ lpObj = &gObj[aIndex];
	//LPOBJ lpTargetObj = &gObj[aTargetIndex];

	//if(lpTargetObj->Type != OBJ_USER && lpTargetObj->m_RecallMon == -1)
	//{
	//	return;
	//}

	//if(lpObj->Class != CLASS_ELF)
	//{
	//	return;
	//}

	//if(CC_MAP_RANGE(lpObj->MapNumber) && lpObj->m_Index != lpTargetObj->m_Index)
	//{
	//	return;
	//}

	//if(skill_level < 0 || skill_level > 7)
	//{
	//	skill_level = 0;
	//}
	////int ExDefenceEnergy = GetPrivateProfileInt("Elf","DefenceEnergy",8,"..\\Data\\ZtData\\Skills.ini");
	//float skill_defense = float(skill_level + 1)*2 + (lpObj->Energy + lpObj->AddEnergy) / ZtConfig.Skills.ExDefenceEnergy;

	//if(lpTargetObj->Class == CLASS_KNIGHT)
	//{
	//	skill_defense += skill_defense/10.0f;
	//}

	//if(gObjCheckBuffEffectValue(lpTargetObj, AT_INCREASE_DEFENSE, (int)skill_defense, 0) == 1) //season3 add-on
	//{
	//	GCMagicAttackNumberSend(lpObj,AT_SKILL_DEFENSE,lpTargetObj->m_Index,0);
	//	return;
	//}

	//gObjApplyBuffEffectDuration(lpTargetObj, AT_INCREASE_DEFENSE, 3, (int)skill_defense, 0, 0, 60); //season3 add-on

	//for(int n = 0; n < MAX_VIEWPORT; n++)
	//{
	//	if(lpObj->VpPlayer2[n].type == OBJ_MONSTER && lpObj->VpPlayer2[n].state != 0)
	//	{
	//		LPOBJ lpMonster = &gObj[lpObj->VpPlayer2[n].number];
	//		if(lpMonster->m_iCurrentAI != 0)
	//		{
	//			lpMonster->m_Agro.IncAgro(lpObj->m_Index,int(skill_defense)/10);
	//		}
	//	}
	//}

	//GCMagicAttackNumberSend(lpObj,AT_SKILL_DEFENSE,lpTargetObj->m_Index,skillSuccess);
	
	int skillSuccess = true;
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(lpTargetObj->Type != OBJ_USER && lpTargetObj->m_RecallMon == -1)
	{
		return;
	}

	if(lpObj->Class != CLASS_ELF)
	{
		return;
	}

	if(CC_MAP_RANGE(lpObj->MapNumber) && lpObj->m_Index != lpTargetObj->m_Index)
	{
		return;
	}

	if(skill_level < 0 || skill_level > 7)
	{
		skill_level = 0;
	}

	int Duration	= g_SkillAdditionInfo.ElfDefenseTime;
	float skill_defense = float(skill_level + 1)*g_SkillAdditionInfo.ElfDefenseEffectFact + (lpObj->Energy + lpObj->AddEnergy) / g_SkillAdditionInfo.ElfDefenseEffectDiv;

	if( g_SkillAdditionInfo.ElfDefenseEffectMax > 0 && skill_defense > g_SkillAdditionInfo.ElfDefenseEffectMax )
	{
		skill_defense = g_SkillAdditionInfo.ElfDefenseEffectMax;
	}

	if(lpTargetObj->Class == CLASS_KNIGHT)
	{
		skill_defense += skill_defense/10.0f;
	}

	if(gObjCheckBuffEffectValue(lpTargetObj, AT_INCREASE_DEFENSE, skill_defense, 0) == 1)
	{
		GCMagicAttackNumberSend(lpObj,AT_SKILL_DEFENSE,lpTargetObj->m_Index,0);
		return;
	}

	gObjApplyBuffEffectDuration(lpTargetObj, AT_INCREASE_DEFENSE, 3, skill_defense, 0, 0, Duration);

	for(int n = 0; n < MAX_VIEWPORT; n++)
	{
		if(lpObj->VpPlayer2[n].type == OBJ_MONSTER && lpObj->VpPlayer2[n].state != 0)
		{
			LPOBJ lpMonster = &gObj[lpObj->VpPlayer2[n].number];
			if(lpMonster->m_iCurrentAI != 0)
			{
				lpMonster->m_Agro.IncAgro(lpObj->m_Index,int(skill_defense)/10);
			}
		}
	}

	GCMagicAttackNumberSend(lpObj,AT_SKILL_DEFENSE,lpTargetObj->m_Index,skillSuccess);
}

void CObjUseSkill::SkillAttack(int aIndex, int aTargetIndex, int skill_level) //
{
	//int skillSuccess = true;
	//LPOBJ lpObj = &gObj[aIndex];
	//LPOBJ lpTargetObj = &gObj[aTargetIndex];

	//if(lpTargetObj->Type != OBJ_USER && lpTargetObj->m_RecallMon == -1)
	//{
	//	return;
	//}

	//if(lpObj->Class != CLASS_ELF)
	//{
	//	return;
	//}

	//if(CC_MAP_RANGE(lpObj->MapNumber) && lpObj->m_Index != lpTargetObj->m_Index)
	//{
	//	return;
	//}

	//if(skill_level < 0 || skill_level > 7)
	//{
	//	skill_level = 0;
	//}
	////int ExAttackEnergy = GetPrivateProfileInt("Elf","AttackEnergy",7,"..\\Data\\ZtData\\Skills.ini");
	//float skill_attack = float((skill_level + 1) * 3) + (lpObj->Energy + lpObj->AddEnergy) / ZtConfig.Skills.ExAttackEnergy;

	//if(lpTargetObj->Class == CLASS_KNIGHT)
	//{
	//	skill_attack += skill_attack/10.0f;
	//}

	//if(gObjCheckBuffEffectValue(lpTargetObj, AT_INCREASE_ATTACK, (int)skill_attack, 0) == 1) //season3 add-on
	//{
	//	GCMagicAttackNumberSend(lpObj,AT_SKILL_ATTACK,lpTargetObj->m_Index,0);
	//	return;
	//}

	//gObjApplyBuffEffectDuration(lpTargetObj, AT_INCREASE_ATTACK, 2, (int)skill_attack, 0, 0, 60); //season3 add-on

	//for(int n = 0; n < MAX_VIEWPORT; n++)
	//{
	//	if(lpObj->VpPlayer2[n].type == OBJ_MONSTER && lpObj->VpPlayer2[n].state != 0)
	//	{
	//		LPOBJ lpMonster = &gObj[lpObj->VpPlayer2[n].number];
	//		if(lpMonster->m_iCurrentAI != 0)
	//		{
	//			lpMonster->m_Agro.IncAgro(lpObj->m_Index,int(skill_attack)/10);
	//		}
	//	}
	//}

	//GCMagicAttackNumberSend(lpObj,AT_SKILL_ATTACK,lpTargetObj->m_Index,skillSuccess);

	int skillSuccess = true;
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(lpTargetObj->Type != OBJ_USER && lpTargetObj->m_RecallMon == -1)
	{
		return;
	}

	if(lpObj->Class != CLASS_ELF)
	{
		return;
	}

	if(CC_MAP_RANGE(lpObj->MapNumber) && lpObj->m_Index != lpTargetObj->m_Index)
	{
		return;
	}

	if(skill_level < 0 || skill_level > 7)
	{
		skill_level = 0;
	}

	float skill_attack	= float((skill_level + 1) * g_SkillAdditionInfo.ElfAttackEffectFact) + (lpObj->Energy + lpObj->AddEnergy) / (float)g_SkillAdditionInfo.ElfAttackEffectDiv;
	int BuffTime		= g_SkillAdditionInfo.ElfAttackTime;

	if( g_SkillAdditionInfo.ElfAttackEffectMax > 0 && skill_attack > g_SkillAdditionInfo.ElfAttackEffectMax )
	{
		skill_attack = g_SkillAdditionInfo.ElfAttackEffectMax;
	}

	if(lpTargetObj->Class == CLASS_KNIGHT)
	{
		skill_attack += skill_attack/10.0f;
	}	
	// ----
	if(gObjCheckBuffEffectValue(lpTargetObj, AT_INCREASE_ATTACK, skill_attack, 0) == 1) //season3 add-on
	{
		GCMagicAttackNumberSend(lpObj,AT_SKILL_ATTACK,lpTargetObj->m_Index,0);
		return;
	}

	gObjApplyBuffEffectDuration(lpTargetObj, AT_INCREASE_ATTACK, 2, skill_attack, 0, 0, BuffTime); //season3 add-on

	for(int n = 0; n < MAX_VIEWPORT; n++)
	{
		if(lpObj->VpPlayer2[n].type == OBJ_MONSTER && lpObj->VpPlayer2[n].state != 0)
		{
			LPOBJ lpMonster = &gObj[lpObj->VpPlayer2[n].number];
			if(lpMonster->m_iCurrentAI != 0)
			{
				lpMonster->m_Agro.IncAgro(lpObj->m_Index,int(skill_attack)/10);
			}
		}
	}

	GCMagicAttackNumberSend(lpObj,AT_SKILL_ATTACK,lpTargetObj->m_Index,skillSuccess);
}

BOOL CObjUseSkill::SkillChangeUse(int aIndex) //
{
//	LPOBJ lpObj = &gObj[aIndex];
//
//	int skill_level = -1;
//
//	if(lpObj->Type != OBJ_USER)
//	{
//		return false;
//	}
//
//	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,10))
//	{
//		if(lpObj->pInventory[10].m_Durability < 1.0f)
//		{
//			skill_level = -1;
//		}
//		else
//		{
//			skill_level = lpObj->pInventory[10].m_Level;
//		}
//	}
//
//	if(lpObj->pInventory[11].IsItem()==1 && skill_level == -1 && lpObj->pInventory[11].m_Type == ITEMGET(13,10))
//	{
//		if(lpObj->pInventory[11].m_Durability < 1.0f)
//		{
//			skill_level = -1;
//		}
//		else
//		{
//			skill_level = lpObj->pInventory[11].m_Level;
//		}
//	}
//
//	if(skill_level > 7)
//	{
//		return false;
//	}
//
//	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,39))
//	{
//		if(lpObj->pInventory[10].m_Durability < 1.0f)
//		{
//			skill_level = -1;
//		}
//		else
//		{
//			skill_level = 372;
//		}
//	}
//
//	if(lpObj->pInventory[11].IsItem()==1 && skill_level == -1 && lpObj->pInventory[11].m_Type == ITEMGET(13,39))
//	{
//		if(lpObj->pInventory[11].m_Durability < 1.0f)
//		{
//			skill_level = -1;
//		}
//		else
//		{
//			skill_level = 372;
//		}
//	}
//
//	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,40)) //Second Edition
//	{
//		if(lpObj->pInventory[10].m_Durability < 1.0f)
//		{
//			skill_level = -1;
//		}
//		else
//		{
//			skill_level = 373;
//		}
//	}
//
//	if(lpObj->pInventory[11].IsItem()==1 && lpObj->pInventory[11].m_Type == ITEMGET(13,40)) //Second Edition
//	{
//		if(lpObj->pInventory[11].m_Durability < 1.0f)
//		{
//			skill_level = -1;
//		}
//		else
//		{
//			skill_level = 373;
//		}
//	}
//
//	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,41)) //Season 2.5 add-on
//	{
//		if(lpObj->pInventory[10].m_Durability < 1.0f)
//		{
//			skill_level = -1;
//		}
//		else
//		{
//			skill_level = 374;
//		}
//	}
//
//	if(lpObj->pInventory[11].IsItem()==1 && lpObj->pInventory[11].m_Type == ITEMGET(13,41)) //Season 2.5 add-on
//	{
//		if(lpObj->pInventory[11].m_Durability < 1.0f)
//		{
//			skill_level = -1;
//		}
//		else
//		{
//			skill_level = 374;
//		}
//	}
//
//	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,42)) //Season 2.5 add-on
//	{
//		if((lpObj->Authority&32) != 32)
//		{
//			return FALSE;
//		}
//
//		skill_level = 378;
//
//	}
//
//	if(lpObj->pInventory[11].IsItem()==1 && lpObj->pInventory[11].m_Type == ITEMGET(13,42)) //Season 2.5 add-on
//	{
//		if((lpObj->Authority&32) != 32)
//		{
//			return FALSE;
//		}
//
//		skill_level = 378;
//	}
//
//	if(IT_MAP_RANGE(lpObj->MapNumber) != FALSE) //Season2.5 add-on (illusion temple checks)
//	{
//		if(g_IllusionTempleEvent.GetState(lpObj->MapNumber) != 0)
//		{
//			int ebp10 = g_IllusionTempleEvent.GetUserJoinSide(lpObj->MapNumber, lpObj->m_Index);
//			if(ebp10 == 0)
//			{
//				skill_level = 404;
//			}
//			else if(ebp10 == 1)
//			{
//				skill_level = 405;
//			}
//		}
//	}
//
//	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,68)) //Season 4 add-on
//	{
//		if(lpObj->pInventory[10].m_Durability < 1.0f)
//		{
//			skill_level = -1;
//		}
//		else
//		{
//			skill_level = 477;
//		}
//	}
//
//	if(lpObj->pInventory[11].IsItem()==1 && lpObj->pInventory[11].m_Type == ITEMGET(13,68)) //Season 4 add-on
//	{
//		if(lpObj->pInventory[11].m_Durability < 1.0f)
//		{
//			skill_level = -1;
//		}
//		else
//		{
//			skill_level = 477;
//		}
//	}
////Panda Ring
//	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,76)) //Season 4 add-on
//	{
//		if(lpObj->pInventory[10].m_Durability < 1.0f)
//		{
//			skill_level = -1;
//		}
//		else
//		{
//			skill_level = 503;
//		}
//	}
//
//	if(lpObj->pInventory[11].IsItem()==1 && lpObj->pInventory[11].m_Type == ITEMGET(13,76)) //Season 4 add-on
//	{
//		if(lpObj->pInventory[11].m_Durability < 1.0f)
//		{
//			skill_level = -1;
//		}
//		else
//		{
//			skill_level = 503;
//		}
//	}
//	//Season 5 Skeleton Ring
//	if(lpObj->pInventory[10].IsItem() && lpObj->pInventory[10].m_Type == ITEMGET(13,122))
//	{
//		if(lpObj->pInventory[10].m_Durability < 1.0f)
//		{
//			skill_level = -1;
//		}
//		else
//		{
//			skill_level = 548;
//		}
//	}
//
//	//Season 5 Skeleton Ring
//	if(lpObj->pInventory[11].IsItem() && lpObj->pInventory[11].m_Type == ITEMGET(13,122))
//	{
//		if(lpObj->pInventory[11].m_Durability < 1.0f)
//		{
//			skill_level = -1;
//		}
//		else
//		{
//			skill_level = 548;
//		}
//	}
//
//	int change = -1;
//
//	switch(skill_level)
//	{
//	case 0: change = 2;	break;
//	case 1: change = 7; break;
//	case 2: change = 14;	break;
//	case 3: change = 8;	break;
//	case 4:	change = 9;	break;
//	case 5:	change = 41;	break;
//	case 372:	change = skill_level;	break;
//	case 373:	change = skill_level;	break; //Second Edition
//	case 374:	change = skill_level;	break; //season 2.5
//	case 378:	change = skill_level;	break; //season 2.5
//	case 404: //season 2.5
//	case 405:
//		change = skill_level;	break;
//	case 477:	change = skill_level;	break; //season 4
//	case 503:	change = skill_level;	break; //season 4.6 panda ring
//	case 548:	change = skill_level;	break;	//Season 5 Skeleton Ring
//	default: change = -1;	break;
//	}
//
//	if(lpObj->m_Change >= 0 && lpObj->m_Change == change)
//	{
//		return false;
//	}
//
//	if(lpObj->m_Change == 41 && change != 41)
//	{
//		lpObj->AddLife = 0;
//
//		GCReFillSend(lpObj->m_Index,lpObj->Life,0xFF,0,lpObj->iShield);
//		GCReFillSend(lpObj->m_Index,(lpObj->MaxLife + lpObj->AddLife),0xFE,0,(lpObj->iMaxShield + lpObj->iAddShield));
//	}
//
//	if(lpObj->m_Change == 372 && change != 372)
//	{
//		lpObj->AddLife = 0;
//		gObjCalCharacter(lpObj->m_Index);
//
//		GCReFillSend(lpObj->m_Index,lpObj->Life,0xFF,0,lpObj->iShield);
//		GCReFillSend(lpObj->m_Index,(lpObj->MaxLife + lpObj->AddLife),0xFE,0,(lpObj->iMaxShield + lpObj->iAddShield));
//	}
//
//	if(lpObj->m_Change == 374) //Season 2.5 add-on
//	{
//		if(change != 374)
//		{
//			lpObj->m_AttackDamageMaxLeft -= 20;
//			lpObj->m_AttackDamageMinLeft -= 20;
//			lpObj->m_AttackDamageMaxRight -= 20;
//			lpObj->m_AttackDamageMinRight -= 20;
//			lpObj->m_MagicDamageMin -= 20;
//			lpObj->m_MagicDamageMax -= 20;
//		}
//	}
//
//	lpObj->m_Change = change;
//	gObjViewportListProtocolCreate(lpObj);
//
////#if(GS_CASTLE==1)
//	g_CastleSiege.NotifySelfCsJoinSide(lpObj->m_Index);
////#endif
//
//	PMSG_KILLCOUNT pMsg = {0};
//
//	PHeadSubSetB((LPBYTE)&pMsg,0xB8,0x01,sizeof(pMsg));
//
//	pMsg.btKillCount = lpObj->m_btKillCount;
//
//	DataSend(aIndex,(LPBYTE)&pMsg,sizeof(pMsg));
//	return true;

	LPOBJ lpObj = &gObj[aIndex];

	int skill_level = -1;

	if(lpObj->Type != OBJ_USER)
	{
		return false;
	}

	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,10))
	{
		if(lpObj->pInventory[10].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = lpObj->pInventory[10].m_Level;
		}
	}

	if(lpObj->pInventory[11].IsItem()==1 && skill_level == -1 && lpObj->pInventory[11].m_Type == ITEMGET(13,10))
	{
		if(lpObj->pInventory[11].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = lpObj->pInventory[11].m_Level;
		}
	}

	if(skill_level > 7)
	{
		return false;
	}

	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,39))
	{
		if(lpObj->pInventory[10].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 372;
		}
	}

	if(lpObj->pInventory[11].IsItem()==1 && skill_level == -1 && lpObj->pInventory[11].m_Type == ITEMGET(13,39))
	{
		if(lpObj->pInventory[11].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 372;
		}
	}

	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,40)) //Second Edition
	{
		if(lpObj->pInventory[10].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 373;
		}
	}

	if(lpObj->pInventory[11].IsItem()==1 && lpObj->pInventory[11].m_Type == ITEMGET(13,40)) //Second Edition
	{
		if(lpObj->pInventory[11].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 373;
		}
	}

	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,41)) //Season 2.5 add-on
	{
		if(lpObj->pInventory[10].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 374;
		}
	}

	if(lpObj->pInventory[11].IsItem()==1 && lpObj->pInventory[11].m_Type == ITEMGET(13,41)) //Season 2.5 add-on
	{
		if(lpObj->pInventory[11].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 374;
		}
	}

	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,42)) //Season 2.5 add-on
	{
		if((lpObj->Authority&32) != 32)
		{
			return FALSE;
		}

		skill_level = 378;

	}

	if(lpObj->pInventory[11].IsItem()==1 && lpObj->pInventory[11].m_Type == ITEMGET(13,42)) //Season 2.5 add-on
	{
		if((lpObj->Authority&32) != 32)
		{
			return FALSE;
		}

		skill_level = 378;
	}

	//if( CHECK_ILLUSIONTEMPLE(lpObj->MapNumber) )
	//{
	//	if( g_IllusionTempleEvent.GetIllusionTempleState(lpObj->MapNumber) != 0 )
	//	{
	//		int team = g_IllusionTempleEvent.GetUserTeam(lpObj->MapNumber, lpObj->m_Index);
	//		if( team == 0 )
	//		{
	//			skill_level = 404;
	//		}
	//		else if( team == 1 )
	//		{
	//			skill_level = 405;
	//		}
	//	}
	//}

		if(IT_MAP_RANGE(lpObj->MapNumber) != FALSE) //Season2.5 add-on (illusion temple checks)
		{
			if(g_IllusionTempleEvent.GetState(lpObj->MapNumber) != 0)
			{
				int team = g_IllusionTempleEvent.GetUserJoinSide(lpObj->MapNumber, lpObj->m_Index);
				if(team == 0)
				{
					skill_level = 404;
				}
				else if(team == 1)
				{
					skill_level = 405;
				}
			}
		}

	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,68)) //Season 4 add-on
	{
		if(lpObj->pInventory[10].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 477;
		}
	}

	if(lpObj->pInventory[11].IsItem()==1 && lpObj->pInventory[11].m_Type == ITEMGET(13,68)) //Season 4 add-on
	{
		if(lpObj->pInventory[11].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 477;
		}
	}

	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,76)) //Season 4.6 add-on
	{
		if(lpObj->pInventory[10].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 503;
		}
	}

	if(lpObj->pInventory[11].IsItem()==1 && lpObj->pInventory[11].m_Type == ITEMGET(13,76)) //Season 4.6 add-on
	{
		if(lpObj->pInventory[11].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 503;
		}
	}
	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13, 122)) // Season 5 Episode 2 JPN Skeleton Ring
	{
		if(lpObj->pInventory[10].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 548;
		}
	}

	if(lpObj->pInventory[11].IsItem()==1 && lpObj->pInventory[11].m_Type == ITEMGET(13, 122)) // Season 5 Episode 2 JPN Skeleton Ring
	{
		if(lpObj->pInventory[11].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 548;
		}
	}
	int change = -1;

	switch(skill_level)
	{
	case 0: change = 2;	break;
	case 1: change = 7; break;
	case 2: change = 14;	break;
	case 3: change = 8;	break;
	case 4:	change = 9;	break;
	case 5:	change = 41;	break;
	case 372:	change = skill_level;	break;
	case 373:	change = skill_level;	break; //Second Edition
	case 374:	change = skill_level;	break; //season 2.5
	case 378:	change = skill_level;	break; //season 2.5
	case 404:								   //season 2.5
	case 405:	change = skill_level;	break;
	case 477:	change = skill_level;	break; //season 4
	case 503:	change = skill_level;	break; //season 4.6
	case 548:	change = skill_level;	break; // Season 5 Episode 2 JPN
	default: change = -1;	break;
	}

	if(lpObj->m_Change >= 0 && lpObj->m_Change == change)
	{
		return false;
	}

	if(lpObj->m_Change == 41 && change != 41)
	{
		lpObj->AddLife = 0;

		GCReFillSend(lpObj->m_Index,lpObj->Life,0xFF,0,lpObj->iShield);
		GCReFillSend(lpObj->m_Index,lpObj->MaxLife + lpObj->AddLife,0xFE,0,lpObj->iMaxShield + lpObj->iAddShield);
	}

	if(lpObj->m_Change == 372 && change != 372)
	{
		lpObj->AddLife = 0;
		gObjCalCharacter(lpObj->m_Index);

		GCReFillSend(lpObj->m_Index,lpObj->Life,0xFF,0,lpObj->iShield);
		GCReFillSend(lpObj->m_Index,lpObj->MaxLife + lpObj->AddLife,0xFE,0,lpObj->iMaxShield + lpObj->iAddShield);
	}

	if(lpObj->m_Change == 374) //Season 2.5 add-on
	{
		if(change != 374)
		{
			lpObj->m_AttackDamageMaxLeft -= 20;
			lpObj->m_AttackDamageMinLeft -= 20;
			lpObj->m_AttackDamageMaxRight -= 20;
			lpObj->m_AttackDamageMinRight -= 20;
			lpObj->m_MagicDamageMin -= 20;
			lpObj->m_MagicDamageMax -= 20;
		}
	}

	if(lpObj->m_Change == 503) //Season 4.6 add-on
	{
		if(change != 503)
		{
			lpObj->m_AttackDamageMaxLeft -= 30;
			lpObj->m_AttackDamageMinLeft -= 30;
			lpObj->m_AttackDamageMaxRight -= 30;
			lpObj->m_AttackDamageMinRight -= 30;
			lpObj->m_MagicDamageMin -= 30;
			lpObj->m_MagicDamageMax -= 30;
		}
	}

	lpObj->m_Change = change;
	gObjViewportListProtocolCreate(lpObj);

	//#if(_GSCS==1)
	g_CastleSiege.NotifySelfCsJoinSide(lpObj->m_Index);
	//#endif

	PMSG_KILLCOUNT pMsg = {0};

	PHeadSubSetB((LPBYTE)&pMsg,0xB8,0x01,sizeof(pMsg));

	pMsg.btKillCount = lpObj->m_btKillCount;

	DataSend(aIndex,(LPBYTE)&pMsg,sizeof(pMsg));
	return true;
}

void CObjUseSkill::SkillHealing(int aIndex, int aTargetIndex, int skill_level) //
{
	int skillSuccess = true;
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(lpTargetObj->Type != OBJ_USER && lpTargetObj->m_RecallMon == -1)
	{
		return;
	}

	if(lpObj->Class != CLASS_ELF)
	{
		return;
	}

	if(CC_MAP_RANGE(lpObj->MapNumber) && lpObj->m_Index != lpTargetObj->m_Index)
	{
		return;
	}

	if(skill_level < 0 || skill_level > 7)
	{
		skill_level = 0;
	}

	lpTargetObj->Life = ((skill_level + 1) * 5 + (lpObj->Energy + lpObj->AddEnergy) / 5) + lpTargetObj->Life;

	if((lpTargetObj->MaxLife + lpTargetObj->AddLife) < lpTargetObj->Life)
	{
		lpTargetObj->Life = lpTargetObj->MaxLife + lpTargetObj->AddLife;
	}

	if(lpTargetObj->Type == OBJ_USER)
	{
		GCReFillSend(lpTargetObj->m_Index,lpTargetObj->Life,0xFF,0,lpTargetObj->iShield);
		GCMagicAttackNumberSend(lpObj,AT_SKILL_HEALING,lpTargetObj->m_Index,skillSuccess);

		for(int n = 0; n < MAX_VIEWPORT; n++)
		{
			if(lpObj->VpPlayer2[n].type == OBJ_MONSTER && lpObj->VpPlayer2[n].state != 0)
			{
				LPOBJ lpMonster = &gObj[lpObj->VpPlayer2[n].number];
				if(lpMonster->m_iCurrentAI != 0)
				{
					lpMonster->m_Agro.IncAgro(lpObj->m_Index,(lpObj->Energy / 5)/40);
				}
			}
		}
	}
	else if(lpTargetObj->m_RecallMon >= 0)
	{
		GCRecallMonLife(lpTargetObj->m_RecallMon,(int)lpTargetObj->MaxLife,(int)lpTargetObj->Life);
	}
}

int CObjUseSkill::SkillMonsterCall(int aIndex, int MonsterType, int x, int y) //identical gs-cs 56
{
	if(gObj[aIndex].MapNumber == MAP_INDEX_ICARUS)
	{
		return false;
	}

	if(CC_MAP_RANGE(gObj[aIndex].MapNumber))
	{
		return false;
	}

	if(gObj[aIndex].m_RecallMon >= 0)
	{
		GCRecallMonLife(aIndex,60,0);
		gObjMonsterCallKill(aIndex);
		return false;
	}

	int result = gObjAddCallMon();

	if(result >= 0)
	{
		gObj[result].X = x;
		gObj[result].Y = y;
		gObj[result].MTX = x;
		gObj[result].MTY = y;
		gObj[result].Dir = 2;
		gObj[result].MapNumber = gObj[aIndex].MapNumber;
		gObjSetMonster(result,MonsterType);
		gObj[result].m_RecallMon = aIndex;
		gObj[result].m_Attribute = 100;
		gObj[result].TargetNumber = (WORD)-1;
		gObj[result].m_ActState.Emotion = 0;
		gObj[result].m_ActState.Attack = 0;
		gObj[result].m_ActState.EmotionCount = 0;
		gObj[result].PathCount = 0;

		gObj[aIndex].m_RecallMon = result;
		gObj[result].m_MoveRange = 15;

		if( gObj[aIndex].m_MPSkillOpt.MpsSummonMonster1 > 0.0f )
		{
			gObj[result].MaxLife	+= gObj[result].MaxLife / 100.0f * gObj[aIndex].m_MPSkillOpt.MpsSummonMonster1;
			gObj[result].Life		+= gObj[result].Life / 100.0f * gObj[aIndex].m_MPSkillOpt.MpsSummonMonster1;
		}

		if( gObj[aIndex].m_MPSkillOpt.MpsSummonMonster2 > 0.0f )
		{
			gObj[result].m_Defense	+= gObj[result].m_Defense / 100.0f * gObj[aIndex].m_MPSkillOpt.MpsSummonMonster1;	//maybe bug?
		}

		if( gObj[aIndex].m_MPSkillOpt.MpsSummonMonster3 > 0.0f )
		{
			gObj[result].m_AttackDamageMax	+= gObj[result].m_AttackDamageMax / 100.0f * gObj[aIndex].m_MPSkillOpt.MpsSummonMonster1;	//too maybe?
			gObj[result].m_AttackDamageMin	+= gObj[result].m_AttackDamageMin / 100.0f * gObj[aIndex].m_MPSkillOpt.MpsSummonMonster1;	//too maybe?
		}

		GCRecallMonLife(gObj[result].m_RecallMon,(int)gObj[result].MaxLife,(int)gObj[result].Life);
		return true;
	}
	return false;
}

void CObjUseSkill::SkillBlowOfFury(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex, BOOL isCombo) //
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int DuelIndex = lpObj->m_iDuelUser;
	int HitCount = 0;
	int bAttack = 0;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
//#if(GS_CASTLE==1)
				else if(lpObj->VpPlayer2[count].type != OBJ_NPC && gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
				{
					EnableAttack = 1;
				}
//#endif
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 4)
					{
						bAttack = 0;

						if(HitCount > 15)
						{
							bAttack = 0;
						}

						if(HitCount >= 10)
						{
							if(rand()%2)
							{
								bAttack = 1;
							}
						}
						else
						{
							bAttack = 1;
						}

						if(bAttack != 0)
						{
							gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,500,lpMagic->m_Skill,isCombo);

							if(isCombo != 0)
							{
								GCMagicAttackNumberSend(lpObj,AT_SKILL_COMBO,aIndex,1);
							}
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
}

void CObjUseSkill::SkillWheel(int aIndex, CMagicInf* lpMagic, int aTargetIndex, BOOL isCombo) //
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int HitCount = 0;
	int bAttack;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
//#if(GS_CASTLE==1)
				else if(lpObj->VpPlayer2[count].type != OBJ_NPC && gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
				{
					EnableAttack = 1;
				}
//#endif
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 3)
					{
						bAttack = 0;

						if(HitCount > 15)
						{
							bAttack = 0;
						}

						if(HitCount >= 10)
						{
							if(rand()%2)
							{
								bAttack = 1;
							}
						}
						else
						{
							bAttack = 1;
						}

						if(bAttack != 0)
						{

							gObjAttack(lpObj,&gObj[tObjNum],lpMagic,0,1,0,isCombo,0,0);

							if(isCombo != 0)
							{
								GCMagicAttackNumberSend(lpObj,AT_SKILL_COMBO,gObj[tObjNum].m_Index,1);
							}
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
}

void CObjUseSkill::SkillPowerSlash(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE targetangle, int aTargetIndex) //
{
	LPOBJ lpObj = &gObj[aIndex];
	int StartDis = 1;
	int tObjNum;
	::SkillFrustrum(targetangle,aIndex);
	int count = 0;
	int HitCount = 0;
	int bAttack;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
//#if(GS_CASTLE==1)
				else if(lpObj->VpPlayer2[count].type != OBJ_NPC && gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
				{
					EnableAttack = 1;
				}
//#endif
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(SkillTestFrustrum(gObj[tObjNum].X,gObj[tObjNum].Y,aIndex))
					{
						bAttack = 0;

						if(HitCount > 10)
						{
							bAttack = 0;
						}
						else
						{						
							if(HitCount >= 5)
							{
								if(rand()%2)
								{
									bAttack = 1;
								}
							}
							else
							{
								bAttack = 1;
							}
						}

						if(bAttack != 0)
						{
							gObjAttack(lpObj,&gObj[tObjNum],lpMagic,1,1,0,0,0,0);
						}

						HitCount++;
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
}

int CObjUseSkill::SkillDeathPoison(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex) //Identical gs-cs 56
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int FirstHit = 0;
	int HitCount = 0;
	int bAttack;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;
	LPOBJ lpTargetObj = &gObj[aTargetIndex];


	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
//#if(GS_CASTLE==1)
				else if(lpObj->VpPlayer2[count].type != OBJ_NPC && gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
				{
					EnableAttack = 1;
				}
//#endif
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					//LogAddC(2, "%s %d", gObj[tObjNum].Name, this->CalDistance(x,y,gObj[tObjNum].X,gObj[tObjNum].Y));
					if(this->CalDistance(x,y,gObj[tObjNum].X,gObj[tObjNum].Y) < 4)
					{
						bAttack = 0;

						if(HitCount > 10)
						{
							bAttack = 0;
						}
						
						if(HitCount >= 5)
						{
							if(rand()%2)
							{
								bAttack = 1;
							}
						}
						else
						{
							bAttack = 1;
						}

						if(bAttack != 0)
						{
							int delay = rand()%500;
							gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,delay,lpMagic->m_Skill,0);
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
	return true;
}

int CObjUseSkill::SkillSuddenIce(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex) //
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int FirstHit = 0;
	int HitCount = 0;
	int bAttack;
	LPOBJ lpTargetObj = &gObj[aTargetIndex];
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
//#if(GS_CASTLE==1)
				else if(lpObj->VpPlayer2[count].type != OBJ_NPC && gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
				{
					EnableAttack = 1;
				}
//#endif
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(this->CalDistance(x,y,gObj[tObjNum].X,gObj[tObjNum].Y) < 4)
					{
						bAttack = 0;

						if(HitCount > 10)
						{
							bAttack = 0;
						}
						
						if(HitCount >= 5)
						{
							if(rand()%2)
							{
								bAttack = 1;
							}
						}
						else
						{
							bAttack = 1;
						}

						if(bAttack != 0)
						{
							int delay = rand()%500;
							gObjAttack(lpObj,&gObj[tObjNum],lpMagic,1,1,0,0,0,0);
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
	return true;
}

BOOL CObjUseSkill::SkillHellFire2(int aIndex, int aTargetIndex, CMagicInf * lpMagic) //
{
	if(aTargetIndex == 58)
	{
		return this->SkillHellFire2Start(aIndex,lpMagic);
	}

	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;

	if(lpObj->SkillHellFire2State == 0)
	{
		LogAddTD("[%s][%s] 헬파이어2 버튼 눌러지지도 않았는데 완료가 되었다",lpObj->AccountID,lpObj->Name); //HermeX Fix
		return false;
	}

	lpObj->SkillHellFire2State = 0;
	int count = 0;
	lpObj->SkillHellFire2Time = 0;

	LPOBJ lpTargetObj = &gObj[aTargetIndex];
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(aTargetIndex == tObjNum || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
//#if(GS_CASTLE==1)
				else if(lpObj->VpPlayer2[count].type != OBJ_NPC && gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
				{
					EnableAttack = 1;
				}
//#endif
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) <= 6)
					{
						gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,600,lpMagic->m_Skill,0);
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}

	GCMagicAttackNumberSend(lpObj,AT_SKILL_EXPHELL,lpObj->m_Index,1);
	return true;
}

BOOL CObjUseSkill::SkillHellFire2Start(int aIndex, CMagicInf * lpMagic) //
{
	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->SkillHellFire2State != 0)
	{
		LogAddTD("[%s][%s] 헬파이어2 버튼 눌러졌는데 또 눌러졌다는거 왔다",lpObj->AccountID,lpObj->Name); //
		return false;
	}

	lpObj->SkillHellFire2Time = GetTickCount();
	lpObj->SkillHellFire2State = 1;
	lpObj->SkillHellFire2Count = 0;

	GCMagicAttackNumberSend(lpObj,AT_SKILL_EXPHELL_START,aIndex,1);
	return true;
}

BOOL CObjUseSkill::SkillKnightBlow(int aIndex, int aTargetIndex, CMagicInf* lpMagic, BOOL isCombo) //
{
	LPOBJ lpObj = &gObj[aIndex];
	int StartDis = 1;
	int tObjNum;

	float fangle = (float)this->GetAngle(lpObj->X,lpObj->Y,gObj[aTargetIndex].X,gObj[aTargetIndex].Y);

	this->SkillFrustrum(aIndex,fangle,1.5f,3.0f);

	int count = 0;
	int loopcount = 0;
	int attackcheck;
	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);

	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					attackcheck = 0;

					if(loopcount == 0)
					{
						attackcheck = 1;
					}
					else if(rand()%3==0)
					{
						attackcheck = 1;
					}

					if(attackcheck != 0)
					{
						if(::SkillTestFrustrum(gObj[tObjNum].X,gObj[tObjNum].Y,aIndex))
						{
							gObjAttack(lpObj,&gObj[tObjNum],lpMagic,0,1,0,isCombo,0,0);
							if(isCombo != 0)
							{
								GCMagicAttackNumberSend(lpObj,AT_SKILL_COMBO,gObj[tObjNum].m_Index,1);
							}
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			loopcount++;
			count = 0;
			if(loopcount >= 3)
			{
				break;
			}
		}
	}
	return true;
}

void CObjUseSkill::SkillFrustrum(int aIndex, float fangle, float tx, float ty) //
{
	LPOBJ lpObj = &gObj[aIndex];

	vec3_t p[4];

	Vector(-tx ,ty , 0.f, p[0]);
	Vector( tx ,ty , 0.f, p[1]);
	Vector( 1.0f, 0.f, 0.f, p[2]);
	Vector(-1.0f, 0.f, 0.f, p[3]);

	vec3_t Angle;

	Vector(0.f, 0.f, fangle, Angle);

	float Matrix[3][4];

	vec3_t vFrustrum[4];

	AngleMatrix(Angle,Matrix);

	for(int i = 0; i < 4; i++)
	{
		VectorRotate(p[i],Matrix,vFrustrum[i]);

		lpObj->fSkillFrustrumX[i] = (int)vFrustrum[i][0] + lpObj->X;
		lpObj->fSkillFrustrumY[i] = (int)vFrustrum[i][1] + lpObj->Y;
	}
}

void CObjUseSkill::SkillFrustrum2(int aIndex, float fangle, float tx, float ty) //
{
	LPOBJ lpObj = &gObj[aIndex];

	vec3_t p[4];

	Vector(0.f, ty, 0.f, p[0]);
	Vector(0.f, ty, 0.f, p[1]);
	Vector(tx, 1.0f, 0.f, p[2]);
	Vector(-tx, 1.0f, 0.f, p[3]);

	vec3_t Angle;

	Vector(0.f, 0.f, fangle, Angle);

	float Matrix[3][4];

	vec3_t vFrustrum[4];

	AngleMatrix(Angle,Matrix);

	for(int i = 0; i < 4; i++)
	{
		VectorRotate(p[i],Matrix,vFrustrum[i]);

		lpObj->fSkillFrustrumX[i] = (int)vFrustrum[i][0] + lpObj->X;
		lpObj->fSkillFrustrumY[i] = (int)vFrustrum[i][1] + lpObj->Y;
	}
}

int CObjUseSkill::GetAngle(int x, int y, int tx, int ty) //
{
	double diffX = x - tx;
	double diffY = y - ty;

	double rad = atan2(diffY,diffX);

	int angle = (int)(rad * 180 / 3.141592741012573 + 90);

	if(angle < 0)
	{
		angle += 360;
	}
	return angle;
}

int CObjUseSkill::CalDistance(int x, int y, int x1, int y1) //
{
	if(x == x1 && y == y1)
	{
		return 0;
	}

	float tx = (float)(x - x1);
	float ty = (float)(y - y1);

	return (int)(sqrt(tx*tx + ty*ty));
}

BOOL CObjUseSkill::SkillAreaCheck(int angel, int x, int y, int tx, int ty, int dis, int arc) //
{
	int minangel = angel - arc;
	int maxangel = angel + arc;

	if(this->CalDistance(x,y,tx,ty) > dis)
	{
		return false;
	}

	int targetangle = this->GetAngle(x,y,tx,ty);

	if(minangel < 0)
	{
		if(targetangle > maxangel)
		{
			if(targetangle > minangel + 360)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if(maxangel < targetangle)
		{
			return false;
		}
	}
	else if(maxangel > 360)
	{
		if(targetangle < minangel)
		{
			if(targetangle < maxangel - 360)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if(maxangel < targetangle)
		{
			return false;
		}
	}
	else if(minangel > targetangle)
	{
		return false;
	}
	else if(maxangel < targetangle)
	{
		return false;
	}
	return true;
}

BOOL CObjUseSkill::SkillSpear(int aIndex, int aTargetIndex, CMagicInf * lpMagic) //
{
	LPOBJ lpObj = &gObj[aIndex];
	int StartDis = 1;
	int tObjNum;

	int iangle = this->GetAngle(lpObj->X,lpObj->Y,gObj[aTargetIndex].X,gObj[aTargetIndex].Y);
	int count = 0;
	int loopcount = 0;
	int attackcheck;

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);

	if(lpObj->SkillLongSpearChange == 0)
	{
		gObjAttack(lpObj,&gObj[aTargetIndex],lpMagic,0,1,0,0,0,0);
		return true;
	}

	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					attackcheck = 0;

					if(loopcount == 0)
					{
						attackcheck = 1;
					}
					else if(rand()%3==0)
					{
						attackcheck = 1;
					}

					if(attackcheck != 0)
					{
						if(SkillSpearHitBox.HitCheck(iangle,lpObj->X,lpObj->Y,gObj[tObjNum].X,gObj[tObjNum].Y))
						{
							gObjAttack(lpObj,&gObj[tObjNum],lpMagic,0,1,0,0,0,0);
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
	return true;
}

BOOL CObjUseSkill::SkillFireBurst(int aIndex, int aTargetIndex, CMagicInf * lpMagic) //
{
	LPOBJ lpObj = &gObj[aIndex];
	int StartDis = 1;
	int tObjNum;
	int count = 0;
	int loopcount = 0;

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);
	gObjAttack(lpObj,&gObj[aTargetIndex],lpMagic,0,1,0,0,0,0);

	int attackcheck;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;
	int delaytime;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0 && aTargetIndex != tObjNum)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					attackcheck = 0;

					if(loopcount == 0)
					{
						attackcheck = 1;
					}
					else if(rand()%3==0)
					{
						attackcheck = 1;
					}

					if(attackcheck != 0)
					{
						if(gObjCalDistance(&gObj[aTargetIndex],&gObj[tObjNum]) < 3)
						{
							delaytime = (rand()*17)%300 + 500;

							gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,delaytime,lpMagic->m_Skill,0);
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
	return true;
}

BOOL CObjUseSkill::SkillDarkHorseAttack(int aIndex, int aTargetIndex, CMagicInf * lpMagic) //
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int HitCount = 0;
	int bAttack;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	GCMagicAttackNumberSend(lpObj,AT_SKILL_DARKHORSE_ATTACK,lpObj->m_Index,1);

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;
				if(gObj[tObjNum].Class < 100 || gObj[tObjNum].Class > 110)
				{
	
					if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
					{
						EnableAttack = 1;
					}
					else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
					{
						EnableAttack = 1;
					}
//#if(GS_CASTLE==1)
					else if(lpObj->VpPlayer2[count].type != OBJ_NPC && gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
					{
						EnableAttack = 1;
					}
//#endif
					else
					{
						int CallMonIndex = gObj[tObjNum].m_Index;
	
						if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
						{
							CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
						}
	
						if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
						{
							EnableAttack = 1;
						}
					}
				}
	
				if(EnableAttack != 0)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 5)
					{
						bAttack = 0;
	
						if(HitCount > 15)
						{
							bAttack = 0;
						}
	
						if(HitCount >= 10)
						{
							if(rand()%2)
							{
								bAttack = 1;
							}
						}
						else
						{
							bAttack = 1;
						}
	
						if(bAttack != 0)
						{
							gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,500,lpMagic->m_Skill,0);
						}
					}
				}
			}
		}
	
		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
	return true;
}

BOOL CObjUseSkill::RecallPartyCheck(int aIndex, int skill_level) //
{
	LPOBJ lpObj = &gObj[aIndex];
	int number;
	int partynum = 0;

	partynum = lpObj->PartyNumber;

	int partycount;
	LPOBJ lpPartyObj;
	int recallcount = 0;

	if(partynum != -1)
	{
		partycount = gParty.m_PartyS[partynum].Count;

		for(int n = 0; n < MAX_USER_IN_PARTY;n++)
		{
			number = gParty.m_PartyS[partynum].Number[n];

			if(number >= 0)
			{
				lpPartyObj = &gObj[number];

				if(lpPartyObj->m_Index != lpObj->m_Index)
				{
					if(lpPartyObj->MapNumber == lpObj->MapNumber)
					{
						if(lpPartyObj->SkillRecallParty_Time != 0)
						{
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

void CObjUseSkill::SkillRecallParty(int aIndex, int skill_level) //
{

#if(SWENG_FIX==TRUE)
	if ( OBJMAX_RANGE(aIndex) == FALSE )	//FIX_CRASH
	{
		return;
	}
#endif

#if(CUSTOM_ZT_TELEPORT==TRUE)
	//if(!g_ZtTeleport.Check(aIndex))
	//{
	//	return;
	//}
#endif
#if(CUSTOM_ZT_TELEPORT_EVO)
	//if(!g_ZtTeleportEvo.Check(aIndex))
	//{
	//	return;
	//}
#endif
	int skillSuccess = true; //2
	LPOBJ lpObj = &gObj[aIndex]; //3

	if(lpObj->Type != OBJ_USER && lpObj->m_RecallMon == -1)
	{
		return;
	}

#if(EVENT_DUNGEON_SIEGE)
	if(!g_DungeonSiege.SiegeDarkLordSummon(aIndex))
	{
		return;
	}
#endif

	if(!gTeleportManager.CheckDLMasterTeleport(lpObj->MapNumber))
	{
		return;
	}

	if(gGENS)
	{
		if( gGensSystem.IsMapBattleZone(lpObj->MapNumber) )
		{
			char msg[255];
			wsprintf(msg,lMsg.Get(3453));
			GCServerMsgStringSend(msg, lpObj->m_Index, 1);
			return;
		}
	}
#ifdef IMPERIAL_CONFLICT_NEW
		if(CImperialGuardian::IsEventMap(lpObj->MapNumber))
		return;
#endif

	if(this->RecallPartyCheck(aIndex,skill_level) == 0)
	{
		MsgOutput(aIndex,lMsg.Get(1238));
		return;
	}

	if(gMoveCommand.CheckMainToMove(lpObj) == 0)
	{
		char msg[255];
		wsprintf(msg,lMsg.Get(1249));
		GCServerMsgStringSend(msg,lpObj->m_Index,1);
		return;
	}

	if(gMoveCommand.CheckInterfaceToMove(lpObj) == 0)
	{
		char msg[255];
		wsprintf(msg,lMsg.Get(1239));
		GCServerMsgStringSend(msg,lpObj->m_Index,1);
		return;
	}

	//season 4 add-on
	if( lpObj->MapNumber == MAP_INDEX_RAKLION_BOSS &&
		lpObj->Connected == PLAYER_PLAYING &&
		(g_Raklion.GetRaklionState() == RAKLION_STATE_CLOSE_DOOR ||
		g_Raklion.GetRaklionState() == RAKLION_STATE_ALL_USER_DIE ||
		g_Raklion.GetRaklionState() == RAKLION_STATE_NOTIFY_4 ||
		g_Raklion.GetRaklionState() == RAKLION_STATE_END) ) 
	{
		char msg[255];
		wsprintf(msg,lMsg.Get(3417));
		GCServerMsgStringSend(msg,lpObj->m_Index,1);
		return;
	}

	int number;
	int partynum;
	int partycount;
	LPOBJ lpPartyObj;
	int recallcount;

	partynum = 0;
	partynum = lpObj->PartyNumber;

	GCMagicAttackNumberSend(lpObj,AT_SKILL_RECALL_PARTY,lpObj->m_Index,skillSuccess);

	recallcount = 0;

	if(partynum != -1)
	{
		partycount = gParty.m_PartyS[partynum].Count;

		for(int n = 0; n < MAX_USER_IN_PARTY;n ++)
		{
			number = gParty.m_PartyS[partynum].Number[n];

			if(number >= 0)
			{
				lpPartyObj = &gObj[number];

				if(lpPartyObj->m_Index != lpObj->m_Index)
				{
//#if(GS_CASTLE==1)
					if(g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
					{
						if(lpPartyObj->m_btCsJoinSide != lpObj->m_btCsJoinSide)
						{
							continue;
						}
					}
//#endif

					if(gPandoraBoxEvent.Started && gPandoraBoxEvent.ActivePlayer == lpPartyObj->m_Index)
					{
						continue;
					}

					if(!gTeleportManager.CheckTeleoprtMap(lpObj->m_Index, lpPartyObj->m_Index))
					{
						continue;
					}

					if(!gTeleportManager.CheckTeleportDL(lpObj->MapNumber) || !gTeleportManager.CheckTeleportDL(lpPartyObj->MapNumber))
					{
						continue;
					}

					if(!gTeleportManager.CheckDLMemberTeleport(lpPartyObj->MapNumber))
					{
						continue;
					}

					if(g_ZtLicense.CheckUser(eZtUB::ulasevich)	|| g_ZtLicense.CheckUser(eZtUB::ulasevich2))
					{
						if(lpPartyObj->m_PK_Level >= 6)
						{
							continue;
						}
					}

					int movelevel = gMoveCommand.GetMoveLevel(lpObj->MapNumber,lpObj->X,lpObj->Y,lpPartyObj->Class);
					int bCheckMainToMove = gMoveCommand.CheckMainToMove(lpPartyObj);
					int bCheckEquipmentToMove = gMoveCommand.CheckEquipmentToMove(lpPartyObj,lpObj->MapNumber);
					int bCheckInterfaceToMove = gMoveCommand.CheckInterfaceToMove(lpPartyObj);

					if(lpPartyObj->Level >= movelevel
						&& movelevel != -1
						&& bCheckMainToMove != false
						&& bCheckEquipmentToMove != false
						&& bCheckInterfaceToMove != false)
					{
						int addx;
						int addy;
						int count = 50;
						int Find = 0;

						while(count--)
						{
							if( g_ZtLicense.CheckUser(eZtUB::Gredy)		||	   
								g_ZtLicense.CheckUser(eZtUB::Gredy2)	||
								g_ZtLicense.CheckUser(eZtUB::GredyLocal) )
							{
								addx = lpObj->X + rand()%5 - 2;
								addy = lpObj->Y + rand()%5 - 2;
							}
							else
							{
								addx = lpObj->X + rand()%9 - 4;
								addy = lpObj->Y + rand()%9 - 4;
							}

							if(gObjCheckTeleportArea(lpObj->m_Index,addx,addy))
							{
								Find = 1;
								break;
							}
						}

						if(Find == 0)
						{
							addx = lpObj->X;
							addy = lpObj->Y;
						}

						lpPartyObj->SkillRecallParty_Time = 7;
						lpPartyObj->SkillRecallParty_MapNumber = lpObj->MapNumber;
						lpPartyObj->SkillRecallParty_X = addx;
						lpPartyObj->SkillRecallParty_Y = addy;

						//Season4 add-on
						if(lpObj->MapNumber == MAP_INDEX_RAKLION_BOSS)
						{
							g_RaklionBattleUserMng.AddUserData(lpPartyObj->m_Index);
						}

#if(FIX_MUHELPER_TP == TRUE)
						lpPartyObj->MuHelperTeleportFix = true;
#endif

						char msg[255];
						wsprintf(msg,lMsg.Get(1251));
						GCServerMsgStringSend(msg,lpPartyObj->m_Index,1);
						recallcount++;
					}
					else
					{
						char msg[255];
						wsprintf(msg,lMsg.Get(1252));
						GCServerMsgStringSend(msg,lpPartyObj->m_Index,1);
					}
				}
			}
		}
	}

	if(recallcount != 0)
	{
		char msg[255];
		wsprintf(msg,lMsg.Get(1244),recallcount);
		GCServerMsgStringSend(msg,lpObj->m_Index,1);
	}
}

void CObjUseSkill::SkillAddCriticalDamage(int aIndex, int skill_level) //004C4920
{
	int skillSuccess = true;
	LPOBJ lpObj = &gObj[aIndex];
	int number;

	if (szAuthKey[14] != AUTHKEY14 )
	{
		DestroyGIocp();
	}

	if(lpObj->Type != OBJ_USER && lpObj->m_RecallMon == -1)
	{
		return;
	}

	if(lpObj->Class != CLASS_DARKLORD)
	{
		return;
	}

	int partynum = 0;
	int totallevel = 0;
	int partycount;
	int dis;

	int ApplyPartyIndex[MAX_USER_IN_PARTY];
	LPOBJ lpPartyObj;
	memset(ApplyPartyIndex,-1,sizeof(ApplyPartyIndex));

	partynum = lpObj->PartyNumber;

	if(partynum != -1)
	{
		partycount = gParty.m_PartyS[partynum].Count;

		for(int n = 0; n < MAX_USER_IN_PARTY; n++)
		{
			number = gParty.m_PartyS[partynum].Number[n];

			if(number >= 0)
			{
				lpPartyObj = &gObj[number];

				if(lpObj->MapNumber == lpPartyObj->MapNumber)
				{
					dis = gObjCalDistance(lpObj,&gObj[number]);
					if(dis < 10)
					{
						ApplyPartyIndex[n] = lpPartyObj->m_Index;
					}
				}
			}
		}
	}

	int addcriticaldamagevalue = (lpObj->Leadership + lpObj->AddLeadership)/g_SkillAdditionInfo.CriticalDamageEffectDiv1 + (lpObj->Energy + lpObj->AddEnergy)/g_SkillAdditionInfo.CriticalDamageEffectDiv2;

	if( g_SkillAdditionInfo.CriticalDamageEffectMax > 0 && addcriticaldamagevalue > g_SkillAdditionInfo.CriticalDamageEffectMax )
	{
		addcriticaldamagevalue = g_SkillAdditionInfo.CriticalDamageEffectMax;
	}

	int SkillTime = (lpObj->Energy + lpObj->AddEnergy)/g_SkillAdditionInfo.CriticalDamageTimeDiv + g_SkillAdditionInfo.CriticalDamageTimeStart;

	if( g_SkillAdditionInfo.CriticalDamageTimeMax > 0 && SkillTime > g_SkillAdditionInfo.CriticalDamageTimeMax )
	{
		SkillTime = g_SkillAdditionInfo.CriticalDamageTimeMax;
	}

	if(partynum == -1)
	{
		gObjApplyBuffEffectDuration(lpObj, AT_INCREASE_CRITICAL_DMG, 17, addcriticaldamagevalue, 0, 0, SkillTime); //season3 add-on

		MsgOutput(aIndex,lMsg.Get(1240),SkillTime);
		GCMagicAttackNumberSend(lpObj,AT_SKILL_ADD_CRITICALDAMAGE,lpObj->m_Index,skillSuccess);
	}
	else
	{
		for(int n = 0;n < MAX_USER_IN_PARTY;n++)
		{
			if(ApplyPartyIndex[n] != -1)
			{
				lpPartyObj = &gObj[ApplyPartyIndex[n]];

				gObjApplyBuffEffectDuration(lpPartyObj, AT_INCREASE_CRITICAL_DMG, 17, addcriticaldamagevalue, 0, 0, SkillTime); //season3 add-on

				MsgOutput(aIndex,lMsg.Get(1240),SkillTime);
				GCMagicAttackNumberSend(lpObj,AT_SKILL_ADD_CRITICALDAMAGE,lpPartyObj->m_Index,skillSuccess);
			}
		}
	}
}

void CObjUseSkill::SkillElectricSpark(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex) //Identical gs-cs 56
{
	LPOBJ lpObj = &gObj[aIndex];

	int TargePosx = lpObj->X - (8 - (TargetPos & 15));
	int TargePosy = lpObj->Y - (8 - ((TargetPos & 240) >> 4));

	int tObjNum;
	int count = 0;
	int DuelIndex = lpObj->m_iDuelUser;
	int iangle = this->GetAngle(lpObj->X,lpObj->Y,TargePosx,TargePosy);
	int delaytime;
	int Hit = 0;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
//#if(GS_CASTLE==1)
				else if(lpObj->VpPlayer2[count].type != OBJ_NPC && gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
				{
					EnableAttack = 1;
				}
//#endif
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(SkillElectricSparkHitBox.HitCheck(iangle,gObj[aIndex].X,gObj[aIndex].Y,gObj[tObjNum].X,gObj[tObjNum].Y))
					{
						delaytime = 500;
						Hit = 1;

						gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,delaytime,lpMagic->m_Skill,0);
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}

	if(Hit != 0)
	{
		DecPartyMemberHPandMP(lpObj);
	}
}

int  DecPartyMemberHPandMP(LPOBJ lpObj)
{
	LPOBJ lpPartyObj;
	int partynum = lpObj->PartyNumber;

	if(OBJMAX_RANGE(partynum)==false)
	{
		LogAdd("error : DecPartyMemberHPandMP %s %d",__FILE__,__LINE__);
		return false;
	}

	int partycount = gParty.m_PartyS[partynum].Count;
	int retcount = 0;

	for(int n = 0; n < MAX_USER_IN_PARTY;n++)
	{
		int number = gParty.m_PartyS[partynum].Number[n];

		if(number >= 0)
		{
			lpPartyObj = &gObj[number];

			if(lpObj->MapNumber == lpPartyObj->MapNumber && lpObj->m_Index != number)
			{
				int dis = gObjCalDistance(lpObj,&gObj[number]);
				if(dis < 10)
				{
					lpPartyObj = &gObj[number];

					int declife = (int)(lpPartyObj->Life * 20.0f / 100.0f);
					int decmana = (int)(lpPartyObj->Mana * 5.0f / 100.0f);

					lpPartyObj->Life = lpPartyObj->Life - declife;
					lpPartyObj->Mana = lpPartyObj->Mana - decmana;

					GCReFillSend(lpPartyObj->m_Index,lpPartyObj->Life,0xFF,0,lpPartyObj->iShield);
					GCManaSend(lpPartyObj->m_Index,lpPartyObj->Mana,0xFF,0,lpPartyObj->BP);
					retcount++;
				}
			}
		}
	}

	return retcount;
}

BOOL CObjUseSkill::SkillSummon(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex)==false)
	{
		return false;
	}

	int iSummonCount = 1;
	int iSummonMonterType = 0;
	BYTE bDoSummon = 1;
	BYTE bSummonSuccess = 0;
	BYTE cSummonX = 0;
	BYTE cSummonY = 0;

	LPOBJ lpObj = &gObj[aIndex];

	switch(lpObj->Class)
	{
	case 161:
		iSummonMonterType = rand()%2+ 147;
		bDoSummon = (rand()%15) ? false : true;
		break;
	case 181:
		iSummonMonterType = rand()%2+ 177;
		bDoSummon = (rand()%15) ? false : true;
		break;
	case 189:
		iSummonMonterType = rand()%2+ 185;
		bDoSummon = (rand()%15) ? false : true;
		break;
	case 197:
		iSummonMonterType = rand()%2+ 193;
		bDoSummon = (rand()%15) ? false : true;
		break;
	case 267:
		iSummonMonterType = rand()%2+ 263;
		bDoSummon = (rand()%15) ? false : true;
		break;
	case 275:
		iSummonMonterType = rand()%2+ 271;
		bDoSummon = (rand()%15) ? false : true;
		break;
	}

	if(bDoSummon == false)
	{
		return false;
	}

	for(int iSC = 0; iSC < iSummonCount; iSC++)
	{
		BYTE cSX = lpObj->X;
		BYTE cSY = lpObj->Y;

		if(gObjGetRandomFreeLocation(lpObj->MapNumber,(BYTE &)cSX,(BYTE &)cSY,2,2,30)==1)
		{
			int result = gObjAddMonster(lpObj->MapNumber);

			if(result >= 0)
			{
				gObj[result].m_PosNum = (WORD)-1;
				gObj[result].X = cSX;
				gObj[result].Y = cSY;
				gObj[result].MapNumber = lpObj->MapNumber;
				gObj[result].TX = gObj[result].X;
				gObj[result].TY = gObj[result].Y;
				gObj[result].m_OldX = gObj[result].X;
				gObj[result].m_OldY = gObj[result].Y;
				gObj[result].Dir = 1;
				gObj[result].StartX = gObj[result].X;
				gObj[result].StartY = gObj[result].Y;
				gObjSetMonster(result,iSummonMonterType);
				gObj[result].m_Attribute = 60;
				gObj[result].MaxRegenTime = 0;
				gObj[result].Dir = rand()%8;
				bSummonSuccess = 1;
				cSummonX = gObj[result].StartX;
				cSummonY = gObj[result].StartY;
			}
		}
	}

	GCMagicAttackNumberSend(lpObj,AT_SKILL_SUMMON,MAKE_NUMBERW(cSummonY, cSummonX),bSummonSuccess);
	return bSummonSuccess;
}

BOOL CObjUseSkill::SkillImmuneToMagic(int aIndex, CMagicInf * lpMagic) //
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(gObjSearchActiveEffect(lpObj, AT_IMMUNE_MAGIC) == FALSE && gObjSearchActiveEffect(lpObj, AT_IMMUNE_HARM) == FALSE) //season3 add-on
	{
		gObjApplyBuffEffectDuration(lpObj, AT_IMMUNE_MAGIC, 0, 0, 0, 0, 10); //season3 add-on
		return true;
	}

	//GCMagicAttackNumberSend(lpObj,AT_SKILL_IMMUNE_TO_MAGIC,lpObj->m_Index,1);
	return false;
}

BOOL CObjUseSkill::SkillImmuneToHarm(int aIndex, CMagicInf * lpMagic) //
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(gObjSearchActiveEffect(lpObj, AT_IMMUNE_MAGIC) == FALSE && gObjSearchActiveEffect(lpObj, AT_IMMUNE_HARM) == FALSE) //season3 add-on
	{
		gObjApplyBuffEffectDuration(lpObj, AT_IMMUNE_HARM, 0, 0, 0, 0, 10); //season3 add-on
		return true;
	}

	//GCMagicAttackNumberSend(lpObj,AT_SKILL_IMMUNE_TO_HARM,lpObj->m_Index,1);
	return false;
}

int CObjUseSkill::RemoveSpecificSkillState(LPOBJ lpObj, int iSkillNumber) //
{
	if(lpObj->Type != OBJ_USER)
	{
		return false;
	}

	int iViewSkillState = 0;

	if(iSkillNumber == AT_SKILL_ATTACK)
	{
		gObjRemoveBuffEffect(lpObj, AT_INCREASE_ATTACK); //season3 add-on
	}
	else if(iSkillNumber == AT_SKILL_DEFENSE)
	{
		gObjRemoveBuffEffect(lpObj, AT_INCREASE_DEFENSE); //season3 add-on
	}

	return true;
}

BOOL CObjUseSkill::RemoveAllCharacterInvalidMagicAndSkillState(LPOBJ lpObj) //004C61F0
{
	if(lpObj->Type != OBJ_USER)
	{
		return false;
	}

	lpObj->m_SkillAttackTime = 0;
	lpObj->m_SkillAttack = 0;


	return true;
}

BOOL CObjUseSkill::SkillKnightRush(int aIndex, int aTargetIndex, CMagicInf * lpMagic) //
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];
	//int ExBKCSSKill = GetPrivateProfileInt("CastleSkills","CastleSkillsOnNormal",0,"..\\Data\\ZtData\\Skills.ini");
	if(!ZtConfig.Character.CastleSiegeSkillEnable)
	{
		if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
		{
			return false;
		}
	}

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);
	gObjAttack(lpObj,&gObj[aTargetIndex],lpMagic,0,1,0,0,0,0);
	return true;
}




BOOL CObjUseSkill::SkillWizardJavalin(int aIndex, int aTargetIndex, CMagicInf * lpMagic) //
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];
	//int ExBKCSSKill = GetPrivateProfileInt("CastleSkills","CastleSkillsOnNormal",0,"..\\Data\\ZtData\\Skills.ini");
	if(!ZtConfig.Character.CastleSiegeSkillEnable)
	{
		if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
		{
			return false;
		}
	}

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);

	int iDelay = 500;

	gObjAddAttackProcMsgSendDelay(lpObj,50,aTargetIndex,iDelay,lpMagic->m_Skill,0);
	gObjAddAttackProcMsgSendDelay(lpObj,50,aTargetIndex,iDelay+200,lpMagic->m_Skill,0);
	return true;
}




BOOL CObjUseSkill::SkillElfRush(int aIndex, int aTargetIndex, CMagicInf * lpMagic) //
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	//int ExBKCSSKill = GetPrivateProfileInt("CastleSkills","CastleSkillsOnNormal",0,"..\\Data\\ZtData\\Skills.ini");
	if(!ZtConfig.Character.CastleSiegeSkillEnable)
	{
		if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
		{
			return false;
		}
	}

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);
	gObjAddAttackProcMsgSendDelay(lpObj,50,aTargetIndex,800,lpMagic->m_Skill,0);
	return true;
}




BOOL CObjUseSkill::SkillMagumOneFlash(int aIndex, int aTargetIndex, CMagicInf * lpMagic) //
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];
	//int ExBKCSSKill = GetPrivateProfileInt("CastleSkills","CastleSkillsOnNormal",0,"..\\Data\\ZtData\\Skills.ini");
	if(!ZtConfig.Character.CastleSiegeSkillEnable)
	{
		if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
		{
			return false;
		}
	}
	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);
	gObjAttack(lpObj,&gObj[aTargetIndex],lpMagic,0,1,0,0,0,0);
	gObjAddAttackProcMsgSendDelay(lpObj,50,aTargetIndex,100,lpMagic->m_Skill,0);
	return true;
}




BOOL CObjUseSkill::SkillMagumDeathCannon(int aIndex, int aTargetIndex, CMagicInf * lpMagic) //
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];
	//int ExBKCSSKill = GetPrivateProfileInt("CastleSkills","CastleSkillsOnNormal",0,"..\\Data\\ZtData\\Skills.ini");
	if(!ZtConfig.Character.CastleSiegeSkillEnable)
	{
		if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
		{
			return false;
		}
	}

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);
	gObjAttack(lpObj,&gObj[aTargetIndex],lpMagic,0,1,0,0,0,0);
	return true;
}




BOOL CObjUseSkill::SkillDarklordSpaceSplit(int aIndex, int aTargetIndex, CMagicInf * lpMagic) //
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	//int ExBKCSSKill = GetPrivateProfileInt("CastleSkills","CastleSkillsOnNormal",0,"..\\Data\\ZtData\\Skills.ini");
	if(!ZtConfig.Character.CastleSiegeSkillEnable)
	{
		if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
		{
			return false;
		}
	}

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);
	gObjAddAttackProcMsgSendDelay(lpObj,50,aTargetIndex,500,lpMagic->m_Skill,0);
	return true;
}

BOOL CObjUseSkill::SkillBrandOfSkill(int aIndex, int aTargetIndex, CMagicInf * lpMagic) //
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	int count = 0;

	gObjApplyBuffEffectDuration(lpObj, AT_DARK_ROD_SKILL, 0, 0, 0, 0, 10); //season3 add-on

	GCMagicAttackNumberSend(lpObj,AT_SKILL_BRAND_OF_SKILL,lpObj->m_Index,1);

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(OBJMAX_RANGE(tObjNum))
			{
				if(lpObj->VpPlayer2[count].type == OBJ_USER)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 5)
					{
						gObjApplyBuffEffectDuration(&gObj[tObjNum], AT_DARK_ROD_SKILL, 0, 0, 0, 0, 10); //season3 add-on
						GCMagicAttackNumberSend(lpObj,AT_SKILL_BRAND_OF_SKILL,tObjNum,1);
					}
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return true;
}

BOOL CObjUseSkill::SkillStun(int aIndex, int aTargetIndex, CMagicInf * lpMagic, BYTE btX, BYTE btY, BYTE btDir, BYTE btTargetPos) //
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	int TargePosx = lpObj->X - (8 - (btTargetPos & 15));
	int TargePosy = lpObj->Y - (8 - ((btTargetPos & 240) >> 4));

	int iangle = this->GetAngle(lpObj->X,lpObj->Y,TargePosx,TargePosy);

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	int tObjNum;
	int count = 0;

	gObjSetKillCount(aIndex,0);

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			if(lpObj->VpPlayer2[count].type == OBJ_USER || lpObj->VpPlayer2[count].type == OBJ_MONSTER)
			{
				tObjNum = lpObj->VpPlayer2[count].number;

				if(OBJMAX_RANGE(tObjNum))
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) <= 4)
					{
						if(SkillElectricSparkHitBox.HitCheck(iangle,lpObj->X,lpObj->Y,gObj[tObjNum].X,gObj[tObjNum].Y))
						{
							gObjApplyBuffEffectDuration(&gObj[tObjNum], AT_STUN, 0, 0, 0, 0, 10); //season3 add-on
							if(!g_ZtLicense.CheckUser(eZtUB::Stone))
							{
								GCMagicAttackNumberSend(lpObj,AT_SKILL_STUN,tObjNum,1);
							}
							gObjSetPosition(tObjNum,gObj[tObjNum].X,gObj[tObjNum].Y);
						}
					}
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return true;
}

BOOL CObjUseSkill::SkillRemoveStun(int aIndex, int aTargetIndex, CMagicInf * lpMagic) //
{

	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	int tObjNum;
	int count = 0;

	gObjSetKillCount(aIndex,0);
	GCMagicAttackNumberSend(lpObj,AT_SKILL_REMOVAL_STUN,lpObj->m_Index,1);

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{

			tObjNum = lpObj->VpPlayer2[count].number;
			if(OBJMAX_RANGE(tObjNum))
			{
				if(lpObj->VpPlayer2[count].type == OBJ_USER)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 6)
					{
						gObjRemoveBuffEffect(&gObj[tObjNum], AT_STUN);
						GCMagicAttackNumberSend(lpObj,AT_SKILL_REMOVAL_STUN,tObjNum,1);
					}
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
return true;
}

//Identical
BOOL CObjUseSkill::SkillAddMana(int aIndex, int aTargetIndex, CMagicInf * lpMagic) //004C67D0
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	int tObjNum;
	int count = 0;
	gObjSetKillCount(aIndex,0);

	int iSwelledMana = 0;

	iSwelledMana = (int)(float(lpObj->MaxMana + lpObj->AddMana) * 50 / 100);

	gObjApplyBuffEffectDuration(lpObj, AT_SWELL_MANA, 5, iSwelledMana, 0, 0, 60); //season3 add-on

	GCManaSend(lpObj->m_Index,(lpObj->MaxMana + lpObj->AddMana),0xFE,0,(lpObj->MaxBP + lpObj->AddBP));

	if( (lpObj->MaxMana + lpObj->AddMana) < lpObj->Mana)
	{
		lpObj->Mana = lpObj->MaxMana + lpObj->AddMana;
		GCManaSend(lpObj->m_Index,lpObj->Mana,0xFF,0,lpObj->BP);
	}

	GCMagicAttackNumberSend(lpObj,AT_SKILL_ADD_MANA,lpObj->m_Index,1);

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(OBJMAX_RANGE(tObjNum) && lpObj->VpPlayer2[count].type == OBJ_USER)
			{
				if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 5)
				{
					if(lpObj->GuildNumber > 0 && gObj[tObjNum].GuildNumber > 0)
					{
						if(lpObj->GuildNumber != gObj[tObjNum].GuildNumber)
						{
							count++;
							continue;
						}

						iSwelledMana = (int)(float(gObj[tObjNum].MaxMana + gObj[tObjNum].AddMana) * 50 / 100);

						gObjApplyBuffEffectDuration(&gObj[tObjNum], AT_SWELL_MANA, 5, iSwelledMana, 0, 0, 60); //season3 add-on

						GCManaSend(tObjNum,(gObj[tObjNum].MaxMana + gObj[tObjNum].AddMana),0xFE,0,(gObj[tObjNum].BP + gObj[tObjNum].MaxBP)); //season3 add-on

						if(gObj[tObjNum].Mana > gObj[tObjNum].MaxMana + gObj[tObjNum].AddMana)
						{
							gObj[tObjNum].Mana = gObj[tObjNum].MaxMana + gObj[tObjNum].AddMana;
							GCManaSend(tObjNum,gObj[tObjNum].Mana,0xFF,0,gObj[tObjNum].BP);
						}

						GCMagicAttackNumberSend(lpObj,AT_SKILL_ADD_MANA,tObjNum,1);
					}
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return true;
}

BOOL CObjUseSkill::SkillCloaking(int aIndex, int aTargetIndex, CMagicInf * lpMagic) //
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	if(OBJMAX_RANGE(aTargetIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	if(lpTargetObj->Type != OBJ_USER)
	{
		LogAddTD("[ANTI-HACK][Cloaking Skill] [%s][%s] Invalid Targeting  TargetType [%d] TargetClass [%d]",
			lpObj->AccountID,lpObj->Name,lpTargetObj->Type,lpTargetObj->Class);
		return false;
	}

	gObjSetKillCount(aIndex,0);

	GCMagicAttackNumberSend(lpObj,AT_SKILL_INVISIBLE,lpObj->m_Index,1);

	gObjApplyBuffEffectDuration(lpTargetObj, AT_INVISIBILITY, 0, 0, 0, 0, 60); //season3 add-on

	GCMagicAttackNumberSend(lpObj,AT_SKILL_INVISIBLE,aTargetIndex,1);
	return true;
}

BOOL CObjUseSkill::RemoveCloakingEffect(int aIndex)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	gObjRemoveBuffEffect(&gObj[aIndex], AT_INVISIBILITY); //season3 add-on
	return true;
}


BOOL CObjUseSkill::SkillRemoveCloaking(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex]; //loc2

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	LPOBJ lpTargetObj = &gObj[aTargetIndex]; //loc3

	if((lpTargetObj->Authority&32) == 32) //Season 2.5 add-on
	{
		if(gObjSearchActiveEffect(lpTargetObj, AT_INVISIBILITY) != FALSE) //season3 add-on
		{
			return false;
		}
	}

	int tObjNum;
	int count = 0;

	gObjSetKillCount(aIndex,0);
	GCMagicAttackNumberSend(lpObj,AT_SKILL_REMOVAL_INVISIBLE,lpObj->m_Index,1);

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(OBJMAX_RANGE(tObjNum) && lpObj->VpPlayer2[count].type == OBJ_USER)
			{
				if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 5)
				{
					gObjRemoveBuffEffect(&gObj[tObjNum], AT_INVISIBILITY); //season3 add-on
					GCMagicAttackNumberSend(lpObj,AT_SKILL_REMOVAL_INVISIBLE,tObjNum,1);
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return true;
}




BOOL CObjUseSkill::SkillRemoveMagic(int aIndex, int aTargetIndex, CMagicInf * lpMagic) //identical gs-cs 56
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	int tObjNum;
	int count = 0;

	gObjSetKillCount(aIndex,0);
	GCMagicAttackNumberSend(lpObj,AT_SKILL_REMOVAL_MAGIC,lpObj->m_Index,1);

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(OBJMAX_RANGE(tObjNum) && lpObj->VpPlayer2[count].type == OBJ_USER)
			{
				if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 5)
				{
					this->RemoveAllCharacterInvalidMagicAndSkillState(&gObj[tObjNum]);
					GCMagicAttackNumberSend(lpObj,AT_SKILL_REMOVAL_MAGIC,tObjNum,1);
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return true;
}

int CObjUseSkill::SkillFenrirAttack(int aIndex,int aTargetIndex,CMagicInf * lpMagic) //identical gs-cs 56
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int HitCount = 0;
	int bAttack;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	if(lpObj->Level < 300)
	{
		return false;
	}

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(gObj[tObjNum].Class < 100 || gObj[tObjNum].Class > 110)
				{
					if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
					{
						EnableAttack = 1;
					}
					else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
					{
						EnableAttack = 1;
					}
//#if(GS_CASTLE==1)
					else if(lpObj->VpPlayer2[count].type != OBJ_NPC && gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
					{
						EnableAttack = 1;
					}
//#endif
					else
					{
						int CallMonIndex = gObj[tObjNum].m_Index;


						if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
						{
							CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
						}

						if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex]) == 1)
						{
							EnableAttack = 1;
						}
					}
				}

				if(EnableAttack != 0)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 6)
					{
						bAttack = 0;

						if(HitCount >= 5)
						{
							bAttack = 0;
						}
						else
						{
							bAttack = 1;
						}

						if(tObjNum == aTargetIndex)
						{
							bAttack = 1;
						}

						if(bAttack != 0)
						{
							gObjAddAttackProcMsgSendDelay(lpObj,53,tObjNum,300,lpMagic->m_Skill,0);
							HitCount++;
						}
					}
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return true;
}

//Identical
int CObjUseSkill::SkillInfinityArrow(int aIndex,int aTargetIndex,CMagicInf * lpMagic) //004C7600
{
	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->Type != OBJ_USER)
	{
		return false;
	}

	if(lpObj->Class != CLASS_ELF || lpObj->ChangeUP == 0)
	{
		return false;
	}

	if(lpObj->m_Index != aTargetIndex)
	{
		return false;
	}

	if(gObjSearchActiveEffect(lpObj, AT_INFINITY_ARROW) == TRUE)
	{
		return false;
	}

	gObjApplyBuffEffectDuration(lpObj, AT_INFINITY_ARROW, 0, 0, 0, 0, g_SkillAdditionInfo.GetInfinityArrowSkillTime());
	GCMagicAttackNumberSend(lpObj,0x4D,lpObj->m_Index,1);
	LogAddTD("[%s][%s] Use Infinity Arrow Skill (Time:%d)(Character Level : %d)(ChangeUp: %d)",	lpObj->AccountID,lpObj->Name,g_SkillAdditionInfo.GetInfinityArrowSkillTime(),lpObj->Level,lpObj->ChangeUP);
	return true;
}
////////////////////////////////////////////////////////////////

BOOL CObjUseSkill::SkillFireScream(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(g_SkillAdditionInfo.GetFireScreamSkill() == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(gObjIsConnected(lpObj->m_Index) == false && gObjIsConnected(lpTargetObj->m_Index) == false)
	{
		return false;
	}

	if(lpObj->Type != OBJ_USER)
	{
		return false;
	}

	if(lpObj->Class != CLASS_DARKLORD)
	{
		return false;
	}

	gObjAttack(lpObj,lpTargetObj,lpMagic,0,0,0,0,0,0);
	return true;
}

BOOL CObjUseSkill::FireScreamExplosionAttack(LPOBJ lpObj, LPOBJ lpTargetObj, int iAttackDamage)
{
	if(gObjIsConnected(lpObj->m_Index) == false && gObjIsConnected(lpTargetObj->m_Index) == false)
	{
		return false;
	}

	if(rand()%10000 > g_SkillAdditionInfo.GetFireScreamExplosionRate())
	{
		return false;
	}

	int iExplosionDamage = iAttackDamage / 10;
	int iTarObjNum;

	if(iExplosionDamage < 1)
	{
		return true;
	}

	int iCount = 0;
	BOOL bEnableAttack;

	while( true )
	{
		if(lpObj->VpPlayer2[iCount].state != 0)
		{
			iTarObjNum = lpObj->VpPlayer2[iCount].number;

			if(iTarObjNum >= 0)
			{
				bEnableAttack = FALSE;

				if(gObj[iTarObjNum].Type == OBJ_MONSTER && gObj[iTarObjNum].m_RecallMon < 0)
				{
					bEnableAttack = TRUE;
				}
				else if(lpTargetObj->Type == OBJ_USER && lpObj->Type == OBJ_USER && gObj[iTarObjNum].Type != OBJ_NPC)
				{
					if(lpTargetObj->m_Index == iTarObjNum)
					{
						bEnableAttack = TRUE;
					}

					if(gObjGetRelationShip(lpObj, &gObj[iTarObjNum]) == 2) //rival??
					{
						bEnableAttack = TRUE;
					}
				}
				else if(lpTargetObj->m_cChaosCastleIndex == gObj[iTarObjNum].m_cChaosCastleIndex && lpTargetObj->m_cChaosCastleIndex != -1)
				{
					bEnableAttack = TRUE;
				}
//#if(GS_CASTLE==1)
				else if(gObj[iTarObjNum].Type != OBJ_NPC && gObj[iTarObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
				{
					if(lpObj->m_btCsJoinSide != gObj[iTarObjNum].m_btCsJoinSide && gObj[iTarObjNum].m_btCsJoinSide > 0)
					{
						bEnableAttack = TRUE;
					}
				}
//#endif
				if(bEnableAttack != FALSE)
				{
					if(lpObj->m_Index != gObj[iTarObjNum].m_Index)
					{
						int iSkillDistance = gObjCalDistance(lpTargetObj,&gObj[iTarObjNum]);

						if(iSkillDistance <= g_SkillAdditionInfo.GetFireScreamExplosionAttackDistance())
						{
							gObjAddMsgSendDelay(lpObj,54,iTarObjNum,100,iExplosionDamage);
							//gObjAttack(lpObj,&gObj[iTarObjNum],lpMagic,1,0,0,0,0,0);
						}
					}
				}
			}
		}

		iCount++;

		if(iCount > MAX_VIEWPORT -1)
		{
			break;
		}
	}
	return true;
}

void CObjUseSkill::SpecificSkillAdditionTreat(LPOBJ lpObj, LPOBJ lpTargetObj, CMagicInf * lpMagic, int iAttackDamage)
{
	int inSkillNum = lpMagic->m_Skill;

	if(inSkillNum == AT_SKILL_FIRESCREAM || 
		(inSkillNum >= 525 && inSkillNum < 530)) //season4 add-on
	{
		gObjUseSkill.FireScreamExplosionAttack(lpObj,lpTargetObj,iAttackDamage);
	}
}

//Identical
int CObjUseSkill::SkillEletrictSurge(int aIndex, int aTargetIndex, CMagicInf* lpMagic) //004C7B90
{
	LPOBJ lpObj = &gObj[aIndex]; //loc2 ebp-8
	int Result = 0; //loc3 ebp-c
	int tObjNum; //loc4 ebp-10

	int fangle = this->GetAngle(lpObj->X,lpObj->Y,gObj[aTargetIndex].X,gObj[aTargetIndex].Y); //loc5 -> ebp-14

	int count = 0; //loc6 ebp-18

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);

	int DuelIndex = lpObj->m_iDuelUser; //loc8 -> ebp-1c
	int EnableAttack; //loc9 -> ebp-20

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(tObjNum == aTargetIndex)
					{
						if(gCheckSkillDistance(aIndex, aTargetIndex, lpMagic->m_Skill) != FALSE)
						{
							gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,700,lpMagic->m_Skill,0);
							Result = 1;
							break;
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
	return Result;
}

//Identical
int CObjUseSkill::SkillEletrictSurgeProc(LPOBJ lpObj, LPOBJ lpTargetObj, int iSkillID, int iAttackDamage, int flag, int Message) //004C7E40
{
	if(gObjIsConnected(lpObj->m_Index) == FALSE && gObjIsConnected(lpTargetObj->m_Index) == FALSE)
	{
		return false;
	}

	if(iAttackDamage <= 0)
	{
		return 0;
	}

	int iDamage = iAttackDamage * Message/ 100; //loc2

	int tObjNum; //loc3
	int count = 0; //loc4

	BOOL bEnableAttack;
	
	while ( true )
	{
		if ( lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if ( tObjNum >= 0 )
			{
				bEnableAttack = FALSE;

				if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					bEnableAttack = TRUE;
				}
				else if(lpTargetObj->m_cChaosCastleIndex != -1 && lpTargetObj->m_cChaosCastleIndex == gObj[tObjNum].m_cChaosCastleIndex)
				{
					bEnableAttack = TRUE;
				}
				else if(lpTargetObj->Type == OBJ_USER && lpObj->Type == OBJ_USER && gObj[tObjNum].Type != OBJ_NPC)
				{
					bEnableAttack = TRUE;
				}

				if(bEnableAttack != FALSE)
				{
					if(lpObj->m_Index != gObj[tObjNum].m_Index)
					{
						int dis = gObjCalDistance(lpTargetObj, &gObj[tObjNum]);

						if(dis <= flag)
						{
							gObjAddMsgSendDelay(lpObj, 58, tObjNum, 300, iDamage);
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}

	return true;
}

int CObjUseSkill::SkillDrainLife(int aIndex, int aTargetIndex, CMagicInf* lpMagic)
{
	if(OBJMAX_RANGE(aTargetIndex) == false) //season4 add-on
	{
		return 0;
	}

	LPOBJ lpObj = &gObj[aIndex]; //loc2 ebp-8
	int Result = 0; //loc3 ebp-c
	int tObjNum; //loc4 ebp-10

	int fangle = this->GetAngle(lpObj->X,lpObj->Y,gObj[aTargetIndex].X,gObj[aTargetIndex].Y); //loc5 -> ebp-14

	int count = 0; //loc6 ebp-18

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);

	int DuelIndex = lpObj->m_iDuelUser; //loc8 -> ebp-1c
	int EnableAttack; //loc9 -> ebp-20

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(tObjNum == aTargetIndex)
					{
						if(gCheckSkillDistance(aIndex, aTargetIndex, lpMagic->m_Skill) != FALSE)
						{
							gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,700,lpMagic->m_Skill,0);
							Result = 1;
							break;
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
	return Result;
}

struct PMSG_CHAIN_LIGHTNING_MAGIC_SEND
{
	struct PBMSG_HEAD2 h;
	BYTE MagicNumberH;
	BYTE MagicNumberL;
	short aIndex;
	BYTE MaxHitUser;
};

#if(!UPDATE_DEDMAKAR)
int CObjUseSkill::SkillChainLightning(int aIndex, int aTargetIndex, CMagicInf* lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false) //season4 add-on
	{
		return 0;
	}

	if(OBJMAX_RANGE(aTargetIndex) == false) //season4 add-on
	{
		return 0;
	}

	LPOBJ lpObj = &gObj[aIndex]; //loc2 ebp-8
	LPOBJ lpTargetObj = &gObj[aTargetIndex]; //loc3 ebp-c

	int local4, tObjNum, count, local7, local8, local9[3], CallMonIndex, local13;

    local4 = 1, count = 0, local9[2] = -1, local8 = -1, local7 = -1;

    BYTE buffer[256];

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);

	local9[1] = lpObj->m_iDuelUser;

	if(gCheckSkillDistance(aIndex, aTargetIndex, lpMagic->m_Skill) == FALSE)
	{
		return FALSE;
	}

	local9[2] = aTargetIndex;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				local9[0] = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0 && 
					(gObj[tObjNum].Class < 100 || gObj[tObjNum].Class > 110)) //Season 4 add-on
				{
					local9[0] = 1;
				}
				else if(tObjNum == aTargetIndex || local9[1] == tObjNum)
				{
					local9[0] = 1;
				}
				else
				{
					CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						local9[0] = 1;
					}
				}

				if(local9[0] != 0) //More than 1 monster
				{
					if (gObj[tObjNum].X >= lpTargetObj->X-1 && gObj[tObjNum].X <= lpTargetObj->X+1 && 
						gObj[tObjNum].Y >= lpTargetObj->Y-1 && gObj[tObjNum].Y <= lpTargetObj->Y+1 && 
						gObj[tObjNum].Type == OBJ_MONSTER)
                    {
                        local8 = tObjNum;

                        if(local7 != -1)
						{
                            break;
						}
                    }
					else if(gObj[tObjNum].X >= lpTargetObj->X-2 && gObj[tObjNum].X <= lpTargetObj->X+2 && 
							gObj[tObjNum].Y >= lpTargetObj->Y-2 && gObj[tObjNum].Y <= lpTargetObj->Y+2 && 
							gObj[tObjNum].Type == OBJ_MONSTER)
                    {
                        local7 = tObjNum;

                        if(local8 != -1)
						{
                            break;
						}
                    }
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}

	if(local7 == -1)
	{
		local7 = local8;
	}

	if(local8 == -1)
	{
		local8 = local9[2];
		local7 = local8;
	}

	local13 = 0;

	PMSG_CHAIN_LIGHTNING_MAGIC_SEND pMsg;

	pMsg.MagicNumberH = SET_NUMBERH(lpMagic->m_Skill);
	pMsg.MagicNumberL = SET_NUMBERL(lpMagic->m_Skill);

	pMsg.aIndex = aIndex;

	pMsg.MaxHitUser = 3;

	local13 += sizeof(pMsg);

	int i;

	for(i = 0; i< 3; i++)
	{
		WORD wUnk = local9[i+2];
        memcpy(&buffer[local13], &wUnk, sizeof(wUnk));
		local13 += 2;
	}

	PHeadSubSetB((LPBYTE)&pMsg,0xBF,0x0A, local13);

	memcpy(buffer, &pMsg, sizeof(pMsg));

    if(lpObj->Type == OBJ_USER)
    {
        ::DataSend(lpObj->m_Index, buffer, pMsg.h.size);
    }

    MsgSendV2(lpObj, buffer, pMsg.h.size);

    for(i = 0;i < 3;i++)
    {
        gObjAddAttackProcMsgSendDelay(lpObj, 50, local9[i+2], i*200+200, lpMagic->m_Skill, i+1);
    }

	return local4;
}

#else

struct PMSG_SKILL_TARGET_COUNT
{
	PBMSG_HEAD2 h;
	BYTE MagicNumberH;
	BYTE MagicNumberL;
	WORD Index;
	BYTE Count;
};

int CObjUseSkill::SkillChainLightning(int aIndex,int aTargetIndex,CMagicInf* lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	int bSuccess = TRUE;
	int tObjNum;
	int count = 0;

	int Target[3];

	Target[0] = -1;
	Target[1] = -1;
	Target[2] = -1;

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);

	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	if( gCheckSkillDistance(aIndex,aTargetIndex,lpMagic->m_Skill) == FALSE )
	{
		return FALSE;
	}

	Target[0] = aTargetIndex;

	while( TRUE )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if( tObjNum >= 0 )
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if( EnableAttack != 0 )
				{
					if( gObj[tObjNum].X >= (lpTargetObj->X -1) &&
						gObj[tObjNum].X <= (lpTargetObj->X +1) &&
						gObj[tObjNum].Y >= (lpTargetObj->Y -1) &&
						gObj[tObjNum].Y <= (lpTargetObj->Y +1) &&
						gObj[tObjNum].Type == OBJ_MONSTER )
					{
						Target[1] = tObjNum;

						if(Target[2] != -1)
							break;
					}
					else if( gObj[tObjNum].X >= (lpTargetObj->X -2) &&
						gObj[tObjNum].X <= (lpTargetObj->X +2) &&
						gObj[tObjNum].Y >= (lpTargetObj->Y -2) &&
						gObj[tObjNum].Y <= (lpTargetObj->Y +2) &&
						gObj[tObjNum].Type == OBJ_MONSTER )
					{
						Target[2] = tObjNum;
	
						if(Target[1] != -1)
							break;
					}
				}
			}
		}

		count++;

		if( count > MAX_VIEWPORT -1)
		{
			break;
		}
	}

	if( Target[2] == -1 )
	{
		Target[2] = Target[1];
	}

	if( Target[1] == -1 )
	{
		Target[1] = Target[0];
		Target[2] = Target[1];
	}

	int lOfs = 0;
	BYTE cBUFF[256];
	PMSG_SKILL_TARGET_COUNT pMsg;

	pMsg.MagicNumberH = SET_NUMBERH(lpMagic->m_Skill);
	pMsg.MagicNumberL = SET_NUMBERL(lpMagic->m_Skill);
	pMsg.Index = aIndex;
	pMsg.Count = 3;

	lOfs += sizeof(pMsg);

	int i;
	for(i = 0; i < 3; i++)
	{
		WORD wIndex = Target[i];
		memcpy(&cBUFF[lOfs],&wIndex,2);
		lOfs+= 2;
	}

	PHeadSubSetB((LPBYTE)&pMsg,0xBF,10,lOfs);
	memcpy(&cBUFF[0],&pMsg,sizeof(pMsg));

	if( lpObj->Type == OBJ_USER )
	{
		DataSend(lpObj->m_Index,(LPBYTE)&cBUFF[0],pMsg.h.size);
	}

	MsgSendV2(lpObj,(LPBYTE)&cBUFF[0],pMsg.h.size);

	for(i = 0; i < 3; i++)
	{
		gObjAddAttackProcMsgSendDelay(lpObj,50,Target[i],200 + 200*i,lpMagic->m_Skill,i+1);
	}

	return bSuccess;
}

#endif

//Identical
int CObjUseSkill::SkillSummonerBook(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, int aTargetIndex) //004C8960
{
	LPOBJ lpObj = &gObj[aIndex]; //loc2

	int result = 0; //loc3
	int count = 0; //loc4

	int tObjNum; //loc5 -> ebp-14

	int DuelIndex = lpObj->m_iDuelUser; //loc6

	int angle = this->GetAngle(lpObj->X,lpObj->Y,x,y); //loc7

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);	

	int iSkillDistance = MagicDamageC.GetSkillDistance(lpMagic->m_Skill); //loc8

	BOOL bEnableAttack;

	if(this->CalDistance(lpObj->X,lpObj->Y,x,y) <= iSkillDistance)
	{
		while( true )
		{
			if(lpObj->VpPlayer2[count].state != 0)
			{
				tObjNum = lpObj->VpPlayer2[count].number;

				if(tObjNum >= 0)
				{
					bEnableAttack = FALSE; //ebp24

					if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
					{
						bEnableAttack = TRUE;
					}
					else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
					{
						bEnableAttack = TRUE;
					}
					else
					{
						int CallMonIndex = gObj[tObjNum].m_Index;

						if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
						{
							CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
						}

						if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==TRUE)
						{
							bEnableAttack = TRUE;
						}
					}

					if(bEnableAttack != FALSE)
					{
						if(gObj[tObjNum].X >= x-2 && gObj[tObjNum].X <= x+2 && gObj[tObjNum].Y >= y-2 && gObj[tObjNum].Y <= y+2)
						{
							gObj[tObjNum].lpAttackObj = lpObj;
							gObjAddAttackProcMsgSendDelay(lpObj, 50, tObjNum, 1000, lpMagic->m_Skill, 0);
							result = 1;
						}
					}
				}
			}

			count++;
			if(count > MAX_VIEWPORT -1)
			{
				break;
			}
		}
	}

	return result;
}

//Identical
int CObjUseSkill::SkillDamageReflection(int aIndex,int aTargetIndex,CMagicInf * lpMagic) //004C8CF0
{
	//LPOBJ lpObj = &gObj[aIndex]; //loc2
	//LPOBJ lpTargetObj = &gObj[aTargetIndex]; //loc3

	//if(lpTargetObj->Type != OBJ_USER || lpObj->Class != CLASS_SUMMONER)
	//{
	//	return FALSE;
	//}

	//int result = 0; //loc4 ebp10

	//int tObjNum; //loc5 -> ebp-14

	//int angle = this->GetAngle(lpObj->X,lpObj->Y,gObj[aTargetIndex].X,gObj[aTargetIndex].Y); //loc6 ebp18

	//int count = 0; //loc7 ebp1c

	//int DuelIndex; //loc8 ebp20

	//BOOL bEnableAttack; //loc9 ebp24

	//GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);

	//DuelIndex = lpObj->m_iDuelUser;
	////嵌臟嵬債惺僚
	////int ExRefStartPower = GetPrivateProfileInt("Summoner","RefStartPower",30,"..\\Data\\ZtData\\Skills.ini");
	////int ExRefEnergy = GetPrivateProfileInt("Summoner","RefEnergy",42,"..\\Data\\ZtData\\Skills.ini");
	////int ExRefMaxPower = GetPrivateProfileInt("Summoner","RefMaxPower",50,"..\\Data\\ZtData\\Skills.ini");
	////int ExRefStartTime = GetPrivateProfileInt("Summoner","RefStartTime",30,"..\\Data\\ZtData\\Skills.ini");
	////int ExRefEneTime = GetPrivateProfileInt("Summoner","RefEneTime",25,"..\\Data\\ZtData\\Skills.ini");

	//if(aIndex == aTargetIndex)
	//{	
	//	/*
	//	int iValue = 30 + (lpObj->Energy / 42);
	//	int iTimer = 30 + (lpObj->Energy / 25);
	//	*/
	//	int iValue = ZtConfig.Skills.ExRefStartPower + (lpObj->Energy / ZtConfig.Skills.ExRefEnergy);
	//	if(iValue > ZtConfig.Skills.ExRefMaxPower)
	//		iValue = ZtConfig.Skills.ExRefMaxPower;
	//	int iTimer = ZtConfig.Skills.ExRefStartTime + (lpObj->Energy / ZtConfig.Skills.ExRefEneTime);

	//	if(gObjCheckBuffEffectValue(lpTargetObj, AT_DAMAGE_REFLECTION, iValue, 0) == 1)
	//	{
	//		GCMagicAttackNumberSend(lpObj,217,lpTargetObj->m_Index,0);
	//		return FALSE;
	//	}

	//	gObjApplyBuffEffectDuration(lpTargetObj, AT_DAMAGE_REFLECTION, 24, iValue, 0, 0, iTimer);
	//	result = 1;
	//}
	//else
	//{
	//	while( true )
	//	{
	//		if(CC_MAP_RANGE(lpObj->MapNumber) != FALSE)
	//		{
	//			break;
	//		}

	//		if(lpObj->VpPlayer2[count].state != 0)
	//		{
	//			tObjNum = lpObj->VpPlayer2[count].number;

	//			if(tObjNum >= 0)
	//			{
	//				bEnableAttack = FALSE; //ebp24

	//				if(lpObj->VpPlayer2[count].type == OBJ_USER)
	//				{
	//					bEnableAttack = TRUE;
	//				}
	//				else if(tObjNum == aTargetIndex || DuelIndex != tObjNum)
	//				{
	//					bEnableAttack = TRUE;
	//				}

	//				if(bEnableAttack != FALSE)
	//				{
	//					if(tObjNum == aTargetIndex)
	//					{
	//						if(gCheckSkillDistance(aIndex, aTargetIndex, lpMagic->m_Skill) != FALSE)
	//						{
	//							lpTargetObj->lpAttackObj = lpObj;

	//								int iValue = ZtConfig.Skills.ExRefStartPower + (lpObj->Energy / ZtConfig.Skills.ExRefEnergy);
	//								if(iValue > ZtConfig.Skills.ExRefMaxPower)
	//									iValue = ZtConfig.Skills.ExRefMaxPower;
	//								int iTimer = ZtConfig.Skills.ExRefStartTime + (lpObj->Energy / ZtConfig.Skills.ExRefEneTime);
	//		
	//							if(gObjCheckBuffEffectValue(lpTargetObj, AT_DAMAGE_REFLECTION, iValue, 0) == 1)
	//							{
	//								GCMagicAttackNumberSend(lpObj,217,lpTargetObj->m_Index,0);
	//								return FALSE;
	//							}

	//							gObjApplyBuffEffectDuration(lpTargetObj, AT_DAMAGE_REFLECTION, 24, iValue, 0, 0, iTimer);
	//							result = 1;
	//							break;
	//						}
	//					}
	//				}
	//			}
	//		}

	//		count++;
	//		
	//		if(count > MAX_VIEWPORT -1)
	//		{
	//			break;
	//		}
	//	}
	//}

	//return result;

	LPOBJ lpObj = &gObj[aIndex]; //loc2
	LPOBJ lpTargetObj = &gObj[aTargetIndex]; //loc3

	if(lpTargetObj->Type != OBJ_USER || lpObj->Class != CLASS_SUMMONER)
	{
		return FALSE;
	}

	int result = 0; //loc4 ebp10

	int tObjNum; //loc5 -> ebp-14

	int angle = this->GetAngle(lpObj->X,lpObj->Y,gObj[aTargetIndex].X,gObj[aTargetIndex].Y); //loc6 ebp18

	int count = 0; //loc7 ebp1c

	int DuelIndex; //loc8 ebp20

	BOOL bEnableAttack; //loc9 ebp24

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);

	DuelIndex = lpObj->m_iDuelUser;

	if(aIndex == aTargetIndex)
	{
		int iValue = g_SkillAdditionInfo.ReflectEffectStart + (lpObj->Energy / g_SkillAdditionInfo.ReflectEffectDiv);

		if( g_SkillAdditionInfo.ReflectEffectMax > 0 && iValue > g_SkillAdditionInfo.ReflectEffectMax )
		{
			iValue = g_SkillAdditionInfo.ReflectEffectMax;
		}

		int iTimer = g_SkillAdditionInfo.ReflectTimeStart + (lpObj->Energy / g_SkillAdditionInfo.ReflectTimeDiv);

		if( g_SkillAdditionInfo.ReflectTimeMax > 0 && iTimer > g_SkillAdditionInfo.ReflectTimeMax )
		{
			iTimer = g_SkillAdditionInfo.ReflectTimeMax;
		}

		if(gObjCheckBuffEffectValue(lpTargetObj, AT_DAMAGE_REFLECTION, iValue, 0) == 1)
		{
			GCMagicAttackNumberSend(lpObj,217,lpTargetObj->m_Index,0);
			return FALSE;
		}

		gObjApplyBuffEffectDuration(lpTargetObj, AT_DAMAGE_REFLECTION, 24, iValue, 0, 0, iTimer);
		result = 1;
	}
	else
	{
		while( true )
		{
			if(CC_MAP_RANGE(lpObj->MapNumber) != FALSE)
			{
				break;
			}

			if(lpObj->VpPlayer2[count].state != 0)
			{
				tObjNum = lpObj->VpPlayer2[count].number;

				if(tObjNum >= 0)
				{
					bEnableAttack = FALSE; //ebp24

					if(lpObj->VpPlayer2[count].type == OBJ_USER)
					{
						bEnableAttack = TRUE;
					}
					else if(tObjNum == aTargetIndex || DuelIndex != tObjNum)
					{
						bEnableAttack = TRUE;
					}

					if(bEnableAttack != FALSE)
					{
						if(tObjNum == aTargetIndex)
						{
							if(gCheckSkillDistance(aIndex, aTargetIndex, lpMagic->m_Skill) != FALSE)
							{
								lpTargetObj->lpAttackObj = lpObj;

								int iValue = g_SkillAdditionInfo.ReflectEffectStart + (lpObj->Energy / g_SkillAdditionInfo.ReflectEffectDiv);

								if( g_SkillAdditionInfo.ReflectEffectMax > 0 && iValue > g_SkillAdditionInfo.ReflectEffectMax )
								{
									iValue = g_SkillAdditionInfo.ReflectEffectMax;
								}

								int iTimer = g_SkillAdditionInfo.ReflectTimeStart + (lpObj->Energy / g_SkillAdditionInfo.ReflectTimeDiv);

								if( g_SkillAdditionInfo.ReflectTimeMax > 0 && iTimer > g_SkillAdditionInfo.ReflectTimeMax )
								{
									iTimer = g_SkillAdditionInfo.ReflectTimeMax;
								}

								if(gObjCheckBuffEffectValue(lpTargetObj, AT_DAMAGE_REFLECTION, iValue, 0) == 1)
								{
									GCMagicAttackNumberSend(lpObj,217,lpTargetObj->m_Index,0);
									return FALSE;
								}

								gObjApplyBuffEffectDuration(lpTargetObj, AT_DAMAGE_REFLECTION, 24, iValue, 0, 0, iTimer);
								result = 1;
								break;
							}
						}
					}
				}
			}

			count++;

			if(count > MAX_VIEWPORT -1)
			{
				break;
			}
		}
	}

	return result;
}

int CObjUseSkill::SkillSleep(int aIndex,int aTargetIndex,CMagicInf * lpMagic) //004C9100
{
	LPOBJ lpObj = &gObj[aIndex]; //loc2

	int result = 0; //loc3 ebpC

	int tObjNum; //loc4 -> ebp-10

	int angle = this->GetAngle(lpObj->X,lpObj->Y,gObj[aTargetIndex].X,gObj[aTargetIndex].Y); //loc5 ebp14

	int count = 0; //loc6 ebp18

	//int DuelIndex; //loc7 ebp1c

	BOOL bEnableAttack; //loc8 ebp20

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);

	//DuelIndex = lpObj->m_iDuelUser;

	int DuelRoom = lpObj->m_iDuelRoom;

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				bEnableAttack = FALSE; //ebp20

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					bEnableAttack = TRUE;
				}
				else if(DuelRoom >= 0) //fix
				{
					bEnableAttack = TRUE;
				}
				else if (CC_MAP_RANGE(lpObj->MapNumber) != FALSE || IT_MAP_RANGE(lpObj->MapNumber) != FALSE)
				{
					bEnableAttack = TRUE;
				}
//#if(GS_CASTLE==1)
				else if(lpObj->VpPlayer2[count].type != OBJ_NPC && 
					gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && 
					g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
				{
					bEnableAttack = TRUE;
				}
//#endif
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==TRUE)
					{
						bEnableAttack = TRUE;
					}
				}

				if(bEnableAttack != FALSE)
				{
					if(tObjNum == aTargetIndex)
					{
						if(gCheckSkillDistance(aIndex, aTargetIndex, lpMagic->m_Skill) != FALSE)
						{
							gObjAttack(lpObj,&gObj[aTargetIndex],lpMagic,1,0,0,0,0,0);
							result = 1;
							break;
						}
					}
				}
			}
		}

		count++;
			
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}

	return result;
}

int CObjUseSkill::SkillBlind(int aIndex,int aTargetIndex,CMagicInf * lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex]; //loc2

	int result = 0; //loc3 ebpC

	int tObjNum; //loc4 -> ebp-10

	int angle = this->GetAngle(lpObj->X,lpObj->Y,gObj[aTargetIndex].X,gObj[aTargetIndex].Y); //loc5 ebp14

	int count = 0; //loc6 ebp18

	int DuelIndex; //loc7 ebp1c

	int loc8; //ebp20
	int loc9; //ebp24

	BOOL bEnableAttack; //loc10 ebp28

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);

	DuelIndex = lpObj->m_iDuelUser;

	loc8 = 0;

	if(gObj[aTargetIndex].Type == OBJ_MONSTER)
	{
		loc8 = lpObj->m_AttackRating * (lpObj->Energy / 50 + 20) / 100;
	}
	else
	{
		loc9 = lpObj->Level*3 + (lpObj->Dexterity * 35)/10;
		loc8 = loc9 * (lpObj->Energy / 50 + 20) / 100;
	}

	if(loc8 < rand()%100)
	{
		GCDamageSend(lpObj->m_Index, gObj[aTargetIndex].m_Index, 0, 0, 0, 0);
		return FALSE;
	}
	else
	{
		while( true )
		{
			if(lpObj->VpPlayer2[count].state != 0)
			{
				tObjNum = lpObj->VpPlayer2[count].number;

				if(tObjNum >= 0)
				{
					bEnableAttack = FALSE;

					if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
					{
						bEnableAttack = TRUE;
					}
					else if(tObjNum == aTargetIndex && DuelIndex == tObjNum)
					{
						bEnableAttack = TRUE;
					}
					else if (CC_MAP_RANGE(lpObj->MapNumber) != FALSE || IT_MAP_RANGE(lpObj->MapNumber) != FALSE)
					{
						bEnableAttack = TRUE;
					}
//#if(GS_CASTLE==1)
					else if(lpObj->VpPlayer2[count].type != OBJ_NPC && 
						gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && 
						g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
					{
						bEnableAttack = TRUE;
					}
//#endif
					else
					{
						int CallMonIndex = gObj[tObjNum].m_Index;

						if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
						{
							CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
						}

						if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==TRUE)
						{
							bEnableAttack = TRUE;
						}
					}

					if(bEnableAttack != FALSE)
					{
						if(tObjNum == aTargetIndex)
						{
							if(gCheckSkillDistance(aIndex, aTargetIndex, lpMagic->m_Skill) != FALSE)
							{
								int iValue1 = 20 + lpObj->Energy / 50;
								int iValue2 = 0;

								if(gObj[aTargetIndex].Type == OBJ_MONSTER)
								{
									iValue2 = 9 + lpObj->Energy / 70 - gObj[aTargetIndex].Level / 15;
								}
								else if(gObj[aTargetIndex].Type == OBJ_USER)
								{
									iValue2 = ( ( lpObj->Energy / 210 ) + ( ( gObj[aTargetIndex].Level - gObj[aTargetIndex].Level ) / 100 ) + 3 );
								}

								if(gObjCheckBuffEffectValue(&gObj[aTargetIndex], AT_BLIND, iValue1, 0) == 1)
								{
									GCMagicAttackNumberSend(lpObj,220,aTargetIndex,0);
									return FALSE;
								}

								gObjApplyBuffEffectDuration(&gObj[aTargetIndex], AT_BLIND, 26, iValue1, 0, 0, iValue2);
								result = 1;
								break;
							}
						}
					}
				}
			}

			count++;
				
			if(count > MAX_VIEWPORT -1)
			{
				break;
			}
		}
	}
	return result;
}

int CObjUseSkill::SkillWeakness(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, int aTargetIndex)
{
	LPOBJ lpObj = &gObj[aIndex]; //loc2

	int result = 0; //loc3 ebpC

	int tObjNum; //loc4 -> ebp-10

	int count = 0; //loc5 ebp14

	int maxhit = 0; //loc6 ebp18

	//int DuelIndex = lpObj->m_iDuelUser; //loc7 ebp1c

	int DuelRoom = lpObj->m_iDuelRoom;

	BOOL bEnableAttack; //loc8 ebp20

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				bEnableAttack = FALSE;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					bEnableAttack = TRUE;
				}
				else if(DuelRoom >= 0)
				{
					bEnableAttack = TRUE;
				}
				else if (CC_MAP_RANGE(lpObj->MapNumber) != FALSE || IT_MAP_RANGE(lpObj->MapNumber) != FALSE)
				{
					bEnableAttack = TRUE;
				}
//#if(GS_CASTLE==1)
				else if(lpObj->VpPlayer2[count].type != OBJ_NPC && 
					gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && 
					g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
				{
					bEnableAttack = TRUE;
				}
//#endif
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==TRUE)
					{
						bEnableAttack = TRUE;
					}
				}

				if(bEnableAttack != FALSE)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 5)
					{
						gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,700,lpMagic->m_Skill,0);
						maxhit++;

						if(maxhit >= 5)
						{
							break;
						}
					}
				}
			}
		}

		count++;
			
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}

	return result;
}

int CObjUseSkill::SkillInnovation(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, int aTargetIndex)
{
	LPOBJ lpObj = &gObj[aIndex]; //loc2

	int result = 0; //loc3 ebpC

	int tObjNum; //loc4 -> ebp-10

	int count = 0; //loc5 ebp14

	int maxhit = 0; //loc6 ebp18

	//int DuelIndex = lpObj->m_iDuelUser; //loc7 ebp1c

	int DuelRoom = lpObj->m_iDuelRoom;

	BOOL bEnableAttack; //loc8 ebp20

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				bEnableAttack = FALSE;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					bEnableAttack = TRUE;
				}
				else if(DuelRoom >= 0) //fix
				{
					bEnableAttack = TRUE;
				}
				else if (CC_MAP_RANGE(lpObj->MapNumber) != FALSE || IT_MAP_RANGE(lpObj->MapNumber) != FALSE)
				{
					bEnableAttack = TRUE;
				}
//#if(GS_CASTLE==1)
				else if(lpObj->VpPlayer2[count].type != OBJ_NPC && 
					gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && 
					g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
				{
					bEnableAttack = TRUE;
				}
//#endif
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==TRUE)
					{
						bEnableAttack = TRUE;
					}
				}

				if(bEnableAttack != FALSE)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 5)
					{
						gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,700,lpMagic->m_Skill,0);
						maxhit++;

						if(maxhit >= 5)
						{
							break;
						}
					}
				}
			}
		}

		count++;
			
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}

	return result;
}

//Season4 Skills #START!
int CObjUseSkill::SkillLightningShock(int aIndex, int aTargetIndex, CMagicInf* lpMagic) //004F7090
{
	LPOBJ lpObj = &gObj[aIndex]; //loc2
	int loc3 = 0; //loc3
	BOOL bAttack = FALSE; //loc4
	int tObjNum; //loc5
	int count = 0; //loc6
	int loc7 = 0; //loc7
	int loc8 = 7; //loc8
	int maxhit = 0; //loc9

	BOOL bEnableAttack; //loc10

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);

	int loc11 = 1;

	int DuelIndex = lpObj->m_iDuelUser; //loc12

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				bEnableAttack = FALSE;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					bEnableAttack = TRUE;
				}
				else if (CC_MAP_RANGE(lpObj->MapNumber) != FALSE || IT_MAP_RANGE(lpObj->MapNumber) != FALSE)
				{
					bEnableAttack = TRUE;
				}
				else if(tObjNum == aTargetIndex && loc11 == 1 || DuelIndex == tObjNum )
				{
					bEnableAttack = TRUE;
				}
//#if(GS_CASTLE==1)
				else if(lpObj->VpPlayer2[count].type != OBJ_NPC && 
					gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && 
					g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
				{
					bEnableAttack = 1;
				}
//#endif
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==TRUE)
					{
						bEnableAttack = TRUE;
					}
				}

				if(bEnableAttack != FALSE)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 7)
					{
						maxhit++;

						if(maxhit > 5)
						{
							if(rand()%2 != 0)
							{
								bAttack = TRUE;
							}
						}
						else
						{
							bAttack = TRUE;
						}

						if(maxhit > 12)
						{
							bAttack = FALSE;
						}

						if(bAttack == TRUE)
						{
							gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,250,lpMagic->m_Skill,0);
						}						
					}
				}
			}
		}

		count++;
			
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}

	return true;
}

int CObjUseSkill::SkillBerserker(int aIndex, CMagicInf* lpMagic) //004F74C0
{
	//if(OBJMAX_RANGE(aIndex) == false)
	//{
	//	return false;
	//}

	//LPOBJ lpObj = &gObj[aIndex];


	////int ExBerserkerStartTime = GetPrivateProfileInt("Summoner","BerserkerStartTime",30,"..\\Data\\ZtData\\Skills.ini");
	////int ExBerserkerEnergyTime = GetPrivateProfileInt("Summoner","BerserkerEnergyTime",20,"..\\Data\\ZtData\\Skills.ini");
	////int ExBerserkerMaxTime = GetPrivateProfileInt("Summoner","BerserkerMaxTime",0,"..\\Data\\ZtData\\Skills.ini");

	////int ExBerserkerEneIncMana = GetPrivateProfileInt("Summoner","BerserkerEneIncMana",30,"..\\Data\\ZtData\\Skills.ini");
	////int ExBerserkerEneDecLife = GetPrivateProfileInt("Summoner","BerserkerEneDecLife",60,"..\\Data\\ZtData\\Skills.ini");
	///*
	//int iDuration = lpObj->Energy / 20 + 30;

	//int iIncMana = lpObj->Energy / 30;
	//int iDecLife = lpObj->Energy / 60;
	//*/
	//int iDuration = lpObj->Energy / ZtConfig.Skills.ExBerserkerEnergyTime + ZtConfig.Skills.ExBerserkerStartTime;
	//int iIncMana  = lpObj->Energy / ZtConfig.Skills.ExBerserkerEneIncMana;
	//int iDecLife  = lpObj->Energy / ZtConfig.Skills.ExBerserkerEneDecLife;
	//
	//if(ZtConfig.Skills.ExBerserkerMaxTime != 0)
	//{
	//	if(iDuration > ZtConfig.Skills.ExBerserkerMaxTime)
	//		iDuration = ZtConfig.Skills.ExBerserkerMaxTime;
	//}

	//gObjApplyBuffEffectDuration(lpObj, AT_BERSERKER, 31, iIncMana, 32, iDecLife, iDuration);

	//GCMagicAttackNumberSend(lpObj,218,lpObj->m_Index,1);
	//return true;

	if(OBJMAX_RANGE(aIndex) == false)
	{
		return FALSE;
	}

	LPOBJ lpObj = &gObj[aIndex];

	int iDuration	= lpObj->Energy / g_SkillAdditionInfo.BerserkerTimeDiv + g_SkillAdditionInfo.BerserkerTimeStart;

	if( g_SkillAdditionInfo.BerserkerTimeMax > 0 && iDuration > g_SkillAdditionInfo.BerserkerTimeMax )
	{
		iDuration = g_SkillAdditionInfo.BerserkerTimeMax;
	}
	
#ifdef FIX_BERSERK_SUM
	int iIncMana;
	if (!ZtConfig.Character.BerserkAddMana)
	{
		iIncMana	= 0;
	}
	else
	{
		iIncMana	= lpObj->Energy / g_SkillAdditionInfo.BerserkerManaIncDiv;
	}
#else
	int iIncMana	= lpObj->Energy / g_SkillAdditionInfo.BerserkerManaIncDiv;
#endif
	int iDecLife	= lpObj->Energy / g_SkillAdditionInfo.BerserkerLifeDecDiv;

	gObjApplyBuffEffectDuration(lpObj, AT_BERSERKER, 31, iIncMana, 32, iDecLife, iDuration); // ->
	GCMagicAttackNumberSend(lpObj,218,lpObj->m_Index,1);

	return TRUE;
}

int CObjUseSkill::SkillPollutionStart(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, int aTargetIndex, int Flag) //004F75D0
{
	LPOBJ lpObj = &gObj[aIndex]; //loc2

	int SkillResult = 0; //loc3

	if(Flag == 59)
	{
		GCMagicAttackNumberSend(lpObj,(WORD)lpMagic->m_Skill,aTargetIndex,1);
	}

	SkillResult = this->SkillWideAttackMultiTarget(aIndex, lpMagic, x, y, aTargetIndex, 3, 1, 0);

	if(Flag >= 59 && Flag < 64)
	{
		gObjAddMsgSendDelay(lpObj, 59, aTargetIndex, 1000, (MAKE_NUMBERDW(Flag, MAKE_NUMBERW(y,x))));
	}

	return SkillResult;
}

//Summoner Pollution + Gigantic Storm + Strike of Destruction :)
int CObjUseSkill::SkillWideAttackMultiTarget(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, int aTargetIndex, int Dis, int Flag, int Delay) //004F7700
{
	LPOBJ lpObj = &gObj[aIndex]; //loc2

	int SkillResult = 0; //loc3

	int count = 0; //loc4
	int tObjNum; //loc5

	int DuelIndex = lpObj->m_iDuelUser; //loc6

	int hitcount = 0; //loc7

	BOOL bAttack = FALSE; //loc8

	int maxhit = 4; //loc9

	int loc10 = 8; //loc10

	if(lpMagic->m_Skill == 237)
	{
		maxhit = 8;
		loc10 = 12;
	}

	int iSkillDistance = MagicDamageC.GetSkillDistance(lpMagic->m_Skill); //loc11

	BOOL bEnableAttack; //loc12

	if(this->CalDistance(lpObj->X,lpObj->Y,x,y) <= iSkillDistance)
	{
		while( true )
		{
			if(lpObj->VpPlayer2[count].state != 0)
			{
				tObjNum = lpObj->VpPlayer2[count].number;

				if(tObjNum >= 0)
				{
					bEnableAttack = FALSE;

					if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
					{
						bEnableAttack = TRUE;
					}
					else if(tObjNum == aTargetIndex && Flag == 1 || DuelIndex == tObjNum)
					{
						bEnableAttack = TRUE;
					}
//#if(GS_CASTLE==1)
					else if(lpObj->VpPlayer2[count].type != OBJ_NPC && 
						gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && 
						g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
					{
						bEnableAttack = TRUE;
					}
//#endif
					else
					{
						int CallMonIndex = gObj[tObjNum].m_Index;

						if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
						{
							CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
						}

						if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==TRUE)
						{
							bEnableAttack = TRUE;
						}
					}

					if(bEnableAttack != FALSE)
					{
						if(gObj[tObjNum].X >= x-Dis && gObj[tObjNum].X <= x+Dis && gObj[tObjNum].Y >= y-Dis && gObj[tObjNum].Y <= y+Dis)
						{
							gObj[tObjNum].lpAttackObj = lpObj;
							hitcount++;

							if(hitcount > maxhit)
							{
								if(rand()%2 != 0)
								{
									bAttack = TRUE;
								}
							}
							else
							{
								bAttack = TRUE;
							}

							if(hitcount > loc10)
							{
								bAttack = FALSE;
							}

							if(bAttack == TRUE)
							{
								if(Delay == FALSE)
								{
									gObjAttack(lpObj,&gObj[tObjNum],lpMagic,1,0,0,0,0,0);
								}
								else
								{
									gObjAddAttackProcMsgSendDelay(lpObj, 50, tObjNum, Delay, lpMagic->m_Skill, 0);
								}
							}
							
							SkillResult = 1;
						}
					}
				}
			}

			count++;

			if(count > MAX_VIEWPORT -1)
			{
				break;
			}
		}
	}

	return SkillResult;
}

int CObjUseSkill::SkillStrikeOfDestructionStart(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, int aTargetIndex) //004F7BE0
{
	int SkillResult = 0; //loc2

	SkillResult = this->SkillWideAttackMultiTarget(aIndex, lpMagic, x, y, aTargetIndex, 3, 1, 500);

	return SkillResult;
}

void CObjUseSkill::SkillFrustrum3(int aIndex, BYTE fangle, float tx, float ty, float arg5, float arg6) //004F7C40
{
	LPOBJ lpObj = &gObj[aIndex];

	vec3_t p[4];
	Vector(-tx , ty, 0.f,p[0]);
	Vector( tx , ty, 0.f,p[1]);
	Vector( arg5, arg6, 0.f,p[2]);
	Vector(-arg5, arg6, 0.f,p[3]);

	//vec3_t Angle;
	vec3_t Angle;

	//Vector(0.f,0.f,fangle*360/(BYTE)255,Angle);
	Vector(0.f,0.f,(float)((BYTE)fangle*360/(BYTE)255),Angle);

	float Matrix[3][4];
	vec3_t vFrustrum[4];
	
	AngleMatrix(Angle,Matrix);

	for(int i = 0; i < 4; i++)
	{
		VectorRotate(p[i],Matrix,vFrustrum[i]);

		lpObj->fSkillFrustrumX[i] = (int)vFrustrum[i][0] + lpObj->X;
		lpObj->fSkillFrustrumY[i] = (int)vFrustrum[i][1] + lpObj->Y;
	}
}

void CObjUseSkill::SkillFlameStrike(int aIndex, CMagicInf* lpMagic, BYTE TargetPos, int aTargetIndex) //004F7E20
{
	LPOBJ lpObj = &gObj[aIndex]; //loc2
	int skillsuccess = 1;

	this->SkillFrustrum3(aIndex, TargetPos, 2.0f, 4.0f, 5.0f, 0);
	
	int tObjNum; //loc4
	int count = 0; //loc5
	int HitCount = 0; //loc6

	BOOL bAttack; //loc7

	int DuelIndex = lpObj->m_iDuelUser; //loc8

	BOOL bEnableAttack; //loc9

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				bEnableAttack = FALSE;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					bEnableAttack = TRUE;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum )
				{
					bEnableAttack = TRUE;
				}
//#if(GS_CASTLE==1)
				else if(lpObj->VpPlayer2[count].type != OBJ_NPC && 
					gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && 
					g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
				{
					bEnableAttack = TRUE;
				}
//#endif
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==TRUE)
					{
						bEnableAttack = TRUE;
					}
				}

				if(bEnableAttack != FALSE)
				{
					if(SkillTestFrustrum(gObj[tObjNum].X,gObj[tObjNum].Y,aIndex))
					{
						bAttack = FALSE;

						if(HitCount >= 8)
						{
							if(rand()%2)
							{
								bAttack = TRUE;
							}
						}
						else
						{
							bAttack = TRUE;
						}

						if(bAttack != FALSE)
						{
							gObjAttack(lpObj,&gObj[tObjNum],lpMagic,1,0,0,0,0,0);
							gObjAttack(lpObj,&gObj[tObjNum],lpMagic,1,0,0,0,0,0);
						}

						HitCount++;
					}
				}
			}
		}

		count++;
			
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
}

int CObjUseSkill::SkillGiganticStormStart(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, int aTargetIndex) //004F81D0
{
	int SkillResult = 0; //loc2

	SkillResult = this->SkillWideAttackMultiTarget(aIndex, lpMagic, x, y, aTargetIndex, 6, 1, 400);

	return SkillResult;
}

void CObjUseSkill::SkillMultiShot(int aIndex, CMagicInf* lpMagic, BYTE TargetPos, int aTargetIndex) //004F8230
{
	LPOBJ lpObj = &gObj[aIndex]; //loc2

	this->SkillFrustrum3(aIndex, TargetPos, 6.0f, 7.0f, 1.0f, 0); //S4 New Skill Frustrum OK :)

	vec3_t Angle; //Good
	Vector(0.f, 6.0f, 0.f, Angle); //3,4,5 Good

	vec3_t p[4]; //Good size OK

	Vector(0.f, 0.f, 40.0f, p[0]); //Good
	Vector(0.f, 0.f, 20.0f, p[1]); //Good
	Vector(0.f, 0.f, 340.0f, p[2]); //Good
	Vector(0.f, 0.f, 320.0f, p[3]); //Good

	float Matrix[3][4]; //Good

	vec3_t vFrustrum[5]; //Good

	AngleMatrix(p[0],Matrix); //Good
	VectorRotate(Angle,Matrix,vFrustrum[0]); //loc44 Good
	
	AngleMatrix(p[1],Matrix); //Good
	VectorRotate(Angle,Matrix,vFrustrum[1]); //loc41 Good

	Vector(0.f, 6.0f, 0.f, vFrustrum[2]);//36,37,38

	AngleMatrix(p[2],Matrix); //Good
	VectorRotate(Angle,Matrix,vFrustrum[3]); //loc35 Good

	AngleMatrix(p[3],Matrix); //Good
	VectorRotate(Angle,Matrix,vFrustrum[4]); //loc32 Good

	Vector(0.f, 0.f, (float)(TargetPos*360/(BYTE)255), p[0]); //15, 16, 17 Good

	AngleMatrix((float*)p,Matrix); //Good

///////////////////////////////////////////////////////////////////////////////////////////////////
	int Value1[5];
	int Value2[5];

	vec3_t vFrustrum2[5];

	for(int i = 0; i < 5; i++) //loc70 Good
	{
		VectorRotate(vFrustrum[i],Matrix,vFrustrum2[i]);

		Value1[i] = (int)vFrustrum2[i][0] + lpObj->X;
		Value2[i] = (int)vFrustrum2[i][1] + lpObj->Y;
	}
///////////////////////////////////////////////////////////////////////////////////////////////////

	int tObjNum; //loc71
	int count = 0; //loc72
	int loc73 = 0; //loc73
	int DuelIndex = lpObj->m_iDuelUser; //loc74
	BOOL bEnableAttack; //loc75

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				bEnableAttack = FALSE;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					bEnableAttack = TRUE;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum )
				{
					bEnableAttack = TRUE;
				}
//#if(GS_CASTLE==1)
				else if(lpObj->VpPlayer2[count].type != OBJ_NPC && 
					gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && 
					g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
				{
					bEnableAttack = TRUE;
				}
//#endif
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==TRUE)
					{
						bEnableAttack = TRUE;
					}
				}

				if(bEnableAttack != FALSE)
				{
					int Value3[5];

					for(int j = 0; j < 5; j++)
					{
						Value3[j] = (((int)Value1[j] - lpObj->X) * (gObj[tObjNum].Y - lpObj->Y)) - (((int)Value2[j] - lpObj->Y) * (gObj[tObjNum].X - lpObj->X));
						
						if(SkillTestFrustrum(gObj[tObjNum].X,gObj[tObjNum].Y,aIndex))
						{
							if(Value3[j] > -5 && Value3[j] < 5)
							{
								gObjAttack(lpObj,&gObj[tObjNum],lpMagic,1,0,0,0,0,0);
							}
						}
					}
				}
			}
		}

		count++;
			
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
}

void CObjUseSkill::SkillSDRecovery(int aIndex, int aTargetIndex, CMagicInf* lpMagic) //004F8980
{
	int skillSuccess = true;
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(lpTargetObj->Type != OBJ_USER && lpTargetObj->m_RecallMon == -1)
	{
		return;
	}

	if(lpObj->Class != CLASS_ELF)
	{
		return;
	}

	if(CC_MAP_RANGE(lpObj->MapNumber) != FALSE && lpObj->m_Index != lpTargetObj->m_Index)
	{
		return;
	}

	if(gObjDuelCheck(lpTargetObj) != 0) //nice trick
	{
		lpTargetObj = lpObj;
	}

	if(lpTargetObj->iShield >= (lpTargetObj->iMaxShield + lpTargetObj->iAddShield + lpTargetObj->m_MPSkillOpt.MpsMaxSD))
	{
		GCMagicAttackNumberSend(lpObj,234,lpTargetObj->m_Index,0);
		return;
	}

	lpTargetObj->iShield += (lpObj->Energy/4) + lpObj->Level;

	if(lpTargetObj->iShield > (lpTargetObj->iMaxShield + lpTargetObj->iAddShield + lpTargetObj->m_MPSkillOpt.MpsMaxSD))
	{
		lpTargetObj->iShield = (lpTargetObj->iMaxShield + lpTargetObj->iAddShield + lpTargetObj->m_MPSkillOpt.MpsMaxSD);
	}

	if(lpTargetObj->Type == OBJ_USER)
	{
		GCReFillSend(lpTargetObj->m_Index, lpTargetObj->Life, 0xFF, 0, lpTargetObj->iShield);
		GCMagicAttackNumberSend(lpObj,234,lpTargetObj->m_Index,(BYTE)skillSuccess);

		for(int n = 0; n < MAX_VIEWPORT; n++)
		{
			if(lpObj->VpPlayer2[n].type == OBJ_MONSTER && lpObj->VpPlayer2[n].state != 0)
			{
				LPOBJ lpMonster = &gObj[lpObj->VpPlayer2[n].number];
				if(lpMonster->m_iCurrentAI != 0)
				{
					lpMonster->m_Agro.IncAgro(lpObj->m_Index,int(lpObj->Energy/5)/40);
				}
			}
		}
	}
}

int CObjUseSkill::SkillExpansionWizardry(int aIndex, int aTargetIndex, CMagicInf *lpMagic) //004F8CF0
{
	//LPOBJ lpObj = &gObj[aIndex];

	//if(lpObj->Type != OBJ_USER)
	//{
	//	return false;
	//}

	//if(lpObj->Class != CLASS_WIZARD)
	//{
	//	return false;
	//}

	//if(lpObj->m_Index != aTargetIndex)
	//{
	//	return false;
	//}

	//if(gObjSearchActiveEffect(lpObj, AT_EXPANSION_WIZARDRY) == 1)
	//{
	//	return false;
	//}
	////ExTest
	////int ExWizardryPowerMax = GetPrivateProfileInt("DarkWizard","WizardryPowerMax",20,"..\\Data\\ZtData\\Skills.ini");
	//int iWizardryDamage = (int)((float)(lpObj->m_MagicDamageMax * ZtConfig.Skills.ExWizardryPowerMax) / 100 );
	////int iWizardryDamage = (float)(lpObj->Energy/9) * (float)0.f; m_MagicDamageMax

	//gObjApplyBuffEffectDuration(lpObj,AT_EXPANSION_WIZARDRY,ADD_OPTION_MAGICDAMAGEMIN,iWizardryDamage,ADD_OPTION_MAGICDAMAGEMAX,iWizardryDamage,1800);
	////gObjApplyBuffEffectDuration(lpObj, AT_EXPANSION_WIZARDRY, 33, iWizardryDamage, 0, 0, 1800);

	//GCMagicAttackNumberSend(lpObj,233,lpObj->m_Index,1);
	//return true;

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->Type != OBJ_USER)
	{
		return FALSE;
	}

	if(lpObj->Class != CLASS_WIZARD)
	{
		return FALSE;
	}

	if(lpObj->m_Index != aTargetIndex)
	{
		return FALSE;
	}

	if(		gObjSearchActiveEffect(lpObj, AT_EXPANSION_WIZARDRY) 
		||	gObjSearchActiveEffect(lpObj, 138) 
		||	gObjSearchActiveEffect(lpObj, 139) )
	{
		return FALSE;
	}

	int iWizardryDamage = (float)(lpObj->Energy / g_SkillAdditionInfo.WizardryEnchantDamageDiv) * (float)g_SkillAdditionInfo.WizardryEnchantDamageFact;

	if( g_SkillAdditionInfo.WizardryEnchantDamageMax > 0 && iWizardryDamage > g_SkillAdditionInfo.WizardryEnchantDamageMax )
	{
		iWizardryDamage = g_SkillAdditionInfo.WizardryEnchantDamageMax;
	}

	gObjApplyBuffEffectDuration(lpObj, AT_EXPANSION_WIZARDRY, 33, iWizardryDamage, 0, 0, g_SkillAdditionInfo.WizardryEnchantTime);
	GCMagicAttackNumberSend(lpObj,233,lpObj->m_Index,1);
	return TRUE;
}

void CObjUseSkill::SkillChaoticDiseier(int aIndex, CMagicInf *lpMagic, BYTE TargetPos, int aTargetIndex) //004F8E10
{
	LPOBJ lpObj = &gObj[aIndex];

	int skillSuccess = true;
	
	this->SkillFrustrum3(aIndex, TargetPos, 1.5f, 6.0f, 1.5f, 0); //S4 New Skill Frustrum OK :)

	int tObjNum; //loc4
	int count = 0; //loc5
	int HitCount = 0; //loc6

	BOOL bAttack; //loc7

	int DuelIndex = lpObj->m_iDuelUser; //loc8

	BOOL bEnableAttack; //loc9

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				bEnableAttack = FALSE;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					bEnableAttack = TRUE;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum )
				{
					bEnableAttack = TRUE;
				}
//#if(GS_CASTLE==1)
				else if(lpObj->VpPlayer2[count].type != OBJ_NPC && 
					gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && 
					g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
				{
					bEnableAttack = TRUE;
				}
//#endif
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==TRUE)
					{
						bEnableAttack = TRUE;
					}
				}

				if(bEnableAttack != FALSE)
				{
					if(SkillTestFrustrum(gObj[tObjNum].X,gObj[tObjNum].Y,aIndex))
					{
						bAttack = FALSE;

						if(HitCount >= 8)
						{
							if(rand()%2)
							{
								bAttack = TRUE;
							}
						}
						else
						{
							bAttack = TRUE;
						}

						if(bAttack != FALSE)
						{
#if(EVOMU_DLSKILLCHANGE==TRUE)
							if(	g_ZtLicense.CheckUser(eZtUB::Gredy)			|| 
								g_ZtLicense.CheckUser(eZtUB::GredyLocal)	|| 
								g_ZtLicense.CheckUser(eZtUB::Gredy2)		||
								g_ZtLicense.CheckUser(eZtUB::SILVER1)		||
								g_ZtLicense.CheckUser(eZtUB::SILVER2)		||
								g_ZtLicense.CheckUser(eZtUB::SILVER_Local)	||
								g_ZtLicense.CheckUser(eZtUB::MuPrime) )
							{
								gObjAttack(lpObj,&gObj[tObjNum],lpMagic,1,0,0,0,0,0);
							}
							else
							{
								gObjAddAttackProcMsgSendDelay(lpObj, 50, tObjNum, 200, lpMagic->m_Skill, 0);
							}
#else
							gObjAddAttackProcMsgSendDelay(lpObj, 50, tObjNum, 200, lpMagic->m_Skill, 0);
#endif
						}

						if(OBJMAX_RANGE(aTargetIndex) != false && tObjNum == aTargetIndex)
						{
#if(EVOMU_DLSKILLCHANGE==TRUE)
							if(	g_ZtLicense.CheckUser(eZtUB::Gredy)			|| 
								g_ZtLicense.CheckUser(eZtUB::GredyLocal)	|| 
								g_ZtLicense.CheckUser(eZtUB::Gredy2)		||
								g_ZtLicense.CheckUser(eZtUB::SILVER1)		||
								g_ZtLicense.CheckUser(eZtUB::SILVER2)		||
								g_ZtLicense.CheckUser(eZtUB::SILVER_Local)	||
								g_ZtLicense.CheckUser(eZtUB::MuPrime) )
							{
								gObjAttack(lpObj,&gObj[tObjNum],lpMagic,1,0,0,0,0,0);
							}
							else
							{
								gObjAddAttackProcMsgSendDelay(lpObj, 50, tObjNum, 200, lpMagic->m_Skill, 0);
							}
#else
							gObjAddAttackProcMsgSendDelay(lpObj, 50, tObjNum, 300, lpMagic->m_Skill, 0);
							LogAddTD("2HIT!!!!!! SUCCESS aTargetIndex : %d , tObjNum : %d", aTargetIndex, tObjNum);
#endif
						}
						else
						{
							LogAddTD("2HIT!!!!!! ERROR   aTargetIndex : %d , tObjNum : %d", aTargetIndex, tObjNum);
						}

						HitCount++;						
					}					
				}
			}
		}

		count++;
			
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
}

int CObjUseSkill::SkillEvilMonster(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	LPOBJ lpObj		= &gObj[aIndex];
	int tObjNum;
	int count		= 0;
	int HitCount	= 0;
	int bAttack;
	int DuelIndex	= lpObj->m_iDuelUser;
	// ----
	while(true)
	{
		if( lpObj->VpPlayer2[count].state )
		{
			tObjNum = lpObj->VpPlayer2[count].number;
			// ----
			if( tObjNum >= 0 )
			{
				int EnableAttack = false;
				// ----
				if( lpObj->VpPlayer2[count].type == 1 )
				{
					EnableAttack = true;
					// ----
					if( gObj[tObjNum].m_RecallMon >= 0 )
					{
						if( tObjNum != aTargetIndex )
						{
							EnableAttack = false;
						}
					}
				}
				// ----
				if( EnableAttack )
				{
					if( gObjCalDistance(lpObj, &gObj[tObjNum]) < 6 )
					{
						bAttack = false;
						// ----
						if( HitCount >= 5 )
						{
							bAttack = false;
						}
						else
						{
							bAttack = true;
						}
						// ----
						if( tObjNum == aTargetIndex )
						{
							bAttack = true;
						}
						// ----
						if( bAttack )
						{
							int delay = rand() % 2000;
							// ----
							gObjAddAttackProcMsgSendDelay(lpObj, 50, tObjNum, 300, lpMagic->m_Skill, 0);
							HitCount++;
							// ----
							LPOBJ lpTargetObj = &gObj[tObjNum];
							// ----
							if( !gObjSearchActiveEffect(lpTargetObj, 55) )
							{
								if( !retResistance(lpTargetObj, 1) )
								{
									lpTargetObj->lpAttackObj = lpObj;
									gObjApplyBuffEffectDuration(lpTargetObj, 55, 19, 3, 0, 0, 20);
								}
							}
						}
					}
				}
			}
		}
		// ----
		count++;
		// ----
		if( count > MAX_VIEWPORT-1 )
		{
			break;
		}
	}
	// ----
	return true;
}
// -------------------------------------------------------------------------------

//00530b60	-> 100% (Identical)
int CObjUseSkill::SkillDeathPoisonForMeDusa(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, int aTargetIndex)
{
	LPOBJ lpObj		= &gObj[aIndex];
	int tObjNum;
	int count		= 0;
	int FirstHit	= 0;
	int HitCount	= 0;
	int DuelIndex	= lpObj->m_iDuelUser;
	int EnableAttack;
	// ----
	if( !OBJMAX_RANGE(aTargetIndex) )
	{
		LogAddTD("[InvalidTargetIndex][SkillDeathPoisonForMeDusa] Index :%d , AccountID : %s ",
			aIndex, gObj[aIndex].AccountID);
		return 0;
	}
	// ----
	LPOBJ lpTargetObj = &gObj[aTargetIndex];
	// ----
	while(true)
	{
		if( lpObj->VpPlayer2[count].state != 0 )
		{
			tObjNum = lpObj->VpPlayer2[count].number;
			// ----
			if( tObjNum >= 0 )
			{
				EnableAttack = 0;
				// ----
				if( lpObj->VpPlayer2[count].type == OBJ_USER && gObj[tObjNum].m_RecallMon < 0 )
				{
					EnableAttack = 1;
				}
				// ----
				if( EnableAttack )
				{
					if( this->CalDistance(x, y, gObj[tObjNum].X, gObj[tObjNum].Y) < 8 )
					{
						if( lpObj->m_Index != gObj[tObjNum].m_Index )
						{
							int iSkillDistance = gObjCalDistance(lpTargetObj, &gObj[tObjNum]);
							// ----
							if( iSkillDistance <= 3 )
							{
								int delay = rand() % 500;
								gObjAddAttackProcMsgSendDelay(lpObj, 50, tObjNum, delay, lpMagic->m_Skill, 0);
								// ----
								if( gObjSearchActiveEffect(&gObj[tObjNum], 55) )
								{
									if( !retResistance(&gObj[tObjNum], 1) )
									{
										gObj[tObjNum].lpAttackObj = lpObj;
										gObjApplyBuffEffectDuration(&gObj[tObjNum], 55, 19, 3, 0, 0, 20);
									}
								}
							}
						}
					}
				}
			}
		}
		// ----
		count++;
		// ----
		if( count > MAX_VIEWPORT -1 )
		{
			break;
		}
	}
	// ----
	return 1;
}
// -------------------------------------------------------------------------------

//00530eb0	-> 100%
int CObjUseSkill::SkillMonkBuff(int aIndex, CMagicInf * lpMagic)
{
	//LPOBJ lpObj = &gObj[aIndex];;
	//// ----
	//if( lpObj->Type != 1 )
	//{
	//	return false;
	//}
	//// ----
	//if( lpObj->Class != CLASS_MONK )
	//{
	//	return false;
	//}
	//// ----
	//if( !lpMagic || lpMagic->m_Skill != 266 )
	//{
	//	return false;
	//}
	//// ----
	//int nEffectValue = 3 + (lpObj->Energy + lpObj->AddEnergy - 404) / (float)100;

	//if(nEffectValue > 10)
	//{
	//	nEffectValue = 10;

	//}
	//
	////if( g_SkillAdditionInfo.m_IgnoreDefenseEffectMax > 0 && nEffectValue > g_SkillAdditionInfo.m_IgnoreDefenseEffectMax )
	////{
	////	nEffectValue = g_SkillAdditionInfo.m_IgnoreDefenseEffectMax;
	////}

	//int Time = lpObj->Energy / 5 + 60;
	//
	////if( g_SkillAdditionInfo.m_IgnoreDefenseTimeMax > 0 && Time > g_SkillAdditionInfo.m_IgnoreDefenseTimeMax )
	////{
	////	Time = g_SkillAdditionInfo.m_IgnoreDefenseTimeMax;
	////}

	//gObjApplyBuffEffectDuration(lpObj, 129, 72, nEffectValue, 0, 0, lpObj->Energy / 5 + 60);
	//GCMagicAttackNumberSend(lpObj, 266, lpObj->m_Index, 1);
	//// ----
	//return true;

	LPOBJ lpObj = &gObj[aIndex];;
	// ----
	if( lpObj->Type != 1 )
	{
		return false;
	}
	// ----
	if( lpObj->Class != CLASS_MONK )
	{
		return false;
	}
	// ----
	if( !lpMagic || lpMagic->m_Skill != 266 )
	{
		return false;
	}
	// ----
	int nEffectValue = g_SkillAdditionInfo.IgnoreDefenseEffectStart + (lpObj->Energy + lpObj->AddEnergy - g_SkillAdditionInfo.IgnoreDefenseEffectSub) / (float)g_SkillAdditionInfo.IgnoreDefenseEffectDiv;

	if( g_SkillAdditionInfo.IgnoreDefenseEffectMax > 0 && nEffectValue > g_SkillAdditionInfo.IgnoreDefenseEffectMax )
	{
		nEffectValue = g_SkillAdditionInfo.IgnoreDefenseEffectMax;
	}

	int Time = lpObj->Energy / g_SkillAdditionInfo.IgnoreDefenseTimeDiv + g_SkillAdditionInfo.IgnoreDefenseTimeStart;

	if( g_SkillAdditionInfo.IgnoreDefenseTimeMax > 0 && Time > g_SkillAdditionInfo.IgnoreDefenseTimeMax )
	{
		Time = g_SkillAdditionInfo.IgnoreDefenseTimeMax;
	}

	gObjApplyBuffEffectDuration(lpObj, 129, ADD_OPTION_IGNOREDEFENSE, nEffectValue, 0, 0, lpObj->Energy / 5 + 60);
	GCMagicAttackNumberSend(lpObj, 266, lpObj->m_Index, 1);
	// ----
	return true;
}
// -------------------------------------------------------------------------------

//00531010	-> 100%
int CObjUseSkill::SkillMonkBuffApplyParty(int aIndex, CMagicInf * lpMagic)
{
	//int skillSuccess = TRUE;
	//LPOBJ lpObj = &gObj[aIndex];
	//int number;

	//if( lpObj->Type != OBJ_USER && lpObj->m_RecallMon == -1 )
	//	return FALSE;

	//if( lpObj->Class != CLASS_MONK )
	//	return FALSE;

	//int partynum = 0;
	//int partycount;
	//int dis;
	//int ApplyPartyIndex[MAX_USER_IN_PARTY];
	//int nEffectValue;
	//memset(ApplyPartyIndex,-1,sizeof(ApplyPartyIndex));
	//LPOBJ lpPartyObj;

	//partynum = lpObj->PartyNumber;

	//if( partynum != -1 )
	//{
	//	partycount = gParty.m_PartyS[partynum].Count;

	//	for(int n = 0; n < MAX_USER_IN_PARTY; n++)
	//	{
	//		number = gParty.m_PartyS[partynum].Number[n];

	//		if( number >= 0 )
	//		{
	//			lpPartyObj = &gObj[number];


	//			if( lpPartyObj->MapNumber == lpObj->MapNumber )
	//			{
	//				dis = gObjCalDistance(lpObj,&gObj[number]);
	//				if( dis < 4 )
	//				{
	//					ApplyPartyIndex[n] = lpPartyObj->m_Index;
	//				}
	//			}
	//		}
	//	}
	//}

	//int Time = 0;

	//if( lpMagic->m_Skill == 267 )
	//{
	//	nEffectValue = 30 + (lpObj->Energy+lpObj->AddEnergy-132)/10;

	//	if( 200 > 0 && nEffectValue > 200 )
	//	{
	//		nEffectValue = 200;
	//	}

	//	Time = 60+lpObj->Energy/5;
	//	
	//	//if( g_SkillAdditionInfo.m_IncreaseHealthTimeMax > 0 && Time > g_SkillAdditionInfo.m_IncreaseHealthTimeMax )
	//	//{
	//	//	Time = g_SkillAdditionInfo.m_IncreaseHealthTimeMax;
	//	//}
	//}
	//else if( lpMagic->m_Skill == 268 )
	//{
	//	nEffectValue = 10 + (lpObj->Energy+lpObj->AddEnergy-80)/10;

	//	if( 100 > 0 && nEffectValue > 100 )
	//	{
	//		nEffectValue = 100;
	//	}

	//	Time = 60+lpObj->Energy/5;
	//	
	//	//if( g_SkillAdditionInfo.m_IncreaseBlockTimeMax > 0 && Time > g_SkillAdditionInfo.m_IncreaseBlockTimeMax )
	//	//{
	//	//	Time = g_SkillAdditionInfo.m_IncreaseBlockTimeMax;
	//	//}
	//}
	//else
	//{
	//	return FALSE;
	//}

	//if( partynum == -1 )
	//{
	//	if( lpMagic->m_Skill == 267 )
	//	{
	//		gObjApplyBuffEffectDuration(lpObj,130,11,nEffectValue,0,0,Time);
	//		GCMagicAttackNumberSend(lpObj,267,lpObj->m_Index,TRUE);
	//		gObjCalCharacter(lpObj->m_Index);
	//	}
	//	else if( lpMagic->m_Skill == 268 )
	//	{
	//		gObjApplyBuffEffectDuration(lpObj,131,74,nEffectValue,0,0,Time);
	//		GCMagicAttackNumberSend(lpObj,268,lpObj->m_Index,TRUE);
	//	}
	//}
	//else
	//{
	//	for(int n = 0; n < MAX_USER_IN_PARTY; n++)
	//	{
	//		if( ApplyPartyIndex[n] != -1 )
	//		{
	//			lpPartyObj = &gObj[ApplyPartyIndex[n]];
	//			if( lpMagic->m_Skill == 267 )
	//			{
	//				gObjApplyBuffEffectDuration(lpPartyObj,130,11,nEffectValue,0,0,Time);
	//				GCMagicAttackNumberSend(lpPartyObj,267,lpPartyObj->m_Index,TRUE);
	//				gObjCalCharacter(lpPartyObj->m_Index);
	//			}
	//			else if( lpMagic->m_Skill == 268 )
	//			{
	//				//71, but why?
	//				gObjApplyBuffEffectDuration(lpPartyObj,131,74,nEffectValue,0,0,Time);
	//				GCMagicAttackNumberSend(lpPartyObj,268,lpPartyObj->m_Index,TRUE);
	//			}
	//		}
	//	}
	//}
	//return TRUE;


	int skillSuccess = TRUE;
	LPOBJ lpObj = &gObj[aIndex];
	int number;

	if( lpObj->Type != OBJ_USER && lpObj->m_RecallMon == -1 )
		return FALSE;

	if( lpObj->Class != CLASS_MONK )
		return FALSE;

	int partynum = 0;
	int partycount;
	int dis;
	int ApplyPartyIndex[MAX_USER_IN_PARTY];
	int nEffectValue;
	memset(ApplyPartyIndex,-1,sizeof(ApplyPartyIndex));
	LPOBJ lpPartyObj;

	partynum = lpObj->PartyNumber;

	if( partynum != -1 )
	{
		partycount = gParty.m_PartyS[partynum].Count;

		for(int n = 0; n < MAX_USER_IN_PARTY; n++)
		{
			number = gParty.m_PartyS[partynum].Number[n];

			if( number >= 0 )
			{
				lpPartyObj = &gObj[number];


				if( lpPartyObj->MapNumber == lpObj->MapNumber )
				{
					dis = gObjCalDistance(lpObj,&gObj[number]);
					if( dis < 4 )
					{
						ApplyPartyIndex[n] = lpPartyObj->m_Index;
					}
				}
			}
		}
	}

	int Time = 0;

	if( lpMagic->m_Skill == 267 )
	{
		nEffectValue = g_SkillAdditionInfo.IncreaseHealthEffectStart + (lpObj->Energy+lpObj->AddEnergy-g_SkillAdditionInfo.IncreaseHealthEffectSub)/g_SkillAdditionInfo.IncreaseHealthEffectDiv;

		if( g_SkillAdditionInfo.IncreaseHealthEffectMax > 0 && nEffectValue > g_SkillAdditionInfo.IncreaseHealthEffectMax )
		{
			nEffectValue = g_SkillAdditionInfo.IncreaseHealthEffectMax;
		}

		Time = g_SkillAdditionInfo.IncreaseHealthTimeStart+lpObj->Energy/g_SkillAdditionInfo.IncreaseHealthTimeDiv;

		if( g_SkillAdditionInfo.IncreaseHealthTimeMax > 0 && Time > g_SkillAdditionInfo.IncreaseHealthTimeMax )
		{
			Time = g_SkillAdditionInfo.IncreaseHealthTimeMax;
		}
	}
	else if( lpMagic->m_Skill == 268 )
	{
		nEffectValue = g_SkillAdditionInfo.IncreaseBlockEffectStart + (lpObj->Energy+lpObj->AddEnergy-g_SkillAdditionInfo.IncreaseBlockEffectSub)/g_SkillAdditionInfo.IncreaseBlockEffectDiv;

		if( g_SkillAdditionInfo.IncreaseBlockEffectMax > 0 && nEffectValue > g_SkillAdditionInfo.IncreaseBlockEffectMax )
		{
			nEffectValue = g_SkillAdditionInfo.IncreaseBlockEffectMax;
		}

		Time = g_SkillAdditionInfo.IncreaseBlockTimeStart+lpObj->Energy/g_SkillAdditionInfo.IncreaseBlockTimeDiv;

		if( g_SkillAdditionInfo.IncreaseBlockTimeMax > 0 && Time > g_SkillAdditionInfo.IncreaseBlockTimeMax )
		{
			Time = g_SkillAdditionInfo.IncreaseBlockTimeMax;
		}
	}
	else
	{
		return FALSE;
	}

	if( partynum == -1 )
	{
		if( lpMagic->m_Skill == 267 )
		{
			gObjApplyBuffEffectDuration(lpObj,130,ADD_OPTION_VITALITY_MONK,nEffectValue,0,0,Time);
			GCMagicAttackNumberSend(lpObj,267,lpObj->m_Index,TRUE);
			gObjCalCharacter(lpObj->m_Index);
		}
		else if( lpMagic->m_Skill == 268 )
		{
			gObjApplyBuffEffectDuration(lpObj,131,ADD_OPTION_SUCCESSFULBLOCKING,nEffectValue,0,0,Time);
			GCMagicAttackNumberSend(lpObj,268,lpObj->m_Index,TRUE);
		}
	}
	else
	{
		for(int n = 0; n < MAX_USER_IN_PARTY; n++)
		{
			if( ApplyPartyIndex[n] != -1 )
			{
				lpPartyObj = &gObj[ApplyPartyIndex[n]];
				if( lpMagic->m_Skill == 267 )
				{
					gObjApplyBuffEffectDuration(lpPartyObj,130,ADD_OPTION_VITALITY_MONK,nEffectValue,0,0,Time);
					GCMagicAttackNumberSend(lpPartyObj,267,lpPartyObj->m_Index,TRUE);
					gObjCalCharacter(lpPartyObj->m_Index);
				}
				else if( lpMagic->m_Skill == 268 )
				{
					//71, but why?
					gObjApplyBuffEffectDuration(lpPartyObj,131,ADD_OPTION_SUCCESSFULBLOCKING,nEffectValue,0,0,Time);
					GCMagicAttackNumberSend(lpPartyObj,268,lpPartyObj->m_Index,TRUE);
				}
			}
		}
	}
	return TRUE;
}

// -------------------------------------------------------------------------------

//005314c0	-> 100%
void CObjUseSkill::SkillMonkBarrageJustOneTarget(int aIndex,CMagicInf * lpMagic,int aTargetIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	int nTargetObjNum = 0;
	int nViewPortObjectCount = 0;
	int DuelIndex = lpObj->m_iDuelUser;

	if( !OBJMAX_RANGE(aTargetIndex) )
	{
		LogAddTD("[InvalidTargetIndex][SkillMonkBarrageJustOneTarget] Index :%d , AccountID : %s ",
			aIndex,gObj[aIndex].AccountID);
		return;
	}

	int EnableAttack;
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	while( TRUE )
	{
		if( lpObj->VpPlayer2[nViewPortObjectCount].state != 0 )
		{
			nTargetObjNum = lpObj->VpPlayer2[nViewPortObjectCount].number;

			if( nTargetObjNum >= 0 && nTargetObjNum == aTargetIndex )
			{
				EnableAttack = FALSE;

				if(lpObj->VpPlayer2[nViewPortObjectCount].type == OBJ_USER )
				{
					EnableAttack = TRUE;
				}
				else if( lpTargetObj->Type == OBJ_MONSTER && gObj[nTargetObjNum].m_RecallMon < 0 )
				{
					EnableAttack = TRUE;
				}
				else if( nTargetObjNum == DuelIndex )
				{
					EnableAttack = TRUE;
				}
				else
				{
					int CallMonIndex = gObj[nTargetObjNum].m_Index;

					if(gObj[nTargetObjNum].Type == OBJ_MONSTER && gObj[nTargetObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[nTargetObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = TRUE;
					}
				}

				if( EnableAttack != FALSE && CalDistance(gObj[aTargetIndex].X,gObj[aTargetIndex].Y,gObj[nTargetObjNum].X,gObj[nTargetObjNum].Y) < 4 )
				{
					int nMaxBarrageCount = 0;

					if( lpMagic->m_Skill == 260 )
					{
						nMaxBarrageCount = 5;
					}
					else if( lpMagic->m_Skill == 261 )
					{
						nMaxBarrageCount = 3;
					}
					else if( lpMagic->m_Skill == 262 )
					{
						nMaxBarrageCount = 5;
					}
					else if( lpMagic->m_Skill == 263 )
					{
						nMaxBarrageCount = 3;
					}
					else
					{
						nMaxBarrageCount = 0;
					}

					if( lpMagic->m_Skill == 260 && rand()%100 < 10 )
					{
						//gObjApplyBuffEffectDuration(lpTargetObj, 76, 29, 5, 0, 0, 10);
					}
					else if( lpMagic->m_Skill == 261 && rand()%100 < 10 )
					{
						gObjApplyBuffEffectDuration(lpTargetObj, 58, 23,10,0,0,10);
					}
					else if( lpMagic->m_Skill == 262 && rand()%100 < 40 )
					{
						if(gGENS)
						{
							if(lpObj->m_GensInfluence != lpTargetObj->m_GensInfluence && gGensSystem.IsMapBattleZone(lpObj->MapNumber))
							{
								lpTargetObj->lpAttackObj = lpObj;
								lpTargetObj->DelayActionTime = 1000;
								lpTargetObj->DelayLevel = 1;
								gObjApplyBuffEffectDuration(lpTargetObj,86,20,0,0,0,10);
							}
						}
						else
						{
							lpTargetObj->lpAttackObj = lpObj;
							lpTargetObj->DelayActionTime = 1000;
							lpTargetObj->DelayLevel = 1;
							gObjApplyBuffEffectDuration(lpTargetObj,86,20,0,0,0,10);
						}
					}

					for(int i = 1; i < nMaxBarrageCount; i++)
					{
						if( i%(nMaxBarrageCount-1) == TRUE  )
						{
							gObjAttack(lpObj,lpTargetObj,lpMagic,TRUE,TRUE,0,0,i,0);
						}
						else
						{
							gObjAttack(lpObj,lpTargetObj,lpMagic,FALSE,TRUE,0,0,i,0);
						}
					}
				}
				break;
			}
		}

		nViewPortObjectCount++;

		if(nViewPortObjectCount > MAX_VIEWPORT -1)
		{
			break;
		}
	}
}
// -------------------------------------------------------------------------------

//00531a30	-> 100%
int CObjUseSkill::SkillMonkDarkSideGetTargetIndex(int aIndex, int aTargetIndex, CMagicInf * lpMagic, WORD * wTargetList)
{
	LPOBJ lpObj = &gObj[aIndex];
	int nTargetObjNum = 0;
	int nViewPortObjectCount = 0;
	int nHitTargetCount = 0;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack = 0;

	if( wTargetList == NULL)
	{
		return false;
	}

	if( lpMagic->m_Skill != 263
		&& g_MasterSkillSystem.GetBaseMasterLevelSkill(lpMagic->m_Skill) != 559 
		)
	{
		return false;
	}
	/*while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;
				if(gObj[tObjNum].Class < 100 || gObj[tObjNum].Class > 110)
				{
	
					if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
					{
						EnableAttack = 1;
					}
					else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
					{
						EnableAttack = 1;
					}
//#if(GS_CASTLE==1)
					else if(lpObj->VpPlayer2[count].type != OBJ_NPC && gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
					{
						EnableAttack = 1;
					}
//#endif
					else
					{
						int CallMonIndex = gObj[tObjNum].m_Index;
	
						if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
						{
							CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
						}
	
						if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
						{
							EnableAttack = 1;
						}
					}
				}
	
				if(EnableAttack != 0)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 5)
					{
						bAttack = 0;
	
						if(HitCount > 15)
						{
							bAttack = 0;
						}
	
						if(HitCount >= 10)
						{
							if(rand()%2)
							{
								bAttack = 1;
							}
						}
						else
						{
							bAttack = 1;
						}
	
						if(bAttack != 0)
						{
							gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,500,lpMagic->m_Skill,0);
						}
					}
				}
			}
		}
	
		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}*/
	if( aTargetIndex != 0 )
	{
		while(true)
		{
			if( lpObj->VpPlayer2[nViewPortObjectCount].state != 0 )
			{
				nTargetObjNum = lpObj->VpPlayer2[nViewPortObjectCount].number;

				if( nTargetObjNum >= 0 && nTargetObjNum < OBJMAX )
				{
					LPOBJ lpTargetObj = &gObj[nTargetObjNum];

					if( lpObj->VpPlayer2[nViewPortObjectCount].type == OBJ_USER && nTargetObjNum == aTargetIndex )
					{
						int nAttackRange = 0;

						if( lpMagic->m_Skill == 263
//#ifndef NO_WORK
							|| g_MasterSkillSystem.GetBaseMasterLevelSkill(lpMagic->m_Skill) == 559 
//#endif
							)
							nAttackRange = 5;
						else
							nAttackRange = 0;

						if( CalDistance(lpObj->X,lpObj->Y,gObj[nTargetObjNum].X,gObj[nTargetObjNum].Y) < nAttackRange )
						{
							wTargetList[nHitTargetCount] = nTargetObjNum;
							nHitTargetCount++;
							break;
						}
					}
				}
			}

			nViewPortObjectCount++;

			if( nViewPortObjectCount > MAX_VIEWPORT-1 )
				break;
		}

		nViewPortObjectCount = 0;
	}

	while(true)
	{
		if( lpObj->VpPlayer2[nViewPortObjectCount].state != 0 )
		{
			nTargetObjNum = lpObj->VpPlayer2[nViewPortObjectCount].number;

			if( nTargetObjNum >= 0 && nTargetObjNum < OBJMAX )
			{
				EnableAttack = FALSE;

				LPOBJ lpTargetObj = &gObj[nTargetObjNum];

				if( gGENS && lpObj->VpPlayer2[nViewPortObjectCount].type == OBJ_USER && gGensSystem.IsMapBattleZone(lpObj->MapNumber) )
				{
					EnableAttack = TRUE;
				}
				else if( lpTargetObj->Type == OBJ_MONSTER && lpTargetObj->m_RecallMon < 0 )
				{
					EnableAttack = TRUE;
				}
				else if( DuelIndex == nTargetObjNum )
				{
					EnableAttack = TRUE;
				}

				else
				{
					int CallMonIndex = gObj[nTargetObjNum].m_Index;

					if(gObj[nTargetObjNum].Type == OBJ_MONSTER && gObj[nTargetObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[nTargetObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = TRUE;
					}
				}
#ifdef _RF_GENS_MAP_DARK_SIDE_
				if(gGensSystem.IsMapBattleZone(lpObj->MapNumber) && gGensSystem.GetGensClass(lpObj) == gGensSystem.GetGensClass(lpTargetObj))
				{

					EnableAttack = FALSE;
				}

#endif

				if( EnableAttack != FALSE && !gObjAttackQ(lpTargetObj) )
				{
					EnableAttack = FALSE;
				}

				if( EnableAttack != FALSE )
				{
					int nAttackRange = 0;

					if( lpMagic->m_Skill == 263 
						|| g_MasterSkillSystem.GetBaseMasterLevelSkill(lpMagic->m_Skill) == 559
						)
						nAttackRange = 5;
					else
						nAttackRange = 0;

					if( CalDistance(lpObj->X,lpObj->Y,gObj[nTargetObjNum].X,gObj[nTargetObjNum].Y) < nAttackRange )
					{
						wTargetList[nHitTargetCount] = nTargetObjNum;
						nHitTargetCount++;

						if( nHitTargetCount >= 5 )
							break;
					}
				}

			}
		}
		nViewPortObjectCount++;

		if( nViewPortObjectCount > MAX_VIEWPORT-1 )
			break;
	}
	return true;
}
// -------------------------------------------------------------------------------

//00531f10	-> 100%
int CObjUseSkill::SkillCharge(int aIndex, CMagicInf * lpMagic, int aTargetIndex)
{
	if( !OBJMAX_RANGE(aIndex) )
	{
		return false;
	}
	// ----
	LPOBJ lpObj = &gObj[aIndex];
	// ----
	//if( lpObj->MapNumber != 30 && lpObj->MapNumber != 31 )	//Castle Siege?
	//{
	//	return false;
	//}
	// ----
	GCMagicAttackNumberSend(lpObj, lpMagic->m_Skill, aTargetIndex, 1);
	gObjAttack(lpObj, &gObj[aTargetIndex], lpMagic, 0, 1, 0, 0, 0, 0);
	// ----
	return true;
}

// -------------------------------------------------------------------------------
int CObjUseSkill::SkillAreaMonsterAttack(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, int aTargetIndex, int Dis, int Flag, int Delay) //004F7700
{
	LPOBJ lpObj = &gObj[aIndex]; //loc2

	int SkillResult = 0; //loc3

	int count = 0; //loc4
	int tObjNum; //loc5

	int DuelIndex = lpObj->m_iDuelUser; //loc6

	int hitcount = 0; //loc7

	BOOL bAttack = FALSE; //loc8

	int maxhit = 4; //loc9

	int loc10 = 8; //loc10

	if(lpMagic->m_Skill == 237)
	{
		maxhit = 8;
		loc10 = 12;
	}

	int iSkillDistance = MagicDamageC.GetSkillDistance(lpMagic->m_Skill); //loc11

	BOOL bEnableAttack; //loc12

	if(this->CalDistance(lpObj->X,lpObj->Y,x,y) <= iSkillDistance)
	{
		while( true )
		{
			if(lpObj->VpPlayer2[count].state != 0)
			{
				tObjNum = lpObj->VpPlayer2[count].number;

				if(tObjNum >= 0)
				{
					bEnableAttack = FALSE;

					if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
					{
						bEnableAttack = TRUE;
					}
					else if(tObjNum == aTargetIndex && Flag == 1 || DuelIndex == tObjNum)
					{
						bEnableAttack = TRUE;
					}
//#if(_GSCS==1)
					else if(lpObj->VpPlayer2[count].type != OBJ_NPC && gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
					{
						bEnableAttack = TRUE;
					}
//#endif
					else
					{
						int CallMonIndex = gObj[tObjNum].m_Index;

						if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
						{
							CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
						}

						if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==TRUE)
						{
							bEnableAttack = TRUE;
						}
					}

					if(bEnableAttack != FALSE)
					{
						if(gObj[tObjNum].X >= x-Dis && gObj[tObjNum].X <= x+Dis && gObj[tObjNum].Y >= y-Dis && gObj[tObjNum].Y <= y+Dis)
						{
							gObj[tObjNum].lpAttackObj = lpObj;
							hitcount++;

							if(hitcount > maxhit)
							{
								if(rand()%2 != 0)
								{
									bAttack = TRUE;
								}
							}
							else
							{
								bAttack = TRUE;
							}

							if(hitcount > loc10)
							{
								bAttack = FALSE;
							}

							if(bAttack == TRUE)
							{
								if(Delay == FALSE)
								{
									gObjAttack(lpObj,&gObj[tObjNum],lpMagic,1,0,0,0,0,0);
								}
								else
								{
									gObjAddAttackProcMsgSendDelay(lpObj, 50, tObjNum, Delay, lpMagic->m_Skill, 0);
								}
							}
							
							SkillResult = 1;
						}
					}
				}
			}

			count++;
			if(count > MAX_VIEWPORT -1)
			{
				break;
			}
		}
	}

	return SkillResult;
}
//
//void CMasterLevelSkillTreeSystem::MLS_SkillChaoticDesier(int aIndex, CMagicInf * lpMagic, BYTE TargetPos, int aTargetIndex)
//{
//	LPOBJ lpObj = &gObj[aIndex];
//	int bSuccess = TRUE;
//
//	MLS_SkillFrustrum3(aIndex,TargetPos,1.5f,6.0f,1.5f,0);
//
//	int tObjNum;
//	int count = 0;
//	int HitCount = 0;
//	int bAttack;
//	int DuelIndex = lpObj->m_iDuelUser;
//	int EnableAttack;
//
//	while ( true )
//	{
//		if(lpObj->VpPlayer2[count].state != 0)
//		{
//			tObjNum = lpObj->VpPlayer2[count].number;
//
//			if(tObjNum >= 0)
//			{
//				EnableAttack = 0;
//
//				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
//				{
//					EnableAttack = 1;
//				}
//				else if( tObjNum == aTargetIndex || DuelIndex == tObjNum)
//				{
//					EnableAttack = 1;
//				}
//
//				else if(lpObj->VpPlayer2[count].type != OBJ_NPC && gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE && g_CastleSiege.GetCastleState() == 7)
//				{
//					if( lpObj->m_btCsJoinSide != gObj[tObjNum].m_btCsJoinSide )
//						EnableAttack = 1;
//				}
//
//				else
//				{
//					int CallMonIndex = gObj[tObjNum].m_Index;
//
//					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
//					{
//						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
//					}
//
//					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
//					{
//						EnableAttack = 1;
//					}
//				}
//
//				if( EnableAttack != FALSE && SkillTestFrustrum(gObj[tObjNum].X,gObj[tObjNum].Y,aIndex) )
//				{
//					bAttack = FALSE;
//
//					if( HitCount > 8 )
//					{
//						if(rand()%2)
//						{
//							bAttack = TRUE;
//						}
//					}
//					else
//					{
//						bAttack = TRUE;
//					}
//
//					if( bAttack != FALSE )
//					{
//#if(EVOMU_DLSKILLCHANGE==TRUE)
//						if(	g_ZtLicense.CheckUser(eZtUB::Gredy)			|| 
//							g_ZtLicense.CheckUser(eZtUB::GredyLocal)	|| 
//							g_ZtLicense.CheckUser(eZtUB::Gredy2)		||
//							g_ZtLicense.CheckUser(eZtUB::SILVER1)		||
//							g_ZtLicense.CheckUser(eZtUB::SILVER2)		||
//							g_ZtLicense.CheckUser(eZtUB::SILVER_Local)	)
//						{
//							gObjAttack(lpObj,&gObj[tObjNum],lpMagic,1,0,0,0,0,0);
//						}
//						else
//						{
//							gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,250,lpMagic->m_Skill,0);
//						}
//#else
//						gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,250,lpMagic->m_Skill,0);
//#endif
//					}
//
//					if( OBJMAX_RANGE(aTargetIndex) && aTargetIndex == tObjNum)
//					{
//#if(EVOMU_DLSKILLCHANGE==TRUE)
//						if(	g_ZtLicense.CheckUser(eZtUB::Gredy)			|| 
//							g_ZtLicense.CheckUser(eZtUB::GredyLocal)	|| 
//							g_ZtLicense.CheckUser(eZtUB::Gredy2)		||
//							g_ZtLicense.CheckUser(eZtUB::SILVER1)		||
//							g_ZtLicense.CheckUser(eZtUB::SILVER2)		||
//							g_ZtLicense.CheckUser(eZtUB::SILVER_Local)	)
//						{
//							gObjAttack(lpObj,&gObj[tObjNum],lpMagic,1,0,0,0,0,0);
//						}
//						else
//						{
//							gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,300,lpMagic->m_Skill,0);
//						}
//#else
//						gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,300,lpMagic->m_Skill,0);
//#endif
//					}
//
//					HitCount++;
//				}
//			}
//		}
//
//		count++;
//		if(count > MAX_VIEWPORT -1)
//		{
//			break;
//		}
//	}
//}