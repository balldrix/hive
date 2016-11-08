#include "GameplayGameState.h"
#include "GameStateManager.h"
#include "Graphics.h"
#include "Input.h"
#include "Texture.h"
#include "Sprite.h"
#include "Controls.h"

GameplayGameState::GameplayGameState()
{}

GameplayGameState::GameplayGameState(GameStateManager* gameStateManager) :
m_gameStateManager(nullptr),
m_graphics(nullptr),
m_input(nullptr),
m_audio(nullptr),
m_running(false),
GameState(L"GAMEPLAY")
{
	// get essential pointers from gamestate manager
	m_gameStateManager = gameStateManager;
	m_graphics = m_gameStateManager->GetGraphics();
	m_input = m_gameStateManager->GetInput();
	m_audio = m_gameStateManager->GetAudio();
}

GameplayGameState::~GameplayGameState()
{
}

void
GameplayGameState::OnEntry()
{
	// load assets for the gameplay state
	LoadAssets();
}

void
GameplayGameState::OnExit()
{
	// release memory and delete assets
	ReleaseAll();
	DeleteAssets();
}

void
GameplayGameState::LoadAssets()
{
	// seed random generator
	srand((int)time(NULL));

	

	// set running to true
	m_running = true;
}

void
GameplayGameState::DeleteAssets()
{
}

void
GameplayGameState::ProcessInput()
{
	///////////////////////////////////////////
	// check if key is released
	///////////////////////////////////////////

	if(!m_input->IsKeyDown(PLAYER_UP_KEY))
	{
		// move player up
		// m_player.SetTargetVelocityY(0.0f);
		m_inputReady = false;
	}
	else if(!m_input->IsKeyDown(PLAYER_DOWN_KEY))
	{
		// move player down
		// m_player.SetTargetVelocityY(0.0f);
		m_inputReady = false;
	}

	if(!m_input->IsKeyDown(PLAYER_RIGHT_KEY))
	{
		// move player right
		// m_player.SetTargetVelocityX(0.0f);

		m_inputReady = false;
	}
	else if(!m_input->IsKeyDown(PLAYER_LEFT_KEY))
	{
		// move player left
		// m_player.SetTargetVelocityX(0.0f);
		m_inputReady = false;
	}

	// if key input is ready
	if(!m_inputReady)
	{
		if(m_input->IsKeyDown('R'))
		{
			// reset game
			//NewGame();
			m_inputReady = true;
		}
	}

	if(!(m_input->IsKeyDown(PLAYER_UP_KEY) ||
	   m_input->IsKeyDown(PLAYER_DOWN_KEY) ||
	   m_input->IsKeyDown(PLAYER_LEFT_KEY) ||
	   m_input->IsKeyDown(PLAYER_RIGHT_KEY) ||
	   m_input->IsKeyDown(PLAYER_A_KEY) ||
	   m_input->IsKeyDown(PLAYER_B_KEY) ||
	   m_input->IsKeyDown(ENTER_KEY) ||
	   m_input->IsKeyDown(F4_KEY)
	   ))
	{
		m_inputReady = false;
	}
}

void
GameplayGameState::Update(float deltaTime)
{
	
}

void
GameplayGameState::Render()
{
	//////////////////////////////////////
	// render background first
	
}

void
GameplayGameState::ReleaseAll()
{
	m_audio->Reset();
}

void
GameplayGameState::ResetGame()
{
}
