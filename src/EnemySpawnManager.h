#pragma once

#include "TilemapData.h"

#include <list>
#include <string>
#include <vector>

class EnemySpawner;

class EnemySpawnManager
{
public:
	EnemySpawnManager();
	~EnemySpawnManager();

	void Init();
	void Update(float deltaTime);
	EnemySpawner* GetSpawner(std::string id);

private:
	void CreateSpawners(const std::vector<MapObjectData>& mapObjectData);
	std::list<EnemySpawner*> m_spawners;
};