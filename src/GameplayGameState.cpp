#include "GameplayGameState.h"

#include "AABB.h"
#include "Animator.h"
#include "AudioEngine.h"
#include "Camera.h"
#include "Collider.h"
#include "ControlSystem.h"
#include "Enemy.h"
#include "EnemySpawnManager.h"
#include "GameDataManager.h"
#include "GameplayConstants.h"
#include "GameState.h"
#include "GameStateManager.h"
#include "GameStateNameLibrary.h"
#include "GlobalConstants.h"
#include "HitBoxManager.h"
#include "ImpactFxPool.h"
#include "Input.h"
#include "LevelCollision.h"
#include "LevelRenderer.h"
#include "NPCManager.h"
#include "ParticleSystem.h"
#include "Player.h"
#include "PlayerAttackState.h"
#include "PlayerBlockState.h"
#include "PlayerBuildSpecialState.h"
#include "PlayerConstants.h"
#include "PlayerDeadState.h"
#include "PlayerHurtState.h"
#include "PlayerIdleState.h"
#include "PlayerKnockbackState.h"
#include "Randomiser.h"
#include "SpriteSheet.h"
#include "StateMachine.h"
#include "TilemapLoader.h"
#include "UIManager.h"
#include "UnitVectors.h"

#include <cmath>
#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>
#include <vector>

using namespace GameStateNameLibrary;
using namespace GameplayConstants;
using namespace GlobalConstants;

GameplayGameState::GameplayGameState() :
	m_graphics(nullptr),
	m_input(nullptr),
	m_camera(nullptr),
	m_controlSystem(nullptr),
	m_NPCManager(nullptr),
	m_player(nullptr),
	m_levelRenderer(nullptr),
	m_enemySpawnManager(nullptr),
	m_canAttack(true),
	m_running(false),
	m_deltaTime(0.0f),
	m_stopTimer(0.0f),
	m_displayHitBoxes(false),
	m_hidePlayerHud(false),
	m_impactFxPool(nullptr),
	m_activeImpacts(0),
	m_particleSystem(nullptr),
	m_collisionCooldown(0.0f),
	m_isCollisionOnCooldown(false),
	m_isHitStopRunning(false),
	GameState(Gameplay)
{}

GameplayGameState::GameplayGameState(GameStateManager* gameStateManager) : GameplayGameState()
{
	m_gameStateManager = gameStateManager;
	m_graphics = m_gameStateManager->GetGraphics();
	m_input = m_gameStateManager->GetInput();
}

GameplayGameState::~GameplayGameState()
{
	DeleteAssets();
}

void GameplayGameState::OnEntry()
{
}

void GameplayGameState::OnExit()
{
}

void GameplayGameState::LoadAssets()
{
	LevelCollision::Init();
	TilemapLoader::Init();

	//TilemapLoader::LoadTilemap("assets\\data\\tilemaps\\tm_lift.json");
	//TilemapLoader::LoadTilemap("assets\\data\\tilemaps\\tm_trailer-level-showcase.json");
	TilemapLoader::LoadTilemap("assets\\data\\tilemaps\\tm_demo.json");

	GameDataManager::LoadAllEnemyDefinitions();
	m_camera = new Camera();
	m_controlSystem = new ControlSystem();
	m_NPCManager = new NPCManager();
	m_player = new Player();
	m_levelRenderer = new LevelRenderer();
	m_enemySpawnManager = new EnemySpawnManager();

	m_player->Init(m_controlSystem);
	m_player->SetCamera(m_camera);
	m_camera->SetTarget(m_player);

	m_levelRenderer->Init(m_graphics, m_camera);
	m_enemySpawnManager->Init();
	LevelCollision::CreateBounds(m_levelRenderer);

	m_NPCManager->Init(m_graphics, m_camera, m_player);
	m_camera->Init(GameWidth);

	m_impactFxPool = new ImpactFxPool();

	m_particleSystem = new ParticleSystem();
	m_particleSystem->Init(m_graphics);

	m_running = true;
}

void GameplayGameState::DeleteAssets()
{
	m_activeImpacts.clear();

	delete m_particleSystem;
	m_particleSystem = nullptr;

	delete m_impactFxPool;
	m_impactFxPool = nullptr;

	delete m_enemySpawnManager;
	m_enemySpawnManager = nullptr;

	delete m_levelRenderer;
	m_levelRenderer = nullptr;

	delete m_player;
	m_player = nullptr;

	delete m_NPCManager;
	m_NPCManager = nullptr;

	delete m_controlSystem;
	m_controlSystem = nullptr;

	delete m_camera;
	m_camera = nullptr;

	LevelCollision::Shutdown();
	TilemapLoader::Shutdown();
}

