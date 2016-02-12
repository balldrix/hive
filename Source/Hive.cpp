#include "Hive.h"

Hive::Hive() :
m_stateManager(NULL)
{
}

Hive::~Hive()
{
	ReleaseAll();

	if (m_stateManager != NULL)
	{
		delete m_stateManager;
		m_stateManager = NULL;
	}
}

void
Hive::Init(HWND hWindow)
{
	Game::Init(hWindow);

	// create state manager object and add game states needed for game
	m_stateManager = new GameStateManager();
	m_stateManager->CreateGlobalSystems(hWindow, m_pGraphics, m_pInput);
	m_stateManager->AddState(new FrontEnd(m_stateManager));
	m_stateManager->AddState(new ControlScreen(m_stateManager));
	m_stateManager->AddState(new Running(m_stateManager));
	m_stateManager->AddState(new GameOver(m_stateManager));
	m_stateManager->SwitchState("RUNNING");

	m_initialised = true;
}

void 
Hive::Update(float deltaTime)
{
	m_stateManager->Update(deltaTime);
}

void
Hive::Render()
{
	m_stateManager->Render();
}

void
Hive::ReleaseAll()
{
	m_stateManager->ReleaseAll();
	Game::ReleaseAll();
}

void
Hive::ResetAll()
{
	m_stateManager->ResetAll();
	Game::ResetAll();
}
