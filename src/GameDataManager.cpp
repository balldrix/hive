#include "GameDataManager.h"

#include "AnimatedSpriteData.h"
#include "HitBoxData.h"
#include "Logger.h"

#include <fmt/core.h>
#include <fstream>
#include <iosfwd>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <system_error>
#include <vector>

using json = nlohmann::json;

GameDataManager* GameDataManager::s_instance = nullptr;

void GameDataManager::Init()
{
	s_instance = new GameDataManager();
}

void GameDataManager::Shutdown()
{
	delete s_instance;
	s_instance = nullptr;
}

AnimatedSpriteData GameDataManager::LoadAnimatedSpriteData(std::string path)
{
	Logger::LogInfo(fmt::format("Loading Animated Sprite Data: {}.", path));

	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		file.open(path);
	}
	catch(std::system_error& e)
	{
		std::string message = fmt::format("[GameDataManager] [AnimatedSpriteData] Failed to load sprite data at {0}: {1}.",
			path,
			e.code().message());

		Logger::LogError(message);
		return AnimatedSpriteData();
	}

	json j = json::parse(file);
	return j.get<AnimatedSpriteData>();
}

std::vector<HitBoxData> GameDataManager::LoadHitboxData(std::string path)
{
	Logger::LogInfo(fmt::format("Loading Hitbox Data: {}.", path));

	std::ifstream file;

	try
	{
		file.open(path);
	}
	catch(std::system_error& e)
	{
		std::string message = fmt::format("[GameDataManager] [HitBoxData] Failed to load HitBox data at {0}: {1}.",
			path,
			e.code().message());

		Logger::LogError(message);
		return std::vector<HitBoxData>();
	}

	json j = json::parse(file);
	return j.get<std::vector<HitBoxData>>();
}
