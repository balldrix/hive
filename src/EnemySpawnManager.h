#pragma once

#include "TilemapData.h"

#include <list>
#include <vector>

class EnemySpawner;

class EnemySpawnManager
{
public:
	EnemySpawnManager();
	~EnemySpawnManager();

	void Init();
	void Update(float deltaTime);

private:
	void CreateSpawners(const std::vector<MapObjectData>& mapObjectData);
	std::list<EnemySpawner*> m_spawners;
};