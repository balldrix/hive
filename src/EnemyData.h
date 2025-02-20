#pragma once

#include "GameObject.h"

struct EnemyData
{
	std::string				type = {};
	std::string				name = {};
	ObjectData				objectData = {};
	float					thinkingTime = {};
	float					hostileRange = {};
	float					fightRange = {};
	float					attackRange = {};
	float					chargeRange = {};
	float					chargeSpeed = {};
	int						encounterIndex = {};

	EnemyData() = default;
};