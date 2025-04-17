#pragma once

#include "AnimationData.h"
#include "SpriteFrameData.h"

#include <directxtk/SimpleMath.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <vector>

using json = nlohmann::json;

struct AnimatedSpriteData
{
	std::vector<SpriteFrameData> spriteFrameData;
	std::vector<AnimationData> animationData;
	Vector2 origin;

	AnimatedSpriteData() = default;
};

inline void from_json(const json& j, AnimatedSpriteData& a)
{
	a.spriteFrameData = j["frames"].get<std::vector<SpriteFrameData>>();

	json m = j["meta"];
	a.animationData = m["frameTags"].get<std::vector<AnimationData>>();

	if(m.contains("origin") && m["origin"].contains("x") && m["origin"].contains("y")) 
	{
		a.origin.x = m["origin"]["x"];
		a.origin.y = m["origin"]["y"];
	}
	else 
	{
		a.origin.x = 0;
		a.origin.y = 0;
	}
}