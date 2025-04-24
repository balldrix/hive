#include "NPCManager.h"

#include "Enemy.h"
#include "EnemyDefinition.h"
#include "GameObject.h"
#include "Graphics.h"
#include "NPCFactory.h"
#include "Player.h"

#include <directxtk/SimpleMath.h>
#include <string>

using namespace DirectX::SimpleMath;

NPCManager* NPCManager::s_instance = nullptr;

NPCManager::NPCManager() :
	m_NPCFactory(nullptr),
	m_hostileEnemy(nullptr),
	m_player(nullptr)
{
	m_enemyList.clear();
}

NPCManager::~NPCManager()
{
	s_instance = nullptr;

	DeleteAll();
}

void NPCManager::Init(Graphics* graphics, Camera* camera, Player* player)
{
	s_instance = this;

	m_player = player;
	m_NPCFactory = new NPCFactory();
}

void NPCManager::SpawnNPC(const Vector2& position, const EnemyDefinition& enemyDefinition, const Vector2& velocity, float height)
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
	for (const Enemy* i : m_enemyList)
	{
		delete i;
		i = nullptr;
	}

	m_enemyList.clear();
	
	delete m_NPCFactory;

	m_NPCFactory = nullptr;
}

void NPCManager::SetAttackingEnemy(Enemy* enemy)
{
	m_hostileEnemy = enemy;
}
