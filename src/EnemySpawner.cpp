#include "EnemySpawner.h"

#include "Logger.h"
#include "NPCManager.h"

const float seconds = 60.0f;

EnemySpawner::EnemySpawner() :
	m_spawnRate(0.0f),
	m_timer(0.0f),
	m_height(0.0f),
	m_maxSpawns(0),
	m_spawnCount(0)
{
}

void EnemySpawner::Init(const SpawnData& spawnData)
{
	Logger::LogInfo("Initialising EnemySpawner.");

	m_spawnPosition = spawnData.spawnPosition;
	m_enemyDefinition = spawnData.enemyDefinition;
	m_spawnRate = spawnData.spawnRate;
	m_height = spawnData.height;
	m_startingVelocity = spawnData.startingVelocity;
	m_timer = m_spawnRate == -1 ? 0 : seconds / m_spawnRate;
	m_maxSpawns = spawnData.maxSpawns;
}

void EnemySpawner::Update(float deltaTime)
{
	if(m_spawnCount >= m_maxSpawns) return;

	m_timer -= deltaTime;

	if(m_timer <= 0)
	{
		m_timer = seconds / m_spawnRate;
		Spawn();
	}
}

void EnemySpawner::Spawn()
{
	NPCManager::Instance()->SpawnNPC(
		m_spawnPosition,
		m_enemyDefinition,
		m_startingVelocity,
		m_facingDirection,
		m_height);
	m_spawnCount++;
}
