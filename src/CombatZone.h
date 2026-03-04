#pragma once

#include <directxtk/SimpleMath.h>
#include <string>
#include <vector>

class EnemySpawnManager;
class NPCManager;

class CombatZone
{
public:
	CombatZone();
	~CombatZone();
	void Init(std::string id, const DirectX::SimpleMath::Vector2& position, std::vector<std::string> spawners, EnemySpawnManager* enemySpawnManager, NPCManager* npcManager);
	void Activate();
	void Deactivate();
	std::string GetId() const { return m_id; }
	DirectX::SimpleMath::Vector2 GetPosition() const { return m_position; }
	bool IsActive() const { return m_isActive; }
	bool IsSpawningComplete();

private:
	std::string m_id;
	DirectX::SimpleMath::Vector2 m_position;
	std::vector<std::string> m_spawnerIDs;
	EnemySpawnManager* m_enemySpawnManager;
	NPCManager* m_NPCManager;
	bool m_isActive;
};
