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

	void	Init(Graphics* graphics, Camera* camera, Player* player);
	bool	InitTypes(const std::string &fileName);
	bool	InitNPCs(Graphics* graphics, Camera* camera, Player* player, const std::string &enemyDataFile);

	void	Render(Graphics* graphics);
	void	Update(float deltaTime);

	void	Reset();
	void	DeleteAll();

	std::vector<Enemy*> GetEnemyList() const { return m_enemyList; }

private:
	NPCFactory*				m_NPCFactory;
	std::vector<Enemy*>		m_enemyList;
	EnemyDataContainer*		m_enemyDataContainer;
};