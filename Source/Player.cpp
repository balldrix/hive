#include "Player.h"
#include "Graphics.h"
#include "Sprite.h"
#include "ControlSystem.h"
#include "SpriteSheet.h"
#include "Animator.h"
#include "HitBoxManager.h"
#include "Resources.h"
#include "ControlSystem.h"
#include "StateMachine.h"
#include "PlayerOwnedStates.h"
#include "UnitVectors.h"
#include "Camera.h"
#include "Error.h"
#include "Constants.h"

using namespace PlayerConstants;
using namespace GlobalConstants;

Player::Player() :
	m_stateMachine(nullptr),
	m_lives(0)
{
}

Player::~Player()
{
	if(m_stateMachine)
	{
		delete m_stateMachine;
		m_stateMachine = nullptr;
	}
}

void Player::Init(SpriteSheet* sprite, Sprite* shadow, Animator* animator, HitBoxManager* hitBoxManager, ControlSystem* controlSystem)
{
	m_sprite = sprite;
	m_controlSystem = controlSystem;
	m_shadow = shadow;
	m_position.x = m_playerData.objectData.startingPosition.x;
	m_position.y = RespawnAirPositionY;
	m_groundPosition.y = m_playerData.objectData.startingPosition.y;
	m_acceleration = m_playerData.objectData.acceleration;
	m_deceleration = m_playerData.objectData.deceleration;
	m_movementSpeed = m_playerData.objectData.walkSpeed;
	m_animator = animator;
	m_animator->SetAnimation(0);
	m_hitBoxManager = hitBoxManager;
	m_grounded = false;

	m_stateMachine = new StateMachine<Player>(this);
	m_stateMachine->Init(PlayerIdleState::Instance(), nullptr, PlayerGlobalState::Instance());

	m_health = m_playerData.objectData.startingHealth;
	m_lives = m_playerData.objectData.startingLives;
}

void Player::LoadData(std::string playerDataFile, std::string damageDataFile)
{
	if(!LoadPlayerData(playerDataFile))
	{
		// unable to load player data file
		std::string error = " Error! No player data file " + playerDataFile + " found.";
		Error::FileLog(error);
	}

	if(!LoadDamageData(damageDataFile))
	{
		// unable to load player data file
		std::string error = " Error! No player damage data file " + damageDataFile + " found.";
		Error::FileLog(error);
	}
}

bool Player::LoadPlayerData(std::string filename)
{
	std::ifstream file;
	file.open(filename);

	if(file)
	{
		std::string line;
		ObjectData data;

		while(std::getline(file, line))
		{
			if(line[0] != '#')
			{
				std::string result = "";

				data.id = "PLAYER";

				file >> result;
				data.startingHealth = std::stoi(result);

				file >> result;
				data.startingLives = std::stoi(result);

				file >> result;
				data.startingPosition.x = std::stof(result);

				file >> result;
				data.startingPosition.y = std::stof(result);

				file >> result;
				data.walkSpeed = std::stof(result);

				file >> result;
				data.acceleration = std::stof(result);

				file >> result;
				data.deceleration = std::stof(result);

				m_playerData.objectData = data;

				file >> result;
				m_playerData.deathTime = std::stof(result);
			}
		}
	}
	else
	{
		return false;
	}

	file.close();
	return true;
}

void Player::Update(float deltaTime)
{
	if(m_dead == true)
		return;

	// update player state machine
	m_stateMachine->Update();

	// update object
	GameObject::Update(deltaTime);

	if(m_stateMachine->GetCurrentState() != PlayerAttackState::Instance())
		m_controlSystem->Update(deltaTime);

	if(m_stateMachine->GetCurrentState() == PlayerDeadState::Instance())
		m_deathTimer += deltaTime;

	if(m_deathTimer > m_playerData.deathTime)
		Kill();
}

void Player::Kill()
{
	m_lives--;
	m_dead = true;
}

