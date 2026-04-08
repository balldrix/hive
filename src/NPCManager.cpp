#include "NPCManager.h"

#include "Camera.h"
#include "CutsceneManager.h"
#include "Enemy.h"
#include "EnemyDefinition.h"
#include "EventManager.h"
#include "GameDataManager.h"
#include "GameObject.h"
#include "Graphics.h"
#include "IEvent.h"
#include "NPCFactory.h"
#include "Player.h"
#include "SpawnNPCEvent.h"

#include <algorithm>
#include <directxtk/SimpleMath.h>
#include <limits>
#include <string>
#include <vector>

using namespace DirectX::SimpleMath;

NPCManager* NPCManager::s_instance = nullptr;

NPCManager::NPCManager() :
	m_NPCFactory(nullptr),
	m_player(nullptr),
	m_eventManager(nullptr),
	m_cutsceneManager(nullptr)
{
	m_enemyList.clear();
}

NPCManager::~NPCManager()
{
	s_instance = nullptr;

	DeleteAll();
}

bool NPCManager::HasWavePrefix(const std::string& waveId, char wavePrefix)
{
	return !waveId.empty() && waveId.front() == wavePrefix;
}

void NPCManager::Init(Camera* camera, Player* player, CutsceneManager* cutsceneManager, EventManager* eventManager, ProjectileManager* projectileManager)
{
	s_instance = this;

	m_player = player;
	m_NPCFactory = new NPCFactory();
	m_NPCFactory->Init(camera, player, cutsceneManager, eventManager, projectileManager);
	m_eventManager = eventManager;
	m_cutsceneManager = cutsceneManager;
	RegisterEvents();
}

void NPCManager::SpawnNPC(std::string id, std::string waveId, const Vector2& position, const EnemyDefinition& enemyDefinition, const Vector2& velocity, const Vector2& direction, float height)
{
	Enemy* enemy = nullptr;

	auto& enemyList = s_instance->m_enemyList;
	for(auto it = enemyList.begin(); it != enemyList.end(); ++it)
	{
		std::string definitionId = (*it)->GetData().id;
		bool isActive = (*it)->IsActive();
		if(definitionId != enemyDefinition.id || isActive) continue;

		enemy = (*it);
		break;
	}

	if(enemy == nullptr)
	{
		enemy = s_instance->m_NPCFactory->GetEnemy(id, enemyDefinition);
		s_instance->m_enemyList.push_back(enemy);
		if(enemyDefinition.id.contains("boss"))
			m_boss = enemy;
	}

	enemy->Reset(id);
	enemy->Spawn(position, waveId);
	enemy->SetPlayerTarget(m_player);
	enemy->SetVelocity(velocity);
	enemy->FlipHorizontally(direction != Vector2::UnitX);
	
	if(height > 0)
	{
		enemy->SetPositionY(-height);
		enemy->SetGrounded(false);
	}
}

void NPCManager::SpawnNPC(SpawnNPCArgument argument)
{
	SpawnNPC(argument.id, "", argument.position, GameDataManager::GetEnemyDefinition(argument.definitionId));
}

void NPCManager::Render(Graphics* graphics)
{
	for(size_t i = 0; i < m_enemyList.size(); i++)
	{
		m_enemyList[i]->Render(graphics);
	}
}

void NPCManager::Update(float deltaTime)
{
	for(size_t i = 0; i < m_enemyList.size(); i++)
	{
		m_enemyList[i]->Update(deltaTime);
	}
}

void NPCManager::Reset()
{
	for(size_t i = 0; i < m_enemyList.size(); i++)
	{
		Enemy* enemy = m_enemyList[i];
		enemy->Reset(enemy->GetID());
	}

	m_hostileEnemyList.clear();
	m_previousHostilesByWave.clear();
}

void NPCManager::DeleteAll()
{
	m_boss = nullptr;

	for(const Enemy* i : m_enemyList)
	{
		delete i;
		i = nullptr;
	}

	m_enemyList.clear();
	m_hostileEnemyList.clear();
	m_previousHostilesByWave.clear();
	
	delete m_NPCFactory;

	m_NPCFactory = nullptr;
}

void NPCManager::SetNextAttackingEnemy(const std::string& waveId)
{
	if(waveId.empty())
	{
		return;
	}

	CleanupHostileEnemyList();

	float closestDistance = std::numeric_limits<float>::max();
	Enemy* newHostile = nullptr;
	WaveHostileHistory& waveHistory = GetOrCreateWaveHistory(waveId);

	for(Enemy* enemy : m_enemyList)
	{
		if(!IsEligibleHostileEnemy(enemy) || enemy->GetWaveId() != waveId)
		{
			continue;
		}

		if(std::find(waveHistory.recentHostiles.begin(), waveHistory.recentHostiles.end(), enemy) != waveHistory.recentHostiles.end())
		{
			continue;
		}

		float distance = Vector2::DistanceSquared(enemy->GetPosition(), m_player->GetPosition());

		if(distance >= closestDistance) continue;

		closestDistance = distance;
		newHostile = enemy;
	}

	if(newHostile)
	{
		waveHistory.recentHostiles.push_back(newHostile);
		if(waveHistory.recentHostiles.size() > 3)
		{
			waveHistory.recentHostiles.erase(waveHistory.recentHostiles.begin());
		}

		SetAttackingEnemy(newHostile);
		return;
	}

	waveHistory.recentHostiles.clear();

	for(Enemy* enemy : m_enemyList)
	{
		if(!IsEligibleHostileEnemy(enemy) || enemy->GetWaveId() != waveId)
		{
			continue;
		}

		float distance = Vector2::DistanceSquared(enemy->GetPosition(), m_player->GetPosition());

		if(distance >= closestDistance)
		{
			continue;
		}

		closestDistance = distance;
		newHostile = enemy;
	}

	if(newHostile != nullptr)
	{
		waveHistory.recentHostiles.push_back(newHostile);
		SetAttackingEnemy(newHostile);
		return;
	}

	ClearAttackingEnemy(waveId);
}

