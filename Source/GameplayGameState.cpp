#include "GameplayGameState.h"
#include "GameStateManager.h"
#include "Graphics.h"
#include "Input.h"
#include "Camera.h"
#include "ControlSystem.h"
#include "Texture.h"
#include "AnimatedSprite.h"
#include "SpriteSheet.h"
#include "Sprite.h"
#include "Animator.h"
#include "Player.h"
#include "Background.h"
#include "InGameHudManager.h"
#include "Resources.h"
#include "UnitVectors.h"
#include "HitBoxManager.h"
#include "NPCManager.h"
#include "Enemy.h"
#include "pch.h"
#include "Error.h"
#include "StateMachine.h"
#include "GameplayOwnedSceneStates.h"
#include "EncounterHandler.h"
#include "TravellingHandler.h"
#include "TravelPrompt.h"
#include "GameOverScreen.h"

using namespace GameplayConstants;
using namespace GlobalConstants;
using namespace InGameHudConstants;

GameplayGameState::GameplayGameState() :
	m_gameStateManager(nullptr),
	m_graphics(nullptr),
	m_input(nullptr),
	m_camera(nullptr),
	m_controlSystem(nullptr),
	m_playerTexture(nullptr),
	m_hitBoxTexture(nullptr),
	m_standardShadowTexture(nullptr),
	m_largeShadowTexture(nullptr),
	m_backgroundTexture(nullptr),
	m_playerSprite(nullptr),
	m_standardShadowSprite(nullptr),
	m_hitBoxSprite(nullptr),
	m_backgroundSprite(nullptr),
	m_playerAnimator(nullptr),
	m_playerHitBoxManager(nullptr),
	m_NPCManager(nullptr),
	m_player(nullptr),
	m_background(nullptr),
	m_hudManager(nullptr),
	m_sceneStateMachine(nullptr),
	m_encounterHandler(nullptr),
	m_travellingHandler(nullptr),
	m_gameOverScreen(nullptr),
	m_canAttack(true),
	m_running(false),
	m_playerBoundary(AABB()),
	m_deltaTime(0.0f),
	GameState(L"GAMEPLAY")
{}

GameplayGameState::GameplayGameState(GameStateManager* gameStateManager) : GameplayGameState()
{
	m_gameStateManager = gameStateManager;
	m_graphics = m_gameStateManager->GetGraphics();
	m_input = m_gameStateManager->GetInput();
}

GameplayGameState::~GameplayGameState()
{
}

void GameplayGameState::OnEntry()
{
	LoadAssets();
}

void GameplayGameState::OnExit()
{
	ReleaseAll();
	DeleteAssets();
}

void GameplayGameState::LoadAssets()
{
	m_camera = new Camera();
	m_controlSystem = new ControlSystem();

	m_playerTexture = new Texture();
	m_hitBoxTexture = new Texture();
	m_standardShadowTexture = new Texture();
	m_largeShadowTexture = new Texture();
	m_backgroundTexture = new Texture();

	m_playerSprite = new Spritesheet();
	m_standardShadowSprite = new Sprite();
	m_hitBoxSprite = new Sprite();
	m_backgroundSprite = new Sprite();

	m_playerAnimator = new Animator();

	m_playerHitBoxManager = new HitBoxManager();

	m_NPCManager = new NPCManager();

	m_player = new Player();
	m_background = new Background();
	m_hudManager = new InGameHudManager();
	m_sceneStateMachine = new StateMachine<GameplayGameState>(this);
	m_encounterHandler = new EncounterHandler();
	m_travellingHandler = new TravellingHandler();

	m_playerTexture->LoadTexture(m_graphics, "GameData\\Sprites\\playerSpriteSheet.png");
	m_hitBoxTexture->LoadTexture(m_graphics, "GameData\\Sprites\\hitbox.png");
	m_standardShadowTexture->LoadTexture(m_graphics, "GameData\\Sprites\\shadow.png");
	m_largeShadowTexture->LoadTexture(m_graphics, "GameData\\Sprites\\shadow_large.png");
	m_backgroundTexture->LoadTexture(m_graphics, "GameData\\Sprites\\backgroundTest.png");

	m_playerSprite->Init(m_playerTexture, "GameData\\SpriteSheetData\\playerSpritesheetData.json");
	m_standardShadowSprite->Init(m_standardShadowTexture);
	m_standardShadowSprite->SetAlpha(0.7f);
	m_hitBoxSprite->Init(m_hitBoxTexture);
	m_backgroundSprite->Init(m_backgroundTexture);
	m_backgroundSprite->SetOrigin(Vector2::Zero);

	m_playerAnimator->Init("GameData\\AnimationData\\playerAnimationData.json");

	m_playerHitBoxManager->Init(m_hitBoxSprite, m_player, "GameData\\HitBoxData\\playerHitBoxData.json");

	m_player->LoadData("GameData\\PlayerData\\playerData.txt", "GameData\\PlayerData\\playerDamage.txt");
	m_player->Init(m_playerSprite, m_standardShadowSprite, m_playerAnimator, m_playerHitBoxManager, m_controlSystem);
	m_player->SetCamera(m_camera);
	m_camera->SetTarget(m_player);

	m_background->Init(m_backgroundSprite);
	m_background->SetCamera(m_camera);

	m_hudManager->Init(m_graphics);
	m_hudManager->SetMaxPlayerHealth(m_player->GetMaxHealth());
	m_hudManager->SetCurrentPlayerHealth(m_player->GetHealth());

	m_NPCManager->Init(m_graphics, m_camera, m_player, m_hudManager, m_standardShadowTexture, m_hitBoxTexture);
	
	m_sceneStateMachine->Init(TravellingSceneState::Instance(), nullptr, GlobalSceneState::Instance());
	m_encounterHandler->Init("GameData\\EncounterData\\encounterPositions.txt", m_NPCManager->GetEnemyList());

	m_playerBoundary.SetMin(Vector2(StartingBoundaryMinX, StartingBoundaryMinY));
	m_playerBoundary.SetMax(Vector2((float)m_background->GetSprite()->GetWidth() - 1.0f, (float)m_graphics->GetHeight() - 1.0f));
	
	m_camera->Init(GameWidth);
	
	m_running = true;
}

