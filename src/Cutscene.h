#pragma once

#include "EventManager.h"
#include "Utils.h"

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

struct CutsceneEvent
{
	std::string name;
	std::string target;
	EventArgument arg;
	float delay = 0.0f;
	bool waitForCompletion = false;
};

struct CutsceneStep
{
	std::vector<CutsceneEvent> events;
	bool stepCompleted = false;
};

struct Cutscene
{
	std::string name;
	std::vector<CutsceneStep> steps;
};

namespace nlohmann
{
	static inline void from_json(const json& j, CutsceneEvent& e) {
		j.at("name").get_to(e.name);
		j.at("target").get_to(e.target);
		j.at("delay").get_to(e.delay);
		j.at("waitForCompletion").get_to(e.waitForCompletion);

		std::string argString;

		if(j.at("arg").is_string()) {
			argString = j.at("arg");
		}
		else if(j.at("arg").is_number()) {
			argString = std::to_string(j.at("arg").get<float>());
		}
		else {
			argString = j.at("arg").dump();
		}

		e.arg = Utils::ParseEventArgument(argString);
	}
	
	static inline void from_json(const json& j, CutsceneStep& s) {
		j.at("events").get_to(s.events);
	}

	static inline void from_json(const json& j, Cutscene& c)
	{
		j.at("name").get_to(c.name);
		j.at("steps").get_to(c.steps);
	}
}