void GameplayGameState::ProcessInput()
{
	if(m_player->GetStateMachine()->IsInState(*PlayerHurtState::Instance()) || 
		m_player->GetStateMachine()->IsInState(*PlayerKnockbackState::Instance()) ||
		m_player->GetStateMachine()->IsInState(*PlayerDeadState::Instance()))
		return;

	auto gamePadState = m_input->GetGamePadState();
	auto buttons = m_input->GetGamePadButtons();

	if(m_input->IsKeyDown(ESC_KEY) || gamePadState.IsMenuPressed())
	{
		m_gameStateManager->SwitchState(Paused);
	}

#ifdef _DEBUG
	if(m_input->IsKeyDown('R') || gamePadState.IsViewPressed())
		ResetGame();

	if(m_input->WasKeyPressed(F4_KEY))
	{
		ToggleHitBoxes();
	}

	if(m_input->WasKeyPressed(F5_KEY))
	{
		TogglePlayerHud();
	}

	if(m_input->WasKeyPressed(F9_KEY))
	{
		m_camera->StartShake(3.0f, 10.0f);
	}

#endif

	if(m_input->IsKeyDown(PLAYER_UP_KEY) || gamePadState.IsDPadUpPressed() || gamePadState.IsLeftThumbStickUp() &&
		!m_input->IsKeyDown(PLAYER_DOWN_KEY))
	{
		if(m_input->IsKeyDown(PLAYER_LEFT_KEY) || gamePadState.IsDPadLeftPressed() || gamePadState.IsLeftThumbStickLeft() &&
			!m_input->IsKeyDown(PLAYER_RIGHT_KEY))
		{
			m_player->Move(UnitVectors::UpLeft);
		}
		else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY) || gamePadState.IsDPadRightPressed() || gamePadState.IsLeftThumbStickRight() &&
			!m_input->IsKeyDown(PLAYER_LEFT_KEY))
		{
			m_player->Move(UnitVectors::UpRight);
		}
		else
		{
			m_player->Move(UnitVectors::Up);
		}
	}
	else if(m_input->IsKeyDown(PLAYER_DOWN_KEY) || gamePadState.IsDPadDownPressed() || gamePadState.IsLeftThumbStickDown())
	{
		if(m_input->IsKeyDown(PLAYER_LEFT_KEY) || gamePadState.IsDPadLeftPressed() || gamePadState.IsLeftThumbStickLeft() &&
			!m_input->IsKeyDown(PLAYER_RIGHT_KEY))
		{
			m_player->Move(UnitVectors::DownLeft);
		}
		else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY) || gamePadState.IsDPadRightPressed() || gamePadState.IsLeftThumbStickRight() &&
			!m_input->IsKeyDown(PLAYER_LEFT_KEY))
		{
			m_player->Move(UnitVectors::DownRight);
		}
		else
		{
			m_player->Move(UnitVectors::Down);
		}
	}
	else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY) || gamePadState.IsDPadRightPressed() || gamePadState.IsLeftThumbStickRight() &&
		!m_input->IsKeyDown(PLAYER_LEFT_KEY))
	{
		m_player->Move(UnitVectors::Right);
	}
	else if(m_input->IsKeyDown(PLAYER_LEFT_KEY) || gamePadState.IsDPadLeftPressed() || gamePadState.IsLeftThumbStickLeft() &&
		!m_input->IsKeyDown(PLAYER_RIGHT_KEY))
	{
		m_player->Move(UnitVectors::Left);
	}

	if(m_input->WasKeyPressed(PLAYER_RIGHT_KEY) || 
		m_input->WasGamePadButtonPressed(buttons.dpadRight) || m_input->WasGamePadButtonPressed(buttons.leftStickRight))
	{
		m_controlSystem->SetControlsPressed(Controls::Right);
		m_controlSystem->ResetDoubleTap();
			
		if(m_controlSystem->GetLastKeyPressed() == Controls::Right &&
			m_controlSystem->CanRun())
		{
			m_player->Run();
		}
	}
	
	if(m_input->WasKeyPressed(PLAYER_LEFT_KEY) || 
		m_input->WasGamePadButtonPressed(buttons.dpadLeft) || m_input->WasGamePadButtonPressed(buttons.leftStickLeft))
	{
		m_controlSystem->SetControlsPressed(Controls::Left);
		m_controlSystem->ResetDoubleTap();

		if(m_controlSystem->GetLastKeyPressed() == Controls::Left &&
			m_controlSystem->CanRun())
		{
			m_player->Run();
		}
	}

	if(m_input->IsKeyDown(PLAYER_Z_KEY) || gamePadState.IsBPressed())
	{
		m_player->Block();
		return;
	}
	else if(m_player->GetStateMachine()->IsInState(*PlayerBlockState::Instance()))
	{
		m_player->GetStateMachine()->ChangeState(PlayerIdleState::Instance());
	}

	if(m_input->WasKeyPressed(PLAYER_X_KEY) || m_input->WasGamePadButtonPressed(buttons.x))
	{
		m_controlSystem->SetControlsPressed(Controls::NormalAttack);
		m_controlSystem->ResetComboTimer();
		return;
	}

	if(m_input->WasKeyPressed(PLAYER_C_KEY) || m_input->WasGamePadButtonPressed(buttons.y))
	{
		m_controlSystem->SetControlsPressed(Controls::StrongAttack);
		m_controlSystem->ResetComboTimer();
		return;
	}

	if(!m_player->GetStateMachine()->IsInState(*PlayerAttackState::Instance()) 
		&& !m_player->IsSpecialReady() 
		&& (m_input->IsKeyDown(PLAYER_V_KEY) || gamePadState.IsAPressed()))
	{
		if(!m_player->GetStateMachine()->IsInState(*PlayerBuildSpecialState::Instance()))
			m_player->GetStateMachine()->ChangeState(PlayerBuildSpecialState::Instance());
		
		m_player->IncreaseSpecial(NormalSpecialRate * m_deltaTime);
	}
	else if(m_player->GetStateMachine()->IsInState(*PlayerBuildSpecialState::Instance()))
	{
		m_player->GetStateMachine()->ChangeState(PlayerIdleState::Instance());
	}

	if(m_player->IsSpecialReady() && (m_input->WasKeyPressed(PLAYER_V_KEY) || m_input->WasGamePadButtonPressed(buttons.a)))
	{
		m_controlSystem->SetControlsPressed(Controls::SpecialAttack);
	}

	if(!(m_input->IsKeyDown(PLAYER_UP_KEY) || gamePadState.IsDPadUpPressed() || gamePadState.IsLeftThumbStickUp() ||
		m_input->IsKeyDown(PLAYER_DOWN_KEY) || gamePadState.IsDPadDownPressed() || gamePadState.IsLeftThumbStickDown() ||
		m_input->IsKeyDown(PLAYER_LEFT_KEY) || gamePadState.IsDPadLeftPressed() || gamePadState.IsLeftThumbStickLeft() ||
		m_input->IsKeyDown(PLAYER_RIGHT_KEY) || gamePadState.IsDPadRightPressed() || gamePadState.IsLeftThumbStickRight() ||
		m_input->IsKeyDown(PLAYER_X_KEY) ||
		m_input->IsKeyDown(PLAYER_Z_KEY) ||
		m_input->WasKeyPressed(PLAYER_C_KEY)))
	{
		m_player->Move(Vector2::Zero);
		m_player->Walk();
	}
}

