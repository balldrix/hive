#pragma once

#include "EnemyDefinition.h"

#include <directxtk/SimpleMath.h>
#include <vector>

using namespace DirectX::SimpleMath;

class Camera;
class Enemy;
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

	void	SpawnNPC(const Vector2& position, const EnemyDefinition& enemyDefinition, const Vector2& velocity, const Vector2& direction, float height);

	void	Render(Graphics* graphics);
	void	Update(float deltaTime);

	void	Reset();
	void	DeleteAll();

	void	SetNextAttackingEnemy();
	void	SetAttackingEnemy(Enemy* enemy);
	Enemy*	GetAttackingEnemy() const { return m_hostileEnemy; }

	std::vector<Enemy*> GetEnemyList() const { return m_enemyList; }
	
private:
	static  NPCManager* s_instance;

	NPCFactory* m_NPCFactory;
	std::vector<Enemy*> m_enemyList;
	Enemy* m_hostileEnemy;
	Player* m_player;
};