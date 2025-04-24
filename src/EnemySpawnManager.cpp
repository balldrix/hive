#include "EnemySpawnManager.h"

#include "EnemyDefinition.h"
#include "EnemySpawner.h"
#include "GameDataManager.h"
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

void EnemySpawnManager::CreateSpawners(const std::vector<MapObjectData>& mapObjectData)
{
	for(const auto& mapObj : mapObjectData)
	{
		EnemySpawner* enemySpawner = new EnemySpawner();

		std::string defId = mapObj.customProperties.at("enemyDefinitionId");

		SpawnData data;
		data.enemyDefinition = GameDataManager::GetEnemyDefinition(defId);
		data.spawnRate = std::stof(mapObj.customProperties.at("spawnRate"));
		data.spawnPosition = Vector2(mapObj.x, mapObj.y);
		data.height = std::stof(mapObj.customProperties.at("height"));
		data.startingVelocity = Vector2(
			std::stof(mapObj.customProperties.at("startingVelocityX")),
			std::stof(mapObj.customProperties.at("startingVelocityY"))
		);

		enemySpawner->Init(data);
		m_spawners.push_back(enemySpawner);
	}
}
