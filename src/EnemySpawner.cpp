#include "EnemySpawner.h"

#include "NPCManager.h"

#include <fmt/core.h>
#include <string>
#include <string.h>

const float seconds = 60.0f;

EnemySpawner::EnemySpawner() :
	m_id(),
	m_type(),
	m_currentWaveId(),
	m_spawnRate(0.0f),
	m_timer(0.0f),
	m_height(0.0f),
	m_maxSpawns(0),
	m_spawnCount(0),
	m_active(false)
{
}

void EnemySpawner::Init(const SpawnData& spawnData)
{
	m_id = spawnData.id;
	m_type = spawnData.type;
	m_spawnPosition = spawnData.spawnPosition;
	m_enemyDefinition = spawnData.enemyDefinition;
	m_spawnRate = spawnData.spawnRate;
	m_height = spawnData.height;
	m_startingVelocity = spawnData.startingVelocity;
	m_timer = m_spawnRate == -1 ? 0 : seconds / m_spawnRate;
	m_maxSpawns = spawnData.maxSpawns;
	if(m_type == "ambient") m_active = true;
}

void EnemySpawner::Update(float deltaTime)
{
	if(!m_active) return;
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
	std::string npcId = fmt::format("{0}_{1}", m_enemyDefinition.id, m_spawnCount);
	std::string spawnId = ExtractSpawnId(m_id);
	m_currentWaveId = fmt::format("{0}_{1}", spawnId, m_spawnCount);
	NPCManager::Instance()->SpawnNPC(npcId,
		m_currentWaveId,
		m_spawnPosition,
		m_enemyDefinition,
		m_startingVelocity,
		m_facingDirection,
		m_height);
	m_spawnCount++;
}

std::string EnemySpawner::ExtractSpawnId(const std::string& spawnerId)
{
	constexpr const char* prefix = "spawner_";
	const size_t start = strlen(prefix);
	const size_t lastUnderscore = spawnerId.find_last_of('_');
	return spawnerId.substr(start, lastUnderscore - start);
}
