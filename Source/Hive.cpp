#include "Hive.h"

Hive::Hive() :
m_stateManager(NULL)
{
}

Hive::~Hive()
{

}

void
Hive::Init(HWND hWindow)
{
	Game::Init(hWindow);



	m_initialised = true;
}

void 
Hive::Update(float deltaTime)
{

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
