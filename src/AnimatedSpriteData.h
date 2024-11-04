#pragma once

#include "AnimationData.h"
#include "SpriteFrameData.h"

#include <nlohmann/json.hpp>
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

	a.origin.x = m["origin"].at("x");
	a.origin.y = m["origin"].at("y");
}