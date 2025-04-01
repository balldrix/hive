#pragma once

#include <map>
#include <string>

enum EnemyType
{
	Normal,
	Ranged,
	Runner,
	Boss
};

typedef std::map<std::string, float> DamageMap;

struct EnemyDefinition
{
	std::string id = {};
	EnemyType enemyType = {};
	std::string spritesheetDataPath = {};
	std::string textureId = {};
	std::string shadowId = {};
	std::string hitBoxDataPath = {};
	DamageMap damageMap = {};
	unsigned int hp = {};
	float walkSpeed = {};
	float runningSpeed = {};
	float acceleration = {};
	float deceleration = {};
	float thinkingTime = {};
	float hostileRange = {};
	float fightRange = {};
	float attackRange = {};
	float chargeRange = {};
	float chargeSpeed = {};
};