void GameplayGameState::DeleteAssets()
{
	if(m_travellingHandler != nullptr)
	{
		delete m_travellingHandler;
		m_travellingHandler = nullptr;
	}

	if(m_encounterHandler != nullptr)
	{
		delete m_encounterHandler;
		m_encounterHandler = nullptr;
	}

	if(m_sceneStateMachine != nullptr)
	{
		delete m_sceneStateMachine;
		m_sceneStateMachine = nullptr;
	}

	if(m_hudManager != nullptr)
	{
		delete m_hudManager;
		m_hudManager = nullptr;
	}

	if(m_background)
	{
		delete m_background;
		m_background = nullptr;
	}

	if(m_player)
	{
		delete m_player;
		m_player = nullptr;
	}

	if(m_NPCManager)
	{
		delete m_NPCManager;
		m_NPCManager = nullptr;
	}

	if(m_playerAnimator)
	{
		delete m_playerAnimator;
		m_playerAnimator = nullptr;
	}

	if(m_backgroundSprite)
	{
		delete m_backgroundSprite;
		m_backgroundSprite = nullptr;
	}

	if(m_hitBoxSprite)
	{
		delete m_hitBoxSprite;
		m_hitBoxSprite = nullptr;
	}

	if(m_standardShadowSprite)
	{
		delete m_standardShadowSprite;
		m_standardShadowSprite = nullptr;
	}

	if(m_playerSprite)
	{
		delete m_playerSprite;
		m_playerSprite = nullptr;
	}

	if(m_backgroundTexture)
	{
		delete m_backgroundTexture;
		m_backgroundTexture = nullptr;
	}

	if(m_largeShadowTexture != nullptr)
	{
		delete m_largeShadowTexture;
		m_largeShadowTexture = nullptr;
	}

	if(m_standardShadowTexture)
	{
		delete m_standardShadowTexture;
		m_standardShadowTexture = nullptr;
	}

	if(m_hitBoxTexture)
	{
		delete m_hitBoxTexture;
		m_hitBoxTexture = nullptr;
	}

	if(m_playerTexture)
	{
		delete m_playerTexture;
		m_playerTexture = nullptr;
	}

	if(m_controlSystem)
	{
		delete m_controlSystem;
		m_controlSystem = nullptr;
	}

	if(m_camera)
	{
		delete m_camera;
		m_camera = nullptr;
	}
}

