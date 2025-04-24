#pragma once

#include "DamageData.h"
#include "Logger.h"

#include <fmt/core.h>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <unordered_map>
#include <vector>

using json = nlohmann::json;

enum EnemyType
{
	Normal,
	Falling,
	Ranged,
	Runner,
	Boss
};

inline const std::unordered_map<std::string, EnemyType>& GetEnemyTypeMap() {
	static const std::unordered_map<std::string, EnemyType> map = {
		{"normal", EnemyType::Normal},
		{"falling", EnemyType::Falling},
		{"ranged", EnemyType::Ranged},
		{"runner", EnemyType::Runner},
		{"boss", EnemyType::Boss},
	};
	return map;
}

inline EnemyType StringToEnemyType(const std::string& str) {
	const auto& map = GetEnemyTypeMap();
	auto it = map.find(str);
	if(it != map.end()) {
		return it->second;
	}

	Logger::LogError(fmt::format("Invalid EnemyType string: {0}", str));
	return EnemyType::Normal;
}

inline std::string EnemyTypeToString(EnemyType type) {
	for(const auto& pair : GetEnemyTypeMap()) {
		if(pair.second == type) {
			return pair.first;
		}
	}

	Logger::LogError("Invalid EnemyType");
	return "unknown";
}

struct EnemyDefinition
{
	std::string id = {};
	EnemyType enemyType = {};
	std::string spritesheetDataPath = {};
	std::string textureId = {};
	std::string shadowId = {};
	std::string hitBoxDataPath = {};
	std::vector<DamageData> damageData = {};
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

namespace nlohmann 
{
	static inline void from_json(const json& j, EnemyDefinition& enemyDefinition) {
		enemyDefinition.id = j.at("id");
		enemyDefinition.enemyType = StringToEnemyType(j.at("enemyType"));
		enemyDefinition.spritesheetDataPath = j.at("spritesheetDataPath");
		enemyDefinition.textureId = j.at("textureId");
		enemyDefinition.shadowId = j.at("shadowId");
		enemyDefinition.hitBoxDataPath = j.at("hitBoxDataPath");
		enemyDefinition.damageData = j.at("damageData").get<std::vector<DamageData>>();
		enemyDefinition.hp = j.at("hp");
		enemyDefinition.walkSpeed = j.at("walkSpeed");
		enemyDefinition.runningSpeed = j.at("runningSpeed");
		enemyDefinition.acceleration = j.at("acceleration");
		enemyDefinition.deceleration = j.at("deceleration");
		enemyDefinition.thinkingTime = j.at("thinkingTime");
		enemyDefinition.hostileRange = j.at("hostileRange");
		enemyDefinition.fightRange = j.at("fightRange");
		enemyDefinition.attackRange = j.at("attackRange");
		enemyDefinition.chargeRange = j.at("chargeRange");
		enemyDefinition.chargeSpeed = j.at("chargeSpeed");
	}
}