#pragma once

#include "DamageData.h"
#include "GameObject.h"
#include "Graphics.h"
#include "PlayerConstants.h"
#include "PlayerDefinition.h"
#include "Sprite.h"
#include "StateMachine.h"

#include <directxtk/SimpleMath.h>
#include <string>

#undef PlaySound

using namespace PlayerConstants;

class ControlSystem;
class CutsceneManager;
template<class T> class StateMachine;
class SoundSource;

class Player : public GameObject
{
public:
	Player();
	virtual								~Player();

	void								Init(ControlSystem* controlSystem, CutsceneManager* cutsceneManager, EventManager* eventManager);
	void								Update(float deltaTime);
	void								Render(Graphics* graphics);
	void								Reset();

	Sprite*								GetShadow() const { return m_shadow; }
	StateMachine<Player>*				GetStateMachine() const { return m_stateMachine; }

	virtual int							GetMaxHealth() const { return m_playerDefinition.hp; }
	float								GetWalkSpeed() const { return m_playerDefinition.walkSpeed; }
	float								GetRunSpeed() const { return m_playerDefinition.runningSpeed; }

	virtual DamageData					GetDamageData() const;

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
	void								SetSpecial(float amount);
	void								IncreaseSpecial(float value = 1.0f);
	bool								IsSpecialReady() const { return m_special == MaxSpecial; }

private:
	PlayerDefinition					LoadPlayerDefinition();
	void								NormalAttack();
	void								StrongAttack();
	void								SpecialAttack();
	void								Attack(std::string attackName);
	void								UpdateStats(bool animate);
	void								RegisterEvents();
	void								PlaySound(const std::string& id);
	void								PlayAttackSound(const std::string& name);
	void								PlayFootstepSound();
	void								PlayHurtSound();
	void								PlayDeathSound();

	PlayerDefinition					m_playerDefinition;
	StateMachine<Player>*				m_stateMachine;
	SoundSource*						m_attackSoundSource;
	SoundSource*						m_footStepSoundSource;
	SoundSource*						m_vocalSoundSource;
	float								m_knockoutTimer;
	float								m_hurtTimer;
	int									m_recentFootstepFrame;
	int									m_kills;
	float								m_special;
	CutsceneManager*					m_cutsceneManager;
};