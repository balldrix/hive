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

	AnimatedSpriteData() = default;
};

namespace nlohmann 
{
	static inline void from_json(const json& j, AnimatedSpriteData& a)
	{
		a.spriteFrameData = j.at("frames").get<std::vector<SpriteFrameData>>();

		json m = j["meta"];
		a.animationData = m["frameTags"].get<std::vector<AnimationData>>();
	}
}