// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum ESingletonReplType
{
	ESPT_Client			UMETA(DisplayName = "Client"),	
	ESPT_Server			UMETA(DisplayName = "Server"),
	ESPT_All			UMETA(DisplayName = "All"),
};


/**
 * 
 */
template<class T, ESingletonReplType ReplType>
class SPIDERMANPROJECT_API SingletonHelper
{
public:
	static T* Instance(UObject* Outer = (UObject*)GetTransientPackage());
	static void DestroyInstance();
	static bool IsInstanced();

private:
	static T* _instance;

};

template<class T, ESingletonReplType ReplType>
T* SingletonHelper<T, ReplType>::_instance = nullptr;

template<class T, ESingletonReplType ReplType>
T* SingletonHelper<T, ReplType>::Instance(UObject* Outer)
{
	bool IsInstanceEnable = false;
	switch (ReplType)
	{
	case ESingletonReplType::ESPT_Client:
	{
		IsInstanceEnable = Outer && Outer->GetWorld() && (Outer->GetWorld()->GetNetMode() == NM_Client || Outer->GetWorld()->GetNetMode() == NM_Standalone);
		break;
	}
	case ESingletonReplType::ESPT_Server:
	{
		IsInstanceEnable = Outer && Outer->GetWorld() && Outer->GetWorld()->GetNetMode() == NM_DedicatedServer;
		break;
	}
	case ESingletonReplType::ESPT_All:
	{
		IsInstanceEnable = true;
		break;
	}
	}

	if (IsInstanceEnable && !_instance)
	{
		_instance = NewObject<T>(Outer);
		_instance->AddToRoot();
	}
	return _instance;
}

template<class T, ESingletonReplType ReplType>
void SingletonHelper<T, ReplType>::DestroyInstance()
{
	if (_instance)
	{
		_instance->RemoveFromRoot();
		//_instance->ConditionalBeginDestroy();
		_instance = nullptr;
	}
}

template<class T, ESingletonReplType ReplType>
bool SingletonHelper<T, ReplType>::IsInstanced()
{
	return !!_instance;
}
