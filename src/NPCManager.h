#pragma once

#include "EnemyDefinition.h"
#include "IEvent.h"

#include <directxtk/SimpleMath.h>
#include <string>
#include <vector>

using namespace DirectX::SimpleMath;

class Camera;
class CutsceneManager;
class Enemy;
class EventManager;
class Graphics;
class NPCFactory;
class Player;
class ProjectileManager;

class NPCManager
{
public:
	~NPCManager();
	NPCManager();

	static	NPCManager* Instance() { return s_instance; }
	void	Init(Camera* camera, Player* player, CutsceneManager* cutsceneManager, EventManager* eventManager, ProjectileManager* projectileManager);

	void	SpawnNPC(std::string id, std::string waveId, const Vector2& position, const EnemyDefinition& enemyDefinition, const Vector2& velocity = Vector2::Zero, const Vector2& direction = Vector2(-1.0f, 0.0f), float height = 0.0f);
	void	SpawnNPC(SpawnNPCArgument argument);

	void	Render(Graphics* graphics);
	void	Update(float deltaTime);

	void	Reset();
	void	DeleteAll();

	void	SetNextAttackingEnemy(const std::string& waveId);
	void	SetNextAttackingEnemy(Enemy* enemy);
	void	SetAttackingEnemy(Enemy* enemy);
	Enemy*	GetAttackingEnemy(const std::string& waveId) const;
	bool	IsAttackingEnemy(const Enemy* enemy) const;
	std::vector<Enemy*>	GetAttackingEnemyList() const { return m_hostileEnemyList; }
	EventManager* GetEventManager() const { return m_eventManager; }
	bool IsWaveDead(std::string waveId);

	std::vector<Enemy*> GetEnemyList() const { return m_enemyList; }

private:
	struct WaveHostileHistory
	{
		std::string waveId;
		std::vector<Enemy*> recentHostiles;
	};

	void RegisterEvents();
	void CleanupHostileEnemyList();
	bool IsEligibleHostileEnemy(const Enemy* enemy) const;
	WaveHostileHistory* FindWaveHistory(const std::string& waveId);
	const WaveHostileHistory* FindWaveHistory(const std::string& waveId) const;
	WaveHostileHistory& GetOrCreateWaveHistory(const std::string& waveId);
	void CleanupWaveHistory();
	void ClearAttackingEnemy(const std::string& waveId);

	static  NPCManager* s_instance;

	NPCFactory* m_NPCFactory;
	std::vector<Enemy*> m_enemyList;
	std::vector<Enemy*> m_hostileEnemyList;
	std::vector<WaveHostileHistory> m_previousHostilesByWave;
	Player* m_player;
	EventManager* m_eventManager;
	CutsceneManager* m_cutsceneManager;
};
