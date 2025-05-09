#pragma once

#include "Camera.h"
#include "DamageData.h"
#include "EnemyDefinition.h"
#include "GameObject.h"
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
								const EnemyDefinition& definition,
								NPCManager* npcManager,
								Texture* shadowTexture,
								State<Enemy>* globalEnemyState,
								State<Enemy>* startingState);

	void					Update(float deltaTime);
	void					Render(Graphics* graphics);
	virtual void			Reset() {};

	void					Spawn(const Vector2& position);

	void					SetDead(bool isDead);
	void					SetPlayerTarget(Player* player);
	void					ResetStateChangeTimer();

	Player*					GetPlayerTarget() const { return m_playerTarget; }
	StateMachine<Enemy>*	GetStateMachine() const { return m_stateMachine; }
	float					GetTimer() const { return m_stateChangeTimer; }
	EnemyDefinition			GetData() const { return m_enemyDefinition; }
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
	virtual void			PlayFootstepSound();
	void					StopWalkingSound();
	virtual void			PlayPunchSound();
	void					PlayHurtSound();
	void					PlayDeathSound();

protected:
	StateMachine<Enemy>*	m_stateMachine;
	SoundSource*			m_vocalSoundSource;
	SoundSource*			m_footStepSoundSource;
	SoundSource*			m_attackSoundSource;
	int						m_recentFootstepFrame;
	EnemyDefinition			m_enemyDefinition;

private:
	Vector2					Seek() const;
	Vector2					Avoid() const;
	Vector2					Strafe() const;

	Player*					m_playerTarget;
	Sprite*					m_portraitSprite;
	Sprite*					m_hitBoxSprite;
	float					m_stateChangeTimer;
	float					m_flashingTimer;
	bool					m_isFlashing;
	State<Enemy>*			m_startingState;
	NPCManager*				m_npcManager;
};