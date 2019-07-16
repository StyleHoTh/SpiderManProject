/*
* Copyright(c) 2017-2019 WindSoul Network Technology, Inc. All rights reserved.
*/


/**
* Desc: 游戏逻辑相关的常量
* Author:
* Date: 2018-04-23
* Time: 21:17
*/

#ifndef	__LogicConstants_H__
#define	__LogicConstants_H__

#include "CoreMinimal.h"
#include <DataContainer.pb.h>

namespace LogicConstants
{
	//****************************** 视角 begin ********************************

	static float SLIDER_LEAVE_RANGE_PERCENT_THRESHOLD_W = 0.6f;
	static float SLIDER_RETURN_RANGE_PERCENT_THRESHOLD_H = 0.6f;
	static float SLIDER_SCREEN_RADIUS_THRESHOLD = 300.f;
	static float SLIDER_SCREEN_RADIUS_MAX = 500.f;
	static float SLIDER_INIT_SPEED = 100.f;
	static float SLIDER_ACCELERATE = 100.f;
	static float SLIDER_BASE_WORLD_DISTANCE = 500.f;
	static int SLIDER_OUT_FIRE_PADDING = 10;
	static int SLIDER_IN_FIRE_PADDING = 250;
	//****************************** 视角 end ********************************

	//****************************** 武器 begin ********************************
	//暴击倍数
	static float DAMAGE_CRIT_TIMES = 1.f;

	static float ONE_SHOOT_CLICK_TIME_THRESHOLD = 300.f;

	//****************************** 武器 end ********************************

	//****************************** 掉落 begin ********************************
	//捡道具的有效距离
	static const float PICK_ITEM_DIST = 150.f;
	//显示道具特效的有效距离
	static const float DROW_ITEM_PARTICLE_DIST = 2000.f;
	//掉道具时的距离
	static const float DROP_ITEM_DIST = 100.f;
	//初始化时的默认Z轴高度
	static const float DROP_ITEM_INIT_LOC_Z = 50.f;
	////初始化时的有效坐标检测半径
	static const float DROP_ITEM_LOC_CHECK_RADIUS = 200.f;
	//****************************** 掉落 end ********************************

	//****************************** 掉落 begin ********************************
	//空手状态的武器ID
	static const FString EMPYT_WEAPON_ID = TEXT("i_wea_empty_hand");
	//****************************** 掉落 end ********************************

	//****************************** 背包 begin ******************************
	static const FString INIT_BAG_ID = TEXT("i_bag_0");

	static const int32 INIT_BAG_CAPACITY = 12;

	void InitConstants()
	{
		if (const ::proto::global_config_camera* config = GameObjectManager<proto::global_config_camera>::Instance().FindGameObject("gcc_001"))
		{
			SLIDER_LEAVE_RANGE_PERCENT_THRESHOLD_W = config->leave_range_percent_threshold_width();
			SLIDER_RETURN_RANGE_PERCENT_THRESHOLD_H = config->return_range_percent_threshold_height();
			SLIDER_INIT_SPEED = config->translate_init_speed();
			SLIDER_ACCELERATE = config->translate_accelerate();
		}

		if (const ::proto::global_config_weapon* config = GameObjectManager<proto::global_config_weapon>::Instance().FindGameObject("gcw_001"))
		{
			DAMAGE_CRIT_TIMES = config->crit_times();
		}
	}

};
#endif
