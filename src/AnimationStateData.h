#pragma once

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

struct AnimationStateData
{
	std::string	name = {};
	unsigned int from = {};
	unsigned int to = {};
	bool loop = {};
	unsigned int frameCount = 1;
	unsigned int endXPos = 0;

	AnimationStateData() = default;
};

namespace nlohmann 
{
	static inline void from_json(const json& j, AnimationStateData& a)
	{
		a.name = j.at("name");
		a.from = j.at("from");
		a.to = j.at("to");
		a.loop = true;

		if(j.contains("repeat"))
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