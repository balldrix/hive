#pragma once

#include "DamageData.h"
#include "GameObject.h"
#include "Graphics.h"
#include "PlayerConstants.h"
#include "PlayerData.h"
#include "Sprite.h"
#include "StateMachine.h"

#include <directxtk/SimpleMath.h>
#include <map>
#include <string>

using namespace PlayerConstants;

class ControlSystem;
template<class T> class StateMachine;
class SoundSource;

class Player : public GameObject
{
public:
	Player();
	virtual								~Player();

	void								Init(ControlSystem* controlSystem);
	void								LoadData(const std::string &playerDataFile, const std::string &attackDataFile);
	bool								LoadPlayerData(const std::string &filename);
	void								Update(float deltaTime);
	void								Render(Graphics* graphics);
	void								Reset();

	Sprite*								GetShadow() const { return m_shadow; }
	StateMachine<Player>*				GetStateMachine() const { return m_stateMachine; }

	virtual int							GetMaxHealth() const { return m_playerData.objectData.startingHealth; }
	float								GetWalkSpeed() const { return m_playerData.objectData.walkSpeed; }
	float								GetRunSpeed() const { return m_playerData.objectData.runningSpeed; }

	virtual DamageData					GetDamageData() const;
	int									GetLives() const { return m_lives; }

	float								GetHurtTimer() const { return m_hurtTimer; }
	void								SetHurtTimer(const float& time) { m_hurtTimer = time; }

	void								Move(const Vector2& direction);
	void								Run();
	void								Walk();
	void								Stop();
	void								Block();
	void								ApplyDamage(GameObject* source, const int& amount);
	void								Knockback(const Vector2& direction, const float& force);
	void								Kill();
	void								Respawn();
	void								ResetKnockoutTimer();
	void								AddKill();
	void								IncreaseSpecial(float value = 1.0f);
	bool								IsSpecialReady() const { return m_special == MaxSpecial; }

	void								PlayPunchSound(const std::string &name);	
	void								PlayWalkingSound();
	void								PlayHurtSound();
	void								PlayDeathSound();

private:
	void								NormalAttack();
	void								StrongAttack();
	void								SpecialAttack();
	void								Attack(std::string attackName);
	void								InitStats();
	void								UpdateStats();

	PlayerData							m_playerData;
	StateMachine<Player>*				m_stateMachine;
	SoundSource*						m_punchSoundSource;
	SoundSource*						m_footStepsSoundSource;
	SoundSource*						m_vocalSoundSource;
	int									m_lives;
	float								m_knockoutTimer;
	float								m_hurtTimer;
	std::map<std::string, std::wstring>	m_playerSounds;
	int									m_recentFootstepFrame;
	int									m_kills;
	float								m_special;
};