void Player::Respawn()
{
	m_stateMachine->ChangeState((PlayerIdleState::Instance()));
	m_position = m_camera->GetPosition() + Vector2(GameWidth * 0.5f, RespawnGroundPositionY);
	m_hitBoxManager->SetCurrentHitBox(0);
	m_groundPosition = m_position;
	m_position.y = RespawnAirPositionY;
	m_deathTimer = 0.0f;
	m_dead = false;
	m_active = true;
	m_grounded = false;
	m_health = m_playerData.objectData.startingHealth;
	SetVelocity(m_currentVelocity.x, m_currentVelocity.y + FallingSpeed);
}

void Player::Render(Graphics* graphics)
{
	// render shadow first
	if(m_shadow)
	{
		m_shadow->SetDepth(m_groundPosition.y / graphics->GetHeight());
		m_shadow->Render(graphics);
	}

	if(m_sprite)
	{
		// set layer depth
		m_sprite->SetDepth(m_groundPosition.y / graphics->GetHeight());

		// render player sprite
		if(m_animator)
		{
			m_sprite->Render(graphics, m_animator->GetCurrentFrame() + m_animator->GetAnimation()->spritesheetIndex);
		}
		else
		{
			m_sprite->Render(graphics, 0);
		}
	}

	// render hitbox
	//if(m_hitBoxManager)
	//{
	//	m_hitBoxManager->Render(graphics);
	//}
}

void Player::Reset()
{
	m_stateMachine->ChangeState((PlayerIdleState::Instance()));
	SetPosition(m_playerData.objectData.startingPosition);
	m_groundPosition = m_position;
	m_position.y = RespawnAirPositionY;
	m_grounded = false;
	m_hitBoxManager->SetCurrentHitBox(0);
	m_health = m_playerData.objectData.startingHealth;
	m_deathTimer = 0.0f;
	m_dead = false;
	m_active = true;
	m_lives = m_playerData.objectData.startingLives;
}

int Player::GetDamage() const
{
	std::string stateName = m_stateMachine->GetCurrentState()->GetName();
	if(m_damageData.count(stateName) == 0)
		return 0;

	return m_damageData.at(stateName);
}

void Player::Move(const Vector2& direction)
{
	// true if switching direction
	if(direction.x < 0 && m_currentVelocity.x > 0 ||
		direction.x > 0 && m_currentVelocity.x < 0)
	{
		// slow down before switching
		SetTargetVelocityX(0.0f);
		return;
	}

	SetTargetVelocity(direction);
}

// stop velocity
void Player::Stop()
{
	SetTargetVelocity(Vector2::Zero);
	SetCurrentVelocity(Vector2::Zero);
}

// normal attack behaviour
void Player::Attack()
{
	if(m_animator->GetAnimation()->name == "Idle" || m_animator->GetAnimation()->name == "Walking")
	{
		// use combo counter to get the correct attack 
		switch(m_controlSystem->GetComboCounter())
		{
		case 0:
		case 1:
			PlayerAttackState::Instance()->SetAttack("Attack1");
			break;
		case 2:
			PlayerAttackState::Instance()->SetAttack("Attack2");
			break;
		case 3:
			PlayerAttackState::Instance()->SetAttack("Attack3");
			break;
		default:
			PlayerAttackState::Instance()->SetAttack("Attack1");
			break;
		}

		m_stateMachine->ChangeState((PlayerAttackState::Instance()));
		m_controlSystem->SetInput(Controls::None);
	}
}

void Player::ApplyDamage(GameObject* source, const int& amount)
{
	m_health -= amount;

	// true if health has gone or damage is high
	if(m_health < 1 || amount > 15)
	{
		// set knockback state
		m_stateMachine->ChangeState(PlayerKnockbackState::Instance());

		Vector2 direction = Vector2::Zero;

		// calculate direction to knockback
		if(this->GetPositionX() < source->GetPositionX())
		{
			direction = UnitVectors::UpLeft;
		}
		else
		{
			direction = UnitVectors::UpRight;
		}

		// knockback with force
		Knockback(direction, 80.0f);

		// bounce 
		SetKnockbackCount(2);
	}
	else
	{
		m_stateMachine->ChangeState(PlayerHurtState::Instance());
	}
}

void Player::Knockback(const Vector2& direction, const float& force)
{
	SetVelocity(direction);
	SetMovementSpeed(force);
}