void NPCManager::SetAttackingEnemy(Enemy* enemy)
{
	if(!IsEligibleHostileEnemy(enemy))
	{
		return;
	}

	CleanupHostileEnemyList();

	for(auto it = m_hostileEnemyList.begin(); it != m_hostileEnemyList.end(); ++it)
	{
		if((*it)->GetWaveId() == enemy->GetWaveId())
		{
			*it = enemy;
			return;
		}
	}

	m_hostileEnemyList.push_back(enemy);
}

void NPCManager::SetNextAttackingEnemy(Enemy* enemy)
{
	if(enemy == nullptr)
	{
		return;
	}

	SetNextAttackingEnemy(enemy->GetWaveId());
}

Enemy* NPCManager::GetAttackingEnemy(const std::string& waveId) const
{
	if(waveId.empty())
	{
		return nullptr;
	}

	for(Enemy* enemy : m_hostileEnemyList)
	{
		if(enemy == nullptr || enemy->GetWaveId() != waveId)
		{
			continue;
		}

		if(IsEligibleHostileEnemy(enemy))
		{
			return enemy;
		}
	}

	return nullptr;
}

bool NPCManager::IsAttackingEnemy(const Enemy* enemy) const
{
	if(enemy == nullptr)
	{
		return false;
	}

	return GetAttackingEnemy(enemy->GetWaveId()) == enemy;
}

bool NPCManager::IsWaveDead(std::string waveId)
{
	if(waveId.empty()) return true;

	for(auto& enemy : m_enemyList)
	{
		if(!enemy->IsActive()) continue;
		if(enemy->GetWaveId() == waveId && !enemy->IsDead()) return false;
	}

	return true;
}

int NPCManager::GetAliveEnemyCountByWavePrefix(char wavePrefix, EnemyType enemyType) const
{
	int count = 0;

	for(const Enemy* enemy : m_enemyList)
	{
		if(enemy == nullptr || !enemy->IsActive() || enemy->IsDead())
		{
			continue;
		}

		if(enemy->GetData().enemyType != enemyType)
		{
			continue;
		}

		if(!HasWavePrefix(enemy->GetWaveId(), wavePrefix))
		{
			continue;
		}

		count++;
	}

	return count;
}

void NPCManager::RegisterEvents()
{
	m_eventManager->RegisterEvent("SpawnNPC", "NPCManager", new SpawnNPCEvent(this));
}

void NPCManager::CleanupHostileEnemyList()
{
	m_hostileEnemyList.erase(
		std::remove_if(m_hostileEnemyList.begin(), m_hostileEnemyList.end(),
			[this](Enemy* enemy)
			{
				return !IsEligibleHostileEnemy(enemy);
			}),
		m_hostileEnemyList.end());

	CleanupWaveHistory();
}

bool NPCManager::IsEligibleHostileEnemy(const Enemy* enemy) const
{
	if(enemy == nullptr || enemy->IsDead() || !enemy->IsActive())
	{
		return false;
	}

	const EnemyType enemyType = enemy->GetData().enemyType;
	if(enemyType == EnemyType::Ranged || enemyType == EnemyType::Boss)
	{
		return false;
	}

	return !enemy->GetWaveId().empty();
}

NPCManager::WaveHostileHistory* NPCManager::FindWaveHistory(const std::string& waveId)
{
	for(auto& history : m_previousHostilesByWave)
	{
		if(history.waveId == waveId)
		{
			return &history;
		}
	}

	return nullptr;
}

const NPCManager::WaveHostileHistory* NPCManager::FindWaveHistory(const std::string& waveId) const
{
	for(const auto& history : m_previousHostilesByWave)
	{
		if(history.waveId == waveId)
		{
			return &history;
		}
	}

	return nullptr;
}

NPCManager::WaveHostileHistory& NPCManager::GetOrCreateWaveHistory(const std::string& waveId)
{
	WaveHostileHistory* history = FindWaveHistory(waveId);
	if(history != nullptr)
	{
		return *history;
	}

	m_previousHostilesByWave.push_back({ waveId, {} });
	return m_previousHostilesByWave.back();
}

void NPCManager::CleanupWaveHistory()
{
	for(auto historyIt = m_previousHostilesByWave.begin(); historyIt != m_previousHostilesByWave.end();)
	{
		auto& recentHostiles = historyIt->recentHostiles;
		recentHostiles.erase(
			std::remove_if(recentHostiles.begin(), recentHostiles.end(),
				[this](Enemy* enemy)
				{
					return std::find(m_enemyList.begin(), m_enemyList.end(), enemy) == m_enemyList.end() ||
						!IsEligibleHostileEnemy(enemy);
				}),
			recentHostiles.end());

		if(historyIt->waveId.empty() || recentHostiles.empty())
		{
			historyIt = m_previousHostilesByWave.erase(historyIt);
			continue;
		}

		++historyIt;
	}
}

void NPCManager::ClearAttackingEnemy(const std::string& waveId)
{
	for(auto it = m_hostileEnemyList.begin(); it != m_hostileEnemyList.end(); ++it)
	{
		if((*it)->GetWaveId() == waveId)
		{
			m_hostileEnemyList.erase(it);
			break;
		}
	}
}
