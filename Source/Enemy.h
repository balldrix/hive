#pragma once

#include "Constants.h"
#include "GameObject.h"
#include "EnemyData.h"
#include "State.h"

class Graphics;
class Player;
class BarController;
class InGameHudManager;
template<class T> class StateMachine;
class SoundSource;

class Enemy : public GameObject
{
public:
	Enemy();
	virtual					~Enemy();

	virtual void			Init(Graphics* graphics,
								 Camera* camera,
								 Player* player,
								 const EnemyData& data,
								 Texture* spriteTexture, 
								 Texture* shadowTexture,
								 Texture* hitBoxTexture,
								 InGameHudManager* inGameUiManager, 
								 Sprite* portraitSprite,
								 State<Enemy>* globalEnemyState);

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
	
	virtual void			Attack();
	void					Kill();

	void					ShowEnemyHud();
	void					ReleaseAll();
	void					DeleteAll();

	void					PlayEntranceSound();
	void					PlayWalkingSound();
	void					StopWalkingSound();
	void					PlayPunchSound();

protected:
	StateMachine<Enemy>*	m_stateMachine;

private:
	EnemyData				m_enemyData;
	Player*					m_playerTarget;
	InGameHudManager*		m_hudManager;
	Sprite*					m_portraitSprite;
	Sprite*					m_hitBoxSprite;
	BarController*			m_healthBar;
	SoundSource*			m_vocalSoundSource;
	SoundSource*			m_footStepsSource;
	SoundSource*			m_punchSoundSource;
	float					m_thinkingTimer;
	bool					m_isHostile;
};