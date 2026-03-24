#pragma once

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

enum class AttackEffect
{
	None,
	Stun,
	Knockback
};

inline AttackEffect AttackEffectFromString(const std::string& effectName)
{
	if(effectName == "stun")
	{
		return AttackEffect::Stun;
	}

	if(effectName == "knockback")
	{
		return AttackEffect::Knockback;
	}

	return AttackEffect::None;
}

struct DamageData
{
	std::string name = {};
	int amount = {};
	float hitStopDuration = {};
	AttackEffect attackEffect = AttackEffect::None;
	float effectDuration = {};
	float knockbackForce = {};
	int knockbackCount = {};
};

namespace nlohmann
{
	static inline void from_json(const json& j, DamageData& damageData)
	{
		damageData.name = j.at("name");
		damageData.amount = j.at("value");
		damageData.hitStopDuration = j.value("hitStop", 0.0f);
		damageData.attackEffect = AttackEffectFromString(j.value("effect", std::string("none")));
		damageData.effectDuration = j.value("effectDuration", 0.0f);
		damageData.knockbackForce = j.value("knockbackForce", 0.0f);
		damageData.knockbackCount = j.value("knockbackCount", 0);
	}
}
