#include "stdafx.h"
#include "TMemory.h"
#include "ZtUtils.h"
#include "ToolKit.h"
#include "Import.h"
#include "Object.h"
#include "SelectChar.h"


#if(ENABLE_CHARACTER_ACTION)

cSelectChar gSelectChar;

void cSelectChar::Load()
{
	
	this->m_SelectCharacterAnimationID = ePlayerAction::AT_RESET;
	
	srand((unsigned)time(NULL));

	//gToolKit.SetHook(ASM::CALL,oOnCharClick_Call,&this->OnCharClick);

	SetOp((LPVOID)oOnCharClick_Call,&this->OnCharClick, ASM::CALL);
};


int cSelectChar::OnCharClick(DWORD This)
{
	//if(oSelectedCharView != -1)
	{
		for(int ViewportID = 0; ViewportID < 5; ViewportID++)
		{
			DWORD ObjectPreview = (DWORD)pGetPreviewStruct(pPreviewThis(), ViewportID);

			if(!ObjectPreview)
			{
				continue;
			}

			short ObjectPetSlot = *(short*)(ObjectPreview + 556);
		
			switch(ObjectPetSlot)
			{
			case ITEM2(13,2): // Horn of Uniria
			case ITEM2(13,3): // Horn of Dinorant
				{
					int Random = (rand() % 2) ? AT_GALLOPINGATTACK7 : ((rand() % 2) ? AT_GALLOPINGATTACK8 : AT_GALLOPINGATTACK9);

					pActionSend(ObjectPreview + 776,Random,true);
					break;
				}
			case ITEM2(13,4): // Dark Horse
				{
					int Random = (rand() % 2) ? AT_GALLOPINGACTION5 : ((rand() % 2) ? AT_GALLOPINGACTION6 : AT_GALLOPINGACTION1);

					if(Random == AT_GALLOPINGACTION5)
					{
						for(int i = 0;i < 5;i++)
						{
							if(i != oSelectedCharView)
							{
								DWORD TempObjectPreview = (DWORD)pGetPreviewStruct(pPreviewThis(), i);
								short TempObjectPetSlot = *(short*)(TempObjectPreview + 556);

								if(TempObjectPreview)
								{								
									if(TempObjectPetSlot == -1)
									{
										pActionSend(TempObjectPreview + 776,AT_FALL1,false);
									}								
								}							
							}
						}
					}

					pActionSend(ObjectPreview + 776,Random,true);
					break;
				}
			case ITEM2(13,37): // Fenrir
				{
					int Action[] = {AT_FENRIRATTACK1, AT_FENRIRATTACK2, AT_FENRIRHURT5, AT_FENRIRACTION1};

					pActionSend(ObjectPreview + 776,Action[rand() % 4],true);
					break;
				}
			default: // None
				{
					int Action[] =
					{
						AT_GREETING1,
						AT_GREETING2,
						AT_GOODBYE1,
						AT_GOODBYE2,
						AT_CLAP1,
						AT_CLAP2,
						AT_CHEER1,
						AT_CHEER2,
						AT_CHEER3,
						AT_POINTING1,
						AT_GESTURE1,
						AT_GESTURE2,
						AT_NEGATE1,
						AT_NEGATE2,
						AT_CRY1,
						AT_CRY2,
						AT_AWKWARD1,
						AT_AWKWARD2,
						AT_SEE1,
						AT_SEE2,
						AT_WIN1,
						AT_WIN2,
						AT_SMILE1,
						AT_SMILE2,
						AT_SLEEP1,
						AT_SLEEP2,
						AT_COLD1,
						AT_COLD2,
						AT_AGAIN1,
						AT_AGAIN2,
						AT_RESPECT1,
						AT_SALUTE1,
						AT_STRETCHING,
						AT_CATHING,
						AT_STRETCHING2,
						AT_FUCKING,
						AT_COMEON,
						AT_LOOK,
						AT_CELEBRATING1,
						AT_CELEBRATING2,
						AT_RUSH1,
						AT_RUSH2,
						AT_RAISE1,
						AT_RAISE2,
						AT_CELEBRATING3,
						AT_CELEBRATING4,
						AT_JUMPING,		
						AT_ROTATING,
						AT_NINJAACTION,
						AT_JUMPING1
					};				

					//pActionSend(ObjectPreview + 776, Action[rand() % 50], true);

					pActionSend(ObjectPreview + 776, gSelectChar.m_SelectCharacterAnimationID, true);

					
					break;
				}


			}
		}

		gSelectChar.m_SelectCharacterAnimationID++;

	}
	return pOnCharClick(This);

}

