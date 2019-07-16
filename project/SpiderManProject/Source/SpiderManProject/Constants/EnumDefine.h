/*
* Copyright(c) 2018 WindSoul Network Technology, Inc. All rights reserved.
*/


/**
* Desc: 代理事件定义
* Author:
* Date: 2018-11-29
*/

#pragma once

#include "CoreMinimal.h"

//FString->Enum 或者 Enum->FString
//只能对使用UENUM()宏的枚举使用
namespace EnumHelper
{
	template<typename TEnum>
	static FString GetStringFromTEnum(const FString& EnumName, const TEnum& Value)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
		if (!EnumPtr)
		{
			return FString(TEXT("InValid"));
		}
		return EnumPtr->GetNameStringByIndex((int32)Value);
	}

	template<typename TEnum>
	static TEnum GetEnumValueFromString(const FString& EnumName, const FString& Value)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
		if (!EnumPtr)
		{
			return TEnum(-1);
		}
		return (TEnum)EnumPtr->GetIndexByName(FName(*Value));
	}
}

UENUM(BlueprintType)
enum class EPUModuleType : uint8
{
	//挂摄像机和弹簧臂
	EMT_Control = 0,
	EMT_Weapon,
	EMT_Pack,
	EMT_Attribute,
	EMT_Interact,
	EMT_Equip,
	EMT_PlayerState,
	EMT_Map,
	EMT_Accessory,
	EMT_Max,
};

UENUM(BlueprintType)
enum class EModuleReplState : uint8
{
	EMRS_Uninitialized = 0,
	EMRS_Initialized,
};

UENUM(BlueprintType)
enum class ECharacterReplState : uint8
{
	ECRS_Uninitialized = 0,
	ECRS_Initialized,
};

UENUM(BlueprintType)
enum class EPlayerControllerReplState : uint8
{
	EPCRS_Uninitialized = 0,
	EPCRS_Initialized,
};

UENUM(BlueprintType)
enum class ETDActorModuleType : uint8
{
	//交互
	EAT_Interact = 0,

	EAT_Max,
};

//视角类型
UENUM(BlueprintType)
enum class ECameraViewMode : uint8
{
	CVM_ThirdPerson,
	CVM_TopDownFollowRole,	//@TODO TopDown
	CVM_FPS,
	CVM_ForcusTarget,
	CVM_MAX,
};

UENUM()
enum EWeaponAnimMode
{
	EMM_EmptyHand					UMETA(DisplayName = "Empty Hand"),			//空手
	EMM_Pistol						UMETA(DisplayName = "Pistol"),				//手枪	
	EMM_RifleHip					UMETA(DisplayName = "Rifle Hip"),			//步枪腰部
	EMM_RifleIronsights				UMETA(DisplayName = "Rifle Ironsights"),	//步枪瞄准
	EMM_ShotgunHip					UMETA(DisplayName = "Shotgun Hip"),			//散弹腰部
	EMM_ShotgunIronsights			UMETA(DisplayName = "Shotgun Ironsights"),	//散弹瞄准
	EMM_Minigun						UMETA(DisplayName = "Minigun"),				//重机枪
	EMM_Thrown						UMETA(DisplayName = "Thrown"),				//投掷物
	EMM_SniperRifle					UMETA(DisplayName = "Sniper Rifle"),		//狙击枪
};

//武器状态
UENUM()
enum EWeaponState
{
	EWS_None			UMETA(DisplayName = "None"),			//初始态
	EWS_EmptyHand		UMETA(DisplayName = "Empty Hand"),		//空手
	EWS_Reloading		UMETA(DisplayName = "Reloading"),		//装弹中
	EWS_Bolting			UMETA(DisplayName = "Bolting"),			//拉栓中
	EWS_HoldFire		UMETA(DisplayName = "Hold Fire"),		//停火中	
	EWS_OpenFire		UMETA(DisplayName = "Open Fire"),		//开火中
	EWS_StartThrown		UMETA(DisplayName = "Start Thrown"),	//投掷
};


//角色状态
UENUM(BlueprintType)
enum class EPlayerState :uint8
{
	EPS_Alive = 0        UMETA(DisplayName = "alive"),                  //生存
	EPS_Dieing           UMETA(DisplayName = "dieing"),                 //死亡中
	EPS_Dead             UMETA(DisplayName = "dead"),                   //已死亡
	EPS_Resurgence       UMETA(DisplayName = "res"),                    //复活中
};


////背包道具操作类型
//UENUM()
//enum class EBagOperateType :uint8
//{
//	PickupItem = 0    UMETA(DisplayName = "add item"),      //拾取道具
//	UseItem           UMETA(DisplayName = "use item"),      //使用道具
//	DiscardItem       UMETA(DisplayName = "discard item"),  //丢弃道具
//};

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	EDT_Bullet = 0,
	EDT_Boom,
	EDT_Fire,
	EDT_Melee,
	EDT_Max,
};

UENUM(BlueprintType)
enum class EKillType : uint8
{
	EKT_M16 = 0,
	EKT_Max,
};

// 和输入位置对应 从1开始
UENUM(BlueprintType)
enum class EWeaponSlotType : uint8
{
	EWST_Rifle1 = 1,
	EWST_Rifle2,
	EWST_Pistol,
	EWST_Grenade,
	EKT_Max,
};

UENUM(BlueprintType)
enum class ECustomCursorType : uint8
{
	ECCT_Normal = 0,
	ECCT_Aim,
	ECCT_Shoot,
	ECCT_Max,
};