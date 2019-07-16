/*
* Copyright(c) 2018 WindSoul Network Technology, Inc. All rights reserved.
*/


/**
* Desc: 事件
* Author:
* Date: 2018-06-27
* Time: 21:17
*/

#pragma once

#include "EngineMinimal.h"
#include "Public/Delegates/DelegateCombinations.h"



#define ECC_Hero ECollisionChannel::ECC_GameTraceChannel1
#define ECC_Weapon ECollisionChannel::ECC_GameTraceChannel2
#define ECC_DamageTrace ECollisionChannel::ECC_GameTraceChannel3
#define ECC_Shield ECollisionChannel::ECC_GameTraceChannel4
#define ECC_ClimbTrace ECollisionChannel::ECC_GameTraceChannel7
#define ECC_BossMesh ECollisionChannel::ECC_GameTraceChannel8

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDamageActorDie, AActor*, AActor*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDoSkillSuccess, FString);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnReceiveDamage, AActor*/*s受害人*/, AActor*/*Killer*/, AActor*/*直接造成伤害对象*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHeroHPChange, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMonsterHPChange, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCharacterEndPlay, class ABaseCharacter*);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerInteract, class ABaseCharacter*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerDirveForward, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerDirveRight, float);

//武器发生变化时
DECLARE_EVENT_OneParam(AWeaponModule, FOnWeaponChangedEvent, const FString&);
//武器状态发生变化

DECLARE_EVENT_FourParams(AWeaponModule, FOnWeaponStateChangedEvent, const FString&, EWeaponState, EWeaponState, const FString&);

DECLARE_EVENT(AAttributeModule, FOnPlayerDeadEvent);
//拾取道具
DECLARE_EVENT_TwoParams(APackModule, FOnItemPickEvent, const FString&, int);
//子弹耗尽
DECLARE_EVENT_OneParam(AGunWeapon, FOnClientBulletExhaustEvent, const FString&);