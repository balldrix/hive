#pragma once

#include "DamageData.h"
#include "EnemyData.h"
#include "GameObject.h"
#include "HitBoxManager.h"
#include "Player.h"
#include "Sprite.h"
#include "State.h"
#include "StateMachine.h"

#include <directxtk/SimpleMath.h>

class Graphics;
class NPCManager;
class Texture;
template<class T> class StateMachine;
class SoundSource;

class Enemy : public GameObject
{
public:
							Enemy();
	virtual					~Enemy();

	void					Init(Graphics* graphics,
								Camera* camera,
								Player* player,
								const EnemyData& data,
								NPCManager* npcManager,
								Texture* shadowTexture,
								State<Enemy>* globalEnemyState,
								State<Enemy>* startingState);

	void					Update(float deltaTime);
	void					Render(Graphics* graphics);
	virtual void			Reset();

	void					SetData(const EnemyData& data);
	void					SetDead();
	void					SetPlayerTarget(Player* player);
	void					SetHostile(bool isHostile);
	void					ResetTimer(float timerMod);

	Player*					GetPlayerTarget() const { return m_playerTarget; }
	StateMachine<Enemy>*	GetStateMachine() const { return m_stateMachine; }
	float					GetTimer() const { return m_thinkingTimer; }
	bool					IsHostile() const { return m_isHostile; }
	EnemyData				GetData() const { return m_enemyData; }
	virtual DamageData		GetDamageData() const;
	NPCManager*				GetManager() const { return m_npcManager; }

	virtual void			ApplyDamage(GameObject* source, const int& amount);
	void					Knockback(const Vector2& direction, const float& force);
		
	virtual void			Attack();
	void					Kill();

	void					ShowEnemyHud();
	void					DeleteAll();

	void					ProcessSteering();
	void					Flash();

	virtual void			PlayEntranceSound();
	virtual void			PlayWalkingSound();
	void					StopWalkingSound();
	virtual void			PlayPunchSound();
	void					PlayHurtSound();
	void					PlayDeathSound();

protected:
	StateMachine<Enemy>*	m_stateMachine;
	SoundSource*			m_vocalSoundSource;
	SoundSource*			m_footStepsSoundSource;
	SoundSource*			m_punchSoundSource;
	int						m_recentFootstepFrame;
	EnemyData				m_enemyData;

private:
	Vector2					Seek() const;
	Vector2					Avoid() const;
	Vector2					Strafe() const;

	Player*					m_playerTarget;
	Sprite*					m_portraitSprite;
	Sprite*					m_hitBoxSprite;
	float					m_thinkingTimer;
	float					m_flashingTimer;
	bool					m_isHostile;
	bool					m_isFlashing;
	State<Enemy>*			m_startingState;
	NPCManager*				m_npcManager;
};