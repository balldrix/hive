#include "CombatZone.h"

#include "EnemySpawner.h"
#include "EnemySpawnManager.h"
#include "NPCManager.h"

#include <directxtk/SimpleMath.h>
#include <string>
#include <utility>
#include <vector>

CombatZone::CombatZone() :
	m_id(),
	m_position(DirectX::SimpleMath::Vector2::Zero),
	m_spawnerIDs(),
	m_enemySpawnManager(nullptr),
	m_isActive(false)
{
}

CombatZone::~CombatZone()
{
}

void CombatZone::Init(
	std::string id,
	const DirectX::SimpleMath::Vector2& position,
	std::vector<std::string> spawners,
	EnemySpawnManager* enemySpawnManager,
	NPCManager* npcManager)
{
	m_id = id;
	m_position = position;
	m_spawnerIDs = std::move(spawners);
	m_enemySpawnManager = enemySpawnManager;
	m_NPCManager = npcManager;
}

void CombatZone::Activate()
{
	for(std::string id : m_spawnerIDs)
	{
		EnemySpawner* spawner = m_enemySpawnManager->GetSpawner(id);
		spawner->SetActive(true);
	}

	m_isActive = true;
}

void CombatZone::Deactivate()
{
	for(std::string id : m_spawnerIDs)
	{
		EnemySpawner* spawner = m_enemySpawnManager->GetSpawner(id);
		spawner->SetActive(false);
	}

	m_isActive = false;
}

bool CombatZone::IsSpawningComplete()
{
	for(const std::string& id : m_spawnerIDs)
	{
		EnemySpawner* spawner = m_enemySpawnManager->GetSpawner(id);

		if(spawner == nullptr) continue;
		if(spawner->GetType() != "combat") continue;

		if(!spawner->IsDoneSpawning() || !m_NPCManager->IsWaveDead(spawner->GetCurrentWaveId()))
		{
			return false;
		}
	}

	return true;
}
