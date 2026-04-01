#include "TriggerManager.h"

#include "AABB.h"
#include "CombatZoneManager.h"
#include "CutsceneManager.h"
#include "EnemySpawner.h"
#include "EnemySpawnManager.h"
#include "Logger.h"
#include "TilemapData.h"
#include "TilemapLoader.h"
#include "TriggerCollider.h"

#include <directxtk/SimpleMath.h>
#include <sstream>
#include <string>
#include <vector>

TriggerManager::TriggerManager() :
	m_combatZoneManager(nullptr),
	m_enemySpawnManager(nullptr),
	m_cutsceneManager(nullptr)
{
}

TriggerManager::~TriggerManager()
{
}

void TriggerManager::Init(CombatZoneManager* combatZoneManager, EnemySpawnManager* enemySpawnManager, CutsceneManager* cutsceneManager)
{
	Logger::LogInfo("Initialising Trigger Manager");

	m_combatZoneManager = combatZoneManager;
	m_enemySpawnManager = enemySpawnManager;
	m_cutsceneManager = cutsceneManager;

	m_triggerColliders.clear();

	for(const TilemapLayer layer : TilemapLoader::GetCurrentMap().layers) {
		if(layer.name == "triggers")
		{
			for(auto& obj : layer.objectData)
			{
				TriggerCollider collider;
				TriggerType type = TriggerType::AmbientSpawner;
				auto typeIt = obj.customProperties.find("type");
				if(typeIt == obj.customProperties.end()) continue;

				if(typeIt->second == "combatZone") type = TriggerType::CombatZoneSpawner;
				if(typeIt->second == "cutscene") type = TriggerType::CutsceneTrigger;

				TriggerColliderData data{};
				Vector2 position = Vector2(obj.x, obj.y);
				Vector2 size = Vector2(obj.width, obj.height);
				AABB aabb = AABB(position, Vector2(position.x + size.x, position.y + size.y));

				std::vector<std::string> result;
				if(obj.customProperties.contains("spawners")) {
					std::stringstream ss(obj.customProperties.at("spawners"));
					std::string token;

					while(std::getline(ss, token, ','))
					{
						token.erase(0, token.find_first_not_of(" \t\n\r"));
						token.erase(token.find_last_not_of(" \t\n\r") + 1);

						if(!token.empty())
							result.push_back(token);
					}

					data.spawnerIds = result;
				}

				if(type == TriggerType::CombatZoneSpawner)
				{
					data.combatZoneId = obj.name;
				}

				if(type == TriggerType::CutsceneTrigger)
				{
					data.cutsceneId = obj.name;
				}

				collider.Init(type, data);
				collider.SetAABB(aabb);
				m_triggerColliders.push_back(collider);
			}
		}
	}
}

void TriggerManager::Update(const Vector2& playerPosition)
{
	if(m_enemySpawnManager == nullptr || m_combatZoneManager == nullptr)
	{
		Logger::LogWarning("[TriggerManager] Update skipped: manager dependency is null");
		return;
	}

	for(auto it = m_triggerColliders.begin(); it != m_triggerColliders.end(); )
	{
		if(!it->OnCollision(playerPosition))
		{
			it++;
		}
		else
		{
			switch(it->GetType())
			{
			case TriggerType::AmbientSpawner:
				for(auto& spawnerId : it->GetSpawnerIds())
				{
					auto spawner = m_enemySpawnManager->GetSpawner(spawnerId);
					if (spawner != nullptr)
						spawner->SetActive(false);
				}
				break;
			case TriggerType::CombatZoneSpawner:
				m_combatZoneManager->ActivateZone(it->GetCombatZoneId());
				break;
			case TriggerType::CutsceneTrigger:
				m_cutsceneManager->StartCutscene(it->GetCutsceneId());
				break;
			default:
				break;
			}

			it = m_triggerColliders.erase(it);
		}
	}
}
