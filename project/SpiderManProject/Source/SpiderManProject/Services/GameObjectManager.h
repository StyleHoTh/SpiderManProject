// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Global/STLGlobalHeader.h"

//获取表格的指定行
#define GET_TAB_ROW(Type, RowID) GameObjectManager<Type>::Instance().FindGameObject(RowID)

//获取表格的整个map数据
#define GET_TAB_MAP(Type) GameObjectManager<Type>::Instance().GetAllGameObjects()

/**
 * Desc：全局唯一数据管理类
 * Author： StevenZhai
 * Date： 2018-1-2018/01/23
 * Time：11：43
 */
template<typename T>
class GameObjectManager
{
public:

	static GameObjectManager& Instance()
	{
		static GameObjectManager Manager;
		return Manager;
	}

private:
	GameObjectManager() {}
	~GameObjectManager() { ClearAll(); }

public:

	bool AddGameObject(const std::string& Id, T* pObj)
	{
		if (GameObjectMapT.find(Id) != GameObjectMapT.end())
		{
			return false;
		}

		GameObjectMapT[Id] = pObj;
		return true;
	}

	bool DeleteGameObject(const std::string& Id)
	{
		typename std::map<std::string, T*>::iterator iter = GameObjectMapT.find(Id);
		if (iter != GameObjectMapT.end())
		{
			delete iter->second; iter->second = NULL;
			GameObjectMapT.erase(iter);

			return true;
		}

		return false;
	}

	const T* FindGameObject(const std::string& Id)
	{
		typename std::map<std::string, T*>::const_iterator iter = GameObjectMapT.find(Id);
		if (iter != GameObjectMapT.end())
		{
			return iter->second;
		}

		return NULL;
	}

	void ClearAll()
	{
		for (typename std::map<std::string, T*>::iterator iter = GameObjectMapT.begin();
			iter != GameObjectMapT.end(); ++iter)
		{
			if (NULL != iter->second)
			{
				delete iter->second;
			}
		}

		GameObjectMapT.clear();
	}

	const std::map<std::string, T*>* GetAllGameObjects()
	{
		return &GameObjectMapT;
	}

private:

	std::map<std::string, T*> GameObjectMapT;
};
