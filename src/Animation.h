#pragma once

#include "pch.h"

namespace
{
	struct Animation
	{
		std::string	name = {};
		unsigned int from = {};
		unsigned int to = {};
		bool loop = {};
		unsigned int frameCount = 1;
		unsigned int endXPos = 0;

		Animation() = default;
	};

	void from_json(const json& j, Animation& a)
	{
		a.name = j.at("name").get<std::string>();
		a.from = j.at("from").get<unsigned int>();
		a.to = j.at("to").get<unsigned int>();
		a.loop = true;
		
		if (j.contains("repeat"))
			a.loop = false;

 		a.frameCount += a.to - a.from;

		if(!j.contains("data"))
			return;

		std::string data = j.at("data").get<std::string>();
		std::string delimiter = "=";
		
		size_t pos = data.find(delimiter);
		std::string value = data.substr(pos + delimiter.length());

		a.endXPos = std::stoi(value);
	}
}
