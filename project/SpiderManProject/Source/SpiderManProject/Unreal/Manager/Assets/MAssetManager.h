// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "../SingletonHelper/SingletonHelper.h"
#include "MAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class SPIDERMANPROJECT_API UMAssetManager : public UAssetManager, public SingletonHelper<UMAssetManager, ESingletonReplType::ESPT_All>
{
	GENERATED_BODY()
	
};
