#include "TilemapLoader.h"

#include "Logger.h"
#include "TilemapData.h"

#include <fmt/core.h>
#include <fstream>
#include <string>

TilemapLoader* TilemapLoader::s_instance = nullptr;

TilemapLoader::TilemapLoader()
{
}

void TilemapLoader::Init()
{
	s_instance = new TilemapLoader;
}

void TilemapLoader::Shutdown()
{
	delete s_instance;
	s_instance = nullptr;
}

void TilemapLoader::LoadTilemap(std::string path)
{
	Logger::LogInfo(fmt::format("Loading Tilemap Data: {}.", path));

	std::ifstream file(path);

	if(file.fail())
	{
		Logger::LogError(fmt::format("[AssetLoader] [Tilemap] Failed to load tile map at {0}.", path));
		return;
	}

	json data = json::parse(file);
	s_instance->m_tilemapData = data.get<TilemapData>();
}
