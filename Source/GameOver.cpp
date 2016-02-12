#include "GameOver.h"
#include "Constants.h"

GameOver::GameOver(GameStateManager* gm) :
m_pGM(gm),
m_pGraphics(NULL),
GameState("GAMEOVER")

{
	m_pGraphics = m_pGM->GetGraphics();
	m_pInput = m_pGM->GetInput();

	
}

GameOver::~GameOver()
{
}

void
GameOver::OnEntry()
{
	LoadAssets();
}

void
GameOver::OnExit()
{
	DeleteAssets();
}

void
GameOver::LoadAssets()
{
	// create new sprites for game over screen
	
}

void
GameOver::DeleteAssets()
{

}

void
GameOver::CheckInput(float deltaTime)
{
	m_inputTimer = 0;

	if (!m_keyPressed)
	{
		m_keyPressed = true;
	}

	if (m_inputTimer > KEY_DELAY)
	{
		m_keyPressed = false;
	}
	else if (!(m_pInput->IsKeyDown(PLAYER_UP_KEY) ||
		m_pInput->IsKeyDown(PLAYER_DOWN_KEY) ||
		m_pInput->IsKeyDown(PLAYER_LEFT_KEY) ||
		m_pInput->IsKeyDown(PLAYER_RIGHT_KEY) ||
		m_pInput->IsKeyDown(ENTER_KEY)
		))
	{
		m_keyPressed = false;
	}

	m_inputTimer += deltaTime;
}

void
GameOver::Update(float deltaTime)
{
	CheckInput(deltaTime);
}

void
GameOver::Render()
{

}

void
GameOver::SelectNext()
{
	
}

void
GameOver::SelectPrevious()
{

}

void
GameOver::SetState(GameOverOptionState state)
{
	m_optionState = state;
}

