#pragma once

#include "AnimationData.h"
#include "SpriteFrameData.h"

#include <directxtk/SimpleMath.h>
#include <nlohmann/json.hpp>
#include <vector>

struct AnimatedSpriteData
{
	std::vector<SpriteFrameData> spriteFrameData;
	std::vector<AnimationData> animationData;
	Vector2 origin;

	AnimatedSpriteData() = default;
};

namespace nlohmann 
{
	static inline void from_json(const json& j, AnimatedSpriteData& a)
	{
		a.spriteFrameData = j.at("frames").get<std::vector<SpriteFrameData>>();

		json m = j["meta"];
		a.animationData = m["frameTags"].get<std::vector<AnimationData>>();

		if(m.contains("origin") && m.at("origin").contains("x") && m.at("origin").contains("y"))
		{
			a.origin.x = m.at("origin").at("x");
			a.origin.y = m.at("origin").at("y");
		}
		else
		{
			a.origin.x = 0;
			a.origin.y = 0;
		}
	}
}