void GameplayGameState::Update(float deltaTime)
{
	UIManager::Update(deltaTime);

	m_deltaTime = deltaTime;
	Tick(deltaTime);
}

void GameplayGameState::Tick(float deltaTime)
{
	m_camera->Update(deltaTime);
	m_levelRenderer->Update(deltaTime);
	m_enemySpawnManager->Update(deltaTime);

	if(m_stopTimer > 0)
	{
		m_isHitStopRunning = true;
		m_stopTimer -= deltaTime;
		return;
	} 
	else if(m_isHitStopRunning)
	{
		m_isHitStopRunning = false;
		AudioEngine::Instance()->Resume();
	}

	if(m_collisionCooldown > 0)
		m_collisionCooldown -= deltaTime;

	if(m_collisionCooldown <= 0)
		m_isCollisionOnCooldown = false;

	m_controlSystem->Update(deltaTime);
	m_player->Update(deltaTime);
	m_NPCManager->Update(deltaTime);

	if(m_player->IsDead())
	{
		//@TODO add game over sequence
		m_player->Respawn();
	}

	for(auto it = m_activeImpacts.begin(); it != m_activeImpacts.end();)
	{
		(*it)->Update(deltaTime);

		if(!(*it)->IsActive())
		{
			m_impactFxPool->ReturnObject(*it);
			it = m_activeImpacts.erase(it);
		}
		else
		{
			++it;
		}
	}

	m_particleSystem->Update(deltaTime);
	LevelCollision::Update(m_camera);
}

