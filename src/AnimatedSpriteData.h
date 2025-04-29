#pragma once

#include "AnimationEventData.h"
#include "AnimationStateData.h"
#include "SpriteFrameData.h"

#include <nlohmann/json.hpp>
#include <vector>

struct AnimatedSpriteData
{
	std::vector<SpriteFrameData> spriteFrameData;
	std::vector<AnimationStateData> animationStateData;
	std::vector<AnimationEventData> animationEventData;

	AnimatedSpriteData() = default;
};

namespace nlohmann
{
    static inline void from_json(const json& j, AnimatedSpriteData& a)
    {
        a.spriteFrameData = j.at("frames").get<std::vector<SpriteFrameData>>();
        a.animationStateData = j.at("meta").at("frameTags").get<std::vector<AnimationStateData>>();

        if(!j.contains("meta") || !j.at("meta").contains("layers")) return;

        for(const auto& layer : j.at("meta").at("layers"))
        {
            if(!layer.contains("cels") || layer.at("cels").empty()) continue;

            for(const auto& cel : layer.at("cels"))
            {
                if(!cel.contains("data")) continue;

                a.animationEventData.emplace_back(cel.get<AnimationEventData>());
            }
        }
    }
}