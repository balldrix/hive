#include "pch.h"

#pragma once

namespace
{
	struct Animation
	{
		std::string	name = {};
		unsigned int from = {};
		unsigned int to = {};
		bool loop = {};
		unsigned int frameCount = 1;

		Animation() = default;
	};

	void from_json(const json& j, Animation& a)
	{
		a.name = j.at("name").get<std::string>();
		a.from = j.at("from").get<unsigned int>();
		a.to = j.at("to").get<unsigned int>();
		a.loop = j.at("loop").get<bool>();

 		a.frameCount += a.to - a.from;
	}
}