void GameplayGameState::ProcessInput()
{
	if(m_input->IsKeyDown(ESC_KEY))
	{
		PostQuitMessage(0);
	}

	if(m_input->IsKeyDown('R'))
	{
		ResetGame();
	}

	if(m_input->IsKeyDown(PLAYER_UP_KEY) &&
		!m_input->IsKeyDown(PLAYER_DOWN_KEY))
	{
		if(m_input->IsKeyDown(PLAYER_LEFT_KEY) &&
			!m_input->IsKeyDown(PLAYER_RIGHT_KEY))
		{
			m_controlSystem->SetInput(Controls::UpLeft);
		}
		else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY) &&
			!m_input->IsKeyDown(PLAYER_LEFT_KEY))
		{
			m_controlSystem->SetInput(Controls::UpRight);
		}
		else
		{
			m_controlSystem->SetInput(Controls::Up);
		}
	}
	else if(m_input->IsKeyDown(PLAYER_DOWN_KEY) &&
		!m_input->IsKeyDown(PLAYER_UP_KEY))
	{
		if(m_input->IsKeyDown(PLAYER_LEFT_KEY) &&
			!m_input->IsKeyDown(PLAYER_RIGHT_KEY))
		{
			m_controlSystem->SetInput(Controls::DownLeft);

		}
		else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY) &&
			!m_input->IsKeyDown(PLAYER_LEFT_KEY))
		{
			m_controlSystem->SetInput(Controls::DownRight);
		}
		else
		{
			m_controlSystem->SetInput(Controls::Down);
		}
	}
	else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY) &&
		!m_input->IsKeyDown(PLAYER_LEFT_KEY))
	{
		m_controlSystem->SetInput(Controls::Right);
	}
	else if(m_input->IsKeyDown(PLAYER_LEFT_KEY) && 
		!m_input->IsKeyDown(PLAYER_RIGHT_KEY))
	{
		m_controlSystem->SetInput(Controls::Left);
	}

	if(m_input->IsKeyDown(PLAYER_A_KEY) &&
		m_controlSystem->CanAttack())
	{
		m_controlSystem->SetInput(Controls::Attack);
		m_controlSystem->CanAttack(false);
		return;
	}

	if(!(m_input->IsKeyDown(PLAYER_UP_KEY) ||
		m_input->IsKeyDown(PLAYER_DOWN_KEY) ||
		m_input->IsKeyDown(PLAYER_LEFT_KEY) ||
		m_input->IsKeyDown(PLAYER_RIGHT_KEY) ||
		m_input->IsKeyDown(PLAYER_A_KEY)))
	{
		m_controlSystem->SetInput(Controls::None);
	}

	if(!m_input->IsKeyDown(PLAYER_A_KEY))
	{
		m_controlSystem->CanAttack(true);
	}
}

void GameplayGameState::Update(float deltaTime)
{
	m_deltaTime = deltaTime;
	m_sceneStateMachine->Update();
}

void GameplayGameState::CheckForEncounter()
{
	if(m_camera->GetPosition().x < m_encounterHandler->GetEncounterPosition())
		return;

	m_sceneStateMachine->ChangeState(EncounterSceneState::Instance());
}

void GameplayGameState::Tick(float deltaTime)
{
	m_player->Update(deltaTime);
	m_camera->Update(deltaTime);
	m_NPCManager->Update(deltaTime);
	m_background->Update(deltaTime);
	m_hudManager->SetMaxPlayerHealth(m_player->GetMaxHealth());
	m_hudManager->SetCurrentPlayerHealth(m_player->GetHealth());
	m_hudManager->UpdatePlayerLives(m_player->GetLives());
	m_hudManager->GetTravelPrompt()->Update(deltaTime);

	if(m_player->IsDead() && m_player->GetLives() > 0)
		m_player->Respawn();
}

