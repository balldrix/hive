#include "GameDataManager.h"

#include "AnimatedSpriteData.h"
#include "CutsceneData.h"
#include "EnemyDefinition.h"
#include "HitBoxData.h"
#include "Logger.h"

#include <fmt/core.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <stdexcept>
#include <string>
#include <system_error>
#include <vector>

using json = nlohmann::json;

GameDataManager* GameDataManager::s_instance = nullptr;

void GameDataManager::Init()
{
	Logger::LogInfo("Initialising Game Data Manager.");

	s_instance = new GameDataManager();
}

void GameDataManager::Destroy()
{
	delete s_instance;
	s_instance = nullptr;
}

std::vector<CutsceneData> GameDataManager::LoadAllCutscenes(const std::string path)
{
	Logger::LogInfo(fmt::format("Loading cutscenes: {}.", path));

	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		file.open(path);
	}
	catch (std::system_error& e)
	{
		std::string message = fmt::format("[GameDataManager] [Cutscene] Failed to load cutscene data at {0}: {1}.",
			path,
			e.code().message());

		Logger::LogError(message);
		return std::vector<CutsceneData>();
	}

	json j = json::parse(file);
	return j.get<std::vector<CutsceneData>>();
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
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

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

void GameDataManager::LoadAllEnemyDefinitions()
{
	Logger::LogInfo("Loading all enemy definitions.");

	auto path = "assets\\data\\enemies\\enemyDefinitions.json";
	std::ifstream file;

	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		file.open(path);
	}
	catch(std::system_error& e)
	{
		std::string message = fmt::format("[GameDataManager] [EnemyDefiniton] Failed to load Enemy Definition data at {0}: {1}.",
			path,
			e.code().message());

		Logger::LogError(message);
		return;
	}

	json j = json::parse(file);
	s_instance->m_enemyDefinitions = j.get<std::vector<EnemyDefinition>>();
}

EnemyDefinition GameDataManager::GetEnemyDefinition(const std::string& id)
{
	for(const auto& def : s_instance->m_enemyDefinitions)
	{
		if(def.id == id) return def;
	}

	std::string message = fmt::format("[GameDataManager] [EnemyDefinition] No defintion with path {0} found.", id);
	Logger::LogError(message);
	throw std::runtime_error(message);
}
