#pragma once

#include "EnemyDefinition.h"

#include <DirectXMath.h>
#include <directxtk/SimpleMath.h>
#include <string>
#include <vector>

using namespace DirectX::SimpleMath;

class Camera;
class Enemy;
class EventManager;
class Graphics;
class NPCFactory;
class Player;

class NPCManager
{
public:
	~NPCManager();
	NPCManager();

	static	NPCManager* Instance() { return s_instance; }
	void	Init(Camera* camera, Player* player);

	void	SpawnNPC(const Vector2& position, const EnemyDefinition& enemyDefinition, const Vector2& velocity = Vector2::Zero, const Vector2& direction = Vector2(-1.0f, 0.0f), float height = 0.0f);

	void	Render(Graphics* graphics);
	void	Update(float deltaTime);

	void	Reset();
	void	DeleteAll();

	void	SetNextAttackingEnemy();
	void	SetAttackingEnemy(Enemy* enemy);
	Enemy*	GetAttackingEnemy() const { return m_hostileEnemy; }
	EventManager* GetEventManager() const { return m_eventManager; }

	std::vector<Enemy*> GetEnemyList() const { return m_enemyList; }

private:
	void RegisterEvents();

	static  NPCManager* s_instance;

	NPCFactory* m_NPCFactory;
	std::vector<Enemy*> m_enemyList;
	Enemy* m_hostileEnemy;
	Player* m_player;
	EventManager* m_eventManager;
};