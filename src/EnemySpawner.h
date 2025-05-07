#pragma once

#include "EnemyDefinition.h"

#include <directxtk/SimpleMath.h>

using namespace DirectX::SimpleMath;

struct SpawnData
{
	EnemyDefinition enemyDefinition = {};
	Vector2 spawnPosition = {};
	float spawnRate = {};
	float height = {};
	Vector2 startingVelocity = {};
	int maxSpawns = {};
	Vector2 direction = {};
};

class EnemySpawner
{
public:
	EnemySpawner();
	~EnemySpawner() = default;

	void Init(const SpawnData& spawnData);
	void Update(float deltaTime);

private:
	void Spawn();

	EnemyDefinition m_enemyDefinition;
	Vector2 m_spawnPosition;
	Vector2 m_startingVelocity;
	Vector2 m_facingDirection;
	float m_height;
	float m_spawnRate;
	float m_timer;
	int m_maxSpawns;
	int m_spawnCount;
};