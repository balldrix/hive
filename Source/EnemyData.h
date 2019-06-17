// EnemyData.h
// Christopher Ball 2019
// stores enemy data

#ifndef _ENEMYDATA_H_
#define _ENEMYDATA_H_

#include "pch.h"
#include "GameObject.h"

enum EnemyType
{
	Mook
};

struct EnemyData
{
	EnemyType				m_type;
	ObjectData				m_objectData;
	float					m_thinkingTime;
	float					m_fightingRange;
	float					m_attackRange;
};

#endif // !_ENEMYDATA_H_
