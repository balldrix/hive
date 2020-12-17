// EnemyData.h
// Christopher Ball 2019-2020
// stores enemy data

#pragma once

#include "pch.h"
#include "GameObject.h"

struct EnemyData
{
	std::string				type;
	ObjectData				objectData;
	float					thinkingTime;
	float					fightingRange;
	float					attackRange;
	float					chargeRange;
	int						chargeSpeed;
	int						encounterIndex;
};