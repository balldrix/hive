#pragma once

#include "EventManager.h"

#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <variant>

using json = nlohmann::json;

struct AnimationEventData
{
	std::string eventName = {};
	unsigned int frameNumber = {};
	EventArgument argument;

	AnimationEventData() = default;
};

namespace nlohmann
{
	static inline void from_json(const json& j, AnimationEventData& eventData)
	{
		if(!j.contains("data")) return;

		eventData.frameNumber = j.at("frame");

		std::string dataString = j.at("data");
		size_t colonPos = dataString.find(":");
		size_t commaPos = dataString.find(",");

		if(colonPos != std::string::npos)
		{
			eventData.eventName = dataString.substr(colonPos + 1, commaPos - colonPos - 1);
			eventData.eventName.erase(0, eventData.eventName.find_first_not_of(" \t"));
		}

		if(commaPos != std::string::npos)
		{
			std::string argString = dataString.substr(commaPos + 1);
			argString.erase(0, argString.find_first_not_of(" \t"));

			try
			{
				eventData.argument = std::stof(argString);
			}
			catch(const std::invalid_argument&)
			{
				eventData.argument = argString;
			}
		}
	}
}