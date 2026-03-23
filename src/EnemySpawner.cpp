#include "EnemySpawner.h"

#include "NPCManager.h"

#include <fmt/core.h>
#include <string>
#include <string.h>

const float seconds = 60.0f;
const float retryDelaySeconds = 1.0f;
const int ambientNormalEnemyCap = 3;

EnemySpawner::EnemySpawner() :
	m_id(),
	m_type(),
	m_currentWaveId(),
	m_spawnRate(0.0f),
	m_timer(0.0f),
	m_height(0.0f),
	m_maxSpawns(0),
	m_spawnCount(0),
	m_isOneShot(false),
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
	m_isOneShot = m_spawnRate <= 0.0f;
	m_height = spawnData.height;
	m_startingVelocity = spawnData.startingVelocity;
	m_facingDirection = spawnData.direction;
	m_timer = m_isOneShot ? 0.0f : seconds / m_spawnRate;
	m_maxSpawns = spawnData.maxSpawns;
	if(m_type == "ambient") m_active = true;
}

void EnemySpawner::Update(float deltaTime)
{
	if(!m_active) return;
	if(m_spawnCount >= m_maxSpawns) return;

	if(m_timer > 0.0f)
	{
		m_timer -= deltaTime;
		if(m_timer > 0.0f)
		{
			return;
		}
	}

	if(!Spawn())
	{
		m_timer = retryDelaySeconds;
		return;
	}

	if(m_isOneShot)
	{
		if(m_spawnCount >= m_maxSpawns)
		{
			m_active = false;
		}
		return;
	}

	m_timer = seconds / m_spawnRate;
}

bool EnemySpawner::Spawn()
{
	std::string spawnId = ExtractSpawnId(m_id);
	std::string uniqueId = ExtractSpawnerId(m_id);
	const bool isAmbientNormalSpawner = !spawnId.empty() &&
		spawnId.front() == 'A' &&
		m_enemyDefinition.enemyType == EnemyType::Normal;

	if(isAmbientNormalSpawner &&
		NPCManager::Instance()->GetAliveEnemyCountByWavePrefix('A', EnemyType::Normal) >= ambientNormalEnemyCap)
	{
		return false;
	}

	std::string npcId = fmt::format("{0}-{1}_{2}", m_enemyDefinition.id, uniqueId, m_spawnCount);
	m_currentWaveId = fmt::format("{0}_{1}", spawnId, m_spawnCount);
	NPCManager::Instance()->SpawnNPC(npcId,
		m_currentWaveId,
		m_spawnPosition,
		m_enemyDefinition,
		m_startingVelocity,
		m_facingDirection,
		m_height);
	m_spawnCount++;
	return true;
}

std::string EnemySpawner::ExtractSpawnId(const std::string& spawnerId)
{
	constexpr const char* prefix = "spawner_";
	const size_t start = strlen(prefix);
	const size_t lastUnderscore = spawnerId.find_last_of('_');
	return spawnerId.substr(start, lastUnderscore - start);
}

std::string EnemySpawner::ExtractSpawnerId(const std::string& spawnerId)
{
	constexpr const char* prefix = "spawner_";
	const size_t start = strlen(prefix);
	return spawnerId.substr(start);
}
