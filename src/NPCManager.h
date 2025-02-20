#pragma once

#include "EnemyDataContainer.h"

#include <string>
#include <vector>

class Camera;
class Enemy;
class Graphics;
class InGameHudManager;
class NPCFactory;
class Player;

class NPCManager
{
public:
	~NPCManager();
	NPCManager();

	static NPCManager* Instance() { return s_instance; }
	void	Init(Graphics* graphics, Camera* camera, Player* player);
	bool	InitTypes(const std::string &fileName);
	bool	InitNPCs(Graphics* graphics, Camera* camera, Player* player, const std::string &enemyDataFile);

	void	Render(Graphics* graphics);
	void	Update(float deltaTime);

	void	Reset();
	void	DeleteAll();

	void	SetAttackingEnemy(Enemy* enemy);
	Enemy*	GetAttackingEnemy() const { return m_hostileEnemy; }

	std::vector<Enemy*> GetEnemyList() const { return m_enemyList; }
	
private:
	static  NPCManager*		s_instance;

	NPCFactory*				m_NPCFactory;
	std::vector<Enemy*>		m_enemyList;
	EnemyDataContainer*		m_enemyDataContainer;
	Enemy*					m_hostileEnemy;
};