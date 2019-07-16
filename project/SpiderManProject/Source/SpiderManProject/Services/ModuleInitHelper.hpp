/*
* Copyright(c) 2018 WindSoul Network Technology, Inc. All rights reserved.
*/

/**
* Desc: Module初始化的工具类。应对联机模式下客户端和服务端初始化差异问题
* Author:
* Date: 2019-04-05
* Time: 16:55
*/

#pragma once

#include "Engine/World.h"

#include "Constants/EnumDefine.h"
#include "Unreal/Module/ModuleListManager.hpp"
#include "Unreal/Character/BaseCharacter.h"


class ModuleInitHelper
{
public:

	static void InitModulesForCharacter(UWorld* World, ABaseCharacter* Character, int ReplTypes)
	{
		if (World && Character)
		{
			for (ModuleInfoInterface* ModuleInfoPtr : ModuleListManager::CharacterModuleInfos)
			{
				if (ModuleInfoPtr)
				{
					if ((ModuleInfoPtr->GetReplType() & ReplTypes) > 0)
					{
						UObject* Obj = ModuleInfoPtr->SpawnModuleDeferred(World, Character);
						if (ACharacterModuleBase* Module = Cast<ACharacterModuleBase>(Obj))
						{
							Character->Modules[(int)ModuleInfoPtr->GetModuleType()] = Module;

							int CurrReplType = ModuleInfoPtr->GetReplType() & ReplTypes;
							switch (CurrReplType)
							{
							case EModuleReplType::EMPT_ClientOnly:
							{
								break;
							}
							case EModuleReplType::EMPT_ServerOnly:
							{
								Module->SetReplicates(false);
								Module->SetAutonomousProxy(false);
								Module->bNetUseOwnerRelevancy = false;
								Module->bOnlyRelevantToOwner = true;
								Module->SetOwner(nullptr);
								break;
							}
							case EModuleReplType::EMPT_RepliateToClient:
							{
								Module->SetReplicates(true);
								Module->SetAutonomousProxy(false);
								Module->bNetUseOwnerRelevancy = false;
								Module->bOnlyRelevantToOwner = true;
								Module->SetOwner(Character);
								break;
							}
							case EModuleReplType::EMPT_RepliateToAllClient:
							{
								Module->SetReplicates(true);
								Module->SetAutonomousProxy(false);
								Module->bNetUseOwnerRelevancy = true;
								Module->bOnlyRelevantToOwner = false;
								Module->SetOwner(Character);
								break;
							}
							case EModuleReplType::EMPT_InteractWithClient:
							{
								Module->SetReplicates(true);
								Module->SetAutonomousProxy(true);
								Module->bNetUseOwnerRelevancy = true;
								Module->SetOwner(Character);
								break;
							}
							}
						}
					}
				}
			}

			if (Character->Modules.Num() == ModuleListManager::CharacterModuleInfos.Num())
			{
				ENetMode NM = Character->GetNetMode();
				for (int i = 0; i < Character->Modules.Num(); i++)
				{
					ACharacterModuleBase* _Module = Character->Modules[i];
					if (_Module)
					{
						//if (ENetMode::NM_DedicatedServer == NM)
						{
							_Module->PostReplicationSetup();
						}

						ModuleInfoInterface* ModuleInfo = ModuleListManager::CharacterModuleInfos[i];
						if (ModuleInfo)
						{
							if (!(ENetMode::NM_Client == NM
								&& (ModuleInfo->GetReplType() == EModuleReplType::EMPT_RepliateToClient 
									|| ModuleInfo->GetReplType() == EModuleReplType::EMPT_RepliateToAllClient
									|| ModuleInfo->GetReplType() == EModuleReplType::EMPT_InteractWithClient)))
							{
								FTransform Transform;
								_Module->FinishSpawning(Transform);
							}
						}

						if (ENetMode::NM_DedicatedServer == NM)
						{
							_Module->OnServerAllModulesCreateComplete();
						}
					}
				}
			}
		}
	}

	static void RefreshModuelTypeForClient(ABaseCharacter* Character)
	{
		if (Character)
		{
			if (ENetMode::NM_Client == Character->GetNetMode())
			{
				if (Character->Modules.Num() == ModuleListManager::CharacterModuleInfos.Num())
				{
					for (int i = 0; i < Character->Modules.Num(); i++)
					{
						if (ACharacterModuleBase* ModulePtr = Character->Modules[i])
						{
							if (ModuleInfoInterface* ModuleInfo = ModuleListManager::CharacterModuleInfos[i])
							{
								ModulePtr->SetModuleType(ModuleInfo->GetModuleType());
							}
						}
					}
				}
			}
		}
	}

	static int FindModuleIndex(ACharacterModuleBase* ClientModule)
	{
		int Index = -1;
		if (ClientModule && ENetMode::NM_Client == ClientModule->GetNetMode())
		{
			for (int i = 0; i < ModuleListManager::CharacterModuleInfos.Num(); i++)
			{
				if (ModuleInfoInterface* ModuleInfo = ModuleListManager::CharacterModuleInfos[i])
				{
					if (ModuleInfo->ModuleTemplatePtr)
					{
						FString LStr1;
						FString RStr1;
						ModuleInfo->ModuleTemplatePtr->GetName().Split("_", &LStr1, &RStr1, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
						
						FString LStr2;
						FString RStr2;
						ClientModule->GetName().Split("_", &LStr2, &RStr2, ESearchCase::IgnoreCase, ESearchDir::FromEnd);

						if (LStr1 == LStr2)
						{
							Index = i;
							break;
						}
					}
				}
			}
		}

		return Index;
	}

	static void InitModulesForActor(UWorld* World, ABaseActor* Character, int ReplTypes)
	{

	}
};