#pragma once

#include <string>
#include <vector>

class EnemySpawnManager;
class NPCManager;

class CombatZone
{
public:
	CombatZone();
	~CombatZone();
	void Init(std::string id, std::vector<std::string> spawners, EnemySpawnManager* enemySpawnManager, NPCManager* npcManager);
	void Activate();
	void Deactivate();
	std::string GetId() const { return m_id; }
	bool IsActive() const { return m_isActive; }
	bool IsSpawningComplete();

private:
	std::string m_id;
	std::vector<std::string> m_spawnerIDs;
	EnemySpawnManager* m_enemySpawnManager;
	NPCManager* m_NPCManager;
	bool m_isActive;
};