/*
int cSelectChar::OnCharClick(DWORD This)
{
	if(oSelectedCharView != -1)
	{
		DWORD ObjectPreview = (DWORD)pGetPreviewStruct(pPreviewThis(), oSelectedCharView);
		short ObjectPetSlot = *(short*)(ObjectPreview + 556);
		
		switch(ObjectPetSlot)
		{
		case ITEM2(13,2): // Horn of Uniria
		case ITEM2(13,3): // Horn of Dinorant
			{
				int Random = (rand() % 2) ? AT_GALLOPINGATTACK7 : ((rand() % 2) ? AT_GALLOPINGATTACK8 : AT_GALLOPINGATTACK9);

				pActionSend(ObjectPreview + 776,Random,true);
				break;
			}
		case ITEM2(13,4): // Dark Horse
			{
				int Random = (rand() % 2) ? AT_GALLOPINGACTION5 : ((rand() % 2) ? AT_GALLOPINGACTION6 : AT_GALLOPINGACTION1);

				if(Random == AT_GALLOPINGACTION5)
				{
					for(int i = 0;i < 5;i++)
					{
						if(i != oSelectedCharView)
						{
							DWORD TempObjectPreview = (DWORD)pGetPreviewStruct(pPreviewThis(), i);
							short TempObjectPetSlot = *(short*)(TempObjectPreview + 556);

							if(TempObjectPreview)
							{								
								if(TempObjectPetSlot == -1)
								{
									pActionSend(TempObjectPreview + 776,AT_FALL1,false);
								}								
							}							
						}
					}
				}

				pActionSend(ObjectPreview + 776,Random,true);
				break;
			}
		case ITEM2(13,37): // Fenrir
			{
				int Action[] = {AT_FENRIRATTACK1, AT_FENRIRATTACK2, AT_FENRIRHURT5, AT_FENRIRACTION1};

				pActionSend(ObjectPreview + 776,Action[rand() % 4],true);
				break;
			}
		default: // None
			{
				int Action[] =
				{
					AT_GREETING1,
					AT_GREETING2,
					AT_GOODBYE1,
					AT_GOODBYE2,
					AT_CLAP1,
					AT_CLAP2,
					AT_CHEER1,
					AT_CHEER2,
					AT_CHEER3,
					AT_POINTING1,
					AT_GESTURE1,
					AT_GESTURE2,
					AT_NEGATE1,
					AT_NEGATE2,
					AT_CRY1,
					AT_CRY2,
					AT_AWKWARD1,
					AT_AWKWARD2,
					AT_SEE1,
					AT_SEE2,
					AT_WIN1,
					AT_WIN2,
					AT_SMILE1,
					AT_SMILE2,
					AT_SLEEP1,
					AT_SLEEP2,
					AT_COLD1,
					AT_COLD2,
					AT_AGAIN1,
					AT_AGAIN2,
					AT_RESPECT1,
					AT_SALUTE1,
					AT_STRETCHING,
					AT_CATHING,
					AT_STRETCHING2,
					AT_FUCKING,
					AT_COMEON,
					AT_LOOK,
					AT_CELEBRATING1,
					AT_CELEBRATING2,
					AT_RUSH1,
					AT_RUSH2,
					AT_RAISE1,
					AT_RAISE2,
					AT_CELEBRATING3,
					AT_CELEBRATING4,
					AT_JUMPING,		
					AT_ROTATING,
					AT_NINJAACTION,
					AT_JUMPING1
				};				

				pActionSend(ObjectPreview + 776,Action[rand() % 50],true);
				break;
			}
		}
	}

	return pOnCharClick(This);
}
*/


void cSelectChar::KeyboardProcces(DWORD dwEvent)
{
	switch(dwEvent)
	{
	case VK_LEFT:
		if(this->m_SelectCharacterAnimationID > ePlayerAction::AT_RESET)
		{
			this->m_SelectCharacterAnimationID--;
		}
		break;
	case VK_RIGHT:
		if(this->m_SelectCharacterAnimationID < ePlayerAction::AT_FENRIRHURT10)
		{
			this->m_SelectCharacterAnimationID++;
		}
		break;
	}
}

#endif