#include "NPCManager.h"

#include "Camera.h"
#include "Enemy.h"
#include "EnemyDefinition.h"
#include "EventManager.h"
#include "GameDataManager.h"
#include "GameObject.h"
#include "Graphics.h"
#include "Logger.h"
#include "NPCFactory.h"
#include "Player.h"

#include <directxtk/SimpleMath.h>
#include <limits>
#include <string>
#include <variant>
#include <vector>

using namespace DirectX::SimpleMath;

NPCManager* NPCManager::s_instance = nullptr;

NPCManager::NPCManager() :
	m_NPCFactory(nullptr),
	m_hostileEnemy(nullptr),
	m_player(nullptr),
	m_eventManager(nullptr)
{
	m_enemyList.clear();
}

NPCManager::~NPCManager()
{
	s_instance = nullptr;

	DeleteAll();
}

void NPCManager::Init(Camera* camera, Player* player)
{
	s_instance = this;

	m_player = player;
	m_NPCFactory = new NPCFactory();
	m_NPCFactory->Init(camera, player);
	m_eventManager = new EventManager();
	RegisterEvents();
}

void NPCManager::SpawnNPC(const Vector2& position, const EnemyDefinition& enemyDefinition, const Vector2& velocity, const Vector2& direction, float height)
{
	Enemy* enemy = nullptr;

	auto& enemyList = s_instance->m_enemyList;
	for(auto it = enemyList.begin(); it != enemyList.end(); ++it)
	{
		std::string id = (*it)->GetData().id;
		bool isActive = (*it)->IsActive();
		if(id != enemyDefinition.id || isActive) continue;

		enemy = (*it);
		break;
	}

	if(enemy == nullptr)
	{
		enemy = s_instance->m_NPCFactory->GetEnemy(enemyDefinition);
		s_instance->m_enemyList.push_back(enemy);
	}

	enemy->Spawn(position);
	enemy->SetPlayerTarget(m_player);
	enemy->SetVelocity(velocity);
	enemy->FlipHorizontally(direction != Vector2::UnitX);
	
	if(height > 0)
	{
		enemy->SetPositionY(-height);
		enemy->SetGrounded(false);
	}
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
		m_enemyList[i]->Reset();
	}
}

void NPCManager::DeleteAll()
{
	for(const Enemy* i : m_enemyList)
	{
		delete i;
		i = nullptr;
	}

	m_enemyList.clear();
	
	delete m_NPCFactory;

	m_NPCFactory = nullptr;
}

void NPCManager::SetNextAttackingEnemy()
{
	static std::vector<Enemy*> previousHostiles;

	float closestDistance = std::numeric_limits<float>::max();
	Enemy* newHostile = nullptr;

	for(Enemy* enemy : m_enemyList)
	{
		if(enemy == m_hostileEnemy || enemy->IsDead() || !enemy->IsActive()) continue;

		if(std::find(previousHostiles.begin(), previousHostiles.end(), enemy) != previousHostiles.end())
			continue;

		float distance = Vector2::DistanceSquared(enemy->GetPosition(), m_player->GetPosition());

		if(distance >= closestDistance) continue;

		closestDistance = distance;
		newHostile = enemy;
	}

	if(newHostile)
	{
		previousHostiles.push_back(newHostile);
		if(previousHostiles.size() > 3)
			previousHostiles.erase(previousHostiles.begin());

		m_hostileEnemy = newHostile;
	}

}

void NPCManager::SetAttackingEnemy(Enemy* enemy)
{
	m_hostileEnemy = enemy;
}

void NPCManager::RegisterEvents()
{
	m_eventManager->RegisterEvent("SpawnNPC", [this](EventArgument arg)
	{
		if(!std::holds_alternative<SpawnNPCArgument>(arg))
		{
			Logger::LogError("[NPCManager] [RegisterEvents] Incorrect argument for Spawn NPC, must be a SpawnEventArgument");
			return true;
		}

		SpawnNPCArgument spawnArgument = std::get<SpawnNPCArgument>(arg);
		SpawnNPC(spawnArgument.position, GameDataManager::GetEnemyDefinition(spawnArgument.definitionId));
		return true;
	});
}
