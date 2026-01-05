#pragma once

#include "TilemapData.h"

#include <string>
#include <vector>

class Camera;
class CombatZone;
class EnemySpawnManager;
class NPCManager;
class Player;

class CombatZoneManager
{
public :
	CombatZoneManager();
	~CombatZoneManager();
	void Init(Camera* camera, Player* player, EnemySpawnManager* spawnManager, NPCManager* npcManager);
	void ActivateZone(std::string id);
	void Update(float deltaTime);

private:
	void CleanUp();
	void CreateCombatZones(const std::vector<MapObjectData>& mapObjectData);

	Camera* m_camera;
	Player* m_player;
	std::vector<CombatZone*> m_combatZones;
	EnemySpawnManager* m_spawnManager;
	NPCManager* m_NPCManager;
};