void GameplayGameState::ProcessCollisions()
{
	if(m_stopTimer > 0 || m_isCollisionOnCooldown)	return;

	std::vector<Enemy*> enemyList = m_NPCManager->GetEnemyList();

	auto isPlayerHitBoxActive = m_player->GetHitBoxManager()->IsHitBoxActive();
	auto playerGroundPositionX = m_player->GetGroundPosition().x;
	auto playerGroundPositionY = m_player->GetGroundPosition().y;

	for(size_t i = 0; i < enemyList.size(); i++)
	{
		Enemy* enemy = enemyList[i];

		if(!enemy->IsActive() || enemy->IsDead()) continue;

		auto playerHitBox = m_player->GetHitBoxManager()->GetHitBox();
		auto playerVerticalRange = VerticalHitRange;

		if(m_player->GetStateMachine()->GetCurrentState()->GetName() == "special")
			playerVerticalRange = GameHeight;

		// true if player hitbox is active and enemy is in vertical range
		if(isPlayerHitBoxActive && fabs(enemy->GetGroundPosition().y - playerGroundPositionY) < playerVerticalRange)
		{
			// check player has hit an enemy
			if(playerHitBox.OnCollision(
				enemy->GetHitBoxManager()->GetHurtBox()))
			{
				auto damageData = m_player->GetDamageData();
				auto groundPosition = enemy->GetGroundPosition();
				auto frameData = enemy->GetSprite()->GetFrameData(enemy->GetAnimator()->GetCurrentFrame());
				auto spriteHeight = frameData.spriteSourceSize.bottom;
				auto normalDirection = Vector2(enemy->GetGroundPosition() - m_player->GetGroundPosition());
				normalDirection.Normalize();

				enemy->ApplyDamage(m_player, damageData.amount);
				enemy->ShowEnemyHud();

				auto animation = m_player->GetAnimator()->GetAnimation();
				if(animation.name.contains("Strong") || animation.name.contains("special"))
					m_camera->StartShake(2.0f, 3.0f);

				m_player->IncreaseSpecial();
				m_player->GetControlSystem()->IncrementHitComboCount();

				if(enemy->GetHealth() <= 0.0f) m_player->AddKill();

				m_stopTimer = damageData.hitStopDuration;
				AudioEngine::Instance()->Pause();
				m_isCollisionOnCooldown = true;
				m_collisionCooldown = damageData.hitStopDuration;

				auto impactFx = m_impactFxPool->Get();
				m_activeImpacts.push_back(impactFx);
				impactFx->DisplayFx(Vector2(groundPosition.x, groundPosition.y - spriteHeight * 0.5f) - m_camera->GetPosition());
				SpawnParticles(impactFx->Position(), normalDirection, (Color)Colors::Green, (Color)Colors::DarkGreen, 1.0f, 200);
			}
		}
	}

	for(size_t i = 0; i < enemyList.size(); i++)
	{
		Enemy* enemy = enemyList[i];

		if(!enemy->IsActive() || enemy->IsDead()) return;

		// true if enemy hitbox is active and player is in vertical range
		if(enemy->GetHitBoxManager()->IsHitBoxActive() &&
			fabs(playerGroundPositionY - enemy->GetGroundPosition().y) < VerticalHitRange)
		{
			// check enemy has hit the player
			if(enemy->GetHitBoxManager()->GetHitBox().OnCollision(
				m_player->GetHitBoxManager()->GetHurtBox()))
			{
				auto damageData = enemy->GetDamageData();
				auto enemyVelocity = enemy->GetCurrentVelocity();
				enemyVelocity.Normalize();
				auto normalDirection = m_player->GetGroundPosition() - enemy->GetGroundPosition();
				normalDirection.Normalize();

				auto frameData = m_player->GetSprite()->GetFrameData(m_player->GetAnimator()->GetCurrentFrame());
				auto spriteHeight = frameData.spriteSourceSize.bottom;

				m_player->ApplyDamage(enemy, damageData.amount);
				m_player->SetPositionX(m_player->GetPositionX() + enemyVelocity.x);
				m_player->IncreaseSpecial();
				m_camera->StartShake(1.0f, 2.0f);

				if(m_player->GetFacingDirection() == enemy->GetFacingDirection())
					m_player->FlipHorizontally(m_player->GetFacingDirection() != Vector3::Left);

				enemy->ShowEnemyHud();

				m_stopTimer = damageData.hitStopDuration;
				AudioEngine::Instance()->Pause();
				m_isCollisionOnCooldown = true;
				m_collisionCooldown = damageData.hitStopDuration;

				auto impactFx = m_impactFxPool->Get();
				m_activeImpacts.push_back(impactFx);
				impactFx->DisplayFx(Vector2(playerGroundPositionX, playerGroundPositionY - spriteHeight * 0.5f) - m_camera->GetPosition());

				if(m_player->GetStateMachine()->IsInState(*PlayerBlockState::Instance()))
				{
					m_player->SetPositionX((m_player->GetGroundPosition() + Vector2(normalDirection * 2.0f)).x);
				}
				else
				{
					SpawnParticles(impactFx->Position(), normalDirection, (Color)Colors::Red, (Color)Colors::DarkRed, 1.0f, 200);
				}

				return;
			}
		}
	}
}

