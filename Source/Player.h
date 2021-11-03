#pragma once

#include "pch.h"
#include "GameObject.h"
#include "State.h"
#include "PlayerData.h"


class ControlSystem;
template<class T> class StateMachine;
class SoundSource;

class Player : public GameObject
{
public:
	Player();
	virtual					~Player();

	void					Init(Spritesheet* sprite, Sprite* shadow, Animator* animator, HitBoxManager* hitBoxManager, ControlSystem* controlSystem);

	void					LoadData(const std::string &playerDataFile, const std::string &attackDataFile);
	bool					LoadPlayerData(const std::string &filename);
	void					Update(float deltaTime);
	void					Render(Graphics* graphics);
	void					Reset();

	StateMachine<Player>*	GetStateMachine() const { return m_stateMachine; }

	virtual int				GetMaxHealth() const { return m_playerData.objectData.startingHealth; }
	float					GetWalkSpeed() const { return m_playerData.objectData.walkSpeed; }
	int						GetDamage() const;
	int						GetLives() const { return m_lives; }

	void					Run();
	void					Walk();
	void					Move(const Vector2& direction);
	void					Stop();
	void					Attack();
	void					ApplyDamage(GameObject* source, const int& amount);
	void					Knockback(const Vector2& direction, const float& force);
	void					Kill();
	void					Respawn();
	void					ResetKnockoutTimer();

	void					PlayPunchSound(const std::string &name);	
	void					PlayWalkingSound();
	void					PlayHurtSound();
	void					PlayDeathSound();

private:
	PlayerData							m_playerData;
	StateMachine<Player>*				m_stateMachine;
	SoundSource*						m_punchSoundSource;
	SoundSource*						m_footStepsSoundSource;
	SoundSource*						m_vocalSoundSource;
	int									m_lives;
	float								m_knockoutTimer;
	std::map<std::string, std::wstring>	m_playerSounds;
	int									m_recentFootstepFrame;
};