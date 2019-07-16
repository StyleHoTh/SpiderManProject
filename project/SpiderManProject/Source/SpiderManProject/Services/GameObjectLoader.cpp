// Fill out your copyright notice in the Description page of Project Settings.

#include "GameObjectLoader.h"
#include "GameObjectManager.h"

#include "Global/ProtocFilesHeader.h"
#include "Tools/ProtobufHelper.hpp"
#include "Paths.h"
#include "FileHelper.h"

#define PROTOBUFFIELD ::google::protobuf::RepeatedPtrField

template<typename RepeatedPtrFieldT, typename T>
bool ForeachGameObject(RepeatedPtrFieldT& field)
{
	for (int i = 0; i < field.size(); ++i)
	{
		T* item = new T();
		item->CopyFrom(field.Get(i));
		GameObjectManager<T>::Instance().AddGameObject(item->id(), item);
	}
	return true;
}


GameObjectLoader::GameObjectLoader()
{
}

GameObjectLoader::~GameObjectLoader()
{
}
//bool	GameObjectLoader::LoadConfigData(const FString& file)
bool	GameObjectLoader::LoadAll()
{
	{
		FString Path = FPaths::ProjectDir();
		//Path = Path.Append(file);
		Path = Path.Append("Content/Config/pro.data");

		TArray<uint8> BinaryBuffer;
		bool b = FFileHelper::LoadFileToArray(BinaryBuffer, *Path);

		if (!b)
		{
			UE_LOG(LogTemp, Error, TEXT("Load data file failed : %s"), *Path);
			return false;
		}

		DataContainer DB;

		//b = DB.ParseFromArray(BinaryBuffer.GetData(), BinaryBuffer.Num());
        b = ProtobufHelper::Parse(DB, BinaryBuffer.GetData(), BinaryBuffer.Num());   

		if (!b)
		{
			UE_LOG(LogTemp, Error, TEXT("Parse stream failed : %s"), *Path);
			return false;
		}
		ForeachGameObject<PROTOBUFFIELD<proto::asset_autoload>&, proto::asset_autoload>((PROTOBUFFIELD<proto::asset_autoload>&)DB.asset_autoload_list());

		ForeachGameObject<PROTOBUFFIELD<proto::box_drop>&, proto::box_drop>((PROTOBUFFIELD<proto::box_drop>&)DB.box_drop_list());

		ForeachGameObject<PROTOBUFFIELD<proto::danger_zone_info>&, proto::danger_zone_info>((PROTOBUFFIELD<proto::danger_zone_info>&)DB.danger_zone_info_list());

		ForeachGameObject<PROTOBUFFIELD<proto::drop_item_rules>&, proto::drop_item_rules>((PROTOBUFFIELD<proto::drop_item_rules>&)DB.drop_item_rules_list());

		ForeachGameObject<PROTOBUFFIELD<proto::global_config_camera>&, proto::global_config_camera>((PROTOBUFFIELD<proto::global_config_camera>&)DB.global_config_camera_list());

		ForeachGameObject<PROTOBUFFIELD<proto::global_config_weapon>&, proto::global_config_weapon>((PROTOBUFFIELD<proto::global_config_weapon>&)DB.global_config_weapon_list());

		ForeachGameObject<PROTOBUFFIELD<proto::item_accessory>&, proto::item_accessory>((PROTOBUFFIELD<proto::item_accessory>&)DB.item_accessory_list());

		ForeachGameObject<PROTOBUFFIELD<proto::item_bag>&, proto::item_bag>((PROTOBUFFIELD<proto::item_bag>&)DB.item_bag_list());

		ForeachGameObject<PROTOBUFFIELD<proto::item_cars>&, proto::item_cars>((PROTOBUFFIELD<proto::item_cars>&)DB.item_cars_list());

		ForeachGameObject<PROTOBUFFIELD<proto::item_equip>&, proto::item_equip>((PROTOBUFFIELD<proto::item_equip>&)DB.item_equip_list());

		ForeachGameObject<PROTOBUFFIELD<proto::item_gunclip>&, proto::item_gunclip>((PROTOBUFFIELD<proto::item_gunclip>&)DB.item_gunclip_list());

		ForeachGameObject<PROTOBUFFIELD<proto::item_medical>&, proto::item_medical>((PROTOBUFFIELD<proto::item_medical>&)DB.item_medical_list());

		ForeachGameObject<PROTOBUFFIELD<proto::item_thrown>&, proto::item_thrown>((PROTOBUFFIELD<proto::item_thrown>&)DB.item_thrown_list());

		ForeachGameObject<PROTOBUFFIELD<proto::item_weapon>&, proto::item_weapon>((PROTOBUFFIELD<proto::item_weapon>&)DB.item_weapon_list());

		ForeachGameObject<PROTOBUFFIELD<proto::language_item_info>&, proto::language_item_info>((PROTOBUFFIELD<proto::language_item_info>&)DB.language_item_info_list());

		ForeachGameObject<PROTOBUFFIELD<proto::unit_info>&, proto::unit_info>((PROTOBUFFIELD<proto::unit_info>&)DB.unit_info_list());

		ForeachGameObject<PROTOBUFFIELD<proto::widget_info>&, proto::widget_info>((PROTOBUFFIELD<proto::widget_info>&)DB.widget_info_list());
	}

	return true;
}// Clear All Data 

bool	GameObjectLoader::ClearAll()
{
	GameObjectManager<proto::asset_autoload>::Instance().ClearAll();

	GameObjectManager<proto::box_drop>::Instance().ClearAll();

	GameObjectManager<proto::danger_zone_info>::Instance().ClearAll();

	GameObjectManager<proto::drop_item_rules>::Instance().ClearAll();

	GameObjectManager<proto::global_config_camera>::Instance().ClearAll();

	GameObjectManager<proto::global_config_weapon>::Instance().ClearAll();

	GameObjectManager<proto::item_accessory>::Instance().ClearAll();

	GameObjectManager<proto::item_bag>::Instance().ClearAll();

	GameObjectManager<proto::item_cars>::Instance().ClearAll();

	GameObjectManager<proto::item_equip>::Instance().ClearAll();

	GameObjectManager<proto::item_gunclip>::Instance().ClearAll();

	GameObjectManager<proto::item_medical>::Instance().ClearAll();

	GameObjectManager<proto::item_thrown>::Instance().ClearAll();

	GameObjectManager<proto::item_weapon>::Instance().ClearAll();

	GameObjectManager<proto::language_item_info>::Instance().ClearAll();

	GameObjectManager<proto::unit_info>::Instance().ClearAll();

	GameObjectManager<proto::widget_info>::Instance().ClearAll();
	
	return true;
}