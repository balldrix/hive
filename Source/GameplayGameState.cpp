#include "GameplayGameState.h"
#include "GameStateManager.h"
#include "Graphics.h"
#include "Input.h"
#include "Texture.h"
#include "AnimatedSprite.h"
#include "SpriteSheet.h"
#include "Sprite.h"
#include "Animator.h"
#include "Player.h"
#include "Enemy.h"
#include "Resources.h"
#include "UnitVectors.h"
#include "ControlSystem.h"
#include "HitBoxManager.h"

GameplayGameState::GameplayGameState() :
	m_gameStateManager(nullptr),
	m_graphics(nullptr),
	m_input(nullptr),
	m_controlSystem(nullptr),
	m_playerTexture(nullptr),
	m_enemyTexture(nullptr),
	m_hitBoxTexture(nullptr),
	m_shadowTexture(nullptr),
	m_backgroundTexture(nullptr),
	m_playerSprite(nullptr),
	m_playerShadowSprite(nullptr),
	m_enemySprite(nullptr),
	m_enemyShadowSprite(nullptr),
	m_hitBoxSprite(nullptr),
	m_backgroundSprite(nullptr),
	m_playerAnimator(nullptr),
	m_enemyAnimator(nullptr),
	m_player(nullptr),
	m_enemy(nullptr),
	m_playerHitBoxManager(nullptr),
	m_enemyHitBoxManager(nullptr),
	m_canAttack(true),
	m_running(false),
	GameState(L"GAMEPLAY")
{}

GameplayGameState::GameplayGameState(GameStateManager* gameStateManager) :
	m_gameStateManager(nullptr),
	m_graphics(nullptr),
	m_input(nullptr),
	m_controlSystem(nullptr),
	m_playerTexture(nullptr),
	m_enemyTexture(nullptr),
	m_hitBoxTexture(nullptr),
	m_shadowTexture(nullptr),
	m_backgroundTexture(nullptr),
	m_playerSprite(nullptr),
	m_playerShadowSprite(nullptr),
	m_enemySprite(nullptr),
	m_enemyShadowSprite(nullptr),
	m_hitBoxSprite(nullptr),
	m_backgroundSprite(nullptr),
	m_playerAnimator(nullptr),
	m_enemyAnimator(nullptr),
	m_player(nullptr),
	m_enemy(nullptr),
	m_playerHitBoxManager(nullptr),
	m_enemyHitBoxManager(nullptr),
	m_canAttack(true),
	m_running(false),
	GameState(L"GAMEPLAY")
{
	// get essential pointers from gamestate manager
	m_gameStateManager = gameStateManager;
	m_graphics = m_gameStateManager->GetGraphics();
	m_input = m_gameStateManager->GetInput();
}

GameplayGameState::~GameplayGameState()
{
}

void GameplayGameState::OnEntry()
{
	// load assets for the gameplay state
	LoadAssets();
}

void GameplayGameState::OnExit()
{
	// release memory and delete assets
	ReleaseAll();
	DeleteAssets();
}

void GameplayGameState::LoadAssets()
{
	// seed random generator
	srand((int)time(NULL));

	// init control system
	m_controlSystem = new ControlSystem();

	// create texture memory
	m_playerTexture = new Texture();
	m_enemyTexture = new Texture();
	m_hitBoxTexture = new Texture();
	m_shadowTexture = new Texture();
	m_backgroundTexture = new Texture();

	// create sprite memory 
	m_playerSprite = new SpriteSheet();
	m_playerShadowSprite = new Sprite();

	m_enemySprite = new SpriteSheet();
	m_enemyShadowSprite = new Sprite();
	
	m_hitBoxSprite = new Sprite();
	m_backgroundSprite = new Sprite();

	// create animator memory
	m_playerAnimator = new Animator();
	m_enemyAnimator = new Animator();

	// create hitbox managers
	m_playerHitBoxManager = new HitBoxManager();
	m_enemyHitBoxManager = new HitBoxManager();

	// create objects in memory
	m_player = new Player();
	m_enemy = new Enemy();

	// load textures
	m_playerTexture->LoadTexture(m_graphics, "GameData\\Sprites\\playerSpriteSheet.png");
	m_enemyTexture->LoadTexture(m_graphics, "GameData\\Sprites\\dummySpritesheet.png");
	m_hitBoxTexture->LoadTexture(m_graphics, "GameData\\Sprites\\hitbox.png");
	m_shadowTexture->LoadTexture(m_graphics, "GameData\\Sprites\\shadow.png");
	m_backgroundTexture->LoadTexture(m_graphics, "GameData\\Sprites\\backgroundTest.png");

	// init sprites
	m_playerSprite->Init(m_playerTexture, "GameData\\SpriteSheetData\\playerSpritesheetData.json");
	m_playerShadowSprite->Init(m_shadowTexture);
	m_playerShadowSprite->SetAlpha(0.7f);
	m_enemySprite->Init(m_enemyTexture, "GameData\\SpriteSheetData\\dummySpritesheetData.json");
	m_enemyShadowSprite->Init(m_shadowTexture);
	m_enemyShadowSprite->SetAlpha(0.7f);
	m_hitBoxSprite->Init(m_hitBoxTexture);
	m_backgroundSprite->Init(m_backgroundTexture);
	m_backgroundSprite->SetOrigin(Vector2::Zero);

	// init animator
	m_playerAnimator->Init("GameData\\AnimationData\\playerAnimationData.json");
	m_enemyAnimator->Init("GameData\\AnimationData\\dummyAnimationData.json");

	// init hitbox managers
	m_playerHitBoxManager->Init(m_hitBoxSprite, m_player, "GameData\\HitBoxData\\playerHitBoxData.json");
	m_enemyHitBoxManager->Init(m_hitBoxSprite, m_enemy, "GameData\\HitBoxData\\dummyHitBoxData.json");

	// init game objects
	m_player->Init(Vector2((float)PlayerStartScreenPositionX, (float)PlayerStartScreenPositionY), m_playerSprite, m_playerShadowSprite, m_playerAnimator, m_playerHitBoxManager,  m_controlSystem);
	m_enemy->Init(Vector2((float)EnemyStartScreenPositionX, (float)EnemyStartScreenPositionY), m_enemySprite, m_enemyShadowSprite, m_enemyAnimator, m_enemyHitBoxManager);

	m_enemy->SetPlayerTarget(m_player);

	// set running to true
	m_running = true;
}

