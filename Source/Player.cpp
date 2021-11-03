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
#include "AudioEngine.h"
#include "SoundManager.h"
#include "SoundSource.h"
#include "Sound.h"
#include "Randomiser.h"

using namespace PlayerConstants;
using namespace GlobalConstants;

Player::Player() :
	m_stateMachine(nullptr),
	m_lives(0),
	m_knockoutTimer(0.0f),
	m_punchSoundSource(nullptr),
	m_footStepsSoundSource(nullptr),
	m_vocalSoundSource(nullptr),
	m_recentFootstepFrame(0)
{
}

Player::~Player()
{
	AudioEngine::Instance()->RemoveSoundSource(m_vocalSoundSource);
	AudioEngine::Instance()->RemoveSoundSource(m_footStepsSoundSource);
	AudioEngine::Instance()->RemoveSoundSource(m_punchSoundSource);

	delete m_vocalSoundSource;
	delete m_footStepsSoundSource;
	delete m_punchSoundSource;
	delete m_stateMachine;
	
	m_vocalSoundSource = nullptr;
	m_footStepsSoundSource = nullptr;
	m_punchSoundSource = nullptr;
	m_stateMachine = nullptr;
}

void Player::Init(Spritesheet* sprite, Sprite* shadow, Animator* animator, HitBoxManager* hitBoxManager, ControlSystem* controlSystem)
{
	m_spriteSheet = sprite;
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

	m_punchSoundSource = new SoundSource();
	m_punchSoundSource->SetTarget(this);
	m_punchSoundSource->SetLooping(false);
	m_punchSoundSource->SetRelative(true);

	m_footStepsSoundSource = new SoundSource();
	m_footStepsSoundSource->SetTarget(this);
	m_footStepsSoundSource->SetLooping(false);
	m_footStepsSoundSource->SetRelative(true);

	m_vocalSoundSource = new SoundSource();
	m_vocalSoundSource->SetTarget(this);
	m_vocalSoundSource->SetLooping(false);
	m_vocalSoundSource->SetRelative(true);

	AudioEngine::Instance()->SetListener(this);
	AudioEngine::Instance()->AddSoundSource(m_punchSoundSource);
	AudioEngine::Instance()->AddSoundSource(m_footStepsSoundSource);
	AudioEngine::Instance()->AddSoundSource(m_vocalSoundSource);

	m_playerSounds =
	{
		{ "Attack1",	L"punch_001" },
		{ "Attack2",	L"punch_003" },
		{ "Attack3",	L"punch_004" },
		{ "Walking1",	L"walk_001"},
		{ "Walking2",	L"walk_002"},
		{ "Walking3",	L"walk_003"},
		{ "Walking4",	L"walk_004"},
		{ "Hurt1",		L"hit_001"},
		{ "Hurt2",		L"hit_002"},
		{ "Hurt3",		L"hit_003"},
		{ "Dead",		L"scream"}
	};
}

void Player::LoadData(const std::string &playerDataFile, const std::string &damageDataFile)
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

bool Player::LoadPlayerData(const std::string &filename)
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

				file >> result;
				m_playerData.knockoutDuration = std::stof(result);
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

	m_stateMachine->Update();
	GameObject::Update(deltaTime);

	if(m_stateMachine->GetCurrentState() != PlayerAttackState::Instance())
		m_controlSystem->Update(deltaTime);

	if(m_stateMachine->GetCurrentState() == PlayerDeadState::Instance() && m_health <= 0)
		m_deathTimer += deltaTime;

	if(m_deathTimer > m_playerData.deathTime)
		Kill();

	if(m_stateMachine->GetCurrentState() == PlayerDeadState::Instance() && m_health > 0)
		m_knockoutTimer += deltaTime;

	if(m_knockoutTimer > m_playerData.knockoutDuration)
		m_stateMachine->ChangeState(PlayerIdleState::Instance());
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
	m_knockoutTimer = 0.0f;
	m_dead = false;
	m_active = true;
	m_grounded = false;
	m_health = m_playerData.objectData.startingHealth;
	SetVelocity(m_currentVelocity.x, m_currentVelocity.y + FallingSpeed);
}