void GameplayGameState::ProcessCollisions()
{
	std::vector<Enemy*> enemyList = m_NPCManager->GetEnemyList();

	for(size_t i = 0; i < enemyList.size(); i++)
	{
		Enemy* enemy = enemyList[i];

		// true if player hitbox is active and 
		if(m_player->GetHitBoxManager()->IsHitBoxActive() &&
			fabs(enemy->GetGroundPosition().y - m_player->GetGroundPosition().y) < VerticalHitRange)
		{
			// check player hitbox vs enemy hurtboxes
			if(m_player->GetHitBoxManager()->GetHitBox().OnCollision(
				enemy->GetHitBoxManager()->GetHurtBox()))
			{
				enemy->ApplyDamage(m_player, m_player->GetDamage());
				enemy->ShowEnemyHud();
				m_player->GetHitBoxManager()->KillAll();
				return;
			}
		}

		if(enemy->GetHitBoxManager()->IsHitBoxActive() &&
			fabs(m_player->GetGroundPosition().y - enemy->GetGroundPosition().y) < VerticalHitRange)
		{
			// check player hitbox vs enemy hurtboxes
			if(enemy->GetHitBoxManager()->GetHitBox().OnCollision(
				m_player->GetHitBoxManager()->GetHurtBox()))
			{
				m_player->ApplyDamage(enemy, enemy->GetDamage());
				enemy->ShowEnemyHud();
				return;
			}
		}
	}

	Vector2 playerBoundaryMin = m_playerBoundary.GetMin();
	Vector2 playerBoundaryMax = m_playerBoundary.GetMax();

	if(m_player->GetGroundPosition().x < playerBoundaryMin.x)
	{
		m_player->SetPosition(Vector2(playerBoundaryMin.x, m_player->GetPositionY()));
		m_player->SetCurrentVelocity(Vector2(0.0f, m_player->GetCurrentVelocity().y));
		m_player->SetTargetVelocity(Vector2(0.0f, m_player->GetTargetVelocity().y));
	}

	if(m_player->GetGroundPosition().y < playerBoundaryMin.y)
	{
		m_player->SetPosition(Vector2(m_player->GetPositionX(), playerBoundaryMin.y));
		m_player->SetCurrentVelocity(Vector2(m_player->GetCurrentVelocity().x, 0.0f));
		m_player->SetTargetVelocity(Vector2(m_player->GetTargetVelocity().x, 0.0f));
	}

	if(m_player->GetGroundPosition().x > playerBoundaryMax.x)
	{
		m_player->SetPosition(Vector2(playerBoundaryMax.x, m_player->GetPositionY()));
		m_player->SetCurrentVelocity(Vector2(0.0f, m_player->GetCurrentVelocity().y));
		m_player->SetTargetVelocity(Vector2(0.0f, m_player->GetTargetVelocity().y));
	}

	if(m_player->GetGroundPosition().y > playerBoundaryMax.y)
	{
		m_player->SetPosition(Vector2(m_player->GetPositionX(), playerBoundaryMax.y));
		m_player->SetCurrentVelocity(Vector2(m_player->GetCurrentVelocity().x, 0.0f));
		m_player->SetTargetVelocity(Vector2(m_player->GetTargetVelocity().x, 0.0f));
	}

	for(size_t i = 0; i < enemyList.size(); i++)
	{
		Enemy* enemy = enemyList[i];

		if(enemy->GetGroundPosition().x < StartingBoundaryMinX)
		{
			enemy->SetPosition(Vector2(StartingBoundaryMinX, enemy->GetPositionY()));
			enemy->SetCurrentVelocity(Vector2(0.0f, enemy->GetCurrentVelocity().y));
			enemy->SetTargetVelocity(Vector2(0.0f, enemy->GetTargetVelocity().y));
		}

		if(enemy->GetGroundPosition().y > playerBoundaryMax.y)
		{
			enemy->SetPosition(enemy->GetPositionX(), playerBoundaryMax.y);
			enemy->SetCurrentVelocity(Vector2(enemy->GetCurrentVelocity().x, 0.0f));
			enemy->SetTargetVelocity(Vector2(enemy->GetTargetVelocity().x, 0.0f));
		}

		if(enemy->GetGroundPosition().y < playerBoundaryMin.y)
		{
			enemy->SetPosition(enemy->GetPositionX(), playerBoundaryMin.y);
			enemy->SetCurrentVelocity(Vector2(enemy->GetCurrentVelocity().x, 0.0f));
			enemy->SetTargetVelocity(Vector2(enemy->GetTargetVelocity().x, 0.0f));
		}
	}
}

void GameplayGameState::Render()
{
	m_background->Render(m_graphics);
	m_player->Render(m_graphics);
	m_NPCManager->Render(m_graphics);
	m_hudManager->Render(m_graphics);
}

void GameplayGameState::ReleaseAll()
{
	if(m_hudManager) { m_hudManager->ReleaseAll(); }
	if(m_backgroundTexture) { m_backgroundTexture->Release(); }
	if(m_standardShadowTexture) { m_standardShadowTexture->Release(); }
	if(m_largeShadowTexture) { m_largeShadowTexture->Release(); }
	if(m_hitBoxTexture) { m_hitBoxTexture->Release(); }
	if(m_playerTexture) { m_playerTexture->Release(); }
}

void GameplayGameState::ResetGame()
{
	m_input->ClearAll();
	m_player->Reset();
	m_NPCManager->Reset();
	m_backgroundSprite->SetPosition(Vector2::Zero);
	m_camera->Reset();
	m_camera->SetTarget(m_player);
	m_hudManager->Reset();
	m_encounterHandler->SetEncounterIndex(0);
	m_sceneStateMachine->ChangeState(TravellingSceneState::Instance());
	SetPlayerBoundaryX(StartingBoundaryMinX, (float)m_background->GetSprite()->GetWidth());
}

void GameplayGameState::SetPlayerBoundaryX(float minX, float maxX)
{
	Vector2 newMin = Vector2(minX, m_playerBoundary.GetMin().y);
	Vector2 newMax = Vector2(maxX, m_playerBoundary.GetMax().y);
	
	m_playerBoundary.SetAABB(AABB(newMin, newMax));
}