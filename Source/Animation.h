#include "pch.h"

#pragma once

namespace
{
	struct Animation
	{
		std::string	name = {};
		int spritesheetIndex = {};
		int frameCount = {};
		int framesPerSecond = {};
		bool loop = {};

		Animation() = default;
	};

	void from_json(const json& j, Animation& a)
	{
		a.name = j.at("name").get<std::string>();
		a.spritesheetIndex = j.at("index").get<int>();
		a.frameCount = j.at("frameCount").get<int>();
		a.framesPerSecond = j.at("framesPerSecond").get<int>();
		a.loop = j.at("loop").get<bool>();
	}
}
