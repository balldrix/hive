// Animation.h
// Christopher Ball 2018
// animation frame data

#include "pch.h"

#ifndef _ANIMATION_H_
#define _ANIMATION_H_

namespace
{
	struct Animation
	{
		std::string	name = {};
		int spriteSheetIndex = {};
		int frameCount = {};
		int framesPerSecond = {};
		bool loop = {};

		Animation() = default;
	};

	void from_json(const json& j, Animation& a)
	{
		a.name = j.at("name").get<std::string>();
		a.spriteSheetIndex = j.at("index").get<int>();
		a.frameCount = j.at("frameCount").get<int>();
		a.framesPerSecond = j.at("framesPerSecond").get<int>();
		a.loop = j.at("loop").get<bool>();
	}
}

#endif // !_ANIMATION_H_
