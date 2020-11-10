// EnemyData.h
// Christopher Ball 2019
// stores enemy data

#ifndef _ENEMYDATA_H_
#define _ENEMYDATA_H_

#include "pch.h"
#include "GameObject.h"

struct EnemyData
{
	std::string				type;
	ObjectData				objectData;
	float					thinkingTime;
	float					fightingRange;
	float					attackRange;
	int						encounterIndex;
};

#endif // !_ENEMYDATA_H_
