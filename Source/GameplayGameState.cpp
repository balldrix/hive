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
#include "Dummy.h"
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
	m_dummyTexture(nullptr),
	m_hitBoxTexture(nullptr),
	m_shadowTexture(nullptr),
	m_playerSprite(nullptr),
	m_playerShadowSprite(nullptr),
	m_dummySprite(nullptr),
	m_dummyShadowSprite(nullptr),
	m_hitBoxSprite(nullptr),
	m_playerAnimator(nullptr),
	m_dummyAnimator(nullptr),
	m_player(nullptr),
	m_dummy(nullptr),
	m_playerHitBoxManager(nullptr),
	m_dummyHitBoxManager(nullptr),
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
	m_dummyTexture(nullptr),
	m_hitBoxTexture(nullptr),
	m_shadowTexture(nullptr),
	m_playerSprite(nullptr),
	m_playerShadowSprite(nullptr),
	m_dummySprite(nullptr),
	m_dummyShadowSprite(nullptr),
	m_hitBoxSprite(nullptr),
	m_playerAnimator(nullptr),
	m_dummyAnimator(nullptr),
	m_player(nullptr),
	m_dummy(nullptr),
	m_playerHitBoxManager(nullptr),
	m_dummyHitBoxManager(nullptr),
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
	m_dummyTexture = new Texture();
	m_hitBoxTexture = new Texture();
	m_shadowTexture = new Texture();

	// create sprite memory 
	m_playerSprite = new SpriteSheet();
	m_playerShadowSprite = new Sprite();

	m_dummySprite = new SpriteSheet();
	m_dummyShadowSprite = new Sprite();
	
	m_hitBoxSprite = new Sprite();

	// create animator memory
	m_playerAnimator = new Animator();
	m_dummyAnimator = new Animator();

	// create hitbox managers
	m_playerHitBoxManager = new HitBoxManager();
	m_dummyHitBoxManager = new HitBoxManager();

	// create objects in memory
	m_player = new Player();
	m_dummy = new Dummy();

	// load textures
	m_playerTexture->LoadTexture(m_graphics, "GameData\\Sprites\\playerSpriteSheet.png");
	m_dummyTexture->LoadTexture(m_graphics, "GameData\\Sprites\\dummySpritesheet.png");
	m_hitBoxTexture->LoadTexture(m_graphics, "GameData\\Sprites\\hitbox.png");
	m_shadowTexture->LoadTexture(m_graphics, "GameData\\Sprites\\shadow.png");

	// init sprites
	m_playerSprite->Init(m_playerTexture, "GameData\\SpriteSheetData\\playerSpritesheetData.json");
	m_playerShadowSprite->Init(m_shadowTexture);
	m_dummySprite->Init(m_dummyTexture, "GameData\\SpriteSheetData\\dummySpritesheetData.json");
	m_dummyShadowSprite->Init(m_shadowTexture);
	m_hitBoxSprite->Init(m_hitBoxTexture);

	// init animator
	m_playerAnimator->Init("GameData\\AnimationData\\playerAnimationData.json");
	m_dummyAnimator->Init("GameData\\AnimationData\\dummyAnimationData.json");

	// init hitbox managers
	m_playerHitBoxManager->Init(m_hitBoxSprite, m_player, "GameData\\HitBoxData\\playerHitBoxData.json");
	m_dummyHitBoxManager->Init(m_hitBoxSprite, m_dummy, "GameData\\HitBoxData\\dummyHitBoxData.json");

	// init game objects
	m_player->Init(Vector2((float)PlayerStartScreenPositionX, (float)PlayerStartScreenPositionY), m_playerSprite, m_playerShadowSprite, m_playerAnimator, m_playerHitBoxManager,  m_controlSystem);
	m_dummy->Init(Vector2((float)DummyStartScreenPositionX, (float)DummyStartScreenPositionY), m_dummySprite, m_dummyShadowSprite, m_dummyAnimator, m_dummyHitBoxManager);

	// set running to true
	m_running = true;
}

void GameplayGameState::DeleteAssets()
{
	// delete dummy
	if(m_dummy)
	{
		delete m_dummy;
		m_dummy = nullptr;
	}

	// delete player
	if(m_player)
	{
		delete m_player;
		m_player = nullptr;
	}

	// delete hit box managers
	if(m_dummyHitBoxManager)
	{
		delete m_dummyHitBoxManager;
		m_dummyHitBoxManager = nullptr;
	}

	if(m_playerHitBoxManager)
	{
		delete m_playerHitBoxManager;
		m_playerHitBoxManager = nullptr;
	}

	// delete animators
	if(m_dummyAnimator)
	{
		delete m_dummyAnimator;
		m_dummyAnimator = nullptr;
	}

	if(m_playerAnimator)
	{
		delete m_playerAnimator;
		m_playerAnimator = nullptr;
	}

	// delete sprites
	if(m_hitBoxSprite)
	{
		delete m_hitBoxSprite;
		m_hitBoxSprite = nullptr;
	}

	if(m_dummyShadowSprite)
	{
		delete m_dummyShadowSprite;
		m_dummyShadowSprite = nullptr;
	}

	if(m_dummySprite)
	{
		delete m_dummySprite;
		m_dummySprite = nullptr;
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

	if(m_dummyTexture)
	{
		delete m_dummyTexture;
		m_dummyTexture = nullptr;
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
	if(m_input->IsKeyDown(VK_ESCAPE))
	{
		PostQuitMessage(0);
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
	m_dummy->Update(deltaTime);
}

void GameplayGameState::ProcessCollisions()
{
	if(m_player->GetHitBoxManager()->IsHitBoxActive())
	{
		if(m_player->GetHitBoxManager()->GetHitBox().OnCollision(
			m_dummy->GetHitBoxManager()->GetHurtBox()))
		{
			m_dummy->ApplyDamage(m_player, 1);
		}
	}
}

void GameplayGameState::Render()
{
	//////////////////////////////////////
	// render background first

	//////////////////////////////////////
	// render game objects
	m_dummy->Render(m_graphics);
	m_player->Render(m_graphics);
}

void GameplayGameState::ReleaseAll()
{
	// release all texture resources
	if(m_shadowTexture) { m_shadowTexture->Release(); }
	if(m_hitBoxTexture) { m_hitBoxTexture->Release(); }
	if(m_dummyTexture) { m_dummyTexture->Release(); }
	if(m_playerTexture) { m_playerTexture->Release(); }
}

void GameplayGameState::ResetGame()
{
}
