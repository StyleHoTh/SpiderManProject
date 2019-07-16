// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SingletonHelper/SingletonHelper.h"
#include "WidgetManager.generated.h"

/**
 * 
 */
UCLASS()
class SPIDERMANPROJECT_API UWidgetManager : public UObject, public SingletonHelper<UWidgetManager, ESingletonReplType::ESPT_Client>
{
	GENERATED_BODY()
	
};
