// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../SingletonHelper/SingletonHelper.h"
#include "AudioManager.generated.h"

/**
 * 
 */
UCLASS()
class SPIDERMANPROJECT_API UAudioManager : public UObject, public SingletonHelper<UAudioManager, ESingletonReplType::ESPT_Client>
{
	GENERATED_BODY()
	
};
