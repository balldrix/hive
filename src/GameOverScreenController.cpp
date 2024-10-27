#include "GameOverScreenController.h"

#include "Animator.h"
#include "GameOverScreen.h"

GameOverScreenController::GameOverScreenController() :
	m_animator(nullptr),
	m_playerLostScreen(nullptr),
	m_playerWonScreen(nullptr)
{
}

GameOverScreenController::~GameOverScreenController()
{
	DeleteAll();
}

void GameOverScreenController::Init(Graphics* graphics)
{
	m_animator = new Animator();
	//m_animator->Init("data\\AnimationData\\gameOverAnimationData.json");

	m_playerLostScreen = new GameOverScreen();
	m_playerLostScreen->Init(graphics, m_animator, "data\\textures\\UI\\player_won_screen.png");

	m_playerWonScreen = new GameOverScreen();
	m_playerWonScreen->Init(graphics, m_animator, "data\\textures\\UI\\player_won_screen.png");
}

void GameOverScreenController::Update(float deltaTime)
{
	m_playerLostScreen->Update(deltaTime);
	m_playerWonScreen->Update(deltaTime);
}

void GameOverScreenController::Render(Graphics* graphics)
{
	m_playerLostScreen->Render(graphics);
	m_playerWonScreen->Render(graphics);
}

void GameOverScreenController::ReleaseAll()
{
	m_playerLostScreen->Release();
	m_playerWonScreen->Release();
}

void GameOverScreenController::Reset()
{
	m_playerLostScreen->Reset();
	m_playerWonScreen->Reset();
}

void GameOverScreenController::EnableWinScreen()
{
	m_playerWonScreen->Enable();
}

void GameOverScreenController::DeleteAll()
{
	if(m_playerWonScreen != nullptr)
	{
		delete m_playerWonScreen;
		m_playerWonScreen = nullptr;
	}

	if(m_playerLostScreen != nullptr)
	{
		delete m_playerLostScreen;
		m_playerLostScreen = nullptr;
	}

	if(m_animator != nullptr)
	{
		delete m_animator;
		m_animator = nullptr;
	}
}