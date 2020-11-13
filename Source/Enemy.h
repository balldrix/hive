// Enemy.h
// Christopher Ball 2019
// Enemy class 

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Constants.h"
#include "GameObject.h"
#include "EnemyData.h"

class Graphics;
class Player;
class BarController;
class InGameHudManager;
template<class T> class StateMachine;

class Enemy : public GameObject
{
public:
	Enemy();
	virtual					~Enemy();

	void					Init(Graphics* graphics,
									const Vector2& position, 
									Spritesheet* sprite, 
									Sprite* shadow, 
									Animator* animator, 
									HitBoxManager* hitBoxManager, 
									InGameHudManager* inGameUiManager, 
									Sprite* portraitSprite);

	void					Update(float deltaTime);
	void					Render(Graphics* graphics);
	void					Reset();

	void					SetData(const EnemyData& data);
	void					SetDead();
	void					SetPlayerTarget(Player* player);
	void					SetHostile(bool isHostile);
	void					ResetTimer();

	Player*					GetPlayerTarget() const { return m_playerTarget; }
	StateMachine<Enemy>*	GetStateMachine() const { return m_stateMachine; }
	float					GetTimer() const { return m_thinkingTimer; }
	bool					IsHostile() const { return m_isHostile; }
	EnemyData				GetData() const { return m_enemyData; }
	int						GetDamage() const;
	InGameHudManager*		GetUiManager() const { return m_hudManager; }

	void					ApplyDamage(GameObject* source, const int& amount);
	void					Knockback(const Vector2& direction, const float& force);
	
	void					Attack();
	void					Kill();

	void					ShowEnemyHud();
	void					ReleaseAll();
	void					DeleteAll();

private:
	EnemyData				m_enemyData;
	Player*					m_playerTarget;
	InGameHudManager*		m_hudManager;
	Sprite*					m_portraitSprite;
	BarController*			m_healthBar;
	StateMachine<Enemy>*	m_stateMachine;
	float					m_thinkingTimer;
	bool					m_isHostile;
};

#endif _ENEMY_H_