#pragma once

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

struct DamageData
{
	std::string name = {};
	int amount = {};
	float hitStopDuration = {};
};

namespace nlohmann
{
	static inline void from_json(const json& j, DamageData& damageData)
	{
		damageData.name = j.at("name");
		damageData.amount = j.at("value");
		damageData.hitStopDuration = j.at("hitStop");
	}
}