#pragma once

#include "pch.h"
#include "GameObject.h"

struct EnemyData
{
	std::string				type;
	std::string				sheetName;
	ObjectData				objectData;
	float					thinkingTime;
	float					hostileRange;
	float					attackRange;
	float					chargeRange;
	float					chargeSpeed;
	int						encounterIndex;
};