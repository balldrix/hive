#pragma once

#include <directxtk/SimpleMath.h>
#include <vector>

using namespace DirectX::SimpleMath;

class CombatZoneManager;
class CutsceneManager;
class EnemySpawnManager;
class TriggerCollider;

class TriggerManager
{
public:
	TriggerManager();
	~TriggerManager();

	void Init(CombatZoneManager* combatZoneManager, EnemySpawnManager* enemySpawnManager, CutsceneManager* cutsceneManager);
	void Update(const Vector2& playerPosition);

private:
	std::vector<TriggerCollider> m_triggerColliders;
	CombatZoneManager* m_combatZoneManager;
	EnemySpawnManager* m_enemySpawnManager;
	CutsceneManager* m_cutsceneManager;
};