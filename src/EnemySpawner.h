#pragma once

#include "EnemyDefinition.h"

#include <directxtk/SimpleMath.h>
#include <string>

using namespace DirectX::SimpleMath;

struct SpawnData
{
	std::string id = {};
	std::string type = {};
	EnemyDefinition enemyDefinition = {};
	Vector2 spawnPosition = {};
	float spawnRate = {};
	float height = {};
	Vector2 startingVelocity = {};
	int maxSpawns = {};
	Vector2 direction = {};
	std::string mode = {};
};

class EnemySpawner
{
public:
	EnemySpawner();
	~EnemySpawner() = default;

	void Init(const SpawnData& spawnData);
	void Update(float deltaTime);
	void SetActive(bool active) { m_active = active; }
	std::string GetId() const { return m_id; }
	std::string GetType() const { return m_type; }
	std::string GetCurrentWaveId() const { return m_currentWaveId; }
	bool IsDoneSpawning() const { return m_spawnCount >= m_maxSpawns; }

private:
	void Spawn();
	std::string ExtractSpawnId(const std::string& spawnerId);

	std::string m_id;
	std::string m_type;
	std::string m_currentWaveId;
	EnemyDefinition m_enemyDefinition;
	Vector2 m_spawnPosition;
	Vector2 m_startingVelocity;
	Vector2 m_facingDirection;
	float m_height;
	float m_spawnRate;
	float m_timer;
	int m_maxSpawns;
	int m_spawnCount;
	bool m_active;
};