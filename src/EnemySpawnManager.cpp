#include "EnemySpawnManager.h"

#include "EnemyDefinition.h"
#include "EnemySpawner.h"
#include "GameDataManager.h"
#include "Logger.h"
#include "TilemapData.h"
#include "TilemapLoader.h"

#include <directxtk/SimpleMath.h>
#include <string>
#include <vector>

EnemySpawnManager::EnemySpawnManager()
{
}

EnemySpawnManager::~EnemySpawnManager()
{
	for(auto& spawner : m_spawners)
	{
		delete spawner;
		spawner = nullptr;
	}

	m_spawners.clear();
}

void EnemySpawnManager::Init()
{
	Logger::LogInfo("Initialising Enemy Spawn Manager");

	auto currentMap = TilemapLoader::GetCurrentMap();

	for(auto i = currentMap.layers.begin(); i != currentMap.layers.end(); i++)
	{
		if(i->name == "spawners")
		{
			CreateSpawners(i->objectData);
		}
	}
}

void EnemySpawnManager::Update(float deltaTime)
{
	for(const auto& spawner : m_spawners)
	{
		spawner->Update(deltaTime);
	}
}

EnemySpawner* EnemySpawnManager::GetSpawner(std::string id)
{
	for(auto* spawner : m_spawners)
	{
		if(spawner->GetId() == id) return spawner;
	}

	return nullptr;
}

void EnemySpawnManager::CreateSpawners(const std::vector<MapObjectData>& mapObjectData)
{
	for(const auto& mapObj : mapObjectData)
	{
		EnemySpawner* enemySpawner = new EnemySpawner();

		std::string defId = mapObj.customProperties.at("enemyDefinitionId");

		SpawnData data;
		data.id = mapObj.name;
		data.type = mapObj.type;
		data.enemyDefinition = GameDataManager::GetEnemyDefinition(defId);
		data.spawnRate = std::stof(mapObj.customProperties.at("spawnRate"));
		data.spawnPosition = Vector2(mapObj.x, mapObj.y);
		data.height = std::stof(mapObj.customProperties.at("height"));
		data.startingVelocity = Vector2(
			std::stof(mapObj.customProperties.at("startingVelocityX")),
			std::stof(mapObj.customProperties.at("startingVelocityY"))
		);
		data.direction = mapObj.customProperties.at("facing") == "left" ? -Vector2::UnitX : Vector2::UnitX;
		data.maxSpawns = std::stoi(mapObj.customProperties.at("maxSpawns"));

		enemySpawner->Init(data);
		m_spawners.push_back(enemySpawner);
	}
}