void Player::ResetKnockoutTimer()
{
	m_knockoutTimer = 0.0f;
}

void Player::Render(Graphics* graphics)
{
	// render shadow first
	if(m_shadow)
	{
		m_shadow->SetDepth(m_groundPosition.y / graphics->GetHeight());
		m_shadow->Render(graphics);
	}

	if(m_spriteSheet)
	{
		// set layer depth
		m_spriteSheet->SetDepth(m_groundPosition.y / graphics->GetHeight());

		// render player sprite
		if(m_animator)
		{
			m_spriteSheet->Render(graphics, m_animator->GetCurrentFrame() + m_animator->GetAnimation()->spritesheetIndex);
		}
		else
		{
			m_spriteSheet->Render(graphics, 0);
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
	SetVelocity(Vector2::Zero);
}

int Player::GetDamage() const
{
	std::string stateName = m_stateMachine->GetCurrentState()->GetName();
	if(m_damageData.count(stateName) == 0)
		return 0;

	return m_damageData.at(stateName);
}

void Player::Run()
{
	//m_movementSpeed = m_playerData.objectData.runningSpeed;
	m_movementSpeed = m_playerData.objectData.walkSpeed * 2.0f;
}

void Player::Walk()
{
	m_movementSpeed = m_playerData.objectData.walkSpeed;
}

void Player::Move(const Vector2& direction)
{
	if(direction.x < 0 && m_currentVelocity.x > 0 ||
		direction.x > 0 && m_currentVelocity.x < 0)
	{
		SetTargetVelocityX(0.0f);
		return;
	}

	SetTargetVelocity(direction);
}

void Player::Stop()
{
	SetTargetVelocity(Vector2::Zero);
	SetCurrentVelocity(Vector2::Zero);
}

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
	}
}

void Player::ApplyDamage(GameObject* source, const int& amount)
{
	m_health -= amount;

	if(m_health < 1 || amount > 15)
	{
		m_stateMachine->ChangeState(PlayerKnockbackState::Instance());

		Vector2 direction = Vector2::Zero;

		if(this->GetPositionX() < source->GetPositionX())
		{
			direction = UnitVectors::UpLeft;
		}
		else
		{
			direction = UnitVectors::UpRight;
		}

		Knockback(direction, 80.0f);
		SetKnockbackCount(2);
	}
	else
	{
		m_stateMachine->ChangeState(PlayerHurtState::Instance());
	}

	PlayHurtSound();
}

void Player::Knockback(const Vector2& direction, const float& force)
{
	SetVelocity(direction);
	SetMovementSpeed(force);
}

void Player::PlayPunchSound(const std::string &name)
{
	std::wstring soundName = m_playerSounds[name];
	m_punchSoundSource->SetSound(SoundManager::GetSound(soundName));
}

void Player::PlayWalkingSound()
{
	if(m_recentFootstepFrame == m_animator->GetCurrentFrame())
		return;

	m_recentFootstepFrame = m_animator->GetCurrentFrame();
	
	uint32_t randomWalkIndex = Randomiser::Instance()->GetRandNum(1, 4);

	std::wstring soundName = m_playerSounds[m_stateMachine->GetCurrentState()->GetName() + std::to_string(randomWalkIndex)];
	m_footStepsSoundSource->SetSound(SoundManager::GetSound(soundName));
}

void Player::PlayHurtSound()
{
	uint32_t randomHurtSound = Randomiser::Instance()->GetRandNum(1, 3);

	std::wstring soundName = m_playerSounds[m_stateMachine->GetCurrentState()->GetName() + std::to_string(randomHurtSound)];
	m_vocalSoundSource->SetSound(SoundManager::GetSound(soundName));
}

void Player::PlayDeathSound()
{
	std::wstring soundName = m_playerSounds[m_stateMachine->GetCurrentState()->GetName()];
	
	Sound* sound = SoundManager::GetSound(soundName);
	
	if(m_vocalSoundSource->GetSound() != sound)	
		m_vocalSoundSource->SetSound(sound);
}
