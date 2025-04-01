#pragma once

#include "EnemyDefinition.h"

#include <directxtk/SimpleMath.h>
#include <vector>

using namespace DirectX::SimpleMath;

struct SpawnData
{
	EnemyDefinition enemyDefinition = {};
	Vector2 spawnPosition = {};
	float spawnRate = {};
	float height = {};
	Vector2 startingVelocity = {};
};

class EnemySpawner
{
public:
	EnemySpawner();
	~EnemySpawner() = default;

	void Init(const SpawnData& spawnData);
	void Update(float deltaTime);
private:
	void Spawn() const;

	EnemyDefinition m_enemyDefinition;
	Vector2 m_spawnPosition;
	Vector2 m_startingVelocity;
	float m_height;
	float m_spawnRate;
	float m_timer;
};