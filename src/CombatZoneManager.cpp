#include "CombatZoneManager.h"

#include "Camera.h"
#include "CombatZone.h"
#include "EnemySpawnManager.h"
#include "GlobalConstants.h"
#include "LevelRenderer.h"
#include "Logger.h"
#include "Player.h"
#include "TilemapData.h"
#include "TilemapLoader.h"
#include "UIManager.h"

#include <algorithm>
#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <sstream>
#include <string>
#include <vector>

using namespace GlobalConstants;

CombatZoneManager::CombatZoneManager() :
	m_camera(nullptr),
	m_player(nullptr),
	m_combatZones(),
	m_spawnManager(nullptr),
	m_NPCManager(nullptr),
	m_levelRenderer(nullptr)
{
}

CombatZoneManager::~CombatZoneManager()
{
	CleanUp();
}

void CombatZoneManager::Init(Camera* camera, Player* player, EnemySpawnManager* spawnManager, NPCManager* npcManager, LevelRenderer* levelRenderer)
{
	Logger::LogInfo("Initialising Combat Zone Manager");

	m_camera = camera;
	m_player = player;
	m_spawnManager = spawnManager;
	m_NPCManager = npcManager;
	m_levelRenderer = levelRenderer;

	auto currentMap = TilemapLoader::GetCurrentMap();

	for(const TilemapLayer layer : currentMap.layers)
	{
		if(layer.name == "triggers")
		{
			CreateCombatZones(layer.objectData);
		}
	}
}

void CombatZoneManager::CleanUp()
{
	for(auto* combatZone : m_combatZones)
	{
		delete combatZone;
		combatZone = nullptr;
	}
}

void CombatZoneManager::CreateCombatZones(const std::vector<MapObjectData>& mapObjectData)
{
	for(const auto& obj : mapObjectData)
	{
		auto position = Vector2(obj.x, obj.y);
		auto typeIt = obj.customProperties.find("type");
		if(typeIt == obj.customProperties.end() || typeIt->second != "combatZone")
			continue;

		auto spawnerIt = obj.customProperties.find("spawners");
		if(spawnerIt == obj.customProperties.end())
			continue;

		std::vector<std::string> result;
		std::stringstream ss(obj.customProperties.at("spawners"));
		std::string token;

		while(std::getline(ss, token, ','))
		{
			token.erase(0, token.find_first_not_of(" \t\n\r"));
			token.erase(token.find_last_not_of(" \t\n\r") + 1);

			if(!token.empty())
				result.push_back(token);
		}

		Logger::LogInfo(fmt::format("Adding combat zone: {}", obj.name));

		CombatZone* zone = new CombatZone();
		zone->Init(obj.name, position, result, m_spawnManager, m_NPCManager);
		m_combatZones.push_back(zone);
	}

	std::sort(m_combatZones.begin(), m_combatZones.end(),
		[](const CombatZone* a, const CombatZone* b)
		{
			return a->GetPosition().x < b->GetPosition().x;
		});
}

void CombatZoneManager::ActivateZone(std::string id)
{
	Logger::LogInfo(fmt::format("Activating combat zone: {}", id));

	for(size_t i = 0; i < m_combatZones.size(); i++)
	{
		auto* zone = m_combatZones[i];
		if(zone->GetId() != id) continue;

		zone->Activate();
		const float halfWidth = GameWidth * 0.5f;
		const float zoneMinX = zone->GetPosition().x - halfWidth;
		const float zoneMaxX = zone->GetPosition().x + halfWidth;
		m_camera->LockBounds(zoneMinX, zoneMaxX);
		return;
	}
}

void CombatZoneManager::Update(float deltaTime)
{
	bool anyZoneActive = false;

	for(auto* zone : m_combatZones)
	{
		if(!zone->IsActive()) continue;
		if(!zone->IsSpawningComplete())
		{
			anyZoneActive = true;
			continue;
		}

		zone->Deactivate();
		if(auto* goView = UIManager::GetView("Combat Zone Go View"))
		{
			goView->TransitionIn(true);
		}

		const float worldMinX = 0.0f;
		const float worldMaxX = static_cast<float>(m_levelRenderer->GetLevelPixelWidth());
		m_camera->ReleaseBoundsSmooth(0.35f, worldMinX, worldMaxX);
	}

	if(!anyZoneActive) m_camera->SetTarget(m_player);
}

CombatZone* CombatZoneManager::GetZoneById(std::string id) const
{
	for(auto* zone : m_combatZones)
	{
		if(zone->GetId() == id) return zone;
	}

	return nullptr;
}