void GameplayGameState::DeleteAssets()
{
	// delete enemy
	if(m_enemy)
	{
		delete m_enemy;
		m_enemy = nullptr;
	}

	// delete player
	if(m_player)
	{
		delete m_player;
		m_player = nullptr;
	}

	// delete hit box managers
	if(m_enemyHitBoxManager)
	{
		delete m_enemyHitBoxManager;
		m_enemyHitBoxManager = nullptr;
	}

	if(m_playerHitBoxManager)
	{
		delete m_playerHitBoxManager;
		m_playerHitBoxManager = nullptr;
	}

	// delete animators
	if(m_enemyAnimator)
	{
		delete m_enemyAnimator;
		m_enemyAnimator = nullptr;
	}

	if(m_playerAnimator)
	{
		delete m_playerAnimator;
		m_playerAnimator = nullptr;
	}

	// delete sprites
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

	if(m_enemyShadowSprite)
	{
		delete m_enemyShadowSprite;
		m_enemyShadowSprite = nullptr;
	}

	if(m_enemySprite)
	{
		delete m_enemySprite;
		m_enemySprite = nullptr;
	}

	if(m_playerShadowSprite)
	{
		delete m_playerShadowSprite;
		m_playerShadowSprite = nullptr;
	}

	if(m_playerSprite)
	{
		delete m_playerSprite;
		m_playerSprite = nullptr;
	}

	// delete textures
	if(m_backgroundTexture)
	{
		delete m_backgroundTexture;
		m_backgroundTexture = nullptr;
	}

	if(m_shadowTexture)
	{
		delete m_shadowTexture;
		m_shadowTexture = nullptr;
	}

	if(m_hitBoxTexture)
	{
		delete m_hitBoxTexture;
		m_hitBoxTexture = nullptr;
	}

	if(m_enemyTexture)
	{
		delete m_enemyTexture;
		m_enemyTexture = nullptr;
	}

	if(m_playerTexture)
	{
		delete m_playerTexture;
		m_playerTexture = nullptr;
	}

	// delete control system
	if(m_controlSystem)
	{
		delete m_controlSystem;
		m_controlSystem = nullptr;
	}
}

