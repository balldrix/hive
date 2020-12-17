#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "pch.h"
#include "GameObject.h"
#include "State.h"
#include "PlayerData.h"

// forward declarations
class ControlSystem;
template<class T> class StateMachine;

class Player : public GameObject
{
public:
	Player();
	virtual					~Player();

	void					Init(Spritesheet* sprite, Sprite* shadow, Animator* animator, HitBoxManager* hitBoxManager, ControlSystem* controlSystem);

	void					LoadData(std::string playerDataFile, std::string attackDataFile);
	bool					LoadPlayerData(std::string filename);
	void					Update(float deltaTime);
	void					Render(Graphics* graphics);
	void					Reset();

	StateMachine<Player>*	GetStateMachine() const { return m_stateMachine; }

	virtual int				GetMaxHealth() const { return m_playerData.objectData.startingHealth; }
	float					GetWalkSpeed() const { return m_playerData.objectData.walkSpeed; }
	int						GetDamage() const;
	int						GetLives() const { return m_lives; }

	// movement
	void					Move(const Vector2& direction);
	void					Stop();

	// attacks
	void					Attack();
	void					ApplyDamage(GameObject* source, const int& amount);
	void					Knockback(const Vector2& direction, const float& force);
	void					Kill();
	void					Respawn();
	void					ResetKnockoutTimer();

private:
	PlayerData				m_playerData;
	StateMachine<Player>*	m_stateMachine;
	int						m_lives;
	float					m_knockoutTimer;
};

#endif _PLAYER_H_