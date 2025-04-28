#pragma once

#include "DamageData.h"

#include <directxtk/SimpleMath.h>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using namespace DirectX::SimpleMath;
using json = nlohmann::json;

struct PlayerDefinition
{
	std::string spritesheetDataPath = {};
	Vector2 spriteOrigin = {};
	std::string textureId = {};
	std::string shadowId = {};
	std::string hitBoxDataPath = {};
	unsigned int hp = {};
	float walkSpeed = {};
	float runningSpeed = {};
	float acceleration = {};
	float deceleration = {};
	float deathTime = {};
	float knockoutDuration = {};
	std::vector<DamageData> damageData = {};
};

namespace nlohmann
{
	static inline void from_json(const json& j, PlayerDefinition& playerDefinition)
	{
		playerDefinition.spritesheetDataPath = j.at("spritesheetDataPath");
		playerDefinition.spriteOrigin = Vector2(j.at("spriteOriginX"), j.at("spriteOriginY"));
		playerDefinition.textureId = j.at("textureId");
		playerDefinition.shadowId = j.at("shadowId");
		playerDefinition.hitBoxDataPath = j.at("hitBoxDataPath");
		playerDefinition.damageData = j.at("damageData").get<std::vector<DamageData>>();
		playerDefinition.hp = j.at("hp");
		playerDefinition.walkSpeed = j.at("walkSpeed");
		playerDefinition.runningSpeed = j.at("runningSpeed");
		playerDefinition.acceleration = j.at("acceleration");
		playerDefinition.deceleration = j.at("deceleration");
		playerDefinition.deathTime = j.at("death_time");
		playerDefinition.knockoutDuration = j.at("knockout_duration");
	}
}