void GameplayGameState::SpawnParticles(const Vector2& position, const Vector2& velocity, Color startColour, Color endColour, float lifeTime, unsigned int number)
{
	m_particleData.Velocity = velocity;
	m_particleData.Position = position;
	m_particleData.ColorBegin = startColour;
	m_particleData.ColorEnd = endColour;
	m_particleData.LifeTime = lifeTime;

	for (unsigned int i = 0; i < number; i++)
	{
		m_particleData.VelocityVariation.x = (Randomiser::Instance()->GetRandNumUniform(1.0f, 5.0f));
		m_particleData.VelocityVariation.y = (Randomiser::Instance()->GetRandNumUniform(-10.0f, 1.0f));
		m_particleData.VelocityVariation.Normalize();
		m_particleData.VelocityVariation *= Randomiser::Instance()->GetRandNumUniform(1.0f, 40.0f);

		m_particleSystem->Emit(m_particleData);
	}
}

void GameplayGameState::Render()
{
	m_levelRenderer->Render(m_graphics);
	m_player->Render(m_graphics);
	m_NPCManager->Render(m_graphics);
	m_particleSystem->Render(m_graphics); 
	UIManager::Render(m_graphics);
	LevelCollision::Render(m_graphics);

	for(auto* it : m_activeImpacts)
	{
		it->Render(m_graphics);
	}
}

void GameplayGameState::ResetGame()
{
	m_input->ClearAll();
	m_player->Reset();
	m_NPCManager->Reset();
	m_camera->Reset();
	//m_camera->SetTarget(m_player);
	UpdateGameBounds(0, (float)m_levelRenderer->GetLevelPixelWidth());
}

void GameplayGameState::UpdateGameBounds(float minX, float maxX)
{
	Collider* upperBounds = LevelCollision::GetCollider(UpperBoundsId);
	Collider* lowerBounds = LevelCollision::GetCollider(LowerBoundsId);
	Collider* leftBounds = LevelCollision::GetCollider(LeftBoundsId);
	Collider* rightBounds = LevelCollision::GetCollider(RightBoundsId);

	upperBounds->SetAABB(AABB(Vector2(minX, upperBounds->GetAABB().GetMin().y), Vector2(maxX, upperBounds->GetAABB().GetMax().y)));
	lowerBounds->SetAABB(AABB(Vector2(minX, lowerBounds->GetAABB().GetMin().y), Vector2(maxX, lowerBounds->GetAABB().GetMax().y)));
	leftBounds->SetAABB(AABB(Vector2(minX - 10, 0), Vector2(minX, GameHeight)));
	rightBounds->SetAABB(AABB(Vector2(maxX, 0), Vector2(maxX + 10, GameHeight)));
}

void GameplayGameState::ToggleHitBoxes()
{
	m_displayHitBoxes = !m_displayHitBoxes;

	m_player->GetHitBoxManager()->SetVisible(m_displayHitBoxes);

	auto npcList = m_NPCManager->GetEnemyList();

	for(Enemy* enemy : npcList)
	{
		enemy->GetHitBoxManager()->SetVisible(m_displayHitBoxes);
	}

	LevelCollision::SetVisible(m_displayHitBoxes);
}

void GameplayGameState::TogglePlayerHud()
{
	m_hidePlayerHud = !m_hidePlayerHud;

	auto hud = UIManager::GetView("UI Hud View");
	
	if(hud == nullptr) return;

	hud->ForceHide(m_hidePlayerHud);
}