void GameplayGameState::ProcessInput()
{
	// quit when escape key is pressed
	if(m_input->IsKeyDown(ESC_KEY))
	{
		PostQuitMessage(0);
	}

	if(m_input->IsKeyDown('R'))
	{
		ResetGame();
	}

	///////////////////////////////////////////
	// check if key is pressed down
	///////////////////////////////////////////

	if(m_input->IsKeyDown(PLAYER_UP_KEY) &&
		!m_input->IsKeyDown(PLAYER_DOWN_KEY))
	{
		if(m_input->IsKeyDown(PLAYER_LEFT_KEY) &&
			!m_input->IsKeyDown(PLAYER_RIGHT_KEY))
		{
			// send up left input to control system
			m_controlSystem->SetInput(UpLeft);
		}
		else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY) &&
			!m_input->IsKeyDown(PLAYER_LEFT_KEY))
		{
			// send up right input to control system
			m_controlSystem->SetInput(UpRight);
		}
		else
		{
			// send up input to control system
			m_controlSystem->SetInput(Up);
		}
	}
	else if(m_input->IsKeyDown(PLAYER_DOWN_KEY) &&
		!m_input->IsKeyDown(PLAYER_UP_KEY))
	{
		if(m_input->IsKeyDown(PLAYER_LEFT_KEY) &&
			!m_input->IsKeyDown(PLAYER_RIGHT_KEY))
		{
			// send down left input to control system
			m_controlSystem->SetInput(DownLeft);

		}
		else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY) &&
			!m_input->IsKeyDown(PLAYER_LEFT_KEY))
		{
			// send down right input to control system
			m_controlSystem->SetInput(DownRight);
		}
		else
		{
			// send up input to control system
			m_controlSystem->SetInput(Down);

		}
	}
	else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY) &&
		!m_input->IsKeyDown(PLAYER_LEFT_KEY))
	{
		// send right input to control system
		m_controlSystem->SetInput(Right);

	}
	else if(m_input->IsKeyDown(PLAYER_LEFT_KEY) && 
		!m_input->IsKeyDown(PLAYER_RIGHT_KEY))
	{
		// send left input to control system
		m_controlSystem->SetInput(Left);
	}

	if(m_input->IsKeyDown(PLAYER_A_KEY) &&
		m_controlSystem->CanAttack())
	{
		m_controlSystem->SetInput(Attack);
		m_controlSystem->CanAttack(false);
		return;
	}

	if(!(m_input->IsKeyDown(PLAYER_UP_KEY) ||
		m_input->IsKeyDown(PLAYER_DOWN_KEY) ||
		m_input->IsKeyDown(PLAYER_LEFT_KEY) ||
		m_input->IsKeyDown(PLAYER_RIGHT_KEY) ||
		m_input->IsKeyDown(PLAYER_A_KEY)))
	{
		// set player input to none
		m_controlSystem->SetInput(None);
	}

	if(!m_input->IsKeyDown(PLAYER_A_KEY))
	{
		m_controlSystem->CanAttack(true);
	}
}

void GameplayGameState::Update(float deltaTime)
{
	// update player
	m_player->Update(deltaTime);
	m_enemy->Update(deltaTime);
}

void GameplayGameState::ProcessCollisions()
{
	// check player hitbox vs enemy hurtboxes
	if(m_player->GetHitBoxManager()->IsHitBoxActive())
	{
		if(m_player->GetHitBoxManager()->GetHitBox().OnCollision(
			m_enemy->GetHitBoxManager()->GetHurtBox()))
		{
			m_enemy->ApplyDamage(m_player, 1);
		}
	}

	// check player position against world objects
	if(m_player->GetGroundPosition().y < 61.0f)
	{
		m_player->SetPosition(Vector2(m_player->GetPositionX(), 61.0f));
		m_player->SetCurrentVelocity(Vector2(m_player->GetCurrentVelocity().x, 0.0f));
		m_player->SetTargetVelocity(Vector2(m_player->GetTargetVelocity().x, 0.0f));
	}

	if(m_player->GetGroundPosition().y > m_graphics->GetHeight() - 1)
	{
		m_player->SetPosition(Vector2(m_player->GetPositionX(), m_graphics->GetHeight() - 1));
		m_player->SetCurrentVelocity(Vector2(m_player->GetCurrentVelocity().x, 0.0f));
		m_player->SetTargetVelocity(Vector2(m_player->GetTargetVelocity().x, 0.0f));
	}

	// check enemy position against world objects
	if(m_enemy->GetGroundPosition().y < 61.0f)
	{
		m_enemy->SetPosition(Vector2(m_enemy->GetPositionX(), 61.0f));
		m_enemy->SetCurrentVelocity(Vector2(m_enemy->GetCurrentVelocity().x, 0.0f));
		m_enemy->SetTargetVelocity(Vector2(m_enemy->GetTargetVelocity().x, 0.0f));
	}

	if(m_enemy->GetGroundPosition().y > m_graphics->GetHeight() - 1)
	{
		m_enemy->SetPosition(Vector2(m_enemy->GetPositionX(), m_graphics->GetHeight() - 1));
		m_enemy->SetCurrentVelocity(Vector2(m_enemy->GetCurrentVelocity().x, 0.0f));
		m_enemy->SetTargetVelocity(Vector2(m_enemy->GetTargetVelocity().x, 0.0f));
	}
}

void GameplayGameState::Render()
{
	//////////////////////////////////////
	// render background first
	m_backgroundSprite->Render(m_graphics);

	//////////////////////////////////////
	// render game objects
	m_enemy->Render(m_graphics);
	m_player->Render(m_graphics);
}

void GameplayGameState::ReleaseAll()
{
	// release all texture resources
	if(m_backgroundTexture) { m_backgroundTexture->Release(); }
	if(m_shadowTexture) { m_shadowTexture->Release(); }
	if(m_hitBoxTexture) { m_hitBoxTexture->Release(); }
	if(m_enemyTexture) { m_enemyTexture->Release(); }
	if(m_playerTexture) { m_playerTexture->Release(); }
}

void GameplayGameState::ResetGame()
{
	m_player->Reset();
	m_enemy->Reset();
}
